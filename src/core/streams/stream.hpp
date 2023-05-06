#pragma once

#include <platform/types.h>
#include <string>
#include <vector>
#include <core/strings.hpp>

class Stream
{
public:
    enum SeekDirection
    {
        SeekDirection_Begin,
        SeekDirection_Current,
        SeekDirection_End
    };

    enum OpenMode
    {
        OpenMode_Read,
        OpenMode_Write,
        OpenMode_ReadWrite
    };

public:
    Stream();
    virtual ~Stream() = default;

    bool Seek(size_t offset, SeekDirection direction = SeekDirection_Begin)
    {
        return this->SeekInternal(offset, direction);
    }

    virtual size_t GetPosition() = 0;

    template<typename T>
    bool Read(T* data)
    {
        return this->ReadBytes((char*)data, sizeof(T));
    }

    template<typename T>
    bool Write(T data)
    {
        return this->WriteBytes((char*)&data, sizeof(T));
    }

    template<typename T>
    bool RawRead(T* data)
    {
        return this->ReadBytes((char*)data, sizeof(T));
    }

    template<typename T>
    bool RawWrite(T data)
    {
        return this->WriteBytes((char*)&data, sizeof(T));
    }

    template<>
    bool Write<Point>(Point data)
    {
        return Write(data.x) && Write(data.y) && Write(data.z);
    }

    template<>
    bool Write<AngAxis>(AngAxis data)
    {
        return Write(data.x) &&
               Write(data.y) &&
               Write(data.z) &&
               Write(data.angle);
    }

    template<>
    bool Write<Polyhedron>(Polyhedron data)
    {
        return Write(data.origin) &&
               Write(data.points[0]) &&
               Write(data.points[1]) &&
               Write(data.points[2]);
    }

    /*template<>
    bool Write<F32>(F32 data)
    {
        // Thanks Rartrin for this function

        if (!mEnableCompression)
            return RawWrite(data);

        //If unable to cast to an integer
        if(data != (S32)data)
        {
            U8 prefix = 0b111<<5;
            return RawWrite(prefix) && RawWrite(*(U32*)&data);
        }
        else
        {
            S32 i = (S32)data;
            if(-16<=i && i<=15)
            {
                U8 prefix = 0b100<<5;
                prefix |= i&0x1F;
                return RawWrite(prefix);
            }
            else if(i == (S8)i)
            {
                U8 prefix = 0b000<<5;
                return RawWrite(prefix) && RawWrite<S8>(i);
            }
            else if(i == (S16)i)
            {
                U8 prefix = 0b001<<5;
                return RawWrite(prefix) && RawWrite<S16>(i);
            }
            else if(i == ((i<<8)>>8))//Int24 (signed)
            {
                U8 prefix = 0b010<<5;
                S24 s = {i};
                return RawWrite(prefix) && RawWrite(s);
            }
            else
            {
                U8 prefix = 0b011<<5;
                return RawWrite(prefix) && RawWrite<S32>(i);
            }
        }

        return true;
    }

    template<>
    bool Read<F32>(F32* data)
    {
        // Thanks Rartrin for this function

        if (!mEnableCompression)
            return RawRead(data);

        U8 prefix;
        if (!RawRead(&prefix))
            return false;

        switch(prefix>>5)
        {
            case 0b000:
            {
                S8 d;
                if (!RawRead(&d))
                    return false;
                *data = d;
                return true;
            }
            case 0b001:
            {
                S16 d;
                if (!RawRead(&d))
                    return false;
                *data = d;
                return true;
            }
            case 0b010:
            {
                S24 d;
                if (!RawRead(&d))
                    return false;
                *data = d.data;
                return true;
            }
            case 0b011:
            {
                S32 d;
                if (!RawRead(&d))
                    return false;
                *data = d;
                return true;
            }
            case 0b111:
            {
                // Raw Float Bits
                return RawRead<U32>((U32*)data);
            }
            case 0b100:
            {
                *data = ((S8)(prefix<<3))>>3; //Signed
                return true;
            }
        }
        //throw "Invalid type";
        return false;
    }*/

    template<> bool Write<F32>(F32 data)
    {
        // Thanks Rartrin for this function

        if (!mEnableCompression)
            return RawWrite(data);

        if (data == -1)
        {
            return RawWrite<U8>(0x7F);
        }

        if(data == 0)
        {
            return RawWrite<U8>(0);
        }
        //If unable to cast to an integer
        if(data != (S32)data)
        {
            U8 prefix = 0x80;
            return RawWrite(prefix) && RawWrite(*(U32*)&data);
        }
        int i = (int)data;

        int neededDataCheck = i<0 ? ~i : i;

        int b=28;
        while(((neededDataCheck>>b)&0x7F) == 0)
        {
            b-=7;
        }
        for(; b>=7; b-=7)
        {
            if(!RawWrite<U8>((U8)(i>>b) | 0x80))
                return false;
        }
        if(!RawWrite<U8>(i&0x7F))
            return false;
        return true;
    }

    template<> bool Read<F32>(F32* data)
    {
        // Thanks Rartrin for this function

        if (!mEnableCompression)
            return RawRead(data);

        U8 val;
        if(!RawRead(&val))
            return false;

        if(val == 0x80)
        {
            // Raw Float Bits
            return RawRead<U32>((U32*)data);
        }

        int ret = val&0x7F;
        while(val&0x80)
        {
            if(!RawRead(&val))
                return false;
            ret = (ret<<7) | (val&0x7F);
        }
        *data = ret;
        return true;
    }

    virtual bool ReadBytes(char* data, size_t size) = 0;
    virtual bool WriteBytes(const char* data, size_t size) = 0;

    template<>
    bool Read<S32>(S32* data)
    {
        if (!mEnableCompression)
            return RawRead(data);
        return Read7BitEncodedIntInternal(data, true);
    }

    template<>
    bool Write<S32>(S32 data)
    {
        if (!mEnableCompression)
            return RawWrite(data);
        return Write7BitEncodedIntInternal(data, true);
    }

    template<>
    bool Read<U32>(U32* data)
    {
        if (!mEnableCompression)
            return RawRead(data);
        return Read7BitEncodedIntInternal((S32*)data, false);
    }

    template<>
    bool Write<U32>(U32 data)
    {
        if (!mEnableCompression)
            return RawWrite(data);
        return Write7BitEncodedIntInternal((S32)data, false);
    }

    bool WriteSTString(const std::string &data);

    bool WriteString(const std::string &data);
    bool WriteCString(const std::string &data);
    bool WriteLenString(const std::string &data);
    bool WriteLocalizedString(const LocalizedString &data);

    std::vector<std::string> GetStringTable() const
    {
        return mStringTable;
    }

    void EnableCompression() { mEnableCompression = true; }
    void DisableCompression() { mEnableCompression = false; }

protected:
    std::vector<std::string> mStringTable;
    bool mEnableCompression;

private:
    virtual bool SeekInternal(size_t offset, SeekDirection direction) = 0;

    bool Read7BitEncodedIntInternal(S32* ret, bool hasSign);
    bool Write7BitEncodedIntInternal(S32 value, bool writeSign);
};

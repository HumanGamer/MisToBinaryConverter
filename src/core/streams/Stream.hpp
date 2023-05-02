#pragma once

#include <platform/types.h>
#include <string>
#include <core/Strings.hpp>

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
    Stream() = default;
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

    virtual bool ReadBytes(char* data, size_t size) = 0;
    virtual bool WriteBytes(const char* data, size_t size) = 0;

    bool Read7BitEncodedInt(S32* ret)
    {
        return Read7BitEncodedIntInternal(ret, true);
    }

    bool Write7BitEncodedInt(S32 value)
    {
        return Write7BitEncodedIntInternal(value, true);
    }

    bool Read7BitEncodedInt(U32* ret)
    {
        return Read7BitEncodedIntInternal((S32*)ret, false);
    }

    bool Write7BitEncodedInt(U32 value)
    {
        return Write7BitEncodedIntInternal((S32)value, false);
    }

    bool WriteString(const std::string &data);
    bool WriteCString(const std::string &data);
    bool WriteLenString(const std::string &data);
    bool WriteLocalizedString(const LocalizedString &data);

private:
    virtual bool SeekInternal(size_t offset, SeekDirection direction) = 0;

    bool Stream::Read7BitEncodedIntInternal(S32* ret, bool hasSign);
    bool Stream::Write7BitEncodedIntInternal(S32 value, bool writeSign);
};

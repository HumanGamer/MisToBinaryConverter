#pragma once

#include <platform/types.h>
#include <string>
#include "Strings.hpp"

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
        return this->ReadInternal((char*)data, sizeof(T));
    }

    template<typename T>
    bool Write(T data)
    {
        return this->WriteInternal((char*)&data, sizeof(T));
    }

    bool WriteString(const std::string &data);
    bool WriteCString(const std::string &data);
    bool WriteLenString(const std::string &data);
    bool WriteLocalizedString(const LocalizedString &data);

private:
    virtual bool ReadInternal(char* data, size_t size) = 0;
    virtual bool WriteInternal(const char* data, size_t size) = 0;
    virtual bool SeekInternal(size_t offset, SeekDirection direction) = 0;
};

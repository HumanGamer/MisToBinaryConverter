#pragma once

#include <platform/types.h>
#include <fstream>
#include <string>
#include "Strings.hpp"

class FileStream
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
    FileStream();
    ~FileStream();

    bool Open(const std::string& filename, OpenMode mode = OpenMode_ReadWrite);

    bool Seek(size_t offset, SeekDirection direction = SeekDirection_Begin);

    size_t GetPosition();
    size_t GetFileSize();

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

protected:
    std::fstream mStream;

private:
    bool ReadInternal(char* data, size_t size);
    bool WriteInternal(const char* data, size_t size);
};
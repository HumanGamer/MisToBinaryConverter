#pragma once

#include <platform/types.h>
#include <fstream>
#include <string>

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
        mStream.read((char*)data, sizeof(T));
        return !mStream.fail();
    }

    template<typename T>
    bool Write(T data)
    {
        mStream.write((char*)&data, sizeof(T));
        return !mStream.fail();
    }

    bool WriteString(const std::string &data);

protected:
    std::fstream mStream;
};
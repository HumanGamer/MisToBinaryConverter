#pragma once

#include <platform/types.h>
#include <fstream>
#include <string>
#include "Stream.hpp"

class FileStream : public Stream
{

public:
    FileStream();
    ~FileStream() override;

    bool Open(const std::string& filename, OpenMode mode = OpenMode_ReadWrite);

    size_t GetFileSize();
    size_t GetPosition() override;

    bool ReadBytes(char* data, size_t size) override;
    bool WriteBytes(const char* data, size_t size) override;

protected:
    std::fstream mStream;

private:
    bool SeekInternal(size_t offset, SeekDirection direction) override;
};
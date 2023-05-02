#include "FileStream.hpp"
#include "Strings.hpp"

FileStream::FileStream() = default;

FileStream::~FileStream()
{
    if (mStream.is_open())
        mStream.close();
}

bool FileStream::Open(const std::string& filename, OpenMode mode)
{
    if (mStream.is_open())
    {
        return false;
    }

    std::ios::openmode openMode = std::ios::binary;
    switch (mode)
    {
    case OpenMode_Read:
        openMode |= std::ios::in;
        break;
    case OpenMode_Write:
        openMode |= std::ios::out;
        break;
    case OpenMode_ReadWrite:
        openMode |= std::ios::in | std::ios::out;
        break;
    }

    mStream.open(filename, openMode);
    return !mStream.fail();
}

bool FileStream::SeekInternal(size_t offset, SeekDirection direction)
{
    switch (direction)
    {
    case SeekDirection_Begin:
        mStream.seekg(offset, std::ios::beg);
        break;
    case SeekDirection_Current:
        mStream.seekg(offset, std::ios::cur);
        break;
    case SeekDirection_End:
        mStream.seekg(offset, std::ios::end);
        break;
    }
    return !mStream.fail();
}

size_t FileStream::GetPosition()
{
    return mStream.tellg();
}

size_t FileStream::GetFileSize()
{
    size_t pos = GetPosition();

    Seek(0, SeekDirection_End);
    size_t size = GetPosition();

    Seek(pos, SeekDirection_Begin);

    return size;
}

bool FileStream::ReadInternal(char *data, size_t size)
{
    mStream.read(data, size);
    return !mStream.fail();
}

bool FileStream::WriteInternal(const char *data, size_t size)
{
    mStream.write(data, size);
    return !mStream.fail();
}

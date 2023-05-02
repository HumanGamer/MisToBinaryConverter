#include "MemStream.hpp"

MemStream::MemStream()
{
    mBuffer = nullptr;
    mBufferSize = 0;
    mPosition = 0;
    mSize = 0;
}

MemStream::MemStream(U8 *data, size_t size)
{
    mBuffer = data;
    mBufferSize = size;
    mPosition = 0;
    mSize = size;
}

MemStream::~MemStream()
{
    delete[] mBuffer;
}

U8 *MemStream::GetBytes() const
{
    // Return buffer with size of stream
    U8 *data = new U8[mSize];
    memcpy(data, mBuffer, mSize);
    return data;
}

size_t MemStream::GetSize() const
{
    return mSize;
}

U8 *MemStream::GetBuffer() const
{
    return mBuffer;
}

size_t MemStream::GetBufferSize() const
{
    return mBufferSize;
}

size_t MemStream::GetPosition()
{
    return mPosition;
}

bool MemStream::ReadInternal(char *data, size_t size)
{
    if (mPosition + size > mBufferSize)
        return false;

    memcpy(data, mBuffer + mPosition, size);
    mPosition += size;
    return true;
}

bool MemStream::WriteInternal(const char *data, size_t size)
{
    if (mPosition + size > mBufferSize)
    {
        size_t newSize = mPosition + size;
        size_t newBufferSize = newSize + (newSize / 2);
        U8 *newBuffer = new U8[newBufferSize];
        memcpy(newBuffer, mBuffer, mBufferSize);
        delete[] mBuffer;
        mBuffer = newBuffer;
        mBufferSize = newBufferSize;
    }

    memcpy(mBuffer + mPosition, data, size);
    mPosition += size;
    mSize += size;
    return true;
}

bool MemStream::SeekInternal(size_t offset, Stream::SeekDirection direction)
{
    switch (direction)
    {
    case Stream::SeekDirection_Begin:
        mPosition = offset;
        break;
    case Stream::SeekDirection_Current:
        mPosition += offset;
        break;
    case Stream::SeekDirection_End:
        mPosition = mBufferSize - offset;
        break;
    }

    return true;
}
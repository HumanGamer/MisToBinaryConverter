#pragma once

#include <platform/types.h>
#include "stream.hpp"

class MemStream : public Stream
{

public:
    MemStream();
    MemStream(U8* data, size_t size);
    ~MemStream() override;

    U8* GetBytes() const;
    size_t GetSize() const;

    U8* GetBuffer() const;
    size_t GetBufferSize() const;

    size_t GetPosition() override;

    bool ReadBytes(char* data, size_t size) override;
    bool WriteBytes(const char* data, size_t size) override;

protected:
    U8* mBuffer;
    size_t mBufferSize;
    size_t mPosition;
    size_t mSize;

private:
    bool SeekInternal(size_t offset, SeekDirection direction) override;
};

#include "Stream.hpp"

bool Stream::WriteString(const std::string &data)
{
    return this->WriteBytes(data.c_str(), data.length());
}

bool Stream::WriteCString(const std::string &data)
{
    if (!this->WriteString(data))
        return false;

    return this->Write('\0');
}

bool Stream::WriteLenString(const std::string &data)
{
    this->Write<uint32_t>(data.length());
    return this->WriteString(data);
}

bool Stream::WriteLocalizedString(const LocalizedString &data)
{
    if (!this->Write(data.IsLocalized()))
        return false;
    return this->WriteCString(data.GetTrimmedValue());
}

bool Stream::Read7BitEncodedIntInternal(S32* ret, bool hasSign)
{
    // Thanks to Rartrin for helping me with this function.

    // Unlike writing, we can't delegate to the 64-bit read on
    // 64-bit platforms. The reason for this is that we want to
    // stop consuming bytes if we encounter an integer overflow.

    U32 result = 0;
    U8 byteReadJustNow;

    // Read the integer 7 bits at a time. The high bit
    // of the byte when on means to continue reading more bytes.
    //
    // There are two failure cases: we've read more than 5 bytes,
    // or the fifth byte is about to cause integer overflow.
    // This means that we can read the first 4 bytes without
    // worrying about integer overflow.

    const int MaxBytesWithoutOverflow = 4;
    for(int shift = 0; shift < MaxBytesWithoutOverflow * 7; shift += 7)
    {
        if(!Read(&byteReadJustNow))
        {
            //End of stream
            *ret = 0;
            return false;
        }
        //Check if 0x80 is off
        if((byteReadJustNow&0x80) == 0)
        {
            if(hasSign && (byteReadJustNow&0x40)!=0)
            {
                result |= (byteReadJustNow & 0x3F) << shift;
                result = ~result;
            }
            else
            {
                result |= (byteReadJustNow & 0x7F) << shift;
            }
            *ret = result;
            return true;
        }
        result |= (byteReadJustNow & 0x7F) << shift;
    }

    // Read the 5th byte. Since we already read 28 bits,
    // the value of this byte must fit within 4 bits (32 - 28),
    // and it must not have the high bit set.

    if(!Read(&byteReadJustNow) || (byteReadJustNow&0xF0)!=0)
    {
        //Invalid format
        *ret = 0;
        return false;
    }
    result |= (U32)byteReadJustNow << (MaxBytesWithoutOverflow * 7);
    //Sign extention is not needed if we read in the full number.

    *ret = result;
    return true;
}

bool Stream::Write7BitEncodedIntInternal(S32 value, bool writeSign)
{
    // Thanks to Rartrin for helping me with this function.

    // Write out an int 7 bits at a time. The high bit of the byte,
    // when on, tells reader to continue reading more bytes.

    bool needsSign = writeSign && value<0;

    U32 uValue = (U32)value;

    if(needsSign)
    {
        uValue = ~uValue;
    }
    while(uValue >= 0x80)
    {
        if (!Write((U8)(uValue | 0x80)))
            return false;
        uValue >>= 7;
    }
    if(needsSign)
    {
        uValue |= 0x40;
    }
    return Write((U8)(uValue));
}

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

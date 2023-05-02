#include "Compression.hpp"

#include <zlib.h>

/*bool CompressMemory(void *in_data, size_t in_data_size, std::vector<U8> &out_data)
{
    std::vector<uint8_t> buffer;

    const size_t BUFSIZE = 128 * 1024;
    uint8_t temp_buffer[BUFSIZE];

    z_stream strm;
    strm.zalloc = 0;
    strm.zfree = 0;
    strm.next_in = reinterpret_cast<uint8_t *>(in_data);
    strm.avail_in = in_data_size;
    strm.next_out = temp_buffer;
    strm.avail_out = BUFSIZE;

    deflateInit(&strm, Z_BEST_COMPRESSION);

    while (strm.avail_in != 0)
    {
        int res = deflate(&strm, Z_NO_FLUSH);
        if(res != Z_OK)
            return false;
        if (strm.avail_out == 0)
        {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFSIZE;
        }
    }

    int deflate_res = Z_OK;
    while (deflate_res == Z_OK)
    {
        if (strm.avail_out == 0)
        {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFSIZE;
        }
        deflate_res = deflate(&strm, Z_FINISH);
    }

    if (deflate_res != Z_STREAM_END)
        return false;
    buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE - strm.avail_out);
    deflateEnd(&strm);

    out_data.swap(buffer);

    return true;
}

bool DecompressMemory(void *in_data, size_t in_data_size, std::vector<U8> &out_data)
{
    unsigned long source_length = in_data_size;
    uLongf destination_length = compressBound(source_length);

    char *destination_data = (char *) malloc(destination_length);
    if (destination_data == nullptr) {
        return Z_MEM_ERROR;
    }

    Bytef *source_data = (Bytef *) in_data;
    int return_value = uncompress((Bytef *) destination_data, &destination_length, source_data, source.size());

    for (int character_index = 0; character_index < destination_length; character_index++) {
        char current_character = destination_data[character_index];
        out_data.push_back(current_character);
    }

    free(destination_data);
    return return_value;
}*/

void add_buffer_to_vector(std::vector<U8> &vector, const char *buffer, uLongf length) {
    for (int character_index = 0; character_index < length; character_index++) {
        char current_character = buffer[character_index];
        vector.push_back(current_character);
    }
}

int CompressMemory(std::vector<U8> source, std::vector<U8> &destination) {
    unsigned long source_length = source.size();
    uLongf destination_length = compressBound(source_length);

    char *destination_data = (char *) malloc(destination_length);
    if (destination_data == nullptr) {
        return Z_MEM_ERROR;
    }

    Bytef *source_data = (Bytef *) source.data();
    int return_value = compress2((Bytef *) destination_data, &destination_length, source_data, source_length,
                                 Z_BEST_COMPRESSION);
    add_buffer_to_vector(destination, destination_data, destination_length);
    free(destination_data);
    return return_value;
}

int DecompressMemory(std::vector<U8> source, std::vector<U8> &destination) {
    unsigned long source_length = source.size();
    uLongf destination_length = compressBound(source_length);

    char *destination_data = (char *) malloc(destination_length);
    if (destination_data == nullptr) {
        return Z_MEM_ERROR;
    }

    Bytef *source_data = (Bytef *) source.data();
    int return_value = uncompress((Bytef *) destination_data, &destination_length, source_data, source.size());
    add_buffer_to_vector(destination, destination_data, destination_length);
    free(destination_data);
    return return_value;
}

#pragma once

#include <platform/types.h>
#include <vector>

extern int CompressMemory(std::vector<U8> source, std::vector<U8> &destination);
extern int DecompressMemory(std::vector<U8> source, std::vector<U8> &destination);

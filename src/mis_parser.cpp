#include "mis_parser.h"
#include <fstream>
#include <MissionParser/Tokenizer.hpp>
#include <MissionParser/Parser.hpp>

bool parse_mis_file(const char* filename, Mission* mis_file)
{
    std::ifstream file;
    file.open(filename, std::ios::binary);
    if (!file.is_open())
        return false;

    file.seekg(0, std::ios::end);
    U64 length = file.tellg();
    file.seekg(0, std::ios::beg);

    char* file_contents = new char[length + 1];
    file.read(file_contents, length);
    file_contents[length] = '\0';
    file.close();

    MissionParser::Tokenizer tokenizer;
    auto tokens = tokenizer.parse(file_contents);

//    for (auto& token : tokens)
//    {
//        token.debugPrint();
//    }

    delete[] file_contents;

    MissionParser::Parser parser;
    parser.parse(tokens);

    parser.debugPrint();

    return true;
}
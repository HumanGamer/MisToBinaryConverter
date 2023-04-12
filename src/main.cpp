#include <iostream>

#include "mis_parser.h"

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char* fileName = argv[1];

    std::cout << "Parsing file: " << fileName << std::endl;

    Mission mis_file;
    if (!parse_mis_file(fileName, &mis_file))
    {
        std::cout << "Failed to parse file" << std::endl;
        return 1;
    }

    std::cout << "Done!" << std::endl;

    return 0;
}

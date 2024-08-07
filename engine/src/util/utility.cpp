#include "utility.h"

std::string ReadFile(std::string path) {
    const char* pathcstr = path.c_str();
    std::ifstream file(path);
    std::string contents;

    if(file.is_open())
    {
        std::ostringstream contentStream;
        contentStream << file.rdbuf();
        contents = contentStream.str();
    }

    file.close();

    return contents;
}
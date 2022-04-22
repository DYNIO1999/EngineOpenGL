#ifndef DENGINE_HELPERS_H
#define DENGINE_HELPERS_H

#include <cstdio>
#include <string>
#include <cerrno>
#include <stdexcept>

namespace DEngine{
    static std::string readFile(const std::string& filename)
    {
        std::FILE *fp = std::fopen(filename.c_str(), "rb");
        if (fp)
        {
            std::string contents;
            std::fseek(fp, 0, SEEK_END);
            contents.resize(std::ftell(fp));
            std::rewind(fp);
            std::fread(&contents[0], 1, contents.size(), fp);
            std::fclose(fp);
            return(contents);
        }
        DENGINE_ERROR("Cant open the file: {}",filename);
        throw errno;
    }
}
#endif
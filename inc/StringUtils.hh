#pragma once
#include <string>

class StringUtils
{
    public:
        StringUtils();
        ~StringUtils();

        std::string toUpperCase(std::string&);
        bool iequals(const std::string&, const std::string&);
};
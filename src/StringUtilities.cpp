#include "../inc/StringUtilities.hh"

#include <algorithm>

std::string StringUtilities::toUpperCase(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    return str;
}

bool StringUtilities::iequals(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}
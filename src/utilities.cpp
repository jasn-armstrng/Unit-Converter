#include "../headers/common.h"

// Function definitions
std::string to_upper(const std::string& str)
{
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c)
    {
        return std::toupper(c);
    });
    return upperStr;
}

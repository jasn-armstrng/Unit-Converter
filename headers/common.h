#ifndef COMMON_H
#define COMMON_H

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

// Map declarations
extern std::unordered_map<std::string, std::unordered_map<std::string, double>> conversions;
extern std::unordered_map<std::string, std::vector<std::string>> constants;

// Function declarations
std::string to_upper(const std::string& str);

#endif

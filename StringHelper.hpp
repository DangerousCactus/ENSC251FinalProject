#ifndef STRINGHELPER_HPP
#define STRINGHELPER_HPP
#include <iostream>
#include <string>

namespace StringHelper {
const std::string PROVINCES[] = {"NL", "PE", "NS", "NB", "QC", "ON", "MB",
                           "SK", "AB", "BC", "YT", "NT", "NU"};

const std::string COUNTRIES[] = {"CANADA", "CHINA", "INDIA", "IRAN", "KOREA"};
const std::string MENU_OPTIONS[] = {"INSERT", "SEARCH", "DELETE", "MERGE"};

std::string toUpper(std::string str);
bool isProvince(std::string province);
bool isCountry(std::string country);
bool isAnagramOf(std::string str1, std::string str2);
bool isValidMenuOption(std::string option);
}  // namespace StringHelper
#endif
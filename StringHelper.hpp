#ifndef STRINGHELPER_HPP
#define STRINGHELPER_HPP
#include <iostream>
#include <string>

// Use a namespace so we don't clutter the global namespace
namespace StringHelper {
// Abbreviations of Canadian provinces
const std::string PROVINCES[] = {"NL", "PE", "NS", "NB", "QC", "ON", "MB",
                                 "SK", "AB", "BC", "YT", "NT", "NU"};

// The countries in our test set
const std::string COUNTRIES[] = {"Canada", "China", "India", "Iran", "Korea"};
const std::string MENU_OPTIONS[] = {"INSERT", "SEARCH", "DELETE", "MERGE"};

// Returns the given string converted to upper case
std::string toUpper(std::string str);

// Checks the given province against our list of 13 provinces
bool isProvince(std::string province);

// Checks the given country against our list of 5 countries
bool isCountry(std::string country);

// Check if one string is an anagram of another
// Precondition: Both strings must be alphabetical ONLY
bool isAnagramOf(std::string str1, std::string str2);

// Check if the provided option is in our list of known menu options
bool isValidMenuOption(std::string option);

// If the given country string is an anagram of a known country, assume a typo
// and return the proper name of the country. Else, return an empty string.
std::string anagramOfCountry(std::string country);
}  // namespace StringHelper
#endif
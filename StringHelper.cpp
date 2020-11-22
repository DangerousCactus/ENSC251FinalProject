#include "StringHelper.hpp"
#include <iostream>
#include <string>

namespace StringHelper {

std::string toUpper(std::string str) {
  std::string temp;
  for (std::string::const_iterator i = str.begin(); i != str.end(); i++)
    temp.push_back(toupper(*i));

  return temp;
}

bool isProvince(std::string province) {
  std::string tempProvince = toUpper(province);
  for (int i = 0; i < sizeof(PROVINCES) / sizeof(PROVINCES[0]); i++)
    if (tempProvince == PROVINCES[i])
      return true;

  return false;
}

bool isCountry(std::string country) {
  std::string tempCountry = toUpper(country);
  for (int i = 0; i < sizeof(COUNTRIES) / sizeof(COUNTRIES[0]); i++)
    if (tempCountry == toUpper(COUNTRIES[i]))
      return true;

  return false;
}

bool isValidMenuOption(std::string option) {
  std::string tempCountry = toUpper(option);
  for (int i = 0; i < sizeof(MENU_OPTIONS) / sizeof(MENU_OPTIONS[0]); i++)
    if (tempCountry == MENU_OPTIONS[i])
      return true;

  return false;
}

// Both strings must be alphabetical only
bool isAnagramOf(std::string str1, std::string str2) {
  int letterCount1[26] = {0};
  int letterCount2[26] = {0};
  if (str1.length() != str2.length())
    return false;

  for (int i = 0; i < str1.length(); i++) {
    letterCount1[toupper(str1[i]) - 'A'] += 1;
    letterCount2[toupper(str2[i]) - 'A'] += 1;
  }

  for (int i = 0; i < 26; i++)
    if (letterCount1[i] != letterCount2[i])
      return false;

  return true;
}

std::string anagramOfCountry(std::string country) {
  std::string tempCountry = toUpper(country);
  for (int i = 0; i < sizeof(COUNTRIES) / sizeof(COUNTRIES[0]); i++)
    if (isAnagramOf(tempCountry, toUpper(COUNTRIES[i])))
      return COUNTRIES[i];

  return "";
}

}  // namespace StringHelper

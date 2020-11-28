#include "StringHelper.hpp"
#include <iostream>
#include <string>

namespace StringHelper {

std::string toUpper(std::string str) {
  std::string temp;
  // Iterate over the string
  for (std::string::const_iterator i = str.begin(); i != str.end(); i++)
    // Capitalize the character and save it
    temp.push_back(toupper(*i));

  return temp;
}

bool isProvince(std::string province) {
  std::string tempProvince = toUpper(province);
  // Iterate over the list of known provinces
  for (int i = 0; i < sizeof(PROVINCES) / sizeof(PROVINCES[0]); i++)
    if (tempProvince == PROVINCES[i])
      return true;

  return false;
}

bool isCountry(std::string country) {
  std::string tempCountry = toUpper(country);
  // Iterate over the list of known countries
  for (int i = 0; i < sizeof(COUNTRIES) / sizeof(COUNTRIES[0]); i++)
    if (tempCountry == toUpper(COUNTRIES[i]))
      return true;

  return false;
}

bool isValidMenuOption(std::string option) {
  std::string tempCountry = toUpper(option);
  // Iterate over the list of known menu options
  for (int i = 0; i < sizeof(MENU_OPTIONS) / sizeof(MENU_OPTIONS[0]); i++)
    if (tempCountry == MENU_OPTIONS[i])
      return true;

  return false;
}

bool isAnagramOf(std::string str1, std::string str2) {
  // Keep track of the frequency of each letter
  int diff = 0;
  int letterCount1[26] = {0};
  int letterCount2[26] = {0};

  // Ensure that the length of the strings differ by atmost 1
  if (abs(str1.length() - str2.length()) > 1)
    return false;

  for (int i = 0; i < str1.length(); i++)
    letterCount1[toupper(str1[i]) - 'A'] += 1;

  for (int i = 0; i < str2.length(); i++)
    letterCount2[toupper(str2[i]) - 'A'] += 1;

  // If the letter counts match, then we have a valid anagram
  for (int i = 0; i < 26; i++)
    diff += abs(letterCount1[i] - letterCount2[i]);

  return diff <= AUTOCORRECT_TOLERANCE + AUTOCORRECT_TOLERANCE / 2;
}

std::string anagramOfCountry(std::string country) {
  std::string tempCountry = toUpper(country);
  for (int i = 0; i < sizeof(COUNTRIES) / sizeof(COUNTRIES[0]); i++)
    if (isAnagramOf(tempCountry, toUpper(COUNTRIES[i])))
      return COUNTRIES[i];

  return "";
}

}  // namespace StringHelper

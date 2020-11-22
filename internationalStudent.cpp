#include "internationalStudent.hpp"
#include "TOEFLScore.hpp"

#include <iomanip>
#include <iostream>

InternationalStudent::InternationalStudent(std::string firstName,
                                           std::string lastName, float cgpa,
                                           int reseachScore, int applicationID,
                                           std::string country,
                                           ToeflScore toefl)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->country = country;
  this->toefl = toefl;
}

InternationalStudent::InternationalStudent(std::string firstName,
                                           std::string lastName, float cgpa,
                                           int reseachScore, int applicationID,
                                           std::string country, int reading,
                                           int listening, int speaking,
                                           int writing)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->country = country;
  this->toefl = ToeflScore(reading, listening, speaking, writing);
}

InternationalStudent::InternationalStudent() : Student(){};

// Getters

std::string InternationalStudent::getCountry() const {
  return country;
}
std::string InternationalStudent::getLocation() const {
  return country;
}
ToeflScore InternationalStudent::getToefl() const {
  return toefl;
}

// Setters
void InternationalStudent::setCountry(std::string country) {
  this->country = country;
}
void InternationalStudent::setToefl(ToeflScore toefl) {
  this->toefl = toefl;
}
std::ostream& InternationalStudent::print(std::ostream& outs) const {
  Student::print(outs);  // Call super
  outs << " | Country: " << std::setw(10) << country;
  outs << " | " << toefl;
  return outs;
}

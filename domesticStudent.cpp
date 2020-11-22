#include "domesticStudent.hpp"
#include <iostream>

DomesticStudent::DomesticStudent(std::string firstName, std::string lastName,
                                 float cgpa, int reseachScore,
                                 int applicationID, std::string province)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->province = province;
}

DomesticStudent::DomesticStudent() : Student(){};

// Getters
std::string DomesticStudent::getLocation() const {
  return province;
}
std::string DomesticStudent::getProvince() const {
  return province;
}
// Setters
void DomesticStudent::setProvince(std::string province) {
  this->province = province;
}

std::ostream& DomesticStudent::print(std::ostream& outs) const {
  Student::print(outs);  // Call super
  outs << " | Province: " << province;
  return outs;
}
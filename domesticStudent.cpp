#include "domesticStudent.hpp"
#include <iostream>

DomesticStudent::DomesticStudent(string firstName, string lastName, float cgpa,
                                 int reseachScore, int applicationID,
                                 string province)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->province = province;
}

DomesticStudent::DomesticStudent() : Student(){};

// Gets
string DomesticStudent::getProvince() const {
  return province;
}

// Sets
void DomesticStudent::setProvince(string province) {
  this->province = province;
}

// Overloads the << operator to output the province
ostream& operator<<(ostream& outs, const DomesticStudent& student) {
  outs << static_cast<Student>(student);
  outs << " | Province: " << student.province;

  return outs;
}

// sortByLocation
// Sorts students by location based on province in ascending order
void sortByLocation(DomesticStudent* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (students[j + 1]->province < students[j]->province)
        swap(students[j], students[j + 1]);
}

// sortByOverall
// Sorts students by Research Score first, then CGPA. If same CGPA,
// Province is used in ascending order.
void sortByOverall(DomesticStudent* students[], int len) {
  sortByLocation(students, len);
  sortByOverall((Student**)students, len);
}
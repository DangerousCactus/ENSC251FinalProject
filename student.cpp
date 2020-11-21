#include "student.hpp"
#include <iomanip>
#include <iostream>
#include "domesticStudent.hpp"
#include "internationalStudent.hpp"

Student::Student(std::string firstName, std::string lastName, float CGPA,
                 int reseachScore, int applicationID)
    : firstName(firstName), lastName(lastName), CGPA(CGPA),
      researchScore(reseachScore), applicationID(applicationID) {}

Student::Student() {}

// Gets
std::string Student::getFirstName() const {
  return firstName;
}
std::string Student::getLastName() const {
  return lastName;
}
float Student::getCGPA() const {
  return CGPA;
}
int Student::getResearchScore() const {
  return researchScore;
}
int Student::getApplicationID() const {
  return applicationID;
}
std::string Student::getLocation() const {
  return "";
}

// Sets
void Student::setFirstName(std::string name) {
  firstName = name;
}
void Student::setLastName(std::string name) {
  lastName = name;
}
void Student::setCGPA(float CGPA) {
  this->CGPA = CGPA;
}
void Student::setResearchScore(int researchScore) {
  this->researchScore = researchScore;
}
void Student::setApplicationID(int applicationID) {
  this->applicationID = applicationID;
}

// Compares two students' CGPAs
int compareCGPA(const Student& student1, const Student& student2) {
  if (student1.CGPA < student2.CGPA)
    return -1;
  else
    return student1.CGPA > student2.CGPA;
}

// Compares two students' Research Scores
int compareResearchScore(const Student& student1, const Student& student2) {
  if (student1.researchScore < student2.researchScore)
    return -1;
  else
    return student1.researchScore > student2.researchScore;
}

// Compares two students' First Names
int compareFirstName(const Student& student1, const Student& student2) {
  if (student1.firstName < student2.firstName)
    return -1;
  else
    return student1.firstName > student2.firstName;
}

// Compares two students' Last Names
int compareLastName(const Student& student1, const Student& student2) {
  if (student1.lastName < student2.lastName)
    return -1;
  else
    return student1.lastName > student2.lastName;
}

// Overloads << operator to output student information including:
// First Name, Last Name, CGPA, Research Score, Application ID.
std::ostream& Student::print(std::ostream& outs) const {
  outs << std::setw(15) << std::left << firstName << ' ' << std::setw(15)
       << std::left << lastName << " | "
       << "CGPA: " << std::setw(4) << CGPA << " | "
       << "Research Score: " << std::setw(3) << researchScore << " | "
       << "Application ID: " << applicationID;

  return outs;
}

std::ostream& operator<<(std::ostream& outs, const Student& student) {
  return student.print(outs);
}

bool operator<(const Student& student1, const Student& student2) {
  if (student1.researchScore < student2.researchScore) {
    return true;
  } else if (student1.researchScore > student2.researchScore) {
    return false;
  } else {
    if (student1.CGPA < student2.CGPA) {
      return true;
    } else if (student1.CGPA > student2.CGPA) {
      return false;
    } else {
      if (student1.getLocation() < student2.getLocation()) {
        return false;
      } else {
        return true;
      }
    }
  }
}

bool operator>(const Student& student2, const Student& student1) {
  if (student1.researchScore < student2.researchScore) {
    return true;
  } else if (student1.researchScore > student2.researchScore) {
    return false;
  } else {
    if (student1.CGPA < student2.CGPA) {
      return true;
    } else if (student1.CGPA > student2.CGPA) {
      return false;
    } else {
      if (student1.getLocation() < student2.getLocation()) {
        return false;
      } else {
        return true;
      }
    }
  }
}

// Bubble sort is implemented below for sorting functions. Since bubble sort
// will only move an element if it is strictly greater than its right most
// neighbour, we can apply bubble sort in a reverse order to accomplish
// overall sorting

// Sorts students by CGPA in Decending order
void sortByCGPA(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareCGPA(*students[j], *students[j + 1]) < 0)
        std::swap(students[j], students[j + 1]);
}

// Sorts students by Research Score in Decending order
void sortByResearchScore(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareResearchScore(*students[j], *students[j + 1]) < 0)
        std::swap(students[j], students[j + 1]);
}

// Sorts students by First Name in Alphabetical order (A -> Z)
void sortByFirstName(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareFirstName(*students[j], *students[j + 1]) > 0)
        std::swap(students[j], students[j + 1]);
}

// Sorts students by Last Name in Alphabetical order (A -> Z)
void sortByLastName(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareLastName(*students[j], *students[j + 1]) > 0)
        std::swap(students[j], students[j + 1]);
}

// sortByOverall
// Sorts students by Research Score first, then CGPA. If same CGPA,
// Province or Country is used in ascending order (A - Z).
void sortByOverall(Student* students[], int& len) {
  sortByCGPA(students, len);
  sortByResearchScore(students, len);
}

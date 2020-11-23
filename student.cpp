#include "student.hpp"
#include <iomanip>
#include <iostream>
#include "StringHelper.hpp"
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
// Case insensitive
int compareFirstName(const Student& student1, const Student& student2) {
  std::string name1 = StringHelper::toUpper(student1.firstName);
  std::string name2 = StringHelper::toUpper(student2.firstName);

  if (name1 < name2)
    return -1;
  else
    return name1 > name2;
}

// Compares two students' Last Names
// Case insensitive
int compareLastName(const Student& student1, const Student& student2) {
  std::string name1 = StringHelper::toUpper(student1.firstName);
  std::string name2 = StringHelper::toUpper(student2.firstName);

  if (name1 < name2)
    return -1;
  else
    return name1 > name2;
}

std::ostream& Student::print(std::ostream& outs) const {
  outs << std::setw(15) << std::left << firstName << ' ' << std::setw(15)
       << std::left << lastName << " | "
       << "CGPA: " << std::setw(4) << std::setprecision(2) << std::fixed << CGPA
       << " | "
       << "Research Score: " << std::setw(3) << researchScore << " | "
       << "Application ID: " << applicationID;

  return outs;
}
// Overloads << operator to output student information including:
// First Name, Last Name, CGPA, Research Score, Application ID.
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
      // Compare by location only if the students are either both domestic or
      // both international.
      if (StringHelper::toUpper(student1.getLocation()) <=
              StringHelper::toUpper(student2.getLocation()) ||
          (student1.getLocation().size() == 2 &&
           student2.getLocation().size() != 2) ||
          (student1.getLocation().size() != 2 &&
           student2.getLocation().size() == 2)) {
        return false;
      } else {
        return true;
      }
    }
  }
}

bool operator>(const Student& student1, const Student& student2) {
  return student2 < student1;
}
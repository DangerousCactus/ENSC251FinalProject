#include "student.hpp"
#include <iostream>

Student::Student(string firstName, string lastName, float cgpa,
                 int reseachScore, int applicationID)
    : firstName(firstName), lastName(lastName), cgpa(cgpa),
      researchScore(reseachScore), applicationID(applicationID) {}

Student::Student() {}

// Gets
string Student::getFirstName() const {
  return firstName;
}
string Student::getLastName() const {
  return lastName;
}
float Student::getcgpa() const {
  return cgpa;
}
int Student::getResearchScore() const {
  return researchScore;
}
int Student::getApplicationID() const {
  return applicationID;
}

// Sets
void Student::setFirstName(string name) {
  firstName = name;
}
void Student::setLastName(string name) {
  lastName = name;
}
void Student::setcgpa(float cgpa) {
  this->cgpa = cgpa;
}
void Student::setResearchScore(int researchScore) {
  this->researchScore = researchScore;
}
void Student::setApplicationID(int applicationID) {
  this->applicationID = applicationID;
}

//
int compareCGPA(const Student student1, const Student student2) {
  if (student1.cgpa < student2.cgpa)
    return -1;
  else
    return student1.cgpa > student2.cgpa;
}

//
int compareResearchScore(const Student student1, const Student student2) {
  if (student1.researchScore < student2.researchScore)
    return -1;
  else
    return student1.researchScore > student2.researchScore;
}

//
int compareFirstName(const Student student1, const Student student2) {
  if (student1.firstName < student2.firstName)
    return -1;
  else
    return student1.firstName > student2.firstName;
}

//
int compareLastName(const Student student1, const Student student2) {
  if (student1.lastName < student2.lastName)
    return -1;
  else
    return student1.lastName > student2.lastName;
}

// Overloads << operator to output student information including: 
// First Name, Last Name, CGPA, Research Score, Application ID.
ostream& operator<<(ostream& outs, const Student& student) {
  outs << "First Name: " << student.firstName << '\n';
  outs << "Last Name: " << student.lastName << '\n';
  outs << "CGPA: " << student.cgpa << '\n';
  outs << "Research Score: " << student.researchScore << '\n';
  outs << "Application ID: " << student.applicationID << '\n';

  return outs;
}

// Sorts students by CGPA in Decending order
void sortByCGPA(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareCGPA(*students[j], *students[j + 1]) < 0)
        swap(students[j], students[j + 1]);
}

// Sorts students by Research Score in Decending order
void sortByResearchScore(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareResearchScore(*students[j], *students[j + 1]) < 0)
        swap(students[j], students[j + 1]);
}

// Sorts students by First Name in Alphabetical order (A -> Z)
void sortByFirstName(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareFirstName(*students[j], *students[j + 1]) > 0)
        swap(students[j], students[j + 1]);
}

// Sorts students by Last Name in Alphabetical order (A -> Z)
void sortByLastName(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (compareLastName(*students[j], *students[j + 1]) > 0)
        swap(students[j], students[j + 1]);
}

// sortByOverall
// Sorts students by Research Score first, then CGPA. If same CGPA, 
// Province or Country is used in ascending order (A - Z).
void sortByOverall(Student* students[], int& len) {
  sortByCGPA(students, len);
  sortByResearchScore(students, len);
}

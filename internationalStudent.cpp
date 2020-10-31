#include "internationalStudent.hpp"
#include "TOEFLScore.hpp"

using namespace std;
#include <iomanip>
#include <iostream>

InternationalStudent::InternationalStudent(string firstName, string lastName,
                                           float cgpa, int reseachScore,
                                           int applicationID, string country,
                                           ToeflScore toefl)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->country = country;
  this->toefl = toefl;
}

InternationalStudent::InternationalStudent(string firstName, string lastName,
                                           float cgpa, int reseachScore,
                                           int applicationID, string country,
                                           int reading, int listening,
                                           int speaking, int writing)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->country = country;
  this->toefl = ToeflScore(reading, listening, speaking, writing);
}

InternationalStudent::InternationalStudent() : Student(){};

// Gets
string InternationalStudent::getCountry() const {
  return country;
}
ToeflScore InternationalStudent::getToefl() const {
  return toefl;
}

// Sets
void InternationalStudent::setCountry(string country) {
  this->country = country;
}
void InternationalStudent::setToefl(ToeflScore toefl) {
  this->toefl = toefl;
}

// Overloads the << operator to output the country
ostream& operator<<(ostream& outs, const InternationalStudent& student) {
  outs << static_cast<Student>(student);
  outs << " | Country: " << setw(10) << student.country;
  outs << " | " << student.toefl;
  return outs;
}

// sortByLocation
// Sorts students by location based on country in ascending order (A - Z).
void sortByLocation(InternationalStudent* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (students[j + 1]->country < students[j]->country)
        swap(students[j], students[j + 1]);
}

// removeLowToeflScores
<<<<<<< HEAD
// Drops student if their TOEFL scores does not meet the threshold
=======
//
>>>>>>> origin/main
void removeLowToeflScores(InternationalStudent* students[], int& len) {
  int i = 0;
  while (i < len) {
    if (students[i]->toefl.getlistening() < 20 ||
        students[i]->toefl.getReading() < 20 ||
        students[i]->toefl.getWriting() < 20 ||
        students[i]->toefl.getSpeaking() < 20 ||
        students[i]->toefl.getTotal() < 93) {
      // cout << students[i]->firstName << students[i]->lastName <<
      // students[i]->toefl;
      swap(students[i], students[len - 1]);
      len--;
    } else {
      i++;
    }
  }
}

// sortByOverall
<<<<<<< HEAD
// Sorts students by Research Score first, then CGPA. If same CGPA, 
// Country is used in ascending order (A - Z).
=======
// Sorts students by Research Score first, then CGPA. If same CGPA,
// Country is used in ascending order.
>>>>>>> origin/main
void sortByOverall(InternationalStudent* students[], int& len) {
  removeLowToeflScores(students, len);
  sortByLocation(students, len);
  sortByOverall((Student**)students, len);
}

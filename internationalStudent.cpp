#include "internationalStudent.hpp"
#include "TOEFLScore.hpp"

using namespace std;
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

string InternationalStudent::getCountry() const {
  return country;
}
ToeflScore InternationalStudent::getToefl() const {
  return toefl;
}

void InternationalStudent::setCountry(string country) {
  this->country = country;
}
void InternationalStudent::setToefl(ToeflScore toefl) {
  this->toefl = toefl;
}
ostream& operator<<(ostream& outs, const InternationalStudent& student) {
  outs << static_cast<Student>(student);
  outs << "Country: " << student.country << '\n';
  outs << student.toefl;
  return outs;
}
void sortByLocation(InternationalStudent* students[], int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - 1 - i; j++)
      if (students[j + 1]->country < students[j]->country)
        swap(students[j], students[j + 1]);
}
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
void sortByOverall(InternationalStudent* students[], int& len) {
  removeLowToeflScores(students, len);
  sortByLocation(students, len);
  sortByOverall((Student**)students, len);
}

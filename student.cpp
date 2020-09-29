// student.cpp to implement your classes
#include "student.hpp"

Student::Student(string firstName,
                 string lastName,
                 float cgpa,
                 int reseachScore,
                 int applicationID)
    : firstName(firstName),
      lastName(lastName),
      cgpa(cgpa),
      researchScore(reseachScore),
      applicationID(applicationID) {}

Student::Student(){};

string Student::getFirstName() {
  return firstName;
}
string Student::getLastName() {
  return lastName;
}
float Student::getcgpa() {
  return cgpa;
}
int Student::getResearchScore() {
  return researchScore;
}
int Student::getApplicationID() {
  return applicationID;
}

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

DomesticStudent::DomesticStudent(string firstName,
                                 string lastName,
                                 float cgpa,
                                 int reseachScore,
                                 int applicationID,
                                 string province)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->province = province;
}

DomesticStudent::DomesticStudent() : Student(){};

string DomesticStudent::getProvince() {
  return province;
};
void DomesticStudent::setProvince(string province) {
  this->province = province;
};

InternationalStudent::InternationalStudent(string firstName,
                                           string lastName,
                                           float cgpa,
                                           int reseachScore,
                                           int applicationID,
                                           string country,
                                           ToeflScore toefl)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->country = country;
  this->toefl = toefl;
}

InternationalStudent::InternationalStudent() : Student(){};

string InternationalStudent::getCountry() {
  return country;
};
ToeflScore InternationalStudent::getToefl() {
  return toefl;
};

void InternationalStudent::setCountry(string country) {
  this->country = country;
};
void InternationalStudent::getToefl(ToeflScore toefl) {
  this->toefl = toefl;
}

ToeflScore::ToeflScore(int reading,
                       int listening,
                       int speaking,
                       int writing,
                       int total)
    : reading(reading),
      listening(listening),
      speaking(speaking),
      writing(writing),
      total(total) {}

ToeflScore::ToeflScore(int reading, int listening, int speaking, int writing)
    : reading(reading),
      listening(listening),
      speaking(speaking),
      writing(writing) {
  this->total = reading + listening + speaking + writing;
}

ToeflScore::ToeflScore() {}

void ToeflScore::setReading(int score) {
  reading = score;
};
void ToeflScore::setlistening(int score) {
  listening = score;
};
void ToeflScore::setSpeaking(int score) {
  speaking = score;
};
void ToeflScore::setWriting(int score) {
  writing = score;
};
void ToeflScore::setTotal(int score) {
  total = score;
};

int ToeflScore::getReading() {
  return reading;
};
int ToeflScore::getlistening() {
  return listening;
};
int ToeflScore::getSpeaking() {
  return speaking;
};
int ToeflScore::getWriting() {
  return writing;
};
int ToeflScore::getTotal() {
  return total;
};
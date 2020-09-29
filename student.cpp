// student.cpp to implement your classes
#include "student.hpp"
#include <iostream>

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

string DomesticStudent::getProvince() const {
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

InternationalStudent::InternationalStudent(string firstName,
                                           string lastName,
                                           float cgpa,
                                           int reseachScore,
                                           int applicationID,
                                           string country,
                                           int reading,
                                           int listening,
                                           int speaking,
                                           int writing)
    : Student(firstName, lastName, cgpa, reseachScore, applicationID) {
  this->country = country;
  this->toefl = ToeflScore(reading, listening, speaking, writing);
}

InternationalStudent::InternationalStudent() : Student(){};

string InternationalStudent::getCountry() const {
  return country;
};
ToeflScore InternationalStudent::getToefl() const {
  return toefl;
};

void InternationalStudent::setCountry(string country) {
  this->country = country;
};
void InternationalStudent::setToefl(ToeflScore toefl) {
  this->toefl = toefl;
}

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

int ToeflScore::getReading() const {
  return reading;
};
int ToeflScore::getlistening() const {
  return listening;
};
int ToeflScore::getSpeaking() const {
  return speaking;
};
int ToeflScore::getWriting() const {
  return writing;
};
int ToeflScore::getTotal() const {
  return total;
};

int compareCGPA(const Student student1, const Student student2) {
  if (student1.cgpa > student2.cgpa) {
    return 1;
  } else if (student1.cgpa < student2.cgpa) {
    return -1;
  } else {
    return 0;
  }
};
int compareResearchScore(const Student student1, const Student student2) {
  if (student1.researchScore > student2.researchScore) {
    return 1;
  } else if (student1.researchScore < student2.researchScore) {
    return -1;
  } else {
    return 0;
  }
};
int compareFirstName(const Student student1, const Student student2) {
  if (student1.firstName > student2.firstName) {
    return 1;
  } else if (student1.firstName < student2.firstName) {
    return -1;
  } else {
    return 0;
  }
};
int compareLastName(const Student student1, const Student student2) {
  if (student1.lastName > student2.lastName) {
    return 1;
  } else if (student1.lastName < student2.lastName) {
    return -1;
  } else {
    return 0;
  }
};

ostream& operator<<(ostream& outs, const Student& student) {
  outs << "First Name: " << student.firstName << '\n';
  outs << "Last Name: " << student.lastName << '\n';
  outs << "CGPA: " << student.cgpa << '\n';
  outs << "Research Score: " << student.researchScore << '\n';
  outs << "Application ID: " << student.applicationID << '\n';

  return outs;
};

ostream& operator<<(ostream& outs, const DomesticStudent& student) {
  outs << static_cast<Student>(student);
  outs << "Province: " << student.province << '\n';

  return outs;
};

ostream& operator<<(ostream& outs, const InternationalStudent& student) {
  outs << static_cast<Student>(student);
  outs << "Country: " << student.country << '\n';
  outs << student.toefl;
  return outs;
};

ostream& operator<<(ostream& outs, const ToeflScore& score) {
  outs << "TOEFL Scores:  Reading: " << score.reading
       << " | Listening: " << score.listening
       << " | Speaking: " << score.speaking << " | Writing: " << score.writing
       << '\n';

  return outs;
};

void sortByCgpa(Student* students[], int len) {
  Student* temp;

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (students[j]->cgpa < students[j + 1]->cgpa) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
};

void sortByResearchScore(Student* students[], int len) {
  Student* temp;

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (students[j]->researchScore < students[j + 1]->researchScore) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
};

void sortByFirstName(Student* students[], int len) {
  Student* temp;

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (students[j + 1]->firstName < students[j]->firstName) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
};

void sortByLastName(Student* students[], int len) {
  Student* temp;

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (students[j + 1]->lastName < students[j]->lastName) {
        temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
};
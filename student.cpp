#include "student.hpp"
#include <iostream>

Student::Student(string firstName, string lastName, float cgpa,
                 int reseachScore, int applicationID)
    : firstName(firstName), lastName(lastName), cgpa(cgpa),
      researchScore(reseachScore), applicationID(applicationID) {}

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

DomesticStudent::DomesticStudent(string firstName, string lastName, float cgpa,
                                 int reseachScore, int applicationID,
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
    : reading(reading), listening(listening), speaking(speaking),
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
  if (student1.cgpa < student2.cgpa) {
    return -1;
  } else {
    return student1.cgpa > student2.cgpa;
  }
};
int compareResearchScore(const Student student1, const Student student2) {
  if (student1.researchScore < student2.researchScore) {
    return -1;
  } else {
    return student1.researchScore > student2.researchScore;
  }
};
int compareFirstName(const Student student1, const Student student2) {
  if (student1.firstName < student2.firstName) {
    return -1;
  } else {
    return student1.firstName > student2.firstName;
  }
};
int compareLastName(const Student student1, const Student student2) {
  if (student1.lastName < student2.lastName) {
    return -1;
  } else {
    return student1.lastName > student2.lastName;
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

// void swap(Student** student1, Student** student2) {
//   Student* temp = *student1;
//   *student1 = *student2;
//   *student2 = temp;
// }

// Decending order
void sortByCgpa(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (compareCGPA(*students[j], *students[j + 1]) < 0) {
        swap(students[j], students[j + 1]);
      }
    }
  }
};

void sortByResearchScore(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (compareResearchScore(*students[j], *students[j + 1]) < 0) {
        swap(students[j], students[j + 1]);
      }
    }
  }
};

// Alphabetical order (A -> Z)
void sortByFirstName(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (compareFirstName(*students[j], *students[j + 1]) > 0) {
        swap(students[j], students[j + 1]);
      }
    }
  }
};

void sortByLastName(Student* students[], int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (compareLastName(*students[j], *students[j + 1]) > 0) {
        swap(students[j], students[j + 1]);
      }
    }
  }
};

void sortByLocation(DomesticStudent* students[], int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (students[j + 1]->province < students[j]->province) {
        swap(students[j], students[j + 1]);
      }
    }
  }
}

void sortByLocation(InternationalStudent* students[], int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (students[j + 1]->country < students[j]->country) {
        swap(students[j], students[j + 1]);
      }
    }
  }
}

void sortByOverall(Student* students[], int& len) {
  sortByCgpa(students, len);
  sortByResearchScore(students, len);
}

void sortByOverall(DomesticStudent* students[], int len) {
  sortByLocation(students, len);
  sortByOverall((Student**)students, len);
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

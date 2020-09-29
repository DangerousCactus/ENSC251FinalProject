// header file student.hpp to declare your classes
using namespace std;  // use namespace std
#include <string>     //you will have to use string in C++
class Student {
 private:
  string firstName;
  string lastName;
  float cgpa;
  int researchScore;
  int applicationID;
};

class DomesticStudent : public Student {
 private:
  string province;
};

class InternationalStudent : public Student {
 private:
  string country;
  ToeflScore toefl;
};

class ToeflScore {
 private:
  int reading;
  int listening;
  int speaking;
  int writing;
  int total;
};

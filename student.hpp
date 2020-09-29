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

 public:
  Student(string firstName,
          string lastName,
          float cgpa,
          int reseachScore,
          int applicationID);

  Student();

  string getFirstName();
  string getLastName();
  float getcgpa();
  int getResearchScore();
  int getApplicationID();

  void setFirstName(string name);
  void setLastName(string name);
  void setcgpa(float cgpa);
  void setResearchScore(int researchScore);
  void setApplicationID(int applicationID);
};

class DomesticStudent : public Student {
 private:
  string province;

 public:
  DomesticStudent(string firstName,
                  string lastName,
                  float cgpa,
                  int reseachScore,
                  int applicationID,
                  string province);

  DomesticStudent();

  string getProvince();
  void setProvince(string province);
};

class InternationalStudent : public Student {
 private:
  string country;
  ToeflScore toefl;

 public:
  InternationalStudent(string firstName,
                       string lastName,
                       float cgpa,
                       int reseachScore,
                       int applicationID,
                       string country,
                       ToeflScore toefl);

  InternationalStudent();

  void getCountry();
  void getToefl();

  void setCountry(string country);
  void getToefl(ToeflScore toefl);
};

class ToeflScore {
 private:
  int reading;
  int listening;
  int speaking;
  int writing;
  int total;

 public:
  ToeflScore(int reading, int listening, int speaking, int writing, int total);
  ToeflScore();

  void setReading(int score);
  void setlistening(int score);
  void setSpeaking(int score);
  void setWriting(int score);
  void setTotal(int score);

  int getReading();
  int getlistening();
  int getSpeaking();
  int getWriting();
  int getTotal();
};

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

  string getFirstName() const;
  string getLastName() const;
  float getcgpa() const;
  int getResearchScore() const;
  int getApplicationID() const;

  void setFirstName(string name);
  void setLastName(string name);
  void setcgpa(float cgpa);
  void setResearchScore(int researchScore);
  void setApplicationID(int applicationID);

  int friend compareCGPA(const Student student1, const Student student2);
  int friend compareResearchScore(const Student student1,
                                  const Student student2);
  int friend compareFirstName(const Student student1, const Student student2);
  int friend compareLastName(const Student student1, const Student student2);

  friend ostream& operator<<(ostream& outs,
                             const Student& student);
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

  string getProvince() const;
  void setProvince(string province);

  friend ostream& operator<<(ostream& outs, const DomesticStudent& student);
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
  ToeflScore(int reading, int listening, int speaking, int writing);
  ToeflScore();

  void setReading(int score);
  void setlistening(int score);
  void setSpeaking(int score);
  void setWriting(int score);
  void setTotal(int score);

  int getReading() const;
  int getlistening() const;
  int getSpeaking() const;
  int getWriting() const;
  int getTotal() const;
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

  void setCountry(string country);
  void setToefl(ToeflScore toefl);

  string getCountry() const;
  ToeflScore getToefl() const;

  friend ostream& operator<<(ostream& outs,
                             const InternationalStudent& student);
};

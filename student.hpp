#ifndef STUDENT_HPP
#define STUDENT_HPP

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
  Student(string firstName, string lastName, float cgpa, int reseachScore,
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

  friend ostream& operator<<(ostream& outs, const Student& student);
};

void sortbyCGPA(Student* students[], int len);
void sortByResearchScore(Student* students[], int len);
void sortByFirstName(Student* students[], int len);
void sortByLastName(Student* students[], int len);
void sortByOverall(Student* students[], int& len);

#endif
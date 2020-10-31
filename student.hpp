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
// Gets
  string getFirstName() const;
  string getLastName() const;
  float getcgpa() const;
  int getResearchScore() const;
  int getApplicationID() const;
// Sets
  void setFirstName(string name);
  void setLastName(string name);
  void setcgpa(float cgpa);
  void setResearchScore(int researchScore);
  void setApplicationID(int applicationID);
  
  // Compares two student's CGPAs
  int friend compareCGPA(const Student student1, const Student student2);
  
  // Compares two student's Research Scores
  int friend compareResearchScore(const Student student1,
                                  const Student student2);

  // Compares two student's First Name
  int friend compareFirstName(const Student student1, const Student student2);

  // Compares two student's Last Name
  int friend compareLastName(const Student student1, const Student student2);

  // Overloads << operator to output student information including: 
  // First Name, Last Name, CGPA, Research Score, Application ID.
  friend ostream& operator<<(ostream& outs, const Student& student);
};

// Sorts students by CGPA in Decending order
void sortByCGPA(Student* students[], int len);

// Sorts students by Research Score in Decending order
void sortByResearchScore(Student* students[], int len);

// Sorts students by First Name in Alphabetical order (A -> Z)
void sortByFirstName(Student* students[], int len);

// Sorts students by Last Name in Alphabetical order (A -> Z)
void sortByLastName(Student* students[], int len);

// sortByOverall
// Sorts students by Research Score first, then CGPA. If same CGPA, 
// Province or Country is used in ascending order (A - Z).
void sortByOverall(Student* students[], int& len);

#endif
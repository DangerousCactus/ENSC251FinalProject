#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>     //you will have to use std::string in C++

class Student {
 private:
  std::string firstName;
  std::string lastName;
  float cgpa;
  int researchScore;
  int applicationID;

 public:
  Student(std::string firstName, std::string lastName, float cgpa, int reseachScore,
          int applicationID);

  Student();
  // Getters
  std::string getFirstName() const;
  std::string getLastName() const;
  float getcgpa() const;
  int getResearchScore() const;
  int getApplicationID() const;

  // Setters
  void setFirstName(std::string name);
  void setLastName(std::string name);
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

  virtual std::string getLocation() const;

  // Overloads << operator to output student information including:
  // First Name, Last Name, CGPA, Research Score, Application ID.
  friend std::ostream& operator<<(std::ostream& outs, const Student& student);
  friend bool operator<(const Student& student1, const Student& student2);
  friend bool operator>(const Student& student1, const Student& student2);
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
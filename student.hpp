#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>  //you will have to use std::string in C++

class Student {
 private:
  std::string firstName;
  std::string lastName;
  float CGPA;
  int researchScore;
  int applicationID;

 public:
  Student(std::string firstName, std::string lastName, float cgpa,
          int reseachScore, int applicationID);

  Student();
  // Getters
  std::string getFirstName() const;
  std::string getLastName() const;
  float getCGPA() const;
  int getResearchScore() const;
  int getApplicationID() const;
  virtual std::string getLocation() const;

  // Setters
  void setFirstName(std::string name);
  void setLastName(std::string name);
  void setCGPA(float CGPA);
  void setResearchScore(int researchScore);
  void setApplicationID(int applicationID);

  // Compares two student's CGPAs
  int friend compareCGPA(const Student& student1, const Student& student2);

  // Compares two student's Research Scores
  int friend compareResearchScore(const Student& student1,
                                  const Student& student2);

  // Compares two student's First Name
  int friend compareFirstName(const Student& student1, const Student& student2);

  // Compares two student's Last Name
  int friend compareLastName(const Student& student1, const Student& student2);

  // Overloads << operator to output student information including:
  // First Name, Last Name, CGPA, Research Score, Application ID.
  virtual std::ostream& print(std::ostream& outs) const;
  friend bool operator<(const Student& student1, const Student& student2);
  friend bool operator>(const Student& student1, const Student& student2);
  friend std::ostream& operator<<(std::ostream& outs, const Student& student);
};

#endif
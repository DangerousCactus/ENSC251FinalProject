#ifndef DOMESTICSTUDENT_HPP
#define DOMESTICSTUDENT_HPP

using namespace std;  // use namespace std
#include <string>
#include "student.hpp"

class DomesticStudent : public Student {
 private:
  string province;

 public:
  DomesticStudent(string firstName, string lastName, float cgpa,
                  int reseachScore, int applicationID, string province);

  DomesticStudent();

  string getProvince() const;
  void setProvince(string province);

  friend ostream& operator<<(ostream& outs, const DomesticStudent& student);
  friend void sortByLocation(DomesticStudent* students[], int len);
};
void sortByOverall(DomesticStudent* students[], int len);
#endif
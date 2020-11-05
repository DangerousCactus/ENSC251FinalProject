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

  // Getters
  virtual string getLocation() const;
  
  // Setters
  void setProvince(string province);
  
  // Overloads the << operator to output the province
  friend ostream& operator<<(ostream& outs, const DomesticStudent& student);

  // sortByLocation
  // Sorts students by location based on province in ascending order
  friend void sortByLocation(DomesticStudent* students[], int len);
};

// sortByOverall
// Sorts students by Research Score first, then CGPA, and Province in 
// ascending order.
void sortByOverall(DomesticStudent* students[], int len);
#endif
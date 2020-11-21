#ifndef DOMESTICSTUDENT_HPP
#define DOMESTICSTUDENT_HPP

#include <string>
#include "student.hpp"

class DomesticStudent : public Student {
 private:
  std::string province;

 public:
  DomesticStudent(std::string firstName, std::string lastName, float cgpa,
                  int reseachScore, int applicationID, std::string province);

  DomesticStudent();

  // Getters
  virtual std::string getLocation() const;
  std::string getProvince() const;

  // Setters
  void setProvince(std::string province);

  virtual std::ostream& print(std::ostream& outs, const DomesticStudent& student);

  // sortByLocation
  // Sorts students by location based on province in ascending order
  friend void sortByLocation(DomesticStudent* students[], int len);
};

// sortByOverall
// Sorts students by Research Score first, then CGPA, and Province in
// ascending order.
void sortByOverall(DomesticStudent* students[], int len);
#endif
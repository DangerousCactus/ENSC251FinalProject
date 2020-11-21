#ifndef INTERNATIONALSTUDENT_HPP
#define INTERNATIONALSTUDENT_HPP

#include "TOEFLScore.hpp"
#include "student.hpp"

class InternationalStudent : public Student {
 private:
  std::string country;
  ToeflScore toefl;

 public:
  InternationalStudent(std::string firstName, std::string lastName, float cgpa,
                       int reseachScore, int applicationID, std::string country,
                       ToeflScore toefl);

  InternationalStudent(std::string firstName, std::string lastName, float cgpa,
                       int reseachScore, int applicationID, std::string country,
                       int reading, int listening, int speaking, int writing);

  InternationalStudent();

  // Setters
  void setCountry(std::string country);
  void setToefl(ToeflScore toefl);

  // Getters
  virtual std::string getLocation() const;
  std::string getCountry() const;
  ToeflScore getToefl() const;

  // Overloads the << operator to output the country
  friend std::ostream& operator<<(std::ostream& outs,
                             const InternationalStudent& student);

  // sortByLocation
  // Sorts students by location based on country in ascending order (A - Z).
  friend void sortByLocation(InternationalStudent* students[], int len);

  // removeLowToeflScores
  // Drops student if their TOEFL scores does not meet the threshold
  friend void removeLowToeflScores(InternationalStudent* students[], int& len);
};
// sortByOverall
// Sorts students by Research Score first, then CGPA. If same CGPA,
// Country is used in ascending order (A - Z).
void sortByOverall(InternationalStudent* students[], int& len);
#endif

#ifndef INTERNATIONALSTUDENT_HPP
#define INTERNATIONALSTUDENT_HPP

#include "student.hpp"
#include "TOEFLScore.hpp"

class InternationalStudent : public Student {
 private:
  string country;
  ToeflScore toefl;

 public:
  InternationalStudent(string firstName, string lastName, float cgpa,
                       int reseachScore, int applicationID, string country,
                       ToeflScore toefl);

  InternationalStudent(string firstName, string lastName, float cgpa,
                       int reseachScore, int applicationID, string country,
                       int reading, int listening, int speaking, int writing);

  InternationalStudent();
  // Sets
  void setCountry(string country);
  void setToefl(ToeflScore toefl);
  // Gets
  string getCountry() const;
  ToeflScore getToefl() const;

  // Overloads the << operator to output the country
  friend ostream& operator<<(ostream& outs,
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

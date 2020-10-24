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

  void setCountry(string country);
  void setToefl(ToeflScore toefl);

  string getCountry() const;
  ToeflScore getToefl() const;

  friend ostream& operator<<(ostream& outs,
                             const InternationalStudent& student);

  friend void sortByLocation(InternationalStudent* students[], int len);
  friend void removeLowToeflScores(InternationalStudent* students[], int& len);
};
void sortByOverall(InternationalStudent* students[], int& len);
#endif

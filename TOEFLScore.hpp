#ifndef TOEFLSCORE_HPP
#define TOEFLSCORE_HPP

using namespace std;
#include <iostream>

class ToeflScore {
 private:
  int reading;
  int listening;
  int speaking;
  int writing;
  int total;

 public:
  ToeflScore(int reading, int listening, int speaking, int writing);
  ToeflScore();
  // Sets
  void setReading(int score);
  void setlistening(int score);
  void setSpeaking(int score);
  void setWriting(int score);
  void setTotal(int score);
  // Gets
  int getReading() const;
  int getlistening() const;
  int getSpeaking() const;
  int getWriting() const;
  int getTotal() const;

  // Overloads << operator to output TOEFL scores in the order:
  // Reading, Lisenting, Speaking, Writing
  friend ostream& operator<<(ostream& outs, const ToeflScore& score);
};

#endif
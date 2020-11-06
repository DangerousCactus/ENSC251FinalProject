#ifndef TOEFLSCORE_HPP
#define TOEFLSCORE_HPP

#include <iostream>

class ToeflScore {
 private:
  int reading;
  int listening;
  int speaking;
  int writing;

 public:
  ToeflScore(int reading, int listening, int speaking, int writing);
  ToeflScore();

  // Setters
  void setReading(int score);
  void setlistening(int score);
  void setSpeaking(int score);
  void setWriting(int score);

  // Getters
  int getReading() const;
  int getlistening() const;
  int getSpeaking() const;
  int getWriting() const;
  int getTotal() const;

  // Overloads << operator to output TOEFL scores in the order:
  // Reading, Lisenting, Speaking, Writing
  friend std::ostream& operator<<(std::ostream& outs, const ToeflScore& score);
};

#endif
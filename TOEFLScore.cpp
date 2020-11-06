#include "TOEFLScore.hpp"

ToeflScore::ToeflScore(int reading, int listening, int speaking, int writing)
    : reading(reading), listening(listening), speaking(speaking),
      writing(writing) {}

ToeflScore::ToeflScore() {}

// Setters
void ToeflScore::setReading(int score) {
  this->reading = score;
}
void ToeflScore::setlistening(int score) {
  this->listening = score;
}
void ToeflScore::setSpeaking(int score) {
  this->speaking = score;
}
void ToeflScore::setWriting(int score) {
  this->writing = score;
}

// Getters
int ToeflScore::getReading() const {
  return reading;
}
int ToeflScore::getlistening() const {
  return listening;
}
int ToeflScore::getSpeaking() const {
  return speaking;
}
int ToeflScore::getWriting() const {
  return writing;
}
int ToeflScore::getTotal() const {
  return reading + listening + speaking + writing;
}

// Overloads << operator to output TOEFL scores in the order:
// Reading, Lisenting, Speaking, Writing
std::ostream& operator<<(std::ostream& outs, const ToeflScore& score) {
  outs << "TOEFL:  R: " << score.reading
       << " | L: " << score.listening
       << " | S: " << score.speaking << " | W: " << score.writing;

  return outs;
}
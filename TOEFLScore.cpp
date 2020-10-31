#include "TOEFLScore.hpp"

ToeflScore::ToeflScore(int reading, int listening, int speaking, int writing)
    : reading(reading), listening(listening), speaking(speaking),
      writing(writing) {}

ToeflScore::ToeflScore() {}

// Sets
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

// Gets
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
ostream& operator<<(ostream& outs, const ToeflScore& score) {
  outs << "TOEFL Scores:  Reading: " << score.reading
       << " | Listening: " << score.listening
       << " | Speaking: " << score.speaking << " | Writing: " << score.writing;

  return outs;
}
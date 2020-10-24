#include "TOEFLScore.hpp"

ToeflScore::ToeflScore(int reading, int listening, int speaking, int writing)
    : reading(reading), listening(listening), speaking(speaking),
      writing(writing) {
  this->total = reading + listening + speaking + writing;
}

ToeflScore::ToeflScore() {}

void ToeflScore::setReading(int score) {
  reading = score;
}
void ToeflScore::setlistening(int score) {
  listening = score;
}
void ToeflScore::setSpeaking(int score) {
  speaking = score;
}
void ToeflScore::setWriting(int score) {
  writing = score;
}
void ToeflScore::setTotal(int score) {
  total = score;
}

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
  return total;
}
ostream& operator<<(ostream& outs, const ToeflScore& score) {
  outs << "TOEFL Scores:  Reading: " << score.reading
       << " | Listening: " << score.listening
       << " | Speaking: " << score.speaking << " | Writing: " << score.writing
       << '\n';

  return outs;
}
#include <gtest/gtest.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../domesticStudent.hpp"
#include "../internationalStudent.hpp"

using namespace std;

struct sortingTest : public ::testing::Test {
  DomesticStudent* domesticStudents[100];
  InternationalStudent* internationalStudents[100];
  int dom_stu_count;
  int int_stu_count;

  virtual void SetUp() override {
    string line;
    ifstream domesticFile("../../domestic-stu.txt");
    if (!domesticFile.is_open()) {
      FAIL();
    }

    getline(domesticFile, line);
    dom_stu_count = 0;

    while (getline(domesticFile, line)) {
      istringstream ss(line);

      string firstName, lastName, province, s_cgpa, s_researchScore;
      float cgpa;
      int researchScore, applicationID;

      getline(ss, firstName, ',');
      getline(ss, lastName, ',');
      getline(ss, province, ',');
      getline(ss, s_cgpa, ',');
      cgpa = atof(s_cgpa.c_str());
      getline(ss, s_researchScore, ',');
      researchScore = atoi(s_researchScore.c_str());

      applicationID = 20200000 + dom_stu_count;
      domesticStudents[dom_stu_count] = new DomesticStudent(
          firstName, lastName, cgpa, researchScore, applicationID, province);

      dom_stu_count++;
    }

    // close your file
    domesticFile.close();

    ifstream internationalFile("../../international-stu.txt");
    if (!internationalFile.is_open()) {
      FAIL();
    }
    getline(internationalFile, line);
    int_stu_count = 0;
    while (getline(internationalFile, line)) {
      istringstream ss(line);

      string firstName, lastName, country, s_cgpa, s_researchScore, s_reading,
          s_listening, s_speaking, s_writing;
      float cgpa;
      int researchScore, reading, listening, speaking, writing, applicationID;

      getline(ss, firstName, ',');
      getline(ss, lastName, ',');
      getline(ss, country, ',');
      getline(ss, s_cgpa, ',');
      cgpa = atof(s_cgpa.c_str());
      getline(ss, s_researchScore, ',');
      researchScore = atoi(s_researchScore.c_str());

      getline(ss, s_reading, ',');
      reading = atoi(s_reading.c_str());

      getline(ss, s_listening, ',');
      listening = atoi(s_listening.c_str());

      getline(ss, s_speaking, ',');
      speaking = atoi(s_speaking.c_str());

      getline(ss, s_writing, ',');
      writing = atoi(s_writing.c_str());

      applicationID = 20200000 + dom_stu_count + int_stu_count;
      internationalStudents[int_stu_count] = new InternationalStudent(
          firstName, lastName, cgpa, researchScore, applicationID, country,
          reading, listening, speaking, writing);

      int_stu_count++;
    }
    // close your file
    internationalFile.close();
  }

  virtual void TearDown() override {
    for (int i = 0; i < 100; i++) {
      delete domesticStudents[i];
      delete internationalStudents[i];
    }
  }
};

TEST_F(sortingTest, sortingTestDom) {
  sortByCGPA((Student**)domesticStudents, dom_stu_count);
  for (int i = 1; i < dom_stu_count; i++) {
    EXPECT_GE(domesticStudents[i - 1]->getCGPA(),
              domesticStudents[i]->getCGPA());
  }

  sortByFirstName((Student**)domesticStudents, dom_stu_count);
  for (int i = 1; i < dom_stu_count; i++) {
    EXPECT_LE(domesticStudents[i - 1]->getFirstName(),
              domesticStudents[i]->getFirstName());
  }

  sortByLastName((Student**)domesticStudents, dom_stu_count);
  for (int i = 1; i < dom_stu_count; i++) {
    EXPECT_LE(domesticStudents[i - 1]->getLastName(),
              domesticStudents[i]->getLastName());
  }

  sortByLocation(domesticStudents, dom_stu_count);
  for (int i = 1; i < dom_stu_count; i++) {
    EXPECT_LE(domesticStudents[i - 1]->getLocation(),
              domesticStudents[i]->getLocation());
  }

  sortByResearchScore((Student**)domesticStudents, dom_stu_count);
  for (int i = 1; i < dom_stu_count; i++) {
    EXPECT_GE(domesticStudents[i - 1]->getResearchScore(),
              domesticStudents[i]->getResearchScore());
  }

  sortByOverall(domesticStudents, dom_stu_count);
  for (int i = 1; i < dom_stu_count; i++) {
    EXPECT_GE(domesticStudents[i - 1]->getResearchScore(),
              domesticStudents[i]->getResearchScore());
    if (domesticStudents[i - 1]->getResearchScore() ==
        domesticStudents[i]->getResearchScore()) {
      EXPECT_GE(domesticStudents[i - 1]->getCGPA(),
                domesticStudents[i]->getCGPA());
      if (domesticStudents[i - 1]->getCGPA() ==
          domesticStudents[i]->getCGPA()) {
        EXPECT_LE(domesticStudents[i - 1]->getLocation(),
                  domesticStudents[i]->getLocation());
      }
    }
  }
}

TEST_F(sortingTest, sortingTestInt) {
  sortByCGPA((Student**)internationalStudents, int_stu_count);
  for (int i = 1; i < int_stu_count; i++) {
    EXPECT_GE(internationalStudents[i - 1]->getCGPA(),
              internationalStudents[i]->getCGPA());
  }

  sortByFirstName((Student**)internationalStudents, int_stu_count);
  for (int i = 1; i < int_stu_count; i++) {
    EXPECT_LE(internationalStudents[i - 1]->getFirstName(),
              internationalStudents[i]->getFirstName());
  }

  sortByLastName((Student**)internationalStudents, int_stu_count);
  for (int i = 1; i < int_stu_count; i++) {
    EXPECT_LE(internationalStudents[i - 1]->getLastName(),
              internationalStudents[i]->getLastName());
  }

  sortByLocation(internationalStudents, int_stu_count);
  for (int i = 1; i < int_stu_count; i++) {
    EXPECT_LE(internationalStudents[i - 1]->getLocation(),
              internationalStudents[i]->getLocation());
  }

  sortByResearchScore((Student**)internationalStudents, int_stu_count);
  for (int i = 1; i < int_stu_count; i++) {
    EXPECT_GE(internationalStudents[i - 1]->getResearchScore(),
              internationalStudents[i]->getResearchScore());
  }

  sortByOverall(internationalStudents, int_stu_count);
  for (int i = 0; i < int_stu_count; i++) {
    EXPECT_GE(internationalStudents[i]->getToefl().getTotal(), 93);
    EXPECT_GE(internationalStudents[i]->getToefl().getReading(), 20);
    EXPECT_GE(internationalStudents[i]->getToefl().getWriting(), 20);
    EXPECT_GE(internationalStudents[i]->getToefl().getlistening(), 20);
    EXPECT_GE(internationalStudents[i]->getToefl().getSpeaking(), 20);
  }

  for (int i = int_stu_count; i < 100; i++) {
    EXPECT_TRUE(internationalStudents[i]->getToefl().getTotal() < 93 ||
                internationalStudents[i]->getToefl().getReading() < 20 ||
                internationalStudents[i]->getToefl().getWriting() < 20 ||
                internationalStudents[i]->getToefl().getlistening() < 20 ||
                internationalStudents[i]->getToefl().getSpeaking() < 20);
  }

  for (int i = 1; i < int_stu_count; i++) {
    EXPECT_GE(internationalStudents[i - 1]->getResearchScore(),
              internationalStudents[i]->getResearchScore());
    if (internationalStudents[i - 1]->getResearchScore() ==
        internationalStudents[i]->getResearchScore()) {
      EXPECT_GE(internationalStudents[i - 1]->getCGPA(),
                internationalStudents[i]->getCGPA());
      if (internationalStudents[i - 1]->getCGPA() ==
          internationalStudents[i]->getCGPA()) {
        EXPECT_LE(internationalStudents[i - 1]->getLocation(),
                  internationalStudents[i]->getLocation());
      }
    }
  }
}

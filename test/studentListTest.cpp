#include <gtest/gtest.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../StudentList.hpp"
#include "../StudentNode.hpp"
#include "../domesticStudent.hpp"
#include "../internationalStudent.hpp"

struct sortingTest : public ::testing::Test {
  DomesticStudent dstest1 =
      DomesticStudent("Bob", "Joe", 4.0, 100, 20202020, "BC");
  DomesticStudent dslast =
      DomesticStudent("Bob", "Joe", 4.0, 10, 20202021, "BC");
  DomesticStudent dsfirst =
      DomesticStudent("Bob", "Joe", 4.4, 100, 20202022, "BC");

  InternationalStudent istest1 = InternationalStudent(
      "Bob", "Joe", 4.0, 100, 20202023, "China", 25, 25, 25, 25);
  InternationalStudent islast = InternationalStudent(
      "Bob", "Joe", 4.0, 10, 20202024, "China", 25, 25, 25, 25);
  InternationalStudent isfirst = InternationalStudent(
      "Bob", "Joe", 4.4, 100, 20202025, "China", 25, 25, 25, 25);
  StudentList<Student> dslist;
  StudentList<Student> islist;

  virtual void SetUp() override {
    std::string line;
    std::ifstream domesticFile("../../domestic-stu.txt");

    if (!domesticFile.is_open()) {
      FAIL();
    }

    getline(domesticFile, line);  // Discard legend

    int dom_stu_count = 0;
    while (getline(domesticFile, line)) {
      std::istringstream ss(line);

      std::string firstName, lastName, province, s_cgpa, s_researchScore;
      float cgpa;
      int researchScore, applicationID;

      getline(ss, firstName, ',');
      getline(ss, lastName, ',');
      getline(ss, province, ',');

      getline(ss, s_cgpa, ',');
      cgpa = atof(s_cgpa.c_str());

      getline(ss, s_researchScore, ',');
      researchScore = atoi(s_researchScore.c_str());

      if (ss.fail() || firstName == "" || lastName == "" || province == "" ||
          s_cgpa == "" || s_researchScore == "") {
        FAIL();
      }

      if (!StringHelper::isProvince(province)) {
        FAIL();
      }

      applicationID = 20200000 + dom_stu_count;

      dslist.addStudentNode(new DomesticStudent(
          firstName, lastName, cgpa, researchScore, applicationID, province));

      dom_stu_count++;
    }

    domesticFile.close();

    std::ifstream internationalFile("../../international-stu.txt");
    if (!internationalFile.is_open()) {
      FAIL();
    }

    getline(internationalFile, line);

    int int_stu_count = 0;
    while (getline(internationalFile, line)) {
      std::istringstream ss(line);

      std::string firstName, lastName, country, s_cgpa, s_researchScore,
          s_reading, s_listening, s_speaking, s_writing;
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

      if (ss.fail() || firstName == "" || lastName == "" || country == "" ||
          s_cgpa == "" || s_researchScore == "" || s_reading == "" ||
          s_writing == "" || s_speaking == "" || s_listening == "") {
        FAIL();
      }

      if (!StringHelper::isCountry(country)) {
        std::string anagram = StringHelper::anagramOfCountry(country);
        if (anagram == "") {
          FAIL();
        } else {
          country = anagram;
        }
      }

      applicationID = 20200000 + dom_stu_count + int_stu_count;

      islist.addStudentNode(new InternationalStudent(
          firstName, lastName, cgpa, researchScore, applicationID, country,
          reading, listening, speaking, writing));

      int_stu_count++;
    }
    // close your file
    internationalFile.close();
  }
};

// The following are helper functions to assist in checking program vailidity

template <typename T>
bool isListSorted(StudentList<T> studentList) {
  StudentNodePtr<T> head = studentList.getHead();
  if (head == nullptr)
    return true;

  while (head->getLink() != nullptr) {
    if (*(head->getStudent()) < *(head->getLink()->getStudent()))
      return false;
    head = head->getLink();
  }
  return true;
}

bool doesStudentExist(StudentList<Student> studentList, Student student) {
  StudentNodePtr<Student> head = studentList.getHead();
  while (head != nullptr) {
    if (head->getStudent()->getApplicationID() == student.getApplicationID())
      return true;
    head = head->getLink();
  }
  return false;
}

bool doAllFieldsHaveValue(std::string toParse, std::string field,
                          std::string value) {
  int currIndex = 0;
  currIndex = toParse.find(field, 0);
  while (currIndex != -1) {
    if (toParse.substr(currIndex + field.length(), value.length())
            .compare(value) != 0)
      return false;
    currIndex = toParse.find(field, currIndex + 1);
  }
  return true;
}

bool doAllFieldsHaveAtLeastValue(std::string toParse, std::string field,
                                 float value) {
  int currIndex = 0;
  currIndex = toParse.find(field, 0);
  while (currIndex != -1) {
    float testValue =
        atof(toParse.substr(currIndex + field.length(), 4).c_str());
    if (value > testValue)
      return false;
    currIndex = toParse.find(field, currIndex + 1);
  }
  return true;
}

/*
1. Insert a DomesticStudent (and InternationalStudent) object into the
DomesticStudent (and InternationalStudent) singly linked list in order.
*/
TEST_F(sortingTest, listInsertTestDomestic) {
  EXPECT_TRUE(isListSorted(dslist));
  // Normal case
  dslist.addStudentNode(new DomesticStudent(dstest1));
  EXPECT_TRUE(doesStudentExist(dslist, dstest1));
  EXPECT_TRUE(isListSorted(dslist));

  // Edge Cases, insert at front or back
  dslist.addStudentNode(new DomesticStudent(dslast));
  EXPECT_TRUE(doesStudentExist(dslist, dslast));
  EXPECT_TRUE(isListSorted(dslist));

  dslist.addStudentNode(new DomesticStudent(dsfirst));
  EXPECT_TRUE(doesStudentExist(dslist, dsfirst));
  EXPECT_TRUE(isListSorted(dslist));

  // Illegal case:
  StudentNodePtr<Student> temp =
      new StudentNode<Student>(new DomesticStudent(dstest1));
  dslist.getTail()->setLink(temp);
  dslist.setTail(temp);
  EXPECT_FALSE(isListSorted(dslist));
}

TEST_F(sortingTest, listInsertTestInternational) {
  EXPECT_TRUE(isListSorted(islist));
  // Normal case
  islist.addStudentNode(new InternationalStudent(istest1));
  EXPECT_TRUE(doesStudentExist(islist, istest1));
  EXPECT_TRUE(isListSorted(islist));

  // Edge Cases, insert at front or back
  islist.addStudentNode(new InternationalStudent(islast));
  EXPECT_TRUE(doesStudentExist(islist, islast));
  EXPECT_TRUE(isListSorted(islist));

  islist.addStudentNode(new InternationalStudent(isfirst));
  EXPECT_TRUE(doesStudentExist(islist, isfirst));
  EXPECT_TRUE(isListSorted(islist));

  // Illegal case
  StudentNodePtr<Student> temp =
      new StudentNode<Student>(new InternationalStudent(istest1));
  islist.getTail()->setLink(temp);
  islist.setTail(temp);
  EXPECT_FALSE(isListSorted(islist));
}

/*
2. Search existing DomesticStudent (and InternationalStudent) objects in the
DomesticStudent (and InternationalStudent) linked list based on the user input
information “application id”, or “cgpa”, or “researchScore”.
*/
TEST_F(sortingTest, listSearchTestAppCGPAResearch) {
  std::string output;
  DomesticStudent lastDomStu =
      DomesticStudent("Claire", "Griffin", 3.45, 95, 20200099, "NS");

  // Normal Case - AppID
  testing::internal::CaptureStdout();
  dslist.searchAppID(20200099);
  output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(doAllFieldsHaveValue(output, "App ID: ", "20200099"));

  // Illegal Case - AppID
  testing::internal::CaptureStdout();
  dslist.searchAppID(0);  // Inexistent ID
  output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(output == "\033[31mNo matching records found.\033[0m\n");

  // Normal Case - CGPA
  testing::internal::CaptureStdout();
  dslist.searchCGPA(3.45);
  output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(doAllFieldsHaveValue(output, "CGPA: ", "3.45"));

  // Illegal Case - CGPA
  testing::internal::CaptureStdout();
  dslist.searchCGPA(-1);  // Inexistent CGPA
  output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(output == "\033[31mNo matching records found.\033[0m\n");

  // Normal Case - Research Score
  testing::internal::CaptureStdout();
  dslist.searchResearchScore(99);
  output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(doAllFieldsHaveValue(output, "Research: ", "99"));

  // Illegal Case - ResearchScore
  testing::internal::CaptureStdout();
  dslist.searchResearchScore(-1);  // Inexistent Research SCore
  output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(output == "\033[31mNo matching records found.\033[0m\n");
}

/*
3. Search existing DomesticStudent (and InternationalStudent) objects in the
DomesticStudent (and InternationalStudent) linked list based on the user input
information “firstName and lastName”.
*/
TEST_F(sortingTest, listSearchTestFirstLast) {
  std::string output;

  // Normal Case
  testing::internal::CaptureStdout();
  dslist.searchFirstLast("Luke", "Bennett");
  output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output.substr(81, 30).compare("Luke            Bennett       "), 0);

  // Illegal Case
  testing::internal::CaptureStdout();
  dslist.searchFirstLast("Non", "Existent");
  output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output == "\033[31mNo matching records found.\033[0m\n");
}

/*
4. Delete existing DomesticStudent (and InternationalStudent) objects in the
DomesticStudent (and InternationalStudent) linked list based on the user input
information “firstName and lastName”.
*/
TEST_F(sortingTest, listDeleteTest) {
  // Normal Case
  Student* currHeadStudent = dslist.getHead()->getStudent();
  EXPECT_TRUE(doesStudentExist(dslist, *currHeadStudent));
  dslist.deleteFirstLast(currHeadStudent->getFirstName(),
                         currHeadStudent->getLastName());
  EXPECT_FALSE(doesStudentExist(dslist, *currHeadStudent));

  // Illegal case
  Student dsfake = DomesticStudent("John", "Doe", 2.0, 67, 20205020, "BC");
  EXPECT_FALSE(doesStudentExist(dslist, dsfake));
  dslist.deleteFirstLast("John", "Doe");
  EXPECT_FALSE(doesStudentExist(dslist, dsfake));
}

/*
5. Delete both the head node and tail node from the DomesticStudent (and
InternationalStudent) linked list in a single delete function.
*/
TEST_F(sortingTest, listHeadTailDeleteTest) {
  Student currHeadStudent = *(dslist.getHead()->getStudent());
  Student currTailStudent = *(dslist.getTail()->getStudent());
  EXPECT_TRUE(doesStudentExist(dslist, currHeadStudent));
  EXPECT_TRUE(doesStudentExist(dslist, currTailStudent));
  dslist.deleteHeadTail();
  EXPECT_FALSE(doesStudentExist(dslist, currHeadStudent));
  EXPECT_FALSE(doesStudentExist(dslist, currTailStudent));
}

/*
6. Merge the two sorted DomesticStudent and InternationalStudent linked lists
into a single Student linked list.

LIST MERGE SEARCH
7. Search existing Student objects in the merged linked list based on the user
input information “cgpa_threshold and researchScore_threshold”.
*/
TEST_F(sortingTest, listMergeTest) {
  StudentList<Student> mergedList;
  StudentNodePtr<Student> tempNode = dslist.getHead();
  while (tempNode != nullptr) {
    DomesticStudent* tempStudent =
        dynamic_cast<DomesticStudent*>(tempNode->getStudent());
    mergedList.addStudentNode(new DomesticStudent(*tempStudent));
    tempNode = tempNode->getLink();
  }

  tempNode = islist.getHead();
  while (tempNode != nullptr) {
    InternationalStudent* tempStudent =
        dynamic_cast<InternationalStudent*>(tempNode->getStudent());

    // If the TOEFL score meets the conditions, add it
    if (tempStudent->getToefl().meetsRequirements())
      mergedList.addStudentNode(new InternationalStudent(*tempStudent));
    tempNode = tempNode->getLink();
  }

  testing::internal::CaptureStdout();
  mergedList.searchCGPAandResearchScoreThreshold(3.5, 90);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(doAllFieldsHaveAtLeastValue(output, "CGPA: ", 3.50));
  EXPECT_TRUE(doAllFieldsHaveAtLeastValue(output, "Research: ", 90));

  // mergedList.print();
}

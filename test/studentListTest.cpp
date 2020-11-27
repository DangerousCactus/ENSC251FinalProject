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
  StudentList<DomesticStudent> dslist;
  StudentList<InternationalStudent> islist;

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

      dslist.addStudentNode(DomesticStudent(
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

      islist.addStudentNode(InternationalStudent(
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

template <typename T>
bool doesStudentExist(StudentList<T> studentList, T student) {
  StudentNodePtr<T> head = studentList.getHead();
  while (head != nullptr) {
    if (head->getStudent()->getApplicationID() == student.getApplicationID())
      return true;
    head = head->getLink();
  }
  return false;
}

template <typename T>
bool doAllCGPAFieldsHaveValue(StudentList<T> studentList, float value) {
  StudentNodePtr<T> top = studentList.getHead();
  while (top != nullptr) {
    if (top->getStudent()->getCGPA() != value)
      return false;

    top = top->getLink();
  }

  return true;
}
template <typename T>
bool doAllResearchScoreFieldsHaveValue(StudentList<T> studentList, int value) {
  StudentNodePtr<T> top = studentList.getHead();
  while (top != nullptr) {
    if (top->getStudent()->getResearchScore() != value)
      return false;

    top = top->getLink();
  }

  return true;
}
template <typename T>
bool doAllApplicationIDFieldsHaveValue(StudentList<T> studentList, int value) {
  StudentNodePtr<T> top = studentList.getHead();
  while (top != nullptr) {
    if (top->getStudent()->getApplicationID() != value)
      return false;

    top = top->getLink();
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
  dslist.addStudentNode(dstest1);
  EXPECT_TRUE(doesStudentExist(dslist, dstest1));
  EXPECT_TRUE(isListSorted(dslist));

  // Edge Cases, insert at front or back
  dslist.addStudentNode(dslast);
  EXPECT_TRUE(doesStudentExist(dslist, dslast));
  EXPECT_TRUE(isListSorted(dslist));

  dslist.addStudentNode(dsfirst);
  EXPECT_TRUE(doesStudentExist(dslist, dsfirst));
  EXPECT_TRUE(isListSorted(dslist));

  // Illegal case (will report failure):
  // StudentNodePtr<DomesticStudent> temp =
  //     new StudentNode<DomesticStudent>(dstest1);
  // dslist.getTail()->setLink(temp);
  // dslist.setTail(temp);
  // EXPECT_TRUE(isListSorted(dslist));
}

TEST_F(sortingTest, listInsertTestInternational) {
  EXPECT_TRUE(isListSorted(islist));
  // Normal case
  islist.addStudentNode(istest1);
  EXPECT_TRUE(doesStudentExist(islist, istest1));
  EXPECT_TRUE(isListSorted(islist));

  // Edge Cases, insert at front or back
  islist.addStudentNode(islast);
  EXPECT_TRUE(doesStudentExist(islist, islast));
  EXPECT_TRUE(isListSorted(islist));

  islist.addStudentNode(isfirst);
  EXPECT_TRUE(doesStudentExist(islist, isfirst));
  EXPECT_TRUE(isListSorted(islist));

  // Illegal case (will report failure):
  // StudentNodePtr<DomesticStudent> temp =
  //     new StudentNode<DomesticStudent>(istest1);
  // islist.getTail()->setLink(temp);
  // islist.setTail(temp);
  // EXPECT_TRUE(isListSorted(islist));
}

/*
2. Search existing DomesticStudent (and InternationalStudent) objects in the
DomesticStudent (and InternationalStudent) linked list based on the user input
information “application id”, or “cgpa”, or “researchScore”.
*/
TEST_F(sortingTest, listSearchTestAppCGPAResearch) {
  DomesticStudent lastDomStu =
      DomesticStudent("Claire", "Griffin", 3.45, 95, 20200099, "NS");
  StudentList<DomesticStudent> temp;

  // Normal Case - AppID
  temp = dslist.searchAppID(20200099);
  EXPECT_TRUE(doAllApplicationIDFieldsHaveValue(temp, 20200099));

  // Illegal Case - AppID
  temp = dslist.searchAppID(0);  // Inexistent ID
  EXPECT_TRUE(temp.isEmpty());

  // Normal Case - CGPA
  temp = dslist.searchCGPA(3.45);
  EXPECT_TRUE(doAllCGPAFieldsHaveValue(temp, 3.45));

  // Illegal Case - CGPA
  temp = dslist.searchCGPA(-1);  // Inexistent CGPA
  EXPECT_TRUE(temp.isEmpty());

  // Normal Case - Research Score
  temp = dslist.searchResearchScore(99);
  EXPECT_TRUE(doAllResearchScoreFieldsHaveValue(temp, 99));

  // Illegal Case - ResearchScore
  temp = dslist.searchResearchScore(-1);  // Inexistent Research SCore
  EXPECT_TRUE(temp.isEmpty());
}

/*
3. Search existing DomesticStudent (and InternationalStudent) objects in the
DomesticStudent (and InternationalStudent) linked list based on the user input
information “firstName and lastName”.
*/
TEST_F(sortingTest, listSearchTestFirstLast) {
  StudentList<DomesticStudent> temp;

  // Normal Case
  temp = dslist.searchFirstLast("Luke", "Bennett");
  EXPECT_TRUE(temp.getHead()->getStudent()->getFirstName() == "Luke");
  EXPECT_TRUE(temp.getHead()->getStudent()->getLastName() == "Bennett");

  // Illegal Case
  temp = dslist.searchFirstLast("Non", "Existent");
  EXPECT_TRUE(temp.isEmpty());
}

/*
4. Delete existing DomesticStudent (and InternationalStudent) objects in the
DomesticStudent (and InternationalStudent) linked list based on the user input
information “firstName and lastName”.
*/
TEST_F(sortingTest, listDeleteTest) {
  // Normal Case
  DomesticStudent currHeadStudent = *(dslist.getHead()->getStudent());
  EXPECT_TRUE(doesStudentExist(dslist, currHeadStudent));
  dslist.deleteFirstLast("Aurora", "Foster");
  EXPECT_FALSE(doesStudentExist(dslist, currHeadStudent));

  // Illegal case
  DomesticStudent dsfake =
      DomesticStudent("John", "Doe", 2.0, 67, 20205020, "BC");
  EXPECT_FALSE(doesStudentExist(dslist, dsfake));
  dslist.deleteFirstLast("John", "Doe");
  EXPECT_FALSE(doesStudentExist(dslist, dsfake));
}

/*
5. Delete both the head node and tail node from the DomesticStudent (and
InternationalStudent) linked list in a single delete function.
*/
TEST_F(sortingTest, listHeadTailDeleteTest) {
  DomesticStudent currHeadStudent = *(dslist.getHead()->getStudent());
  DomesticStudent currTailStudent = *(dslist.getTail()->getStudent());
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
  StudentList<Student> temp;

  StudentNodePtr<DomesticStudent> tempds = dslist.getHead();
  while (tempds != nullptr) {
    mergedList.addStudentNode(DomesticStudent(*(tempds->getStudent())));
    tempds = tempds->getLink();
  }

  StudentNodePtr<InternationalStudent> tempis = islist.getHead();
  while (tempis != nullptr) {
    ToeflScore tempToefl = tempis->getStudent()->getToefl();

    // If the TOEFL score meets the conditions, add it into the merged list
    if (tempToefl.meetsRequirements()) {
      mergedList.addStudentNode(InternationalStudent(*(tempis->getStudent())));
    }
    tempis = tempis->getLink();
  }

  temp = mergedList.searchCGPAandResearchScoreThreshold(3.5, 90);

  StudentNodePtr<Student> head = temp.getHead();
  while (head != nullptr) {
    EXPECT_GE(head->getStudent()->getCGPA(), 3.5);
    EXPECT_GE(head->getStudent()->getResearchScore(), 90);
    head = head->getLink();
  }

  temp.print();

  // mergedList.print();
}

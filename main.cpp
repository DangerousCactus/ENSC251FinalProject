#include <climits>
#include <cstdlib>   //atof and atoi
#include <fstream>   //file processing
#include <iostream>  //cin and cout
#include <sstream>   //formatted string processing
#include "StringHelper.hpp"
#include "StudentList.hpp"
#include "domesticStudent.hpp"
#include "internationalStudent.hpp"

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BOLD = "\033[1m";
const std::string CLEAR = "\033[0m";

// forceIntInput
// Helper function to reject invalid input and suggests possible correction
void forceIntInput(std::istream& inps, std::string message, int& field,
                   int maxAllow) {
  do {
    std::cout << message;
    inps >> field;

    if (inps.fail()) {
      inps.clear();
      inps.ignore(INT_MAX, '\n');
      std::cout << YELLOW << BOLD << "Enter a number please. Try again:\n"
                << CLEAR;
      continue;
    }

    inps.ignore(INT_MAX, '\n');

    if (field > 0 && field <= maxAllow)
      break;

    std::cout << YELLOW << BOLD
              << "Please enter a valid selection. Try again:\n";

  } while (true);
}

int main() {
  StudentList<DomesticStudent> dslist;
  StudentList<InternationalStudent> islist;
  std::string line;
  std::ifstream domesticFile("domestic-stu.txt");

  if (!domesticFile.is_open()) {
    std::cout << "Unable to open file domestic-stu.txt" << std::endl;
    return -1;
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

    if (ss.fail()) {
      std::cout << RED
                << "ERROR: domestic-stu.txt does not have all required fields\n"
                << CLEAR;
      exit(-1);
    }

    applicationID = 20200000 + dom_stu_count;
    dslist.addStudentNode(new DomesticStudent(
        firstName, lastName, cgpa, researchScore, applicationID, province));

    dom_stu_count++;
  }

  domesticFile.close();

  std::ifstream internationalFile("international-stu.txt");
  if (!internationalFile.is_open()) {
    std::cout << "Unable to open file international-stu.txt" << std::endl;
    return -1;
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

    if (ss.fail()) {
      std::cout
          << RED
          << "ERROR: international-stu.txt does not have all required fields\n"
          << CLEAR;
      exit(-1);
    }

    applicationID = 20200000 + dom_stu_count + int_stu_count;
    islist.addStudentNode(new InternationalStudent(
        firstName, lastName, cgpa, researchScore, applicationID, country,
        reading, listening, speaking, writing));

    int_stu_count++;
  }
  // close your file
  internationalFile.close();

  // End reading of files and loading of student data

  StudentList<Student> mergedList;

  StudentNodePtr<DomesticStudent> tempds = dslist.getHead();
  while (tempds != nullptr) {
    mergedList.addStudentNode(new DomesticStudent(*(tempds->getStudent())));
    tempds = tempds->getLink();
  }

  StudentNodePtr<InternationalStudent> tempis = islist.getHead();
  while (tempis != nullptr) {
    ToeflScore tempToefl = tempis->getStudent()->getToefl();

    // If the TOEFL score meets the conditions, add it into the merged list
    if (tempToefl.getlistening() >= 20 && tempToefl.getReading() >= 20 &&
        tempToefl.getWriting() >= 20 && tempToefl.getSpeaking() >= 20 &&
        tempToefl.getTotal() >= 93) {
      mergedList.addStudentNode(
          new InternationalStudent(*(tempis->getStudent())));
    }
    tempis = tempis->getLink();
  }

  // mergedList.searchCGPAandResearchScoreThreshold(3, 95);

  // dslist.print();
  // dslist.searchFirstLast("MaRy", "WHItE");

  // int domOrInt = 0, sortType = 0;

  // // Menu while loop
  // // User chooses either Domestic or International student database
  // while (true) {
  //   std::cout << std::string(50, '-') << '\n';
  //   std::cout << "Student Database\n";
  //   std::cout << std::string(50, '-') << '\n';

  //   std::cout << "Choose an option below to sort:" << std::endl;
  //   std::cout << "1. Domestic" << std::endl;
  //   std::cout << "2. International" << std::endl;
  //   std::cout << "3. Merged Domestic and International" << std::endl;
  //   std::cout << "4. Quit" << std::endl;

  //   // User chooses the sorting order of the previously selected student
  //   // database

  //   forceIntInput(std::cin, "> ", domOrInt, 4);

  //   // Quit the program
  //   if (domOrInt == 4) {
  //     std::cout << RED << BOLD << "\nPROGRAM EXITED\n\n" << CLEAR;
  //     return 0;
  //   }

  //   std::cout << "\nChoose a task:" << std::endl;
  //   std::cout << "1. Search Student" << std::endl;
  //   std::cout << "2. Create Student" << std::endl;
  //   std::cout << "3. Delete Student" << std::endl;

  //   forceIntInput(std::cin, "> ", sortType, 3);

  //   switch (sortType) {
  //     case 1:
  //       break;
  //     default:
  //       std::cout << RED << "\nInvalid Input!" << BOLD << "\n\nPlease try
  //       again\n\n"
  //            << CLEAR << std::endl;
  //   }
  // }
}

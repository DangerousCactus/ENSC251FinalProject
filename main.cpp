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
  StudentList<Student> dslist;
  StudentList<Student> islist;

  std::string line;
  std::ifstream domesticFile("domestic-stu.txt");

  if (!domesticFile.is_open()) {
    std::cout << "Unable to open file domestic-stu.txt" << std::endl;
    return -1;
  }

  std::cout << GREEN << "Reading data from domestic-stu.txt...\n" << CLEAR;
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
      std::cout << RED
                << "ERROR: domestic-stu.txt does not have all required fields\n"
                << CLEAR;
      exit(-1);
    }

    if (!StringHelper::isProvince(province)) {
      std::cout << RED << "ERROR: " << province << " is not a valid province.\n"
                << CLEAR;
      exit(-1);
    }

    applicationID = 20200000 + dom_stu_count;
    try {
      dslist.addStudentNode(new DomesticStudent(
          firstName, lastName, cgpa, researchScore, applicationID, province));
    } catch (std::bad_alloc) {
      std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
      exit(-1);
    }

    dom_stu_count++;
  }

  domesticFile.close();
  std::cout << GREEN << "Reading data from domestic-stu.txt succeeded.\n"
            << CLEAR;
  std::ifstream internationalFile("international-stu.txt");
  if (!internationalFile.is_open()) {
    std::cout << "Unable to open file international-stu.txt" << std::endl;
    return -1;
  }
  std::cout << GREEN << "Reading data from international-stu.txt...\n" << CLEAR;
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
      std::cout
          << RED
          << "ERROR: international-stu.txt does not have all required fields\n"
          << CLEAR;
      exit(-1);
    }

    if (!StringHelper::isCountry(country)) {
      std::string anagram = StringHelper::anagramOfCountry(country);
      if (anagram != "") {
        std::cout << YELLOW << "Detected typo in " << CLEAR << country << YELLOW
                  << ". Autocorrecting to " << anagram << ".\n"
                  << CLEAR;
        country = anagram;
      } else {
        std::cout << RED << "ERROR: " << country << " is not a valid country.\n"
                  << CLEAR;
        exit(-1);
      }
    }

    applicationID = 20200000 + dom_stu_count + int_stu_count;
    try {
      islist.addStudentNode(new InternationalStudent(
          firstName, lastName, cgpa, researchScore, applicationID, country,
          reading, listening, speaking, writing));
    } catch (std::bad_alloc) {
      std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
      exit(-1);
    }

    int_stu_count++;
  }
  // close your file
  internationalFile.close();
  std::cout << GREEN << "Reading data from international-stu.txt succeeded."
            << CLEAR << std::endl;

  // End reading of files and loading of student data
  // islist.print();
  StudentList<Student> mergedList;
  try {
    StudentNodePtr<Student> tempds = dslist.getHead();
    while (tempds != nullptr) {
      DomesticStudent* tempStudent =
          dynamic_cast<DomesticStudent*>(tempds->getStudent());
      mergedList.addStudentNode(new DomesticStudent(*tempStudent));
      tempds = tempds->getLink();
    }

    StudentNodePtr<Student> tempis = islist.getHead();
    while (tempis != nullptr) {
      InternationalStudent* tempStudent =
          dynamic_cast<InternationalStudent*>(tempis->getStudent());

      // If the TOEFL score meets the conditions, add it into the merged list
      if (tempStudent->getToefl().meetsRequirements()) {
        mergedList.addStudentNode(new InternationalStudent(*tempStudent));
      }
      tempis = tempis->getLink();
    }
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
    exit(-1);
  }
  mergedList.print();
  // mergedList.print();

  /*
  Which List?

  DO
  Domestic
  International
  Merged
  Exit

    DO
    Option?
    Search Student
      APPID
      CGPA
      ResearchScore
      First & Last Name
      Hybrid Threshold
    Create Student
      Data Points based on List ID
    Delete Student by First and Last name
    Delete Head & Tail Nodes
    WHILE
  WHILE
  */

  StudentList<Student>* studentLists[] = {&dslist, &islist, &mergedList};
  std::string studentListNames[] = {"Domestic", "International",
                                    "Merged Domestic and International"};

  std::string listChoice;
  std::string taskChoice;
  int listID;

  // Menu while loop
  // User chooses either Domestic or International student database
  while (true) {
    std::cout << std::string(50, '-') << '\n';
    std::cout << "Student Database\n";
    std::cout << std::string(50, '-') << '\n';

    std::cout << "Choose a list to interact with:" << std::endl;
    std::cout << "(D)omestic" << std::endl;
    std::cout << "(I)nternational" << std::endl;
    std::cout << "(M)erged Domestic and International" << std::endl;
    std::cout << "(Q)uit this program" << std::endl;

    std::cin >> listChoice;

    if (StringHelper::toUpper(listChoice) == "D" ||
        StringHelper::isAnagramOf(listChoice, "domestic")) {
      listID = 0;
    } else if (StringHelper::toUpper(listChoice) == "I" ||
               StringHelper::isAnagramOf(listChoice, "international")) {
      listID = 1;
    } else if (StringHelper::toUpper(listChoice) == "M" ||
               StringHelper::isAnagramOf(listChoice, "domestic")) {
      listID = 2;
    } else if (StringHelper::toUpper(listChoice) == "Q" ||
               StringHelper::isAnagramOf(listChoice, "quit")) {
      std::cout << RED << BOLD << "\nPROGRAM EXITED\n\n" << CLEAR;
      return 0;
    } else {
      std::cout << RED << listChoice << " is not a valid option." << std::endl;
      std::cout << YELLOW << "Please choose one of the lists to get started"
                << CLEAR << std::endl;

      continue;
    }

    while (true) {
      std::cout << "\nChoose a task to perform on the "
                << studentListNames[listID] << "list:" << std::endl;
      std::cout << "(S)earch Student" << std::endl;
      std::cout << "(C)reate Student" << std::endl;
      std::cout << "(R)emove Student by First and Last name" << std::endl;
      std::cout << "(D)elete Head & Tail Nodes" << std::endl;
      std::cout << "(P)rint List" << std::endl;

      std::cin >> taskChoice;

      if (StringHelper::toUpper(taskChoice) == "S" ||
          StringHelper::isAnagramOf(taskChoice, "search")) {
        // Search Options
      } else if (StringHelper::toUpper(taskChoice) == "C" ||
                 StringHelper::isAnagramOf(taskChoice, "create")) {
      } else if (StringHelper::toUpper(taskChoice) == "R" ||
                 StringHelper::isAnagramOf(taskChoice, "remove")) {
      } else if (StringHelper::toUpper(taskChoice) == "D" ||
                 StringHelper::isAnagramOf(taskChoice, "delete")) {
        studentLists[listID]->deleteHeadTail();
      } else if (StringHelper::toUpper(taskChoice) == "P" ||
                 StringHelper::isAnagramOf(taskChoice, "print")) {
        studentLists[listID]->print();
      } else {
        std::cout << RED << taskChoice << " is not a valid option."
                  << std::endl;
        std::cout << YELLOW
                  << "Please choose one of following tasks to get started"
                  << CLEAR << std::endl;
        std::cout
            << "Search: Search for a student based on a variety of criteria\n"
            << "Create: Add a student to the list\n"
            << "Remove: Remove a student from the list if the provided first "
               "and last names match\n"
            << "Delete: Remove the topmost and bottommost student from the "
               "list\n"
            << "Print: Print the current list\n";
      }
    }
  }
}
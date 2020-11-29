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
const std::string CLR = "\033[0m";

void failOnEOF(std::istream& inps) {
  if (inps.eof()) {
    std::cout << RED << BOLD << "\nPROGRAM TERMINATED UNEXPECTEDLY\n\n" << CLR;
    exit(-1);
  }
}

void forceIntInput(std::istream& inps, std::string message, int& field,
                   int maxAllow) {
  do {
    std::cout << message;
    inps >> field;

    failOnEOF(inps);

    if (inps.fail()) {
      inps.clear();
      inps.ignore(INT_MAX, '\n');
      std::cout << YELLOW << BOLD << "Enter a number please. Try again:\n"
                << CLR;
      continue;
    }

    inps.ignore(INT_MAX, '\n');

    if (field >= 0 && field <= maxAllow)
      break;

    std::cout << YELLOW << BOLD
              << "Please enter a valid selection. Try again:\n"
              << CLR;

  } while (true);
}

void forceCGPAinput(std::istream& inps, float& field) {
  do {
    std::cout << "Enter CGPA: ";
    inps >> field;

    failOnEOF(inps);

    if (inps.fail()) {
      inps.clear();
      inps.ignore(INT_MAX, '\n');
      std::cout << YELLOW << BOLD << "Enter a number please. Try again:\n"
                << CLR;
      continue;
    }

    inps.ignore(INT_MAX, '\n');

    if (field >= 0 && field <= 4.33)
      break;

    std::cout << YELLOW << BOLD
              << "Please enter a value between 0 and 4.33. Try again:\n"
              << CLR;

  } while (true);
}

void listSelect(StudentList<Student>* list[3], std::string listNames[3],
                int& domCount, int& intCount);
void actionSelect(StudentList<Student>* list, std::string listName,
                  int& domCount, int& intCount);
void searchSelect(StudentList<Student>* list);
void insertStudent(StudentList<Student>* list, std::string listName,
                   int& domCount, int& intCount);

int main() {
  StudentList<Student> dslist;
  StudentList<Student> islist;
  StudentList<Student> mergedList;

  int dom_stu_count = 0;
  int int_stu_count = 0;

  std::string line;
  std::ifstream domesticFile("domestic-stu.txt");

  if (!domesticFile.is_open()) {
    std::cout << "Unable to open file domestic-stu.txt" << std::endl;
    return -1;
  }

  std::cout << GREEN << "Reading data from domestic-stu.txt..." << CLR
            << std::endl;

  getline(domesticFile, line);  // Discard legend

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
                << "ERROR: domestic-stu.txt does not have all required fields"
                << CLR << std::endl;
      exit(-1);
    }

    if (!StringHelper::isProvince(province)) {
      std::cout << RED << "ERROR: " << province << " is not a valid province."
                << CLR << std::endl;
      exit(-1);
    }

    applicationID = 20200000 + dom_stu_count++;
    try {
      dslist.addStudentNode(new DomesticStudent(
          firstName, lastName, cgpa, researchScore, applicationID, province));
    } catch (std::bad_alloc) {
      std::cerr << "ERROR: Unable to allocate memory. Exiting program."
                << std::endl;
      exit(-1);
    }
  }
  domesticFile.close();

  std::cout << GREEN << "Reading data from domestic-stu.txt succeeded." << CLR
            << std::endl;
  std::ifstream internationalFile("international-stu.txt");
  if (!internationalFile.is_open()) {
    std::cout << "Unable to open file international-stu.txt" << std::endl;
    return -1;
  }
  std::cout << GREEN << "Reading data from international-stu.txt..." << CLR
            << std::endl;
  getline(internationalFile, line);
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
          << "ERROR: international-stu.txt does not have all required fields"
          << CLR << std::endl;
      exit(-1);
    }

    if (!StringHelper::isCountry(country)) {
      std::string anagram = StringHelper::anagramOfCountry(country);
      if (anagram != "") {
        std::cout << YELLOW << "Detected typo in " << CLR << country << YELLOW
                  << ". Autocorrecting to " << anagram << CLR << std::endl;
        country = anagram;
      } else {
        std::cout << RED << "ERROR: " << country << " is not a valid country.\n"
                  << CLR;
        exit(-1);
      }
    }

    applicationID = 20200000 + dom_stu_count + int_stu_count++;
    try {
      islist.addStudentNode(new InternationalStudent(
          firstName, lastName, cgpa, researchScore, applicationID, country,
          reading, listening, speaking, writing));
    } catch (std::bad_alloc) {
      std::cerr << "ERROR: Unable to allocate memory. Exiting program."
                << std::endl;
      exit(-1);
    }
  }
  // close your file
  internationalFile.close();
  std::cout << GREEN << "Reading data from international-stu.txt succeeded."
            << CLR << std::endl;

  // End reading of files and loading of student data

  StudentList<Student>* studentLists[] = {&dslist, &islist, &mergedList};
  std::string studentListNames[] = {"Domestic", "International",
                                    "Merged Domestic and International"};

  listSelect(studentLists, studentListNames, dom_stu_count, int_stu_count);
  return 0;
}

void listSelect(StudentList<Student>* list[3], std::string listNames[3],
                int& domCount, int& intCount) {
  // Menu while loop
  // User chooses either Domestic or International student database
  while (true) {
    std::string listChoice;
    std::cout << std::string(50, '-') << '\n';
    std::cout << "Student Database\n";
    std::cout << std::string(50, '-') << '\n';

    std::cout << BOLD << "Choose a list to interact with:" << CLR << std::endl;
    std::cout << "(D)omestic" << std::endl;
    std::cout << "(I)nternational" << std::endl;
    std::cout << "(M)erged Domestic and International (this copies both lists "
                 "then merges them)"
              << std::endl;
    std::cout << "(Q)uit this program" << std::endl;

    std::cin >> listChoice;

    if (StringHelper::toUpper(listChoice) == "D" ||
        StringHelper::isAnagramOf(listChoice, "domestic")) {
      actionSelect(list[0], listNames[0], domCount, intCount);
    } else if (StringHelper::toUpper(listChoice) == "I" ||
               StringHelper::isAnagramOf(listChoice, "international")) {
      actionSelect(list[1], listNames[1], domCount, intCount);
    } else if (StringHelper::toUpper(listChoice) == "M" ||
               StringHelper::isAnagramOf(listChoice, "merged")) {
      // Merge the lists
      try {
        StudentNodePtr<Student> tempNode = list[0]->getHead();
        while (tempNode != nullptr) {
          DomesticStudent* tempStudent =
              dynamic_cast<DomesticStudent*>(tempNode->getStudent());
          list[2]->addStudentNode(new DomesticStudent(*tempStudent));
          tempNode = tempNode->getLink();
        }

        tempNode = list[1]->getHead();
        while (tempNode != nullptr) {
          InternationalStudent* tempStudent =
              dynamic_cast<InternationalStudent*>(tempNode->getStudent());

          // If the TOEFL score meets the conditions, add it
          if (tempStudent->getToefl().meetsRequirements())
            list[2]->addStudentNode(new InternationalStudent(*tempStudent));
          tempNode = tempNode->getLink();
        }
      } catch (std::bad_alloc) {
        std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
        exit(-1);
      }
      actionSelect(list[2], listNames[2], domCount, intCount);
    } else if (StringHelper::toUpper(listChoice) == "Q" ||
               StringHelper::isAnagramOf(listChoice, "quit")) {
      std::cout << RED << BOLD << "\nPROGRAM EXITED\n\n" << CLR;
      return;
    } else {
      failOnEOF(std::cin);
      std::cout << RED << listChoice << " is not a valid option." << std::endl;
      std::cout << YELLOW << "Please choose one of the lists to get started"
                << CLR << std::endl;

      continue;
    }
  }
}
void actionSelect(StudentList<Student>* list, std::string listName,
                  int& domCount, int& intCount) {
  bool selecting = true;
  while (selecting) {
    std::string taskChoice;
    std::cout << BOLD << "\nChoose a task to perform on the " << listName
              << " student list:" << CLR << std::endl;
    std::cout << "(S)earch Student" << std::endl;
    std::cout << ((listName.substr(0, 6) == "Merged") ? ""
                                                      : "(C)reate Student\n");
    std::cout << "(R)emove Student by First and Last name" << std::endl;
    std::cout << "(D)elete Head & Tail Nodes" << std::endl;
    std::cout << "(P)rint List" << std::endl;
    std::cout << "(B)ack to previous menu" << std::endl;

    std::cin >> taskChoice;

    if (StringHelper::toUpper(taskChoice) == "S" ||
        StringHelper::isAnagramOf(taskChoice, "search")) {
      if (list->isEmpty()) {
        std::cout << RED << "The list is empty." << CLR << std::endl;
        selecting = false;
      } else
        searchSelect(list);
    } else if (StringHelper::toUpper(taskChoice) == "C" ||
               StringHelper::isAnagramOf(taskChoice, "create")) {
      if (listName.substr(0, 6) == "Merged")
        std::cout << RED << taskChoice << " is not a valid option." << CLR
                  << std::endl;
      else
        insertStudent(list, listName, domCount, intCount);
    } else if (StringHelper::toUpper(taskChoice) == "R" ||
               StringHelper::isAnagramOf(taskChoice, "remove")) {
      if (list->isEmpty()) {
        std::cout << RED << "The list is empty." << CLR << std::endl;
        selecting = false;
        continue;
      }
      std::string firstName, lastName;
      std::cout << "Enter first name: ";
      std::cin >> firstName;
      std::cout << "Enter last name: ";
      std::cin >> lastName;
      if (list->deleteFirstLast(firstName, lastName)) {
        std::cout << GREEN << "Deleted specified students.\n" << CLR;
      } else {
        std::cout << RED << "No students matched your query\n" << CLR;
      }

    } else if (StringHelper::toUpper(taskChoice) == "D" ||
               StringHelper::isAnagramOf(taskChoice, "delete")) {
      if (list->isEmpty()) {
        std::cout << RED << "The list is empty." << CLR << std::endl;
        selecting = false;
      } else {
        list->deleteHeadTail();
        std::cout << GREEN << "Deleted head/tail nodes" << CLR << std::endl;
      }
    } else if (StringHelper::toUpper(taskChoice) == "P" ||
               StringHelper::isAnagramOf(taskChoice, "print")) {
      list->print();
    } else if (StringHelper::toUpper(taskChoice) == "B" ||
               StringHelper::isAnagramOf(taskChoice, "back")) {
      selecting = false;
    } else {
      failOnEOF(std::cin);
      std::cout << RED << taskChoice << " is not a valid option." << std::endl;
      std::cout << YELLOW
                << "Please choose one of following tasks to get started" << CLR
                << std::endl;
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
void searchSelect(StudentList<Student>* list) {
  std::string searchMethod;
  bool searchAgain;
  do {
    searchAgain = false;
    std::cout << BOLD << "\nHow would you like to search the list?\n" << CLR;
    std::cout << "(A)pplication ID\n";
    std::cout << "(C)GPA\n";
    std::cout << "(R)esearch Score\n";
    std::cout << "(F)irst and Last name\n";
    std::cout << "(H)ybrid Threshold of CGPA and Research Score\n";
    std::cout << "(B)ack to previous menu\n";

    std::cin >> searchMethod;

    if (StringHelper::toUpper(searchMethod) == "A" ||
        StringHelper::isAnagramOf(searchMethod, "application")) {
      int id;
      forceIntInput(std::cin, "Enter the application ID: ", id, INT_MAX);
      list->searchAppID(id);

    } else if (StringHelper::toUpper(searchMethod) == "C" ||
               StringHelper::isAnagramOf(searchMethod, "cgpa")) {
      float cgpa;
      forceCGPAinput(std::cin, cgpa);
      list->searchCGPA(cgpa);
    } else if (StringHelper::toUpper(searchMethod) == "R" ||
               StringHelper::isAnagramOf(searchMethod, "research")) {
      int score;
      forceIntInput(std::cin, "Enter the research score: ", score, 100);
      list->searchResearchScore(score);
    } else if (StringHelper::toUpper(searchMethod) == "F" ||
               StringHelper::isAnagramOf(searchMethod, "first")) {
      std::string firstName, lastName;
      std::cout << "Enter first name: ";
      std::cin >> firstName;
      std::cout << "Enter last name: ";
      std::cin >> lastName;
      list->searchFirstLast(firstName, lastName);
    } else if (StringHelper::toUpper(searchMethod) == "H" ||
               StringHelper::isAnagramOf(searchMethod, "hybrid")) {
      float cgpa;
      forceCGPAinput(std::cin, cgpa);
      int score;
      forceIntInput(std::cin, "Enter the research score: ", score, 100);
      list->searchCGPAandResearchScoreThreshold(cgpa, score);
    } else if (StringHelper::toUpper(searchMethod) == "B" ||
               StringHelper::isAnagramOf(searchMethod, "back")) {
      continue;
    } else {
      failOnEOF(std::cin);
      std::cout << RED << searchMethod << " is not a valid option." << CLR
                << std::endl;
      searchAgain = true;
    }
  } while (searchAgain);
}

void insertStudent(StudentList<Student>* list, std::string listName,
                   int& domCount, int& intCount) {
  std::string firstName, lastName, location;
  float CGPA = -1;
  int researchScore = -1;

  std::cout << "Enter first name: ";
  std::cin >> firstName;
  std::cout << "Enter last name: ";
  std::cin >> lastName;
  forceCGPAinput(std::cin, CGPA);
  forceIntInput(std::cin, "Enter Research Score: ", researchScore, 100);

  if (listName == "Domestic") {
    do {
      std::cout << "Enter Province Code (AB, BC,...): ";
      std::cin >> location;
      if (!StringHelper::isProvince(location))
        std::cout << RED << "That is not a valid province code.\n" << CLR;

    } while (!StringHelper::isProvince(location));

  } else if (listName == "International") {
    do {
      std::cout << "Enter Country: ";
      std::cin >> location;
      if (!StringHelper::isCountry(location))
        std::cout << RED << "That is not a valid country code.\n" << CLR;

    } while (!StringHelper::isCountry(location));
  }

  if (listName == "Domestic") {
    try {
      list->addStudentNode(
          new DomesticStudent(firstName, lastName, CGPA, researchScore,
                              20202020 + intCount + domCount++, location));
    } catch (std::bad_alloc) {
      std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
      exit(-1);
    }

  } else {
    int r, l, s, w;
    forceIntInput(std::cin, "Enter TOEFL Reading Score (max 30): ", r, 30);
    forceIntInput(std::cin, "Enter TOEFL Listening Score (max 30): ", l, 30);
    forceIntInput(std::cin, "Enter TOEFL Speaking Score (max 30): ", s, 30);
    forceIntInput(std::cin, "Enter TOEFL Writing Score (max 30): ", w, 30);
    try {
      list->addStudentNode(new InternationalStudent(
          firstName, lastName, CGPA, researchScore,
          20202020 + domCount + intCount++, location, r, l, s, w));
    } catch (std::bad_alloc) {
      std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
      exit(-1);
    }
  }
}
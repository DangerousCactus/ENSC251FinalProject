#include <climits>
#include <cstdlib>   //atof and atoi
#include <fstream>   //file processing
#include <iostream>  //cin and cout
#include <sstream>   //formatted string processing
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
  StudentList<DomesticStudent> sl;
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

    applicationID = 20200000 + dom_stu_count;
    sl.addStudentNode(DomesticStudent(firstName, lastName, cgpa, researchScore,
                                      applicationID, province));

    dom_stu_count++;
  }

  domesticFile.close();
  StudentList<DomesticStudent> sl2(sl);
  StudentList<DomesticStudent> sl3 = sl;

  sl.print();
}

/*
int main() {
  DomesticStudent* domesticStudents[100];
  InternationalStudent* internationalStudents[100];

  // Read the domestic-stu.txt file and exit if failed
  string line;
  ifstream domesticFile("domestic-stu.txt");
  if (!domesticFile.is_open()) {
    cout << "Unable to open file domestic-stu.txt" << endl;
    return -1;
  }

  // Read the first line of domestic-stu.txt, which specifies
  // the file format. And then print it out to the screen
  getline(domesticFile, line);
  // cout << "File format: " << line << endl;

  int dom_stu_count = 0;
  while (getline(domesticFile, line)) {
    istringstream ss(line);

    string firstName, lastName, province, s_cgpa, s_researchScore;
    float cgpa;
    int researchScore, applicationID;

    // get firstName separated by comma
    getline(ss, firstName, ',');

    // get lastName separated by comma
    getline(ss, lastName, ',');

    // get province separated by comma
    getline(ss, province, ',');

    // get cpga separated by comma, and convert string to float
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());

    // get researchScore separated by comma, and convert it to int
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());

    applicationID = 20200000 + dom_stu_count;
    domesticStudents[dom_stu_count] = new DomesticStudent(
        firstName, lastName, cgpa, researchScore, applicationID, province);

    dom_stu_count++;
  }

  // close your file
  domesticFile.close();

  ifstream internationalFile("international-stu.txt");
  if (!internationalFile.is_open()) {
    cout << "Unable to open file international-stu.txt" << endl;
    return -1;
  }
  getline(internationalFile, line);
  int int_stu_count = 0;
  while (getline(internationalFile, line)) {
    istringstream ss(line);

    string firstName, lastName, country, s_cgpa, s_researchScore, s_reading,
        s_listening, s_speaking, s_writing;
    float cgpa;
    int researchScore, reading, listening, speaking, writing, applicationID;

    // get firstName separated by comma
    getline(ss, firstName, ',');

    // get lastName separated by comma
    getline(ss, lastName, ',');

    // get province separated by comma
    getline(ss, country, ',');

    // get cpga separated by comma, and convert string to float
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());

    // get researchScore separated by comma, and convert it to int
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

  // End reading of files and loading of student data

  int domOrInt = 0, sortType = 0;
  // By storing the pointers, we can just index stuLists instead of using if
  // statements
  Student** stuLists[] = {(Student**)domesticStudents,
                          (Student**)internationalStudents};
  int stuCounts[] = {dom_stu_count, int_stu_count};

  // Menu while loop
  // User chooses either Domestic or International student database
  while (true) {
    cout << string(50, '-') << '\n';
    cout << "Student Database\n";
    cout << string(50, '-') << '\n';

    cout << "Choose an option below to sort:" << endl;
    cout << "1. Domestic" << endl;
    cout << "2. International" << endl;
    cout << "3. Quit" << endl;

    // User chooses the sorting order of the previously selected student
    // database

    forceIntInput(cin, "> ", domOrInt, 3);

    // Quit the program
    if (domOrInt == 3) {
      cout << RED << BOLD << "\nPROGRAM EXITED\n\n" << CLEAR;
      for (int i = 0; i < dom_stu_count; i++)
        delete domesticStudents[i];

      for (int i = 0; i < int_stu_count; i++)
        delete internationalStudents[i];
      return 0;
    }

    cout << "\nChoose a sorting order" << endl;
    cout << "1. CGPA" << endl;
    cout << "2. Research Score" << endl;
    cout << "3. First Name" << endl;
    cout << "4. Last Name" << endl;
    cout << "5. Location" << endl;
    cout << "6. Overall" << endl;

    forceIntInput(cin, "> ", sortType, 6);

    switch (sortType) {
      case 1:
        sortByCGPA(stuLists[domOrInt - 1], stuCounts[domOrInt - 1]);
        break;
      case 2:
        sortByResearchScore(stuLists[domOrInt - 1], stuCounts[domOrInt - 1]);
        break;
      case 3:
        sortByFirstName(stuLists[domOrInt - 1], stuCounts[domOrInt - 1]);
        break;
      case 4:
        sortByLastName(stuLists[domOrInt - 1], stuCounts[domOrInt - 1]);
        break;
      case 5:
        if (domOrInt == 1)
          sortByLocation(domesticStudents, dom_stu_count);
        else
          sortByLocation(internationalStudents, int_stu_count);
        break;
      case 6:
        if (domOrInt == 1)
          sortByOverall(domesticStudents, dom_stu_count);
        else
          sortByOverall(internationalStudents, int_stu_count);
        break;
      default:
        cout << RED << "\nInvalid Input!" << BOLD << "\n\nPlease try again\n\n"
             << CLEAR << endl;
    }
    // Loops through the array of pointers for the selected student database
    // and outputs each student's information.
    if (domOrInt == 1)
      for (int i = 0; i < dom_stu_count; i++)
        cout << *domesticStudents[i] << endl;
    else
      for (int i = 0; i < int_stu_count; i++)
        cout << *internationalStudents[i] << endl;
  }
}
*/
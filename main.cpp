#include <cstdlib>   //atof and atoi
#include <fstream>   //file processing
#include <iostream>  //cin and cout
#include <sstream>   //formatted string processing
#include "domesticStudent.hpp"
#include "internationalStudent.hpp"

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

  sortByOverall(internationalStudents, int_stu_count);
  for (int i = 0; i < int_stu_count; i++) {
    cout << *internationalStudents[i] << endl;
  }

  return 0;
}

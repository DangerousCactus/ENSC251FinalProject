#ifndef STUDENTLIST_HPP
#define STUDENTLIST_HPP
#include <iostream>
#include "StudentNode.hpp"
#include "student.hpp"

// Define an alias to make the class easier to understand
template <typename T>
using StudentNodePtr = StudentNode<T>*;

template <typename T>
class StudentList {
 private:  // By default the list is empty
  StudentNodePtr<T> head = nullptr;
  StudentNodePtr<T> tail = nullptr;

 public:
  StudentList();

  // Dynamic big three since we have dynamic member variables
  StudentList(const StudentList& studentList);
  StudentList& operator=(const StudentList studentList);
  ~StudentList();

  StudentNodePtr<T> getHead() const;
  StudentNodePtr<T> getTail() const;

  void setHead(const StudentNodePtr<T> head);
  void setTail(const StudentNodePtr<T> tail);

  // Add a student to the list by passing a pointer to the student object.
  void addStudentNode(T* student);

  // Delete a student from the list based on first and last name
  bool deleteFirstLast(std::string first, std::string last);
  // Delete both the head and tail of the student list in one delete function
  bool deleteHeadTail();

  /*Search students in the list based on multiple fields*/

  void searchAppID(int id) const;
  void searchCGPA(float cgpa) const;
  void searchFirstLast(std::string first, std::string last) const;
  void searchResearchScore(int score) const;

  // Prints out all students which have a CGPA and Research Score that are both
  // greater than or equal to the given threshold
  void searchCGPAandResearchScoreThreshold(float CGPA, int score) const;

  // Print out all the objects in the list by calling the (virtual) print
  // function of each object
  void print();

 private:
  // Internal recursive/iterative functions used for initialization and
  // destruction of the StudentList
  
  void deleteList();
  void deleteStudentNode(StudentNodePtr<T> studentNode);
  void copySubList(StudentNodePtr<T> node);
};

#include "StudentList.cpp"
#endif
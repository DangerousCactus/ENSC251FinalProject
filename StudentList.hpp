#ifndef STUDENTLIST_HPP
#define STUDENTLIST_HPP
#include <iostream>
#include "StudentNode.hpp"
#include "student.hpp"

template <typename T>
using StudentNodePtr = StudentNode<T>*;

template <typename T>
class StudentList {
 private:
  StudentNodePtr<T> head = nullptr;
  StudentNodePtr<T> tail = nullptr;

 public:
  StudentList();

  StudentList(const StudentList& studentList);
  StudentList& operator=(const StudentList studentList);
  ~StudentList();

  StudentNodePtr<T> getHead();
  StudentNodePtr<T> getTail();

  void setHead(StudentNodePtr<T> head);
  void setTail(StudentNodePtr<T> tail);

  void addStudentNode(T* student);
  void deleteStudentNode(StudentNodePtr<T> studentNode);
  void deleteFirstLast(std::string first, std::string last);
  void deleteHeadTail();

  void searchAppID(int id);
  void searchCGPA(float cgpa);
  void searchFirstLast(std::string first, std::string last);
  void searchResearchScore(int score);
  void searchCGPAandResearchScoreThreshold(float CGPA, int score);

  void print();
};

#include "StudentList.cpp"
#endif
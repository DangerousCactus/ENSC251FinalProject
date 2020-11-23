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

  StudentNodePtr<T> getHead() const;
  StudentNodePtr<T> getTail() const;

  void setHead(const StudentNodePtr<T> head);
  void setTail(const StudentNodePtr<T> tail);

  void addStudentNode(const T& student);
  void deleteFirstLast(std::string first, std::string last);
  void deleteHeadTail();

  void searchAppID(int id) const;
  void searchCGPA(float cgpa) const;
  void searchFirstLast(std::string first, std::string last) const;
  void searchResearchScore(int score) const;
  void searchCGPAandResearchScoreThreshold(float CGPA, int score) const;

  void print();

 private:
  void deleteList();
  void deleteStudentNode(StudentNodePtr<T> studentNode);
  void copySubList(StudentNodePtr<T> node);
};

#include "StudentList.cpp"
#endif
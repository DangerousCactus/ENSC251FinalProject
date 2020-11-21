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

  void addStudentNode(T student);
  void print();
};

#include "StudentList.cpp"
#endif
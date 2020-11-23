#ifndef STUDENTNODE_CPP
#define STUDENTNODE_CPP
#include "StudentNode.hpp"
#include <iostream>

template <typename T>
StudentNode<T>::StudentNode() {}

template <typename T>
StudentNode<T>::StudentNode(T student) {
  try {
    this->student = new T(student);
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
    exit(-1);
  }
}

template <typename T>
StudentNode<T>::StudentNode(const StudentNode& studentNode)
    : StudentNode(*(studentNode.student)) {}

template <typename T>
StudentNode<T>& StudentNode<T>::operator=(const StudentNode<T> studentNode) {
  this->student = T(*studentNode.student);
  return this;
}

template <typename T>
StudentNode<T>::~StudentNode() {
  delete student;
}

template <typename T>
StudentNode<T>* StudentNode<T>::getLink() const {
  return link;
}

template <typename T>
T* StudentNode<T>::getStudent() const {
  return student;
}

template <typename T>
void StudentNode<T>::setLink(StudentNode* link) {
  this->link = link;
}

template <typename T>
void StudentNode<T>::setStudent(T* student) {
  this->student = student;
}

#endif
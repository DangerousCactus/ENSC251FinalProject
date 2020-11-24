#ifndef STUDENTNODE_CPP
#define STUDENTNODE_CPP
#include "StudentNode.hpp"
#include <iostream>

template <typename T>
StudentNode<T>::StudentNode() {}

template <typename T>
StudentNode<T>::StudentNode(T* student) {
  this->student = student;
}

template <typename T>
StudentNode<T>::StudentNode(const StudentNode& studentNode)
    : StudentNode(new T(*studentNode.student)) {}

template <typename T>
StudentNode<T>& StudentNode<T>::operator=(const StudentNode<T> studentNode) {
  delete this->student;
  this->student = new T(*studentNode.student);
  return this;
}

template <typename T>
StudentNode<T>::~StudentNode() {
  delete student;
}

// Getters
template <typename T>
StudentNode<T>* StudentNode<T>::getLink() const {
  return link;
}

template <typename T>
T* StudentNode<T>::getStudent() const {
  return student;
}

// Setters
template <typename T>
void StudentNode<T>::setLink(StudentNode* link) {
  this->link = link;
}

template <typename T>
void StudentNode<T>::setStudent(T* student) {
  this->student = student;
}

#endif
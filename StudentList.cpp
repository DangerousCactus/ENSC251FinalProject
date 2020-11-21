#ifndef STUDENTLIST_CPP
#define STUDENTLIST_CPP
#include "StudentList.hpp"

template <typename T>
StudentList<T>::StudentList() {}

template <typename T>
StudentList<T>::StudentList(const StudentList& studentList) {
  StudentNodePtr<T> currOldHead = studentList.head;

  head = new StudentNode<T>(*currOldHead);
  StudentNodePtr<T> currNewHead = head;

  currOldHead = currOldHead->getLink();

  while (currOldHead != nullptr) {
    currNewHead->setLink(new StudentNode<T>(*(currOldHead->getStudent())));
    currNewHead = currNewHead->getLink();
    currOldHead = currOldHead->getLink();
  }

  tail = currNewHead;
}

template <typename T>
StudentList<T>& StudentList<T>::operator=(const StudentList<T> studentList) {
  StudentNodePtr<T> currHead = head;
  while (currHead != nullptr) {
    StudentNodePtr<T> temp = currHead;
    currHead = currHead->getLink();
    delete temp;
  }

  StudentNodePtr<T> currOldHead = studentList.head;
  StudentNodePtr<T> currNewHead = head;

  currNewHead = new StudentNode<T>(currOldHead);
  currOldHead = currOldHead->getLink();

  while (currOldHead != nullptr) {
    currNewHead->setLink(new StudentNode<T>(currOldHead->getLink()));
    currNewHead = currNewHead->getLink();
    currOldHead = currOldHead->getLink();
  }

  return this;
}

template <typename T>
StudentList<T>::~StudentList() {
  StudentNodePtr<T> currHead = head;
  while (currHead != nullptr) {
    StudentNodePtr<T> temp = currHead;
    currHead = currHead->getLink();
    delete temp;
  }
}

template <typename T>
StudentNodePtr<T> StudentList<T>::getHead() {
  return head;
}

template <typename T>
StudentNodePtr<T> StudentList<T>::getTail() {
  return tail;
}

template <typename T>
void StudentList<T>::addStudentNode(T student) {
  StudentNodePtr<T> currParent = head;
  StudentNodePtr<T> newNode = new StudentNode<T>(student);

  // if (currParent == nullptr) {
  //   head = newNode;
  //   tail = newNode;
  // } else {
  //   tail->setLink(newNode);
  //   tail = newNode;
  // }

  if (currParent == nullptr) {
    head = newNode;
    tail = newNode;
    return;
  } else {
    while (*(currParent->getStudent()) > student) {
      if (currParent->getLink() == nullptr) {
        currParent->setLink(newNode);
        tail = newNode;
        return;
      } else {
        currParent = currParent->getLink();
      }
    }
    T* tempStudent = newNode->getStudent();
    newNode->setStudent(currParent->getStudent());
    currParent->setStudent(tempStudent);
    newNode->setLink(currParent->getLink());
    currParent->setLink(newNode);
    return;
  }
}

template <typename T>
void StudentList<T>::print() {
  StudentNodePtr<T> currHead = head;
  while (currHead != nullptr) {
    std::cout << *(currHead->getStudent()) << std::endl;
    currHead = currHead->getLink();
  }
}

#endif
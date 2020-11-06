#ifndef STUDENTLIST_CPP
#define STUDENTLIST_CPP
#include "StudentList.hpp"

template <typename T>
void deleteSubList(StudentNodePtr<T> toDelete) {
  if (toDelete == nullptr)
    return;
  deleteSubList(toDelete->link);
  delete toDelete;
}

template <typename T>
StudentNodePtr<T> copySubList(StudentNodePtr<T> toCopy,
                              StudentNodePtr<T> currHead,
                              StudentNodePtr<T>& tail) {
  if (toCopy == nullptr) {
    tail = currHead;
    return nullptr;
  } else {
    StudentNodePtr<T> newNode = new StudentNode<T>;
    newNode->student = toCopy->student;
    newNode->link = copySubList(toCopy->link, newNode, tail);
    return newNode;
  }
}

template <typename T>
StudentList<T>::StudentList() {}

template <typename T>
StudentList<T>::StudentList(const StudentList& studentList) {
  head = copySubList(studentList.head, (StudentNodePtr<T>)nullptr, tail);
}

template <typename T>
StudentList<T>& StudentList<T>::operator=(const StudentList studentList) {
  deleteSubList(head);
  head = copySubList(studentList.head, nullptr, tail);
}

template <typename T>
StudentList<T>::~StudentList() {
  deleteSubList(head);
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
  StudentNodePtr<T> newNode = new StudentNode<T>;
  StudentNodePtr<T> currParent = head;

  if (currParent == nullptr) {
    head = newNode;
    tail = newNode;
    newNode->student = student;
  } else {
    while (currParent->student > student) {
      if (currParent->link == nullptr) {
        currParent->link = newNode;
        newNode->student = student;
        tail = newNode;
        return;
      }
      currParent = currParent->link;
    }
    T temp = currParent->student;
    currParent->student = student;
    newNode->student = temp;

    newNode->link = currParent->link;
    currParent->link = newNode;
  }
}

template <typename T>
void StudentList<T>::print() {
  StudentNodePtr<T> currHead = head;
  while (currHead != nullptr) {
    std::cout << currHead->student << std::endl;
    currHead = currHead->link;
  }
}

#endif
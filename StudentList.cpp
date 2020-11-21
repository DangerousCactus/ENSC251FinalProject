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
    currNewHead->setLink(new StudentNode<T>(*currOldHead));
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
void StudentList<T>::setHead(StudentNodePtr<T> head) {
  this->head = head;
}

template <typename T>
void StudentList<T>::setTail(StudentNodePtr<T> tail) {
  this->tail = tail;
}

template <typename T>
void StudentList<T>::addStudentNode(T* student) {
  StudentNodePtr<T> currParent = head;
  StudentNodePtr<T> newNode = new StudentNode<T>(student);

  if (currParent == nullptr) {
    head = newNode;
    tail = newNode;
    return;
  } else {
    while (!(*(currParent->getStudent()) < *student)) {
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

    if (newNode->getLink() == nullptr)
      tail = newNode;

    return;
  }
}

template <typename T>
void StudentList<T>::deleteStudentNode(StudentNodePtr<T> studentNode) {
  if (head == nullptr)
    return;

  if (head == studentNode) {
    head = studentNode->getLink();
    if (tail == studentNode) {
      tail = nullptr;
    }
    delete studentNode;
    return;
  }

  StudentNodePtr<T> temp = head;
  while (temp->getLink() != studentNode) {
    if (temp->getLink() == nullptr)
      return;
    temp = temp->getLink();
  }

  temp->setLink(studentNode->getLink());
  if (tail == studentNode)
    tail = temp;

  delete studentNode;
}

template <typename T>
void StudentList<T>::print() {
  StudentNodePtr<T> currHead = head;
  while (currHead != nullptr) {
    std::cout << *(currHead->getStudent()) << std::endl;
    currHead = currHead->getLink();
  }
}

template <typename T>
void StudentList<T>::searchAppID(int id) {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getApplicationID() == id) {
      std::cout << *(currHead->getStudent()) << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "No matching records found.\n";
}

template <typename T>
void StudentList<T>::searchCGPA(float cgpa) {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getcgpa() == cgpa) {
      std::cout << *(currHead->getStudent()) << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "No matching records found.\n";
}

template <typename T>
void StudentList<T>::searchResearchScore(int score) {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getResearchScore() == score) {
      std::cout << *(currHead->getStudent()) << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "No matching records found.\n";
}

template <typename T>
void StudentList<T>::searchFirstLast(std::string first, std::string last) {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  T temp;
  temp.setFirstName(first);
  temp.setLastName(last);

  while (currHead != nullptr) {
    if (compareFirstName(*(currHead->getStudent()), temp) == 0 &&
        compareLastName(*(currHead->getStudent()), temp) == 0) {
      std::cout << *(currHead->getStudent()) << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "No matching records found.\n";
}

template <typename T>
void StudentList<T>::deleteFirstLast(std::string first, std::string last) {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  T temp;
  temp.setFirstName(first);
  temp.setLastName(last);

  while (currHead != nullptr) {
    if (currHead->getStudent()->getFirstName() == first &&
        currHead->getStudent()->getLastName() == last) {
      deleteStudentNode(currHead);
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "No matching records found.\n";
}

template <typename T>
void StudentList<T>::deleteHeadTail() {
  deleteStudentNode(head);
  deleteStudentNode(tail);
}
#endif
#ifndef STUDENTLIST_CPP
#define STUDENTLIST_CPP
#include "StudentList.hpp"
#include <iostream>
#include <sstream>
#include "StringHelper.hpp"

template <typename T>
StudentList<T>::StudentList() {}

template <typename T>
StudentList<T>::StudentList(const StudentList& studentList) {
  this->copySubList(studentList.head);
}

template <typename T>
StudentList<T>& StudentList<T>::operator=(const StudentList<T> studentList) {
  this->deleteList();
  this->copySubList(studentList.head);
  return this;
}

template <typename T>
StudentList<T>::~StudentList() {
  this->deleteList();
}

// Iterates over the list and deletes each StudentNode
template <typename T>
void StudentList<T>::deleteList() {
  StudentNodePtr<T> currHead = head;
  while (currHead != nullptr) {
    StudentNodePtr<T> temp = currHead;
    currHead = currHead->getLink();
    delete temp;
  }
  head = nullptr;
  tail = nullptr;
}

// Copies a list starting from a given node
template <typename T>
void StudentList<T>::copySubList(StudentNodePtr<T> node) {
  StudentNodePtr<T> currOldHead = node;
  if (currOldHead == nullptr)  // If the list we are copying from is empty
    return;

  try {  // Copy over the top most node
    head = new StudentNode<T>(*currOldHead);
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
    exit(-1);
  }

  StudentNodePtr<T> currNewHead = head;
  currOldHead = currOldHead->getLink();

  // Keep copying until we hit the end of the list
  while (currOldHead != nullptr) {
    try {
      currNewHead->setLink(new StudentNode<T>(*(currOldHead)));
    } catch (std::bad_alloc) {
      std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
      exit(-1);
    }

    currNewHead = currNewHead->getLink();
    currOldHead = currOldHead->getLink();
  }

  // Set the tail to the last node
  tail = currNewHead;
}

// Getters
template <typename T>
StudentNodePtr<T> StudentList<T>::getHead() const {
  return head;
}

template <typename T>
StudentNodePtr<T> StudentList<T>::getTail() const {
  return tail;
}

// Setters
template <typename T>
void StudentList<T>::setHead(const StudentNodePtr<T> head) {
  this->head = head;
}

template <typename T>
void StudentList<T>::setTail(const StudentNodePtr<T> tail) {
  this->tail = tail;
}

// Takes a pointer to a student and places it into the list while maintaining a
// sorted order
template <typename T>
void StudentList<T>::addStudentNode(T* student) {
  StudentNodePtr<T> currParent = head;
  StudentNodePtr<T> newNode;

  try {  // Create the studentNode
    newNode = new StudentNode<T>(student);
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
    exit(-1);
  }

  if (currParent == nullptr) {  // If the list is empty
    head = newNode;
    tail = newNode;
    return;
  } else {  // Sort in non-increasing order
    while (!(*currParent->getStudent() < *student)) {
      if (currParent->getLink() == nullptr) {  // If we've reached the end
        currParent->setLink(newNode);
        tail = newNode;
        return;
      } else {
        currParent = currParent->getLink();
      }
    }

    // Place the node into the list
    newNode->setStudent(currParent->getStudent());
    currParent->setStudent(student);
    newNode->setLink(currParent->getLink());
    currParent->setLink(newNode);

    // If we just added to the end of the list, update the tail
    if (newNode->getLink() == nullptr)
      tail = newNode;

    return;
  }
}

// Delete a StudentNode by searching for the StudentNodePointer
template <typename T>
void StudentList<T>::deleteStudentNode(StudentNodePtr<T> studentNode) {
  if (head == nullptr)  // If the list is empty
    return;

  if (head == studentNode) {  // If the node is at the top
    head = studentNode->getLink();
    if (tail == studentNode) {  // If our node was the only one in the list
      tail = nullptr;
    }
    delete studentNode;
    return;
  }

  StudentNodePtr<T> temp = head;

  // Iterate over the list
  while (temp->getLink() != studentNode) {
    // If we've reached the end but still haven't found the node
    if (temp->getLink() == nullptr)
      return;
    temp = temp->getLink();
  }

  // Delete the node now that we've found it, and update the links
  temp->setLink(studentNode->getLink());
  if (tail == studentNode)
    tail = temp;

  delete studentNode;
}

// Print each object in the list
template <typename T>
void StudentList<T>::print() {
  StudentNodePtr<T> currHead = head;
  while (currHead != nullptr) {
    std::cout << *currHead->getStudent() << std::endl;
    currHead = currHead->getLink();
  }
  if (head == nullptr) {
    std::cout << "\033[31m"
              << "The list is empty."
              << "\033[0m" << std::endl;
  }
}

// The following functions search the list based on various criteria

template <typename T>
void StudentList<T>::searchAppID(int id) const {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getApplicationID() == id) {
      if (!found)
        std::cout << std::string(80, '-') << std::endl;
      std::cout << *currHead->getStudent() << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "\033[31mNo matching records found.\033[0m\n";
  else
    std::cout << std::string(80, '-') << std::endl;
}

template <typename T>
void StudentList<T>::searchCGPA(float cgpa) const {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getCGPA() == cgpa) {
      if (!found)
        std::cout << std::string(80, '-') << std::endl;
      std::cout << *currHead->getStudent() << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "\033[31mNo matching records found.\033[0m\n";
  else
    std::cout << std::string(80, '-') << std::endl;
}

template <typename T>
void StudentList<T>::searchResearchScore(int score) const {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getResearchScore() == score) {
      if (!found)
        std::cout << std::string(80, '-') << std::endl;
      std::cout << *currHead->getStudent() << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "\033[31mNo matching records found.\033[0m\n";
  else
    std::cout << std::string(80, '-') << std::endl;
}

template <typename T>
void StudentList<T>::searchFirstLast(std::string first,
                                     std::string last) const {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  bool foundClose = false;
  std::stringstream possibleMatches;

  T temp;
  temp.setFirstName(first);
  temp.setLastName(last);

  while (currHead != nullptr) {
    if (compareFirstName(*currHead->getStudent(), temp) == 0 &&
        compareLastName(*currHead->getStudent(), temp) == 0) {
      if (!found)
        std::cout << std::string(80, '-') << std::endl;
      std::cout << *currHead->getStudent() << std::endl;
      found = true;
    } else if (StringHelper::isAnagramOf(currHead->getStudent()->getFirstName(),
                                         first) &&
               StringHelper::isAnagramOf(currHead->getStudent()->getLastName(),
                                         last)) {
      possibleMatches << *currHead->getStudent() << '\n';
      foundClose = true;
    }
    currHead = currHead->getLink();
  }
  if (!found) {
    std::cout << "\033[31mNo matching records found.\033[0m\n";
    if (foundClose) {
      std::cout << "\033[33mHowever, we did find some similar students to your "
                   "query\033[0m\n";
      std::cout << std::string(80, '-') << std::endl
                << possibleMatches.str() << std::string(80, '-') << std::endl;
    }
  } else
    std::cout << std::string(80, '-') << std::endl;
}

// Print out all students that meet the CGPA and Research Score threshold
template <typename T>
void StudentList<T>::searchCGPAandResearchScoreThreshold(float CGPA,
                                                         int score) const {
  StudentNodePtr<T> currHead = head;
  bool found = false;

  while (currHead != nullptr) {
    if (currHead->getStudent()->getCGPA() >= CGPA &&
        currHead->getStudent()->getResearchScore() >= score) {
      if (!found)
        std::cout << std::string(80, '-') << std::endl;
      std::cout << *currHead->getStudent() << std::endl;
      found = true;
    }
    currHead = currHead->getLink();
  }
  if (!found)
    std::cout << "\033[31mNo matching records found.\033[0m\n";
  else
    std::cout << std::string(80, '-') << std::endl;
}

// Delete all objects in the list which have the specified first and last name
template <typename T>
bool StudentList<T>::deleteFirstLast(std::string first, std::string last) {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  T temp;
  temp.setFirstName(StringHelper::toUpper(first));
  temp.setLastName(StringHelper::toUpper(last));

  if (head == nullptr)
    return true;

  while (compareFirstName(*currHead->getStudent(), temp) == 0 &&
         compareLastName(*currHead->getStudent(), temp) == 0 &&
         head != nullptr) {
    head = head->getLink();
    delete currHead;
    currHead = head;
    currHead = currHead->getLink();
  }

  while (currHead != nullptr) {
    if (compareFirstName(*currHead->getStudent(), temp) == 0 &&
        compareLastName(*currHead->getStudent(), temp) == 0) {
      StudentNodePtr<T> temp = currHead;
      currHead = currHead->getLink();
      deleteStudentNode(temp);
      found = true;
    } else {
      currHead = currHead->getLink();
    }
  }
  return found;
}

// Delete the head and tail of the list
template <typename T>
bool StudentList<T>::deleteHeadTail() {
  if (head == nullptr)
    return false;
  else {
    deleteStudentNode(head);
    deleteStudentNode(tail);
  }
  return true;
}
#endif
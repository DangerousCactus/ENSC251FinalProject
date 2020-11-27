#ifndef STUDENTLIST_CPP
#define STUDENTLIST_CPP
#include "StudentList.hpp"
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
  return *this;
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

template <typename T>
bool StudentList<T>::isEmpty() {
  return head == nullptr;
}

// Allocate memory for the student and then place the student into the list
template <typename T>
void StudentList<T>::addStudentNode(T student) {
  T* newStudent;

  try {
    newStudent = new T(student);
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
    exit(-1);
  }

  addStudentNode(newStudent);
}

// Takes a pointer to a student and places it into the list while maintaining a
// sorted order
template <typename T>
void StudentList<T>::addStudentNode(T* student) {
  StudentNodePtr<T> newNode;

  try {  // Create the studentNode
    newNode = new StudentNode<T>(student);
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
    exit(-1);
  }
  placeNodeInList(newNode);
}

template <typename T>
void StudentList<T>::addStudentNode(StudentNode<T> studentNode) {
  StudentNodePtr<T> newNode;

  try {  // Create the studentNode
    newNode = new StudentNode<T>(studentNode);
  } catch (std::bad_alloc) {
    std::cerr << "ERROR: Unable to allocate memory. Exiting program.\n";
    exit(-1);
  }

  placeNodeInList(newNode);
}

template <typename T>
void StudentList<T>::placeNodeInList(StudentNodePtr<T> studentNode) {
  StudentNodePtr<T> currParent = head;
  if (currParent == nullptr) {  // If the list is empty
    head = studentNode;
    tail = studentNode;
    return;
  } else {  // Sort in non-increasing order
    while (!(*currParent->getStudent() < *studentNode->getStudent())) {
      if (currParent->getLink() == nullptr) {  // If we've reached the end
        currParent->setLink(studentNode);
        tail = studentNode;
        return;
      } else {
        currParent = currParent->getLink();
      }
    }

    // Place the node into the list
    T* temp = studentNode->getStudent();
    studentNode->setStudent(currParent->getStudent());
    currParent->setStudent(temp);
    studentNode->setLink(currParent->getLink());
    currParent->setLink(studentNode);

    // If we just added to the end of the list, update the tail
    if (studentNode->getLink() == nullptr)
      tail = studentNode;

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
}

// The following functions search the list based on various criteria

template <typename T>
StudentList<T> StudentList<T>::searchAppID(int id) const {
  StudentList<T> output;
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getApplicationID() == id) {
      output.addStudentNode(*currHead->getStudent());
      found = true;
    }
    currHead = currHead->getLink();
  }

  return output;
}

template <typename T>
StudentList<T> StudentList<T>::searchCGPA(float cgpa) const {
  StudentList<T> output;
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getCGPA() == cgpa) {
      output.addStudentNode(*currHead->getStudent());
      found = true;
    }
    currHead = currHead->getLink();
  }

  return output;
}

template <typename T>
StudentList<T> StudentList<T>::searchResearchScore(int score) const {
  StudentList<T> output;
  StudentNodePtr<T> currHead = head;
  bool found = false;
  while (currHead != nullptr) {
    if (currHead->getStudent()->getResearchScore() == score) {
      output.addStudentNode(*currHead->getStudent());
      found = true;
    }
    currHead = currHead->getLink();
  }

  return output;
}

template <typename T>
StudentList<T> StudentList<T>::searchFirstLast(std::string first,
                                               std::string last) const {
  StudentList<T> output;
  StudentNodePtr<T> currHead = head;
  bool found = false;
  T temp;
  temp.setFirstName(first);
  temp.setLastName(last);

  while (currHead != nullptr) {
    if (compareFirstName(*currHead->getStudent(), temp) == 0 &&
        compareLastName(*currHead->getStudent(), temp) == 0) {
      output.addStudentNode(*currHead->getStudent());
      found = true;
    }
    currHead = currHead->getLink();
  }

  return output;
}

// Print out all students that meet the CGPA and Research Score threshold
template <typename T>
StudentList<T> StudentList<T>::searchCGPAandResearchScoreThreshold(
    float CGPA, int score) const {
  StudentList<T> output;
  StudentNodePtr<T> currHead = head;
  bool found = false;

  while (currHead != nullptr) {
    if (currHead->getStudent()->getCGPA() >= CGPA &&
        currHead->getStudent()->getResearchScore() >= score) {
      output.addStudentNode(StudentNode<T>(*currHead));
      found = true;
    }
    currHead = currHead->getLink();
  }

  return output;
}

// Delete all objects in the list which have the specified first and last name
template <typename T>
void StudentList<T>::deleteFirstLast(std::string first, std::string last) {
  StudentNodePtr<T> currHead = head;
  bool found = false;
  T temp;
  temp.setFirstName(StringHelper::toUpper(first));
  temp.setLastName(StringHelper::toUpper(last));

  while (currHead != nullptr) {
    if (compareFirstName(*(currHead->getStudent()), temp) == 0 &&
        compareLastName(*(currHead->getStudent()), temp) == 0) {
      StudentNodePtr<T> temp = currHead;
      currHead = currHead->getLink();
      deleteStudentNode(temp);
      found = true;
    } else {
      currHead = currHead->getLink();
    }
  }
  if (!found)
    std::cout << "No matching records found.\n";
}

// Delete the head and tail of the list
template <typename T>
void StudentList<T>::deleteHeadTail() {
  deleteStudentNode(head);
  deleteStudentNode(tail);
}
#endif
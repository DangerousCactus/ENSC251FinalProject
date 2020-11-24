#ifndef STUDENTNODE_HPP
#define STUDENTNODE_HPP

template <typename T>
class StudentNode {
 private:  // The node stores a link to a student, and the next node
  T* student;
  StudentNode* link = nullptr;

 public:
  StudentNode();
  // Construct a new node by giving it a pointer to a student
  StudentNode(T* student);

  // Dynamic big three since we have dynamic member variables
  StudentNode(const StudentNode& studentNode);
  StudentNode& operator=(const StudentNode studentNode);
  ~StudentNode();

  StudentNode* getLink() const;
  T* getStudent() const;

  void setLink(StudentNode* link);
  void setStudent(T* student);
};
#include "StudentNode.cpp"
#endif
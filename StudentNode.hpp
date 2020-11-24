#ifndef STUDENTNODE_HPP
#define STUDENTNODE_HPP

template <typename T>
class StudentNode {
 private:
  T* student;
  StudentNode* link = nullptr;

 public:
  StudentNode();
  StudentNode(T* student);

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
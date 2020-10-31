#include <gtest/gtest.h>
#include "../domesticStudent.cpp"
#include "../internationalStudent.cpp"
#include "../student.cpp"

TEST(studentTest, studentGettersSetters) {
  Student student("Bob", "Builder", 2.0, 95, 0);
  EXPECT_EQ(student.getFirstName(), "Bob");
  EXPECT_EQ(student.getLastName(), "Builder");
  EXPECT_FLOAT_EQ(student.getcgpa(), 2.0);
  EXPECT_EQ(student.getResearchScore(), 95);
  EXPECT_EQ(student.getApplicationID(), 0);

  student.setFirstName("First");
  student.setLastName("Last");
  student.setcgpa(3.2);
  student.setResearchScore(90);
  student.setApplicationID(100);

  EXPECT_EQ(student.getFirstName(), "First");
  EXPECT_EQ(student.getLastName(), "Last");
  EXPECT_FLOAT_EQ(student.getcgpa(), 3.2);
  EXPECT_EQ(student.getResearchScore(), 90);
  EXPECT_EQ(student.getApplicationID(), 100);
}

TEST(studentTest, domesticStudentGettersSetters) {
  DomesticStudent dstudent("Bob", "Builder", 2.0, 95, 0, "Ontario");
  EXPECT_EQ(dstudent.getProvince(), "Ontario");

  dstudent.setProvince("British Columbia");
  EXPECT_EQ(dstudent.getProvince(), "British Columbia");
}

TEST(studentTest, internationalTOEFLStudentGettersSetters) {
  ToeflScore t(10, 20, 25, 23);
  InternationalStudent istudent("Bob", "Builder", 2.0, 95, 0, "North Korea", t);

  EXPECT_EQ(istudent.getCountry(), "North Korea");
  EXPECT_EQ(istudent.getToefl().getReading(), 10);
  EXPECT_EQ(istudent.getToefl().getlistening(), 20);
  EXPECT_EQ(istudent.getToefl().getSpeaking(), 25);
  EXPECT_EQ(istudent.getToefl().getWriting(), 23);
  EXPECT_EQ(istudent.getToefl().getTotal(), 78);

  istudent.setCountry("France");
  t.setReading(11);
  t.setlistening(21);
  t.setSpeaking(22);
  t.setWriting(5);
  istudent.setToefl(t);

  EXPECT_EQ(istudent.getCountry(), "France");
  EXPECT_EQ(istudent.getToefl().getReading(), 11);
  EXPECT_EQ(istudent.getToefl().getlistening(), 21);
  EXPECT_EQ(istudent.getToefl().getSpeaking(), 22);
  EXPECT_EQ(istudent.getToefl().getWriting(), 5);
  EXPECT_EQ(istudent.getToefl().getTotal(), 59);
}

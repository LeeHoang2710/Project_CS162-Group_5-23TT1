#pragma once
#include "struct_and_library.h"

Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass, string p_class);
StudentNode* initStudentNode(Student new_student);
void addNewStudentNode(StudentNode*& head, Student new_student);
void removeStudentNode(StudentNode*& head, Student student_1);
StudentNode* searchStudentNode(StudentNode* head, string student_1_id);
void readStudentFromFile(ifstream& file, StudentNode*& list_student);
void exportStudentToFile(ofstream& file, StudentNode*& list_student);
ClassNode* searchClass(ClassNode* allClass, string class_id);

#include "../struct and function/struct_and_library.h"

Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_class);
StudentNode* initStudentNode(Student new_student);
void addNewStudentNode(StudentNode*& head, Student new_student);
void removeStudentNode(StudentNode*& head, Student student_1);
void displayStudent(StudentNode* StuHead);
StudentNode* searchStudentNode(StudentNode* head, string student_1_id);
void readStudentFromFile(ifstream& file, string filename, StudentNode*& liststu);
bool readStudentFromTerminal(StudentNode*& liststu);
void exportStudentToFile(ofstream& file, StudentNode*& list_student);
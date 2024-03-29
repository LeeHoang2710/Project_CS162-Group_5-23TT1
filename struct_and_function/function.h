#include "struct_and_library.h"

// Login Session
void StorePassWordStudent(StudentNode *&StuPass, ifstream &ip, string file); // These 2 functions will load password file to a linked list
void StorePassWordStaff(StaffNode *&StaffPass, ifstream &ip, string file);
bool LoginForStudent(StudentNode *StuList, string &username, string &pass); // 1st parameter is the linked list, 2nd parameter is the ID of student who is onl
bool LoginForStaff(StaffNode *StaffPass, string &username, string &pass);   // 3rd parameter is the node store the current id, used it only for changing password
void UpdateStuPassFile(StudentNode *List, ofstream &op);                    // Update the password file when someone change password;
void UpdateStaffPassFile(StaffNode *List, ofstream &op);
bool ChangePassStudent(StudentNode *current); // get the node of user who is online and change password in it;
bool ChangePassStaff(StaffNode *current);

Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass, string p_class);
StudentNode *initStudentNode(Student new_student);
void addNewStudentNode(StudentNode *&head, Student new_student);
void removeStudentNode(StudentNode *&head, Student student_1);
StudentNode *searchStudentNode(StudentNode *head, string student_1_id);
void readStudentFromFile(ifstream &file, StudentNode *&list_student);
void exportStudentToFile(ofstream &file, StudentNode *&list_student);

Year createYear(string p_year_id);
YearNode *initYearNode(Year school_year);
void addNewYearNode(YearNode *&head, Year year);
void removeNewYearNode(YearNode *&head, Year year);
YearNode *searchYearNode(YearNode *head, string year);
void importYear(YearNode *&year_list, string filename, ifstream &fin);
void exportYear(YearNode *year_list, string filename, ofstream &fout);
void deleteYearList(YearNode *&year_list);

Semester createSemester(const string &sem_id, const string &start_date, const string &end_date);
SemesterNode *createSemesterNode(const Semester &new_sem);
void appendSemesterNode(SemesterNode *&sem_list, Semester new_sem);
void importSemester(SemesterNode *&sem_list, istringstream &is);
void exportSemesterInYear(SemesterNode *sem_list, ofstream &fout);
void deleteSemesterList(SemesterNode *&sem_list);

Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, Session teaching_session);
CourseNode *initCourseNode(Course new_course, StudentNode *liststu);
void addNewCourseNode(CourseNode *&head, Course cs, StudentNode *liststu);
void deletecourse(CourseNode *CourseHead, string delCourse);

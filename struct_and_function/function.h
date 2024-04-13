#include "struct_and_library.h"

// Login Session
void StorePassWordStudent(StudentNode *&StuPass, ifstream &ip, string file);
void StorePassWordStaff(StaffNode *&StaffPass, ifstream &ip, string file);
bool LoginForStudent(StudentNode *StuList, string &username, string &pass);
bool LoginForStaff(StaffNode *StaffPass, string &username, string &pass);
void UpdateStuPassFile(StudentNode *List, ofstream &op);
void UpdateStaffPassFile(StaffNode *List, ofstream &op);
bool ChangePassStudent(StudentNode *current);
bool ChangePassStaff(StaffNode *current);

// Student
Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass, string p_class);
StudentNode *initStudentNode(Student new_student);
void addNewStudentNode(StudentNode *&head, Student new_student);
bool removeStudentNode(StudentNode *&head, string studentId);
StudentNode *searchStudentNode(StudentNode *head, string student_1_id);
void readStudentFromFile(ifstream &file, StudentNode *&list_student);
void exportStudentToFile(ofstream &file, StudentNode *&list_student);

// Year
Year createYear(string p_year_id, ClassNode *allclass);
YearNode *initYearNode(Year school_year);
void addNewYearNode(YearNode *&head, Year year);
void removeNewYearNode(YearNode *&head, Year year);
YearNode *searchYearNode(YearNode *head, string year);
void importYear(YearNode *&year_list, string filename, ifstream &fin);
void exportYear(YearNode *&year_list, string filename, ofstream &fout);
void deleteYearList(YearNode *&year_list);

// Semester
Semester createSemester(const string &sem_id, const string &start_date, const string &end_date);
SemesterNode *createSemesterNode(const Semester &new_sem);
void appendSemesterNode(SemesterNode *&sem_list, Semester new_sem);
void importSemester(SemesterNode *&sem_list, stringstream &is, ifstream &fin);
void exportSemesterInYear(SemesterNode *&sem_list, ofstream &fout);
void deleteSemesterList(SemesterNode *&sem_list);

// Course
Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, Session teaching_session);
CourseNode *initCourseNode(Course new_course);
// void addNewCourseNode(CourseNode *&head, Course cs, StudentNode *liststu);
void appendNewCourseNode(CourseNode *&head, Course cs);
bool deleteCourse(CourseNode *&CourseHead, string delCourse);
void importCourse(CourseNode *&Courselist, ifstream &fin);
void exportCourse(CourseNode *&Courselist, ofstream &fout);
void compareCourse(Course &old, Course &newone);
void replaceCourse(CourseNode *&curr, Course newone);
CourseNode *findCourse(CourseNode *head, string input);

// Class
Class CreateClass(string classid);
ClassNode *InitializeClassNode(Class newclass);
void AddClassNode(ClassNode *&head, Class newclass);
void DeleteClassNode(ClassNode *&head, Class del_class);
ClassNode *SearchClassNode(ClassNode *&head, string searchclass);
void AddStudent(ClassNode *&head, string classid, StudentNode *newstudent);
void ReadClassfromfile(ClassNode *&Listclass, string file_name, ifstream &fin);
void ExportClassTFile(ClassNode *&Listclass, string file_name, ofstream &fout);
ClassNode *findClass(ClassNode *head, string input);
void importClass(ClassNode *&classes, stringstream &ss, ifstream &fin);
void exportClass(ClassNode *class_list, ofstream &fout);
bool ReadClassFile(ClassNode *&Listclass, string file_name, ifstream &fin);

// Results
void Loadcoursescorefromfile(ifstream &fin, StudentNode *&Studentlist);
float updateTotalGpa(StudentNode *studentNode);
void Exportallscoretofile(ofstream &fout, StudentNode *&Studentlist);
Results createResults(const string& course_id, const string& sem_id, const string& year_id, float process, float midterm, float final);
ResultsNode* createResultsNode(const Results& results);
void appendResultsNode(ResultsNode*& results_list, ResultsNode* resultsNode);
float updateTotalGpa(StudentNode* studentNode);

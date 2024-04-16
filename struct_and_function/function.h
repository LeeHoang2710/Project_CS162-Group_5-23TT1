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

// Staff
Staff createStaff(string p_staff_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass);
StaffNode *initStaffNode(Staff new_staff);
void addNewStaffNode(StaffNode *&head, Staff new_staff);
void importStaff(StaffNode *&Staff_list, ifstream &ip, string filename);
StaffNode *searchStaffNode(StaffNode *head, string staff_1_id);
void ExportStaff(StaffNode *&Staff_list, ofstream &op, string filename);

// Student
Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass, string p_class);
StudentNode *initStudentNode(Student new_student);
void addNewStudentNode(StudentNode *&head, Student new_student);
bool removeStudentNode(StudentNode *&head, string studentId);
StudentNode *searchStudentNode(StudentNode *head, string student_1_id);
void readStudentFromFile(ifstream &file, StudentNode *&list_student);
void exportStudentToFile(ofstream &file, StudentNode *list_student);
bool importNewStudentsFromStaff(ClassNode*& classNode, string file_name, ifstream& fin);

// Year
Year createYear(string p_year_id, ClassSubNode* classSublist);
YearNode *initYearNode(Year school_year);
void addNewYearNode(YearNode *&head, Year year);
void removeNewYearNode(YearNode *&head, Year year);
YearNode *searchYearNode(YearNode *head, string year);
//void importYear(YearNode *&year_list, string filename, ifstream &fin);
//void exportYear(YearNode *&year_list, string filename, ofstream &fout);
void deleteYearList(YearNode *&year_list);

// Semester
Semester createSemester(const string &sem_id, const string &start_date, const string &end_date);
SemesterNode *createSemesterNode(const Semester &new_sem);
void appendSemesterNode(SemesterNode *&sem_list, Semester new_sem);
bool importSemester(ClassNode* allClass, SemesterNode*& sem_list, stringstream& is, ifstream& fin);
void exportSemesterInYear(SemesterNode *&sem_list, ofstream &fout);
void deleteSemesterList(SemesterNode *&sem_list);

// Course
Course createCourse(string course_id, string course_name, string teacher_name, int num_credit, int max_students, Session teaching_session, string class_id, ClassNode* class_list);
CourseNode *initCourseNode(Course new_course);
// void addNewCourseNode(CourseNode *&head, Course cs, StudentNode *liststu);
void appendNewCourseNode(CourseNode *&head, Course cs);
bool deleteCourse(CourseNode *&CourseHead, string delCourse);
bool importCourse(ClassNode* allClass, CourseNode*& Courselist, ifstream& fin);
void exportCourse(CourseNode *&Courselist, ofstream &fout);
void compareCourse(Course &old, Course &newone);
void replaceCourse(CourseNode*& curr, Course newOne, string year_id, string sem_id);
CourseNode *findCourse(CourseNode *head, string input);

// Class
Class CreateClass(string classid);
ClassNode *InitializeClassNode(Class newclass);
void AddClassNode(ClassNode*& head, ClassNode* newclassnode);
void DeleteClassNode(ClassNode *&head, Class del_class);
//ClassNode *SearchClassNode(ClassNode *&head, string searchclass);
//void AddStudent(ClassNode *&head, string classid, StudentNode *newstudent);
void ReadClassfromfile(ClassNode *&Listclass, string file_name, ifstream &fin);
void ExportClassTFile(ClassNode *Listclass, string file_name, ofstream &fout);
ClassSubNode *findClasses(ClassNode *head, string input);
//void importClass(ClassNode *&classes, stringstream &ss, ifstream &fin);
//void exportClass(ClassNode *class_list, ofstream &fout);
bool importNewClassesFromStaff(YearNode* currYearNode, ClassNode*& Listclass, string file_name, ifstream& fin);

// Results
bool importResults(ifstream &fin, ClassNode *&MainClass, string filename);
float updateTotalGpa(StudentNode *studentNode);
void Exportallscoretofile(ofstream& fout, string filename, ClassNode* allClass);
Results createResults(const string &course_id, const string &sem_id, const string &year_id, float process, float midterm, float final);
ResultsNode *createResultsNode(const Results &results);
void appendResultsNode(ResultsNode *&results_list, ResultsNode *resultsNode);
float updateTotalGpa(StudentNode *studentNode);
ResultsNode* searchResultsNode(ResultsNode* results_list, string course_id, string year_id, string sem_id);
void updateCourseIdForClass(ClassNode*& classNode, string old_course_id, string new_course_id, string year_id, string sem_id);
bool UpdateResults(ifstream& fin, string filename, string yr, string sem, Course& curr);

//Class helper
bool importYear(YearNode*& year_list, ClassNode* allClass, string filename, ifstream& fin);
bool exportYear(YearNode*& year_list, string filename, ofstream& fout);
ClassSubNode* createClassSubNode(ClassNode* classNode);
void appendClassSubNode(ClassSubNode*& classSublist, ClassSubNode* classSubNode);
void addResultsNodeToClass(ClassNode*& classNode, const string& year_id, const string& sem_id, const string& course_id);
ClassNode* searchClassNode(ClassNode* allClass, string class_id);
bool importClassSubNode(ClassNode* allClass, Year& year, stringstream& ss);
void exportClassSubNode(ClassSubNode* classSublist, ofstream& fout);

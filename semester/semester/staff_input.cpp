#include "../staff_input.h"

bool importClassFromStaff(ifstream& fin, const string& filename, ClassNode*& class_list)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open file " << filename << " to get class information." << endl;
        return false;
    }

    string class_id;
    getline(fin, class_id);
    Class newClass = CreateClass(class_id);

    readStudentFromFile(fin, newClass.student_list);
    AddClassNode(class_list, newClass);

    fin.close();
    return true;
}

bool importResultsFromStaff(ifstream& fin, const string& filename, CourseNode* courseNode)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open file " << filename << " to " << endl;
		return false;
    }

    importResultsInCourse(fin, courseNode);

    fin.close();
    return true;
}

bool importResultsInCourse(ifstream& fin, CourseNode* courseNode)
{
    string line;
    while (getline(fin, line))
    {
        istringstream iss(line);
        string student_id, process, midterm, final;
        getline(iss, student_id, ',');
        getline(iss, process, ',');
        getline(iss, midterm, ',');
        getline(iss, final, ',');
        StudentNode* studentNode = searchStudentNode(courseNode->course.main_class->my_class.student_list, student_id);
        updateScore(studentNode->student.results_list->results.score, stof(process), stof(midterm), stof(final));
        updateCurrentSemGpa(studentNode);
        updateTotalGpa(studentNode);
    }
}

// add main_class to course
// add new ResultNode to each student in class
bool importCoursesFromStaff(ifstream& fin, const string& filename, YearNode* year_list, YearNode* yearNode, SemesterNode* semNode)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open file " << filename << " to get course information." << endl;
        return false;
    }

    if (!yearNode || !semNode)
    {
		cout << "Year or semester is not exist." << endl;
		return false;
	}

    string year_id, sem_id;
    getline(fin, year_id);
    getline(fin, sem_id);

    if (year_id != yearNode->school_year.year_id)
    {
        cout << "Year id does not match." << endl;
        return false;
    }

    if (sem_id != semNode->sem.semester_id)
    {
        cout << "Semester id does not match." << endl;
        return false;
    }

    bool check = importCourses(fin, year_list, semNode->sem.course_list, year_id, sem_id);
    if (!check)
    {
		cout << "Error when importing courses." << endl;
		return false;
	}

    fin.close();
    return true;
}

bool importCourses(ifstream& fin, YearNode* year_list, CourseNode*& course_list, const string& year_id, const string& sem_id)
{
    string number;
    while (getline(fin, number))
    {
        Course cs;
        if (number == "*")
            return;
        stringstream line(number);
        getline(line, cs.course_id, ',');
        getline(line, cs.course_name, ',');
        getline(line, cs.teacher_name, ',');
        getline(line, number, ',');
        cs.num_credit = stoi(number);
        getline(line, number, ',');
        cs.max_students = stoi(number);
        getline(line, number, ',');
        cs.teaching_session.day_of_the_week = stoi(number);
        getline(line, number, ',');
        cs.teaching_session.session_no = stoi(number);
        getline(line, number, '\n');
        cs.main_class = searchClassNodeFromAllYears(year_list, number);
        if (!cs.main_class)
        {
			cout << "Cannot find class " << number << endl;
			return false;
		}

        appendNewCourseNode(course_list, cs);
        addResultsNodeToClass(cs.main_class, year_id, sem_id, cs.course_id);
    }

    return true;
}

ClassNode* searchClassNodeFromAllYears(YearNode* year_list, const string& class_id)
{
    YearNode* currYear = year_list;
    while (currYear)
    {
        ClassNode* currClass = findClass(currYear->school_year.allclass, class_id);
        if (currClass)
            return currClass;
        currYear = currYear->next;
    }
    return nullptr;
}
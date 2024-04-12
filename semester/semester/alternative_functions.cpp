#include "../alternative_functions.h"

// Function to import courses from a file
void importCourses(CourseNode*& course_list, ifstream& fin)
{
    string course_id, course_name, teacher_name, number;
    int num_credit, max_students, day_of_the_week, session_no;

    while (getline(fin, course_id, ','))
    {
        getline(fin, course_name, ',');
        getline(fin, teacher_name, ',');
        getline(fin, number, ',');
        num_credit = stoi(number);
        getline(fin, number, ',');
        max_students = stoi(number);
        getline(fin, number, ',');
        day_of_the_week = stoi(number);
        getline(fin, number);
        session_no = stoi(number);

        Session session = createSession(day_of_the_week, session_no);

        Course cs = createCourse(course_id, course_name, teacher_name, num_credit, max_students, day_of_the_week, session_no);
        appendCourseNode(course_list, cs);
    }
}

// Function to export school year and semester information to a file
void exportYear(YearNode* year_list, const string& filename, ofstream& fout)
{
    fout.open(filename);
    if (!fout.is_open())
    {
        cout << "Cannot open " << filename << " to export school year and semester information." << endl;
        fout.close();
        return;
    }

    YearNode* current_year = year_list;
    while (current_year)
    {
        fout << current_year->school_year.year_id << endl;
        exportSemester(current_year->school_year.list_sem, fout);
        current_year = current_year->next;
        if (current_year)
            fout << "*" << endl;
    }

    fout.close();
}

// Function to export a semester to a file
void exportSemester(SemesterNode* sem_list, ofstream& fout)
{
    while (sem_list)
    {
        fout << sem_list->sem.semester_id << ","
             << sem_list->sem.start_date << ","
             << sem_list->sem.end_date << endl;
        sem_list = sem_list->next;
    }
}

// Function to import courses in a semester from a file
void importCourseInSem(CourseNode*& course_list, ifstream& fin, const string& semester_id, const string& year_id)
{
    string number;
    while (getline(fin, number))
    {
        Course cs;

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
        getline(line, number, '\n');
        cs.teaching_session.session_no = stoi(number);

        appendCourseNode(course_list, cs, semester_id, year_id);
    }
}

// Function to append a course node to the course list
void appendCourseNode(CourseNode*& head, Course cs, const string& semester_id, const string& year_id)
{
    CourseNode* new_course_node = initCourseNode(cs);
    new_course_node->semester_id = semester_id;
    new_course_node->year_id = year_id;
    if (!head)
        head = new_course_node;
    else
    {
        CourseNode* list_course = head;
        while (list_course->next)
            list_course = list_course->next;
        list_course->next = new_course_node;
    }
}
#include "../alternative_functions.h"

// Function to import school year and semester information from a file
void importYear(YearNode*& year_list, const string& filename, ifstream& fin)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open " << filename << " to import school year and semester information." << endl;
        return;
    }

    string line;
    while (getline(fin, line))
    {
        // Skip empty lines or lines starting with "//"
        if (line.empty() || line == "//")
            continue;

        // Check if the line indicates a new semester
        if (line.find("Semester") != string::npos)
        {
            string semester_id, start_date, end_date;
            getline(fin, semester_id);
            getline(fin, start_date, ',');
            getline(fin, end_date);

            // Create a new Semester
            Semester new_sem = createSemester(semester_id, start_date, end_date);
            // Import courses in the semester
            importCourseInSem(new_sem.course_list, fin, new_sem.semester_id, "");
            // Append the new Semester to the sem_list
            appendSemesterNode(year_list->school_year.list_sem, createSemesterNode(new_sem));
        }
        // Check if the line indicates importing courses
        else if (line.find("*") != string::npos)
        {
            // Import courses in the current semester
            importCourses(year_list->school_year.list_sem->sem.course_list, fin);
        }
    }

    fin.close();
}

// Function to import courses from a file
void importCourses(CourseNode*& course_list, ifstream& fin)
{
    string course_id, course_name, teacher_name, number;
    int num_credit, max_students, day_of_the_week, session_no;

    while (getline(fin, course_id, ','))
    {
        getline(fin, course_name, ',');
        getline(fin, teacher_name, ',');
        getline(fin, number, ',');
        num_credit = stoi(number);
        getline(fin, number, ',');
        max_students = stoi(number);
        getline(fin, number, ',');
        day_of_the_week = stoi(number);
        getline(fin, number);
        session_no = stoi(number);

        // Create a new Course
        Course cs = createCourse(course_id, course_name, teacher_name, num_credit, max_students, day_of_the_week, session_no);
        // Append the new Course to the course_list
        appendCourseNode(course_list, cs);
    }
}

// Function to export school year and semester information to a file
void exportYear(YearNode* year_list, const string& filename, ofstream& fout)
{
    fout.open(filename);
    if (!fout.is_open())
    {
        cout << "Cannot open " << filename << " to export school year and semester information." << endl;
        fout.close();
        return;
    }

    YearNode* current_year = year_list;
    while (current_year)
    {
        fout << current_year->school_year.year_id << endl;
        exportSemester(current_year->school_year.list_sem, fout);
        current_year = current_year->next;
        if (current_year)
            fout << "*" << endl;
    }

    fout.close();
}

// Function to export a semester to a file
void exportSemester(SemesterNode* sem_list, ofstream& fout)
{
    while (sem_list)
    {
        fout << sem_list->sem.semester_id << ","
             << sem_list->sem.start_date << ","
             << sem_list->sem.end_date << endl;
        sem_list = sem_list->next;
    }
}

// Function to import courses in a semester from a file
void importCourseInSem(CourseNode*& course_list, ifstream& fin, const string& semester_id, const string& year_id)
{
    string number;
    while (getline(fin, number))
    {
        Course cs;

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
        getline(line, number, '\n');
        cs.teaching_session.session_no = stoi(number);

        // Append the new Course to the course_list
        appendCourseNode(course_list, cs, semester_id, year_id);
    }
}

// Function to append a course node to the course list
void appendCourseNode(CourseNode*& head, Course cs, const string& semester_id, const string& year_id)
{
    CourseNode* new_course_node = initCourseNode(cs);
    new_course_node->semester_id = semester_id;
    new_course_node->year_id = year_id;
    if (!head)
        head = new_course_node;
    else
    {
        CourseNode* list_course = head;
        while (list_course->next)
            list_course = list_course->next;
        list_course->next = new_course_node;
    }
}

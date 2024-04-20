#include "../include/function.h"

Student createStudent(string student_id, string first, string last, bool gender, string dob, string social_id, string pass)
{
    Student person;
    person.student_id = student_id;
    person.first_name = first;
    person.last_name = last;
    person.gender = gender;
    person.dob = dob;
    person.social_id = social_id;
    if (!pass.empty())
        person.password = pass;

    return person;
}

StudentNode *initStudentNode(Student new_student)
{
    StudentNode *new_student_node = new StudentNode;
    new_student_node->next = nullptr;
    new_student_node->student = new_student;
    return new_student_node;
}

void addNewStudentNode(StudentNode *&head, Student new_student)
{
    StudentNode *new_student_node = initStudentNode(new_student);
    if (!head)
    {
        head = new_student_node;
        head->student.num = 1;
    }
    else
    {
        StudentNode *list_Student = head;
        while (list_Student->next)
            list_Student = list_Student->next;

        new_student_node->student.num = list_Student->student.num + 1;
        list_Student->next = new_student_node;
    }
}

StudentNode *searchStudentNode(ClassNode *allClass, string studentId)
{
    for (ClassNode *tmp = allClass; tmp != nullptr; tmp = tmp->next)
    {
        StudentNode *student = searchStudentNodeInOneClass(tmp->my_class.student_list, studentId);
        if (student != nullptr)
            return student;
    }

    return nullptr;
}

StudentNode *searchStudentNodeInOneClass(StudentNode *head, string student_id)
{
    while (head)
    {
        if (head->student.student_id == student_id)
            return head;

        head = head->next;
    }

    return nullptr;
}

void readStudentFromFile(ifstream &file, StudentNode *&list_student)
{
    string line;
    while (getline(file, line))
    {
        if (line == "*")
            return;

        stringstream ss(line);
        string stu_id, first, last, gender, dob, social_id, password;
        getline(ss, stu_id, ',');
        getline(ss, first, ',');
        getline(ss, last, ',');
        getline(ss, gender, ',');
        getline(ss, dob, ',');
        getline(ss, social_id, ',');
        getline(ss, password, ',');

        addNewStudentNode(list_student, createStudent(stu_id, first, last, stoi(gender), dob, social_id, password));
    }
}

void exportStudentToFile(ofstream &file, StudentNode *list_student)
{
    if (!list_student)
        file << "*" << endl;
    else
    {
        while (list_student)
        {
            Student person = list_student->student;
            file << person.student_id << ","
                 << person.first_name << ","
                 << person.last_name << ","
                 << person.gender << ","
                 << person.dob << ","
                 << person.social_id << ","
                 << person.password << endl;
            list_student = list_student->next;
        }

        file << "*" << endl;
    }
}

bool importNewStudentsFromStaff(ClassNode *&classNode, string file_name, ifstream &fin)
{
    fin.open(file_name);
    if (!fin.is_open())
    {
        cout << "Cannot open " << file_name << endl;
        return false;
    }

    string line;
    getline(fin, line);
    if (classNode->my_class.class_id != line)
    {
        cout << "Class id " << line << " does not match with " << classNode->my_class.class_id << endl;
        return false;
    }

    readStudentFromFile(fin, classNode->my_class.student_list);
    fin.close();
    return true;
}

void updateStudentsNumBeforeRemoval(StudentNode *studentNodeToDelete)
{
    StudentNode *temp = studentNodeToDelete->next;
    while (temp)
    {
        --(temp->student.num);
        temp = temp->next;
    }
}

bool removeStudentNode(StudentNode *&head, string studentId)
{
    StudentNode *studentNodeToDelete = searchStudentNodeInOneClass(head, studentId);
    if (!studentNodeToDelete)
    {
        cout << "Student " << studentId << " does not exist." << endl;
        return false;
    }

    updateStudentsNumBeforeRemoval(studentNodeToDelete);
    if (head == studentNodeToDelete)
        head = head->next;
    else
    {
        StudentNode *temp = head;
        while (temp->next != studentNodeToDelete)
            temp = temp->next;

        temp->next = studentNodeToDelete->next;
    }

    delete studentNodeToDelete;
    return true;
}

void deleteStudentList(StudentNode *&studentList)
{
    while (studentList)
    {
        StudentNode *temp = studentList;
        deleteResultsList(temp->student.results_list);
        studentList = studentList->next;
        delete temp;
    }
}

// StudentSubNode
StudentSubNode *createStudentSubNode(StudentNode *studentNode)
{
    return new StudentSubNode{studentNode, nullptr};
}

void appendStudentSubNode(StudentSubNode *&studentSubList, StudentSubNode *studentSubNode)
{
    if (!studentSubList)
        studentSubList = studentSubNode;
    else
    {
        StudentSubNode *temp = studentSubList;
        while (temp->next)
            temp = temp->next;

        temp->next = studentSubNode;
    }
}

// Add one extra student to a course
bool addStudentSubNodeToCourse(ClassNode *allClass, CourseNode *&courseNode, string student_id, string year_id, string sem_id)
{
    StudentNode *studentNode = searchStudentNode(allClass, student_id);
    if (!studentNode)
    {
        cout << "Student " << student_id << " does not exist." << endl;
        return false;
    }
    else
    {
        StudentNode *temp = searchStudentNodeInOneClass(courseNode->course.main_class->my_class.student_list, student_id);
        if (temp == studentNode)
        {
            cout << "Student " << student_id << " already exists in course's main class " << courseNode->course.main_class->my_class.class_id << courseNode->course.course_id << endl;
            return false;
        }
    }

    StudentSubNode *studentSubNode = createStudentSubNode(studentNode);
    appendStudentSubNode(courseNode->course.extra_stu, studentSubNode);

    Results results = createResults(courseNode->course.course_id, sem_id, year_id);
    appendResultsNode(studentNode->student.results_list, createResultsNode(results));
    return true;
}

StudentSubNode *searchStudentSubNode(StudentSubNode *studentSubList, string student_id)
{
    StudentSubNode *temp = studentSubList;
    while (temp)
    {
        if (temp->student_node->student.student_id == student_id)
            return temp;

        temp = temp->next;
    }

    cout << "StudentSubNode " << student_id << " does not exist here." << endl;
    return nullptr;
}

// Remove one extra student from a course
bool deleteStudentSubNode(StudentSubNode *&studentSubList, string student_id, string course_id, string year_id, string sem_id)
{
    StudentSubNode *nodeToDelete = searchStudentSubNode(studentSubList, student_id);
    if (nodeToDelete)
    {
        if (studentSubList == nodeToDelete)
            studentSubList = studentSubList->next;
        else
        {
            StudentSubNode *temp = studentSubList;
            while (temp->next != nodeToDelete)
                temp = temp->next;

            temp->next = nodeToDelete->next;
        }

        deleteResultsNode(nodeToDelete->student_node->student.results_list, course_id, year_id, sem_id);
        delete nodeToDelete;
        return true;
    }

    return false;
}

// Delete all extra students before deleting a course
void deleteAllExtraStudents(StudentSubNode *&studentSubList, string course_id, string year_id, string sem_id)
{
    StudentSubNode *temp = studentSubList;
    while (studentSubList)
    {
        StudentSubNode *temp = studentSubList;
        deleteResultsNode(temp->student_node->student.results_list, course_id, year_id, sem_id);
        delete temp;
        studentSubList = studentSubList->next;
    }
}

#include "../struct_and_function/function.h"

Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass)
{
    Student person;
    person.num = p_num;
    person.student_id = p_student_id;
    person.first_name = p_first;
    person.last_name = p_last;
    person.gender = p_gender;
    person.dob = p_dob;
    person.social_id = p_social_id;
    if (!p_pass.empty())
        person.password = p_pass;

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
        head = new_student_node;
    else
    {
        StudentNode *list_Student = head;
        while (list_Student->next)
            list_Student = list_Student->next;
        list_Student->next = new_student_node;
    }
}

bool removeStudentNode(StudentNode*& head, string studentId)
{
    if (head->student.student_id == studentId)
    {
        StudentNode* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    for (StudentNode* tmp = head; tmp->next != nullptr; tmp = tmp->next)
    {
        if (tmp->next->student.student_id == studentId)
        {
            StudentNode* del = tmp->next;
            tmp->next = tmp->next->next;
            delete del;
            return true;
        }
    }

    return false;
}

StudentNode* searchStudentNode(ClassNode* allClass, string studentId)
{
	for (ClassNode* tmp = allClass; tmp != nullptr; tmp = tmp->next)
	{
		StudentNode* student = searchStudentNodeInOneClass(tmp->my_class.student_list, studentId);
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
        string number;
        Student person;
        getline(ss, number, ',');
        person.num = stoi(number);
        getline(ss, person.student_id, ',');
        getline(ss, person.first_name, ',');
        getline(ss, person.last_name, ',');
        getline(ss, number, ',');
        person.gender = stoi(number);
        getline(ss, person.dob, ',');
        getline(ss, person.social_id, ',');
        getline(ss, person.password, ',');
        addNewStudentNode(list_student, person);
    }
}

void exportStudentToFile(ofstream &file, StudentNode *list_student)
{
    if (!list_student)
    {
        file << "*" << endl;
        return;
    }

    else
    {
        while (list_student)
        {
            Student person = list_student->student;
            file << person.num << ","
                << person.student_id << ","
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

bool importNewStudentsFromStaff(ClassNode*& classNode, string file_name, ifstream& fin)
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
    
    while (getline(fin, line))
    {
        Student temp;
        istringstream iss(line);
        string field;
        getline(iss, field, ',');
        temp.num = stoi(field);
        getline(iss, temp.student_id, ',');
        getline(iss, temp.first_name, ',');
        getline(iss, temp.last_name, ',');
        getline(iss, field, ',');
        temp.gender = stoi(field);
        getline(iss, temp.dob, ',');
        getline(iss, temp.social_id, ',');
        getline(iss, temp.password, ',');
        addNewStudentNode(classNode->my_class.student_list, temp);
    }

    fin.close();
    return true;
}

void deleteStudentList(StudentNode*& studentList)
{
    while (studentList)
    {
		StudentNode* temp = studentList;
        deleteResultsList(temp->student.results_list);
		studentList = studentList->next;
		delete temp;
	}
}

// StudentSubNode

StudentSubNode* createStudentSubNode(StudentNode* studentNode)
{
    return new StudentSubNode{ studentNode, nullptr };
}

void appendStudentSubNode(StudentSubNode*& studentSubList, StudentSubNode* studentSubNode)
{
    if (!studentSubList)
        studentSubList = studentSubNode;
    else
    {
        StudentSubNode* temp = studentSubList;
        while (temp->next)
            temp = temp->next;

        temp->next = studentSubNode;
    }
}

// Add one extra student to a course
bool addStudentSubNodeToCourse(ClassNode* allClass, CourseNode*& courseNode, string student_id, string year_id, string sem_id)
{
    StudentNode* studentNode = searchStudentNode(allClass, student_id);
    if (!studentNode)
    {
        cout << "Student " << student_id << " does not exist." << endl;
        return false;
    }

    StudentSubNode* studentSubNode = createStudentSubNode(studentNode);
    appendStudentSubNode(courseNode->course.extra_stu, studentSubNode);
    Results results = createResults(courseNode->course.course_id, year_id, sem_id, 0.0f, 0.0f, 0.0f);
    appendResultsNode(studentNode->student.results_list, createResultsNode(results));
    return true;
}

StudentSubNode* searchStudentSubNode(StudentSubNode* studentSubList, string student_id)
{
    StudentSubNode* temp = studentSubList;
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
bool deleteStudentSubNode(StudentSubNode*& studentSubList, string student_id, string course_id, string year_id, string sem_id)
{
    StudentSubNode* nodeToDelete = searchStudentSubNode(studentSubList, student_id);
    if (nodeToDelete)
    {
        if (studentSubList == nodeToDelete)
            studentSubList = studentSubList->next;
        else
        {
            StudentSubNode* temp = studentSubList;
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
void deleteAllExtraStudents(StudentSubNode*& studentSubList, string course_id, string year_id, string sem_id)
{
    StudentSubNode* temp = studentSubList;
    while (studentSubList)
    {
        StudentSubNode* temp = studentSubList;
        deleteResultsNode(temp->student_node->student.results_list, course_id, year_id, sem_id);
        delete temp;
        studentSubList = studentSubList->next;
    }
}

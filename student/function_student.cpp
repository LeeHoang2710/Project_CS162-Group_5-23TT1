#include ".\struct and function\student.h"

Student createStudent(int p_num, string p_student_id, string p_first, string p_last, bool p_gender, string p_dob, string p_social_id, string p_pass, string p_class)
{
    Student person;
    person.num = p_num;
    person.student_id = p_student_id;
    person.first_name = p_first;
    person.last_name = p_last;
    person.gender = p_gender;
    person.dob = p_dob;
    person.social_id = p_social_id;
    person.password = p_pass;
    person.student_class = p_class;
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
    return;
}

void removeStudentNode(StudentNode *&head, Student student_1)
{
    if (!head)
        return;
    StudentNode *person = head;
    while (person && person->next)
    {
        if (person->next->student.student_id == student_1.student_id)
        {
            StudentNode *temp = person;
            person->next = person->next->next;
            delete temp;
        }
        else
            person = person->next;
    }
}

StudentNode *searchStudentNode(StudentNode *head, Student student_1)
{
    if (!head)
    {
        cout << "Cannot find the searched student..." << endl;
        return nullptr;
    }
    StudentNode *list_student = head;
    while (list_student)
    {
        if (list_student->student.student_id == student_1.student_id)
            return list_student;
        else
            list_student = list_student->next;
    }
    cout << "Cannot find the searched student..." << endl;
    return nullptr;
}

void readStudentFromFile(ifstream &file, StudentNode *&list_student)
{
    file.open("./database/student.csv");
    if (!file.is_open())
        cout << "Can not open file" << endl;
    else
    {
        string line;

        while (getline(file, line))
        {
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
            getline(ss, person.student_class, ',');

            addNewStudentNode(list_student, person);
        }
    }
    file.close();
}

void exportStudentToFile(ofstream &file, StudentNode *list_student)
{
    file.open("./database/student.csv");
    if (!file.is_open())
        cout << "Can not open file" << endl;
    else
    {
        if (!list_student)
        {
            file.close();
            return;
        }
        else
        {
            while (list_student)
            {
                Student person = list_student->student;
                file << person.num << "," << person.student_id << "," << person.first_name << "," << person.last_name;
                file << person.social_id << "," << person.password << "," << person.student_class << endl;
                list_student = list_student->next;
            }
        }
    }
    file.close();
}
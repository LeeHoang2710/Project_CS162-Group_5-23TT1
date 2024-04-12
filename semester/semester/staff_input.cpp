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

bool importResultFromStaff(ifstream& fin, const string& filename, CourseNode* courseNode)
{
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Cannot open file " << filename << " to " << endl;
		return false;
    }

    importResultInCourse(fin, courseNode);

    fin.close();
    return true;
}

bool importResultInCourse(ifstream& fin, CourseNode* courseNode)
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
        updateScore(studentNode->student.result_list->result.score, stof(process), stof(midterm), stof(final));
        updateCurrentSemGpa(studentNode);
        updateTotalGpa(studentNode);
    }
}
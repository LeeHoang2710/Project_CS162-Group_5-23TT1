#include "../struct_and_function/function.h"

void StorePassWordStudent(StudentNode *&StuPass, ifstream &ip, string file)
{
    ip.open(file);
    StudentNode *cur = StuPass;
    Student tmp;

    while (getline(ip, tmp.student_id, ',') && getline(ip, tmp.password, '\n'))
    {
        StudentNode *newNode = new StudentNode;
        newNode->student = tmp;
        newNode->next = NULL;

        if (StuPass == NULL)
        {
            StuPass = newNode;
            cur = StuPass;
        }
        else
        {
            cur->next = newNode;
            cur = cur->next;
        }
    }

    ip.close();
}
void StorePassWordStaff(StaffNode *&StaffPass, ifstream &ip, string file)
{
    ip.open(file);
    StaffNode *cur = StaffPass;
    Staff tmp;

    while (getline(ip, tmp.username, ',') && getline(ip, tmp.password, '\n'))
    {
        StaffNode *newNode = new StaffNode;
        newNode->staff = tmp;
        newNode->next = NULL;

        if (StaffPass == NULL)
        {
            StaffPass = newNode;
            cur = StaffPass;
        }
        else
        {
            cur->next = newNode;
            cur = cur->next;
        }
    }

    ip.close();
}
bool LoginForStudent(StudentNode *StuPass, string &username, string &pass)
{
    if (!StuPass)
        return false;
    StudentNode *tmp = StuPass;
    for (tmp; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->student.student_id == username && tmp->student.password == pass)
            return true;
    }
    return false;
}
bool LoginForStaff(StaffNode *StaffPass, string &username, string &pass)
{
    if (!StaffPass)
        return false;
    StaffNode *tmp = StaffPass;
    for (tmp; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->staff.username == username && tmp->staff.password == pass)
            return true;
    }
    return false;
}
void UpdateStuPassFile(StudentNode *List, ofstream &op)
{
    op.open("../database/Students_Password.csv");
    for (StudentNode *tmp = List; tmp != NULL; tmp = tmp->next)
    {
        op << tmp->student.student_id << ",";
        op << tmp->student.password;
        if (tmp->next != NULL)
            op << endl;
    }
    op.close();
}
void UpdateStaffPassFile(StaffNode *List, ofstream &op)
{
    op.open("../database/Staff_Password.csv");
    for (StaffNode *tmp = List; tmp != NULL; tmp = tmp->next)
    {
        op << tmp->staff.username << ",";
        op << tmp->staff.password;
        if (tmp->next != NULL)
            op << endl;
    }
    op.close();
}
bool ChangePassStudent(StudentNode *current)
{
    while (1)
    {
        string input_Pass;
        // cout << "Enter your current password: ";
        cin >> input_Pass;
        if (current->student.password == input_Pass)
        {
            // cout << "Enter your new password: ";
            cin >> input_Pass;
            current->student.password = input_Pass;
            // cout << "Password changed successfully " << endl;
            return true;
        }
        else
        {
            // cout << "current password is wrong, please try again" << endl;
            return false;
        }
    }
}
bool ChangePassStaff(StaffNode *current)
{
    while (1)
    {
        string input_Pass;
        // cout << "Enter your current password: ";
        cin >> input_Pass;
        if (current->staff.password == input_Pass)
        {
            // cout << "Enter your new password: ";
            cin >> input_Pass;
            current->staff.password = input_Pass;
            // cout << "Password changed successfully" << endl;
            return true;
        }
        else
        {
            // cout << "current password is wrong, please try again" << endl;
            return false;
        }
    }
}
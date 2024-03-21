#pragma once
void StorePassWordStudent(StudentNode*& StuPass, ifstream& ip); //These 2 fucntions will load password file to a linked list
void StorePassWordStaff(StaffNode*& StaffPass, ifstream& ip);
void LoginForStudent(StudentNode* StuList, string& onstatus_ID, StudentNode*& ChangeStuPass); // 1st parameter is the linked list, 2nd parameter is the ID of student who is onl
void LoginForStaff(StaffNode* StaffPass, string& onstatus_UserName, StaffNode*& ChangeStaffPass); // 3rd parameter is the node store the current id, used it only for changing password
void UpdateStuPassFile(StudentNode* List, ofstream& op); //Update the password file when someone change password;
void UpdateStaffPassFile(StaffNode* List, ofstream& op);
void ChangePassStudent(StudentNode* current); //get the node of user who is online and change password in it;
void ChangePassStaff(StaffNode* current);
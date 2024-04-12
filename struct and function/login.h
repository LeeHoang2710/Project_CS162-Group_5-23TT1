#pragma once
void StorePassWordStudent(StudentNode*& StuPass); //These 2 fucntions will load password file to a linked list
void StorePassWordStaff(StaffNode*& StaffPass);
bool LoginForStudent(StudentNode* StuList, string input_ID, string input_Pass); // 1st parameter is the linked list, 2nd parameter is the ID of student who is onl
bool LoginForStaff(StaffNode* StaffPass, string input_Username, string input_Pass); // 3rd parameter is the node store the current id, used it only for changing password, 4 and 5 parameter is what user enter
void UpdateStuPassFile(StudentNode* List, ofstream& op); //Update the password file when someone change password;
void UpdateStaffPassFile(StaffNode* List, ofstream& op);
bool ChangePassStudent(StudentNode* current, string input_Pass, string newpass); //get the node of user who is online and change password in it;
bool ChangePassStaff(StaffNode* current, string input_Pass, string newpass);
StaffNode* searchStaffNode(StaffNode* head, string staff_1_id);
void profilestaff(ifstream& ip, string staff_id);
void profilestudent(ifstream& ip, string stu_id);
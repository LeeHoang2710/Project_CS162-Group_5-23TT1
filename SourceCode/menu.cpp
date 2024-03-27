#pragma once
#include <iostream>
using namespace std;
#include "../struct and function/menu.h"
#include "../struct and function/course.h"
#include "../struct and function/student.h"
#include "../struct and function/login.h"

int main() {
	cout << "Are you a staff or a student: " << endl;
	cout << "1.Staff || 2.Student " << endl;
	cout << "Enter your choice: ";
	int role; cin >> role;
	cin.ignore();
	switch (role) {
	case 1:
	{
		StaffNode* StaffPass = NULL; // linked list of the whole password
		string Staff_Locate; // store the id to locate which staff is using
		StaffNode* StaffCurrent = NULL;//Node of where the current staff is
		StorePassWordStaff(StaffPass);
		string input_username, input_password;
		cout << "-------------LOGIN-------------" <<endl; 
		do {
			cout << "Username: ";
			getline(cin, input_username, '\n');
			cout << "Password: ";
			getline(cin, input_password, '\n');
		} while (LoginForStaff(StaffPass, Staff_Locate, StaffCurrent, input_username, input_password) == false);
		//after login
		bool mainmenu = true;
		while (mainmenu) {
			cout <<endl <<  "-------------------------------" << endl;
			cout << "1. School year " << endl;
			cout << "2. Course " << endl;
			cout << "3. Class " << endl;
			cout << "4. Profile " << endl;
			cout << "5. Log out " << endl;
			cout << "Enter your choice: ";
			int choice; cin >> choice;
			switch (choice) {
			case 1: {
				bool yearloop = true;
				while (yearloop) {
					cout << endl << "-------------------------------" << endl;
					cout << "1. Create a new school year " << endl;
					cout << "2. View school year " << endl;
					cout << "3. Return " << endl;
					cout << "Enter your choice: ";
					cin >> choice;
					switch (choice) {
					case 1: {
						cout << endl << "-------------------------------" << endl;
						cout << "1. Create a class " << endl;
						cout << "2. Return " << endl;
						cout << "Enter your choice: ";
						cin >> choice;
						switch (choice) {
						case 1: {
							//class function
							cout << "return to main menu?    1.yes || your choice: ";
							int check = 0;
							cin >> check;
							if (check == 1) yearloop = false;
							break;

						}
						case 2: {
							break;
						}
						}
						break;
					}
					case 2: {
						break;
					}
					}
				}
				break;
			}
			case 2: {
				cout << "1.  ";
				break;
			}
			case 3: {
				break; }
			case 4: {
				break; }
			}
		}
		break;
	}
	case 2:
	{
		StudentNode* StuPass = NULL;
		string Stu_Locate;
		StudentNode* StuCurrent = NULL;
		StorePassWordStudent(StuPass);
		string input_id, input_password;
		do {
			cout << "Username: ";
			getline(cin, input_id, '\n');
			cout << "Password: ";
			getline(cin, input_password, '\n');
		} while (LoginForStudent(StuPass, Stu_Locate, StuCurrent, input_id, input_password) == false);
		break;
	}
	}
	//above is login
	
}
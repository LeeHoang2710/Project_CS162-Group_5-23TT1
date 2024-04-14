//#pragma once
//#include <iostream>
//using namespace std;
//#include "../struct_and_library.h"
//#include "../struct and function/menu.h"
//#include "../struct and function/course.h"
//#include "../struct and function/student.h"
//#include "../struct and function/login.h"
//#include "../struct and function/year.h"
//#include "../struct and function/semester.h"
//
//int main() {
//	cout << "Are you a staff or a student: " << endl;
//	cout << "1.Staff || 2.Student " << endl;
//	cout << "Enter your choice: ";
//	int role; cin >> role;
//	cin.ignore();
//	switch (role) {
//	case 1:
//	{
//		StaffNode* StaffPass = NULL; // linked list of the whole password
//		string Staff_Locate; // store the id to locate which staff is using
//		StaffNode* StaffCurrent = NULL;//Node of where the current staff is
//		StorePassWordStaff(StaffPass);
//		string input_username, input_password;
//		cout << "-------------LOGIN-------------" << endl;
//		do {
//			cout << "Username: ";
//			getline(cin, input_username, '\n');
//			cout << "Password: ";
//			getline(cin, input_password, '\n');
//		} while (LoginForStaff(StaffPass, Staff_Locate, StaffCurrent, input_username, input_password) == false);
//		//after login
//		bool mainmenu = true;
//		while (mainmenu) {
//			cout << endl << "-------------------------------" << endl;
//			cout << "1. School year " << endl;
//			cout << "2. Course " << endl;
//			cout << "3. Class " << endl;
//			cout << "4. Profile " << endl;
//			cout << "5. Log out " << endl;
//			cout << "Enter your choice: ";
//			int choice; cin >> choice;
//			switch (choice) {
//			case 1: {
//				bool yearloop = true;
//				while (yearloop) {
//					cout << endl << "-------------SCHOOL YEAR------------------" << endl;
//					cout << "1. Create a new school year " << endl;
//					cout << "2. View school year " << endl;
//					cout << "3. Return " << endl;
//					cout << "Enter your choice: ";
//					cin >> choice;
//					switch (choice) {
//					case 1: {
//						cout << endl << "------------------------------" << endl;
//						string year_id;
//						inputYearId(year_id);
//						//import year, semester list before
//						YearNode* newYearNode = initYearNode(createYear(year_id);
//						appendYearNode(year_list, newYearNode));
//						cout << "Added school year successfully." << endl;
//
//						cout << "1. Add semester " << endl;
//						cout << "2. Return " << endl;
//						cout << "Enter your choice: ";
//						cin >> choice;
//						switch (choice) {
//						case 1: {
//							//class function
//							cout << "return to main menu?    1.yes || your choice: ";
//							int check = 0;
//							cin >> check;
//							if (check == 1) yearloop = false;
//							break;
//
//						}
//						case 2: {
//							string sem_id, start_date, end_date;
//							inputSemesterInfo(sem_id, start_date, end_date);
//							SemesterNode* newSem = createSemesterNode(createSemester(sem_id, start_date, end_date));
//							appendSemesterNode(newYearNode->school_year.list_sem, newSem);
//							break;
//						}
//						default:
//							cout << "choose again" << endl;
//							break;
//						}
//						break;
//					}
//					case 2: {
//						//view list of school years (view year id)...
//
//						//choose school year:
//						string searchYearId;
//						inputYearId(searchYearId);
//						YearNode* currYearNode = searchYearNode(year_list, searchYearId);
//						if (!currYearNode)
//						{
//							cout << "School year does not exist. Please try again." << endl;
//							break;
//						}
//
//						bool semesterloop = true;
//						while (semesterloop) {
//							cout << "------------------------------------" << endl;
//							cout << "1. Fix year id " << endl;
//							cout << "2. Add a semester " << endl;
//							cout << "3. Update semester's information " << endl;
//							cout << "4. Return " << endl;
//							cout << "Enter your choice: ";
//							cin >> choice;
//							switch (choice) {
//							case 1: {
//								//currYear is declared somewhere
//								string newYearId;
//								inputYearId(newYearId);
//								updateYearId(currYearNode, newYearId);
//								break;
//							}
//							case 2: {
//								string sem_id, start_date, end_date;
//								inputSemesterInfo(sem_id, start_date, end_date);
//								SemesterNode* newSem = createSemesterNode(createSemester(sem_id, start_date, end_date));
//								appendSemesterNode(currYearNode->school_year.list_sem, newSem);
//								break;
//							}
//							case 3: {
//								//view list of semesters in currYearNode (view semester id)...
//								//if there are no semesters then break
//								
//								//choose semester:
//								int semNum;
//								cout << "Enter semester number (1, 2, or 3): ";
//								cin >> semNum;
//								SemesterNode* currSemNode = searchSemesterNode(currYearNode, semNum);
//								if (!currSemNode)
//								{
//									cout << "Semester does not exist. Please try again." << endl;
//									break;
//								}
//								//view current sem info
//								string newStartDate, newEndDate;
//								inputSemesterDates(newStartDate, newEndDate);
//								updateSemesterInfo(currSemNode, newStartDate, newEndDate);
//								//view current sem info
//								cout << "Updated successfully." << endl;
//								break;
//							}
//							case 4: {
//								semesterloop = false;
//								break;
//							}
//							}
//						}
//						break;
//					}
//					case 3: {
//						yearloop = false;
//						break;
//					}
//					default:
//						cout << "choose again" << endl;
//						break;
//					}
//				}
//				break;
//			}
//			case 2: {
//				bool courseloop = true;
//				while (courseloop) {
//					cout << "---------------COURSE-------------" << endl;
//					cout << "1. Update or fix information of a course" << endl;
//					cout << "2. View courses " << endl; //choose year to view course;
//					cout << "3. Return" << endl;
//					cout << "Enter your choice: ";
//					cin >> choice;
//					switch (choice) {
//					case 1: {
//						break;
//					}
//					case 2: {
//						break;
//					}
//					case 3: {
//						courseloop = false;
//						break;
//					}
//					default:
//						cout << "choose again" <<endl;
//						break;
//					}
//				}
//				break;
//			}
//			case 3: {
//				break; 
//			}
//			case 4: {
//				break;
//			}
//			default:
//				cout << "choose again" << endl;
//				break;
//			}
//		}
//		break;
//	}
//	case 2:
//	{
//		StudentNode* StuPass = NULL;
//		string Stu_Locate;
//		StudentNode* StuCurrent = NULL;
//		StorePassWordStudent(StuPass);
//		string input_id, input_password;
//		do {
//			cout << "Username: ";
//			getline(cin, input_id, '\n');
//			cout << "Password: ";
//			getline(cin, input_password, '\n');
//		} while (LoginForStudent(StuPass, Stu_Locate, StuCurrent, input_id, input_password) == false);
//		break;
//	}
//	default: 
//		cout << "choose again" << endl;
//		break;
//	}
//}
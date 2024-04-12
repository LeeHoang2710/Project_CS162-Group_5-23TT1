//#pragma once
//#include <iostream>
//using namespace std;
//#include "../struct and function/menu.h"
//#include "../struct and function/course.h"
//#include "../struct and function/student.h"
//#include "../struct and function/login.h"
//#include "../session, year, semester/year.h"
//#include "../session, year, semester/session.h"
//#include "../session, year, semester/semester.h"
//#include "class.h"
//
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
//		ifstream ip;
//		ofstream op;
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
//		//declare Head of linked list;
//		YearNode* yearlist = nullptr;
//		YearNode* newyear = nullptr;
//		string filename;
//		while (mainmenu) {
//			cout << endl << "-------------------------------" << endl;
//			cout << "1. School year " << endl;
//			cout << "2. Course " << endl;
//			cout << "3. Class " << endl;
//			cout << "4. Profile " << endl;
//			cout << "5. Log out " << endl;
//			cout << "6. Semester " << endl;
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
//						Year temp=createYear(year_id);
//						newyear= initYearNode(temp);
//						appendYearNode(yearlist, newyear);
//						cout << "Year " << year_id << "has been created" << endl;
//						//
//
//						//
//						cout << "1. Add semester " << endl;
//						cout << "2. Add new classes " << endl;
//						cout << "3. Return " << endl;
//						cout << "Enter your choice: ";
//						cin >> choice;
//						switch (choice) {
//						case 1: {
//							/*string sem_id, start, end;*/
//							/*inputSemesterInfo(sem_id, start, end);
//							Semester newsem = createSemester(sem_id, start, end);
//							SemesterNode* newsemnode = createSemesterNode(newsem);
//							appendSemesterNode(newyear->school_year.list_sem, newsemnode);
//							cout << "A new semester has just been created " << endl;*/
//							bool check = 0;
//							cin >> check;
//							if (check == 1) yearloop = false;
//							break;
//
//						}
//						case 2: {
//							cout << "-------ADDING CLASSES---------" << endl;
//							while (1) {
//								string classid, headteacher;
//								cout << "Class id: ";
//								cin.ignore();
//								getline(cin, classid, '\n');
//								cout << "Head teacher: ";
//								getline(cin, headteacher, '\n');
//								cout << "Enter filename to add students ";
//								StudentNode* stuhead = nullptr;
//								readStudentFromFile(ip, filename, stuhead);
//								Class newclass = CreateClass(classid, headteacher, stuhead);
//								AddClassNode(newyear->school_year.allclass, newclass);
//								cout << "0. Continue || 1.Exit ";
//								bool exit = 0; // phai thoat ra khoi vong lap
//								cin >> exit;
//								if (exit) break;
//							}
//							break;
//						}
//						default:
//							cout << "choose again" << endl;
//							break;
//						}
//						break;
//					}
//					case 2: {
//						bool semesterloop = true;
//						while (semesterloop) {
//							cout << "------------------------------------" << endl;
//							cout << "1. Fix year id " << endl;
//							cout << "2. Update semester in a school year " << endl;
//							cout << "3. Return " << endl;
//							cout << "Enter your choice: ";
//							cin >> choice;
//							switch (choice) {
//							case 1: {
//								break;
//							}
//							case 2: {
//								break;
//							}
//							case 3: {
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
//					//list ra may cai semester de chon course
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
//			case 6:
//			{
//				string sem_id, start, end;
//				inputSemesterInfo(sem_id, start, end);
//				Semester newsem = createSemester(sem_id, start, end);
//				SemesterNode* newsemnode = createSemesterNode(newsem);
//				appendSemesterNode(newyear->school_year.list_sem, newsemnode);
//				cout << "A new semester has just been created " << endl;
//				cout << "Add courses to this semester: " <<endl;
//				while (1) {
//					InputCourse(newsemnode->sem.course_list);
//					cout << "0. Continue || 1. Finish: ";
//				    bool exit;
//					cin >> exit;
//					if (exit) break;
//				}
//				
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
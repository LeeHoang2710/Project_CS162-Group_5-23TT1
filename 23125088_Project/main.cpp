#include "function.h"
int main (){
	YearNode* YearNodehead = 0;
	SemesterNode* SemesterNodehead = 0;
	CourseNode* CourseNodehead = 0;
	ClassNode* ClassNodehead = 0;
	StudentNode* StudentNodehead = 0;
	StaffNode* StaffNodehead = 0;
	ifstream fin;
	fin.open("namefilestudent");
	if (fin.is_open()) {
		StorePassWordStudent(StudentNodehead, fin);
		fin.close();
	}
	fin.open("namefilestaff");
	if (fin.is_open()) {
		StorePassWordStaff(StaffNodehead, fin);
		fin.close();
	}
	while (1)
	{
		int n;
		while (1)
		{
			cout << "1. Log in.\n";
			cout << "2. Exit.\n";
			cout << "Your choice: ";
			cin >> n;
			switch (n)
			{
			case 1:
			{
				while (1) {
					int p;
					cout << "1. Go back.\n";
					cout << "2. Log in with student account.\n";
					cout << "3. Log in with staff account.\n";
					cin >> p;
					switch (p)
					{
					case 1:
					{						
						break;
					}
					case 2:
					{
						/*LoginForStudent();
						if(LoginForStudent())
						{

						}
						*/
					    
						break;
					}
					case 3:
					{						
						/*LoginForStaff();
						if(LoginForStaff())
						{
						     
						}
						*/
						cout << "Log in successfully!.\n";
						int m;
						while (1) {
							cout << "1. Log out";
							cout << "2. Change password.\n";
							cout << "3. Semester.\n";
							cout << "4. School year and class.\n";
							cout << "5. View a list of classes.\n";
							cout << "6. View List of course.\n";
							cout << "7. View a list of students in a class.\n";
							cout << "8. View a list of students in a course.\n";
							cout << "9. Export a list of students in a course to a CSV file.\n";
							cout << "10. Import the scoreboard of a course.\n";
							cout << "11. Update a student's result.\n";
							cout << "12. View the scoreboard of a class.\n";
							cout << "Your choice: ";
							cin >> m;
							switch (m) {
							case 1:
							{
								break;
							}
							case 2:
							{
								ChangePassStaff(StaffNodehead);
								break;
							}
							case 3:
							{
								int p;
								cout << "1. Go back.\n";
								cout << "2. Import year semester from file.\n";
								cout << "3. Export year semester to text file.\n";
								break;
							}
							default:
								break;
							}
						}
					}
					default:
						break;
					}					
				}
			}
			case 2:
			{
				break;
			}
			default:
				break;
			}
			
		}
	}
	return 0;
}

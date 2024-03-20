#include <iostream>
using namespace std;
int main()
{
	int n;
	while (1) {
		cout << "1. Log in.\n";
		cout << "2. Exit.\n";
		cout << "-------\n";
		cout << "Your choice: ";
		cin >> n;
		if (n == 1) {
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
				if (m == 1) {
					break;
				}
				else if (m == 2) {
					//void changepassword...
				}
				else if (m == 3) {
					int p;
					while (1) {
						cout << "1. Go back.\n";
						cout << "2. Create one semester.\n";
						cout << "3. Add one course to currrent semester.\n";
						cout << "Update CSV file.\n";
						cin>>p;
					}
				}
				else if (m == 4) {
					int p;
					cout << "1. Add one school year.\n";
					cout << "2. Add ona class.\n";
					cin >> p;
				}
				else if (m == 5) {

				}
				else if (m == 6) {
				
				}
				else if (m == 7) {

				}
				else if (m == 8) {
					
				}
				else if (m == 9) {

				}
				else if (m == 10) {

				}
				else if (m == 11) {

				}
				else if (m == 12) {

				}
			}
		
		}
		else if (n == 2) {
			break;//Exit
		}
		else {
			cout << "Your choice is invalid,please choose again.\n";
		}
	}
	return 0;
}

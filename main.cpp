#include "./struct_and_function/view_function.h"

int main()
{
    RenderWindow window;
    window.create(VideoMode(1440, 960), "CS162-Project", Style::Default);
    window.setFramerateLimit(60);
    int page = 1;
    bool is_staff = false, menu = false;
    string username = "";
    string pass = "";
    StudentNode *user1 = nullptr;
    StaffNode *user2 = nullptr;
    YearNode *year = nullptr;
    ClassNode *class_list = nullptr;
    ofstream fout;
    ifstream fin;

    // StorePassWordStudent(user1, fin, "./database/student_password.csv");
    // StorePassWordStaff(user2, fin, "./database/staff_password.csv");
    importStaff(user2, fin, "./database/staff_list.csv");
    ReadClassfromfile(class_list, "./database/class.csv", fin);
    bool success = importYear(year, class_list, "./database/semester.csv", fin);
    if (!success)
        cout << "Cannot import year" << endl;

    success = importResults(fin, class_list, "./database/result.csv");
    if (!success)
        cout << "Cannot import result" << endl;

    StaffNode *user = nullptr;
    while (window.isOpen())
    {
        switch (page)
        {
        case 1:
            Scene1(window, page, is_staff);
            break;
        case 2:
        {
            bool see = false;
            logIn(window, page, is_staff, see, user1, user2, username, pass, user);
            break;
        }
        case 3:
        {
            if (is_staff)
                homeStaff(window, page, user, menu);
            /*else
                homeStudent(window, page); */
            break;
        }
        case 4:
        {
            School(window, page, is_staff, year, class_list, menu);
            break;
        }
        case 16:
        {
            Classes(window, page, is_staff, class_list, menu);
            break;
        }
        case 19:
        {
            Other(window, page, user, menu);
            break;
        }
        case 20:
        {
            changePassword(window, page, is_staff, user, menu);
            break;
        }
        case 21:
        {
            Profile(window, page, user, menu);
            break;
        }

        default:
            break;
        }
    }
    exportYear(year, "./database/semester.csv", fout);
    ExportClassTFile(class_list, "./database/class.csv", fout);
    Exportallscoretofile(fout, "./database/result.csv", class_list);
    ExportStaff(user2, fout, "./database/staff_list.csv");
    deleteYearList(year);
    delete user, user1, user2;
    delete class_list;

    return 0;
}

// page 1: who are you
// page 2: log in
// page 3: home staff
// page 4: school year
// page 5: semester
// page 6: create sem
// page 7: course
// page 8: create cour
// page 9: update cour
#include "./include/view_function.h"

int main()
{
    RenderWindow window;
    window.create(VideoMode(1440, 960), "CS162-Project-LMS-Group-5", Style::Default);
    window.setFramerateLimit(60);
    Image icon;
    icon.loadFromFile("./image/page1/Asset 1.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int page = 1;
    bool is_staff = false, menu = false;
    string username = "";
    string pass = "";
    StaffNode *user2 = nullptr;
    YearNode *year = nullptr;
    ClassNode *class_list = nullptr;
    ofstream fout;
    ifstream fin;

    bool success;
    importStaff(user2, fin, "./database/staff_list.csv");
    ReadClassFromFile(class_list, "./database/class_list.csv", fin);
    success = importYear(year, class_list, "./database/year_list.csv", fin);
    if (!success)
        cout << "Cannot import year" << endl;

    success = importResults(fin, class_list, "./database/results_list.csv");
    if (!success)
        cout << "Cannot import result" << endl;

    StaffNode *user = nullptr;
    StudentNode *user1 = nullptr;
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
            logIn(window, page, is_staff, see, user2, username, pass, user, user1, class_list);
            break;
        }
        case 3:
        {
            if (is_staff)
                homeStaff(window, page, user, menu);
            break;
        }
        case 4:
        {
            if (!is_staff)
                homeStudent(window, page, user1, menu);
            break;
        }
        case 5:
        {
            School(window, page, is_staff, year, class_list, menu);
            break;
        }
        case 6:
        {
            Classes(window, page, is_staff, class_list, menu);
            break;
        }
        case 7:
        {
            Other1(window, page, user, menu);
            break;
        }
        case 8:
        {
            courseStudent(window, page, year, user1, menu);
            break;
        }
        case 9:
        {
            resultStudent(window, page, user1, menu);
            break;
        }
        case 10:
        {
            Other2(window, page, user1, menu);
            break;
        }

        case 21:
        {
            changePassword(window, page, is_staff, user, user1, menu);
            break;
        }
        case 22:
        {
            Profile1(window, page, user, menu);
            break;
        }
        case 23:
        {
            Profile2(window, page, class_list, user1, menu);
            break;
        }

        default:
            break;
        }
    }
    exportYear(year, "./database/year_list.csv", fout);
    ExportClassToFile(class_list, "./database/class_list.csv", fout);
    ExportAllScoreToFile(fout, "./database/results_list.csv", class_list);
    ExportStaff(user2, fout, "./database/staff_list.csv");

    deleteClassList(class_list);
    deleteYearList(year);
    deleteStaffList(user2);

    return 0;
}

// page 1: who are you
// page 2: log in
// page 3: home staff
// page 4: home student
// page 5: school year
// page 6: class
// page 7: other - staff
// page 8: course
// page 9: scoreboard
// page 10: other - student
// page 11: semester
// page 12: create sem
// page 13: course
// page 14: create cour
// page 15: update cour
// page 16: result cour
// page 17: student
// page 18: result stu
// page 19: course - student
// page 20: score - student
// page 21: change password
// page 22: profile - staff
// page 23: profile - student
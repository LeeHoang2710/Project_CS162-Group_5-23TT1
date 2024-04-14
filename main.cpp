#include "./struct_and_function/view_function.h"

int main()
{
    RenderWindow window;
    window.create(VideoMode(1440, 960), "CS162-Project", Style::Default);
    int page = 1;
    bool is_staff = false;
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
    importYear(year, "./database/semester.csv", fin);
    ReadClassfromfile(class_list, "./database/class.csv", fin);

    while (page > 0 && window.isOpen())
    {
        switch (page)
        {
        case 1:
            Scene1(window, page, is_staff);
            break;
        case 2:
        {
            bool see = false;
            logIn(window, page, is_staff, see, user1, user2, username, pass);
            break;
        }
        // case 3:
        // {
        //     if (is_staff)
        //         homeStaff(window, page);
        //     /*else
        //         homeStudent(window, page); */
        //     break;
        // }
        case 4:
        {
            School(window, page, is_staff, year);
            break;
        }
        case 16:
        {
            Classes(window, page, is_staff, class_list);
        }
        // case 19:
        // {
        //     Other(window, page, is_staff);
        //     break;
        // }
        case 20:
        {
            changePassword(window, page, is_staff);
            break;
        }

        default:
            break;
        }
    }
    exportYear(year, "./database/semester.csv", fout);
    ExportClassTFile(class_list, "./database/class.csv", fout);
    deleteYearList(year);
    delete user1, user2;
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
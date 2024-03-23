#include "view_function.h"

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
    ifstream ip;

    StorePassWordStudent(user1, ip, "../database/student_password.csv");
    StorePassWordStaff(user2, ip, "../database/staff_password.csv");
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
        case 3:
        {
            if (is_staff)
                homeStaff(window, page);
            /*else
                homeStudent(window, page); */
            break;
        }
        case 4:
        {
            // School(window, page, is_staff);
            break;
        }
        case 19:
        {
            Other(window, page, is_staff);
            break;
        }
        case 20:
        {
            changePassword(window, page, is_staff);
            break;
        }

        default:
            break;
        }
    }

    return 0;
}

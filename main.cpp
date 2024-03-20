#include "view_function.h"

int main()
{
    RenderWindow window;
    window.create(VideoMode(1440, 960), "CS162-Project", Style::Default);
    int page = 1;
    bool is_staff = false;

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
            logIn(window, page, is_staff, see);
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
            Year(window, page, is_staff);
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

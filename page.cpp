#include "view_function.h"
void Scene1(RenderWindow &window, int &page, bool &is_staff)
{
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page1/scene1-bg.png", 180, 120);
    Object o2 = createObject("./image/page1/scene1-staff.png", 340, 462);
    Object o3 = createObject("./image/page1/scene1-student.png", 834, 462);
    Event event;
    while (window.isOpen() && page == 1)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (isHere(o2.bound, mouse))
                    {
                        is_staff = true;
                        page = 2;
                    }
                    else if (isHere(o3.bound, mouse))
                    {
                        is_staff = false;
                        page = 2;
                    }
                }
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(o2.draw);
        window.draw(o3.draw);
        window.display();
    }
}

void logIn(RenderWindow &window, int &page, bool is_staff, bool see, StudentNode *user1, StaffNode *user2, string &name, string &pass)
{

    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page2/scene2-bg.png", 180, 120);
    Object o2 = createObject("./image/page2/login-bg.png", 340, 279);
    Object o3 = createObject("./image/page2/login-button.png", 589, 606);
    Object o4 = createObject("./image/page2/username.png", 603.0f, 432.0f);
    Object o5 = createObject("./image/page2/password.png", 603.0f, 522.0f);
    Object o6 = createObject("./image/page2/alert.png", 423, 351);
    Object o7 = createObject("./image/page2/open.png", 1003, 533);
    Object o8 = createObject("./image/page2/closed.png", 1003, 533);

    Info inputUsername = createText("", 641.0f, 432.0f);
    Info inputPassword = createText("", 641.0f, 522.0f);
    bool isTypingUsername = false, isTypingPassword = false, log_in = true;
    Clock clock;
    string username = "", password = "", hidden_pass = "";

    while (window.isOpen() && page == 2)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (isHere(o4.bound, mouse))
                    {
                        isTypingUsername = true;
                        isTypingPassword = false;
                        inputUsername.txt.setString(username);
                    }
                    else if (isHere(o5.bound, mouse))
                    {
                        isTypingPassword = true;
                        isTypingUsername = false;
                        if (!see)
                            inputPassword.txt.setString(hidden_pass);
                        else
                            inputPassword.txt.setString(password);
                        if (isHere(o7.bound, mouse))
                        {
                            see = true;
                            inputPassword.txt.setString(password);
                        }
                        else if (isHere(o8.bound, mouse))
                        {
                            see = false;
                            inputPassword.txt.setString(hidden_pass);
                        }
                    }
                    // we have to check if the password is right/wrong then move to the next page
                    else if (isHere(o3.bound, mouse))
                    {
                        name = username;
                        pass = password;
                        if (is_staff && LoginForStaff(user2, name, pass))
                        {
                            log_in = true;
                            page = 3;
                        }
                        else if (!is_staff && LoginForStudent(user1, name, pass))
                        {
                            log_in = true;
                            page = 3;
                        }
                        else
                            log_in = false;
                        clock.restart();
                    }
                    else
                    {
                        isTypingUsername = false;
                        isTypingPassword = false;
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                if (isTypingUsername)
                {
                    if (event.text.unicode < 128)
                    {
                        if (event.text.unicode == 8 && !username.empty())
                        {
                            // backspace character
                            username.pop_back();
                        }
                        else if (event.text.unicode == 13) // enter character
                            isTypingUsername = false;
                        else if (event.text.unicode >= 32)
                        {
                            username += static_cast<char>(event.text.unicode);
                        }
                        inputUsername.txt.setString(username + '_');
                    }
                }
                else if (isTypingPassword)
                {
                    if (event.text.unicode < 128)
                    {
                        if (event.text.unicode == 8)
                        {
                            if (!password.empty() && !hidden_pass.empty())
                            {
                                password.pop_back();
                                hidden_pass.pop_back();
                            }
                        }
                        else if (event.text.unicode == 13)
                            isTypingPassword = false;
                        else if (event.text.unicode >= 32)
                        {
                            password += static_cast<char>(event.text.unicode);
                            hidden_pass += '*';
                        }
                        if (see)
                            inputPassword.txt.setString(password + '_');
                        else
                            inputPassword.txt.setString(hidden_pass + '_');
                    }
                }
                break;
            }
            }
        }

        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);

        window.draw(o2.draw);
        window.draw(o3.draw);
        window.draw(o4.draw);
        window.draw(o5.draw);
        window.draw(inputUsername.txt);
        window.draw(inputPassword.txt);
        if (see)
            window.draw(o8.draw);
        else
            window.draw(o7.draw);
        if (!log_in)
            window.draw(o6.draw);
        if (!log_in && clock.getElapsedTime().asSeconds() >= 3)
            log_in = true;
        window.display();
    }
}

void homeStaff(RenderWindow &window, int &page)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/home/homeStaff-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/home/year.png", 235, 348);
    Object o3 = createObject("./image/page3-staff/home/course.png", 235, 462);
    Object o4 = createObject("./image/page3-staff/home/class.png", 235, 580);
    Object o5 = createObject("./image/page3-staff/home/other.png", 235, 698);
    while (window.isOpen() && page == 3)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (isHere(o2.bound, mouse))
                    {
                        page = 4;
                    }
                    if (isHere(o3.bound, mouse))
                    {
                        page = 10;
                    }
                    if (isHere(o5.bound, mouse))
                    {
                        page = 19;
                    }
                }
            }
            break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(o2.draw);
        window.draw(o3.draw);
        window.draw(o4.draw);
        window.draw(o5.draw);
        window.display();
    }
}

void School(RenderWindow &window, int &page, bool is_staff, YearNode *&year)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object f = createObject("./image/page3-staff/forward.png", 231, 259);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object o1 = createObject("./image/page3-staff/school_year/year-bg.png", 180, 120);
    // Object o2 = createObject("./image/page3-staff/school_year/2020.png", 235, 347);
    // Object o3 = createObject("./image/page3-staff/school_year/2021.png", 235, 464);
    // Object o4 = createObject("./image/page3-staff/school_year/2022.png", 235, 581);
    //  Object o5 = createObject("./image/page3-staff/school_year/2023.png", 235, 698);
    Object create = createObject("./image/page3-staff/school_year/create.png", 263, 259);
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object *add[4];
    Info *id[4];
    YearNode *yr[4];
    for (int i = 0; i < 4; ++i)
    {
        add[i] = createObjectTest("./image/page3-staff/school_year/year-node.png", 235, 117 * i + 347);
        id[i] = createInfoTest("", 316, 117 * i + 354);
    }

    bool new_page = false;
    string str = "";
    int count = 0, change = 0;
    while (window.isOpen() && page == 4)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (isHere(f.bound, mouse))
                        page = 5;
                    else if (isHere(b.bound, mouse))
                        page = 3;
                    else if (isHere(create.bound, mouse) && is_staff)
                    {
                        YearNode *curr = year;
                        if (!curr)
                            str = "2023-2024";
                        // default year
                        else
                        {
                            while (curr->next)
                            {
                                curr = curr->next;
                                count++;
                            }
                            str = curr->school_year.year_id;
                            stringstream input(str);
                            int start, end;
                            char dash;
                            input >> start >> dash >> end;
                            str = to_string(start + 1) + dash + to_string(end + 1);
                        }
                        Year new_year = createYear(str);
                        addNewYearNode(year, new_year);
                        count++;
                    }
                    else if (isHere(menu.bound, mouse))
                        page = 3;
                    else if (isHere(prev.bound, mouse))
                    {
                        new_page = true;
                        change += 4;
                    }
                    else if (isHere(next.bound, mouse) && change != 0)
                    {
                        new_page = true;
                        change -= 4;
                    }
                }
            }
            break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        // if (new_page)

        YearNode *temp = year;
        for (int i = 0; i < change; ++i)
            temp = temp->next;
        for (int i = 0; i < 4; ++i)
        {
            yr[i] = temp;
            id[i]->txt.setString(yr[i]->school_year.year_id);
            temp = temp->next;
        }
        new_page = false;

        for (int i = 0; i < 4; ++i)
        {
            if (id[i]->txt.getString() == "")
                break;
            window.draw(add[i]->draw);
            window.draw(id[i]->txt);
        }
        window.draw(create.draw);
        window.draw(f.draw);
        window.draw(b.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(menu.draw);
        window.display();
    }
    for (int i = 0; i < 4; ++i)
    {
        delete add[i], id[i], yr[i];
    }
}

void Other(RenderWindow &window, int &page, bool is_staff)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object f = createObject("./image/page3-staff/forward.png", 231, 256);
    Object b = createObject("./image/page3-staff/backward.png", 183, 256);
    Object o1 = createObject("./image/page3-staff/other/other-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/other/log-out.png", 230, 354);
    Object o3 = createObject("./image/page3-staff/other/change-pass.png", 230, 465);
    Object o4 = createObject("./image/page3-staff/other/profile.png", 230, 576);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);

    while (window.isOpen() && page == 19)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    /*if (isHere(f.bound, mouse))
                        page = 5; */
                    if (isHere(b.bound, mouse))
                        page = 3;
                    else if (isHere(o2.bound, mouse))
                        page = 2;
                    else if (isHere(o3.bound, mouse))
                        page = 20;
                }
            }
            break;
            }

            window.clear();
            window.draw(screen.draw);
            window.draw(o1.draw);
            window.draw(o2.draw);
            window.draw(o3.draw);
            window.draw(o4.draw);
            window.draw(f.draw);
            window.draw(b.draw);
            window.draw(menu.draw);
            window.display();
        }
    }
}

void changePassword(RenderWindow &window, int &page, bool is_staff)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object f = createObject("./image/page3-staff/forward.png", 231, 200);
    Object b = createObject("./image/page3-staff/backward.png", 183, 200);
    Object o1 = createObject("./image/page2/scene2-bg.png", 180, 120);
    Object o2 = createObject("./image/page2/changePass/change-bg.png", 340, 279);
    Object o3 = createObject("./image/page2/changePass/change-button.png", 589, 606);
    // o4 is old pass
    Object o4 = createObject("./image/page2/changePass/new-pass.png", 641, 432.0f);
    Object o5 = createObject("./image/page2/changePass/new-pass.png", 641, 522.0f);
    Object o6 = createObject("./image/page2/changePass/change.png", 429, 343);
    Object o7 = createObject("./image/page2/open.png", 1003, 443);
    Object o8 = createObject("./image/page2/closed.png", 1003, 443);
    Object o9 = createObject("./image/page2/open.png", 1003, 533);
    Object o10 = createObject("./image/page2/closed.png", 1003, 533);

    Info oldPassword = createText("", 665.0f, 432.0f);
    Info newPassword = createText("", 665.0f, 522.0f);

    bool isTypingOld = false, isTypingNew = false;
    bool seeOld = false, seeNew = false;
    bool Change = false;
    Clock clock;

    string old_pass = "", new_pass = "", hidden_old = "", hidden_new = "";

    while (window.isOpen() && page == 20)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (isHere(o4.bound, mouse))
                    {
                        isTypingOld = true;
                        isTypingNew = false;
                        if (!seeOld)
                            oldPassword.txt.setString(hidden_old);
                        else
                            oldPassword.txt.setString(old_pass);
                        if (isHere(o7.bound, mouse))
                        {
                            seeOld = true;
                            oldPassword.txt.setString(old_pass);
                        }
                        else if (isHere(o8.bound, mouse))
                        {
                            seeOld = false;
                            oldPassword.txt.setString(hidden_old);
                        }
                    }
                    else if (isHere(o5.bound, mouse))
                    {
                        isTypingNew = true;
                        isTypingOld = false;
                        if (!seeNew)
                            newPassword.txt.setString(hidden_new);
                        else
                            newPassword.txt.setString(new_pass);
                        if (isHere(o9.bound, mouse))
                        {
                            seeNew = true;
                            newPassword.txt.setString(new_pass);
                        }
                        else if (isHere(o8.bound, mouse))
                        {
                            seeNew = false;
                            newPassword.txt.setString(hidden_new);
                        }
                    }
                    // we confirm the change successfully
                    else if (isHere(o3.bound, mouse))
                    {
                        Change = true;
                        clock.restart();
                    }
                    else if (isHere(b.bound, mouse))
                        page = 19;
                    else
                    {
                        isTypingOld = false;
                        isTypingNew = false;
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                if (isTypingOld)
                {
                    if (event.text.unicode < 128)
                    {
                        if (event.text.unicode == 8)
                        {
                            if (!old_pass.empty() && !hidden_old.empty())
                            {
                                old_pass.pop_back();
                                hidden_old.pop_back();
                            }
                        }
                        else if (event.text.unicode == 13)
                            isTypingOld = false;
                        else if (event.text.unicode >= 32)
                        {
                            old_pass += static_cast<char>(event.text.unicode);
                            hidden_old += '*';
                        }
                        if (seeOld)
                            oldPassword.txt.setString(old_pass + '_');
                        else
                            oldPassword.txt.setString(hidden_old + '_');
                    }
                }
                else if (isTypingNew)
                {
                    if (event.text.unicode < 128)
                    {
                        if (event.text.unicode == 8)
                        {
                            if (!new_pass.empty() && !hidden_new.empty())
                            {
                                new_pass.pop_back();
                                hidden_new.pop_back();
                            }
                        }
                        else if (event.text.unicode == 13)
                            isTypingNew = false;
                        else if (event.text.unicode >= 32)
                        {
                            new_pass += static_cast<char>(event.text.unicode);
                            hidden_new += '*';
                        }
                        if (seeNew)
                            newPassword.txt.setString(new_pass + '_');
                        else
                            newPassword.txt.setString(hidden_new + '_');
                    }
                }
                break;
            }
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(o2.draw);
        window.draw(o3.draw);
        window.draw(o4.draw);
        window.draw(o5.draw);
        window.draw(oldPassword.txt);
        window.draw(newPassword.txt);
        if (seeOld)
            window.draw(o8.draw);
        else
            window.draw(o7.draw);
        if (seeNew)
            window.draw(o10.draw);
        else
            window.draw(o9.draw);
        window.draw(f.draw);
        window.draw(b.draw);
        if (Change)
            window.draw(o6.draw);
        if (Change && clock.getElapsedTime().asSeconds() >= 3)
            Change = false;
        window.display();
    }
}

void Study(RenderWindow &window, int &page, bool is_staff)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/home/homeStaff-bg.png", 180, 120);
}
void Classes(RenderWindow &window, int &page, bool is_staff)
{
}
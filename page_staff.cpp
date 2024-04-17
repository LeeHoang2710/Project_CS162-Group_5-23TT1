#include "./struct_and_function/view_function.h"

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
        updateColorOnHover(window, o2);
        updateColorOnHover(window, o3);
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

void logIn(RenderWindow &window, int &page, bool is_staff, bool see, StaffNode *user3, string &name, string &pass, StaffNode *&user, StudentNode *&user1, ClassNode* class_list)
{

    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page2/scene2-bg.png", 180, 120);
    Object o2 = createObject("./image/page2/login-bg.png", 340, 282);
    Object o3 = createObject("./image/page2/login-button.png", 589, 608);
    Object o4 = createObject("./image/page2/username.png", 604, 435);
    Object o5 = createObject("./image/page2/password.png", 603, 525);
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
        updateColorOnHover(window, o3);
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
                        if (is_staff && LoginForStaff(user3, name, pass))
                        {
                            log_in = true;
                            page = 3;
                            user = searchStaffNode(user3, name);
                        }
                        else
                        {
                            log_in = false;
                            page = 4;
                            user1 = searchStudentNode(class_list, name);
                        }

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
                        inputUsername.txt.setString(username + '|');
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
                            inputPassword.txt.setString(password + '|');
                        else
                            inputPassword.txt.setString(hidden_pass + '|');
                    }
                }
                break;
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

void homeStaff(RenderWindow &window, int &page, StaffNode *&user, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/home/homeStaff-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/home/year.png", 235, 348);
    Object o3 = createObject("./image/page3-staff/home/class.png", 235, 462);
    Object o4 = createObject("./image/page3-staff/home/other.png", 235, 580);
    ;
    while (window.isOpen() && page == 3)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, o2);
        updateColorOnHover(window, o3);
        updateColorOnHover(window, o4);
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
                    switchPage(o2.bound, mouse, 5, page, Exit);
                    switchPage(o3.bound, mouse, 6, page, Exit);
                    switchPage(o4.bound, mouse, 7, page, Exit);
                }
                break;
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
        window.draw(o4.draw);
        window.display();
    }
}

void School(RenderWindow &window, int &page, bool is_staff, YearNode *&year, ClassNode *&class_list, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object o1 = createObject("./image/page3-staff/school_year/year-bg.png", 180, 120);
    Object create = createObject("./image/page3-staff/school_year/create_yr.png", 263, 259);
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object sum = createObject("./image/page3-staff/school_year/total.png", 946, 258);
    Object alert = createObject("./image/page3-staff/school_year/add-1st-class-bg.png", 301, 295);
    Object path = createObject("./image/page3-staff/school_year/file-path.png", 539, 482);
    Object import = createObject("./image/page3-staff/school_year/import.png", 589, 591);
    Object exit = createObject("./image/page2/exit.png", 1070, 305);
    Object valid = createObject("./image/page2/import-succ.png", 423, 351);
    Object invalid = createObject("./image/page2/invalid-path.png", 423, 351);
    Info total = createText("", 1050, 258);
    Info file = createText("", 560, 490);
    Object *add[4]{};
    Info *id[4]{};
    YearNode *one[4];
    for (int i = 0; i < 4; ++i)
    {
        createObjectTest(add[i], "./image/page3-staff/school_year/year-node.png", 235, 117 * i + 347);
        createInfoTest(id[i], "", 316, 117 * i + 354);
        id[i]->txt.setFillColor(Color::Yellow);
        id[i]->txt.setStyle(Text::Bold);
    }

    bool new_page = true, new_class = false, typing_path = false, Import = false, showImportResult = false;
    bool checkPath = false;
    Clock clock;
    YearNode *target = nullptr;
    string str = "", file_path = "";
    int count = 0, change = 0;
    for (YearNode *curr = year; curr; curr = curr->next)
        count++;
    while (window.isOpen() && page == 5)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, create);
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
        updateColorOnHover(window, menu);
        for (int i = 0; i < 4; ++i)
        {
            Object &addRef = *add[i];
            updateColorOnHover(window, addRef);
        }
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

                    switchPage(b.bound, mouse, 3, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    if (isHere(create.bound, mouse))
                    {
                        YearNode *curr = year;
                        while (curr->next)
                            curr = curr->next;
                        str = curr->school_year.year_id;
                        stringstream input(str);
                        int start, end;
                        char dash;
                        input >> start >> dash >> end;
                        str = to_string(start + 1) + dash + to_string(end + 1);

                        Year new_year = createYear(str, nullptr);
                        new_year.list_sem = nullptr;
                        addNewYearNode(year, new_year);
                        count++;
                        new_page = true;
                    }
                    if (isHere(prev.bound, mouse) && change != 0)
                    {
                        new_page = true;
                        change -= 4;
                    }
                    if (isHere(next.bound, mouse))
                    {
                        new_page = true;
                        change += 4;
                    }
                    if (isHere(exit.bound, mouse))
                        new_class = false;
                    if (isHere(import.bound, mouse))
                    {
                        Import = true;
                        clock.restart();
                        showImportResult = true;
                    }
                    if (isHere(path.bound, mouse))
                    {
                        typing_path = true;
                        file.txt.setString(file_path);
                    }
                    for (int i = 0; i < 4; ++i)
                    {
                        if (isHere(add[i]->bound, mouse) && one[i] && !new_class)
                        {

                            if (!one[i]->school_year.classSublist)
                            {
                                new_class = true;
                                target = one[i];
                            }
                            else
                            {
                                page = 11;
                                Semesters(window, page, one[i], class_list, Exit);
                                if (Exit)
                                    return;
                            }
                        }
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                Typing(typing_path, file, file_path, event);
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        total.txt.setString(to_string(count) + " years");
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(create.draw);
        window.draw(b.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(menu.draw);
        window.draw(sum.draw);
        window.draw(total.txt);
        if (new_page && year)
        {
            YearNode *temp = year;
            for (int i = 0; i < change; ++i)
                temp = temp->next;
            for (int i = 0; i < 4; ++i)
            {
                if (temp)
                {
                    one[i] = temp;
                    id[i]->txt.setString(one[i]->school_year.year_id);
                    temp = temp->next;
                }
                else
                    id[i]->txt.setString("");
            }
            new_page = false;
        }

        for (int i = 0; i < 4; ++i)
        {
            if (id[i]->txt.getString() == "")
                break;
            window.draw(add[i]->draw);
            window.draw(id[i]->txt);
        }
        if (new_class)
        {
            window.draw(alert.draw);
            window.draw(path.draw);
            window.draw(import.draw);
            window.draw(exit.draw);
            if (typing_path)
                window.draw(file.txt);
            if (Import)
            {
                ifstream fin;
                checkPath = importNewClassesFromStaff(target, class_list, file_path, fin);
                Import = false;
            }
            if (showImportResult && clock.getElapsedTime().asSeconds() < 3)
                chooseDraw_2(window, valid, invalid, checkPath);
            else if (clock.getElapsedTime().asSeconds() >= 3)
                showImportResult = false;
        }

        window.display();
    }
    for (int i = 0; i < 4; ++i)
        delete add[i], id[i]; // one[i];
}

void Semesters(RenderWindow &window, int &page, YearNode *&year, ClassNode *class_list, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/school_year/semester-bg.png", 180, 120);
    Object create = createObject("./image/page3-staff/school_year/create_sem.png", 263, 259);
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object *add[3]{};
    Info *id[3]{};
    SemesterNode *sem[3];
    for (int i = 0; i < 3; ++i)
    {
        createObjectTest(add[i], "./image/page3-staff/school_year/year-node.png", 235, 117 * i + 347);
        createInfoTest(id[i], "", 316, 117 * i + 354);
        id[i]->txt.setFillColor(Color::Yellow);
        id[i]->txt.setStyle(Text::Bold);
    }
    while (window.isOpen() && page == 11)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, create);
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
        updateColorOnHover(window, menu);
        for (int i = 0; i < 3; ++i)
        {
            Object &addRef = *add[i];
            updateColorOnHover(window, addRef);
        }
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
                    switchPage(b.bound, mouse, 5, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    if (isHere(create.bound, mouse))
                    {
                        page = 12;
                        addSemester(window, year, page, Exit);
                        if (Exit)
                            return;
                    }
                    for (int i = 0; i < 3; ++i)
                    {
                        if (isHere(add[i]->bound, mouse) && sem[i])
                        {
                            page = 13;
                            Courses(window, sem[i]->sem.course_list, page, year->school_year.year_id, sem[i]->sem.semester_id, class_list, Exit);
                            if (Exit)
                                return;
                        }
                    }
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(create.draw);
        window.draw(b.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(menu.draw);
        SemesterNode *temp = year->school_year.list_sem;
        for (int i = 0; i < 3; ++i)
        {
            if (temp)
            {
                sem[i] = temp;
                id[i]->txt.setString(sem[i]->sem.semester_id);
                temp = temp->next;
            }
            else
                id[i]->txt.setString("");
        }
        for (int i = 0; i < 3; ++i)
        {
            if (id[i]->txt.getString() == "")
                break;
            window.draw(add[i]->draw);
            window.draw(id[i]->txt);
        }
        window.display();
    }
    for (int i = 0; i < 3; ++i)
        delete add[i], id[i];
}

void addSemester(RenderWindow &window, YearNode *&check, int &page, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/school_year/new-semester-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/school_year/input.png", 465, 380);
    Object o3 = createObject("./image/page3-staff/school_year/input.png", 465, 446);
    Object o4 = createObject("./image/page3-staff/school_year/input.png", 465, 513);
    Object o5 = createObject("./image/page3-staff/school_year/input.png", 465, 579);
    Object append = createObject("./image/page3-staff/school_year/add.png", 384, 260);
    Object saved = createObject("./image/page3-staff/school_year/save-success.png", 418, 372);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Clock clock;
    bool typing_sem = false, typing_st = false, typing_e = false, save = false;
    Info t2 = createText("", 480, 385);
    Info t3 = createText(check->school_year.year_id, 480, 451);
    Info t4 = createText("", 480, 518);
    Info t5 = createText("", 480, 584);
    string sem_id, start, end;

    while (window.isOpen() && page == 12)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, append);
        updateColorOnHover(window, menu);
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
                    switchPage(b.bound, mouse, 5, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    if (isHere(o2.bound, mouse))
                    {
                        typing_sem = true;
                        typing_e = false;
                        typing_st = false;
                        t2.txt.setString(sem_id);
                    }
                    else if (isHere(o4.bound, mouse))
                    {
                        typing_st = true;
                        typing_e = false;
                        typing_sem = false;
                        t4.txt.setString(start);
                    }
                    else if (isHere(o5.bound, mouse))
                    {
                        typing_e = true;
                        typing_st = false;
                        typing_sem = false;
                        t5.txt.setString(end);
                    }
                    else if (isHere(append.bound, mouse))
                    {
                        if (sem_id >= "1" && sem_id <= "3")
                            sem_id = "Semester " + sem_id;
                        Semester new_sem = createSemester(sem_id, start, end);
                        appendSemesterNode(check->school_year.list_sem, new_sem);
                        save = true;
                        clock.restart();
                    }
                    else
                    {
                        typing_sem = false;
                        typing_st = false;
                        typing_e = false;
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                Typing(typing_sem, t2, sem_id, event);
                Typing(typing_st, t4, start, event);
                Typing(typing_e, t5, end, event);
                break;
            }
            default:
                break;
            }

            window.clear();
            window.draw(screen.draw);
            window.draw(o1.draw);
            window.draw(o2.draw);
            window.draw(o3.draw);
            window.draw(o4.draw);
            window.draw(o5.draw);
            window.draw(t2.txt);
            window.draw(t3.txt);
            window.draw(t4.txt);
            window.draw(t5.txt);
            window.draw(b.draw);
            window.draw(menu.draw);
            window.draw(append.draw);
            objectAppear(window, save, clock, saved, 2);
            window.display();
        }
    }
}

void Courses(RenderWindow &window, CourseNode *&course, int &page, string &yr, string &sem, ClassNode *class_list, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object create = createObject("./image/page3-staff/course/create-cour.png", 260, 258);
    Object del = createObject("./image/page3-staff/course/delete-cour.png", 589, 258);
    Object sum = createObject("./image/page3-staff/school_year/total.png", 946, 258);
    Object o1 = createObject("./image/page3-staff/course/course-bg.png", 180, 120);

    Object o2 = createObject("./image/page3-staff/course/delete-bg.png", 301, 385);
    Object exit = createObject("./image/page2/exit.png", 1044, 398);
    Object id = createObject("./image/page3-staff/course/id.png", 539, 484);
    Object confirm = createObject("./image/page3-staff/course/confirm.png", 583, 566);
    Object valid = createObject("./image/page2/delete-succ.png", 423, 351);
    Object invalid = createObject("./image/page2/invalid-id.png", 423, 351);
    Info total = createText("", 1050, 258);
    Info title = createText(yr + " - " + sem, 475, 168);
    Info kill = createText("", 560, 490);
    Object *subject[4]{};
    Info *inf[4]{};
    CourseNode *one[4];
    for (int i = 0; i < 4; ++i)
    {
        createObjectTest(subject[i], "./image/page3-staff/school_year/year-node.png", 235, 117 * i + 347);
        createInfoTest(inf[i], "", 316, 117 * i + 354);
        inf[i]->txt.setFillColor(Color::Yellow);
        inf[i]->txt.setStyle(Text::Bold);
    }
    bool new_page = true, del_course = false, typing_id = false, showDelResult = false;
    bool Confirm = false, checkDel = false;
    int count = 0, change = 0;
    string cour_id = "";
    Clock clock;
    for (CourseNode *curr = course; curr; curr = curr->next)
        count++;
    while (window.isOpen() && page == 13)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, create);
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
        updateColorOnHover(window, menu);
        updateColorOnHover(window, del);
        for (int i = 0; i < 4; ++i)
        {
            Object &subjectRef = *subject[i];
            updateColorOnHover(window, subjectRef);
        }
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
                    switchPage(b.bound, mouse, 11, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    if (isHere(create.bound, mouse))
                    {
                        page = 14;
                        addCourse(window, course, page, yr, sem, class_list, Exit);
                        if (Exit)
                            return;
                    }
                    if (isHere(prev.bound, mouse) && change != 0)
                    {
                        new_page = true;
                        change -= 4;
                    }
                    if (isHere(next.bound, mouse))
                    {
                        new_page = true;
                        change += 4;
                    }
                    if (isHere(del.bound, mouse))
                        del_course = true;
                    if (isHere(id.bound, mouse))
                    {
                        typing_id = true;
                        kill.txt.setString(cour_id);
                    }
                    if (isHere(exit.bound, mouse))
                        del_course = false;
                    if (isHere(confirm.bound, mouse))
                    {
                        Confirm = true;
                        showDelResult = true;
                        clock.restart();
                    }
                    for (int i = 0; i < 4; ++i)
                    {
                        if (isHere(subject[i]->bound, mouse) && one[i] && !del_course)
                        {
                            page = 15;
                            updateCourse(window, one[i], page, yr, sem, class_list, Exit);
                            if (Exit)
                                return;
                        }
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                Typing(typing_id, kill, cour_id, event);
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(create.draw);
        window.draw(del.draw);
        window.draw(sum.draw);
        window.draw(b.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(menu.draw);
        total.txt.setString(to_string(count) + " courses");
        window.draw(total.txt);
        window.draw(title.txt);
        if (new_page && course)
        {
            CourseNode *temp = course;
            for (int i = 0; i < change; ++i)
                temp = temp->next;
            for (int i = 0; i < 4; ++i)
            {
                if (temp)
                {
                    one[i] = temp;
                    inf[i]->txt.setString(one[i]->course.course_id + " - " + one[i]->course.course_name + " - " + one[i]->course.main_class->my_class.class_id);
                    temp = temp->next;
                }
                else
                    inf[i]->txt.setString("");
            }
            new_page = false;
        }
        for (int i = 0; i < 4; ++i)
        {
            if (inf[i]->txt.getString() == "")
                break;
            window.draw(subject[i]->draw);
            window.draw(inf[i]->txt);
        }
        if (del_course)
        {
            window.draw(o2.draw);
            window.draw(id.draw);
            window.draw(confirm.draw);
            window.draw(exit.draw);
            if (typing_id)
                window.draw(kill.txt);
            if (Confirm)
            {
                checkDel = deleteCourseNode(course, cour_id, yr, sem);
                count--;
                Confirm = false;
            }
            if (showDelResult && clock.getElapsedTime().asSeconds() < 3)
                chooseDraw_2(window, valid, invalid, checkDel);
            else if (clock.getElapsedTime().asSeconds() >= 3)
                showDelResult = false;
        }
        window.display();
    }
    for (int i = 0; i < 4; ++i)
        delete subject[i], inf[i];
}

void addCourse(RenderWindow &window, CourseNode *&course, int &page, string yr, string sem, ClassNode *class_list, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object append = createObject("./image/page3-staff/school_year/add.png", 319, 258);
    Object import = createObject("./image/page3-staff/course/import.png", 534, 258);
    Object o1 = createObject("./image/page3-staff/course/create-cour-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/course/input.png", 497, 377);
    Object o3 = createObject("./image/page3-staff/course/input.png", 497, 438);
    Object o4 = createObject("./image/page3-staff/course/input.png", 497, 499);
    Object o5 = createObject("./image/page3-staff/course/input.png", 497, 560);
    Object o6 = createObject("./image/page3-staff/course/input_1.png", 506, 620);
    Object o7 = createObject("./image/page3-staff/course/input_1.png", 965, 620);

    Object valid2 = createObject("./image/page3-staff/school_year/save-success.png", 423, 351);
    Object invalid2 = createObject("./image/page3-staff/class/invalid_sea.png", 423, 351);
    Clock clock;
    bool typing_id = false, typing_name = false, typing_class = false, typing_teacher = false, typing_num = false, typing_cre = false;

    bool save = false, check_class = false;

    Info *inf[4]{};
    Object *yes[6]{}, *no[6]{}, *yes_sess[4]{}, *no_sess[4]{};
    bool check_day[6], check_sess[4];
    for (int i = 0; i < 4; ++i)
    {
        createInfoTest(inf[i], "", 512, 377 + 61 * i);
        createObjectTest(yes_sess[i], "./image/page3-staff/course/yes.png", 398 + 185 * i, 732);
        createObjectTest(no_sess[i], "./image/page3-staff/course/no.png", 398 + 185 * i, 732);
        check_sess[i] = false;
    }
    for (int i = 0; i < 6; ++i)
    {
        createObjectTest(yes[i], "./image/page3-staff/course/yes.png", 326 + 130 * i, 672 + 15);
        createObjectTest(no[i], "./image/page3-staff/course/no.png", 326 + 130 * i, 672 + 15);
        check_day[i] = false;
    }
    Info stu = createText("", 525, 625);
    Info cre = createText("", 985, 625);
    string cour_id, cour_name, classes, teacher, num, credit;
    int day = 0, sess = 0;
    while (window.isOpen() && page == 14)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, append);
        updateColorOnHover(window, import);
        updateColorOnHover(window, menu);
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
                    switchPage(b.bound, mouse, 13, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    for (int i = 0; i < 6; ++i)
                    {
                        if (isHere(no[i]->bound, mouse))
                        {
                            check_day[i] = true;
                            day = i + 2;
                        }
                        else if (isHere(yes[i]->bound, mouse))
                        {
                            check_day[i] = false;
                            day = 0;
                        }
                    }
                    for (int i = 0; i < 4; ++i)
                    {
                        if (isHere(no_sess[i]->bound, mouse))
                        {
                            check_sess[i] = true;
                            sess = i + 1;
                        }
                        else if (isHere(yes_sess[i]->bound, mouse))
                        {
                            check_sess[i] = false;
                            sess = 0;
                        }
                    }
                    if (isHere(o2.bound, mouse))
                    {
                        typing_id = true;
                        typing_class = false;
                        typing_teacher = false;
                        typing_name = false;
                        typing_num = false;
                        typing_cre = false;
                        inf[0]->txt.setString(cour_id);
                    }
                    else if (isHere(o3.bound, mouse))
                    {
                        typing_name = true;
                        typing_id = false;
                        typing_class = false;
                        typing_teacher = false;
                        typing_num = false;
                        typing_cre = false;
                        inf[1]->txt.setString(cour_name);
                    }
                    else if (isHere(o4.bound, mouse))
                    {
                        typing_class = true;
                        typing_name = false;
                        typing_id = false;
                        typing_teacher = false;
                        typing_num = false;
                        typing_cre = false;
                        inf[2]->txt.setString(classes);
                    }
                    else if (isHere(o5.bound, mouse))
                    {
                        typing_teacher = true;
                        typing_id = false;
                        typing_name = false;
                        typing_class = false;
                        typing_num = false;
                        typing_cre = false;
                        inf[3]->txt.setString(teacher);
                    }
                    else if (isHere(o6.bound, mouse))
                    {
                        typing_num = true;
                        typing_id = false;
                        typing_name = false;
                        typing_class = false;
                        typing_teacher = false;
                        typing_cre = false;
                        stu.txt.setString(num);
                    }
                    else if (isHere(o7.bound, mouse))
                    {
                        typing_cre = true;
                        typing_id = false;
                        typing_name = false;
                        typing_class = false;
                        typing_teacher = false;
                        typing_num = false;
                        cre.txt.setString(credit);
                    }
                    else if (isHere(append.bound, mouse))
                    {
                        save = true;
                        Session s1;
                        s1.day_of_the_week = day;
                        s1.session_no = sess;
                        Course new_cour = createCourse(cour_id, cour_name, teacher, stoi(credit), stoi(num), s1, classes, class_list);
                        if (!new_cour.main_class)
                            check_class = false;
                        else
                        {
                            addResultsNodeToClass(new_cour.main_class, yr, sem, cour_id);
                            appendNewCourseNode(course, new_cour);
                            check_class = true;
                        }

                        clock.restart();
                    }
                    else
                    {
                        typing_id = false;
                        typing_name = false;
                        typing_class = false;
                        typing_teacher = false;
                        typing_num = false;
                        typing_cre = false;
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                Typing(typing_id, *inf[0], cour_id, event);
                Typing(typing_name, *inf[1], cour_name, event);
                Typing(typing_class, *inf[2], classes, event);
                Typing(typing_teacher, *inf[3], teacher, event);
                Typing(typing_num, stu, num, event);
                Typing(typing_cre, cre, credit, event);
                break;
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
        window.draw(o4.draw);
        window.draw(o5.draw);
        window.draw(o6.draw);
        window.draw(o7.draw);
        window.draw(b.draw);
        window.draw(menu.draw);
        window.draw(append.draw);
        window.draw(import.draw);
        window.draw(stu.txt);
        window.draw(cre.txt);
        for (int i = 0; i < 4; ++i)
        {
            window.draw(inf[i]->txt);
            chooseDraw_1(window, yes_sess[i], no_sess[i], check_sess[i]);
        }
        for (int i = 0; i < 6; ++i)
            chooseDraw_1(window, yes[i], no[i], check_day[i]);
        if (check_class)
            objectAppear(window, save, clock, valid2, 2);
        else
            objectAppear(window, save, clock, invalid2, 2);
        window.display();
    }
    for (int i = 0; i < 4; ++i)
        delete inf[i], yes_sess[i], no_sess[i];
    for (int i = 0; i < 6; ++i)
        delete yes[i], no[i];
}

void updateCourse(RenderWindow &window, CourseNode *&course, int &page, string yr, string sem, ClassNode *class_list, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);

    Object edit = createObject("./image/page3-staff/course/update/edit.png", 883, 158);
    Object update = createObject("./image/page3-staff/course/update/save.png", 1042, 158);
    Object import = createObject("./image/page3-staff/course/update/import-res.png", 639, 258);
    Object result = createObject("./image/page3-staff/course/update/result.png", 839, 258);
    Object view = createObject("./image/page3-staff/course/update/view.png", 1036, 258);
    Object arrow = createObject("./image/page3-staff/course/update/arrow.png", 826, 265);
    Object append = createObject("./image/page3-staff/course/update/add-stu.png", 285, 258);

    Object add = createObject("./image/page3-staff/course/update/add-stu-bg.png", 301, 385);
    Object exit2 = createObject("./image/page2/exit.png", 1044, 398);
    Object id = createObject("./image/page3-staff/course/id.png", 539, 484);
    Object confirm = createObject("./image/page3-staff/course/update/confirm.png", 583, 566);

    Object o1 = createObject("./image/page3-staff/course/update/update-cour-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/course/input.png", 497, 377);
    Object o3 = createObject("./image/page3-staff/course/input.png", 497, 438);
    Object o4 = createObject("./image/page3-staff/course/input.png", 497, 499);
    Object o5 = createObject("./image/page3-staff/course/input.png", 497, 560);
    Object o6 = createObject("./image/page3-staff/course/input_1.png", 506, 620);
    Object o7 = createObject("./image/page3-staff/course/input_1.png", 965, 620);

    Object alert = createObject("./image/page3-staff/course/update/import-bg.png", 301, 295);
    Object path = createObject("./image/page3-staff/school_year/file-path.png", 539, 482);
    Object button = createObject("./image/page3-staff/school_year/import.png", 589, 591);
    Object exit = createObject("./image/page2/exit.png", 1070, 305);
    Object valid1 = createObject("./image/page2/import-succ.png", 423, 351);
    Object invalid1 = createObject("image/page2/invalid-path.png", 423, 351);

    Object valid2 = createObject("./image/page3-staff/school_year/save-success.png", 423, 351);
    Object invalid2 = createObject("./image/page3-staff/class/invalid_sea.png", 423, 351);

    Object valid3 = createObject("./image/page3-staff/course/update/add-succ.png", 423, 351);
    Object invalid3 = createObject("./image/page2/invalid-id.png", 423, 351);

    Clock clock;
    bool typing_id = false, typing_name = false, typing_class = false, typing_teacher = false, typing_num = false, typing_cre = false;
    bool editing = false, resulting = false, save = false, check_class = false;

    bool new_stu = false, typing_path = false, Import = false, showImportResult = false, checkPath = false;
    bool one_stu = false, typing_stu = false, showAddResult = false, checkAdd = false;

    Info *inf[4]{};
    Object *yes[6]{}, *no[6]{}, *yes_sess[4]{}, *no_sess[4]{};
    bool check_day[6], check_sess[4];
    for (int i = 0; i < 4; ++i)
    {
        createInfoTest(inf[i], "", 512, 377 + 61 * i);
        createObjectTest(yes_sess[i], "./image/page3-staff/course/yes.png", 398 + 185 * i, 732);
        createObjectTest(no_sess[i], "./image/page3-staff/course/no.png", 398 + 185 * i, 732);
        check_sess[i] = false;
    }
    for (int i = 0; i < 6; ++i)
    {
        createObjectTest(yes[i], "./image/page3-staff/course/yes.png", 326 + 130 * i, 672 + 15);
        createObjectTest(no[i], "./image/page3-staff/course/no.png", 326 + 130 * i, 672 + 15);
        check_day[i] = false;
    }
    Info stu = createText(to_string(course->course.max_students), 525, 625);
    Info cre = createText(to_string(course->course.num_credit), 985, 625);
    Info file = createText("", 560, 490);
    Info born = createText("", 560, 490);
    string cour_id, cour_name, classes, teacher, num, credit;
    string file_path = "", stu_id = "";
    int day = 0, sess = 0;
    while (window.isOpen() && page == 15)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, menu);
        updateColorOnHover(window, update);
        updateColorOnHover(window, edit);
        updateColorOnHover(window, result);
        updateColorOnHover(window, import);
        updateColorOnHover(window, append);
        updateColorOnHover(window, view);

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
                    switchPage(b.bound, mouse, 13, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    if (isHere(append.bound, mouse))
                        one_stu = true;
                    if (isHere(exit2.bound, mouse))
                        one_stu = false;
                    if (isHere(id.bound, mouse))
                    {
                        typing_stu = true;
                        born.txt.setString(stu_id);
                    }
                    if (isHere(confirm.bound, mouse))
                    {
                        showAddResult = true;
                        clock.restart();
                    }

                    if (isHere(edit.bound, mouse))
                        editing = true;
                    if (editing)
                    {
                        for (int i = 0; i < 6; ++i)
                        {
                            if (isHere(no[i]->bound, mouse))
                            {
                                check_day[i] = !check_day[i];
                                day = check_day[i] ? i + 2 : 0;
                            }
                            else if (isHere(yes[i]->bound, mouse))
                            {
                                check_day[i] = !check_day[i];
                                day = check_day[i] ? 0 : i + 2;
                            }
                        }
                        for (int i = 0; i < 4; ++i)
                        {
                            if (isHere(no_sess[i]->bound, mouse))
                            {
                                check_sess[i] = !check_sess[i];
                                sess = check_sess[i] ? i + 1 : 0;
                            }
                            else if (isHere(yes_sess[i]->bound, mouse))
                            {
                                check_sess[i] = !check_sess[i];
                                sess = check_sess[i] ? 0 : i + 1;
                            }
                        }
                        if (isHere(o2.bound, mouse))
                        {
                            typing_id = true;
                            typing_class = false;
                            typing_teacher = false;
                            typing_name = false;
                            typing_num = false;
                            typing_cre = false;
                            inf[0]->txt.setString(cour_id);
                        }
                        else if (isHere(o3.bound, mouse))
                        {
                            typing_name = true;
                            typing_id = false;
                            typing_class = false;
                            typing_teacher = false;
                            typing_num = false;
                            typing_cre = false;
                            inf[1]->txt.setString(cour_name);
                        }
                        else if (isHere(o4.bound, mouse))
                        {
                            typing_class = true;
                            typing_name = false;
                            typing_id = false;
                            typing_teacher = false;
                            typing_num = false;
                            typing_cre = false;
                            inf[2]->txt.setString(classes);
                        }
                        else if (isHere(o5.bound, mouse))
                        {
                            typing_teacher = true;
                            typing_id = false;
                            typing_name = false;
                            typing_class = false;
                            typing_num = false;
                            typing_cre = false;
                            inf[3]->txt.setString(teacher);
                        }
                        else if (isHere(o6.bound, mouse))
                        {
                            typing_num = true;
                            typing_id = false;
                            typing_name = false;
                            typing_class = false;
                            typing_teacher = false;
                            typing_cre = false;
                            stu.txt.setString(num);
                        }
                        else if (isHere(o7.bound, mouse))
                        {
                            typing_cre = true;
                            typing_id = false;
                            typing_name = false;
                            typing_class = false;
                            typing_teacher = false;
                            typing_num = false;
                            cre.txt.setString(credit);
                        }
                        else if (isHere(update.bound, mouse))
                        {
                            save = true;
                            Session s1;
                            s1.day_of_the_week = day;
                            s1.session_no = sess;
                            string temp = credit;
                            if (temp == "")
                                temp = "0";

                            if (num == "")
                                num = "0";

                            Course new_cour = createCourse(cour_id, cour_name, teacher, stoi(temp), stoi(num), s1, classes, class_list);
                            if (!classes.empty() && !new_cour.main_class)
                                check_class = false;
                            else
                            {
                                compareCourse(course->course, new_cour);
                                replaceCourse(course, new_cour, yr, sem);
                                check_class = true;
                            }

                            editing = false;
                            clock.restart();
                        }
                        else
                        {
                            typing_id = false;
                            typing_name = false;
                            typing_class = false;
                            typing_teacher = false;
                            typing_num = false;
                            typing_cre = false;
                        }
                    }
                    if (isHere(result.bound, mouse))
                        resulting = !resulting;
                    if (resulting && isHere(view.bound, mouse))
                    {
                        page = 16;
                        resultCourse(window, course, page, yr, sem);
                        if (Exit)
                            return;
                    }
                    if (isHere(import.bound, mouse) && resulting)
                        new_stu = true;
                    if (isHere(exit.bound, mouse))
                        new_stu = false;
                    if (isHere(path.bound, mouse))
                    {
                        typing_path = true;
                        file.txt.setString(file_path);
                    }
                    if (isHere(button.bound, mouse))
                    {
                        Import = true;
                        showImportResult = true;
                        clock.restart();
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                if (editing)
                {
                    Typing(typing_id, *inf[0], cour_id, event);
                    Typing(typing_name, *inf[1], cour_name, event);
                    Typing(typing_class, *inf[2], classes, event);
                    Typing(typing_teacher, *inf[3], teacher, event);
                    Typing(typing_num, stu, num, event);
                    Typing(typing_cre, cre, credit, event);
                }
                if (new_stu)
                    Typing(typing_path, file, file_path, event);
                if (one_stu)
                    Typing(typing_stu, born, stu_id, event);
                break;
            }
            default:
                break;
            }
        }
        if (!editing)
        {
            inf[0]->txt.setString(course->course.course_id);
            inf[1]->txt.setString(course->course.course_name);
            inf[2]->txt.setString(course->course.main_class->my_class.class_id);
            inf[3]->txt.setString(course->course.teacher_name);
            check_day[course->course.teaching_session.day_of_the_week - 2] = true;
            check_sess[course->course.teaching_session.session_no - 1] = true;
        }

        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(o2.draw);
        window.draw(o3.draw);
        window.draw(o4.draw);
        window.draw(o5.draw);
        window.draw(o6.draw);
        window.draw(o7.draw);
        window.draw(b.draw);
        window.draw(append.draw);
        window.draw(result.draw);
        if (editing)
            window.draw(update.draw);
        else
            window.draw(edit.draw);
        if (resulting)
        {
            window.draw(import.draw);
            window.draw(view.draw);
            window.draw(arrow.draw);
        }

        window.draw(menu.draw);
        window.draw(stu.txt);
        window.draw(cre.txt);
        for (int i = 0; i < 4; ++i)
        {
            window.draw(inf[i]->txt);
            chooseDraw_1(window, yes_sess[i], no_sess[i], check_sess[i]);
        }
        for (int i = 0; i < 6; ++i)
            chooseDraw_1(window, yes[i], no[i], check_day[i]);
        if (check_class)
            objectAppear(window, save, clock, valid2, 2);
        else
            objectAppear(window, save, clock, invalid2, 2);

        if (new_stu)
        {
            window.draw(alert.draw);
            window.draw(path.draw);
            window.draw(button.draw);
            window.draw(exit.draw);
            if (typing_path)
                window.draw(file.txt);
            if (Import)
            {
            }
        }

        if (one_stu)
        {
            window.draw(add.draw);
            window.draw(id.draw);
            window.draw(confirm.draw);
            window.draw(exit2.draw);
            if (typing_stu)
                window.draw(born.txt);
            if (showAddResult)
            {
                // checkAdd = addStudentToCourse(course, stu_id);
            }
            if (showAddResult && clock.getElapsedTime().asSeconds() < 3)
                chooseDraw_2(window, valid3, invalid3, checkAdd);
            else if (clock.getElapsedTime().asSeconds() >= 3)
                showAddResult = false;
        }

        window.display();
    }
    for (int i = 0; i < 4; ++i)
        delete inf[i], yes_sess[i], no_sess[i];
    for (int i = 0; i < 6; ++i)
        delete yes[i], no[i];
}

void resultCourse(RenderWindow &window, CourseNode *&course, int &page, string yr, string sem)
{
    Event event;
    Clock clock;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/course/update/res-cour-bg.png", 180, 120);
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object o2 = createObject("./image/page3-staff/result/gpa.png", 410, 721);
    Object eXport = createObject("./image/page3-staff/course/update/export.png", 822, 721);
    Object export_file = createObject("./image/page3-staff/course/update/file_path.png", 423, 351);
    Info name = createText(course->course.course_id + " - " + course->course.course_name + " - " + course->course.main_class->my_class.class_id, 216, 155);
    string destination = "";
    Info path = createText("", 490, 513);
    path.txt.setStyle(Text::Regular);
    path.txt.setCharacterSize(23);
    Info num = createText("", 460, 726);
    int count = 0, change = 0;
    for (StudentNode *curr = course->course.main_class->my_class.student_list; curr != nullptr; curr = curr->next)
        count++;
    num.txt.setString(to_string(count));
    bool new_page = true, success = false;
    StudentNode *stu_list = course->course.main_class->my_class.student_list;
    StudentNode *one[8];
    Info *res[8][6]{};
    for (int i = 0; i < 8; ++i)
    {
        createInfoTest(res[i][0], "", 220, 298 + 48 * i);
        createInfoTest(res[i][1], "", 405, 298 + 48 * i);
        createInfoTest(res[i][2], "", 690, 298 + 48 * i);
        createInfoTest(res[i][3], "", 835, 298 + 48 * i);
        createInfoTest(res[i][4], "", 980, 298 + 48 * i);
        createInfoTest(res[i][5], "", 1140, 298 + 48 * i);
        for (int j = 0; j < 6; ++j)
            res[i][j]->txt.setCharacterSize(24);
    }
    while (window.isOpen() && page == 16)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, menu);
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
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
                    if (isHere(menu.bound, mouse))
                    {
                        page = 15;
                        return;
                    }
                    if (isHere(prev.bound, mouse) && change != 0)
                    {
                        new_page = true;
                        change -= 8;
                    }
                    if (isHere(next.bound, mouse))
                    {
                        new_page = true;
                        change += 8;
                    }
                    if (isHere(eXport.bound, mouse))
                    {
                        ofstream op;
                        destination = "export";
                        ExportStudentTofile(op, destination, course);
                        success = true;
                        clock.restart();
                    }
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(menu.draw);
        window.draw(o2.draw);
        window.draw(eXport.draw);
        window.draw(name.txt);
        window.draw(num.txt);
        if (new_page && stu_list)
        {

            StudentNode *temp = stu_list;
            for (int i = 0; i < change; ++i)
                temp = temp->next;
            for (int i = 0; i < 8; ++i)
            {
                if (temp)
                {
                    one[i] = temp;
                    ResultsNode *temp_res = searchResultsNode(temp->student.results_list, course->course.course_id, yr, sem);

                    res[i][0]->txt.setString(one[i]->student.student_id);
                    res[i][1]->txt.setString(one[i]->student.last_name + " " + one[i]->student.first_name);
                    res[i][2]->txt.setString(to_string(one[i]->student.results_list->results.score.process).substr(0, 4));
                    res[i][3]->txt.setString(to_string(one[i]->student.results_list->results.score.midterm).substr(0, 4));
                    res[i][4]->txt.setString(to_string(one[i]->student.results_list->results.score.final).substr(0, 4));
                    res[i][5]->txt.setString(to_string(one[i]->student.results_list->results.score.overall).substr(0, 4));
                    temp = temp->next;
                }
                else
                    res[i][0]->txt.setString("");
            }
            new_page = false;
        }
        for (int i = 0; i < 8; ++i)
        {
            if (res[i][0]->txt.getString() == "")
                break;
            for (int j = 0; j < 7; ++j)
                window.draw(res[i][j]->txt);
        }
        if (success)
        {
            window.draw(export_file.draw);
            path.txt.setString(destination);
            window.draw(path.txt);
        }
        if (success && clock.getElapsedTime().asSeconds() >= 5)
            success = false;
        window.display();
    }
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 7; ++j)
            delete res[i][j];
}

void Other1(RenderWindow &window, int &page, StaffNode *&user, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/other/other-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/other/log-out.png", 230, 354);
    Object o3 = createObject("./image/page3-staff/other/change-pass.png", 230, 465);
    Object o4 = createObject("./image/page3-staff/other/profile.png", 230, 576);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    while (window.isOpen() && page == 7)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, menu);
        updateColorOnHover(window, o2);
        updateColorOnHover(window, o3);
        updateColorOnHover(window, o4);
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
                    switchPage(b.bound, mouse, 3, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    switchPage(o2.bound, mouse, 1, page, Exit);
                    switchPage(o3.bound, mouse, 21, page, Exit);
                    switchPage(o4.bound, mouse, 22, page, Exit);
                }
                break;
            }
            default:
                break;
            }

            window.clear();
            window.draw(screen.draw);
            window.draw(o1.draw);
            window.draw(o2.draw);
            window.draw(o3.draw);
            window.draw(o4.draw);
            window.draw(b.draw);
            window.draw(menu.draw);
            window.display();
        }
    }
}

void changePassword(RenderWindow &window, int &page, bool is_staff, StaffNode *&user, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page2/scene2-bg.png", 180, 120);
    Object o2 = createObject("./image/page2/changePass/change-bg.png", 340, 279);
    Object o3 = createObject("./image/page2/changePass/change-button.png", 589, 606);
    // o4 is old pass
    Object o4 = createObject("./image/page2/changePass/new-pass.png", 641, 432.0f);
    Object o5 = createObject("./image/page2/changePass/new-pass.png", 641, 522.0f);
    Object success = createObject("./image/page2/changePass/change.png", 429, 343);
    Object fail = createObject("./image/page2/changePass/try-again.png", 429, 343);
    Object o7 = createObject("./image/page2/open.png", 1003, 443);
    Object o8 = createObject("./image/page2/closed.png", 1003, 443);
    Object o9 = createObject("./image/page2/open.png", 1003, 533);
    Object o10 = createObject("./image/page2/closed.png", 1003, 533);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);

    Info oldPassword = createText("", 665.0f, 432.0f);
    Info newPassword = createText("", 665.0f, 522.0f);
    Info res = createText("", 1000, 700);

    bool isTypingOld = false, isTypingNew = false;
    bool seeOld = false, seeNew = false;
    bool Change = false;
    Clock clock;

    string old_pass = "", new_pass = "", hidden_old = "", hidden_new = "";

    while (window.isOpen() && page == 21)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, o3);
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
                    switchPage(b.bound, mouse, 7, page, Exit);
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
                        if (old_pass == user->staff.password)
                        {
                            user->staff.password = new_pass;
                            Change = true;
                        }
                        else
                            Change = false;
                        clock.restart();
                    }
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
                            oldPassword.txt.setString(old_pass + '|');
                        else
                            oldPassword.txt.setString(hidden_old + '|');
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
                            newPassword.txt.setString(new_pass + '|');
                        else
                            newPassword.txt.setString(hidden_new + '|');
                    }
                }
                break;
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
        window.draw(b.draw);
        objectAppear(window, Change, clock, success, 2);
        if (Change)
            res.txt.setString(user->staff.password);
        window.draw(res.txt);
        window.display();
    }
}

void Classes(RenderWindow &window, int &page, bool is_staff, ClassNode *class_list, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/class/class-bg.png", 180, 120);
    Object sum = createObject("./image/page3-staff/school_year/total.png", 946, 258);
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object sort = createObject("./image/page3-staff/class/search-cla.png", 270, 262);
    Object confirm = createObject("./image/page3-staff/class/confirm.png", 475, 264);
    Object inval = createObject("./image/page3-staff/class/invalid_sea.png", 423, 351);
    Info total = createText("", 1050, 258);
    Info sort_input = createText("", 330, 264);
    Object *add[4]{};
    Info *id[4]{};
    ClassNode *one[4];
    ClassSubNode *res = nullptr;
    for (int i = 0; i < 4; ++i)
    {
        createObjectTest(add[i], "./image/page3-staff/school_year/year-node.png", 235, 117 * i + 347);
        createInfoTest(id[i], "demo-text", 316, 117 * i + 354);
        id[i]->txt.setFillColor(Color::Yellow);
        id[i]->txt.setStyle(Text::Bold);
    }
    bool new_page = true, find_class = false;
    string input;
    int count = 0, change = 0;
    for (ClassNode *curr = class_list; curr; curr = curr->next)
        count++;
    while (window.isOpen() && page == 6)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, menu);
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
        for (int i = 0; i < 4; ++i)
        {
            Object &addRef = *add[i];
            updateColorOnHover(window, addRef);
        }
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

                    switchPage(b.bound, mouse, 3, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);

                    if (isHere(prev.bound, mouse) && change != 0)
                    {
                        new_page = true;
                        change -= 4;
                    }
                    if (isHere(next.bound, mouse))
                    {
                        new_page = true;
                        change += 4;
                    }
                    if (isHere(sort.bound, mouse))
                        find_class = true;
                    if (isHere(confirm.bound, mouse))
                    {
                        res = findClasses(class_list, input);
                        new_page = true;
                    }
                    for (int i = 0; i < 4; ++i)
                    {
                        if (isHere(add[i]->bound, mouse) && one[i])
                        {
                            page = 17;
                            Students(window, page, one[i], Exit);
                            if (Exit)
                                return;
                        }
                    }
                }
                break;
            }
            case Event::TextEntered:
                Typing(find_class, sort_input, input, event);
                break;
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(b.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(sum.draw);
        window.draw(menu.draw);
        window.draw(sort.draw);
        window.draw(confirm.draw);
        window.draw(sort_input.txt);
        if (new_page && class_list && !find_class)
        {
            ClassNode *temp = class_list;
            for (int i = 0; i < change; ++i)
                temp = temp->next;
            for (int i = 0; i < 4; ++i)
            {
                if (temp)
                {
                    one[i] = temp;
                    id[i]->txt.setString(one[i]->my_class.class_id);
                    temp = temp->next;
                }
                else
                    id[i]->txt.setString("");
            }
            new_page = false;
        }
        if (new_page && res && find_class)
        {
            ClassSubNode *temp = res;
            for (int i = 0; i < 4; ++i)
            {
                if (temp)
                {
                    one[i] = temp->class_node;
                    id[i]->txt.setString(one[i]->my_class.class_id);
                    temp = temp->next;
                }
                else
                    id[i]->txt.setString("");
            }
            new_page = false;
        }
        // else if (!res && find_class)
        // {
        //     window.draw(inval.draw);
        //     find_class = false;
        // }

        for (int i = 0; i < 4; ++i)
        {
            if (id[i]->txt.getString() == "")
                break;
            window.draw(add[i]->draw);
            window.draw(id[i]->txt);
        }
        window.display();
    }
    for (int i = 0; i < 4; ++i)
        delete add[i], id[i];
}

void Students(RenderWindow &window, int &page, ClassNode *&class_list, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object o1 = createObject("./image/page3-staff/class/student-bg.png", 180, 120);

    Object o2 = createObject("./image/page3-staff/class/result-bg.png", 180, 120);
    Object create = createObject("./image/page3-staff/class/create-stu.png", 270, 262);
    Object del = createObject("./image/page3-staff/class/delete-stu.png", 581, 262);
    Object eXport = createObject("./image/page3-staff/class/export.png", 910, 262);
    Object res = createObject("./image/page3-staff/class/result.png", 1080, 204);
    Object infor = createObject("./image/page3-staff/class/infor.png", 951, 204);

    Object o3 = createObject("./image/page3-staff/class/delete-bg.png", 301, 385);
    Object exit2 = createObject("./image/page2/exit.png", 1044, 398);
    Object id = createObject("./image/page3-staff/course/id.png", 539, 484);
    Object confirm = createObject("./image/page3-staff/course/confirm.png", 583, 566);
    Object valid1 = createObject("./image/page2/delete-succ.png", 423, 351);
    Object invalid1 = createObject("./image/page2/invalid-id.png", 423, 351);

    Object alert = createObject("./image/page3-staff/class/import-stu-bg.png", 301, 295);
    Object path = createObject("./image/page3-staff/school_year/file-path.png", 539, 482);
    Object import = createObject("./image/page3-staff/school_year/import.png", 589, 591);
    Object exit1 = createObject("./image/page2/exit.png", 1070, 305);
    Object valid2 = createObject("./image/page2/import-succ.png", 423, 351);
    Object invalid2 = createObject("./image/page2/invalid-path.png", 423, 351);

    Info title = createText("Class - " + class_list->my_class.class_id, 475, 168);
    Info kill = createText("", 560, 490);
    Info file = createText("", 560, 490);

    Info *stu[7][7]{};
    Info *resl[7][5]{};
    StudentNode *one[7];
    StudentNode *stu_list = class_list->my_class.student_list;
    for (int i = 0; i < 7; ++i)
    {
        createInfoTest(stu[i][0], "", 270, 426 + 48 * i);
        createInfoTest(stu[i][1], "", 342, 426 + 48 * i);
        createInfoTest(stu[i][2], "", 498, 426 + 48 * i);
        createInfoTest(stu[i][3], "", 595, 426 + 48 * i);
        createInfoTest(stu[i][4], "", 820, 426 + 48 * i);
        createInfoTest(stu[i][5], "", 895, 426 + 48 * i);
        createInfoTest(stu[i][6], "", 1050, 426 + 48 * i);
        createInfoTest(resl[i][0], "1", 270, 426 + 48 * i);
        createInfoTest(resl[i][1], "2", 342, 426 + 48 * i);
        createInfoTest(resl[i][2], "3", 498, 426 + 48 * i);
        createInfoTest(resl[i][3], "4", 790, 426 + 48 * i);
        createInfoTest(resl[i][4], "5", 972, 426 + 48 * i);

        for (int j = 0; j < 7; ++j)
            stu[i][j]->txt.setCharacterSize(24);
    }

    Object *detail[7]{};
    for (int i = 0; i < 7; ++i)
        createObjectTest(detail[i], "./image/page3-staff/class/detail.png", 1083, 426 + 48 * i);

    bool new_page = true, result = false, del_stu = false, typing_id = false, showDelResult = false;
    bool checkDel = false;

    bool new_stu = false, typing_path = false, Import = false, showImportResult = false, checkPath = false;
    Clock clock;
    string stu_id = "", file_path = "";
    int count = 0, change = 0;
    for (StudentNode *curr = stu_list; curr; curr = curr->next)
        count++;
    while (window.isOpen() && page == 17)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
        updateColorOnHover(window, menu);
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
        updateColorOnHover(window, create);
        updateColorOnHover(window, del);
        updateColorOnHover(window, eXport);
        updateColorOnHover(window, res);
        updateColorOnHover(window, infor);
        updateColorOnHover(window, import);
        updateColorOnHover(window, exit1);
        updateColorOnHover(window, exit2);
        for (int i = 0; i < 7; ++i)
        {
            Object &detailRef = *detail[i];
            updateColorOnHover(window, detailRef);
        }

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
                    switchPage(b.bound, mouse, 6, page, Exit);
                    switchPage(menu.bound, mouse, 3, page, Exit);
                    if (isHere(res.bound, mouse))
                        result = true;
                    else if (isHere(infor.bound, mouse))
                        result = false;
                    if (isHere(prev.bound, mouse) && change != 0)
                    {
                        new_page = true;
                        change -= 7;
                    }
                    if (isHere(exit2.bound, mouse))
                        del_stu = false;
                    if (isHere(next.bound, mouse))
                    {
                        new_page = true;
                        change += 7;
                    }
                    if (isHere(del.bound, mouse))
                        del_stu = true;
                    if (isHere(id.bound, mouse))
                    {
                        typing_id = true;
                        kill.txt.setString(stu_id);
                    }
                    if (isHere(confirm.bound, mouse))
                    {
                        showDelResult = true;
                        clock.restart();
                    }
                    if (result)
                    {
                        for (int i = 0; i < 7; ++i)
                        {
                            if (isHere(detail[i]->bound, mouse) && one[i])
                            {
                                page = 18;
                                studentResult(window, page, one[i]);
                                if (Exit)
                                    return;
                            }
                        }
                    }
                    if (isHere(create.bound, mouse))
                        new_stu = true;
                    if (isHere(exit1.bound, mouse))
                        new_stu = false;
                    if (isHere(path.bound, mouse))
                    {
                        typing_path = true;
                        file.txt.setString(file_path);
                    }
                    if (isHere(import.bound, mouse))
                    {
                        Import = true;
                        showImportResult = true;
                        clock.restart();
                    }
                }
                break;
            }
            case Event::TextEntered:
            {
                Typing(typing_id, kill, stu_id, event);
                Typing(typing_path, file, file_path, event);
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        chooseDraw_2(window, o2, o1, result);
        window.draw(create.draw);
        window.draw(del.draw);
        window.draw(eXport.draw);
        chooseDraw_2(window, infor, res, result);
        window.draw(b.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(menu.draw);
        window.draw(title.txt);
        if (new_page && stu_list && !result)
        {
            StudentNode *temp = stu_list;
            for (int i = 0; i < change; ++i)
                temp = temp->next;
            for (int i = 0; i < 7; ++i)
            {
                if (temp)
                {
                    one[i] = temp;
                    stu[i][0]->txt.setString(to_string(one[i]->student.num));
                    stu[i][1]->txt.setString(one[i]->student.student_id);
                    stu[i][2]->txt.setString(one[i]->student.first_name);
                    stu[i][3]->txt.setString(one[i]->student.last_name);
                    stu[i][4]->txt.setString((one[i]->student.gender) ? "F" : "M");
                    stu[i][5]->txt.setString(one[i]->student.dob);
                    stu[i][6]->txt.setString(one[i]->student.social_id);
                    temp = temp->next;
                }
                else
                    stu[i][0]->txt.setString("");
            }
            new_page = false;
        }
        if (!new_page && stu_list && result)
        {
            StudentNode *temp = stu_list;
            for (int i = 0; i < change; ++i)
                temp = temp->next;
            for (int i = 0; i < 5; ++i)
            {
                if (temp)
                {
                    one[i] = temp;
                    resl[i][0]->txt.setString(to_string(one[i]->student.num));
                    resl[i][1]->txt.setString(one[i]->student.student_id);
                    resl[i][2]->txt.setString(one[i]->student.last_name + one[i]->student.first_name);
                    resl[i][3]->txt.setString("0.0");
                    resl[i][4]->txt.setString(to_string(one[i]->student.total_gpa));
                    temp = temp->next;
                }
                else
                    resl[i][0]->txt.setString("");
            }
            new_page = false;
        }
        if (!result)
        {
            for (int i = 0; i < 7; ++i)
            {
                if (stu[i][0]->txt.getString() == "")
                    break;
                for (int j = 0; j < 7; ++j)
                    window.draw(stu[i][j]->txt);
            }
        }
        else
        {
            for (int i = 0; i < count - change; ++i)
            {
                window.draw(detail[i]->draw);
                // if (resl[i][0]->txt.getString() == "")
                //     break;
                for (int j = 0; j < 5; ++j)
                    window.draw(resl[i][j]->txt);
            }
        }

        if (del_stu)
        {
            window.draw(o3.draw);
            window.draw(id.draw);
            window.draw(confirm.draw);
            window.draw(exit2.draw);
            if (typing_id)
                window.draw(kill.txt);
            if (showDelResult)
            {
                checkDel = removeStudentNode(class_list->my_class.student_list, stu_id);
                count--;
            }
            if (showDelResult && clock.getElapsedTime().asSeconds() < 3)
                chooseDraw_2(window, valid1, invalid1, checkDel);
            else if (clock.getElapsedTime().asSeconds() >= 3)
                showDelResult = false;
        }

        if (new_stu)
        {
            window.draw(alert.draw);
            window.draw(path.draw);
            window.draw(import.draw);
            window.draw(exit1.draw);
            if (typing_path)
                window.draw(file.txt);
            if (Import)
            {
                ifstream fin;
                checkPath = importNewStudentsFromStaff(class_list, file_path, fin);
                Import = false;
            }
            if (showImportResult && clock.getElapsedTime().asSeconds() < 3)
                chooseDraw_2(window, valid2, invalid2, checkPath);
            else if (clock.getElapsedTime().asSeconds() >= 3)
                showImportResult = false;
        }

        window.display();
    }
    for (int i = 0; i < 7; ++i)
        delete detail[i];
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            delete stu[i][j];
}

void studentResult(RenderWindow &window, int &page, StudentNode *&student)
{

    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/result/result-bg.png", 180, 120);
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object o2 = createObject("./image/page3-staff/result/full-name.png", 342, 137);
    Object o3 = createObject("./image/page3-staff/result/id.png", 913, 137);
    Object o4 = createObject("./image/page3-staff/result/gpa.png", 350, 721);
    Info name = createText(student->student.last_name + " " + student->student.first_name, 379, 144);
    Info id = createText(student->student.student_id, 957, 144);
    Info gpa = createText("", 379, 721);
    Info *res[8][7]{};
    for (int i = 0; i < 8; ++i)
    {
        createInfoTest(res[i][0], "", 210, 298 + 48 * i);
        createInfoTest(res[i][1], "", 330 + 5, 298 + 48 * i);
        createInfoTest(res[i][2], "", 500, 298 + 48 * i);
        createInfoTest(res[i][3], "", 700 - 10, 298 + 48 * i);
        createInfoTest(res[i][4], "", 850 - 15, 298 + 48 * i);
        createInfoTest(res[i][5], "", 1000 - 20, 298 + 48 * i);
        createInfoTest(res[i][6], "", 1150 - 10, 298 + 48 * i);
        for (int j = 0; j < 7; ++j)
            res[i][j]->txt.setCharacterSize(24);
    }
    int count = 0, change = 0;
    bool new_page = true;
    ResultsNode *res_list = student->student.results_list;
    ResultsNode *one[8];
    while (window.isOpen() && page == 18)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, menu);
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
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
                    if (isHere(menu.bound, mouse))
                    {
                        page = 17;
                        return;
                    }
                    if (isHere(prev.bound, mouse) && change != 0)
                    {
                        new_page = true;
                        change -= 8;
                    }
                    if (isHere(next.bound, mouse))
                    {
                        new_page = true;
                        change += 8;
                    }
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(menu.draw);
        window.draw(o2.draw);
        window.draw(o3.draw);
        window.draw(o4.draw);
        window.draw(name.txt);
        window.draw(id.txt);
        gpa.txt.setString(to_string(student->student.total_gpa).substr(0, 4));
        window.draw(gpa.txt);
        if (new_page && res_list)
        {
            ResultsNode *temp = res_list;
            for (int i = 0; i < change; ++i)
                temp = temp->next;
            for (int i = 0; i < 8; ++i)
            {
                if (temp)
                {
                    one[i] = temp;
                    res[i][0]->txt.setString(one[i]->results.course_id);
                    res[i][1]->txt.setString(one[i]->results.sem_id);
                    res[i][2]->txt.setString(one[i]->results.year_id);
                    res[i][3]->txt.setString(to_string(one[i]->results.score.process).substr(0, 4));
                    res[i][4]->txt.setString(to_string(one[i]->results.score.midterm).substr(0, 4));
                    res[i][5]->txt.setString(to_string(one[i]->results.score.final).substr(0, 4));
                    res[i][6]->txt.setString(to_string(one[i]->results.score.overall).substr(0, 4));
                    temp = temp->next;
                }
                else
                    res[i][0]->txt.setString("");
            }
            new_page = false;
        }
        for (int i = 0; i < 8; ++i)
        {
            if (res[i][0]->txt.getString() == "")
                break;
            for (int j = 0; j < 7; ++j)
                window.draw(res[i][j]->txt);
        }
        window.display();
    }
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 7; ++j)
            delete res[i][j];
}

void Profile1(RenderWindow &window, int &page, StaffNode *person, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page1/profile/staff-bg.png", 180, 120);
    Object staff_id = createObject("./image/page1/profile/staff-id.png", 431, 394);
    Object full_name = createObject("./image/page1/profile/full-namw.png", 467, 467);
    Object dob = createObject("./image/page1/profile/dob.png", 504, 547);
    Object social_id = createObject("./image/page1/profile/social-id.png", 431, 702);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object *y[2]{}, *n[2]{};
    for (int i = 0; i < 2; ++i)
    {
        createObjectTest(y[i], "./image/page3-staff/course/yes.png", 453 + 354 * i, 637);
        createObjectTest(n[i], "./image/page3-staff/course/no.png", 453 + 354 * i, 637);
    }
    Info id = createText(person->staff.username, 475, 400);
    Info name = createText(person->staff.last_name + " " + person->staff.first_name, 490, 472);
    Info date = createText(person->staff.dob, 525, 555);
    Info social = createText(person->staff.social_id, 475, 708);

    while (window.isOpen() && page == 21)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, menu);
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
                    switchPage(menu.bound, mouse, 3, page, Exit);
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(o1.draw);
        window.draw(menu.draw);
        window.draw(staff_id.draw);
        window.draw(full_name.draw);
        window.draw(dob.draw);
        window.draw(social_id.draw);
        window.draw(id.txt);
        window.draw(name.txt);
        window.draw(date.txt);
        window.draw(social.txt);
        if (person->staff.gender)
        {
            window.draw(y[0]->draw);
            window.draw(n[1]->draw);
        }
        else
        {
            window.draw(y[1]->draw);
            window.draw(n[0]->draw);
        }
        window.display();
    }
}

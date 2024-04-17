#include "./struct_and_function/view_function.h"

void homeStudent(RenderWindow &window, int &page, StudentNode *&user, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page4-student/home/home-stu.png", 180, 120);
    Object o2 = createObject("./image/page4-student/home/course.png", 235, 348);
    Object o3 = createObject("./image/page4-student/home/score.png", 235, 462);
    Object o4 = createObject("./image/page4-student/home/other.png", 235, 580);
    while (window.isOpen() && page == 4)
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
                    switchPage(o2.bound, mouse, 8, page, Exit);
                    switchPage(o3.bound, mouse, 9, page, Exit);
                    switchPage(o4.bound, mouse, 10, page, Exit);
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

void courseStudent(RenderWindow &window, int &page, YearNode *year_list, StudentNode *person, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object prev = createObject("./image/page3-staff/prev.png", 180, 793);
    Object next = createObject("./image/page3-staff/next.png", 1212, 793);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    Object sum = createObject("./image/page3-staff/school_year/total.png", 946, 258);
    Object o1 = createObject("./image/page3-staff/course/course-bg.png", 180, 120);
    Info total = createText("", 1050, 258);

    ResultsNode *res = person->student.results_list;
    CourseNode *course[20];
    Object *subject[4]{};
    Info *inf[4]{};
    for (int i = 0; i < 4; ++i)
    {
        createObjectTest(subject[i], "./image/page3-staff/school_year/year-node.png", 235, 117 * i + 347);
        createInfoTest(inf[i], "", 316, 117 * i + 354);
        inf[i]->txt.setFillColor(Color::Yellow);
        inf[i]->txt.setStyle(Text::Bold);
    }
    int count = 0, change = 0;
    bool new_page = true;
    for (res; res; res = res->next)
    {

        for (YearNode *year; year; year = year->next)
        {
            if (res->results.year_id == year_list->school_year.year_id)
            {
                for (SemesterNode *sem = year->school_year.list_sem; sem; sem = sem->next)
                {
                    if (res->results.sem_id == sem->sem.semester_id)
                    {
                        for (CourseNode *cs = sem->sem.course_list; cs; cs = cs->next)
                        {
                            if (res->results.course_id == cs->course.course_id)
                            {
                                course[count] = cs;
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    total.txt.setString(to_string(count) + "courses");
    while (window.isOpen() && page == 8)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, prev);
        updateColorOnHover(window, next);
        updateColorOnHover(window, menu);
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
                    switchPage(menu.bound, mouse, 4, page, Exit);
                    switchPage(b.bound, mouse, 4, page, Exit);
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
        window.draw(b.draw);
        window.draw(sum.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(total.txt);
        if (new_page)
        {

            for (int i = 0; i < 4; ++i)
            {
                CourseNode *temp = course[change - 1 + i];
                if (temp)
                    inf[i]->txt.setString(temp->course.course_id + " - " + temp->course.course_name);
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
        window.display();
    }
    for (int i = 0; i < 4; ++i)
        delete subject[i], inf[i];
}

void Other2(RenderWindow &window, int &page, StudentNode *&user, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page3-staff/other/other-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/other/log-out.png", 230, 354);
    Object o3 = createObject("./image/page3-staff/other/change-pass.png", 230, 465);
    Object o4 = createObject("./image/page3-staff/other/profile.png", 230, 576);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);
    while (window.isOpen() && page == 10)
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
                    switchPage(b.bound, mouse, 4, page, Exit);
                    switchPage(menu.bound, mouse, 4, page, Exit);
                    switchPage(o2.bound, mouse, 1, page, Exit);
                    switchPage(o3.bound, mouse, 21, page, Exit);
                    switchPage(o4.bound, mouse, 23, page, Exit);
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

void Profile2(RenderWindow &window, int &page, ClassNode *class_list, StudentNode *person, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object o1 = createObject("./image/page4-student/home/stu-profile-bg.png", 180, 120);
    Object student_id = createObject("./image/page1/profile/staff-id.png", 431, 394);
    Object full_name = createObject("./image/page1/profile/full-namw.png", 467, 467);
    Object dob = createObject("./image/page4-student/home/input.png", 504, 547);
    Object class_name = createObject("./image/page4-student/home/input.png", 924, 547);
    Object social_id = createObject("./image/page1/profile/social-id.png", 431, 702);
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object *y[2]{}, *n[2]{};
    for (int i = 0; i < 2; ++i)
    {
        createObjectTest(y[i], "./image/page3-staff/course/yes.png", 453 + 354 * i, 637);
        createObjectTest(n[i], "./image/page3-staff/course/no.png", 453 + 354 * i, 637);
    }
    Info id = createText(person->student.student_id, 475, 400);
    Info name = createText(person->student.last_name + " " + person->student.first_name, 490, 472);
    Info date = createText(person->student.dob, 520, 553);
    Info class_id = createText(person->student.class_id, 940, 553);
    Info social = createText(person->student.social_id, 475, 708);
    while (window.isOpen() && page == 23)
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
                    switchPage(menu.bound, mouse, 4, page, Exit);
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
        window.draw(student_id.draw);
        window.draw(class_name.draw);
        window.draw(full_name.draw);
        window.draw(dob.draw);
        window.draw(social_id.draw);
        window.draw(id.txt);
        window.draw(name.txt);
        window.draw(date.txt);
        window.draw(social.txt);
        window.draw(class_id.txt);
        if (person->student.gender)
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
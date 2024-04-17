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

void courseStudent(RenderWindow &window, int &page, YearNode *&year_list, StudentNode *person, bool &Exit)
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
    CourseNode *course[20]{};
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
        for (YearNode *year = year_list; year; year = year->next)
        {
            if (res->results.year_id == year->school_year.year_id)
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
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    total.txt.setString(to_string(count) + " courses");
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
                    for (int i = 0; i < 4; ++i)
                    {
                        if (isHere(subject[i]->bound, mouse) && course[i])
                        {
                            page = 19;
                            detailStudent(window, page, course[i], Exit);
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
        window.draw(menu.draw);
        window.draw(b.draw);
        window.draw(sum.draw);
        window.draw(prev.draw);
        window.draw(next.draw);
        window.draw(total.txt);
        if (new_page)
        {

            for (int i = change % 4; i < 4; ++i)
            {
                CourseNode *temp = course[change + i];
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

void detailStudent(RenderWindow &window, int &page, CourseNode *course, bool &Exit)
{
    Event event;
    Object screen = createBackGround("./image/page1/main-bg.png");
    Object menu = createObject("./image/page3-staff/exit.png", 1236, 96);
    Object b = createObject("./image/page3-staff/backward.png", 183, 259);

    Object o1 = createObject("./image/page3-staff/course/update/update-cour-bg.png", 180, 120);
    Object o2 = createObject("./image/page3-staff/course/input.png", 497, 377);
    Object o3 = createObject("./image/page3-staff/course/input.png", 497, 438);
    Object o4 = createObject("./image/page3-staff/course/input.png", 497, 499);
    Object o5 = createObject("./image/page3-staff/course/input.png", 497, 560);
    Object o6 = createObject("./image/page3-staff/course/input_1.png", 506, 620);
    Object o7 = createObject("./image/page3-staff/course/input_1.png", 965, 620);

    Object *yes[6]{}, *no[6]{}, *yes_sess[4]{}, *no_sess[4]{};
    Info *inf[4]{};
    createInfoTest(inf[0], course->course.course_id, 512, 377);
    createInfoTest(inf[1], course->course.course_name, 512, 438);
    createInfoTest(inf[2], course->course.main_class->my_class.class_id, 512, 499);
    createInfoTest(inf[3], course->course.teacher_name, 512, 560);
    bool check_day[6], check_sess[4];
    for (int i = 0; i < 4; ++i)
    {
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
    int day = 0, sess = 0;
    while (window.isOpen() && page == 19)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        updateColorOnHover(window, b);
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
                    switchPage(b.bound, mouse, 8, page, Exit);
                    switchPage(menu.bound, mouse, 4, page, Exit);
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        window.draw(menu.draw);
        window.draw(o1.draw);
        window.draw(o2.draw);
        window.draw(o3.draw);
        window.draw(o4.draw);
        window.draw(o5.draw);
        window.draw(o6.draw);
        window.draw(o7.draw);
        window.draw(b.draw);
        window.draw(stu.txt);
        window.draw(cre.txt);
        check_day[course->course.teaching_session.day_of_the_week - 2] = true;
        check_sess[course->course.teaching_session.session_no - 1] = true;
        for (int i = 0; i < 4; ++i)
        {
            window.draw(inf[i]->txt);
            chooseDraw_1(window, yes_sess[i], no_sess[i], check_sess[i]);
        }
        for (int i = 0; i < 6; ++i)
            chooseDraw_1(window, yes[i], no[i], check_day[i]);
        window.display();
    }
}

void resultStudent(RenderWindow &window, int &page, StudentNode *student, bool &Exit)
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
    while (window.isOpen() && page == 9)
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
                        page = 4;
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
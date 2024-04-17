#include <iostream>
#include "SFML/Graphics.hpp"
#include "function.h"

using namespace sf;
using namespace std;

struct Object
{
    Texture text;
    Sprite draw;
    FloatRect bound;
    bool isHover(RenderWindow &window)
    {
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f worldPos = window.mapPixelToCoords(mousePos);
        return bound.contains(worldPos);
    }
};

struct Info
{
    Font font;
    Text txt;
    FloatRect bound;
};

Object createObject(string input, float x, float y);
// Object *createObjectTest(string input, float x, float y);
void createObjectTest(Object *&me, string s, float x, float y);
Object createBackGround(string s);
Info createText(string s, float x, float y);
// Info *createInfoTest(string s, float x, float y);
void createInfoTest(Info *&a, string s, float x, float y);
bool isHere(FloatRect &bound, Vector2f &mouse);
void updateColorOnHover(RenderWindow &window, Object &o);
void chooseDraw_1(RenderWindow &window, Object *x, Object *y, bool check);
void chooseDraw_2(RenderWindow &window, Object x, Object y, bool check);
void switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page, bool &menu);
void changePosition(Object &a, float x, float y);
void Typing(bool &texting, Info &info, string &input, Event event);
void objectAppear(RenderWindow &window, bool &change, Clock &clock, Object &o, int period);

void Scene1(RenderWindow &window, int &page, bool &is_staff);
void logIn(RenderWindow &window, int &page, bool is_staff, bool see, StaffNode *user3, string &name, string &pass, StaffNode *&user, StudentNode *&user1, ClassNode *class_list);
void homeStaff(RenderWindow &window, int &page, StaffNode *&user, bool &Exit);
void School(RenderWindow &window, int &page, bool is_staff, YearNode *&year, ClassNode *&class_list, bool &Exit);
void Semesters(RenderWindow &window, int &page, YearNode *&year, ClassNode *class_list, bool &Exit);
void addSemester(RenderWindow &window, YearNode *&year, int &page, bool &Exit);
void Courses(RenderWindow &window, CourseNode *&course, int &page, string &yr, string &sem, ClassNode *class_list, bool &Exit);
void addCourse(RenderWindow &window, CourseNode *&course, int &page, string yr, string sem, ClassNode *class_list, bool &Exit);
void updateCourse(RenderWindow &window, CourseNode *&course, int &page, string yr, string sem, ClassNode *class_list, bool &Exit);
void resultCourse(RenderWindow &window, CourseNode *&course, int &page, string yr, string sem);
void Classes(RenderWindow &window, int &page, bool is_staff, ClassNode *class_list, bool &Exit);
void Students(RenderWindow &window, int &page, ClassNode *&class_list, bool &Exit);
void studentResult(RenderWindow &window, int &page, StudentNode *&student);
void Other1(RenderWindow &window, int &page, StaffNode *&user, bool &Exit);
void changePassword(RenderWindow &window, int &page, bool is_staff, StaffNode *&user, bool &Exit);
void Profile1(RenderWindow &window, int &page, StaffNode *person, bool &Exit);

void homeStudent(RenderWindow &window, int &page, StudentNode *&user, bool &Exit);
void courseStudent(RenderWindow &window, int &page, YearNode *&year_list, StudentNode *person, bool &Exit);
void detailStudent(RenderWindow &window, int &page, CourseNode *course, bool &Exit);
void resultStudent(RenderWindow &window, int &page, StudentNode *student, bool &Exit);
void Other2(RenderWindow &window, int &page, StudentNode *&user, bool &Exit);
void Profile2(RenderWindow &window, int &page, ClassNode *class_list, StudentNode *person, bool &Exit);
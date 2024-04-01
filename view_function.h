#include <iostream>
#include "SFML/Graphics.hpp"
#include "./struct_and_function/function.h"

using namespace sf;
using namespace std;

struct Object
{
    Texture text;
    Sprite draw;
    FloatRect bound;
};

struct Info
{
    Font font;
    Text txt;
    FloatRect bound;
};

Object createObject(string input, float x, float y);
Object *createObjectTest(string input, float x, float y);
Object createBackGround(string s);
Info createText(string s, float x, float y);
Info *createInfoTest(string s, float x, float y);
bool isHere(FloatRect &bound, Vector2f &mouse);
bool Draw(RenderWindow &window, Vector2f &mouse, Object x, Object y);
void chooseDraw(RenderWindow &window, Object *x, Object *y, bool check);
void switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page);
void changePosition(Object &a, float x, float y);
void Typing(bool &texting, Info &info, string &input, Event event);
void objectAppear(RenderWindow &window, bool &change, Clock &clock, Object &o);

void Scene1(RenderWindow &window, int &page, bool &is_staff);
void logIn(RenderWindow &window, int &page, bool is_staff, bool see, StudentNode *user1, StaffNode *user2, string &name, string &pass);
void homeStaff(RenderWindow &window, int &page);
void School(RenderWindow &window, int &page, bool is_staff, YearNode *&year);
void Semesters(RenderWindow &window, int &page, YearNode *&year);
void addSemester(RenderWindow &window, YearNode *&year, int &page);
void Courses(RenderWindow &window, CourseNode *&course, int &page, string &yr, string &sem);
void addCourse(RenderWindow &window, CourseNode *&course, int &page);
void updateCourse(RenderWindow &window, CourseNode *&course, int &page);
void Study(RenderWindow &window, int &page, bool is_staff);
void Classes(RenderWindow &window, int &page, bool is_staff);
void Other(RenderWindow &window, int &page, bool is_staff);
void changePassword(RenderWindow &window, int &page, bool is_staff);
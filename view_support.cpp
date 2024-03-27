#include "view_function.h"

Object createObject(string input, float x, float y)
{
    Object icon;
    icon.text.loadFromFile(input);
    icon.draw.setTexture(icon.text);
    icon.draw.setPosition(x, y);
    icon.bound = icon.draw.getGlobalBounds();
    icon.text.setSmooth(true);
    // The global bounds are the smallest rectangle that contains the entire sprite, in global coordinate(relative to the window, not the sprite)
    return icon;
}
Object *createObjectTest(string s, float x, float y)
{
    Object *me = new Object;
    me->text.loadFromFile(s);
    me->draw.setTexture(me->text);
    me->draw.setPosition(x, y);
    me->bound = me->draw.getGlobalBounds();
    return me;
}

Object createBackGround(string input)
{
    Object me;
    me.text.loadFromFile(input);
    me.draw.setTexture(me.text);
    me.bound = me.draw.getGlobalBounds();
    me.text.setSmooth(true);
    return me;
}

Info createText(string str, float x, float y)
{
    Info input;
    input.font.loadFromFile("./image/font/Arial.ttf");
    input.txt.setFont(input.font);
    input.txt.setStyle(Text::Bold);
    input.txt.setCharacterSize(30);
    input.txt.setFillColor(Color::Black);
    input.txt.setPosition(x, y);
    input.txt.setString(str);
    input.bound = input.txt.getGlobalBounds();
    return input;
}

Info *createInfoTest(string s, float x, float y)
{
    Info *a = new Info;
    a->font.loadFromFile("./image/font/Arial.ttf");
    a->txt.setFont(a->font);
    a->txt.setCharacterSize(30);
    a->txt.setPosition(x, y);
    a->txt.setFillColor(Color::Black);
    a->txt.setString(s);
    a->bound = a->txt.getGlobalBounds();
    return a;
}
bool isHere(FloatRect &bound, Vector2f &mouse)
{
    return bound.contains(mouse);
}

bool chooseDraw(RenderWindow &window, Vector2f &mouse, Object x, Object y)
{
    if (isHere(x.bound, mouse))
    {
        window.draw(x.draw);
        return true;
    }
    else
    {
        window.draw(y.draw);
        return false;
    }
}

void switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page)
{
    if (isHere(bound, mouse))
        page = k;
    return;
}

void changePosition(Object &a, float x, float y)
{
    a.draw.setPosition(x, y);
    a.bound = a.draw.getGlobalBounds();
}

void Typing(bool &texting, Info &infor, string &input, Event event)
{
    if (texting)
    {
        if (event.text.unicode < 128)
        {
            if (event.text.unicode == 8)
            {
                if (!input.empty())
                    input.pop_back();
            }
            else if (event.text.unicode == 13)
                texting = false;
            else if (event.text.unicode >= 32)
                input += static_cast<char>(event.text.unicode);
            infor.txt.setString(input + '_');
        }
    }
}

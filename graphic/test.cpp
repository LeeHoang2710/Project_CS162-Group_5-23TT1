#include <iostream>
#include "SFML\Graphics.hpp"
#include <windows.h>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(540, 360), "SFML", Style::Default);
    RectangleShape player(Vector2f(200.0f, 240.0f));
    player.setFillColor(Color::Blue);
    // move the origin of the object from 0,0  to 100,100
    player.setOrigin(100.0f, 100.0f);
    /*Texture playerTexture;
    playerTexture.loadFromFile("./image/Staff1.png");
    Vector2u TextureSize = playerTexture.getSize();
    player.setTexture(&playerTexture);*/
    /*Font font;
    if (!font.loadFromFile("../image/font/Arial.ttf"))
    {
        cout << "Error loading file" << endl;
        system("pause");
    }
    Text text;
    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(20);
    text.setPosition(50, 50);
    text.setFillColor(Color::Green); */
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::A))
            player.move(-0.1f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
            player.move(0.0f, -0.1f);
        if (Keyboard::isKeyPressed(Keyboard::Key::S))
            player.move(0.0f, 0.1f);
        if (Keyboard::isKeyPressed(Keyboard::Key::D))
            player.move(0.1f, 0.0f);
        /*
       if (Mouse::isButtonPressed(Mouse::Left))
       {
           Vector2i mousePos = Mouse::getPosition(window);
           // player has vector2f type so we have to cast integer to float
           player.setPosition((float)mousePos.x, (float)mousePos.y);
       }*/
        window.clear();
        window.draw(player);

        window.display();
    }
}
#include <iostream>
#include "SFML\Graphics.hpp"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1080, 720), "SFML", Style::Default);
    RectangleShape player(Vector2f(200.0f, 200.0f));
    player.setFillColor(Color::Blue);

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
            case Event::Resized:
                cout << "New window width: " << event.size.width << " New window height: " << event.size.height << endl;
                break;
            }
        }

        if(KeyBoard::isKeyPressed(Keyboard::Key::A)) player.m
        window.clear();
        window.draw(player);
        window.display();
    }


}
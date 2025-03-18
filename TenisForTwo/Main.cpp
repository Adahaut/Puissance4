#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int main()
{

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tenis For Two");

    sf::RectangleShape table(sf::Vector2f(1700, 15));
    table.setFillColor(sf::Color::White);
    table.setPosition(110, 1030);

    sf::RectangleShape nest(sf::Vector2f(20, 100));
    nest.setFillColor(sf::Color::White);
    nest.setPosition(960, 925);

    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(960, 540);

    sf::CircleShape racket(30);
    racket.setFillColor(sf::Color::Green);
    racket.setPosition(480, 540);

    sf::CircleShape racket2(30);
    racket2.setFillColor(sf::Color::Red);
    racket2.setPosition(1440, 540);

    float v = 1;
    float s = -0.2;
    bool canplay = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        sf::Vector2f gravity(0, v);
        sf::Vector2f speed(s, 0);

        window.draw(nest);
        window.draw(table);
        window.draw(ball);
        window.draw(racket);
        window.draw(racket2);

        ball.move(gravity);
        v += 0.001;

        ball.move(speed);

        if (ball.getPosition().x < 0)
        {
            std::cout << "looser" << std::endl;
            window.close();
            main();
        }
        else if (ball.getPosition().x > 1920)
        {
            std::cout << "winner" << std::endl;
            window.close();
            main();
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && ball.getPosition().x < 960 && canplay == true)
        {
            s = 0.5;
            v = -1;
            racket.setPosition(ball.getPosition().x, ball.getPosition().y);
            canplay = false;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ball.getPosition().x < 960 && canplay == true)
        {
            s = 1;
            v = 2;
            canplay = false;
            racket.setPosition(ball.getPosition().x, ball.getPosition().y);
        }


        if (ball.getGlobalBounds().intersects(table.getGlobalBounds()))
        {
            v = -1;
        }
        if (ball.getGlobalBounds().intersects(nest.getGlobalBounds())) 
        {
            s = -s;
        }
        if (ball.getPosition().y <= 0)
        {
            v = 1;
        }

        if (ball.getPosition().x > 1260 && canplay == false)
        {
            int a = rand() % 3 + 1; //One out of three chance of smash

            if (a == 1) 
            {
                s = -1;
                v = 2;
                racket2.setPosition(ball.getPosition().x, ball.getPosition().y);
            }
            else
            {
                s = -0.5;
                v = -1;
                racket2.setPosition(ball.getPosition().x, ball.getPosition().y);
            }
            canplay = true;
        }

        window.display();
    }

    return 0;
}

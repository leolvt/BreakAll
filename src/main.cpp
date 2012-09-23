#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
//#include "BreakAll.h"

int main()
{

#if 1

    std::cout << "Hello World!" << std::endl;
    
    std::cout << "Current Video Mode: ";
    std::cout << sf::VideoMode::getDesktopMode().width << "x";
    std::cout << sf::VideoMode::getDesktopMode().height << std::endl;

    std::cout << "Available Modes: " << std::endl;
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for(sf::VideoMode mode : modes) {
        if (mode.bitsPerPixel != 32) continue;
        std::cout << mode.width << "x" << mode.height << "x" << mode.bitsPerPixel << std::endl;
    }

    //sf::Window window(sf::VideoMode(1920, 1080), "My window");
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Titlebar|sf::Style::Close);
    window.setPosition(sf::Vector2i(0,0));
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && 
                event.key.code == sf::Keyboard::Escape)
                window.close();

        }

        window.clear();
        window.draw(shape);
        window.display();
    }

#else 

    BreakAll::Initialize();
    BreakAll::Run();
    BreakAll::Terminate();

#endif

    return 0;
}

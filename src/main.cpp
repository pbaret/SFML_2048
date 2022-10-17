#include <SFML/Graphics.hpp>
#include "global.h"
#include "window.h"
#include "game_manager.h"
#include "gui.h"
#include "font-arial.h"
#include <iostream>

using namespace gns;

int main()
{
    if (!GUI::text_font.loadFromMemory(&arial_ttf, arial_ttf_len))
    {
        std::cerr << "problem with font" << std::endl;
    }

    // create the window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(window_width, window_height)), "2048 - C++ version of Gabriele Cirulli's game");
    window.setFramerateLimit(30);    // no framerate limit

    GameManager game_manager(&window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        game_manager.ProcessUserInputs();

        game_manager.UpdateGameState();

        game_manager.UpdateDisplay();
    }

    return 0;
}
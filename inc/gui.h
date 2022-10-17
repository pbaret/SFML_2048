#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class GUI
{
private:
    sf::RenderWindow * m_pt_display_window;
    std::vector<sf::RectangleShape> m_gui_shapes;
    std::vector<sf::Text> m_gui_texts;
    std::vector<sf::RectangleShape> m_empty_tiles;

public:
    static sf::Font text_font;

public:
    GUI(sf::RenderWindow * pt_display_window);
    ~GUI();
    void Draw();

};

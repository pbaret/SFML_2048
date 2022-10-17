#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <stdint.h>

/**
 * @brief game namespace
 */
namespace gns
{    
    constexpr sf::Color color_grid_bg = sf::Color(0x9e9e9eff);
    constexpr sf::Color color_grid_empty_tile = sf::Color(0xbdbdbdff);

    constexpr sf::Color color_window_bg = sf::Color(0xefebe9ff);
    constexpr sf::Color color_button_dark = sf::Color(0x6d4c41ff);
    constexpr sf::Color color_button_light = sf::Color(0xd7ccc8ff);

    constexpr sf::Color color_font_dark = sf::Color(0x6d4c41ff);
    constexpr sf::Color color_font_light = sf::Color(0xefebe9ff); // Same window bg?

    extern std::map<int, sf::Color> color_map_tile;
}
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "gui.h"
#include "grid.h"

/**
 * @brief Game manager : handles all the application and game logic
 */
class GameManager
{
private:
    sf::RenderWindow * m_pt_display_window;   /**< @brief Pointer to the display window of the game */
    GUI m_gui;
    Grid m_grid;
    sf::Text m_txt_title;       /**< @brief Title of the game */
    
public:
    /**
     * @brief Construct a new Game Manager object
     * 
     * @param pt_display_window : pointer to the display window that the game manager will use to display game updates.
     */
    GameManager(sf::RenderWindow * pt_display_window);

    /**
     * @brief Destroy the Game Manager object
     */
    ~GameManager();

    /**
     * @brief Process all the user inputs and events (Keyboard, mouse, window close etc...)
     */
    void ProcessUserInputs();

    /**
     * @brief Update the state of the game
     */
    void UpdateGameState();

    /**
     * @brief Update display by rendering a full frame
     * @note clears the previous window (fill with black)
     */
    void UpdateDisplay();

private:

    /**
     * @brief Check if the input mouse position lands in the game window region of the screen
     * 
     * @param mouse_pos : input mouse position relative to game window
     * @return true if in the window, false otherwise
     */
    inline bool IsMouseInWindow(sf::Vector2i & mouse_pos) const;
};


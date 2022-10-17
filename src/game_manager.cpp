#include "game_manager.h"
#include "global.h"
#include "window.h"
#include "gui.h"

#include <iostream>
#include <string>

#include "grid.h"

using namespace gns;

GameManager::GameManager(sf::RenderWindow * pt_display_window) :
    m_pt_display_window(pt_display_window),
    m_gui(pt_display_window),
    m_grid(pt_display_window)
{
    /*m_txt_title = sf::Text("2048", GUI::text_font, tile_font_size);
    SetTextLocalOrigin(m_txt_title, LocalOrigin::Top);
    m_txt_title.setPosition(sf::Vector2f((window_width)/2, window_margin));
    m_txt_title.setStyle(sf::Text::Bold);
    m_txt_title.setFillColor(color_font_dark);*/

    /*m_txt_footer = sf::Text("Developped by Pierre BARET - WTFPL License", m_txt_font, 20);
    SetTextLocalOrigin(m_txt_footer, LocalOrigin::Bottom);
    m_txt_footer.setPosition(GridPositionToWindowCoordinate((width)/2, (height - 1)));
    m_txt_footer.setFillColor(sf::Color(128,0,255));

    
    m_txt_stats = sf::Text(std::to_string(m_nb_iteration), m_txt_font, 20);
    SetTextLocalOrigin(m_txt_stats, LocalOrigin::TopRight);
    m_txt_stats.setPosition(GridPositionToWindowCoordinate((width-2), 4));
    m_txt_stats.setFillColor(sf::Color(128,255,255));*/
}


GameManager::~GameManager()
{
}


inline bool GameManager::IsMouseInWindow(sf::Vector2i & mouse_pos) const
{
    return ((mouse_pos.x > 0) && (mouse_pos.x < window_width) && (mouse_pos.y > 0) && (mouse_pos.y < window_height));
}

void GameManager::ProcessUserInputs()
{
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (m_pt_display_window->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Left:
                {
                    m_grid.Update(GridMovement::LEFT);
                }
                break;
                case sf::Keyboard::Right:
                {
                    m_grid.Update(GridMovement::RIGHT);
                }
                break;
                case sf::Keyboard::Up:
                {
                    m_grid.Update(GridMovement::UP);
                }
                break;
                case sf::Keyboard::Down:
                {
                    m_grid.Update(GridMovement::DOWN);
                }
                break;
                // Quit
                case sf::Keyboard::Q:
                {
                    m_pt_display_window->close();
                }
                break;
                default:
                break;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*m_pt_display_window);
            if (IsMouseInWindow(mouse_pos))
            {
                const uint32_t x = static_cast<uint32_t>(mouse_pos.x);
                const uint32_t y = static_cast<uint32_t>(mouse_pos.y);

                std::cout << (int)x << " " << (int)y << std::endl;
            }
        }

        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            m_pt_display_window->close();
        }
    }
}

void GameManager::UpdateGameState()
{

}

void GameManager::UpdateDisplay()
{
    m_gui.Draw();
    m_grid.Draw();

    //m_grid.DrawGrid(m_pt_display_window);
    //m_pt_display_window->draw(m_txt_title);
    //m_pt_display_window->draw(m_txt_footer);
    //m_pt_display_window->draw(m_txt_stats);

    m_pt_display_window->display();
}


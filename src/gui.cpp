#include "gui.h"
#include "window.h"
#include "colors.h"
#include "global.h"

#include "grid.h"

using namespace gns;

// Init static variable
sf::Font GUI::text_font = sf::Font();

GUI::GUI(sf::RenderWindow * pt_display_window) :
    m_pt_display_window(pt_display_window)
{
    // GUI BACKGROUND
    sf::RectangleShape gui_bg(sf::Vector2f(window_width, window_height));
    gui_bg.setPosition(sf::Vector2f(0,0));
    gui_bg.setFillColor(color_window_bg);
    m_gui_shapes.push_back(gui_bg);

    // INFO TEXT BACKGROUND
    sf::RectangleShape info_txt_bg(sf::Vector2f(window_width - 4 * window_margin, 4 * box_padding + 3 * box_font_size));
    info_txt_bg.setPosition(sf::Vector2f(2 * window_margin, 2 * window_margin + title_font_size));
    info_txt_bg.setFillColor(color_button_light);
    m_gui_shapes.push_back(info_txt_bg);

    // PLACEHOLDER 1 : NEW GAME BUTTON
    sf::RectangleShape placeholder1(sf::Vector2f(tile_size + window_margin, 2 * box_padding + box_font_size));
    placeholder1.setPosition(sf::Vector2f(  window_margin + grid_width * tile_size + (grid_width + 1) * tile_margin - placeholder1.getSize().x, 
                                            info_txt_bg.getPosition().y + info_txt_bg.getSize().y + tile_margin));
    placeholder1.setFillColor(color_button_light);
    m_gui_shapes.push_back(placeholder1);

    // PLACEHOLDER 2 : HIGHSCORE
    sf::RectangleShape placeholder2(sf::Vector2f(tile_size + window_margin, 2 * box_padding + box_font_size));
    placeholder2.setPosition(sf::Vector2f(placeholder1.getPosition().x, placeholder1.getPosition().y + placeholder1.getSize().y + tile_margin));
    placeholder2.setFillColor(color_button_light);
    m_gui_shapes.push_back(placeholder2);

    // PLACEHOLDER 3 : SCORE
    sf::RectangleShape placeholder3(sf::Vector2f(tile_size + window_margin, 2 * box_padding + box_font_size));
    placeholder3.setPosition(sf::Vector2f(placeholder2.getPosition().x - placeholder2.getSize().x - tile_margin, placeholder2.getPosition().y));
    placeholder3.setFillColor(color_button_light);
    m_gui_shapes.push_back(placeholder3);

    // GAME GRID BACKGROUND
    sf::RectangleShape grid_bg(sf::Vector2f(grid_width * tile_size + (grid_width + 1) * tile_margin, grid_height * tile_size + (grid_height + 1) * tile_margin));
    grid_bg.setPosition(sf::Vector2f(window_margin, window_height - window_margin - grid_height * tile_size - (grid_height + 1) * tile_margin));
    grid_bg.setFillColor(color_grid_bg);
    m_gui_shapes.push_back(grid_bg);

    // EMPTY TILES
    const sf::Vector2f first_tile_pos = grid_bg.getPosition() + sf::Vector2f(tile_margin, tile_margin);
    Grid::FirstTileGUIPos = first_tile_pos;

    for (int l = 0; l < grid_height; l++)
    {
        for (int c = 0; c < grid_width; c++)
        {
            sf::RectangleShape tile(sf::Vector2f(tile_size, tile_size));
            tile.setPosition(first_tile_pos + sf::Vector2f(c * (tile_margin + tile_size), l * (tile_margin + tile_size)));
            tile.setFillColor(color_grid_empty_tile);
            m_empty_tiles.push_back(tile);
        }
    }

    /// TEXTS

    sf::Text title = sf::Text("2048", GUI::text_font, tile_font_size);
    SetTextLocalOrigin(title, LocalOrigin::Top);
    title.setPosition(sf::Vector2f((window_width)/2, window_margin));
    title.setStyle(sf::Text::Bold);
    title.setFillColor(color_font_dark);
    m_gui_texts.push_back(title);

    sf::Text info_txt = sf::Text("", GUI::text_font, info_font_size);
    info_txt.setString("Control with keyboaard arrows\n\n  Developped by Pierre BARET\n\n       WTFPL License");
    SetTextLocalOrigin(info_txt, LocalOrigin::TopLeft);
    info_txt.setPosition(sf::Vector2f(info_txt_bg.getPosition() + sf::Vector2f(box_padding, box_padding)));
    info_txt.setStyle(sf::Text::Style::Regular);
    info_txt.setFillColor(color_font_light);
    m_gui_texts.push_back(info_txt);
}

GUI::~GUI()
{
}

void GUI::Draw()
{
    for (const auto & shape : m_gui_shapes)
    {
        m_pt_display_window->draw(shape);
    }

    for (const auto & shape : m_empty_tiles)
    {
        m_pt_display_window->draw(shape);
    }

    for (const auto & txt : m_gui_texts)
    {
        m_pt_display_window->draw(txt);
    }
}


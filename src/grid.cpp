#include "grid.h"
#include "window.h"
#include "colors.h"
#include "gui.h"

using namespace gns;

sf::Vector2f Grid::FirstTileGUIPos = sf::Vector2f();

Grid::Grid(sf::RenderWindow * pt_display_window) :
    m_pt_display_window(pt_display_window),
    mt(rd())
{
    dist_x = std::uniform_int_distribution<>(0, gns::grid_width-1);
    dist_y = std::uniform_int_distribution<>(0, gns::grid_height-1);
    dist_rate = std::uniform_int_distribution<>(1, 100);
    
    ResetGrid();
}

Grid::~Grid()
{
}

void Grid::Draw() const
{
    for (int l = 0; l < m_grid.size(); l++)
    {
        for (int c = 0; c < m_grid[l].size(); c++)
        {
            const uint32_t val = m_grid[l][c].Value();
            if (val != 0)
            {
                sf::RectangleShape tile(sf::Vector2f(tile_size, tile_size));
                sf::Vector2f tile_position = sf::Vector2(FirstTileGUIPos + sf::Vector2f(c * (tile_margin + tile_size), l * (tile_margin + tile_size)));
                tile.setPosition(tile_position);
                tile.setFillColor(color_map_tile[val]);
                m_pt_display_window->draw(tile);

                std::string label = std::to_string(val);
                uint32_t font_size = std::max((int)(tile_font_size / label.size()), 20);
                sf::Text tile_label(label, GUI::text_font, font_size);
                tile_label.setFillColor(sf::Color::White);
                SetTextLocalOrigin(tile_label, LocalOrigin::Bottom);
                tile_label.setPosition(tile_position + sf::Vector2f(tile_size/2, tile_size/2));
                m_pt_display_window->draw(tile_label);
            }
        }
    }
}


void Grid::MergeTiles(Tile & dst, Tile & merged)
{
    dst.Pow();
    merged.SetValue(0);
}

void Grid::MoveTile(Tile & dst, Tile & src)
{
    dst.SetValue(src.Value());
    src.SetValue(0);
}

bool Grid::MoveGridLeft()
{
    bool grid_movement_occured = false;

    for (int l = 0; l < grid_height; l++)
    {
        for (int c = 0; c < grid_width; c++)
        {
            Tile & current_tile = m_grid[l][c];

            if (current_tile.Value() != 0)
            {
                // 1. Merge following cells if necessary
                for (int cc = c + 1; cc < grid_width; cc++)
                {
                    if (m_grid[l][cc].Value() != 0)
                    {
                        if (m_grid[l][cc].Value() == current_tile.Value())
                        {
                            grid_movement_occured = true;
                            MergeTiles(current_tile, m_grid[l][cc]);
                        }
                        break;
                    }
                }
                // 2. Move the Cell left
                for (int cc = 0; cc < c; cc++)
                {
                    if (IsCellEmpty(cc, l))
                    {
                        grid_movement_occured = true;
                        MoveTile(m_grid[l][cc], current_tile);
                        break;
                    }
                }
            }
        }
    }

    return grid_movement_occured;
}

bool Grid::MoveGridRight()
{
    bool grid_movement_occured = false;

    for (int l = 0; l < grid_height; l++)
    {
        for (int c = grid_width - 1; c >= 0; c--)
        {
            Tile & current_tile = m_grid[l][c];

            if (current_tile.Value() != 0)
            {
                // 1. Merge following cells if necessary
                for (int cc = c - 1; cc >= 0; cc--)
                {
                    if (m_grid[l][cc].Value() != 0)
                    {
                        if (m_grid[l][cc].Value() == current_tile.Value())
                        {
                            grid_movement_occured = true;
                            MergeTiles(current_tile, m_grid[l][cc]);
                        }
                        break;
                    }
                }
                // 2. Move the Cell right
                for (int cc = grid_width - 1; cc > c; cc--)
                {
                    if (IsCellEmpty(cc, l))
                    {
                        grid_movement_occured = true;
                        MoveTile(m_grid[l][cc], current_tile);
                        break;
                    }
                }
            }
        }
    }

    return grid_movement_occured;
}

bool Grid::MoveGridDown()
{
    bool grid_movement_occured = false;

    for (int c = 0; c < grid_width; c++)
    {
        for (int l = grid_height - 1; l >= 0; l--)
        {
            Tile & current_tile = m_grid[l][c];

            if (current_tile.Value() != 0)
            {
                // 1. Merge following cells if necessary
                for (int ll = l - 1; ll >= 0; ll--)
                {
                    if (m_grid[ll][c].Value() != 0)
                    {
                        if (m_grid[ll][c].Value() == current_tile.Value())
                        {
                            grid_movement_occured = true;
                            MergeTiles(current_tile, m_grid[ll][c]);
                        }
                        break;
                    }
                }
                // 2. Move the Cell down
                for (int ll = grid_height - 1; ll > l; ll--)
                {
                    if (IsCellEmpty(c, ll))
                    {
                        grid_movement_occured = true;
                        MoveTile(m_grid[ll][c], current_tile);
                        break;
                    }
                }
            }
        }
    }

    return grid_movement_occured;
}

bool Grid::MoveGridUp()
{
    bool grid_movement_occured = false;

    for (int c = 0; c < grid_width; c++)
    {
        for (int l = 0; l < grid_height; l++)
        {
            Tile & current_tile = m_grid[l][c];

            if (current_tile.Value() != 0)
            {
                // 1. Merge following cells if necessary
                for (int ll = l + 1; ll < grid_height; ll++)
                {
                    if (m_grid[ll][c].Value() != 0)
                    {
                        if (m_grid[ll][c].Value() == current_tile.Value())
                        {
                            grid_movement_occured = true;
                            MergeTiles(current_tile, m_grid[ll][c]);
                        }
                        break;
                    }
                }
                // 2. Move the Cell up
                for (int ll = 0; ll < l; ll++)
                {
                    if (IsCellEmpty(c, ll))
                    {
                        grid_movement_occured = true;
                        MoveTile(m_grid[ll][c], current_tile);
                        break;
                    }
                }
            }
        }
    }

    return grid_movement_occured;
}

void Grid::Update(const GridMovement & direction)
{
    bool grid_movement_occured = false;
    switch (direction)
    {
    using enum GridMovement;
    case LEFT:
    {
        grid_movement_occured = MoveGridLeft();
    }
    break;
    case RIGHT:
    {
        grid_movement_occured = MoveGridRight();
    }
    break;
    case UP:
    {
        grid_movement_occured = MoveGridUp();
    }
    break;
    case DOWN:
    {
        grid_movement_occured = MoveGridDown();
    }
    break;
    
    default:
        break;
    }

    // Avoid infinite loop
    if (IsGridFull() == false && grid_movement_occured)
    {
        DropRandomTile();
    }
}

bool Grid::IsCellEmpty(uint32_t x, uint32_t y) const
{
    return (m_grid[y][x].Value() == 0);
}

bool Grid::IsGridStuck() const
{
    for (int l = 0; l < m_grid.size(); l++)
    {
        for (int c = 0; c < m_grid[l].size(); c++)
        {
            Tile current_tile = m_grid[l][c];

            if (current_tile.Value() == 0)
            {
                return false;
            }

            if (c != grid_width - 1)
            {
                Tile right_tile = m_grid[l][c+1];
                if (right_tile.Value() == current_tile.Value())
                {
                    return false;
                }
            }

            if (l != grid_height - 1)
            {
                Tile down_tile = m_grid[l+1][c];
                if (down_tile.Value() == current_tile.Value())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Grid::IsGridFull() const
{
    for (int l = 0; l < m_grid.size(); l++)
    {
        for (int c = 0; c < m_grid[l].size(); c++)
        {
            if (IsCellEmpty(c, l))
            {
                return false;
            }
        }
    }
    return true;
}

void Grid::ResetGrid()
{
    for (auto & grid_line : m_grid)
    {
        grid_line.fill(Tile(0));
    }

    DropRandomTile();
    DropRandomTile();
}

void Grid::DropRandomTile()
{
    bool found_empty_spot = false;
    while (found_empty_spot == false)
    {
        uint32_t x = dist_x(mt);
        uint32_t y = dist_y(mt);

        if (IsCellEmpty(x, y))
        {
            found_empty_spot = true;

            uint32_t chance = dist_rate(mt);
            uint32_t tile_value = (chance <= 10) ? 4 : 2;
            m_grid[y][x] = Tile(tile_value);
        }
    }
}

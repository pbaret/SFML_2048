#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "tile.h"
#include "global.h"
#include <random>

#include <stdint.h>

enum class GridMovement
{
    UP, DOWN, LEFT, RIGHT
};

class Grid
{
private:
    sf::RenderWindow * m_pt_display_window;
    std::array<std::array<Tile, gns::grid_width>, gns::grid_height> m_grid;

    std::random_device rd;  /**< @brief to drop food randomly */
    std::mt19937 mt;        /**< @brief to drop food randomly */
    std::uniform_int_distribution<> dist_x; /**< @brief randomly generate x coordinate (used to drop tile at random empty places) */
    std::uniform_int_distribution<> dist_y; /**< @brief randomly generate y coordinate (used to drop tile at random empty places) */
    std::uniform_int_distribution<> dist_rate; /**< @brief randomly generate y coordinate (used to drop tile at random empty places) */

private:
    inline bool IsCellEmpty(uint32_t x, uint32_t y) const;
    bool IsGridStuck() const;
    bool IsGridFull() const;
    inline void MergeTiles(Tile & dst, Tile & merged);
    inline void MoveTile(Tile & dst, Tile & src);

    bool MoveGridLeft();
    bool MoveGridRight();
    bool MoveGridUp();
    bool MoveGridDown();
    
public:
    Grid(sf::RenderWindow * pt_display_window);
    ~Grid();

    static sf::Vector2f FirstTileGUIPos;

    void Draw() const;
    void Update(const GridMovement & direction);
    void ResetGrid();
    void DropRandomTile();

};

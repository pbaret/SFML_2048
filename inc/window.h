#pragma once

#include <stdint.h>
#include "global.h"

/**
 * @brief game namespace
 */
namespace gns
{    
    constexpr uint32_t window_margin = 30;
    constexpr uint32_t tile_margin = 10;
    constexpr uint32_t tile_size = 80;
    constexpr uint32_t tile_font_size = 50;

    constexpr uint32_t info_font_size = 20;
    constexpr uint32_t box_font_size = 30;
    constexpr uint32_t box_padding = 10;

    constexpr uint32_t title_font_size = 80;

    constexpr uint32_t window_height = 
        window_margin + title_font_size + window_margin + 4 * box_padding + 3 * box_font_size + 2 * (2 * box_padding + box_font_size) + 3 * tile_margin +
        grid_height * tile_size + (grid_height + 1) * tile_margin + window_margin;

    constexpr uint32_t window_width = 
        2 * window_margin +
        (grid_width + 1) * tile_margin +
        grid_width * tile_size;
}
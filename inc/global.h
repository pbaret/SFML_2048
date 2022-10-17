#ifndef GLOBAL__H
#define GLOBAL__H

#include <stdint.h>
#include <string>
#include <SFML/Graphics.hpp>

/**
 * @brief game namespace
 */
namespace gns
{    
    constexpr uint32_t grid_width = 4;   /**< @brief Width of 2048 grid. */
    constexpr uint32_t grid_height = 4;  /**< @brief Height of 2048 grid. */

    /**
     * @brief Local anchor to place displayable elements
     */
    enum class LocalOrigin
    {
        TopLeft, Top, TopRight,
        Left, Center, Right,
        BottomLeft, Bottom, BottomRight
    };

    /**
     * @brief Set the Text Local Origin 
     * 
     * @param txt : input/output text to process
     * @param anchor : new local origin to take
     */
    inline void SetTextLocalOrigin(sf::Text & txt, LocalOrigin anchor)
    {
        auto rect = txt.getLocalBounds();
        sf::Vector2f new_anchor(0,0);

        switch (anchor)
        {
        case LocalOrigin::TopLeft:
            new_anchor = sf::Vector2f(0,0);
            break;
        case LocalOrigin::Top:
            new_anchor = sf::Vector2f(rect.width/2,0);
            break;
        case LocalOrigin::TopRight:
            new_anchor = sf::Vector2f(rect.width,0);
            break;
        case LocalOrigin::Left:
            new_anchor = sf::Vector2f(0,rect.height/2);
            break;
        case LocalOrigin::Center:
            new_anchor = sf::Vector2f(rect.width/2,rect.height/2);
            break;
        case LocalOrigin::Right:
            new_anchor = sf::Vector2f(rect.width,rect.height/2);
            break;
        case LocalOrigin::BottomLeft:
            new_anchor = sf::Vector2f(0,rect.height);
            break;
        case LocalOrigin::Bottom:
            new_anchor = sf::Vector2f(rect.width/2,rect.height);
            break;
        case LocalOrigin::BottomRight:
            new_anchor = sf::Vector2f(rect.width,rect.height);
            break;
        
        default:
            break;
        }

        txt.setOrigin(new_anchor);
    }

}


#endif // GLOBAL__H

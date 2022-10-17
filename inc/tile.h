#pragma once

#include <stdint.h>

class Tile
{
private:
    uint32_t m_value;

public:
    Tile(uint32_t value = 0);
    ~Tile();

    uint32_t Value() const { return m_value; }
    void SetValue(uint32_t new_value) { m_value = new_value; }

    void Pow() { m_value *= 2; };
};


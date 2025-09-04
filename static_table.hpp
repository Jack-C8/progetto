#ifndef EL_STATIC_TABLE_HPP
#define EL_STATIC_TABLE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "base_graphics.hpp"
#include "game_state.hpp"
#include "card_renderer.hpp"

namespace el {
void drawStaticTable(sf::RenderWindow& window, sf::Font& font,
                     float fishes_left, int score, const sf::Texture texture1,
                     const sf::Texture texture2,
                      GameState& state, CardRenderer& renderer, unsigned int& currentTurn);

void firstWindow(sf::RenderWindow& first_window, sf::Font& font);

}  // namespace el

#endif
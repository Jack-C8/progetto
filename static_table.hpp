#ifndef EL_STATIC_TABLE_HPP
#define EL_STATIC_TABLE_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "base_graphics.hpp"
#include "buttons.hpp"
#include "card.hpp"
#include "hand.hpp"
#include "methods.hpp"

namespace el {
void drawStaticTable(sf::RenderWindow& window, sf::Font& font,
                     float fishes_left, int score, const sf::Texture& texture1,
                     const sf::Texture& texture2,

                     std::vector<sf::Text>& allLetters);
void First_Window(sf::RenderWindow& first_window, sf::Font& font);
void overlay(sf::RenderWindow& window, Buttons& buttons, GameState& state,
             sf::Font& font, sf::Text& bet_text, const std::string& bet_input);
}  // namespace el
#endif
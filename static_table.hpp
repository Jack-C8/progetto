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
#include "card.hpp"
#include "card_renderer.hpp"
#include "hand.hpp"

namespace el {
void drawStaticTable(sf::RenderWindow& window, sf::Font& font,
                     float fishes_left, int score, const sf::Sprite& sprite,
                     const sf::Sprite& sprite2,

                     std::vector<sf::Text>& allLetters);

extern ::sf::RectangleShape hit_button;
extern ::sf::RectangleShape stand_button;
extern ::sf::RectangleShape double_button;
void firstWindow(sf::RenderWindow& first_window, sf::Font& font);
extern ::sf::RectangleShape input_box;
extern ::sf::RectangleShape ok_button;
}  // namespace el

#endif
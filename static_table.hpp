#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "CardRenderer.hpp"
#include "basegraphics.hpp"
#include "card.hpp"
#include "hand.hpp"
#pragma once

namespace el {
void DrawStaticTable(sf::RenderWindow& window, sf::Font& font,
                     float fishes_left, int score, const sf::Sprite& sprite,
                     const sf::Sprite& sprite2,

                     std::vector<sf::Text>& allLetters);

extern ::sf::RectangleShape hit_button;
extern ::sf::RectangleShape stand_button;
extern ::sf::RectangleShape double_button;
void First_Window(sf::RenderWindow& first_window, sf::Font& font);
extern ::sf::RectangleShape input_box;
extern ::sf::RectangleShape ok_button;
} 
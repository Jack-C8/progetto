#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "basegraphics.hpp"
#include "CardRenderer.hpp"
// #include "Grafiche.hpp"
#include "card.hpp"
#include "hand.hpp"

void DrawStaticTable(sf::RenderWindow& window, sf::Font& font,
               float fishes_left, int score,
               const sf::Sprite& sprite, const sf::Sprite& sprite2,
              
               const std::vector<sf::Text>& allLetters
               );
               
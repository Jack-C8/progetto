#ifndef EL_BASE_GRAPHICS_HPP
#define EL_BASE_GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>

#include "card_renderer.hpp"
#include "game_state.hpp"

namespace el {

class GameState;
class CardRenderer;

void drawText(sf::RenderWindow& window, sf::Font& font, const std::string& str,
              float x, float y, unsigned int size, sf::Color color,
              float angle_of_rotation);
void drawCircle(sf::RenderWindow& window, float x, float y, float radius,
                sf::Color background, float thickness, sf::Color borders);
sf::RectangleShape RectangularButton(float x, float y, float w, float h,
                                     sf::Color background, float thickness,
                                     sf::Color borders,
                                     float angle_of_rotation);
void drawRect(sf::RenderWindow& window, float x, float y, float w, float h,
              sf::Color background, float thickness, sf::Color borders,
              float angle_of_rotation);
std::vector<sf::Text> createCurvedText(const std::string& text,
                                       const sf::Font& font,
                                       unsigned int charSize,
                                       sf::Vector2f center, float radius,
                                       float startAngleDeg,
                                       float totalAngleDeg);

sf::Sprite getsprite(sf::RenderWindow& window, float x, float y, float x_scale,
                     float y_scale, sf::Texture texture);

void drawNewCards(sf::RenderWindow& window, GameState& state,
                  CardRenderer& renderer);
}  // namespace el

#endif
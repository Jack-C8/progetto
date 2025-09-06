#ifndef EL_BASE_GRAPHICS_HPP
#define EL_BASE_GRAPHICS_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "card.hpp"
#include "hand.hpp"
namespace el {
void drawText(sf::RenderWindow& window, sf::Font& font, const std::string& str,
              float x, float y, unsigned int size, sf::Color color,
              float angle_of_rotation);
void drawCircle(sf::RenderWindow& window, float x, float y, float radius,
                sf::Color background, float thickness, sf::Color borders);
sf::Text getText(sf::Font& font, const std::string& str, float x, float y,
                 unsigned int size, sf::Color color, float angle_of_rotation);
sf::RectangleShape RectangularButton(float x, float y, float w, float h,
                                     sf::Color background, float thickness,
                                     sf::Color borders,
                                     float angle_of_rotation);
sf::Sprite getSprite(float x, float y, float x_scale, float y_scale,
                     sf::Texture texture);
void drawRect(sf::RenderWindow& window, float x, float y, float w, float h,
              sf::Color background, float thickness, sf::Color borders,
              float angle_of_rotation);
std::vector<sf::Text> createCurvedText(const std::string& text,
                                       const sf::Font& font,
                                       unsigned int charSize,
                                       sf::Vector2f center, float radius,
                                       float startAngleDeg,
                                       float totalAngleDeg);
}  // namespace el
#endif
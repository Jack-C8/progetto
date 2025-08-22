#include <SFML/Graphics.hpp>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
void DrawText(sf::RenderWindow& window, sf::Font& font, const std::string& str,
              float x, float y, int size, sf::Color color,
              float angle_of_rotation);
void drawCircle(sf::RenderWindow& window, float x, float y, float raggio,
                sf::Color sfondo, float thickness, sf::Color bordi);
sf::RectangleShape RectangularButton(sf::RenderWindow& window, float x, float y,
                                     float w, float h, sf::Color sfondo,
                                     float thickness, sf::Color bordi,
                                     float angle_of_rotation);
void drawRect(sf::RenderWindow& window, float x, float y, float w, float h,
              sf::Color sfondo, float thickness, sf::Color bordi,
              float angle_of_rotation);
std::vector<sf::Text> createCurvedText(const std::string& text,
                                       const sf::Font& font,
                                       unsigned int charSize,
                                       sf::Vector2f center, float radius,
                                       float startAngleDeg, float totalAngleDeg,
                                       bool rotateLetters );

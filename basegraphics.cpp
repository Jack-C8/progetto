#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>
#include <cassert>
#include "basegraphics.hpp"
#include "CardRenderer.hpp"
// #include "Grafiche.hpp"
#include "card.hpp"
#include "hand.hpp"
// namespace el {
void DrawText(sf::RenderWindow& window, sf::Font& font, const std::string& str,
              float x, float y, int size, sf::Color color,
              float angle_of_rotation) {
  sf::Text text(str, font, size);
  text.setFillColor(color);
  text.setPosition(x, y);
  text.setRotation(angle_of_rotation);
  window.draw(text);
}

void drawCircle(sf::RenderWindow& window, float x, float y, float raggio,
                sf::Color sfondo, float thickness, sf::Color bordi) {
  sf::CircleShape cerchio(raggio);
  cerchio.setPosition(x - raggio, y - raggio);
  cerchio.setFillColor(sfondo);
  cerchio.setOutlineThickness(thickness);
  cerchio.setOutlineColor(bordi);
  window.draw(cerchio);
}
sf::RectangleShape RectangularButton(sf::RenderWindow& window, float x, float y,
                                     float w, float h, sf::Color sfondo,
                                     float thickness, sf::Color bordi,
                                     float angle_of_rotation) {
  sf::RectangleShape rect(sf::Vector2f(w, h));
  rect.setPosition(x, y);
  rect.setOutlineColor(bordi);
  rect.setOutlineThickness(thickness);
  rect.setFillColor(sfondo);
  rect.setRotation(angle_of_rotation);
  return rect;
}

void drawRect(sf::RenderWindow& window, float x, float y, float w, float h,
              sf::Color sfondo, float thickness, sf::Color bordi,
              float angle_of_rotation) {
  sf::RectangleShape rect(sf::Vector2f(w, h));
  rect.setPosition(x, y);
  rect.setOutlineColor(bordi);
  rect.setOutlineThickness(thickness);
  rect.setFillColor(sfondo);
  rect.setRotation(angle_of_rotation);
  window.draw(rect);
}

std::vector<sf::Text> createCurvedText(const std::string& text,
                                       const sf::Font& font,
                                       unsigned int charSize,
                                       sf::Vector2f center, float radius,
                                       float startAngleDeg, float totalAngleDeg,
                                       bool rotateLetters=true) {
  std::vector<sf::Text> letters;
  float angleStep = totalAngleDeg / static_cast<float>(text.size() - 1);

  for (std::size_t i = 0; i < text.size(); ++i) {
    float angleDeg = startAngleDeg - i * angleStep;
    float angleRad = angleDeg * 3.14159265f / 180.f;

    float x = center.x + radius * std::cos(angleRad);
    float y = center.y + radius * std::sin(angleRad);

    sf::Text letter(text[i], font, charSize);
    letter.setPosition(x, y);

    if (rotateLetters) letter.setRotation(angleDeg - 90.f);

    sf::FloatRect bounds = letter.getLocalBounds();
    letter.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    letters.push_back(letter);
  }

  return letters;
}
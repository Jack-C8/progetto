#include "base_graphics.hpp"

namespace el {
void drawText(sf::RenderWindow& window, sf::Font& font, const std::string& str,
              float x, float y, unsigned int size, sf::Color color,
              float angle_of_rotation) {
  sf::Text text(str, font, size);
  text.setFillColor(color);
  text.setPosition(x, y);
  text.setRotation(angle_of_rotation);
  window.draw(text);
}

void drawCircle(sf::RenderWindow& window, float x, float y, float radius,
                sf::Color background, float thickness, sf::Color borders) {
  sf::CircleShape circle(radius);
  circle.setPosition(x - radius, y - radius);
  circle.setFillColor(background);
  circle.setOutlineThickness(thickness);
  circle.setOutlineColor(borders);
  window.draw(circle);
}
sf::RectangleShape RectangularButton(float x, float y, float w, float h,
                                     sf::Color background, float thickness,
                                     sf::Color borders,
                                     float angle_of_rotation) {
  sf::RectangleShape rect(sf::Vector2f(w, h));
  rect.setPosition(x, y);
  rect.setOutlineColor(borders);
  rect.setOutlineThickness(thickness);
  rect.setFillColor(background);
  rect.setRotation(angle_of_rotation);
  return rect;
}

sf::Sprite getsprite(sf::RenderWindow& window, float x, float y, float x_scale,
                     float y_scale, sf::Texture texture) {
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(x_scale, y_scale);
  sprite.setPosition(x, y);
  return sprite;
}

void drawRect(sf::RenderWindow& window, float x, float y, float w, float h,
              sf::Color background, float thickness, sf::Color borders,
              float angle_of_rotation) {
  sf::RectangleShape rect(sf::Vector2f(w, h));
  rect.setPosition(x, y);
  rect.setOutlineColor(borders);
  rect.setOutlineThickness(thickness);
  rect.setFillColor(background);
  rect.setRotation(angle_of_rotation);
  window.draw(rect);
}

std::vector<sf::Text> createCurvedText(const std::string& text,
                                       const sf::Font& font,
                                       unsigned int charSize,
                                       sf::Vector2f center, float radius,
                                       float startAngleDeg,
                                       float totalAngleDeg) {
  std::vector<sf::Text> letters;
  float angleStep = totalAngleDeg / static_cast<float>(text.size() - 1);

  for (std::size_t i = 0; i < text.size(); ++i) {
    float angleDeg = startAngleDeg - static_cast<float>(i) * angleStep;
    float angleRad = angleDeg * 3.14159265f / 180.f;

    float x = center.x + radius * std::cos(angleRad);
    float y = center.y + radius * std::sin(angleRad);

    sf::Text letter(text[i], font, charSize);
    letter.setPosition(x, y);

    letter.setRotation(angleDeg - 90.f);

    sf::FloatRect bounds = letter.getLocalBounds();
    letter.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    letters.push_back(letter);
  }

  return letters;
}
}  // namespace el
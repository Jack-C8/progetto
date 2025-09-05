#include "base_graphics.hpp"
#include "game_state.hpp"
#include "card_renderer.hpp"

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

void drawNewCards(sf::RenderWindow& window, el::GameState& state,
                  CardRenderer& renderer) {
  for (unsigned int i = 0; i <= 1; i++) {
    renderer.drawCard(window, state.getPlayers()[1].getHand().handElement(i),
                      640.f + 90.f * static_cast<float>(i), 600, 0);
  }

  for (unsigned int i = 0; i <= 1; i++) {
    renderer.drawCard(window, state.getPlayers()[0].getHand().handElement(i),
                      310.f + 55.f * static_cast<float>(i),
                      420.f + 55.f * static_cast<float>(i), 45);
  }
  for (unsigned int i = 0; i <= 1; i++) {
    renderer.drawCard(window, state.getPlayers()[2].getHand().handElement(i),
                      1033.f + 57.f * static_cast<float>(i),
                      513.f - 53.f * static_cast<float>(i), 315);
  }
  for (unsigned int i = 0; i <= 1; i++) {
    renderer.drawCard(window, state.getPlayers()[3].getHand().handElement(i),
                      645.f + 80.f * static_cast<float>(i), 130, 0);
  }
}
}  // namespace el
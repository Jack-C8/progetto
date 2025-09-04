#include "buttons.hpp"

#include "base_graphics.hpp"

namespace el {

Buttons::Buttons(sf::Font& f) : font(f) {
  hit_button = RectangularButton(850, 740, 100, 50, sf::Color(150, 150, 150), 2,
                                 sf::Color::White, 0);
  stand_button = RectangularButton(980, 740, 100, 50, sf::Color(150, 150, 150),
                                   2, sf::Color::White, 0);
  double_button = RectangularButton(915, 810, 100, 50, sf::Color(150, 150, 150),
                                    2, sf::Color::White, 0);
  ok_button = RectangularButton(655, 750, 100, 50, sf::Color::White, 4,
                                sf::Color(180, 180, 180), 0);
  input_box = RectangularButton(615, 620, 200, 50, sf::Color::White, 3,
                                sf::Color::Black, 0);
}

void Buttons::drawFirstButtons(sf::RenderWindow& window) {
  window.draw(hit_button);
  window.draw(stand_button);
  window.draw(double_button);
  drawText(window, font, "STAND", 990, 750, 25, sf::Color::White, 0);
  drawText(window, font, "HIT", 880, 750, 25, sf::Color::White, 0);
  drawText(window, font, "DOUBLE", 915, 815, 25, sf::Color::White, 0);
}
}  // namespace el

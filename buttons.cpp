#include "buttons.hpp"

#include "base_graphics.hpp"

namespace el {
Buttons::Buttons(sf::Font& f) : font(f) {
  hit_button_ = RectangularButton(850, 740, 100, 50, sf::Color(150, 150, 150),
                                  2, sf::Color::White, 0);
  stand_button_ = RectangularButton(980, 740, 100, 50, sf::Color(150, 150, 150),
                                    2, sf::Color::White, 0);
  double_button_ = RectangularButton(
      915, 810, 100, 50, sf::Color(150, 150, 150), 2, sf::Color::White, 0);
  ok_button_ = RectangularButton(655, 750, 100, 50, sf::Color::White, 4,
                                 sf::Color(180, 180, 180), 0);
  input_box_ = RectangularButton(615, 620, 200, 50, sf::Color::White, 3,
                                 sf::Color::Black, 0);
  bet_box_ = RectangularButton(565, 400, 300, 80, sf::Color::White, 3.,
                               sf::Color::Black, 0.);

  ok_bet_ = RectangularButton(655, 500, 120, 60, sf::Color(200, 200, 200), 2.,
                              sf::Color::Black, 0);
}

void Buttons::drawFirstButtons(sf::RenderWindow& window) {
  window.draw(hit_button_);
  window.draw(stand_button_);
  window.draw(double_button_);
  drawText(window, font, "STAND", 990, 750, 25, sf::Color::White, 0);
  drawText(window, font, "HIT", 880, 750, 25, sf::Color::White, 0);
  drawText(window, font, "DOUBLE", 915, 815, 25, sf::Color::White, 0);
}
void Buttons::drawPayingModeButtons(sf::RenderWindow& window) {
  window.draw(bet_box_);
  window.draw(ok_bet_);
  drawText(window, font, "OK", 690, 510, 30, sf::Color::Black, 0);
}
}
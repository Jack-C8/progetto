#ifndef EL_BUTTONS_HPP
#define EL_BUTTONS_HPP
#include <SFML/Graphics.hpp>
#include <vector>

namespace el {
class Buttons {
  sf::RectangleShape hit_button_;
  sf::RectangleShape stand_button_;
  sf::RectangleShape double_button_;
  sf::RectangleShape input_box_;
  sf::RectangleShape ok_button_;
  sf::RectangleShape bet_box_;
  sf::RectangleShape ok_bet_;

  sf::Font& font;

 public:
  Buttons(sf::Font& font);

  void drawFirstButtons(sf::RenderWindow& window);
  sf::RectangleShape& getHitButton() { return hit_button_; }
  sf::RectangleShape& getStandButton() { return stand_button_; }
  sf::RectangleShape& getDoubleButton() { return double_button_; }
  sf::RectangleShape& getOkButton() { return ok_button_; }
  sf::RectangleShape& getInputBox() { return input_box_; }
  sf::RectangleShape& getOk_bet() { return ok_bet_; }
  sf::RectangleShape& getBet_box() { return bet_box_; }
  void drawPayingModeButtons(sf::RenderWindow& window);
};
}  // namespace el
#endif

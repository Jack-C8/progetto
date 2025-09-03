#ifndef EL_BUTTONS_HPP
#define EL_BUTTONS_HPP
#include <SFML/Graphics.hpp>
#include <vector>
namespace el{
class Buttons {
  
    sf::RectangleShape hit_button;
    sf::RectangleShape stand_button;
    sf::RectangleShape double_button;
    sf::RectangleShape input_box;
    sf::RectangleShape ok_button;

    sf::Font& font;
public:
    Buttons(sf::Font& font);

    
void DrawFirstButtons(sf::RenderWindow& window);
    // getter per i bottoni
    sf::RectangleShape& getHitButton()   { return hit_button; }
    sf::RectangleShape& getStandButton() { return stand_button; }
    sf::RectangleShape& getDoubleButton(){ return double_button; }
    sf::RectangleShape& getOkButton()    { return ok_button; }
    sf::RectangleShape& getInputBox()    { return input_box; }


};
}
#endif

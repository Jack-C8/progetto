#include "first_window.hpp"

namespace el {
float firstWindow() {
  sf::RenderWindow first_window(sf::VideoMode(1430, 1000), "Insert fishes");
  sf::Font font;
  if (!font.loadFromFile("assets/fonts/arial.ttf")) return -1;
  el::Buttons buttons(font);
  std::string input_str;
  std::string error_message;
  const int MAX_FISH = 1000000;
  sf::Text input_text;
  input_text.setFont(font);
  input_text.setCharacterSize(30);
  input_text.setFillColor(sf::Color::Black);
  input_text.setPosition(620, 625);

  while (first_window.isOpen()) {
    sf::Event event;
    while (first_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        first_window.close();
      }
      if (event.type == sf::Event::TextEntered) {
        if (std::isdigit(static_cast<unsigned char>(event.text.unicode))) {
          input_str += static_cast<char>(event.text.unicode);
        } else if (event.text.unicode == 8 && !input_str.empty()) {
          input_str.pop_back();
        }
      }

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),
                           static_cast<float>(event.mouseButton.y));
        if (buttons.getOkButton().getGlobalBounds().contains(mouse)) {
          if (!input_str.empty()) {
            try {
              int temp = std::stoi(input_str);
              if (temp > 0 && temp <= MAX_FISH) {
                return static_cast<float>(temp);
                first_window.close();
              } else if (temp > MAX_FISH) {
                error_message =
                    "Massimo consentito: " + std::to_string(MAX_FISH);
              } else {
                error_message = "Inserire un intero positivo!";
              }
            } catch (...) {
              error_message = "Valore non valido!";
            }
          } else {
            error_message = "Nessun valore inserito!";
          }
        }
      }
    }

    input_text.setString(input_str);
    first_window.clear(sf::Color(0, 150, 80));
    first_window.draw(buttons.getInputBox());
    first_window.draw(buttons.getOkButton());
    first_window.draw(input_text);
    First_Window(first_window, font);

    if (!error_message.empty()) {
      el::drawText(first_window, font, error_message, 570, 700, 25,
                   sf::Color::Red, 0);
    }
    first_window.display();
  }
  return 0;
}
}  // namespace el
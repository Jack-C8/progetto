#include <functional>

#include "base_graphics.hpp"
#include "buttons.hpp"
#include "card.hpp"
#include "card_renderer.hpp"
#include "first_window.hpp"
#include "game_state.hpp"
#include "hand.hpp"
#include "player.hpp"
#include "static_table.hpp"

int main() {
  sf::Clock stop;
  std::function<void()> afterWait;
  sf::Font font;
  if (!font.loadFromFile("assets/fonts/arial.ttf")) return -1;
  el::Buttons buttons(font);
  el::CardRenderer renderer("assets/fonts/arial.ttf", "assets/suits");
  sf::RenderWindow window(sf::VideoMode(1430, 1000), "Blackjack Simulator",
                          sf::Style::Default);
  window.setFramerateLimit(15);
  sf::Texture texture1, texture2;
  if (!texture1.loadFromFile("assets/Images/Fishcontainer.png")) return -1;
  if (!texture2.loadFromFile("assets/Images/cardcontainer.png")) return -1;
  std::string bet_input;
  sf::Clock error_timer;
  std::string error_message;
  sf::Text bet_text;
  bet_text.setFont(font);
  bet_text.setCharacterSize(40);
  bet_text.setFillColor(sf::Color::Black);
  bet_text.setPosition(580, 410);

  el::TurnStructure Structure{el::Phase::BETTING, 0};
  float humanFishes = el::firstwindow();
  if (humanFishes == -1) return -1;
  std::vector<float> moneyMonitor{humanFishes, 0., 1000., 1000.};
  el::GameState state(moneyMonitor);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      // betting
      if (Structure.phase == el::Phase::BETTING && Structure.turn == 0 &&
          state.getRoundOver() == false) {
        if (event.type == sf::Event::TextEntered) {
          if (std::isdigit(static_cast<unsigned char>(event.text.unicode))) {
            if (bet_input.size() < 6)
              bet_input += static_cast<char>(event.text.unicode);
          } else if (event.text.unicode == 8 && !bet_input.empty()) {
            bet_input.pop_back();
          }
        }
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),
                             static_cast<float>(event.mouseButton.y));
          if (buttons.getOk_bet().getGlobalBounds().contains(mouse) &&
              !bet_input.empty()) {
            try {
              float temp_bet = std::stoi(bet_input);
              if (temp_bet > 0 && temp_bet <= (moneyMonitor[0])) {
                moneyMonitor[1] = temp_bet;
                moneyMonitor[0] -= moneyMonitor[1];
                state.startGame(moneyMonitor);
                Structure.phase = el::Phase::ROUND;
              } else {
                error_message = "Puntata non valida (saldo: " +
                                std::to_string(moneyMonitor[0]) + ")";
                error_timer.restart();
              }
            } catch (...) {
              error_message = "Valore non valido!";
              error_timer.restart();
            }
          }
        }  // round!
      } else if (Structure.phase == el::Phase::ROUND &&
                 state.getRoundOver() == false) {
        if (Structure.turn == 0) {
          state.nextTurn(Structure.turn);
        }
        if (Structure.turn == 1) {
          if (event.type == sf::Event::MouseButtonPressed &&
              event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y));
            if (buttons.getHitButton().getGlobalBounds().contains(mousePos)) {
              state.getPlayers()[1].hit(state.getDeck());
            }
            if (buttons.getStandButton().getGlobalBounds().contains(mousePos)) {
              state.getPlayers()[1].stand();
            }
            if (buttons.getDoubleButton().getGlobalBounds().contains(
                    mousePos)) {
              state.getPlayers()[1].doubleDown(state.getDeck());
            }
          }
        }
        if (Structure.turn == 2) {
          state.nextTurn(Structure.turn);
        }
        if (Structure.turn == 3) {
          state.nextTurn(Structure.turn);
        }
        if (Structure.turn == 4 && state.getPlayers()[1].isStanding() == true) {
          el::drawNewCards(window, state, renderer);
          Structure.phase = el::Phase::PAYING;
          state.getRoundOver() = true;
          state.getPlayers()[1].isStanding() = false;  // ready for newgame
        }
      }
    }
    // paying!
    if (Structure.phase == el::Phase::PAYING && state.getRoundOver() == true) {
      std::vector<float> moneyForNewGame;
      moneyForNewGame =
          el::payOut(state, window, font, buttons, bet_text, bet_input);
      state.startGame(moneyForNewGame);
      state.getRoundOver() = false;
      Structure.phase = el::Phase::BETTING;
      Structure.turn = 0;
    }
    window.clear(sf::Color(20, 20, 20));
    el::drawStaticTable(window, font, moneyMonitor[0],
                        state.getPlayers()[1].getHand().handScore(), texture1,
                        texture2, state, renderer, Structure.turn);
    buttons.drawFirstButtons(window);
    window.display();
  }
}
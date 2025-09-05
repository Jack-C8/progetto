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
  sf::Clock stop;  // orologio per rallentare

  std::function<void()> afterWait;  // rallentamenti

  sf::Font font;  // font
  if (!font.loadFromFile("assets/fonts/arial.ttf")) {
    return -1;
  }

  el::Buttons buttons(font);  // creazione dei bottoni

  std::string bet_input;  // inizializzazione di bet_input

  sf::Clock error_timer;

  std::string error_message;

  el::CardRenderer renderer("assets/fonts/arial.ttf",
                            "assets/suits");  // creazione grafica delle carte

  sf::RenderWindow window(
      sf::VideoMode(1430, 1000), "Blackjack Simulator",
      sf::Style::Default);  // creazione della finestra di gioco

  sf::Texture texture1;
  if (!texture1.loadFromFile("assets/Images/Fishcontainer.png")) {
    return -1;
  }

  sf::Texture texture2;
  if (!texture2.loadFromFile("assets/Images/cardcontainer.png")) {
    return -1;
  }

  sf::Text bet_text;
  bet_text.setFont(font);
  bet_text.setCharacterSize(40);
  bet_text.setFillColor(sf::Color::Black);
  bet_text.setPosition(580, 410);

  unsigned int currentTurn{5};
  std::vector<float> roundOver;
  float humanFishes = el::firstwindow();  // non è così se alle fishes vogliamo
                                          // togliere la puntata
  float humanBet;  // = el::bettingMode();

  // per betText usare funzione

  el::GameState state(humanFishes, humanBet);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      //betting Mode
      if (currentTurn == 5 && state.getRoundOver() == false) {
        if (event.type == sf::Event::TextEntered) {
          if (std::isdigit(static_cast<unsigned char>(event.text.unicode))) {
            if (bet_input.size() < 6)
              bet_input += static_cast<char>(event.text.unicode);
          } else if (event.text.unicode == 8 && !bet_input.empty()) {
            bet_input.pop_back();
          }
        } //gestione dell'inserimento della puntata
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),
                             static_cast<float>(event.mouseButton.y));
          if (buttons.getOk_bet().getGlobalBounds().contains(mouse) &&
              !bet_input.empty()) {

                //controllo che mouse sia su ok e che bet non sia vuoto
            try {
              int temp_bet = std::stoi(bet_input);
              if (temp_bet > 0 && temp_bet <= static_cast<int>(humanFishes)) {
                humanBet = temp_bet;
                currentTurn = 0;
                humanFishes -= static_cast<float>(humanBet);
                el::GameState state(humanFishes, humanBet);
              } else {
                error_message =
                    "Puntata non valida (saldo: " +
                    std::to_string(static_cast<float>(humanFishes)) + ")";
                error_timer.restart();
              }
            } catch (...) {
              error_message = "Valore non valido!";
              error_timer.restart();
            }
          }
        }
        //validazione della puntata
      }
      state.startGame(humanBet, humanFishes);
      window.clear(sf::Color(20, 20, 20));
      el::drawStaticTable(window, font, humanFishes,
                          state.getPlayers()[1].getHand().handScore(), texture1,
                          texture2, state, renderer, currentTurn);
      buttons.drawFirstButtons(window);  // commentino
      assert(currentTurn == 0);
      state.nextTurn(currentTurn);  // bot1

      // turno nostro
      if (state.getPlayers()[1].isStanding() == false && currentTurn == 1) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left && currentTurn == 1) {
          sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                static_cast<float>(event.mouseButton.y));
          if (buttons.getHitButton().getGlobalBounds().contains(mousePos)) {
            state.getPlayers()[1].hit(state.getDeck());
          }
          if (buttons.getStandButton().getGlobalBounds().contains(mousePos)) {
            state.getPlayers()[1].stand();
          }
          if (buttons.getDoubleButton().getGlobalBounds().contains(mousePos)) {
            state.getPlayers()[1].doubleDown(state.getDeck());
          }
        }
      }

      state.advanceTurn(currentTurn);
      assert(currentTurn == 2);  // bot2
      state.nextTurn(currentTurn);
      assert(currentTurn == 3);
      state.nextTurn(currentTurn);  // dealer
      // el::drawcards_after_turn(state); creare funzione

      // Overlay per bet di gioco con bettingMode e definizione di humanBet

      // Disegno delle carte accedendo ai personaggi. FARE FUNZIONE

      // state.players_[i].hand_.hand_element(1) e (2)

      assert(currentTurn == 4);

      if (currentTurn == static_cast<unsigned int>(4)) {
        std::vector<float> roundOver = payOut(state, currentTurn, window, font,
                                              buttons, bet_text, bet_input);
      }
      if (!error_message.empty() &&
          error_timer.getElapsedTime().asSeconds() < 2.5f) {
        el::drawRect(window, 465, 250, 500, 80, sf::Color(200, 0, 0, 200), 2.,
                     sf::Color::White, 0);

        sf::Text err_text(error_message, font, 30);
        err_text.setFillColor(sf::Color::White);
        sf::FloatRect bounds = err_text.getLocalBounds();
        err_text.setPosition(465.f + 250.f - bounds.width / 2.f,
                             250.f + 40.f - bounds.height / 2.f);
        window.draw(err_text);
      }

      assert(currentTurn == 5);
      state.startGame(roundOver[0], roundOver[1]);
    }
  }
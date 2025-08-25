#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "CardRenderer.hpp"
#include "basegraphics.hpp"
#include "card.hpp"
#include "hand.hpp"
#include "methods.hpp"
#include "static_table.hpp"

int main() {
  sf::Clock stop;
  std::function<void()> afterWait;

  sf::Font font;
  el::GameState state;
  if (!font.loadFromFile("arial.ttf")) return -1;

  float fishes_left = 0.0f;
  int actual_bet;
  bool bettingMode = true;
  std::string bet_input;

  sf::Clock error_timer;

  sf::RenderWindow first_window(sf::VideoMode(1430, 1000), "Insert fishes");

  sf::Text input_text;
  input_text.setFont(font);
  input_text.setCharacterSize(30);
  input_text.setFillColor(sf::Color::Black);
  input_text.setPosition(620, 605);

  std::string input_str;
  std::string error_message;
  sf::Texture initial_texture;
  if (!initial_texture.loadFromFile("initial_decoration.png")) {
    return -1;
  }
  const int MAX_FISH = 1000000;

  while (first_window.isOpen()) {
    sf::Event event;
    while (first_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) first_window.close();

      if (event.type == sf::Event::TextEntered) {
        if (std::isdigit(event.text.unicode)) {
          input_str += static_cast<char>(event.text.unicode);
        } else if (event.text.unicode == 8 &&
                   !input_str.empty()) {  // backspace
          input_str.pop_back();
        }
      }

      // Bottone OK
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
        if (ok_button.getGlobalBounds().contains(mouse)) {
          if (!input_str.empty()) {
            try {
              int temp = std::stoi(input_str);
              if (temp > 0 && temp <= MAX_FISH) {
                fishes_left = temp;  // valore valido
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
    first_window.draw(input_box);
    first_window.draw(ok_button);
    first_window.draw(input_text);
    First_Window(first_window, font);

    // Messaggio errore
    if (!error_message.empty()) {
      DrawText(first_window, font, error_message, 570, 700, 25, sf::Color::Red,
               0);
    }
    Createsprite(first_window, 50, 600, 0.4f, 0.3f, initial_texture);
    first_window.display();
  }

  sf::RenderWindow window(sf::VideoMode(1430, 1000), "BlackJack Simulator",
                          sf::Style::Default);

  CardRenderer renderer("assets/fonts/arial.ttf", "assets/suits");

  std::vector<sf::Text> allLetters;

  sf::Texture texture;
  if (!texture.loadFromFile("Fishcontainer.png")) {
    return -1;  // errore se non trova l'immagine
  }
  sf::Texture texture2;
  if (!texture2.loadFromFile("cardcontainer.png")) {
    return -1;
  }

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(0.8f, 0.6f);
  sprite.setPosition(638, 10);

  sf::Sprite sprite2;
  sprite2.setTexture(texture2);
  sprite2.setScale(0.08f, 0.1f);
  sprite2.setPosition(830, 10);

  sf::RectangleShape overlay(sf::Vector2f(1430, 1000));
  overlay.setFillColor(sf::Color(0, 0, 0, 150));
  sf::RectangleShape bet_box(sf::Vector2f(300, 80));
  bet_box.setFillColor(sf::Color::White);
  bet_box.setOutlineThickness(3);
  bet_box.setOutlineColor(sf::Color::Black);
  bet_box.setPosition(565, 400);
  sf::RectangleShape ok_bet(sf::Vector2f(120, 60));
  ok_bet.setFillColor(sf::Color(200, 200, 200));
  ok_bet.setOutlineThickness(2);
  ok_bet.setOutlineColor(sf::Color::Black);
  ok_bet.setPosition(655, 500);
  sf::Text bet_text;
  bet_text.setFont(font);
  bet_text.setCharacterSize(40);
  bet_text.setFillColor(sf::Color::Black);
  bet_text.setPosition(580, 410);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (bettingMode) {
        if (event.type == sf::Event::TextEntered) {
          if (std::isdigit(event.text.unicode)) {
            if (bet_input.size() < 6)
              bet_input += static_cast<char>(event.text.unicode);
          } else if (event.text.unicode == 8 && !bet_input.empty()) {
            bet_input.pop_back();
          }
        }
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
          if (ok_bet.getGlobalBounds().contains(mouse) && !bet_input.empty()) {
            try {
              int temp_bet = std::stoi(bet_input);
              if (temp_bet > 0 && temp_bet <= (int)fishes_left) {
                actual_bet = temp_bet;
                bettingMode = false;
                fishes_left -= actual_bet;
                state = el::GameState();
              } else {
                error_message = "Puntata non valida (saldo: " +
                                std::to_string((int)fishes_left) + ")";
                error_timer.restart();
              }
            } catch (...) {
              error_message = "Valore non valido!";
              error_timer.restart();
            }
          }
        }
      }
      if (state.wait && stop.getElapsedTime().asSeconds() > 2.f) {
        state.wait = false;
        afterWait();  // esegue l’azione prevista dopo i 2 secondi
      }
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (hit_button.getGlobalBounds().contains(mousePos)) {
          state.hit = true;
        }
        if (stand_button.getGlobalBounds().contains(mousePos)) {
          state.stand = true;
        }
        if (double_button.getGlobalBounds().contains(mousePos)) {
          state.double_down = true;
        }
      }
    }
    window.clear(sf::Color(20, 20, 20));
    DrawStaticTable(window, font, fishes_left, state.your_score, sprite,
                    sprite2, allLetters);

    for (int i = 0; i <= 1; i++) {
      renderer.drawCard(window, state.your_hand.hand_element(i), 640 + 90 * i,
                        600, 0);
    }

    for (int i = 0; i <= 1; i++) {
      renderer.drawCard(window, state.bot1_hand.hand_element(i), 310 + 55 * i,
                        420 + 55 * i, 45);
    }
    for (int i = 0; i <= 1; i++) {
      renderer.drawCard(window, state.bot2_hand.hand_element(i), 1033 + 57 * i,
                        513 - 53 * i, 315);
    }
    for (int i = 0; i <= 1; i++) {
      renderer.drawCard(window, state.dealer_hand.hand_element(i), 645 + 80 * i,
                        130, 0);
    }
    if (state.bot1_turn == true) {
      bot1(state.deck, state.bot1_hand);
      state.bot1_turn = false;
      state.wait = true;

      stop.restart();
      afterWait = [&]() { state.your_turn = true; };
      drawCircle(window, 195, 570, 4., sf::Color::Green, 2., sf::Color::White);

    } else if (state.your_turn) {
      drawCircle(window, 670, 770, 4., sf::Color::Green, 2., sf::Color::White);

      if (state.hit) {
        state.your_hand.hand_draw(state.deck);
        state.your_score = state.your_hand.hand_score();
        state.hit = false;
      }
      if (state.stand) {
        state.stand = false;
        state.your_turn = false;
        state.wait = true;
        stop.restart();
        afterWait = [&]() { state.bot2_turn = true; };

        // or bot1_turn depending on your desired flow
      }
      if (state.double_down) {
        state.your_hand.hand_draw(state.deck);
        state.your_score = state.your_hand.hand_score();
        state.double_down = false;
        fishes_left -= actual_bet;
        actual_bet += actual_bet;
        state.your_turn = false;
        state.wait = true;
        stop.restart();
        afterWait = [&]() { state.bot2_turn = true; };
      }

      if (state.your_score >= 21) {
        state.your_turn = false;
        state.wait = true;
        stop.restart();
        afterWait = [&]() { state.bot2_turn = true; };
      }
    }

    else if (state.bot2_turn == true) {
      bot2(state.deck, state.bot2_hand);
      state.bot2_turn = false;
      state.wait = true;
      stop.restart();
      afterWait = [&]() { state.dealer_turn = true; };
      drawCircle(window, 1255, 560, 4., sf::Color::Green, 2., sf::Color::White);
    }
    if (state.dealer_turn == true) {
      dealer(state.deck, state.dealer_hand);
      state.dealer_turn = false;
      bettingMode = true;
      state.payingmode = true;
    }

    for (int i = 2; i < state.your_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.your_hand.hand_element(i),
                        685 + 75 * (i - 2), 500, 0);
    }
    for (int i = 2; i < state.bot1_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.bot1_hand.hand_element(i),
                        410 + 55 * (i - 2), 320 + 55 * (i - 1), 45);
    }
    for (int i = 2; i < state.bot2_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.bot2_hand.hand_element(i),
                        990 + 55 * (i - 2), 360 + 55 * (i - 1), 315);
    }
    for (int i = 2; i < state.dealer_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.dealer_hand.hand_element(i),
                        645 + 55 * (i - 2), 130 + 55 * (i - 1), 0);
    }

    if (state.your_hand.hand_score() <= 21 &&
            state.your_hand.hand_score() > state.dealer_hand.hand_score() &&
            state.payingmode ||
        state.dealer_hand.hand_score() > 21 && state.payingmode) {
      state.payingmode = false;
      fishes_left += actual_bet * 2;
    }
    if (blackjack(state.your_hand) && state.payingmode) {
      state.payingmode = false;
      fishes_left += actual_bet * 25 / 10;
    }

    if (state.your_hand.hand_score() <= 21 &&
        state.your_hand.hand_score() == state.dealer_hand.hand_score() &&
        state.payingmode) {
      fishes_left += actual_bet;
      state.payingmode = false;
    }
    if (bettingMode) {
      window.draw(overlay);
      window.draw(bet_box);
      window.draw(ok_bet);
      bet_text.setString(bet_input);
      window.draw(bet_text);
      DrawText(window, font, "OK", 690, 510, 30, sf::Color::Black, 0);
      DrawText(window, font, "Inserisci puntata:", 610, 350, 25,
               sf::Color::White, 0);
      if (!error_message.empty() &&
          error_timer.getElapsedTime().asSeconds() < 2.5f) {
        sf::RectangleShape err_box(sf::Vector2f(500, 80));
        err_box.setFillColor(sf::Color(200, 0, 0, 200));
        err_box.setOutlineThickness(2);
        err_box.setOutlineColor(sf::Color::White);
        err_box.setPosition(465, 250);
        window.draw(err_box);

        sf::Text err_text(error_message, font, 30);
        err_text.setFillColor(sf::Color::White);
        sf::FloatRect bounds = err_text.getLocalBounds();
        err_text.setPosition(465 + 250 - bounds.width / 2,
                             250 + 40 - bounds.height / 2);
        window.draw(err_text);
      }
    }
    window.display();
  }
}
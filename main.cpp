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
  int actual_bet{0};
  bool bettingMode = true;
  std::string bet_input;

  sf::Clock error_timer;

  sf::RenderWindow first_window(sf::VideoMode(1430, 1000), "Insert fishes");

  sf::Text input_text;
  input_text.setFont(font);
  input_text.setCharacterSize(30);
  input_text.setFillColor(sf::Color::Black);
  input_text.setPosition(620, 625);

  std::string input_str;
  std::string error_message;
  sf::Texture initial_texture;
  if (!initial_texture.loadFromFile("initial_decoration.png")) {
    return -1;
  }
  sf::Sprite initial_sprite;
  initial_sprite.setTexture(initial_texture);
  initial_sprite.setScale(0.2f, 0.2f);
  initial_sprite.setPosition(100, 650);
  const int MAX_FISH = 1000000;

  while (first_window.isOpen()) {
    sf::Event event;
    while (first_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        first_window.close();
      }
      if (event.type == sf::Event::TextEntered) {
        if (std::isdigit(event.text.unicode)) {
          input_str += static_cast<char>(event.text.unicode);
        } else if (event.text.unicode == 8 && !input_str.empty()) {
          input_str.pop_back();
        }
      }

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),static_cast<float>( event.mouseButton.y));
        if (ok_button.getGlobalBounds().contains(mouse)) {
          if (!input_str.empty()) {
            try {
              int temp = std::stoi(input_str);
              if (temp > 0 && temp <= MAX_FISH) {
                fishes_left = temp;
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

    if (!error_message.empty()) {
      DrawText(first_window, font, error_message, 570, 700, 25, sf::Color::Red,
               0);
    }
    first_window.draw(initial_sprite);
    first_window.display();
  }

  sf::RenderWindow window(sf::VideoMode(1430, 1000), "BlackJack Simulator",
                          sf::Style::Default);

  el::CardRenderer renderer("assets/fonts/arial.ttf", "assets/suits");

  std::vector<sf::Text> allLetters;

  sf::Texture texture;
  if (!texture.loadFromFile("Fishcontainer.png")) {
    return -1;
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

  sf::RectangleShape bet_box = RectangularButton(
      window, 565, 400, 300, 80, sf::Color::White, 3., sf::Color::Black, 0.);

  sf::RectangleShape ok_bet =
      RectangularButton(window, 655, 500, 120, 60, sf::Color(200, 200, 200), 2.,
                        sf::Color::Black, 0);
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
          sf::Vector2f mouse(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
          if (ok_bet.getGlobalBounds().contains(mouse) && !bet_input.empty()) {
            try {
              int temp_bet = std::stoi(bet_input);
              if (temp_bet > 0 && temp_bet <= (int)fishes_left) {
                actual_bet = temp_bet;
                bettingMode = false;
                fishes_left -= static_cast<float>(actual_bet);
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
      if (state.wait && stop.getElapsedTime().asSeconds() > 3.f) {
        state.wait = false;
        afterWait();
      }
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
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
      renderer.drawCard(window, state.your_hand.hand_element(i), 640.f + 90.f * static_cast<float>(i),
                        600, 0);
    }

    for (int i = 0; i <= 1; i++) {
      renderer.drawCard(window, state.bot1_hand.hand_element(i), 310.f + 55.f * static_cast<float>(i),
                        420.f + 55.f * static_cast<float>(i), 45);
    }
    for (int i = 0; i <= 1; i++) {
      renderer.drawCard(window, state.bot2_hand.hand_element(i), 1033.f + 57.f * static_cast<float>(i),
                        513.f - 53.f * static_cast<float>(i), 315);
    }
    for (int i = 0; i <= 1; i++) {
      renderer.drawCard(window, state.dealer_hand.hand_element(i), 645.f + 80.f * static_cast<float>(i),
                        130, 0);
      if (state.dealer_card_shown == false) {
        drawRect(window, 725, 130, 63, 88, sf::Color::Black, 0.,
                 sf::Color::Black, 0.);
      }
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
      }
      if (state.double_down && fishes_left >= static_cast<float>(actual_bet)) {
        state.your_hand.hand_draw(state.deck);
        state.your_score = state.your_hand.hand_score();
        state.double_down = false;
        fishes_left -= static_cast<float>(actual_bet);
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
      state.dealer_card_shown = true;
    }

    for (int i = 2; i < state.your_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.your_hand.hand_element(i),
                        685.f + 75.f * static_cast<float>(i - 2), 500.f, 0);
    }
    for (int i = 2; i < state.bot1_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.bot1_hand.hand_element(i),
                        410.f + 55.f * static_cast<float>(i - 2), 320.f + 55.f * static_cast<float>(i - 1), 45);
    }
    for (int i = 2; i < state.bot2_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.bot2_hand.hand_element(i),
                        990.f + 55.f * static_cast<float>(i-2), 415.f - 55.f * static_cast<float>(i - 2), 315);
    }
    for (int i = 2; i < state.dealer_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.dealer_hand.hand_element(i),
                        645.f , 130.f + 55.f * static_cast<float>(i - 2), 0);
    }

    if (bettingMode) {
      drawRect(window, 0, 0, 1430, 1000, sf::Color(0, 0, 0, 150), 0.,
               sf::Color::Transparent, 0.);
      window.draw(bet_box);
      window.draw(ok_bet);
      if (state.you_won) {
        DrawText(window, font, "YOU WON", 520, 100, 80, sf::Color::White, 0);
      } else if (state.draw) {
        DrawText(window, font, "IT'S A DRAW", 520, 100, 80, sf::Color::White,
                 0);
      } else {
        DrawText(window, font, "YOU LOST", 520, 100, 80, sf::Color::White, 0);
      }

      bet_text.setString(bet_input);
      window.draw(bet_text);
      DrawText(window, font, "OK", 690, 510, 30, sf::Color::Black, 0);
      DrawText(window, font, "Inserisci puntata:", 610, 350, 25,
               sf::Color::White, 0);
    }
    if (state.payingmode) {
      state.payingmode = false;

      int player_score = state.your_hand.hand_score();
      int dealer_score = state.dealer_hand.hand_score();

      state.you_won = false;
      state.draw = false;

      if (state.your_hand.blackjack() == true) {
        fishes_left += static_cast<float>(actual_bet * 2.5);
        state.you_won = true;
      } else if (player_score <= 21 && dealer_score > 21) {
        fishes_left += static_cast<float>(actual_bet * 2);
        state.you_won = true;
      } else if (player_score <= 21 && player_score > dealer_score) {
        fishes_left +=static_cast<float>(actual_bet * 2);
        state.you_won = true;
      } else if (player_score <= 21 && player_score == dealer_score) {
        fishes_left += static_cast<float>(actual_bet);
        state.draw = true;
      }
      bet_text.setString(bet_input);
      window.draw(bet_text);
      DrawText(window, font, "OK", 690, 510, 30, sf::Color::Black, 0);
      DrawText(window, font, "Inserisci puntata:", 610, 350, 25,
               sf::Color::White, 0);
    }

    if (!error_message.empty() &&
        error_timer.getElapsedTime().asSeconds() < 2.5f) {
      drawRect(window, 465, 250, 500, 80, sf::Color(200, 0, 0, 200), 2.,
               sf::Color::White, 0);

      sf::Text err_text(error_message, font, 30);
      err_text.setFillColor(sf::Color::White);
      sf::FloatRect bounds = err_text.getLocalBounds();
      err_text.setPosition(465.f + 250.f - bounds.width / 2.f,
                           250.f + 40.f - bounds.height / 2.f);
      window.draw(err_text);
      state.dealer_card_shown = true;
    }
    window.display();
}
}
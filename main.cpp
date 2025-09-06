#include "base_graphics.hpp"
#include "buttons.hpp"
#include "card.hpp"
#include "card_renderer.hpp"
#include "first_window.hpp"
#include "hand.hpp"
#include "methods.hpp"
#include "static_table.hpp"

int main() {
  sf::Clock stop;
  std::function<void()> afterWait;
  std::string error_message;
  sf::Font font;
  el::GameState state;

  if (!font.loadFromFile("assets/fonts/arial.ttf")) {
    std::cerr << "Errore caricamento font!" << std::endl;
    return -1;
  }
  el::Buttons buttons(font);
  state.getYourFishes() = el::firstWindow();
  int actual_bet = 0;
  std::string bet_input;
  sf::Clock error_timer;
  sf::RenderWindow window(sf::VideoMode(1430, 1000), "BlackJack Simulator",
                          sf::Style::Default);
  el::CardRenderer renderer("assets/fonts/arial.ttf", "assets/suits");
  sf::Texture texture1, texture2;
  if (!texture1.loadFromFile("assets/Images/Fishcontainer.png") ||
      !texture2.loadFromFile("assets/Images/cardcontainer.png")) {
    std::cerr << "Errore caricamento texture!" << std::endl;
    return -1;
  }

  std::vector<sf::Text> allLetters;
  sf::Text bet_text =
      el::getText(font, "", 580, 410, 40, sf::Color::Black, 0.f);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (state.getPhases()[0] || state.getPhases()[5]) {
        state.handleBetting(buttons, state.getYourFishes(), actual_bet,
                            bet_input, error_message, error_timer, bet_text,
                            afterWait, event);
      } else if (state.getPhases()[2]) {
        state.playerHandleEvent(stop, afterWait, state.getYourFishes(),
                                actual_bet, buttons, event);
      }
    }
    if (state.wait && stop.getElapsedTime().asSeconds() > 3.f) {
      state.wait = false;
      if (afterWait) afterWait();
    }
    window.clear(sf::Color(20, 20, 20));
    el::drawStaticTable(window, font, state.getYourFishes(),
                        state.getYourScore(), texture1, texture2, allLetters);
    el::drawInitialCards(window, renderer, state);
    el::drawAdditionalCards(window, renderer, state);
    if (state.getPhases()[1]) state.botTurn(stop, afterWait, 1);
    if (state.getPhases()[3]) state.botTurn(stop, afterWait, 2);
    if (state.getPhases()[4]) {
      state.dealerPlay();
      state.advanceTurn(4);
      state.dealer_card_shown = true;
      state.calculatePayout(state.getYourFishes(), actual_bet);
    }
    if (state.getPhases()[0] || state.getPhases()[5]) {
      el::overlay(window, buttons, state, font, bet_text, bet_input);
    }
    if (!error_message.empty() &&
        error_timer.getElapsedTime().asSeconds() < 2.5f) {
      state.drawError(window, error_message, font);
    }
    state.drawPlayerUI(window);
    window.display();
  }
}

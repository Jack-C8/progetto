#ifndef EL_METHODS_HPP
#define EL_METHODS_HPP

#include <SFML/Graphics.hpp>
#include <cctype>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>

#include "base_graphics.hpp"
#include "buttons.hpp"
#include "card.hpp"
#include "hand.hpp"

namespace el {

class GameState {
 private:
  Deck deck;
  Hand your_hand;
  Hand bot1_hand;
  Hand bot2_hand;
  Hand dealer_hand;

  std::vector<bool> phases{false, false, false, false, false, false};
  float yourFishes;
  int your_score{0};

 public:
  bool dealer_card_shown{false};
  bool you_won{false};
  bool draw{false};
  bool hit{false};
  bool stand{false};
  bool wait{false};
  bool double_down{false};
  GameState();

  GameState(float fishes);

  void advanceTurn(unsigned int current_turn);

  void resetRound(float fishes);

  void dealerPlay();
  void bot1Play();
  void bot2Play();

  Hand& getYourHand() { return your_hand; }
  Hand& getBot1Hand() { return bot1_hand; }
  Hand& getBot2Hand() { return bot2_hand; }
  Hand& getDealerHand() { return dealer_hand; }
  float& getYourFishes() { return yourFishes; }
  std::vector<bool>& getPhases() { return phases; }
  int& getYourScore() { return your_score; }
  Deck& getDeck() { return deck; }

  void handleBetting(Buttons& buttons, float& fishes_left, int& actual_bet,
                     std::string& bet_input, std::string& error_message,
                     sf::Clock& error_timer, sf::Text& bet_text,
                     std::function<void()>& afterWait, const sf::Event& event);

  void botTurn(sf::Clock& stop, std::function<void()>& afterWait,
               const int& bot_number);

  void playerHandleEvent(sf::Clock& stop, std::function<void()>& afterWait,
                         float& fishes_left, int& actual_bet, Buttons& buttons,
                         const sf::Event& event);

  void drawPlayerUI(sf::RenderWindow& window);
  void drawError(sf::RenderWindow& window, const std::string& message,
                 sf::Font& font);

  void calculatePayout(float& fishes_left, int actual_bet);
};

}  // namespace el
#endif

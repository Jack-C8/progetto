#ifndef EL_GAME_STATE_HPP
#define EL_GAME_STATE_HPP

#include <vector>

#include "base_graphics.hpp"
#include "buttons.hpp"
#include "card.hpp"
#include "hand.hpp"
#include "player.hpp"

namespace el {

class GameState {
 private:
  Deck deck_;
  std::vector<Player> players_;
  bool roundOver{false};
  float humanStartingFishes_;
  float humanGameBet_;
  bool dealerCardShown{false};

 public:
  GameState(float humanStartingFishes, float humanGameBet);

  void startGame(float humanFishes, float humanBet);

  void nextTurn(unsigned int& currentTurn);

  void advanceTurn(unsigned int& currentTurn);

  void botLogic1(Player& bot1, const Hand& dealerHand);

  void botLogic2(Player& bot2, const Hand& dealerHand);

  void dealerLogic(Player& player);

  std::vector<Player>& getPlayers() { return players_; }

  Deck& getDeck();
};

std::vector<float> payOut(GameState& state, unsigned int currentTurn,
                          sf::RenderWindow& window, sf::Font& font,
                          el::Buttons buttons, sf::Text bet_text,
                          std::string bet_input);

};  // namespace el

#endif
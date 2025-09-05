#ifndef EL_GAME_STATE_HPP
#define EL_GAME_STATE_HPP

#include <SFML/Graphics.hpp>
#include <cassert>
#include <vector>

#include "base_graphics.hpp"
#include "buttons.hpp"
#include "card.hpp"
#include "card_renderer.hpp"
#include "hand.hpp"
#include "player.hpp"

namespace el {
enum class Phase { BETTING, ROUND, PAYING };

struct TurnStructure {
  Phase phase;
  unsigned int turn;
};

class GameState {
 private:
  Deck deck_;
  std::vector<Player> players_;
  std::vector<float> moneyMonitor_;
  bool roundOver_{false};
  bool dealerCardShown_{false};

 public:
  GameState(std::vector<float>& moneyMonitor);

  void startGame(std::vector<float>& moneyMonitor);

  void nextTurn(unsigned int& currentTurn);

  void advanceTurn(unsigned int& currentTurn);

  void botLogic1(Player& bot1, const Hand& dealerHand);

  void botLogic2(Player& bot2, const Hand& dealerHand);

  void dealerLogic(Player& player);

  std::vector<Player>& getPlayers();

  Deck& getDeck();

  bool& getRoundOver();
};

std::vector<float> payOut(GameState& state, sf::RenderWindow& window,
                          sf::Font& font, el::Buttons buttons,
                          sf::Text bet_text, std::string bet_input);

};  // namespace el

#endif
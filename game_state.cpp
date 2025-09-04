#include "game_state.hpp"

#include "card.hpp"
#include "hand.hpp"
#include "player.hpp"

namespace el {

GameState::GameState(float humanStartingFishes, float humanGameBet)
    : humanStartingFishes_(humanStartingFishes), humanGameBet_(humanGameBet) {
  float humanBet = humanGameBet;
  float humanFishes = humanStartingFishes_;
  startGame(humanFishes, humanBet);
}

void GameState::startGame(float humanFishes, float humanBet) {
  getPlayers().clear();
  deck_.shuffle();

  getPlayers().emplace_back(PlayerType::Bot1, 1000, 50);
  getPlayers().emplace_back(PlayerType::Human, humanFishes, humanBet);
  getPlayers().emplace_back(PlayerType::Bot2, 1000, 50);
  getPlayers().emplace_back(PlayerType::Dealer);

  for (int p = 0; p < getPlayers().size(); ++p) {
    getPlayers()[p].getHand() = Hand(deck_.topCard(), deck_.topCard());
  }
}

void GameState::nextTurn() {
  Player& current = getPlayers()[currentTurn];

  if (current.getType() == PlayerType::Bot1) {
    botLogic1(current, players_.back().getHand());
    advanceTurn();
  } else if (current.getType() == PlayerType::Dealer) {
    dealerLogic(current);
    advanceTurn();
  } else if (current.getType() == PlayerType::Bot2) {
    botLogic2(current, players_.back().getHand());
    advanceTurn();
  }
}

void GameState::advanceTurn() {
  ++currentTurn;
  if (currentTurn >= getPlayers().size()) {
    roundOver = true;
  }
}

void GameState::botLogic1(Player& bot1, const Hand& dealerHand) {
  unsigned int dealerFirstCard = 0;
  const Card& dealerCard = dealerHand.handElement(dealerFirstCard);
  int botScore = bot1.getHand().handScore();
  float botBet = bot1.getBet();

  if (botScore == 13 && dealerCard.game_value_ < 10) {
    bot1.doubleDown(deck_);
  } else if (botScore < 5) {
    bot1.hit(deck_);
    bot1.hit(deck_);
    bot1.hit(deck_);
  } else if (botScore == 10 && dealerCard.game_value_ < 6) {
    bot1.doubleDown(deck_);
  } else {
    while (bot1.getHand().handScore() < 15) {
      bot1.hit(deck_);
    }
  }

  bot1.stand();
}

void GameState::botLogic2(Player& bot2, const Hand& dealerHand) {
  unsigned int dealerFirstCard = 0;
  const Card& dealerCard = dealerHand.handElement(dealerFirstCard);
  int botScore = bot2.getHand().handScore();
  float botBet = bot2.getBet();

  if (botScore == 11 && dealerCard.game_value_ < 8) {
    bot2.doubleDown(deck_);
  } else if (botScore < 5) {
    bot2.hit(deck_);
    bot2.hit(deck_);
    bot2.hit(deck_);
  } else if (botScore == 7 && dealerCard.game_value_ < 9) {
    bot2.hit(deck_);
    bot2.doubleDown(deck_);
  } else {
    while (bot2.getHand().handScore() < 17) {
      bot2.hit(deck_);
    }
  }

  bot2.stand();
}

void GameState::dealerLogic(Player& dealer) {
  while (dealer.getHand().handScore() <= 16) {
    dealer.hit(deck_);
  }
  dealer.stand();
}

std::vector<Player>& GameState::getPlayers() { return players_; }

void payOut(GameState& state) {
  int dealerScore = state.getPlayers().back().getHand().handScore();

  for (int i = 0; i < 3; ++i) {
    if (state.getPlayers()[i].getHand().blackjack() == true) {
      state.getPlayers()[i].getFishes() +=
          (2.5 * state.getPlayers()[i].getBet());
      break;
    }

    if (state.getPlayers()[i].getHand().handScore() > dealerScore &&
        state.getPlayers()[i].getHand().handScore() <= 21) {
      state.getPlayers()[i].getFishes() += state.getPlayers()[i].getBet();
    } else if (state.getPlayers()[i].getHand().handScore() < 21 &&
               dealerScore > 21) {
      state.getPlayers()[i].getFishes() += state.getPlayers()[i].getBet();
    }
  }
}
};  // namespace el
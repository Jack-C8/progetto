#include "gamestate.hpp"

#include "card.hpp"
#include "hand.hpp"
#include "player.hpp"

namespace el {

GameState::GameState(float humanStartingFishes, float humanGameBet)
    : humanStartingFishes_(humanStartingFishes), humanGameBet_(humanGameBet) {
  float humanBet = humanGameBet_;
  float humanFishes = humanStartingFishes_;
  startGame(humanFishes, humanBet);
}  // più flessibile ricominciare richiamando startGame()

void GameState::startGame(float humanFishes, float humanBet) {
  players_.clear();
  deck_.shuffle();

  players_.emplace_back(PlayerType::Bot1, 1000, 50);
  players_.emplace_back(PlayerType::Human, humanFishes, humanBet);
  players_.emplace_back(PlayerType::Bot2, 1000, 50);
  players_.emplace_back(PlayerType::Dealer);

  for (int p = 0; p < players_.size(); ++p) {
    players_[p].hand_ = Hand(deck_.topCard(), deck_.topCard());
  }
}

void GameState::nextTurn() {
  Player& current = players_[current_turn];

  if (current.type_ == PlayerType::Bot1) {
    botLogic1(current, players_.back().hand_);
    advanceTurn();
  } else if (current.type_ == PlayerType::Dealer) {
    dealerLogic(current);
    advanceTurn();
  } else if (current.type_ == PlayerType::Bot2) {
    botLogic2(current, players_.back().hand_);
    advanceTurn();
  }
}

void GameState::advanceTurn() {
  ++current_turn;
  if (current_turn >= players_.size()) {
    round_over = true;
  }
}

void GameState::botLogic1(Player& bot1, Hand& dealerHand) {
  const Card& dealerCard = dealerHand.hand_element(0);
  int botScore = bot1.hand_.hand_score();
  float botBet = bot1.bet_;

  if (botScore == 13 && dealerCard.game_value_ < 10) {
    bot1.double_down(deck_);
  } else if (botScore < 5) {
    bot1.hit(deck_);
    bot1.hit(deck_);
    bot1.hit(deck_);
  } else if (botScore == 10 && dealerCard.game_value_ < 6) {
    bot1.double_down(deck_);
  } else {
    while (bot1.hand_.hand_score() < 15) {
      bot1.hit(deck_);
    }
  }

  bot1.stand();
}

void GameState::botLogic2(Player& bot2, Hand& dealerHand) {
  const Card& dealerCard = dealerHand.hand_element(0);
  int botScore = bot2.hand_.hand_score();
  float botBet = bot2.bet_;

  if (botScore == 11 && dealerCard.game_value_ < 8) {
    bot2.double_down(deck_);
  } else if (botScore < 5) {
    bot2.hit(deck_);
    bot2.hit(deck_);
    bot2.hit(deck_);
  } else if (botScore == 7 && dealerCard.game_value_ < 9) {
    bot2.hit(deck_);
    bot2.double_down(deck_);
  } else {
    while (bot2.hand_.hand_score() < 17) {
      bot2.hit(deck_);
    }
  }

  bot2.stand();
}

void GameState::dealerLogic(Player& player) {
  while (player.hand_.hand_score() <= 16) {
    player.hit(deck_);
  }
}

void payout(GameState& state) {
  int dealerScore = state.players_.back().hand_.hand_score();

  for (int i = 0; i < 3; ++i) {
    if (state.players_[i].hand_.blackjack() == true) {
      state.players_[i].fishes_ += (2.5 * state.players_[i].bet_);
      break;
    }

    if (state.players_[i].hand_.hand_score() > dealerScore &&
        state.players_[i].hand_.hand_score() <= 21) {
      state.players_[i].fishes_ += state.players_[i].bet_;
    } else if (state.players_[i].hand_.hand_score() < 21 && dealerScore > 21) {
      state.players_[i].fishes_ += state.players_[i].bet_;
    }
  }
}
};  // namespace el
#ifndef EL_METHODS_HPP
#define EL_METHODS_HPP

#include <numeric>
#include <stdexcept>
#include <vector>

#include "card.hpp"
#include "hand.hpp"

namespace el {

struct GameState {
  Deck deck;
  Hand your_hand;
  Hand bot1_hand;
  Hand bot2_hand;
  Hand dealer_hand;
  bool has_split{false};
  bool bot1_turn{true};
  bool your_turn{false};
  bool split_turn{false};
  bool bot2_turn{false};
  bool dealer_turn{false};
  bool hit{false};
  bool stand{false};
  bool wait{false};
  int your_score{0};
  bool game_over{false};
  bool payingmode = false;
  bool double_down{false};
  bool dealer_card_shown{false};
  bool you_won;
  bool draw;
  GameState();
};

void dealer(Deck& deck, Hand& hand);

void bot1(Deck& deck, Hand& hand);

void bot2(Deck& deck, Hand& hand);


}

#endif
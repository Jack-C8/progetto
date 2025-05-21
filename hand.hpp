#ifndef  HD_HAND_HPP
#define HD_HAND_HPP

#include <vector>

#include "card.hpp"

namespace hd{

 class Hand
  {
    std::vector<el::Card> hand_;

public:
Hand(el::Card c1, el::Card c2)  {
  hand_.push_back(c1);
  hand_.push_back(c2);

}

int card_number(hd::Hand);
    int score();

    void Draw(el::Deck &deck);

    void covered_Draw(el::Deck &deck);

    void reveal();

    std::vector<el::Card> hand() const;
  };
}
  #endif
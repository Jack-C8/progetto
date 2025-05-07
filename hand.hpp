#ifndef  HD_HAND_HPP
#define HD_HAND_HPP

#include <vector>

#include "card.hpp"

namespace hd{

 class Hand
  {
    std::vector<el::Card> hand_;

public:
    int score();

    void Draw(el::Deck &deck);

    void covered_Draw(el::Deck &deck);

    void reveal();

    std::vector<el::Card> hand() const;
  };
}
  #endif
#ifndef HD_HAND_HPP
#define HD_HAND_HPP

#include <vector>

#include "card.hpp"

namespace el
{

    class Hand
    {
        std::vector<Card> hand_{};

    public:
        Hand(Card c1, Card c2);

        const Card element(int i) const;

        int size();

        int score();

        void Draw(el::Deck &deck);

        void covered_Draw(el::Deck &deck);

        void reveal();

        std::vector<el::Card> hand() const;
    };
}
#endif
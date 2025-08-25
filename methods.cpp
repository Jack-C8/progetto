#include "methods.hpp"

#include "card.hpp"
#include "hand.hpp"

namespace el {

GameState::GameState() : deck() {
  deck.shuffle();
  your_hand = Hand(deck.topCard(), deck.topCard());
  bot1_hand = Hand(deck.topCard(), deck.topCard());
  bot2_hand = Hand(deck.topCard(), deck.topCard());
  dealer_hand = Hand(deck.topCard(), deck.topCard());
  your_score = your_hand.hand_score();
}

void dealer(Deck& deck, Hand& hand) {
  while (hand.hand_score() <= 16) {
    hand.hand_draw(deck);
  }
}

void bot1(Deck& deck, Hand& hand) {
  while (hand.hand_score() <= 16) {
    hand.hand_draw(deck);
  }
}

void bot2(Deck& deck, Hand& hand) {
  while (hand.hand_score() <= 17) {
    hand.hand_draw(deck);
}
}

}
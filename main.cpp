#include <iostream>
// #include <algorithm>

#include "card.hpp"
#include "hand.hpp"
// vogliamo mettere dei timer che mettono tipo 1/2 sec tra le pescate e tra le
// azioni dei bot? -J

void bot_turn(el::Deck deck, el::Hand hand, int n) {
  if (hand.hand_score() <= n) {  // bot 1: n=14 perchè appena più di metà delle carte
    hand.hand_draw(deck);        // mi fanno stare dentro i 21
    // stampa carta sul tavolo     bot 2: n=17 perchè appena meno di un terzo
    // delle carte
  }  // mi fanno stare dentro i 21
}

void bet_result(int money, int bet, el::Hand hand, el::Hand dealer_hand) {
  if (dealer_hand.hand_score() > hand.hand_score() || hand.hand_score() > 21) {
    money -= bet;
  }
  if (dealer_hand.hand_score() < hand.hand_score()) {
    money += bet;
  }
}

int main() {
  std::cout << "Quanti soldi vuole convertire in fish?\n";
  int player_money;
  std::cin >> player_money;
  int bot1_money{100};
  int bot2_money{100};
  el::Deck deck;

  // stampa schermata iniziale
  // stampa schermata di gioco

  while (/*giocatore non clicca pulsante esci*/ ||
         soldi_player == 0)  // turno completo di gioco
  {
    int player_bet = ;  // il giocatore deve sceglierlo dalla schermata
    int bot1_bet{10};
    int bot2_bet{10};

    el::Hand player_hand;
    el::Hand dealer_hand;
    el::Hand bot1_hand;
    el::Hand bot2_hand;

    bot1_hand.hand_draw(deck);
    player_hand.hand_draw(deck);
    bot2_hand.hand_draw(deck);
    dealer_hand.hand_draw(deck);

    bot1_hand.hand_draw(deck);
    player_hand.hand_draw(deck);
    bot2_hand.hand_draw(deck);
    dealer_hand.covered_hand_draw(deck);
    // stampa carte sul tavolo man mano che vengono pescate

    bot_turn(deck, bot1_hand, 15);

    // turno giocatore
    if (/*giocatore clicca su double*/) {
      player_bet = player_bet * 2;
    }
    while (/* giocatore non ha cliccato su "stand" */ ||
           player_hand.hand_score() >= 21) {
      if (/*giocatore clicca hit*/) {
        player_hand.hand_draw(deck);
        // stampa carta sul tavolo
      }
    }

    bot_turn(deck, bot2_hand, 17);
    // turno dealer
    dealer_hand.reveal();
    std::vector<el::Card> dealer_vector = dealer_hand.hand();
    const auto iter = std::find_if(
        dealer_vector.begin(), dealer_vector.end(),
        [](el::Card c) { return c.range_ == "A" && c.game_value_ == 11; });
    if (dealer_hand.hand_score() <= 16 ||
        (dealer_hand.hand_score() == 17 &&
         iter != dealer_vector
                     .end())) {  // la seconda condizione è per il "soft 17":
      dealer_hand.hand_draw(
          deck);  // se il dealer ha 17 ma ha almeno un asso che sta valendo 11
      // stampa carta         //   deve pescare di nuovo (altrimenti pesca solo
      // se ha meno di 17)
    }  // (l'asso può valere 1 o 11)
    bet_result(bot1_money, bot1_bet, bot1_hand, dealer_hand);
    bet_result(player_money, player_bet, player_hand, dealer_hand);
    bet_result(bot2_money, bot2_bet, bot2_hand, dealer_hand);
  }
}
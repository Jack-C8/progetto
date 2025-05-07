#include <numeric>
#include <vector>

#include "card.hpp"

namespace hd {

class Hand {
  std::vector<el::Card> hand;

 public:
  void Draw(el::Deck& deck) {
    el::Card top = deck.topCard();
    hand.push_back(top);
  }

  int player_score(std::vector<el::Card> player_hand) {
    int score = {std::accumulate(
        player_hand.begin(), player_hand.end(), 0,
        [](int acc, el::Card card) { return acc + card.game_value; })};

    return score;

    /*questa è la funzione base di calcolo del punteggio con la quale
     vengono calcolati tutti i punteggi*/
  }
};

}  // namespace hd

/*la funzione di calcolo è implementata correttamente (spero)
per quanto riguarda il calcolo del valore dell'asso credo di aggiungere una
funzione check all'interno da fare girare di default solo per controllare se la
mano ha un asso

in caso positivo bisogna creare una funzione che viene chiamata e chiede al
giocatore quale valore attribuire a tutti gli assi che ha, banalmente direi con
un ciclo for che scorre tutte le carte e di quelle contrassegnate da range == A
lo chiede, una persona può pescare anche tutti e 12 gli assi, sarebbe un figlio
di puttana? sì.*/
#include <numeric>

#include "card.hpp"
#include "hand.hpp"

namespace hd
{
    int Hand::score()
    {
      int score = std::accumulate(hand_.begin(), hand_.end(), 0, [](int acc, el::Card card)
                                   { return acc + card.game_value_; });

      return score;
    }
// int size(hd::Hand){
//     return hand_.size();
// };
    void Hand::Draw(el::Deck &deck)
    {
      el::Card top = deck.topCard();
      hand_.emplace_back(top);
      if (score() > 21)
      {
        for (auto it = hand_.begin(); it != hand_.end(); ++it)
        {
          if (it->range_ == "A")
          {
            it->game_value_ = 1;
            break;
          }
        }
      }
    }

    void Hand::covered_Draw(el::Deck &deck)
    {
      el::Card top = deck.topCard();
      hand_.emplace_back(top);
      top.face_ == false;
      if (score() > 21) // se sfori dai 21 controlla se ci sono degli assi, assegna al primo
      {                        // che trovi il valore 1 e esci dal ciclo
        for (auto it{hand_.begin()}; it != hand_.end(); ++it)
        {
          if (it->range_ == "A")
          {
            it->game_value_ = 1;
            break;
          }
        }
      }
    }

    void Hand::reveal()
    {
      for (auto it = hand_.begin(); it != hand_.end(); ++it)
      {
        if (it->face_ == false)
        {
          it->face_ = true;
        }
      }
    }

  std::vector<el::Card> Hand::hand() const {
    return hand_;
  }

}
/*la funzione di calcolo è implementata correttamente (spero)
per quanto riguarda il calcolo del valore dell'asso credo di aggiungere una
funzione check all'interno da fare girare di default solo per controllare se la
mano ha un asso

in caso positivo bisogna creare una funzione che viene chiamata e chiede al
giocatore quale valore attribuire a tutti gli assi che ha, banalmente direi con
un ciclo for che scorre tutte le carte e di quelle contrassegnate da range == A
lo chiede, una persona può pescare anche tutti e 12 gli assi, sarebbe un figlio
di puttana? sì.*/
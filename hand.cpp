#include <numeric>
#include <vector>
// facciamo un header anche per hand? -J
#include "card.hpp"

namespace hd
{
  class Hand
  {
    std::vector<el::Card> hand_;

  public:
    int player_score()
    {
      int score = {std::accumulate(hand_.begin(), hand_.end(), 0, [](int acc, el::Card card)
                                   { return acc + card.game_value_; })};

      return score;
    }

    void Draw(el::Deck &deck)
    {
      el::Card top = deck.topCard();
      hand_.emplace_back(top);
      if (player_score() > 21)
      {
        for (auto it{hand_.begin()}; it != hand_.end(); ++it)
        {
          if ((*it).range_ == "A")
          {
            (*it).game_value_ = 1;
            break;
          }
        }
      }
    }

    void covered_Draw(el::Deck &deck)
    {
      el::Card top = deck.topCard();
      hand_.emplace_back(top);
      top.face_ == false;
      if (player_score() > 21) // se sfori dai 21 controlla se ci sono degli assi, assegna al primo
      {                        // che trovi il valore 1 e esci dal ciclo
        for (auto it{hand_.begin()}; it != hand_.end(); ++it)
        {
          if ((*it).range_ == "A")
          {
            (*it).game_value_ = 1;
            break;
          }
        }
      }
    }

    void reveal()
    {

      for (auto it = hand_.begin(); it != hand_.end(); ++it)
      {
        if ((*it).face_ == false)
        {
          (*it).face_ = true;
        }
      }
    }
  };
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
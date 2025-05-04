#include <algorithm>
#include <random>

#include "card.hpp"

namespace el
{

  Card::Card(const std::string &suit, const std::string &range, int const game_value) : suit_{suit}, range_{range}, game_value_{game_value}, face_{true} {}

  bool operator==(const Card& one, const Card &other)
  {
    if ((one.suit_ == other.suit_) && (one.range_ == other.range_))
    {
      return true;
    }
    return false;
  }

  Deck::Deck()
  {
    std::string suits[] = {"Hearts", "Clubs", "Spades", "Diamonds"};
    std::string ranges[] = {"2", "3", "4", "5", "6", "7", "8",
                            "9", "10", "J", "Q", "K", "A"};
    int game_value[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (int n{0}; n < 3; ++n)      // 3 mazzi
    {
      for (int i{0}; i < 4; ++i)
      {
        for (int j{0}; j < 13; ++j)
        {
          deck_.emplace_back(suits[i], ranges[j], game_value[j]);
        }
      }
    }
  }

  void Deck::shuffle()
  {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(deck_.begin(), deck_.end(), rng);
  }

  Card Deck::topCard()
  {
    if (deck_.size() > 30)
    {
      throw std::runtime_error{"Not enough cards, reset the game!"};
    }
    Card top = deck_.back();
    deck_.pop_back();
    return top;
  }

  size_t Deck::deck_size() const{ return deck_.size(); }

  const std::vector<Card> &Deck::get_deck() const { return deck_; }
} // namespace el

/*per deck.back chiedere se c'è bisogno della dereferenziazzione dell'ultimo
 * elemento di deck per associarlo a top*/

/* secondo me no, ho guardato su cppreference e deck.back ti restituisce una reference all'ultimo elemento
 ma non un iteratore, è un po' come quando come argomento di una funzione passi una reference
 e non il valore di per sè, non cambia nulla -J */
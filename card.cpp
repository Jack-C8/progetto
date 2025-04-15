#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <iostream> //togli appena finito, serve per testare su due piedi con cout

struct Card
{
  std::string suit_;
  std::string range_;
  int game_value_;
  Card(const std::string &suit, const std::string &range, int game_value) : suit_{suit}, range_{range}, game_value_{game_value} {}

  bool operator==(const Card &other) const
  {
    return suit_ == other.suit_ && range_ == other.range_;
  }
};

class Deck
{
  std::vector<Card> cards;

public:
  Deck()
  {
    std::string suits[] = {"Hearts", "Clubs", "Spades", "Diamonds"};
    std::string ranges[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int game_value[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    // std::string suits[] is not a lambda but contains the possible value in
    // order.

    for (int i{0}; i < 3; ++i)
    {
      for (int j{0}; j < 13; ++j)
      {
        cards.emplace_back(suits[i], ranges[j], game_value[j]);
      }
    }
  }

  void shuffle()
  {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(cards.begin(), cards.end(), rng);
  }

  Card draw() {                  // fatto io, va bene? -J
    Card c = *cards.begin();
    cards.erase(cards.begin());
    return c;
  }
  int size() const { return cards.size(); }  
  //const std::vector<Card> &getCards() const { return cards; }     secondo me non serve -J
};

/*Test da implementare: 
verifica della size di cards,
verificare che il mazzo abbia tutte le carte in modo corretto,
verificare che il mescolamento funzioni e che il mazzo cambi ordine,
verificare che i valori siano quelli giusti, 
verificare il funzionamento di erase (rimpicciolisce il mazzo di 1?)*/

int main()
{
  Card c{"spade", "3", 3};
  std::cout << c.suit_;
}
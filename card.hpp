#include <algorithm>
#include <random>
#include <string>
#include <vector>

struct Card {
  std::string suit;
  std::string range;
  int game_value;
  Card(const std::string& suit, const std::string& range, int game_value)
      : suit{suit}, range{range}, game_value{game_value} {}

  bool operator==(const Card& other) const {
    if (suit == other.suit && range == other.range) {
      return true;
    }
    return false;
  }
};
class Deck {
  std::vector<Card> cards;

 public:
  Deck() {
    std::string suits[] = {"Hearts", "Clubs", "Spades", "Diamonds"};
    std::string ranges[] = {"2", "3",  "4", "5", "6", "7", "8",
                            "9", "10", "J", "Q", "K", "A"};
    int game_value[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 13; ++j) {
        cards.emplace_back(suits[i], ranges[j], game_value[j]);
      }
    }
  }
  void shuffle() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(cards.begin(), cards.end(), rng);
  }

  size_t getNumberOfCards() const { return cards.size(); }
  const std::vector<Card>& getCards() const { return cards; }
};

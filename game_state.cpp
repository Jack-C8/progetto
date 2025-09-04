#include "game_state.hpp"

#include "card.hpp"
#include "hand.hpp"
#include "player.hpp"

namespace el {

GameState::GameState(float humanStartingFishes, float humanGameBet)
    : humanStartingFishes_(humanStartingFishes), humanGameBet_(humanGameBet) {
  float humanBet = humanGameBet;
  float humanFishes = humanStartingFishes_;
  startGame(humanFishes, humanBet);
}

void GameState::startGame(float humanFishes, float humanBet) {
  getPlayers().clear();
  deck_.shuffle();

  getPlayers().emplace_back(PlayerType::Bot1, 1000, 50);
  getPlayers().emplace_back(PlayerType::Human, humanFishes, humanBet);
  getPlayers().emplace_back(PlayerType::Bot2, 1000, 50);
  getPlayers().emplace_back(PlayerType::Dealer);

  for (int p = 0; p < getPlayers().size(); ++p) {
    getPlayers()[p].getHand() = Hand(deck_.topCard(), deck_.topCard());
  }
}

void GameState::nextTurn(unsigned int& currentTurn) {
  Player& current = getPlayers()[currentTurn];

  if (current.getType() == PlayerType::Bot1) {
    botLogic1(current, players_.back().getHand());
    advanceTurn(currentTurn);
  } else if (current.getType() == PlayerType::Dealer) {
    dealerLogic(current);
    advanceTurn(currentTurn);
  } else if (current.getType() == PlayerType::Bot2) {
    botLogic2(current, players_.back().getHand());
    advanceTurn(currentTurn);
  }
}

void GameState::advanceTurn(unsigned int& currentTurn) {
  ++currentTurn;
  if (currentTurn >= getPlayers().size()) {
    roundOver = true;
  }
}

void GameState::botLogic1(Player& bot1, const Hand& dealerHand) {
  unsigned int dealerFirstCard = 0;
  const Card& dealerCard = dealerHand.handElement(dealerFirstCard);
  int botScore = bot1.getHand().handScore();
  float botBet = bot1.getBet();

  if (botScore == 13 && dealerCard.game_value_ < 10) {
    bot1.doubleDown(deck_);
  } else if (botScore < 5) {
    bot1.hit(deck_);
    bot1.hit(deck_);
    bot1.hit(deck_);
  } else if (botScore == 10 && dealerCard.game_value_ < 6) {
    bot1.doubleDown(deck_);
  } else {
    while (bot1.getHand().handScore() < 15) {
      bot1.hit(deck_);
    }
  }

  bot1.stand();
}

void GameState::botLogic2(Player& bot2, const Hand& dealerHand) {
  unsigned int dealerFirstCard = 0;
  const Card& dealerCard = dealerHand.handElement(dealerFirstCard);
  int botScore = bot2.getHand().handScore();
  float botBet = bot2.getBet();

  if (botScore == 11 && dealerCard.game_value_ < 8) {
    bot2.doubleDown(deck_);
  } else if (botScore < 5) {
    bot2.hit(deck_);
    bot2.hit(deck_);
    bot2.hit(deck_);
  } else if (botScore == 7 && dealerCard.game_value_ < 9) {
    bot2.hit(deck_);
    bot2.doubleDown(deck_);
  } else {
    while (bot2.getHand().handScore() < 17) {
      bot2.hit(deck_);
    }
  }

  bot2.stand();
}

void GameState::dealerLogic(Player& dealer) {
  while (dealer.getHand().handScore() <= 16) {
    dealer.hit(deck_);
  }
  dealer.stand();
}

Deck& GameState::getDeck() { return deck_; }

std::vector<Player>& GameState::getPlayers() { return players_; }

std::vector<float> payOut(GameState& state, unsigned int& currentTurn,
                          sf::RenderWindow& window, sf::Font& font,
                          el::Buttons buttons, sf::Text bet_text,
                          std::string bet_input) {
  std::vector<float> utilities;
  drawRect(window, 0, 0, 1430, 1000, sf::Color(0, 0, 0, 150), 0,
           sf::Color::Transparent, 0);
  drawText(window, font, "BOT 1", 100, 20, 50, sf::Color::White, 0);
  drawText(window, font, "YOU", 530, 20, 50, sf::Color::White, 0);
  drawText(window, font, "BOT 2", 960, 20, 50, sf::Color::White, 0);

  int dealerScore = state.getPlayers().back().getHand().handScore();

  for (int i = 0; i < 3; ++i) {
    if (state.getPlayers()[i].getHand().blackjack() == true) {
      state.getPlayers()[i].getFishes() +=
          (2.5 * state.getPlayers()[i].getBet());
      drawText(window, font, "YOU WON", 100 + i * 430, 50, 50, sf::Color::White,
               0);

      break;
    }

    if (state.getPlayers()[i].getHand().handScore() > dealerScore &&
        state.getPlayers()[i].getHand().handScore() <= 21) {
      drawText(window, font, "YOU WON!", 100 + i * 430, 50, 50,
               sf::Color::White, 0);
      state.getPlayers()[i].getFishes() += (2 * state.getPlayers()[i].getBet());
    } else if (state.getPlayers()[i].getHand().handScore() < 21 &&
               dealerScore > 21) {
      drawText(window, font, "YOU WON!", 100 + i * 430, 50, 50,
               sf::Color::White, 0);
      state.getPlayers()[i].getFishes() += (2 * state.getPlayers()[i].getBet());

    } else if (state.getPlayers()[i].getHand().handScore() == dealerScore &&
               dealerScore <= 21) {
      state.getPlayers()[i].getFishes() += state.getPlayers()[i].getBet();
      drawText(window, font, "IT'S A DRAW!", 100 + i * 430, 50, 50,
               sf::Color::White, 0);

    } else {
      drawText(window, font, "YOU LOST!", 100 + i * 430, 50, 50,
               sf::Color::White, 0);
    }
  }
  utilities[0] = state.getPlayers()[1].getFishes();

  state.advanceTurn(currentTurn);
  buttons.drawPayingModeButtons(window);
  el::drawText(window, font, "Inserisci puntata:", 610, 350, 25,
               sf::Color::White, 0);
  bet_text.setString(bet_input);
  window.draw(bet_text);
  utilities[1] = std::stoi(bet_input);
  return utilities;
}
};  // namespace el
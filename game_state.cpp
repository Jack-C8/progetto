#include "game_state.hpp"

namespace el {

GameState::GameState(std::vector<float>& moneyMonitor)
    : moneyMonitor_(moneyMonitor) {
  startGame(moneyMonitor);
}

void GameState::startGame(std::vector<float>& moneyMonitor) {
  getPlayers().clear();
  deck_.shuffle();
  getPlayers().emplace_back(PlayerType::Bot1, moneyMonitor[2], 50);
  getPlayers().emplace_back(PlayerType::Human, moneyMonitor[0],
                            moneyMonitor[1]);
  getPlayers().emplace_back(PlayerType::Bot2, moneyMonitor[3], 50);
  getPlayers().emplace_back(PlayerType::Dealer, 0., 0.);

  for (int p = 0; p < getPlayers().size(); ++p) {
    getPlayers()[p].getHand() = Hand(deck_.topCard(), deck_.topCard());
  }
}

void GameState::nextTurn(unsigned int& currentTurn) {
  Player& current = getPlayers()[currentTurn];

  switch (current.getType()) {
    case PlayerType::Bot1:
      botLogic1(current, players_.back().getHand());
      advanceTurn(currentTurn);
      break;
    case PlayerType::Bot2:
      botLogic2(current, players_.back().getHand());
      advanceTurn(currentTurn);
      break;
    case PlayerType::Dealer:
      dealerLogic(current);
      advanceTurn(currentTurn);
      break;
    case PlayerType::Human:
      break;
    default:
      break;
  }
}

void GameState::advanceTurn(unsigned int& currentTurn) {
  ++currentTurn;
  if (currentTurn >= getPlayers().size()) {
    roundOver_ = true;
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

bool& GameState::getRoundOver() { return roundOver_; }

std::vector<float> payOut(GameState& state, sf::RenderWindow& window,
                          sf::Font& font, el::Buttons& buttons,
                          sf::Text& bet_text, std::string& bet_input) {
  int newBet{0};
  std::vector<float> newMoney{0., 0., 0., 0.};
  drawRect(window, 0, 0, 1430, 1000, sf::Color(0, 0, 0, 150), 0,
           sf::Color::Transparent, 0);
  drawText(window, font, "BOT 1", 100, 20, 50, sf::Color::White, 0);
  drawText(window, font, "YOU", 530, 20, 50, sf::Color::White, 0);
  drawText(window, font, "BOT 2", 960, 20, 50, sf::Color::White, 0);

  int dealerScore = state.getPlayers()[3].getHand().handScore();

  for (int i = 0; i < 3; ++i) {
    if (state.getPlayers()[i].getHand().blackjack() == true) {
      state.getPlayers()[i].getFishes() +=
          (2.5 * state.getPlayers()[i].getBet());
      drawText(window, font, "WIN!", 100 + i * 430, 50, 50, sf::Color::White,
               0);
    } else if (state.getPlayers()[i].getHand().handScore() > dealerScore &&
               state.getPlayers()[i].getHand().handScore() <= 21) {
      drawText(window, font, "WIN!", 100 + i * 430, 50, 50, sf::Color::White,
               0);
      state.getPlayers()[i].getFishes() += (2 * state.getPlayers()[i].getBet());
    } else if (state.getPlayers()[i].getHand().handScore() < 21 &&
               dealerScore > 21) {
      drawText(window, font, "WIN!", 100 + i * 430, 50, 50, sf::Color::White,
               0);
      state.getPlayers()[i].getFishes() += (2 * state.getPlayers()[i].getBet());

    } else if (state.getPlayers()[i].getHand().handScore() == dealerScore &&
               dealerScore <= 21) {
      state.getPlayers()[i].getFishes() += state.getPlayers()[i].getBet();
      drawText(window, font, "DRAW!", 100 + i * 430, 50, 50, sf::Color::White,
               0);

    } else {
      drawText(window, font, "LOSE!", 100 + i * 430, 50, 50, sf::Color::White,
               0);
    }
  }
  newMoney[2] = state.getPlayers()[0].getFishes();
  newMoney[0] = state.getPlayers()[1].getFishes();
  newMoney[3] = state.getPlayers()[2].getFishes();

  buttons.drawPayingModeButtons(window);
  el::drawText(window, font, "Inserisci puntata:", 610, 350, 25,
               sf::Color::White, 0);
  bet_text.setString(bet_input);
  window.draw(bet_text);
  if (!bet_input.empty()) {
    try {
      newBet = std::stoi(bet_input);
    } catch (...) {
      newBet = 0;
      std::cerr << "Errore conversione bet_input\n";
    }
  }

  newMoney[1] = newBet;
  assert(static_cast<float>(newBet) <= newMoney[0]);
  window.display();

  bool okClicked = false;
  while (!okClicked && window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        okClicked = true;
      }
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                              static_cast<float>(event.mouseButton.y));
        if (buttons.getOk_bet().getGlobalBounds().contains(mousePos)) {
          okClicked = true;
        }
      }
    }
    window.clear(sf::Color(20, 20, 20));
    drawRect(window, 0, 0, 1430, 1000, sf::Color(0, 0, 0, 150), 0,
             sf::Color::Transparent, 0);
    buttons.drawPayingModeButtons(window);
    el::drawText(window, font, "Inserisci puntata:", 610, 350, 25,
                 sf::Color::White, 0);
    window.draw(bet_text);
    window.display();
  }
  return newMoney;
}
};  // namespace el
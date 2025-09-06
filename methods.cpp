#include "methods.hpp"

namespace el {

GameState::GameState() {
  deck.shuffle();
  your_hand = Hand(deck.topCard(), deck.topCard());
  bot1_hand = Hand(deck.topCard(), deck.topCard());
  bot2_hand = Hand(deck.topCard(), deck.topCard());
  dealer_hand = Hand(deck.topCard(), deck.topCard());

  your_score = your_hand.handScore();
  for (size_t i = 0; i < phases.size(); ++i) phases[i] = false;
  phases[0] = true;

  wait = false;
  hit = false;
  stand = false;
  double_down = false;

  dealer_card_shown = false;
  you_won = false;
  draw = false;
}

GameState::GameState(float fishes) { resetRound(fishes); }

void GameState::resetRound(float fishes) {
  (void)fishes;
  deck = Deck();
  deck.shuffle();
  your_hand = Hand(deck.topCard(), deck.topCard());
  bot1_hand = Hand(deck.topCard(), deck.topCard());
  bot2_hand = Hand(deck.topCard(), deck.topCard());
  dealer_hand = Hand(deck.topCard(), deck.topCard());
  your_score = your_hand.handScore();

  hit = stand = wait = double_down = false;
  dealer_card_shown = you_won = draw = false;
}

void GameState::dealerPlay() {
  while (dealer_hand.handScore() <= 16) {
    dealer_hand.handDraw(deck);
  }
}

void GameState::advanceTurn(unsigned int current_turn) {
  phases[current_turn] = false;
  if (current_turn + static_cast<unsigned int>(1) <
      static_cast<unsigned int>(phases.size())) {
    phases[current_turn + static_cast<unsigned int>(1)] = true;
  }
}

void GameState::bot1Play() {
  while (bot1_hand.handScore() <= 16) {
    bot1_hand.handDraw(deck);
  }
}

void GameState::bot2Play() {
  while (bot2_hand.handScore() <= 17) {
    bot2_hand.handDraw(deck);
  }
}

void GameState::handleBetting(Buttons& buttons, float& fishes_left,
                              int& actual_bet, std::string& bet_input,
                              std::string& error_message,
                              sf::Clock& error_timer, sf::Text& bet_text,
                              std::function<void()>& afterWait,
                              const sf::Event& event) {
  bet_text.setString(bet_input);

  if (event.type == sf::Event::TextEntered) {
    unsigned int unicode = event.text.unicode;
    if (unicode == 8) {
      if (!bet_input.empty()) bet_input.pop_back();
      bet_text.setString(bet_input);
    } else if (unicode < 128 &&
               std::isdigit(static_cast<unsigned char>(unicode))) {
      if (bet_input.size() < 6) {
        bet_input.push_back(static_cast<char>(unicode));
        bet_text.setString(bet_input);
      }
    }
  }

  auto confirmBet = [&](int temp_bet) {
    actual_bet = temp_bet;
    fishes_left -= static_cast<float>(actual_bet);

    resetRound(yourFishes);
    if (phases[5] == true) phases[5] = false;
    advanceTurn(0);
    bet_input.clear();
    bet_text.setString("");
    afterWait = nullptr;
  };
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Enter) {
    if (!bet_input.empty()) {
      try {
        int temp_bet = std::stoi(bet_input);
        if (temp_bet > 0 && temp_bet <= static_cast<int>(fishes_left)) {
          confirmBet(temp_bet);
        } else {
          error_message =
              "Puntata non valida (saldo: " + std::to_string(fishes_left) + ")";
          error_timer.restart();
        }
      } catch (...) {
        error_message = "Valore non valido!";
        error_timer.restart();
      }
    }
  }

  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),
                       static_cast<float>(event.mouseButton.y));
    if (buttons.getOkBet().getGlobalBounds().contains(mouse) &&
        !bet_input.empty()) {
      try {
        int temp_bet = std::stoi(bet_input);
        if (temp_bet > 0 && temp_bet <= static_cast<int>(fishes_left)) {
          confirmBet(temp_bet);
        } else {
          error_message =
              "Puntata non valida (saldo: " + std::to_string(fishes_left) + ")";
          error_timer.restart();
        }
      } catch (...) {
        error_message = "Valore non valido!";
        error_timer.restart();
      }
    }
  }
}

void GameState::botTurn(sf::Clock& stop, std::function<void()>& afterWait,
                        const int& bot_number) {
  if (bot_number == 1 && phases[1]) {
    bot1Play();
    phases[1] = false;
    wait = true;
    stop.restart();
    afterWait = [this]() { phases[2] = true; };
  } else if (bot_number == 2 && phases[3]) {
    bot2Play();
    phases[3] = false;
    wait = true;
    stop.restart();
    afterWait = [this]() { phases[4] = true; };
  }
}

void GameState::playerHandleEvent(sf::Clock& stop,
                                  std::function<void()>& afterWait,
                                  float& fishes_left, int& actual_bet,
                                  Buttons& buttons, const sf::Event& event) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                          static_cast<float>(event.mouseButton.y));
    if (buttons.getHitButton().getGlobalBounds().contains(mousePos)) {
      hit = true;
    }
    if (buttons.getStandButton().getGlobalBounds().contains(mousePos)) {
      stand = true;
    }
    if (buttons.getDoubleButton().getGlobalBounds().contains(mousePos)) {
      double_down = true;
    }
  }

  if (hit) {
    your_hand.handDraw(deck);
    your_score = your_hand.handScore();
    hit = false;
  }

  if (stand) {
    stand = false;
    phases[2] = false;
    wait = true;
    stop.restart();
    afterWait = [this]() { phases[3] = true; };
  }

  if (double_down) {
    if (fishes_left >= static_cast<float>(actual_bet)) {
      your_hand.handDraw(deck);
      your_score = your_hand.handScore();
      fishes_left -= static_cast<float>(actual_bet);
      actual_bet += actual_bet;
      double_down = false;
      phases[2] = false;
      wait = true;
      stop.restart();
      afterWait = [this]() { phases[3] = true; };
    } else {
      double_down = false;
    }
  }

  if (your_score >= 21) {
    phases[2] = false;
    wait = true;
    stop.restart();
    afterWait = [this]() { phases[3] = true; };
  }
}

void GameState::drawPlayerUI(sf::RenderWindow& window) {
  if (phases[2]) {
    drawCircle(window, 670, 770, 4.f, sf::Color::Green, 2.f, sf::Color::White);
  }
}

void GameState::drawError(sf::RenderWindow& window, const std::string& message,
                          sf::Font& font) {
  if (message.empty()) return;
  sf::Text err_text(message, font, 30);
  err_text.setFillColor(sf::Color::White);
  sf::FloatRect bounds = err_text.getLocalBounds();
  err_text.setPosition(465.f + 250.f - bounds.width / 2.f,
                       250.f + 40.f - bounds.height / 2.f);
  el::drawRect(window, 465, 250, 500, 80, sf::Color(200, 0, 0, 200), 2.f,
               sf::Color::White, 0.f);
  window.draw(err_text);
}

void GameState::calculatePayout(float& fishes_left, int actual_bet) {
  you_won = false;
  draw = false;

  int player_score = your_hand.handScore();
  int dealer_score = dealer_hand.handScore();

  if (your_hand.blackjack()) {
    fishes_left += static_cast<float>(actual_bet * 2.5);
    you_won = true;
  } else if (player_score <= 21 && dealer_score > 21) {
    fishes_left += static_cast<float>(actual_bet * 2);
    you_won = true;
  } else if (player_score <= 21 && player_score > dealer_score) {
    fishes_left += static_cast<float>(actual_bet * 2);
    you_won = true;
  } else if (player_score <= 21 && player_score == dealer_score) {
    fishes_left += static_cast<float>(actual_bet * 1);
    draw = true;
  }
}

}  // namespace el

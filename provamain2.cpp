#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "CardRenderer.hpp"
// #include "Grafiche.hpp"
#include "card.hpp"
#include "hand.hpp"
// namespace el {
void DrawText(sf::RenderWindow& window, sf::Font& font, const std::string& str,
              float x, float y, int size, sf::Color color,
              float angle_of_rotation) {
  sf::Text text(str, font, size);
  text.setFillColor(color);
  text.setPosition(x, y);
  text.setRotation(angle_of_rotation);
  window.draw(text);
}

void drawcircle(sf::RenderWindow& window, float x, float y, float raggio,
                sf::Color sfondo, float thickness, sf::Color bordi) {
  sf::CircleShape cerchio(raggio);
  cerchio.setPosition(x - raggio, y - raggio);
  cerchio.setFillColor(sfondo);
  cerchio.setOutlineThickness(thickness);
  cerchio.setOutlineColor(bordi);
  window.draw(cerchio);
}
sf::RectangleShape RectangularButton(sf::RenderWindow& window, float x, float y,
                                     float w, float h, sf::Color sfondo,
                                     float thickness, sf::Color bordi,
                                     float angle_of_rotation) {
  sf::RectangleShape rect(sf::Vector2f(w, h));
  rect.setPosition(x, y);
  rect.setOutlineColor(bordi);
  rect.setOutlineThickness(thickness);
  rect.setFillColor(sfondo);
  rect.setRotation(angle_of_rotation);
  return rect;
}

void drawRect(sf::RenderWindow& window, float x, float y, float w, float h,
              sf::Color sfondo, float thickness, sf::Color bordi,
              float angle_of_rotation) {
  sf::RectangleShape rect(sf::Vector2f(w, h));
  rect.setPosition(x, y);
  rect.setOutlineColor(bordi);
  rect.setOutlineThickness(thickness);
  rect.setFillColor(sfondo);
  rect.setRotation(angle_of_rotation);
  window.draw(rect);
}

std::vector<sf::Text> createCurvedText(const std::string& text,
                                       const sf::Font& font,
                                       unsigned int charSize,
                                       sf::Vector2f center, float radius,
                                       float startAngleDeg, float totalAngleDeg,
                                       bool rotateLetters = true) {
  std::vector<sf::Text> letters;
  float angleStep = totalAngleDeg / static_cast<float>(text.size() - 1);

  for (std::size_t i = 0; i < text.size(); ++i) {
    float angleDeg = startAngleDeg - i * angleStep;
    float angleRad = angleDeg * 3.14159265f / 180.f;

    float x = center.x + radius * std::cos(angleRad);
    float y = center.y + radius * std::sin(angleRad);

    sf::Text letter(text[i], font, charSize);
    letter.setPosition(x, y);

    if (rotateLetters) letter.setRotation(angleDeg - 90.f);

    sf::FloatRect bounds = letter.getLocalBounds();
    letter.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    letters.push_back(letter);
  }

  return letters;
}

std::vector<sf::Vector2f> createCircularPositions(sf::Vector2f center,
                                                  float radius,
                                                  float startAngleDeg,
                                                  float totalAngleDeg,
                                                  int count) {
  std::vector<sf::Vector2f> positions;
  float angleStep = totalAngleDeg / static_cast<float>(count - 1);

  for (int i = 0; i < count; ++i) {
    float angleDeg = startAngleDeg - i * angleStep;
    float angleRad = angleDeg * 3.14159265f / 180.f;

    float x = center.x + radius * std::cos(angleRad);
    float y = center.y + radius * std::sin(angleRad);

    positions.emplace_back(x, y);
  }

  return positions;
}

void bot1(el::Deck& deck, el::Hand& hand) {
  while (hand.hand_score() <=
         18) {             // bot 1: n=14 perchè appena più di metà dhdle carte
    hand.hand_draw(deck);  // mi fanno stare dentro i 21
    // stampa carta sul tavolo     bot 2: n=17 perchè appena meno di un terzo
    // dhdle carte
  }
}
void bot2(el::Deck& deck, el::Hand& hand) {
  while (hand.hand_score() <=
         17) {             // bot 1: n=14 perchè appena più di metà dhdle carte
    hand.hand_draw(deck);  // mi fanno stare dentro i 21
    // stampa carta sul tavolo     bot 2: n=17 perchè appena meno di un terzo
    // dhdle carte
  }
}
void dealer(el::Deck& deck, el::Hand& hand) {
  while (hand.hand_score() <= 16)

  {
    hand.hand_draw(deck)
        /* code */
        ;
  }
};
struct GameState {
  el::Deck deck;
  el::Hand your_hand;
  el::Hand bot1_hand;
  el::Hand bot2_hand;
  el::Hand dealer_hand;
  bool bot1_turn{true};
  bool your_turn{false};
  bool bot2_turn{false};
  bool dealer_turn{false};
  bool hit{false};
  bool stand{false};
  bool wait{false};
  int your_score{0};
  bool game_over{false};

  GameState() : deck() {
    deck.shuffle();
    your_hand = el::Hand(deck.topCard(), deck.topCard());
    bot1_hand = el::Hand(deck.topCard(), deck.topCard());
    bot2_hand = el::Hand(deck.topCard(), deck.topCard());
    dealer_hand = el::Hand(deck.topCard(), deck.topCard());
    your_score = your_hand.hand_score();
  }
};

int main() {
  sf::Clock stop;
  std::function<void()> afterWait;
  sf::RenderWindow first_window(sf::VideoMode(1430, 1000), "Insert fishes",
                                sf::Style::Default);
  //  while (first_window.isOpen()) {
  //  sf::Event event;
  // while (first_window.pollEvent(event)) {
  // if (event.type == sf::Event::Closed) {
  //   first_window.close();  // Chiude la prima finestra
  // }
  // }

  //  first_window.clear(sf::Color(20, 20, 20));
  // first_window.display();
  //}
  sf::RenderWindow window(sf::VideoMode(1430, 1000), "BlackJack Simulator",
                          sf::Style::Default);

  CardRenderer renderer("assets/fonts/arial.ttf", "assets/suits");

  sf::Font font;
  if (!font.loadFromFile("arial.ttf")) return -1;

  std::vector<sf::Text> allLetters;

  sf::Texture texture;
  if (!texture.loadFromFile("Fishcontainer.png")) {
    return -1;  // errore se non trova l'immagine
  }
  sf::Texture texture2;
  if (!texture2.loadFromFile("cardcontainer.png")) {
    return -1;
  }

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(0.8f, 0.6f);
  sprite.setPosition(638, 10);

  sf::Sprite sprite2;
  sprite2.setTexture(texture2);
  sprite2.setScale(0.08f, 0.1f);
  sprite2.setPosition(830, 10);

  auto curved1 = createCurvedText("BLACKJACK PAYS 3 TO 2", font, 15,
                                  {715.f, 15.f}, 260.f, 180.f, 180.f);
  auto curved2 =
      createCurvedText("DEALER MUST STAND ON 17, AND MUST DRAW TO 16", font, 15,
                       {715.f, 15.f}, 350.f, 180.f, 180.f);
  allLetters.insert(allLetters.end(), curved1.begin(), curved1.end());
  allLetters.insert(allLetters.end(), curved2.begin(), curved2.end());

  std::vector<sf::Vector2f> redCircleCoords =
      createCircularPositions({715.f, 50.f}, 400.f, 180.f, 180.f, 10);

  float fishes_left{0.};
  sf::RectangleShape double_button{
      RectangularButton(window, 850, 810, 100, 50, sf::Color(150, 150, 150), 2,
                        sf::Color::White, 0)};  // double button
  sf::RectangleShape split_button{
      RectangularButton(window, 980, 810, 100, 50, sf::Color(150, 150, 150), 2,
                        sf::Color::White, 0)};  // split button

  sf::RectangleShape hit_button{
      RectangularButton(window, 850, 740, 100, 50, sf::Color(150, 150, 150), 2,
                        sf::Color::White, 0)};  // hit button
  sf::RectangleShape stand_button{
      RectangularButton(window, 980, 740, 100, 50, sf::Color(150, 150, 150), 2,
                        sf::Color::White, 0)};  // stand button

  std::vector<el::Card> hit_cards{};
  GameState state;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::R) {
          std::cout << "Restarting game...\n";
          state = GameState();
        }
      }
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (state.wait && stop.getElapsedTime().asSeconds() > 2.f) {
        state.wait = false;
        afterWait();  // esegue l’azione prevista dopo i 2 secondi
      }
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (hit_button.getGlobalBounds().contains(mousePos)) {
          state.hit = true;
        }
        if (stand_button.getGlobalBounds().contains(mousePos)) {
          state.stand = true;
          ;
        }
      }
    }

    window.clear(sf::Color(20, 20, 20));

    drawcircle(window, 715, 0, 715, sf::Color(0, 150, 80), 10.f,
               sf::Color(210, 180, 140));
    drawcircle(window, 715, 0, 320, sf::Color::Black, 5, sf::Color::White);

    drawRect(window, 660, 740, 120, 120, sf::Color(139, 0, 0), 3.f,
             sf::Color(212, 175, 55), 0);  // YOU
    drawRect(window, 440, 741, 200, 120, sf::Color(210, 180, 140), 3.,
             sf::Color(101, 67, 33), 0);  // fish slot
    drawRect(window, 645, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             0);  // card1 you
    drawRect(window, 725, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             0);  // card 2 you
    drawRect(window, 725, 130, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             0);  // card 2 dealer
    drawRect(window, 645, 130, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             0);  // card 1 dealer
    drawRect(window, 310, 420, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             45);  // carta 1 P1
    drawRect(window, 365, 475, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             45);  // carta 2 P1
    drawRect(window, 1033, 513, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             315);  // carta 1 P2
    drawRect(window, 1090, 460, 63, 88, sf::Color::White, 0.f, sf::Color::White,
             315);  // carta 2P2
    drawRect(window, 990, 415, 63, 88, sf::Color::Transparent, 1.f,
             sf::Color::Yellow, 315);  // slot carta P2
    drawRect(window, 410, 375, 63, 88, sf::Color::Transparent, 1.f,
             sf::Color::Yellow, 45);  // slot carta P1
    drawRect(window, 685, 500, 63, 88, sf::Color::Transparent, 1.f,
             sf::Color::Yellow, 0);  // slot carta you

    drawRect(window, 190, 540, 130, 130, sf::Color(10, 17, 114), 3.f,
             sf::Color(212, 175, 55), 45);  // P1 box
    drawRect(window, 1250, 530, 130, 130, sf::Color(10, 17, 114), 3.f,
             sf::Color(212, 175, 55), 45);  // P2 box
    window.draw(hit_button);
    window.draw(double_button);
    window.draw(split_button);
    window.draw(stand_button);

    // DrawText(window, font, "DEALER", 630, 20, 40, sf::Color::White, 0);
    DrawText(window, font, "PLAYER 1", 160, 590, 20, sf::Color::White, 45);
    DrawText(window, font, "PLAYER 2", 1210, 640, 20, sf::Color::White, 315);
    DrawText(window, font, "STAND", 990, 750, 25, sf::Color::White, 0);
    DrawText(window, font, "HIT", 880, 750, 25, sf::Color::White, 0);
    DrawText(window, font, "DOUBLE", 980, 820, 25, sf::Color::White, 0);
    DrawText(window, font, "SPLIT", 867, 820, 25, sf::Color::White, 0);
    DrawText(window, font, "YOU", 675, 775, 40, sf::Color::White, 0);
    DrawText(window, font, "Current Score:", 765, 495, 15, sf::Color::Black, 0);
    DrawText(window, font, std::to_string(state.your_score), 800, 510, 50,
             sf::Color::Black, 0);
    DrawText(window, font, "FISH BALANCE", 470, 750, 20, sf::Color::Black, 0);
    DrawText(window, font, std::to_string(fishes_left), 470, 805, 30,
             sf::Color::Black, 0);

    for (int i = 0; i < redCircleCoords.size(); i++) {
      drawcircle(window, redCircleCoords[i].x, redCircleCoords[i].y, 10,
                 sf::Color(168, 0, 32), 2.f, sf::Color::White);
      DrawText(window, font, std::to_string(17 + i), redCircleCoords[i].x - 5,
               redCircleCoords[i].y - 7, 10, sf::Color::White, 0);
    }

    for (const auto& letter : allLetters) window.draw(letter);
    window.draw(sprite);
    window.draw(sprite2);
    renderer.drawCard(window, state.your_hand.hand_element(0), 640, 600, 0);
    renderer.drawCard(window, state.your_hand.hand_element(1), 730, 600, 0);
    renderer.drawCard(window, state.bot1_hand.hand_element(0), 310, 420, 45);
    renderer.drawCard(window, state.bot1_hand.hand_element(1), 365, 475, 45);
    renderer.drawCard(window, state.bot2_hand.hand_element(0), 1033, 513, 315);
    renderer.drawCard(window, state.bot2_hand.hand_element(1), 1090, 460, 315);
    renderer.drawCard(window, state.dealer_hand.hand_element(0), 645, 130,
                      0);  // dealer card 1
    renderer.drawCard(window, state.dealer_hand.hand_element(1), 725, 130,
                      0);  // dealer card 2

    if (state.bot1_turn == true) {
      bot1(state.deck, state.bot1_hand);
      state.bot1_turn = false;
      state.wait = true;

      stop.restart();
      afterWait = [&]() { state.your_turn = true; };

    } else if (state.your_turn) {
      if (state.hit) {
        state.your_hand.hand_draw(state.deck);
        state.your_score = state.your_hand.hand_score();
        state.hit = false;
      } else if (state.stand) {
        state.stand = false;
        state.your_turn = false;
        state.wait = true;
        stop.restart();
        afterWait = [&]() { state.bot2_turn = true; };

        // or bot1_turn depending on your desired flow
      } else if (state.your_score >= 21) {
        std::cout << "hai perso godo" << std::endl;
        state.your_turn = false;
        state.wait = true;
        stop.restart();
        afterWait = [&]() { state.bot2_turn = true; };
      }
    }

    else if (state.bot2_turn == true) {
      bot2(state.deck, state.bot2_hand);
      state.bot2_turn = false;
      state.wait = true;
      stop.restart();
      afterWait = [&]() { state.dealer_turn = true; };

    } else if (state.dealer_turn == true) {
      dealer(state.deck, state.dealer_hand);
      state.dealer_turn = false;
    }

    for (int i = 2; i < state.your_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.your_hand.hand_element(i),
                        685 + 75 * (i - 2), 500, 0);
    }
    for (int i = 2; i < state.bot1_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.bot1_hand.hand_element(i),
                        310 + 55 * (i - 2), 420 + 55 * (i - 2), 45);
    }
    for (int i = 2; i < state.bot2_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.bot2_hand.hand_element(i),
                        1033 + 55 * (i - 2), 513 + 55 * (i - 2), 315);
    }
    for (int i = 2; i < state.dealer_hand.hand_size(); ++i) {
      renderer.drawCard(window, state.dealer_hand.hand_element(i),
                        645 + 55 * (i - 2), 130 + 55 * (i - 2), 0);
    }

    window.display();
  }
  if (state.your_hand.hand_score() <= 21 &&
      state.your_hand.hand_score() > state.dealer_hand.hand_score()) {
    std::cout << "you won" << std::endl;
  }
  if (state.your_hand.hand_score() <= 21 &&
      state.dealer_hand.hand_score() > 21) {
    std::cout << "dealer busted you won" << std::endl;
  }
  return 0;
}

#include "static_table.hpp"

namespace el {

void drawStaticTable(sf::RenderWindow& window, sf::Font& font,
                     float fishes_left, int score, const sf::Texture& texture1,
                     const sf::Texture& texture2, GameState& state,
                     CardRenderer& renderer, unsigned int currentTurn) {
  std::vector<sf::Text> allLetters;
  drawCircle(window, 715, 0, 715, sf::Color(0, 150, 80), 10.f,
             sf::Color(210, 180, 140));
  drawCircle(window, 715, 0, 320, sf::Color::Black, 5, sf::Color::White);

  drawRect(window, 660, 740, 120, 120, sf::Color(139, 0, 0), 3.f,
           sf::Color(212, 175, 55), 0);
  drawRect(window, 435, 741, 205, 120, sf::Color(210, 180, 140), 3.f,
           sf::Color(101, 67, 33), 0);
  drawRect(window, 645, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           0);
  drawRect(window, 725, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           0);
  drawRect(window, 645, 130, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           0);
  drawRect(window, 725, 130, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           0);

  drawRect(window, 310, 420, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           45);
  drawRect(window, 365, 475, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           45);
  drawRect(window, 1033, 513, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           315);
  drawRect(window, 1090, 460, 63, 88, sf::Color::White, 0.f, sf::Color::White,
           315);
  drawRect(window, 990, 415, 63, 88, sf::Color::Transparent, 1.f,
           sf::Color::Yellow, 315);
  drawRect(window, 410, 375, 63, 88, sf::Color::Transparent, 1.f,
           sf::Color::Yellow, 45);
  drawRect(window, 685, 500, 63, 88, sf::Color::Transparent, 1.f,
           sf::Color::Yellow, 0);

  drawRect(window, 190, 540, 130, 130, sf::Color(10, 17, 114), 3.f,
           sf::Color(212, 175, 55), 45);
  drawRect(window, 1250, 530, 130, 130, sf::Color(10, 17, 114), 3.f,
           sf::Color(212, 175, 55), 45);

  drawText(window, font, "PLAYER 1", 160, 590, 20, sf::Color::White, 45);
  drawText(window, font, "PLAYER 2", 1210, 640, 20, sf::Color::White, 315);
  drawText(window, font, "STAND", 990, 750, 25, sf::Color::White, 0);
  drawText(window, font, "HIT", 880, 750, 25, sf::Color::White, 0);
  drawText(window, font, "DOUBLE", 915, 815, 25, sf::Color::White, 0);
  drawText(window, font, "YOU", 675, 775, 40, sf::Color::White, 0);
  drawText(window, font, "Current Score:", 620, 400, 30, sf::Color::Black, 0);
  drawText(window, font, std::to_string(score), 680, 420, 50, sf::Color::Black,
           0);
  drawText(window, font, "FISH BALANCE:", 470, 750, 20, sf::Color::Black, 0);
  drawText(window, font, std::to_string(fishes_left), 440, 810, 30,
           sf::Color::Black, 0);
  auto curved1 = createCurvedText("BLACKJACK PAYS 3 TO 2", font, 15,
                                  {715.f, 15.f}, 260.f, 180.f, 180.f);
  auto curved2 =
      createCurvedText("DEALER MUST STAND ON 17, AND MUST DRAW TO 16", font, 15,
                       {715.f, 15.f}, 350.f, 180.f, 180.f);
  allLetters.insert(allLetters.end(), curved1.begin(), curved1.end());
  allLetters.insert(allLetters.end(), curved2.begin(), curved2.end());

  for (const auto& letter : allLetters) {
    window.draw(letter);
  }

  window.draw(getsprite(window, 638, 10, 0.8f, 0.6f, texture1));
  window.draw(getsprite(window, 830, 10, 0.08f, 0.1f, texture2));
  for (unsigned int i = 0; i < 2; i++) {
    renderer.drawCard(window, state.getPlayers()[1].getHand().handElement(i),
                      640.f + 90.f * static_cast<float>(i), 600, 0);
  }

  for (unsigned int i = 0; i < 2; i++) {
    renderer.drawCard(window, state.getPlayers()[0].getHand().handElement(i),
                      310.f + 55.f * static_cast<float>(i),
                      420.f + 55.f * static_cast<float>(i), 45);
  }
  for (unsigned int i = 0; i < 2; i++) {
    renderer.drawCard(window, state.getPlayers()[2].getHand().handElement(i),
                      1033.f + 57.f * static_cast<float>(i),
                      513.f - 53.f * static_cast<float>(i), 315);
  }
  for (unsigned int i = 0; i < 2; i++) {
    renderer.drawCard(window, state.getPlayers()[3].getHand().handElement(i),
                      645.f + 80.f * static_cast<float>(i), 130, 0);
    if (currentTurn != 3) {
      el::drawRect(window, 725, 130, 63, 88, sf::Color::Blue, 0.,
                   sf::Color::White, 0.);
    }
  }
}
void firstWindow(sf::RenderWindow& first_window, sf::Font& font) {
  std::vector<std::string> rules = {
      "Welcome to Blackjack!",
      "Get as close to 21 as possible without going over.",
      "Beat the dealer to win!",
      "",
      "How to play:",
      "- Each player starts with 2 cards.Face cards are worth 10, Aces can "
      "be 1 or 11, and all other cards are their number value.",
      "- Hit to take another card, Stand to keep your total.",
      "- Double Down: Feeling confident? Double your bet and get exactly one "
      "more card before standing.Use it wisely!",
      "- Dealer draws until reaching 17 or higher.",
      "- Bust if you go over 21.",
      "-This table admits a maximum budget of 1000000",
      "",
      "Tips:",
      "-Always watch the dealer's cards",
      "-Do not forget to smartly manage your fish, hit wisely, and aim for "
      "that perfect 21!",
      "Good luck, have fun, and may the cards be ever in your favor!"};

  std::vector<sf::Text> ruleTexts;
  float startY = 80.f;
  for (size_t i = 0; i < rules.size(); ++i) {
    drawText(first_window, font, rules[i], 50.f,
             startY + static_cast<float>(i) * 30.f, 25, sf::Color::Black, 0.);
  }
  drawText(first_window, font, "OK", 685, 758, 30, sf::Color::Black, 0.);
  drawText(first_window, font, "Enter fish amount:", 608, 580, 25,
           sf::Color::Black, 0.);
}
}  // namespace el
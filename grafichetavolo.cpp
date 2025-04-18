#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>

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
//POSIZIONI CERCHIO
std::vector<sf::Vector2f> createCircularPositions(
    sf::Vector2f center, float radius, float startAngleDeg,
    float totalAngleDeg, int count) {
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

int main() {
  sf::RenderWindow window(sf::VideoMode(1430, 1000), "BlackJack Simulator", sf::Style::Default);

  sf::Font font;
  if (!font.loadFromFile("arial.ttf")) return -1;

  std::vector<sf::Text> allLetters;

  // SCRITTE CURVE
  auto curved1 = createCurvedText("BLACKJACK PAYS 3 TO 2", font, 15, {715.f, 15.f}, 260.f, 180.f, 180.f);
  auto curved2 = createCurvedText("DEALER MUST STAND ON 17, AND MUST DRAW TO 16", font, 15, {715.f, 15.f}, 350.f, 180.f, 180.f);
  allLetters.insert(allLetters.end(), curved1.begin(), curved1.end());
  allLetters.insert(allLetters.end(), curved2.begin(), curved2.end());

  // POSIZIONI TONDINI ROSSI
  std::vector<sf::Vector2f> redCircleCoords = createCircularPositions(
      {715.f, 50.f}, 400.f, 180.f, 180.f, 10);  // centro, raggio, inizio, arco, count

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color(20, 20, 20));

    
    drawcircle(window, 715, 0, 715, sf::Color(0, 150, 80), 10.f, sf::Color(210, 180, 140));
    drawcircle(window, 715, 0, 320, sf::Color::Black, 5, sf::Color::White);

    drawRect(window, 660, 740, 120, 120, sf::Color(150, 150, 150), 2.f, sf::Color::White, 0); // YOU
    drawRect(window, 645, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0); 
    drawRect(window, 725, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0);
    drawRect(window, 725, 100, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0);
    drawRect(window, 645, 100, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0);
    drawRect(window, 310, 420, 63, 88, sf::Color::White, 0.f, sf::Color::White, 45);
    drawRect(window, 365, 475, 63, 88, sf::Color::White, 0.f, sf::Color::White, 45);
    drawRect(window, 1033, 513, 63, 88, sf::Color::White, 0.f, sf::Color::White, 315);
    drawRect(window, 1090, 460, 63, 88, sf::Color::White, 0.f, sf::Color::White, 315);
    drawRect(window, 850, 780, 100, 50, sf::Color(150, 150, 150), 2, sf::Color::White, 0);
    drawRect(window, 980, 780, 100, 50, sf::Color(150, 150, 150), 2, sf::Color::White, 0);
    drawRect(window, 190, 540, 130, 130, sf::Color(150, 150, 150), 2, sf::Color::White, 45);
    drawRect(window, 1250, 530, 130, 130, sf::Color(150, 150, 150), 2, sf::Color::White, 45);

    DrawText(window, font, "DEALER", 630, 20, 40, sf::Color::White, 0);
    DrawText(window, font, "PLAYER 1", 160, 590, 20, sf::Color::White, 45);
    DrawText(window, font, "PLAYER 2", 1210, 640, 20, sf::Color::White, 315);
    DrawText(window, font, "STAND", 990, 790, 25, sf::Color::White, 0);
    DrawText(window, font, "HIT", 880, 790, 25, sf::Color::White, 0);
    DrawText(window, font, "YOU", 675, 775, 40, sf::Color::White, 0);

    for (int i = 0; i < redCircleCoords.size(); i++) {
      drawcircle(window, redCircleCoords[i].x, redCircleCoords[i].y, 10, sf::Color(168, 0, 32), 2.f, sf::Color::White);
      DrawText(window, font, std::to_string(17 + i), redCircleCoords[i].x - 5, redCircleCoords[i].y-7, 10, sf::Color::White, 0);
    }

    for (const auto& letter : allLetters) window.draw(letter);

    window.display();
  }

  return 0;
}

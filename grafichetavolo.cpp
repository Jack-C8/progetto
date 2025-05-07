#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>

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

int main() {
  sf::RenderWindow window(sf::VideoMode(1430, 1000), "BlackJack Simulator",
                          sf::Style::Default);

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

  int your_score{0};

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

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        // if (button.getGlobalBounds().contains(mousePos)) {
        //   your_score += 10;
        // }
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
    DrawText(window, font, std::to_string(your_score), 800, 510, 50,
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


    window.display();
  }

  return 0;
}

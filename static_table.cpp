#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "basegraphics.hpp"
#include "CardRenderer.hpp"
// #include "Grafiche.hpp"
#include "card.hpp"
#include "hand.hpp"
#include "static_table.hpp"
void DrawStaticTable(sf::RenderWindow& window, sf::Font& font,
               float fishes_left, int score,
               const sf::Sprite& sprite, const sf::Sprite& sprite2,
               
               const std::vector<sf::Text>& allLetters
               ) 
{
    // Sfondo del tavolo
    drawCircle(window, 715, 0, 715, sf::Color(0, 150, 80), 10.f, sf::Color(210,180,140));
    drawCircle(window, 715, 0, 320, sf::Color::Black, 5, sf::Color::White);

    // Caselle giocatori e dealer
    drawRect(window, 660, 740, 120, 120, sf::Color(139,0,0), 3.f, sf::Color(212,175,55), 0); // YOU
    drawRect(window, 440, 741, 200, 120, sf::Color(210,180,140), 3.f, sf::Color(101,67,33), 0); // fish slot
    drawRect(window, 645, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0); // card 1 you
    drawRect(window, 725, 600, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0); // card 2 you
    drawRect(window, 645, 130, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0); // card 1 dealer
    drawRect(window, 725, 130, 63, 88, sf::Color::White, 0.f, sf::Color::White, 0); // card 2 dealer

    drawRect(window, 310, 420, 63, 88, sf::Color::White, 0.f, sf::Color::White, 45);  // carta 1 P1
    drawRect(window, 365, 475, 63, 88, sf::Color::White, 0.f, sf::Color::White, 45);  // carta 2 P1
    drawRect(window, 1033, 513, 63, 88, sf::Color::White, 0.f, sf::Color::White, 315); // carta 1 P2
    drawRect(window, 1090, 460, 63, 88, sf::Color::White, 0.f, sf::Color::White, 315); // carta 2 P2

    // Slot carte aggiuntive
    drawRect(window, 990, 415, 63, 88, sf::Color::Transparent, 1.f, sf::Color::Yellow, 315); 
    drawRect(window, 410, 375, 63, 88, sf::Color::Transparent, 1.f, sf::Color::Yellow, 45);  
    drawRect(window, 685, 500, 63, 88, sf::Color::Transparent, 1.f, sf::Color::Yellow, 0);   

    // Box giocatori
    drawRect(window, 190, 540, 130, 130, sf::Color(10,17,114), 3.f, sf::Color(212,175,55), 45); // P1 box
    drawRect(window, 1250, 530, 130, 130, sf::Color(10,17,114), 3.f, sf::Color(212,175,55), 45); // P2 box

    // Bottoni
    

    // Testi
    DrawText(window, font, "PLAYER 1", 160, 590, 20, sf::Color::White, 45);
    DrawText(window, font, "PLAYER 2", 1210, 640, 20, sf::Color::White, 315);
    DrawText(window, font, "STAND", 990, 750, 25, sf::Color::White, 0);
    DrawText(window, font, "HIT", 880, 750, 25, sf::Color::White, 0);
    DrawText(window, font, "DOUBLE", 980, 820, 25, sf::Color::White, 0);
    DrawText(window, font, "SPLIT", 867, 820, 25, sf::Color::White, 0);
    DrawText(window, font, "YOU", 675, 775, 40, sf::Color::White, 0);
    DrawText(window, font, "Current Score:", 765, 495, 15, sf::Color::Black, 0);
    DrawText(window, font, std::to_string(score), 800, 510, 50, sf::Color::Black, 0);
    DrawText(window, font, "FISH BALANCE", 470, 750, 20, sf::Color::Black, 0);
    DrawText(window, font, std::to_string(fishes_left), 470, 805, 30, sf::Color::Black, 0);

    // Cerchietti rossi numerati
   

    // Testi curvi e sprites
    for (const auto& letter : allLetters) window.draw(letter);
    window.draw(sprite);
    window.draw(sprite2);
  
}
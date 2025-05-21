#include <SFML/Graphics.hpp>
#include "card.hpp"
#include <map>
#pragma once

class CardRenderer {
 public:
  CardRenderer(const std::string& fontPath, const std::string& suitFolder);

  void drawCard(sf::RenderWindow& window, const el::Card& card, float x, float y, float a);

 private:
  sf::Font font;
  std::map<std::string, sf::Texture> suitTextures;

  sf::Texture generateCardTexture(const el::Card& card);
};
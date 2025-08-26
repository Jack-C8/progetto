#include <SFML/Graphics.hpp>
#include <map>

#include "card.hpp"
#pragma once

namespace el {

class CardRenderer {
 public:
  CardRenderer(const std::string& fontPath, const std::string& suitFolder);

  void drawCard(sf::RenderWindow& window, const el::Card& card, float x,
                float y, float a);

 private:
  sf::Font font;
  std::map<std::string, sf::Texture> suitTextures;

  sf::Texture generateCardTexture(const el::Card& card);
};
}
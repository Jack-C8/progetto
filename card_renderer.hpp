#ifndef EL_CARD_RENDERER_HPP
#define EL_CARD_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <stdexcept>

#include "card.hpp"

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
}  // namespace el

#endif
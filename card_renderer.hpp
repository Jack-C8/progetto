#ifndef EL_CARD_RENDERER_HPP
#define EL_CARD_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <stdexcept>

#include "card.hpp"

namespace el {

class CardRenderer {
  sf::Font font_;
  std::map<std::string, sf::Texture> suitTextures_;

  sf::Texture generateCardTexture(const el::Card& card);

 public:
  CardRenderer(const std::string& fontPath, const std::string& suitFolder);

  void drawCard(sf::RenderWindow& window, const el::Card& card, float x,
                float y, float a);
};
}  // namespace el

#endif
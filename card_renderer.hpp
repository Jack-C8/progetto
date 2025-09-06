#ifndef CARD_RENDERER_HPP
#define CARD_RENDERER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <stdexcept>

#include "base_graphics.hpp"
#include "card.hpp"
#include "methods.hpp"

namespace el {
class CardRenderer {
 public:
  CardRenderer(const std::string& fontPath, const std::string& suitFolder);

  void drawCard(sf::RenderWindow& window, const el::Card& card, float x,
                float y, float a);

 private:
  sf::Font font;
  std::map<std::string, sf::Texture> suitTextures;

  sf::Texture generateCardTexture(el::Card card);
};
void drawAdditionalCards(sf::RenderWindow& window, el::CardRenderer& renderer,
                         GameState& state);
void drawInitialCards(sf::RenderWindow& window, el::CardRenderer& renderer,
                      GameState& state);
}  // namespace el
#endif
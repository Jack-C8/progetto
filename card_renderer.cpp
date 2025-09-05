#include "card_renderer.hpp"

namespace el {
CardRenderer::CardRenderer(const std::string& fontPath,
                           const std::string& suitFolder) {
  if (!font_.loadFromFile(fontPath)) {
    std::cerr << "Errore: font non caricato!\n";
  }

  std::vector<std::string> suits = {"Hearts", "Spades", "Clubs", "Diamonds"};
  for (const auto& suit : suits) {
    sf::Texture tex;
    if (tex.loadFromFile(suitFolder + "/" + suit + ".png")) {
      suitTextures_[suit] = tex;
    } else {
      std::cerr << "Errore caricando il seme: " << suit << std::endl;
    }
  }
}

sf::Texture CardRenderer::generateCardTexture(const el::Card& card) {
  sf::RenderTexture renderTexture;
  renderTexture.create(63.f, 88.f);
  renderTexture.clear(sf::Color::White);

  sf::Text text;
  text.setFont(font_);
  text.setString(card.range_);
  text.setCharacterSize(20);
  text.setFillColor((card.suit_ == "Hearts" || card.suit_ == "Diamonds")
                        ? sf::Color::Red
                        : sf::Color::Black);
  text.setPosition(5.f, 5.f);
  renderTexture.draw(text);

  auto it = suitTextures_.find(card.suit_);
  if (it != suitTextures_.end()) {
    sf::Sprite suitSprite(it->second);
    suitSprite.setScale(0.8f, 0.8f);
    suitSprite.setPosition(30.f, 40.f);
    renderTexture.draw(suitSprite);
  }

  renderTexture.display();
  return renderTexture.getTexture();
}

void CardRenderer::drawCard(sf::RenderWindow& window, const el::Card& card,
                            float x, float y, float a) {
  sf::Texture texture = generateCardTexture(card);
  sf::Sprite sprite(texture);
  sprite.setPosition(x, y);
  sprite.rotate(a);
  window.draw(sprite);
}
}
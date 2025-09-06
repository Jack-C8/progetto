#include "card_renderer.hpp"

namespace el {
CardRenderer::CardRenderer(const std::string& fontPath,
                           const std::string& suitFolder) {
  if (!font.loadFromFile(fontPath)) {
    std::cerr << "Errore: font non caricato!\n";
  }

  std::vector<std::string> suits = {"Hearts", "Spades", "Clubs", "Diamonds"};
  for (const auto& suit : suits) {
    sf::Texture tex;
    if (tex.loadFromFile(suitFolder + "/" + suit + ".png")) {
      suitTextures[suit] = tex;
    } else {
      std::cerr << "Errore caricando il seme: " << suit << std::endl;
    }
  }
}

sf::Texture CardRenderer::generateCardTexture(el::Card card) {
  sf::RenderTexture renderTexture;
  renderTexture.create(63.f, 88.f);
  renderTexture.clear(sf::Color::White);

  sf::Text text;
  text.setFont(font);
  text.setString(card.getRange());
  text.setCharacterSize(20);
  text.setFillColor((card.getSuit() == "Hearts" || card.getSuit() == "Diamonds")
                        ? sf::Color::Red
                        : sf::Color::Black);
  text.setPosition(5.f, 5.f);
  renderTexture.draw(text);

  auto it = suitTextures.find(card.getSuit());
  if (it != suitTextures.end()) {
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
void drawAdditionalCards(sf::RenderWindow& window, el::CardRenderer& renderer,
                         GameState& state) {
  for (int i = 2; i < state.getYourHand().handSize(); ++i) {
    renderer.drawCard(
        window, state.getYourHand().handElement(static_cast<std::size_t>(i)),
        685.f + 75.f * static_cast<float>(i - 2), 500.f, 0);
  }
  for (int i = 2; i < state.getBot1Hand().handSize(); ++i) {
    renderer.drawCard(
        window, state.getBot1Hand().handElement(static_cast<std::size_t>(i)),
        410.f + 55.f * static_cast<float>(i - 2),
        320.f + 55.f * static_cast<float>(i - 1), 45);
  }
  for (int i = 2; i < state.getBot2Hand().handSize(); ++i) {
    renderer.drawCard(
        window, state.getBot2Hand().handElement(static_cast<std::size_t>(i)),
        990.f + 55.f * static_cast<float>(i - 2),
        415.f - 55.f * static_cast<float>(i - 2), 315);
  }
  for (int i = 2; i < state.getDealerHand().handSize(); ++i) {
    renderer.drawCard(
        window, state.getDealerHand().handElement(static_cast<std::size_t>(i)),
        685.f, 240.f + 55.f * static_cast<float>(i - 2), 0);
  }
}
void drawInitialCards(sf::RenderWindow& window, el::CardRenderer& renderer,
                      el::GameState& state) {
  for (int i = 0; i <= 1; ++i) {
    renderer.drawCard(
        window, state.getYourHand().handElement(static_cast<std::size_t>(i)),
        640.f + 90.f * static_cast<float>(i), 600, 0);
  }
  for (int i = 0; i <= 1; ++i) {
    renderer.drawCard(window,
                      state.getBot1Hand().handElement(static_cast<size_t>(i)),
                      310.f + 55.f * static_cast<float>(i),
                      420.f + 55.f * static_cast<float>(i), 45);
  }
  for (int i = 0; i <= 1; ++i) {
    renderer.drawCard(window,
                      state.getBot2Hand().handElement(static_cast<size_t>(i)),
                      1033.f + 57.f * static_cast<float>(i),
                      513.f - 53.f * static_cast<float>(i), 315);
  }
  for (int i = 0; i <= 1; ++i) {
    renderer.drawCard(window,
                      state.getDealerHand().handElement(static_cast<size_t>(i)),
                      645.f + 80.f * static_cast<float>(i), 130, 0);
    if (!state.dealer_card_shown) {
      el::drawRect(window, 725, 130, 63, 88, sf::Color::Blue, 0.,
                   sf::Color::Black, 0.);
    }
  }
}

}  // namespace el
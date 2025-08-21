/*classe per i metodi da utilizzare come funzioni non libere all'interno del
main così che tutto abbia un'origine precisa, pensavo di mettere qui i comandi
di split e  i turni dei bot

ragionamenti su tasto split, si può cliccare solo quando si hanno 2 carte
uguali, una volta aggiunta una terza carta non è possibile giocare il tasto
split

aggiungo dei throw temporanei sempre in split*/

#include "card.hpp"
#include "hand.hpp"
namespace el {
class methods {
 public:
  Card split(Hand hand) {
    if (hand.hand_size() != 2) {
      throw std::runtime_error{"Split is not available in this situation"};
    }
    if (!(hand.hand_element(0) == hand.hand_element(1))) {
      throw std::runtime_error{"Split "}
    }
  }
}
};
}  // namespace el
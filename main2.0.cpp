#include "base_graphics.hpp"
#include "buttons.hpp"
#include "card.hpp"
#include "card_renderer.hpp"
#include "game_state.hpp"
#include "hand.hpp"
#include "player.hpp"
#include "static_table.hpp"

int main() {
  // Clock
  // Font
  // Button
  // Error_time
  // Error_message
  // CardRenderer
  unsigned int humanFishes;
  unsigned int humanBet;  // definite una volta fatto input

  // Prima finestra con istruzioni e fish iniziali e definizione di humanFishes

  // Overlay per bet di gioco con bettingMode e definizione di humanBet

  // PROBLEMA! Non posso inizializzare state senza bet, ma betting Mode parte
  // solo se current_turn esiste;

  // Dichiarazione di state, prima o dopo overlay;

  // state.current_turn = 0; e così parte il game vero e proprio

  // DrawStatic e DrawButton (Tavolo e Bottoni);

  // Disegno delle carte accedendo ai personaggi.
  // state.players_[i].hand_.hand_element(1) e (2)
  // NB finché current_turn !=3 la seconda carta del dealer è coperta!

  // state.nextTurn() turno del bot1 con current_turn che passa da 0 a 1

  // turno umano gestito dai bottoni (if current_turn == 1)!
  // i bottoni chiamano la funzione
  // state.players_[current_turn].hit(state.deck_)

  // state.advanceTurn() con current_turn che avanza a due.

  // state.nextTurn() cioè bot2 current da 2 a 3.

  // state.nextTurn() cioè dealer current da 3 a 4.
  // qui viene scoperta la carta del dealer.

  // payOut con current_turn = 4 che ritorna le fish rimaste.

  // advanceTurn e current == 5 (viene attivato round_over) e bettingMode;

  // startGame(ritorno di payOut, nuova bet da bettingMode.)

  // PROBLEMI: ogni volta le bet dei bot tornano a 1000 perché non ci salviamo
  // se vincono o perdono siccome si tratta di un ciclone while direi di mettere
  // bettingMode in 5 e startGame in 6 se no rischiamo che il gioco riparta di
  // continuo.
}
#include <iostream>
#include "card.cpp"
#include "hand.cpp" // questi o gli header? -J
                    // vogliamo mettere dei timer che mettono tipo 1/2 sec tra le pescate e tra le azioni dei bot? -J

void turno_bot_prudente(el::Deck deck)
{
    hd::Hand mano;
    mano.Draw(deck);
    // stampa carta sul tavolo
    mano.Draw(deck);
    // stampa carta sul tavolo
    if (mano.player_score() <= 14)
    {                                   // 14 perchè appena più di metà delle carte
        mano.Draw(deck);                // mi fanno stare dentro i 21
        // stampa carta sul tavolo
    }
}

void turno_bot_audace(el::Deck deck)
{
    hd::Hand mano;
    mano.Draw(deck);
    // stampa carta sul tavolo
    mano.Draw(deck);
    // stampa carta sul tavolo
    if (mano.player_score() <= 17)
    {                                // 17 perchè appena meno di un terzo delle carte
        mano.Draw(deck);            // mi fanno stare dentro i 21
     // stampa carta sul tavolo
    }
}

int main()
{
    std::cout << "Quanti soldi vuole convertire in fish?\n";
    int soldi_player;
    std::cin >> soldi_player;
    int soldi_bot_prudente{100};
    int soldi_bot_audace{100};
    el::Deck deck;
    // stampa schermata iniziale
    // stampa schermata di gioco

    while (/*giocatore clicca pulsante esci*/ || soldi_player == 0) // turno completo di gioco
    {
        hd::Hand mano; // mano player
        hd::Hand dealer_hand;
        dealer_hand.Draw(deck);
         // stampa carta sul tavolo
        dealer_hand.covered_Draw(deck);
        // stampa carta
         turno_bot_prudente(deck);

        mano.Draw(deck); // turno del player
        // stampa carta sul tavolo
        mano.Draw(deck);
        // stampa carta sul tavolo
        if (/*giocatore clicca su double*/) {
            // raddoppia la posta
        }
        while (/* giocatore non ha cliccato su "stand" */ || mano.player_score() >= 21)
        {
            if (/*giocatore clicca hit*/)
            {
                mano.Draw(deck);
                // stampa carta sul tavolo
            }
        }

        turno_bot_audace(deck);
       
       // turno dealer da implementare

    }
}
#include <iostream>
// #include <algorithm>

#include "card.hpp"
#include "hand.hpp"
// vogliamo mettere dei timer che mettono tipo 1/2 sec tra le pescate e tra le azioni dei bot? -J

void bot_turn(el::Deck deck, hd::Hand hand, int n)
{
    if (hand.score() <= n)
    {                    // bot 1: n=14 perchè appena più di metà delle carte
        hand.Draw(deck); // mi fanno stare dentro i 21
        // stampa carta sul tavolo     bot 2: n=17 perchè appena meno di un terzo delle carte
    } // mi fanno stare dentro i 21
}

void bet_result(int money, int bet, hd::Hand hand, hd::Hand dealer_hand)
{
    if (dealer_hand.score() > hand.score() || hand.score() > 21)
    {
        money -= bet;
    }
    if (dealer_hand.score() < hand.score())
    {
        money += bet;
    }
}

int main()
{
    std::cout << "Quanti soldi vuole convertire in fish?\n";
    int player_money;
    std::cin >> player_money;
    int bot1_money{100};
    int bot2_money{100};
    el::Deck deck;

    // stampa schermata iniziale
    // stampa schermata di gioco

    while (/*giocatore non clicca pulsante esci*/ || soldi_player == 0) // turno completo di gioco
    {

        int player_bet = ; // il giocatore deve sceglierlo dalla schermata
        int bot1_bet{10};
        int bot2_bet{10};

        hd::Hand player_hand;
        hd::Hand dealer_hand;
        hd::Hand bot1_hand;
        hd::Hand bot2_hand;

        bot1_hand.Draw(deck);
        player_hand.Draw(deck);
        bot2_hand.Draw(deck);
        dealer_hand.Draw(deck);

        bot1_hand.Draw(deck);
        player_hand.Draw(deck);
        bot2_hand.Draw(deck);
        dealer_hand.covered_Draw(deck);
        // stampa carte sul tavolo man mano che vengono pescate

        bot_turn(deck, bot1_hand, 15);
        // turno giocatore
        if (/*giocatore clicca su double*/)
        {
            // raddoppia la posta
        }
        while (/* giocatore non ha cliccato su "stand" */ || player_hand.score() >= 21)
        {
            if (/*giocatore clicca hit*/)
            {
                player_hand.Draw(deck);
                // stampa carta sul tavolo
            }
        }

        bot_turn(deck, bot2_hand, 17);
                                             // turno dealer
        dealer_hand.reveal();
        std::vector<el::Card> dealer_vector = dealer_hand.hand();
        const auto iter = std::find_if(dealer_vector.begin(), dealer_vector.end(), [](el::Card c)
                                       { return c.range_ == "A" && c.game_value_ == 11; });
        if (dealer_hand.score() <= 16 || (dealer_hand.score() == 17 && iter != dealer_vector.end()))
        {                           // la seconda condizione è per il "soft 17":
            dealer_hand.Draw(deck); // se il dealer ha 17 ma ha almeno un asso che sta valendo 11
            // stampa carta         //   deve pescare di nuovo (altrimenti pesca solo se ha meno di 17)
        }
        bet_result(bot1_money, bot1_bet, bot1_hand, dealer_hand);
        bet_result(player_money, player_bet, player_hand, dealer_hand);
        bet_result(bot2_money, bot2_bet, bot2_hand, dealer_hand);
    }
}
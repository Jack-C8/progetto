#include "doctest.h"
#include "card.cpp"

TEST_CASE("Deck shuffle")
{
    el::Deck deck1;
    el::Deck deck2;

    SUBCASE("Two shuffled decks")
    {
        deck1.shuffle();
        deck2.shuffle();
        // mescolo i mazzi e con sto ciclo che almeno in una posizione le carte sono
        // diverse il che vuol dire che i mazzi sono stati mischiati.
        // iteratore arriva fino a 52 perché se trova un mazzo in ordine è già un
        // problema.
        bool different = false;
        for (size_t i{0}; i < 52; ++i)
        {
            if (!(deck1.get_deck()[i] == deck2.get_deck()[i]))
            {
                different = true;
                break;
            }
        }
        CHECK(different == true);
    }

    SUBCASE("One shuffled deck & one unshuffled deck")
    {
        deck2.shuffle();
        bool different = false;
        for (size_t i{0}; i < 14; ++i)
        {
            if (!(deck1.get_deck()[i] == deck2.get_deck()[i]))
            {
                different = true;
                break;
            }
        }
        CHECK(different == true);
    }

    SUBCASE("Number of cards after shuffle")
    {
        deck1.shuffle();
        CHECK(deck1.deck_size() == 156);
    }
}

TEST_CASE("Deck draw")
{
    el::Deck deck;

    SUBCASE("Draw the last constructed card")
    {
        el::Card card{"Diamonds", "A", 11};
        CHECK(deck.topCard() == card);
        CHECK(deck.deck_size() == 155);
    }

    SUBCASE("Draw several cards from unshuffled deck") // sfrutto il fatto che il costruttore
    {                                                  // costruisce il mazzo con un ordine iniziale che conosco
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard(); // pesco le prime 4 carte e vedo se sono al punto giusto
        CHECK(deck.deck_size() == 152);
        el::Card card1{"Diamonds", "10", 10};
        CHECK(deck.topCard() == card1);
        CHECK(deck.deck_size() == 151);
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard();
        deck.topCard(); // pesco le prime 20 carte
        CHECK(deck.deck_size() == 136);
        el::Card card2{"Spades", "7", 7};
        CHECK(deck.topCard() == card2);
        CHECK(deck.deck_size() == 135);
    }
}

TEST_CASE("Card operator==")
{
    el::Card c1{"Hearts", "2", 2};
    el::Card c2{"Hearts", "3", 3};
    el::Card c3{"Clubs", "2", 2};
    el::Card c4{"Hearts", "2", 3};
    el::Card c5{"Spades", "4", 4};
    CHECK((c1 == c1) == true);
    CHECK((c1 == c2) == false);
    CHECK((c1 == c3) == false);
    CHECK((c1 == c4) == true); // operator== non deve tener conto del game_value della carta
    CHECK((c1 == c5) == false);
}
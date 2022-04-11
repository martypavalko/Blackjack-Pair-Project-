#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>
using namespace std;

struct Card {
  string value;
  string suit;
};

string printCard(Card c) { return (c.value + c.suit); }

struct Deck {
  int currentCard = 0;
  Card card[52];
};

Deck create_deck() {
  const int NUMCARDS = 52;
  const int CARDSIZE = 2;
  Deck deck;
  char suits[] = {'C', 'D', 'H', 'S'};
  char cardValues[] = {'A', 'K', 'Q', 'J', 'T', '9', '8',
                       '7', '6', '5', '4', '3', '2'};

  int count = 0;
  Card current;
  // for each suit
  for (int n = 0; n < 4; n++) {
    // for each of the unique card calues
    for (int m = 0; m < 13; m++) {
      current.suit = suits[n];
      current.value = cardValues[m];
      deck.card[count] = current;
      count++;
    }
  }
  if (count == 52) {
    cout << "deck size OK..." << endl;
  } else {
    cout << "deck size: " << count << ", ERROR...exiting." << endl;
    exit(-1);
  }
  return deck;
}

struct Hand {
  string owner;
  int numCards = 0;
  // max possible hand is A,A,A,A,2,2,2,2,3,3,3
  Card card[12];
};

Hand createHand(string owner) {
  Hand h;
  h.owner = owner;
  return h;
}

void printHand(Hand h) {
  string s;
  cout << "\n" << h.owner << "'s hand:";
  for (int i = 0; i < h.numCards; i++) {
    s += (" " + printCard(h.card[i]));
  }
  cout << s << endl;
}

void printDHand(Hand h) {
  string s;
  cout << "\n" << h.owner << "'s hand: ?? ";
  for (int i = 1; i < h.numCards; i++) {
    s += (" " + printCard(h.card[i]));
  }
  cout << s << endl;
}
// DONE: create a version of the above to print the dealer's hand, with the
// first (face-down) card obscured by ?? This is easier than it may first
// appear.  Examine the function carefully.

Hand addCard(Hand h, Card c) {
  // h.numCards is the last element in the Hand's Card array.
  // Don't attempt to add past element 11 (0-11 is 12 items).
  if (h.numCards < 11) {
    h.card[h.numCards] = c;
    // the hand is one larger.
    h.numCards++;
    // cout << "DEBUG: " << h.owner << "'s hand size: " << h.numCards << endl;
  }
  return h;
}

Hand dealCard(Hand h, Deck d) {
  int i = d.currentCard;
  // cout << h.owner << "'s hand pre-deal: ";
  // printHand(h);
  // cout << "DEBUG: About to deal: " << d.card[i].value << d.card[i].suit <<
  // endl;
  h = addCard(h, d.card[d.currentCard]);

  // cout << "DEBUG: Current hand:";
  // printHand(h);
  // cout << "DEBUG: Next deck card: " << d.card[i+1].value << d.card[i+1].suit
  // << endl;
  return h;
}

// DONE: replace the cards suits in the deck with the symbols
// METHOD 1 - use a function that swaps out the value of the card suit.
Card suitReplace(Card c) {
  if (c.suit == "S") {
    c.suit = "♠";
  } else if (c.suit == "H") {
    c.suit = "♥";
  } else if (c.suit == "C") {
    c.suit = "♣";
  } else if (c.suit == "D") {
    c.suit = "♦";
  } else {
    cout << "ERROR: invalid suit value in card: " << c.value << c.suit << endl;
  }
  return c;
}

// DONE: Evaluate the hand, including Aces being worth 11 or 1 (if necessary)
// You will have to modify this code to get variable aces to work.
int eval(Hand h) {
  int score = 0;

  map<string, int> cardMap = {
      {"A", 11}, {"K", 10}, {"Q", 10}, {"J", 10}, {"T", 10}, {"9", 9}, {"8", 8},
      {"7", 7},  {"6", 6},  {"5", 5},  {"4", 4},  {"3", 3},  {"2", 2}};

  // DEBUG: Print the cardVal map -- comment this out in your program
  // cout << "\nThe map is:\n";
  // cout << "KEY\tVALUE\n";
  // for (const auto& [key, value] : cardMap){
  // 	cout << key << ":\t" << value << " points\n";
  // }

  // for each card in the hand, add the score:
  for (int n = 0; n < h.numCards; n++) {
    // cout << "DEBUG: Looking for " << h.card[n].value << endl;
    auto search = cardMap.find(h.card[n].value);
    if (search != cardMap.end()) {
      // cout << "Found key: " << search->first << ", value: " << search->second
      // << '\n';
      score += static_cast<int>(search->second);
    } else {
      cout << "ERROR: key not found\n";
    }
  }
  if (score > 21) {
    int aceCount = 0;
    for (int i = 0; i < h.numCards; i++) {
      if (h.card[i].value == "A") {
        aceCount++;
      }
    }
    if (aceCount > 4) {
      cout << "Error, too many aces." << endl;
      return -1;
    }
    // cout << "Debug Aces: " << aceCount << "\n\n";
    for (int n = 0; n < aceCount; n++) {
      score = score - 10;
    }
  }

  // cout << "Total hand score is: " << score << endl;
  return score;
}

void printDeck(Deck d) {
  for (int i = 0; i < 52; i++) {
    cout << d.card[i].value << d.card[i].suit;
    if (i != 51) {
      cout << ',';
    }
  }
  cout << endl;
  return;
}

Deck shuffle(Deck d, int NUMCARDS) {
  int seed = time(0);
  srand(seed);
  Card placeholder;
  int current = 0;
  while (current < NUMCARDS) {
    placeholder = d.card[current];
    int target = (rand() % 52);
    d.card[current] = d.card[target];
    d.card[target] = placeholder;
    current++;
  }
  return d;
}
// === MAIN === 
int main(){
	const int NUMCARDS =52;
	const int CARDSIZE = 2;
	int playernum;
	cout << "How many players? [1,2,3]" << endl;
	cin >> playernum;

  int player1Wins = 0;
  int player2Wins = 0;
  int player3Wins = 0;
  int dealerWins = 0;
  int gamesPlayed = 0;
  int player1Pushes = 0;
  int player2Pushes = 0;
  int player3Pushes = 0;
  
	while(true){
    bool player1Blj = false;
    bool player2Blj = false;
    bool player3Blj = false;
		Deck deck;
		// There are zero cards when you declare a new Hand.
		// Hand dealerHand, player1Hand;
		Hand dealerHand = createHand("Dealer");
		Hand player1Hand = createHand("Player 1");
		Hand player2Hand = createHand("Player 2");
		Hand player3Hand = createHand("Player 3");
		// player2Hand, player3Hand;

		deck = create_deck();
		// printDeck(deck);
		// Replace the card letters with symbols
		// Method 1: via function

		for(int i=0; i<52; i++){
			deck.card[i] = suitReplace(deck.card[i]);
			// cout << deck.card[i].value << deck.card[i].suit << endl;
		}
		cout << endl;

		printDeck(deck); // DEBUG: deck validation.
    deck = shuffle(deck, NUMCARDS);

    // ==== DEAL HANDS ====
    
    // If there is only 1 player and the dealer
    if (playernum == 1) {
  		player1Hand = dealCard(player1Hand, deck);
  		deck.currentCard++;

      dealerHand = dealCard(dealerHand, deck);
      deck.currentCard++;

      player1Hand = dealCard(player1Hand, deck);
  		deck.currentCard++;

      // Check for blackjack
      if (eval(player1Hand) == 21) {
        cout << "BLACKJACK!";
      }
      else {
        dealerHand = dealCard(dealerHand, deck);
        deck.currentCard++;
      }
    }
    // If there are only 2 players and the dealer
    else if (playernum == 2)
    {
      player1Hand = dealCard(player1Hand, deck);
      deck.currentCard++;
      
      player2Hand = dealCard(player2Hand, deck);
		  deck.currentCard++;

      dealerHand = dealCard(dealerHand, deck);
      deck.currentCard++;

      player1Hand = dealCard(player1Hand, deck);
  		deck.currentCard++;

      // Check for Player 1 Blackjack
      if (eval(player1Hand) == 21) {
        cout << "BLACKJACK!";
      }
      else {
        player2Hand = dealCard(player2Hand, deck);
        deck.currentCard++;

        // Check for Player 2 Blackjack
        if (eval(player2Hand) == 21) {
          cout << "BLACKJACK!";
        }
        else {
          dealerHand = dealCard(dealerHand, deck);
          deck.currentCard++;
        }
      }
    }
    // If there are 3 players and the dealer
    else if (playernum == 3)
    {
      player1Hand = dealCard(player1Hand, deck);
      deck.currentCard++;
      
      player2Hand = dealCard(player2Hand, deck);
		  deck.currentCard++;
      
      player3Hand = dealCard(player3Hand, deck);
		  deck.currentCard++;

      dealerHand = dealCard(dealerHand, deck);
      deck.currentCard++;

      player1Hand = dealCard(player1Hand, deck);
      deck.currentCard++;

      // Check for Player 1 Blackjack
      if (eval(player1Hand) == 21) {
        cout << "BLACKJACK!";
      }
      else {
        player2Hand = dealCard(player2Hand, deck);
        deck.currentCard++;

        // Check for Player 2 Blackjack
        if (eval(player2Hand) == 21) {
          cout << "BLACKJACK";
        }
        else {
          player3Hand = dealCard(player3Hand, deck);
          deck.currentCard++;

          if (eval(player3Hand) == 21) {
            cout << "BLACKJACK!";
          }
          else {
            dealerHand = dealCard(dealerHand, deck);
            deck.currentCard++;
          }
        }
      }
    }

    printHand(player1Hand);
    cout << "Player 1 score: " << eval(player1Hand) << endl << endl;
    
    if(playernum>1){
      printHand(player2Hand);
      cout << "Player 2 score: " << eval(player2Hand) << endl << endl;
      if(eval(player2Hand)==21)
      {
        printHand(player2Hand);
        cout << "BLACKJACK!" << endl;
        if(eval(dealerHand)<21){
        player2Wins++;
        }
      }
      else{
        cout << "PUSH" << endl;
      }
      if(playernum>2){
        printHand(player3Hand);
        cout << "Player 3 score: " << eval(player3Hand) << endl << endl;
        if(eval(player1Hand)==21)
        {
          printHand(player1Hand);
          cout << "BLACKJACK!" << endl;
          if(eval(dealerHand)<21){
            player3Wins++;
          }
          else{
            cout << "PUSH" << endl;
          }
        }
      } 
    }
    printDHand(dealerHand);
    if(eval(player1Hand)==21)
    {
      printHand(dealerHand);
      cout << "BLACKJACK!";
      if()
    }
    cout << endl;

    while(eval(player1Hand)<21){
      char decision;
      printHand(player1Hand);
      cout << "Player 1 score: " << eval(player1Hand) << endl;
      cout << "Will you hit?(y/n)" << endl;
      cin >> decision;
      if(decision == 'y' or decision == 'Y'){
        player1Hand = dealCard(player1Hand, deck);
        deck.currentCard++;
        
      }
      else{
        printHand(player1Hand);
        cout << "Player 1 score: " << eval(player1Hand) << endl << endl;
        break;}
    }


    if(eval(player1Hand)>21)
    {
      printHand(player1Hand);
      cout << "BUST!";
    }
    else
    {
      printHand(player1Hand);
      cout << "Player 1 score: " << eval(player1Hand) << endl;
    }

    if(playernum>1){
      while(eval(player2Hand)<21 or eval(player1Hand)!=21){
        char decision;
        printHand(player2Hand);
        cout << "Player 2 score: " << eval(player2Hand) << endl << endl;
        cout << "Will you hit?(y/n)" << endl;
        cin >> decision;
        if(decision == 'y' or decision == 'Y'){
          player2Hand = dealCard(player2Hand, deck);
          deck.currentCard++;
          
        }
        else{
          printHand(player2Hand);
          cout << "Player 2 score: " << eval(player2Hand) << endl;
          break;}
      }
      printHand(player2Hand);
      cout << "Player 3 score: " << eval(player2Hand) << endl << endl;
      
      if(playernum>2){
        while(eval(player3Hand)<21){
          char decision;
          printHand(player3Hand);
          cout << "Player 3 score: " << eval(player3Hand) << endl;
          cout << "Will you hit?(y/n)" << endl;
          cin >> decision;
          if(decision == 'y' or decision == 'Y'){
            player3Hand = dealCard(player3Hand, deck);
            deck.currentCard++;
            
          }
          else{
            printHand(player3Hand);
            cout << "Player 3 score: " << eval(player3Hand) << endl << endl;
            break;}
        }
        printHand(player1Hand);
        cout << "Player 3 score: " << eval(player3Hand) << endl;
      }
    }
    while(eval(dealerHand)<17){
      if(playernum>2){
        while(eval(dealerHand)<eval(player1Hand) or eval(dealerHand)<eval(player2Hand) or eval(dealerHand)<eval(player3Hand)){
        dealerHand = dealCard(dealerHand, deck);
        }
      }
      if(playernum>1){
        while(eval(dealerHand)<eval(player1Hand) or eval(dealerHand)<eval(player2Hand)){
        dealerHand = dealCard(dealerHand, deck);
        }
      }
      else{
        while(eval(dealerHand)<eval(player1Hand)){
        dealerHand = dealCard(dealerHand, deck);
        }
      }
    }

    printHand(dealerHand);
    cout << "Dealer's score: " << eval(dealerHand) << endl << endl;

		// TODO: print out hand of all players

		// print out the dealer's hand, hiding the hole card:

		// subsequent printing will require a function in the case that the dealer hits (on a hand < 16).		

		//cout << "DEBUG In main(): " << player1Hand.owner << "'s hand value: " << eval(player1Hand) << endl;
		//cout << "DEBUG In main(): " << dealerHand.owner << "'s hand value: " << eval(dealerHand) << endl;

    if(((eval(dealerHand)>eval(player1Hand)) or (eval(dealerHand)>eval(player2Hand)) or (eval(dealerHand)>eval(player3Hand))) and (eval(dealerHand)<21))
    {
      dealerWins++;
    }
    
    if((eval(player1Hand)>eval(dealerHand)) or (eval(dealerHand)>21 and eval(player1Hand)<22))
    {
      cout << "Player 1 Wins";
      player1Wins++;
    }
    
    if((eval(player2Hand)>eval(dealerHand) or (eval(dealerHand)>21 and eval(player2Hand)<22)) and playernum>1)
    {
      cout << "Player 2 Wins";
      player2Wins++;
    }

    if((eval(player3Hand)>eval(dealerHand) or (eval(dealerHand)>21 and eval(player3Hand)<22)) and playernum>2)
    {
      cout << "Player 3 Wins";
      player3Wins++;
    }

    cout << "Player 1 Wins: " << player1Wins << endl;
    cout << "Player 2 Wins: " << player2Wins << endl;
    cout << "Player 3 Wins: " << player3Wins << endl;
    cout << "Dealer Wins: " << dealerWins << endl;

		char replay;
		cout << "\n\nPlay again?(y/n)";
		cin >> replay;
		if(replay == 'n' or replay == 'N'){break;}
	}

  cout << "Player 1 Wins: " << player1Wins << endl;
  cout << "Player 2 Wins: " << player2Wins << endl;
  cout << "Player 3 Wins: " << player3Wins << endl;
  cout << "Dealer Wins: " << dealerWins << endl;

	// TODO:(Kenneth) Check for a Blackjack condition.  The game ends if any player (or the dealer) was dealt Blackjack.
	// If the Dealer has Blackjack and a Player doesn't, the game is over and every Player loses. 
	// It's a PUSH (tie) if the Player has one as well, nobody "wins"
	// DONE(Naif): Prompt each player to Hit or Stand and deal out cards *appropriately*
	// -- if they have 21, don't let them hit.
	// DONE(Naif): The turn ends for each player if they bust (score > 21), and have no Aces (that they can elect to be a 1).
	// DONE:(Naif) The dealer takes the last turn, and has an opportunity to hit repeatedly (on a hand <= 16, but must stand on a 17 or above).
	// TODO(Kenneth): Keep track of Player and Dealer wins, losses and ties
	// DONE: Put the entire game in a play again (game state loop) -- each hand is one round of a larger game. 
	return 0;
}

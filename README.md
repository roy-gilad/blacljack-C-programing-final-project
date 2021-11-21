# blacljack-C-programing-final-project
terminal-based game of black jack between a human player and a computer controlled dealer. 


Embedded C Final Project

Black-Jack Game (v1.2.0)

Make a terminal-based game of black jack between a human player and a computer
controlled dealer.

Game parts definitions
The game will use playing cards. Or simply a “Card” struct. Each card has four fields: suit,
rank & next.
suit: A suit can have one of the following values: Spades, Hearts, Clubs and Diamonds.
(You can use global constant char arrays)
rank: A rank can have one of the following values: Ace,2,3,4,5,6,7,8,9,10,Jack,Queen,
King (You can use global constant char arrays)
The fields suit and rank should be stored together in a uint8_t, where the first 2 bits [1:0]
are used to represent the suit, the next 4 bits [5:2] are used to represent the rank ([7:6]
unused)
next: The game will utilize linked lists of Card structs. Using a Card pointer called “next” to
link the cards together.
value: The value of a card is not a field but is instead calculated from the rank:
Ranks 2-9 have “face values” (rank 2’s value is 2, rank 3’s value is 3 etc) The values of
the ranks Jack, Queen & King are always 10. The value of an Ace is 1. (An additional
10 might be added to a hand containing an Ace as will be explained later)
Game Flow and Phases
The game will start from phase 1 listed below, and when each part is done the game will
move to the next phase. (However, some phases may move to a previous phase)
1. Game Initialization: Create a card linked list called “deck”. It will represent a deck of 52
standard playing cards, containing one of every combination of rank and suit.
Start with two empty card linked lists called “dealer_hand” and “player_hand”
Start with a “cash” integer equals to 1000, and “bet” equals 0.
2. Betting phase:
print the player’s cash, and bet.
Ask the player how much they’re willing to add to the bet (can’t be more than cash
available). Deduct that much from cash and add to the bet. Bets must be made in multiples
of 10. The player can choose to add 0 to the bet only if the bet is already greater than 0.
3. Initial Deal phase
draw 2 cards into the dealer hand, and 2 cards into the player hand. (see “notes on
drawing cards” below).
Note on drawing random cards: to “draw” a card from the deck to a hand, select a
random position in the deck list, remove the card in that position and insert it as the last
position of the hand.
Selecting a random number: call srand(time(NULL)) to initialize the random number
generator. Do this only once at the beginning of the program.
Whenever you need a random number, call rand() to produce a pseudo random number. if
you want a random position between 0 and 51 you can use modulus:
rand() % 52
(both srand and rand are part of the stdlib.h library)
(phase 3 continued)
Show what cards each player has, except that the second card of the dealer will be hidden
(show ?????? instead).
For example:
If the dealer drew King of Hearts and 5 of Spades, and the Player drew 7 of Diamonds and
Ace of Clubs, show this on the screen:
dealer: King of Hearts, ????????
player: 7 of Diamonds, Ace of Clubs
4. Black Jack
Calculate the hand value of the player (see explanation below).
If it’s 21: - print “Black Jack!” - add one and a half the bet to the cash and reduce the bet
back to 0. - move to the Reset Cards phase.
If it’s not 21, move to phase 4.
Calculating hand value: Sum the value of each card in the list representing that hand.
The value of Jack, Queen and King is 10. Calculate the Value of Aces as 1.
if the hand contains at least one Ace add 10 to the value. However , if the value is more
than 21 after adding 10, subtract it back by 10.
4. Hit or Stand Phase
b) input the user for either “hit” or “stand”. If the user chooses “stand” move to the next
phase (dealer draw phase).
c) If the user chooses “hit”, draw a card into the player’s hand. Then, calculate the value of
the player’s hand. If it’s above 21, the player loses the bet, print “bust” and move to the
“lose bet” phase. If the value is below 21, repeat phase 4.
5. Dealer draw phase
Calculate the value of the hand of the dealer. If it’s greater than the player’s hand value,
that player loses. Print “you lose” and move to the “lose bet phase”.
Otherwise, keep drawing cards until one of the following occurs:
- the dealer’s hand value is greater than the player’s hand value. - the dealer’s hand value
has reached a value of 17 or more.
If the dealer’s hand value is above 21, print “dealer bust”. Add the bet twice to the cash
and reset the bet to 0. move to the Reset Cards phase.
If the dealer’s hand is 21 or below and the dealer’s hand value is the same as the player’s,
print “tie”, move to the Reset Cards phase. (The bet doesn’t reset to 0).
If the dealer’s hand value is 21 or below and it is greater than the player’s hand, print
“dealer wins”, set the bet to 0. move the Reset Cards phase.
6. Reset Cards.
Add all the cards in the player’s and dealer’s hand to the top of the deck. (player and
dealer hand should now be empty. The deck should contain all the cards, order doesn’t
matter).
If the player's cash is less than 10, the game is over, print “out of cash to bet. Game Over.”
and end the program.
Otherwise, ask the player if they wish to bet again (yes/no). If they do, go back to phase 2.
Otherwise, end the program.
Before the program ends, free all dynamically allocated memory.

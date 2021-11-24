/*
    project: blackjack 1.2 V
    course: C programing 08/2021
    submit: roy gilad
    id: 203523527
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include<stdint.h> 
#include<time.h>

#define SUIT_NUM 4
#define RANK_NUM 13

// GLOBAL
char const SUIT[SUIT_NUM][10]={"Spades","Hearts","Clubs","Diamonds"};
char const RANK[RANK_NUM][10]={"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};

//TYPE
typedef struct Card Card;
struct Card {
     uint8_t suit :2 ,
             rank :4 ;
     Card *next;
};

//FUNC DECLARATION
void init_card_list (Card ** head_deck,int suit_data,int rank_data);//create 52 card link list- deck.
void add_card(Card ** head_deck,Card ** dealer_player,int position);// add card to dealer or player from the deck from specific position
int check_bet(int * bet,int * cash);//check if the bet input is correct
int get_cards_value(Card **card_list);//calculate hands card for given link list
void free_list(Card **p_card_list);//free link list from memory
void print_hand(Card **p_card_list);//print given link list
void clean_hands(Card ** head_deck,Card **player_list,Card **dealer_list);//remove player and dealer cards  list yo deck list

//MAIN
int main()
{
    int i,j,position,cash=1000,bet=0,deck_count=52,game_over=0,phase=1,hit_stand,keep_bet=1,add_bet,dealer_sum,player_sum;
    Card *head_deck=NULL;
    Card *node=NULL;
    Card *player_hand=NULL;
    Card *dealer_hand=NULL;
    time_t t;

   //Intializes random number generator 
   srand((unsigned) time(&t));
    //create 52 card list.
    for(i=0;i<SUIT_NUM;i++) // i=0,1,2,3
    {
        for(j=1;j<=RANK_NUM;j++) //j= 1,2,3...13
        {
            init_card_list (&head_deck,i,j);
        }
    }
    
    
    printf("~~~~~~~Wellcome to bleacjack game~~~~~~~~~\n");
    while (!game_over && keep_bet) // while loop if game not over (out of cash) and the player wnt to keep bet 
    {

    switch (phase)
    {    
        case 1:  // phase 1- betting phashe:
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("your cash is: %d \nyour bet is: %d\n\n",cash,bet);
            printf("how much you want to add the bet? ");
            scanf("%d",&add_bet);
            bet+=add_bet;
            while(check_bet(&add_bet,&cash)) //if the bet not correct it loop over again
            {
                printf("how much you want to bet? ");
                scanf("%d",&add_bet);
            }
            printf("your cash is: %d \nyour bet is: %d\n\n",cash,bet);

            // Initial hands
            deck_count=52;
            for (i=0;i<2;i++) // give to card to player and dealer
            {
                position= rand() % deck_count+1; //rand number in change number. in begin range 1...52, after one card out  1..51 
                add_card(&head_deck,&player_hand,position); // add card to the player hand
                deck_count--;// decrease the card range for the rand func
                position= rand() % deck_count+1;
                add_card(&head_deck,&dealer_hand,position);// add card to the dealer hand
                deck_count--;
            }

            //print dealer hand  
            node=dealer_hand;
            printf("dealer: ");
            while (node->next != NULL)
            {
                printf("%s of  %s ,",RANK[node->rank-1],SUIT[node->suit]);
                node=node->next;
            }
            printf(" ?????????");//  dealer hide card

            printf("\n\n");
            
            //print player hand  
            printf("player: ");
            print_hand(&player_hand);// print hand function
            printf("\n\n");


            // blackjack- player hand is 21
            if (get_cards_value(&player_hand)==21)
            {
                printf("Black Jack!\n you get %d!",bet+bet/2);
                cash+=bet+bet/2;
                bet=0;
                clean_hands(&head_deck,&player_hand,&dealer_hand); // remove dealer and player hand to deck link list 
                printf("do you want bet again? write '1' for yes or '0' for no \n");
                scanf("%d",&keep_bet);//if user insert '0' the code stop the while loop.
                phase=1; //betting phase,
                break;
            }            
        case 2: // phase 2- hit or stand 
            printf("Hit or Stand? for hit insert '1' stand insert '0'\n");
            scanf("%d",&hit_stand);
            if (hit_stand==1) //hit
            {
                position= rand() % deck_count+1; //rand number in change number. in begin range 1...52, after one card out  1..51 
                add_card(&head_deck,&player_hand,position); // add card to the player hand
                deck_count--;// decrease the card range for the rand func
                printf("your hand: ");
                print_hand(&player_hand);  
                if (get_cards_value(&player_hand)>21)  // the player bust, cards over 21 
                {
                    printf("you bust\n\n");
                    bet=0;
                    clean_hands(&head_deck,&player_hand,&dealer_hand);
                    if (cash<10) 
                    {
                        printf("out of cash. game over\n");
                        game_over=1;
                        break;
                    }
                    else
                    {
                        printf("do you want bet again? write '1' for yes or '0' for no \n");
                        scanf("%d",&keep_bet);
                        phase=1; //betting phase,if user insert '0' the code stop the while loop.
                        break;
                    }
                }
                else
                {
                    phase= 2 ; // go to hit or stand phase again
                    break;
                }
    
            }
            if (hit_stand==0) //stand
            {
                //dealer draw phase
                dealer_sum=get_cards_value(&dealer_hand);
                player_sum=get_cards_value(&player_hand);
                
                if(dealer_sum>21 )
                {
                    printf("dealer bust\n");
                    phase=4; //win phase
                    break;
                }
                if (dealer_sum>player_sum)
                {
                    printf("dealer win\n");
                    phase=3; //loos phase
                    break;
                }

                while (dealer_sum<17)// dealer draw card until he get 17 or more
                {
                    position= rand() % deck_count+1; 
                    add_card(&head_deck,&dealer_hand,position); // add card to the dealer hand
                    deck_count--;
                    dealer_sum=get_cards_value(&dealer_hand);
                }

                if(dealer_sum>21 ||  dealer_sum<player_sum)
                {
                    printf("dealer bust\n");
                    phase=4; //win phase
                    break;
                }
                if (dealer_sum>player_sum)
                {
                    printf("dealer win\n");
                    phase=3; //loos phase
                    break;
                }
                
                else
                {
                    phase=5;// tie phase
                    break;
                }

            }
            else
            {
                printf("wrong input");
                phase=2; //repet this phase
                break;
            }         
        case 3: //phase 3-lose bet phase
            //print hands  
            printf("player: ");
            print_hand(&player_hand);
            printf("\n");
            printf("dealer: ");
            print_hand(&dealer_hand);
            printf("\n");

            printf("you bust.\n");
            bet=0;
            clean_hands(&head_deck,&player_hand,&dealer_hand);
            if (cash<10) 
            {
                printf("out of cash. game over\n");
                game_over=1;
                break;
            }
            else
            {
                printf("do you want bet again? write '1' for yes or '0' for no \n");
                scanf("%d",&keep_bet);
                phase=1; //betting phase,if user insert '0' the code stop the while loop.
                break;

            }
        case 4: //phase 4-win bet 
            //print hands  
            printf("player: ");
            print_hand(&player_hand);
            printf("\n");
            printf("dealer: ");
            print_hand(&dealer_hand);
            printf("\n");

            printf("you win\n");
            cash+=bet*2;
            bet=0;
            clean_hands(&head_deck,&player_hand,&dealer_hand);
            if (cash<10) 
            {
                printf("out of cash. game over\n");
                game_over=1;
                break;
            }
            else
            {
                printf("do you want bet again? write '1' for yes or '0' for no \n");
                scanf("%d",&keep_bet);
                phase=1; //betting phase,if user insert '0' the code stop the while loop.
                break;

            }

        case 5: // tie bet phase
            //print hands  
            printf("player: ");
            print_hand(&player_hand);
            printf("\n");
            printf("dealer: ");
            print_hand(&dealer_hand);
            printf("\n");

            printf("tie... no one win\n");
            clean_hands(&head_deck,&player_hand,&dealer_hand);

            phase =1;
            break;
    } //end of switch
    
    } //end of while -game over

    printf("bye bye you have %d $, stay safe...",cash);
    free_list(&head_deck);//free memory
    return 0;
}
//FUNCTION
void init_card_list (Card ** head_deck,int suit_data,int rank_data)
{   

    Card *newNode = NULL;
    newNode=malloc(sizeof(Card));

    // insert data to new node
    newNode->suit=suit_data;
    newNode->rank=rank_data;     
    newNode->next= NULL;

    //if list empty
    if(*head_deck == NULL)
         *head_deck = newNode;
    
    //else find the last node and add the newNode
    else
    {
        Card *lastNode = *head_deck;
        
        //last node's next address will be NULL.
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        //add the newNode at the end of the linked list
        lastNode->next = newNode;
    }
    
} 
void add_card(Card ** head_deck,Card ** dealer_player,int position)
{
    int count=1;
    Card *temp_deck,*prev,*temp_dp;
    
    temp_deck=*head_deck;
    temp_dp=*dealer_player;
    prev=*head_deck;

    // find card position
    if(position==1) *head_deck=temp_deck->next;
    else
    {
        while (temp_deck!=NULL && count!=position)
        {
            prev=temp_deck;
            temp_deck=temp_deck->next;
            count++;
        }
        //remove from the deck by skip to next card
        prev->next=temp_deck->next;
    }
    //in case player or dealer hand empty
    if (temp_dp == NULL) 
    {
       *dealer_player=temp_deck;
        temp_deck->next=NULL;
    }

    //in case player / dealer hand not empty add a card in the end of the list
    else
    {
        //find the last card in player / dealer hand
        while (temp_dp->next!=NULL)
        {
            temp_dp=temp_dp->next;
        }
        temp_dp->next=temp_deck;
        temp_deck->next=NULL;
    }
}
void free_list(Card **p_card_list)
{
    Card *node=*p_card_list;
    Card *prev_node=node;

    while(node != NULL)
    {
        prev_node=node;
        node=node->next;
        free(prev_node);
    }
}

int get_cards_value(Card **card_list)
{
    int sum=0;
    int count_ace=0;
    Card *node=*card_list;
    while(node!=NULL)
    {   
        if (node->rank==1)
        {
            sum+=1;
            count_ace++;
        }
        
        else if (node->rank>10 && node->rank<14)
        {
            sum+=10;
        }
        else
            sum+=(int)node->rank;
        node=node->next; 
    }
    //in case ace in hand
    while ((count_ace>0 ) && (sum<21))
    {
        
        sum+=10;
        if (sum>21)
        {
            sum=sum-10;
            count_ace--; 
        }
        else
        {
            count_ace--;
        }
    }
   return sum;
}

int check_bet(int * bet,int * cash)
{

    if (*bet%10)
    {
        printf("Bet must be made in multiples of 10\n");
        return 1; 
    }

    if (*bet>*cash)
    {
         printf("bet can’t be more than cash available\n"); 
         return 1;
    }
    else
    {
        *cash=*cash-*bet;
        return 0;
    }
}

void print_hand(Card **p_card_list)
{
    Card *node=*p_card_list;
    
    if  (node==NULL) return; //list empty

    while (node->next != NULL)
    {
        printf("%s of  %s ,",RANK[node->rank-1],SUIT[node->suit]);
        node=node->next;
    }
    printf("%s of  %s\n",RANK[node->rank-1],SUIT[node->suit]);  
}

void clean_hands(Card ** head_deck,Card **player_list,Card **dealer_list)
{
    Card *temp_deck;
    temp_deck=*head_deck;

    //clean player list
    while (temp_deck->next != NULL) temp_deck=temp_deck->next; //find the last node
    temp_deck->next=*player_list;
    *player_list=NULL;

    //clean dealer list
    while (temp_deck->next != NULL) temp_deck=temp_deck->next; //find the last node
    temp_deck->next=*dealer_list;
    *dealer_list=NULL;

}
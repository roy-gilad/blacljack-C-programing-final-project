#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include<stdint.h> 

#define SUIT_NUM 4
#define RANK_NUM 13

/*  TODO
    1. The player can choose to add 0 to the bet only if the bet is already greater than 0

*/


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
void init_card_list (Card ** head_deck,int suit_data,int rank_data);
void add_card(Card ** head_deck,Card ** dealer_player,int position);
int check_bet(int * bet,int * cash);
int get_cards_value(Card **card_list);
void free_list(Card **p_card_list);
void print_hand(Card **p_card_list);

//MAIN
int main()
{
    int i,j,position,cash=1000,bet,deck_count=52;
    Card *head_deck=NULL;
    Card *node=NULL;
    Card *player_hand=NULL;
    Card *dealer_hand=NULL;
    time_t t;

   //Intializes random number generator 
   srand((unsigned) time(&t));
    //create 52 card list.
    for(i=0;i<SUIT_NUM;i++) // 0,1,2,3
    {
        for(j=1;j<=RANK_NUM;j++) //1,2,3...13
        {
            init_card_list (&head_deck,i,j);
        }
    }
    // betting phashe:
    
    printf("~~~~~~~Wellcome to bleacjack game~~~~~~~~~\n");
    printf(" you have : %d $\n ",cash);
    printf("how much you want to bet? ");
    scanf("%d",&bet);
    while(check_bet(&bet,&cash)) //if the bet not correct it loop over again
    {
        printf("how much you want to bet? ");
        scanf("%d",&bet);
    }
    printf("your cash is: %d \nyour bet is: %d\n\n",cash,bet);

    // Initial Deal - phase 3

    for (i=0;i<2;i++) // give to card to player and dealer
    {
        position= rand() % deck_count+1; //rand number in change number. in begin range 1...52, after one card out  1..51 
        add_card(&head_deck,&player_hand,position); // add card to the player hand
        deck_count--;
        position= rand() % deck_count+1;
        add_card(&head_deck,&dealer_hand,position);// add card to the dealer hand
        deck_count--;
    }

    //print hands - phase 3  

    //print dealer hand  
    node=dealer_hand;
    printf("dealer: ");
    while (node->next != NULL)
    {
        printf("%s of  %s ,",RANK[node->rank-1],SUIT[node->suit]);
        node=node->next;
    }
    printf(" ?????????");

    printf("\n\n");
    
    //print player hand  
    printf("player: ");
    print_hand(&player_hand);
    printf("\n\n");

    // blackjack case
    if (get_cards_value(&player_hand)==21)
    {
        printf("Black Jack!\n you get %d!",bet+bet/2);
        cash+=bet+bet/2;
        bet=0;
        printf("cash now is: %d",cash);
    }
   
   // printf("sum is: %d",get_cards_value(&player_hand));
    



   // print deck
   // node=head_deck;
   
    // while (node != NULL)
    // {
    //     printf("%s of  %s \n",RANK[node->rank-1],SUIT[node->suit]);
    //     node=node->next;
    // }

    //free memory 
  //  free_list(&head_deck);
  //  free_list(&player_hand);


    
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
        sum+=9;
        sum>21 ? sum=sum-9 : count_ace--;
        
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
         return 1111;
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
    while (node->next != NULL)
    {
        printf("%s of  %s ,",RANK[node->rank-1],SUIT[node->suit]);
        node=node->next;
    }
    

    printf("%s of  %s",RANK[node->rank-1],SUIT[node->suit]);
    
    
}

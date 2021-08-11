#include <stdio.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int ,int );
void disclaimer();
void aboutthegame();
void playgame();
void drawboard(char *);
int procedure(char *, int player, char*, char *, char *);
int wincheck(char *);
int fourmatch(char *, int, int, int, int);
int horizontalmatch(char *);
int verticalmatch(char *);
int diagonalmatch(char *);


int main()
{
    int choice;

    gotoxy(32,0);
    printf("!!!!!WELCOME!!!!!\n\n");
    gotoxy(27,2);
    printf("***The Seven Amigo Presents***\n");
    gotoxy(19,3);
    printf("***A Most Interesting & Addicting 2 Player Game***\n");
    gotoxy(31,4);
    printf("!!!***RATTIC***!!!\n\n");
    gotoxy(32,6);
    printf("***DISCLAIMER***\n\n");
    disclaimer();
    printf("\n\nPress Enter To Go Main Menu\n\n");
    getch();

    while(1)
    {
        system("cls");
        printf("***MAIN MENU*** \n 1.Play \n 2.How To Play ? \n 3.About The Game\n 4.Quit?\n Enter Your Choice \t ");
        scanf("%d",&choice);


        switch(choice)
        {
            case 1: printf("\n\n");
                    playgame();
                    printf("*****!!!Press Enter To Return To Main Menu!!!*****");
                    getch();
                    break;

            case 2: printf("\n\n");
                    printf("Rules And Instructions Are Given Below :-\n\n• Two players are required for playing the game.\n• A dashboard of 6 row and 7 column is provided to you, it means there are total of 42 spaces in which you can place your symbol one by one.\n• Each player get 21 turns at the max.\n• You have to select your symbol as per your choice [between X  and O].\n• The player  with the symbol (X) will  get the first chance and vice versa.\n• Before starting, players decide randomly which of them will be the beginner; moves are made alternatively, one by turn.\n• Enter the column number to place your symbol in dashboard.\n• Symbol automatically placed in the last row of selected column.\n• First of all last row will be filled then the row preceding it and proceeds in same manner.\n• Player who first matches their four Symbol (X) or (O) in a straight line either horizontally ,vertically or diagonally will win the match.\n• If all 42 spaces are filled with the symbol (X) or (O) and there is no any straight line matching with any respective symbol then the match will tie.\n");
                    printf("\n\nPress Enter To Go Main Menu\n\n");
                    getch();
                    break;

            case 3: printf("\n\n");
                    aboutthegame();
                    printf("\n\nPress Enter To Go Main Menu\n\n");
                    getch();
                    break;

            case 4: return 0;

           default: printf("\n\n");
                    printf("Invalid Choice Please Try Again Later \n \n");
                    printf("\n\nPress Enter To Go Main Menu\n\n");
                    getch();

        }
    }
}

void playgame()
{
            char player1[30],player2[30];
            int i,turn,done=0;
            char board[42];
            char symbol[2] = {'X','O'} ;

            printf("Enter The First Player Name Who Wants To Play With 'X'\t");
            scanf("%s",&player1);
            printf("Enter The Second Player Name Who Wants To Play With 'O'\t");
            scanf("%s",&player2);

            for(i=0;i<42;i++)
                board[i]='\0';

            for(turn=0;turn<42 && !done;turn++)
            {
                drawboard(board);
                while(!procedure(board, turn % 2, symbol, player1, player2))
                {
                    drawboard(board);
                    printf("***Column full! Try Another Column !!***\n");
                }
                done=wincheck(board);
            }
            drawboard(board);
            if(turn==42 && !done)
            {
               printf("***Oops!! It's A TIE!!!***\n");
            }
            else
            {
                if (turn%2==1)
                printf(" !!!!! CONGRATULATIONS %s(X) \n YOU WIN!!!!! \n \n ", player1);
                else
                printf(" !!!!! CONGRATULATIONS %s(O) \n YOU WIN!!!!! \n \n ", player2);
            }
            printf("!!!!!!! Game Ends !!!!!!!\n");
            getch();
}

void drawboard(char *board)
{
    int row,col;
    printf("  1   2   3   4   5   6   7\n\n");
    for(row=0;row<6;row++)
    {
        for(col=0;col<7;col++)
        {
            printf("| %c ",board[7*row+col]);
        }
        printf("| \n");
        printf("-----------------------------\n");
    }
}

int procedure(char *board, int player, char *symbol, char *player1, char *player2)
{
    int row, col = 0;

    if(player==0)
    printf("NOW %s (X) TURN :\nPlease Choose The Column: ", player1);
    else
    printf("NOW %s (0) TURN :\nPlease Choose The Column: ", player2);

    while(1)
    {
        scanf("%d",&col);
        if(col < 1 || col > 7)
        {
          while(getchar() != '\n');
          printf("Invalid Selection, Please Try Again !!!!");
        }
        else
        {
            break;
        }
    }

    col--;
    for(row=5; row >= 0; row--)
    {
        if(board[7 * row + col] == '\0')
        {
            board[7 * row + col] = symbol[player];
            return 1;
        }
    }
    return 0;
}

int wincheck(char *board)
{
    return ( horizontalmatch(board) || verticalmatch(board) || diagonalmatch(board));
}

int fourmatch(char *board, int a, int b, int c, int d)
{
    return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != '\0');
}

int horizontalmatch(char *board)
{
    int row,col,i,w=1;
    for(row=0;row<6;row++)
    {
        for(col=0;col<4;col++)
        {
            i=7*row+col;
            if(fourmatch(board,i,i+w,i+w*2,i+w*3))
                return 1;
        }
    }
    return 0;
}

int verticalmatch(char *board)
{
    int row, col,i,h=7;
    for(row = 0; row < 3; row++)
    {
       for(col = 0; col < 7; col++)
       {
          i = 7 * row + col;
          if(fourmatch(board, i, i + h, i + h * 2, i + h * 3))
              return 1;
       }
    }
    return 0;
}

int diagonalmatch(char *board)
{
    int row,col,i,count=0,r=6,l=8;
    for(row = 0; row < 3; row++)
    {
      for(col = 0; col < 7; col++)
      {
         i = 7 * row + col;
         if(count <= 3 && fourmatch(board, i, i + l, i + l * 2, i + l * 3) || count >= 3 && fourmatch(board, i, i + r, i + r * 2, i + r * 3))
         {
            return 1;
         }
         count++;
      }
      count = 0;
   }
   return 0;

}

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void aboutthegame()
{
    printf("If your looking for a simple strategy game that can be played with just about anyone, including young children, RATTIC is for you.\n");
    printf("RATTIC is a combination of word (RaT) and (Tactics) meaning technique usually used in multiplayer games.\n");
    printf("It is an abstract strategy board game.\n");
    printf("The idea of this game has been taken from a Japanese game (Gomoku).\n");
    printf("It is FREE!\n");
    printf("Put your strategy skills to the test and see if you have what it takes to outsmart your opponents.\n");
    printf("The game objective is to place your symbol in the grid and be the first to get 4 symbol in a line either horizontally, vertically, or diagonally to win.\n");
    printf("It’s simple, fast, and fun.\n Master the grid!\n");
    printf("This game helps children improve hand & eye coordination & strategic thinking skills.\n");
    printf("The game is fun and approachable, which makes it accessible for people of all ages.\n");
    printf("If you have never played RATTIC, then you are in for a treat.\n");
    printf("You will have a blast playing this game with your friends.\n");
    printf("Want a fun way to pass the time?\n");
    printf("Try your hand at RATTIC game that tests your skills in strategy, creativity, and luck!\n\n\n");
    printf("**** RATTIC Features ****\n\n6X7 game grid.\nBeautiful and simple user interface.\nFast Paced Gameplay.\nThis game is made with the help of “C program”.\n\n\n");
    printf("*****About The Developer*****\n\n     ***GAME CREDITS***\n  !!!!!The Seven Amigo!!!!!\n\n");
    printf("S.No.  Roll No.   Name             Reg.No.\n");
    printf("1.     18-CS-01   SHIVANSH SAGAR   18105111016\n");
    printf("2.     18-CS-04   JEMINI KUMAR     18105111019\n");
    printf("3.     18-CS-18   SHUBHAM KUMAR    18105111021\n");
    printf("4.     18-CS-52   PRAGATI          18105111034\n");
    printf("5.     18-CS-57   POOJA PRIYA      18105111033\n");
    printf("6.     18-CS-58   ANJALI           18105111031\n");
    printf("7.     18-CS-65   AKSHAY VERMA     18105111040\n\n");
    printf("From 2018 Batch C.S.E Branch Of Darbhanga College Of Engineering, Darbhanga,Bihar.\n");
}

void disclaimer()
{
    printf("RATTIC is a game made only for playing and educational purpose.\n");
    printf("The materials available on or through this game is created by THE SEVEN AMIGO.\n");
    printf("To the maximum extent permitted by the law , we make no statement, representation, or warranty about the quality, accuracy, context, completeness, availability or suitability for any purpose.\n");
    printf("Despite our best efforts , we make no warranties that the materials available on this game are free from infection by computer viruses.\n");
    printf("We disclaim all responsibility and liability for all expenses, losses, damages and our contents are intended to be used or must be used for learning purpose.\n");
    printf("The makers of this game are not responsible for mental stress caused to the loosing team.\n");
    printf("This game cannot be copyrighted until the owners consent.T&C's Applied.\n");
    printf("The last decision will be taken by owner and you have no any rights to use edit and maltreat with the source codes without any legal permission.\n");
    printf("For more details regarding terms of use contact owner.\n");
}

#include "stdio.h"
#define B_SIZE 3
#define COLOR_BOLD "\e[1m"
#define COLOR_OFF "\e[m"

// function that prints the board in a human friendly way
// the mode is 1 if you want block numbers to show
void printBoard(char board[B_SIZE][B_SIZE], int mode)
{
    int blockCount = 1;
    // loop over all board characters
    for (int i = 0; i < B_SIZE; i++)
    {
        for (int j = 0; j < B_SIZE; j++)
        {
            if (board[i][j] == ' ' && mode == 1)
            {
                // if empty print the
                printf("%d", blockCount);
            }
            else
            {
                // print each character
                if (mode == 1)
                {
                    printf(COLOR_BOLD "%c" COLOR_OFF, board[i][j]);
                }
                else
                {
                    printf("%c", board[i][j]);
                }
            }
            // if not the final character in row
            // print a vertical line after it
            if (j < B_SIZE - 1)
            {
                printf("|");
            }
            blockCount++;
        }
        // print a new line after each row
        printf("\n");
        // if not the final row print a horizontal
        // line after it
        if (i < B_SIZE - 1)
        {
            printf("-+-+-\n");
        }
    }
    printf("\n");
}

// function that checks whether the board is in a win situation
// if yes it returns the wining character (X or O)
// if no it returns an empty space
char checkWin(char board[B_SIZE][B_SIZE])
{
    // check horizontal
    for (int i = 0; i < B_SIZE; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    // check vertical
    for (int i = 0; i < B_SIZE; i++)
    {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    // check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][0];
    }

    return ' ';
}

int main()
{
    // initialize empty board
    char board[B_SIZE][B_SIZE] = {{' ', ' ', ' '},
                                  {' ', ' ', ' '},
                                  {' ', ' ', ' '}};

    // get player characters
    char playerOne;
    char playerTwo;
    int i = 0;
    while (playerOne != 'X' && playerOne != 'O' && playerOne != 'x' && playerOne != 'o')
    {
        // clear scanner input
        if (i != 0)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
        printf("please enter player 1 character (X or O): ");
        scanf("%c", &playerOne);
        i++;
    }
    switch (playerOne)
    {
    case 'x':
        playerTwo = 'o';
        break;
    case 'X':
        playerTwo = 'O';
        break;
    case 'o':
        playerTwo = 'x';
        break;
    case 'O':
        playerTwo = 'X';
    }

    int currentPlayer = 1;
    char currentPlayerChar = playerOne;

    // game loop (ends in 9 turns)
    for (int i = 0; i < B_SIZE * B_SIZE; i++)
    {
        printf("\nPlayer %d turn \n\n", currentPlayer);
        // show game state
        printf("Game State: \n");
        printBoard(board, 0);

        // have player choose a valid block
        int currentBlock = 0;
        while (!(currentBlock >= 1 && currentBlock <= 9))
        {
            printf("Available Blocks: \n");
            printBoard(board, 1);
            printf("player %d, please enter one of the available block numbers: ", currentPlayer);
            scanf("%d", &currentBlock);
        }

        // fill choosen block with player char
        int i = (currentBlock - 1) / 3;
        int j = (currentBlock - 1) % 3;
        board[i][j] = currentPlayerChar;

        // check win
        char wins = checkWin(board);
        if (wins != ' ')
        {
            printBoard(board, 0);
            printf("%c wins the game!\n", wins);
            return 0;
        }

        // change player for next turn
        if (currentPlayer == 1)
        {
            currentPlayer = 2;
            currentPlayerChar = playerTwo;
        }
        else
        {
            currentPlayer = 1;
            currentPlayerChar = playerOne;
        }
    }
    printf("The Game is a Draw!\n");
    return 0;
}
#include <stdio.h>
#include <stdbool.h>

/* ######### CONFIG ######### */

#define IS_TO_PRINT_BOARD 1
#define NUMBER_MAX_DISCS 20

/* ########################## */

#define NUMBER_PINS 3
#define FIRST_PIN 0
#define MIDDLE_PIN 1
#define LAST_PIN 2
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT (-1)


typedef struct game_state
{
    int pins[NUMBER_MAX_DISCS][NUMBER_PINS];
    int positionDiscInPin[NUMBER_PINS];
    int numberDiscs;
} GameState;

void
initGame(GameState *board)
{
    int i;

    for (i = 0; i < board->numberDiscs; i++)
    {
        board->pins[i][0] = board->numberDiscs - i;
        board->pins[i][1] = 0;
        board->pins[i][2] = 0;
    }

    board->positionDiscInPin[0] = board->numberDiscs - 1;
    board->positionDiscInPin[1] = -1;
    board->positionDiscInPin[2] = -1;
}

int
getFirstDiscInPin(GameState *board, int pin)
{
    return board->pins[board->positionDiscInPin[pin]][pin];
}

bool
isValidMoviment(GameState *board, int from, int dest)
{
    bool rc = true;

    if(getFirstDiscInPin(board, from) > getFirstDiscInPin(board, dest))
    {
        rc = false;
    }

    return rc;
}

void
printBoard(GameState *board)
{
#if IS_TO_PRINT_BOARD == 1
    int i;
    int j;

    for (i = 0; i < board->numberDiscs; i++)
    {
        for (j = 0; j < NUMBER_PINS; j++)
        {
            printf("%d ", board->pins[board->numberDiscs - i - 1][j]);
        }
        printf("\n");
    }
    printf("\n");
#else /*#if IS_TO_PRINT_BOARD == 1 */
    UNUSED_PARAMETER(board);
#endif /*#else IS_TO_PRINT_BOARD == 1 */
}

bool
move(GameState *board, int from, int dest)
{
    bool rc = false;
    if((rc = isValidMoviment(board, from, dest)))
    {
        board->pins[board->positionDiscInPin[dest] + 1][dest] = getFirstDiscInPin(board, from);
        board->pins[board->positionDiscInPin[from]][from] = 0;
        board->positionDiscInPin[from]--;
        board->positionDiscInPin[dest]++;
    }
}

void
solveGame(GameState *board)
{
    move(board, 0, 2);
}

int
main()
{
    GameState board;

    printf("discs: ");
    scanf("%d", &(board.numberDiscs));

    initGame(&board);
    printf("---- Start ----\n");
    solveGame(&board);
    printf("---- Finish ----\n");
    printBoard(&board);

    return 0;
}

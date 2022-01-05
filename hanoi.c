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

#define UNUSED_PARAMETER(x) (void)x

#define INVERT_DIRECTION(x) x *= (-1)

typedef struct game_state
{
    int pins[NUMBER_MAX_DISCS][NUMBER_PINS];
    int positionDiscInPin[NUMBER_PINS];
    unsigned int numberDiscs;
} GameState;

void
initGame(GameState *board)
{
    unsigned int i;

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
isValidMoviment(GameState *board, unsigned int from, unsigned int dest)
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

void
solveGame(GameState *board)
{

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

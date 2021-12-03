#include <stdio.h>
#include <stdbool.h>

#define NUMBER_DISCS 2
#define NUMBER_PINS 3

typedef struct game_state
{
    unsigned int pins[NUMBER_DISCS][NUMBER_PINS];
    int positionDiscInPin[NUMBER_PINS];
} GameState;

void
initGame(GameState *board)
{
    int i;

    for (i = 0; i < NUMBER_DISCS; i++)
    {
        board->pins[i][0] = NUMBER_DISCS - i;
        board->pins[i][1] = 0;
        board->pins[i][2] = 0;
    }

    board->positionDiscInPin[0] = NUMBER_DISCS - 1;
    board->positionDiscInPin[1] = -1;
    board->positionDiscInPin[2] = -1;
}

void
printBoard(GameState *board)
{
    int i;
    int j;

    for (i = 0; i < NUMBER_DISCS; i++)
    {
        for (j = 0; j < NUMBER_PINS; j++)
        {
            printf("%d ", board->pins[NUMBER_DISCS - i - 1][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void
solveGame(GameState *board, int lastMoviment[2])
{
    static int direction = 1;
    int currentMoviment[2];

    currentMoviment[0] = lastMoviment[0];
    currentMoviment[1] = lastMoviment[1];
    if (false == (board->pins[0][0] == 0 &&
                  (board->pins[0][1] == 0 || board->pins[0][2] == 0)))
    {
        if (direction > 0)
        {
            if (lastMoviment[0] == NUMBER_PINS - 2)
            {
                direction = -1;
                currentMoviment[0] = NUMBER_PINS - 1;
                currentMoviment[1] = NUMBER_PINS - 2;
            }
            else if ((lastMoviment[1] == NUMBER_PINS - 1 && direction == 1) ||
                     (lastMoviment[1] == 0 && direction == 0))
            {
                currentMoviment[0] += direction;
                currentMoviment[1] = currentMoviment[0] + direction;
            }
            else
            {
                currentMoviment[1] += direction;
            }
        }

        if (board->positionDiscInPin[currentMoviment[0]] >= 0)
        {
            if ((board->pins[board->positionDiscInPin[currentMoviment[0]]]
                            [currentMoviment[0]] <
                 board->pins[board->positionDiscInPin[currentMoviment[1]]]
                            [currentMoviment[1]]) ||
                (board->pins[board->positionDiscInPin[currentMoviment[1]]]
                            [currentMoviment[1]] == 0))
            {
                printBoard(board);
                board->positionDiscInPin[currentMoviment[1]]++;
                board->pins[board->positionDiscInPin[currentMoviment[1]]]
                           [currentMoviment[1]] =
                    board->pins[board->positionDiscInPin[currentMoviment[0]]]
                               [currentMoviment[0]];
                board->pins[board->positionDiscInPin[currentMoviment[0]]]
                           [currentMoviment[0]] = 0;
                board->positionDiscInPin[currentMoviment[0]]--;
                printf("%d->%d\n", currentMoviment[0], currentMoviment[1]);
                currentMoviment[0] = 0;
                currentMoviment[1] = 0;
                solveGame(board, currentMoviment);
            }
            else
            {
                solveGame(board, currentMoviment);
            }
        }
        else
        {
            solveGame(board, currentMoviment);
        }
    }
}

int
main()
{
    GameState board;
    int position[2] = {0, 0};

    initGame(&board);
    solveGame(&board, position);
    printf("Finish\n");
    printBoard(&board);

    return 0;
}
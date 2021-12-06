#include <stdio.h>
#include <stdbool.h>

/* ######### CONFIG ######### */

#define IS_TO_PRINT_BOARD 1
#define NUMBER_DISCS 7

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
    int pins[NUMBER_DISCS][NUMBER_PINS];
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
#if IS_TO_PRINT_BOARD == 1
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
#else /*#if IS_TO_PRINT_BOARD == 1 */
    UNUSED_PARAMETER(board);
#endif /*#else IS_TO_PRINT_BOARD == 1 */
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
        if (lastMoviment[0] == MIDDLE_PIN)
        {
            if(direction == DIRECTION_LEFT)
            {
                INVERT_DIRECTION(direction);
                currentMoviment[0] = LAST_PIN;
                currentMoviment[1] = FIRST_PIN;
            }
            else
            {
                INVERT_DIRECTION(direction);
                currentMoviment[0] = FIRST_PIN;
                currentMoviment[1] = FIRST_PIN;
            }
        }
        else if ((lastMoviment[1] == LAST_PIN && direction == DIRECTION_LEFT) || (lastMoviment[1] == MIDDLE_PIN && direction == DIRECTION_RIGHT))
        {
            currentMoviment[0] += direction;
            currentMoviment[1] = currentMoviment[0] + direction;
        }
        else if (lastMoviment[0] == lastMoviment[1])
        {
            currentMoviment[1] += direction;
        }
        else
        {
            currentMoviment[1]++;
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
                printf("%d->%d\n", currentMoviment[0] + 1, currentMoviment[1] + 1);
                if (direction == DIRECTION_LEFT)
                {
                    currentMoviment[0] = FIRST_PIN;
                    currentMoviment[1] = FIRST_PIN;
                }
                else
                {
                    currentMoviment[0] = LAST_PIN;
                    currentMoviment[1] = LAST_PIN;
                }
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
#include <stdio.h>

#define PIN1 '1'
#define PIN2 '2'
#define PIN3 '3'

void
solveHanoi(int n, char pin1, char pin2, char pin3)
{
    if (n > 0)
    {
        solveHanoi(n - 1, pin1, pin3, pin2);
        printf("\n%c->%c", pin1, pin3);
        solveHanoi(n - 1, pin2, pin1, pin3);
    }
}

int
main()
{
    int n;

    printf("Discs: ");
    scanf("%d", &n);

    solveHanoi(n, PIN1, PIN2, PIN3);

    return 0;
}

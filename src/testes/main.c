#include<time.h>
#include<stdio.h>

int main()
{
    time_t seconds;
    seconds = time(NULL);

    printf("Antes do while: %d\n\n", seconds);
    while((time(NULL) - seconds) <= 3);
    printf("Depois de 3 segundos: %d\n\n", time(NULL));

    return 0;
}

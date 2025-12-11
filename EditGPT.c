#include <stdio.h>

int isPrime(int n)
{
    if (n <= 1) return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void fibonacci(int terms)
{
    int a = 0, b = 1, next;

    printf("\nFibonacci Series: ");

    for (int i = 1; i <= terms; i++)
    {
        printf("%d ", a);
        next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
}

int main()
{
    int num, terms;

    printf("Enter a number to check if it's prime: ");
    scanf("%d", &num);

    if (isPrime(num))
        printf("%d is a Prime Number.\n", num);
    else
        printf("%d is NOT a Prime Number.\n", num);

    printf("\nHow many Fibonacci terms you want? ");
    scanf("%d", &terms);

    fibonacci(terms);

    return 0;
}


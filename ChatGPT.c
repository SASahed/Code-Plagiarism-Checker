#include <stdio.h>

// Function to check if number is prime
int isPrime(int n)
{
    if (n <= 1) return 0; // 0 and 1 are not prime

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0; // Not prime
    }
    return 1; // Prime
}

// Function to print Fibonacci series
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

// Main Function
int main()
{
    int num, terms;

    // Check Prime Number
    printf("Enter a number to check if it's prime: ");
    scanf("%d", &num);

    if (isPrime(num))
        printf("%d is a Prime Number.\n", num);
    else
        printf("%d is NOT a Prime Number.\n", num);

    // Fibonacci
    printf("\nHow many Fibonacci terms you want? ");
    scanf("%d", &terms);

    fibonacci(terms);

    return 0;
}

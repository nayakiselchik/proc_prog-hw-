#include <stdio.h>
#include <math.h>

double babylonianSqrt(double number, double tolerance, int *iterations){
    if (number < 0) {
        printf("Error: Cannot compute the square root of a negative number.\n");
        return -1.0;
    }
    
    if (number == 0) {
        *iterations = 0;
        return 0.0;
    }

    if (number == 1) {
        *iterations = 0;
        return 1.0;
    }

    double guess = number / 2.0;
    double next_guess = 0.0;
    *iterations = 0;

    while(1)
    {
        next_guess = 0.5 * (guess + number / guess);
        (*iterations)++;
        if (fabs(next_guess - guess) < tolerance)
            break;
        guess = next_guess;
    }
    return next_guess;
}

int main() {
    double number, tolerance, sqrtResult;
    int iterations = 0;

    printf("Enter the number to find the square root of: ");
    scanf("%lf", &number);

    printf("Enter the tolerance for convergence: ");
    scanf("%lf", &tolerance);

    sqrtResult = babylonianSqrt(number, tolerance, &iterations);

    printf("Number of iterations: %d\n", iterations);
    printf("Approximate square root: %.6f\n", sqrtResult);

    return 0;
}

#include <stdio.h>
#include <math.h>

// Factorial function
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int matrixSize = 25; // Number of spaces in the Playfair matrix
    double possibleKeys = factorial(matrixSize);

    // Adjust for symmetries
    possibleKeys /= pow(2, 10); // 2^10 for flipping horizontally or vertically
    possibleKeys /= 2; // Account for swapping pairs of letters

    printf("Approximate number of possible keys for the Playfair cipher: %.0f\n", possibleKeys);

    return 0;
}

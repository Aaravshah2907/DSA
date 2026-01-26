int exponentiation(int base, int exp) {
    if (exp < 0) {
        return -1; // Error: Exponent should be non-negative
    }
    if (exp == 0) {
        return 1; // Base case: any number to the power of 0 is 1
    }
    return base * exponentiation(base, exp - 1); // Recursive case
}
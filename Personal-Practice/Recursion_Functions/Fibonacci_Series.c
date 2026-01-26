int Fibonacci(int n) {
    if (n <= 0) {
        return 0; // Base case: F(0) = 0
    }
    if (n == 1) {
        return 1; // Base case: F(1) = 1
    }
    return Fibonacci(n - 1) + Fibonacci(n - 2); // Recursive case
}
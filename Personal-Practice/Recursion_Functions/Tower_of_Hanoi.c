int Tower_of_Hanoi(int n, char source, char destination, char auxiliary) {
    if (n == 1) {
        // Move disk from source to destination
        return 1;
    }
    int moves = 0;
    moves += Tower_of_Hanoi(n - 1, source, auxiliary, destination);
    moves += 1; // Move disk from source to destination
    moves += Tower_of_Hanoi(n - 1, auxiliary, destination, source);
    return moves;
}

// Example usage:
// int main() {
//     int n = 3; // Number of disks
//     int total_moves = Tower_of_Hanoi(n, 'A', 'C', 'B');
//     printf("Total moves required: %d\n", total_moves);
//     return 0;
// }
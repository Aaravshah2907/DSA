int Binary_Search(int arr[], int low, int high, int target) {
    if (low > high) {
        return -1; // Target not found
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) {
        return mid; // Target found
    } else if (arr[mid] > target) {
        return Binary_Search(arr, low, mid - 1, target); // Search in the left half
    } else {
        return Binary_Search(arr, mid + 1, high, target); // Search in the right half
    }
}
#include <iostream>
#include <vector>
#include <algorithm> // For std::max

using namespace std;

// Function to find the maximum subarray sum using Kadane's Algorithm
int kadaneAlgorithm(const vector<int>& arr) {
    if (arr.empty()) return 0; // Handle empty array case

    long maxSum = arr[0]; // Initialize maximum subarray sum
    long currentSum = arr[0]; // Initialize current sum

    for (int i = 1; i < arr.size(); i++) {
        currentSum = max(static_cast<long>(arr[i]), currentSum + arr[i]); // Update current sum
        maxSum = max(maxSum, currentSum); // Update maximum sum if necessary
    }
    
    return maxSum; 
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, 5, 4};
    int maxSum = kadaneAlgorithm(arr); // Call the Kadane's Algorithm function
    cout << "Maximum subarray sum: " << maxSum << endl; 
    return 0;
}

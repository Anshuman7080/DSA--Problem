#include <iostream>
#include <unordered_set>
using namespace std;

// Returns length of the longest contiguous subsequence
int findLongestConseqSubseq(int arr[], int n) {
    unordered_set<int> numSet(arr, arr + n); // Insert all elements into a set
    int longestStreak = 0;

    for (int num : numSet) {
        // Check if it's the start of a streak
        if (numSet.find(num - 1) == numSet.end()) {
            int currentNum = num;
            int currentStreak = 1;

            // Count the streak
            while (numSet.find(currentNum + 1) != numSet.end()) {
                currentNum++;
                currentStreak++;
            }
            longestStreak = max(longestStreak, currentStreak); // Update longest streak
        }
    }
    return longestStreak;
}

// Driver code
int main() {
    int arr[] = { 1, 2, 2, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Length of the Longest contiguous subsequence is " 
         << findLongestConseqSubseq(arr, n) << endl;
    return 0;
}

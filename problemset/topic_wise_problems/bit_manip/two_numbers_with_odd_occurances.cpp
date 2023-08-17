// problem link: https://www.codingninjas.com/studio/problems/two-numbers-with-odd-occurrences_8160466?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf

// solution: below

vector<int> twoOddNum(vector<int> arr){
    int value = 0;
    for (int i : arr) {
        value ^= i;
    }
    // To get rightmost set bit, we use the trick (num & -num)
    // as -ve of a number is represented as 2's complement so we can access right most set bit.
    int right_bit = value & -value;
    int x = 0, y = 0;
    for (int i : arr) {
        // separeting the numbers based on their right most bit is set or not.
        if ((right_bit & i) == 0) {
            x ^= i;
        } else {
            y ^= i;
        }
    }
    if (x < y) {
        return {y, x};
    }
    return {x, y};
}
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
vector<int> arr;
//xác định cho đúng base case
void SumOfOnes(int n)
{
    if (n == 0 || n == 1)
    {
        arr.push_back(n);
    }
    else
    {
        SumOfOnes(n / 2);
        arr.push_back(n % 2);
        SumOfOnes(n / 2);
    }
}
int main()
{
    int n, l, r, ans = 0;
    cin >> n >> l >> r;
    SumOfOnes(n);
    for (int i = l - 1; i < r; i++)
    {
        ans = ans + arr[i];
    }
    cout << ans;
    return 0;
}

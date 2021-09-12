#include <iostream>
#include <math.h>
using namespace std;
//Bài toán tháp Hà Nội,in ra các bước chuyển và số lần chuyển
//chuyển n cục từ cột x qua cột y
void Tower(int n, char a, char b, char c)
{
    if (n == 1)
        cout << a << "-->" << c << endl;
    else
    {
        Tower(n - 1, a, c, b);
        Tower(1, a, b, c);
        Tower(n - 1, b, a, c);
    }
}
int countTower(int n)
{
    if (n == 1)
        return 1;
    else
        return 2 * countTower(n - 1) + 1;
}
int main()
{
    char x = 'A', y = 'B', z = 'C';
    int n;
    cin >> n;
    Tower(n, x, y, z);
    return 0;
}

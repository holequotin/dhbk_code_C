#include <iostream>
#include <string>
using namespace std;
bool similarStrings(string a, string b)
{
    int l = a.length();
    if (a == b)
        return true;
    if (l == 1)
        return false;
    else
    {
        //chia thành 2 chuỗi bằng nhau
        string a1 = a.substr(0, l / 2);
        string a2 = a.substr(l / 2, l / 2);
        string b1 = b.substr(0, l / 2);
        string b2 = b.substr(l / 2, l / 2);
        //chia để trị
        return (similarStrings(a1, b1) && similarStrings(a2, b2)) || (similarStrings(a1, b2) && similarStrings(a2, b1));
    }
}
int main()
{
    string a, b;
    cin >> a >> b;
    cout << similarStrings(a, b);
    return 0;
}

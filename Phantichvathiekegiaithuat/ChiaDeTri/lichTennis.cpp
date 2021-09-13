#include <iostream>

using namespace std;
//Bài toán xếp lịch tennis,đấu trong n-1 ngày,với số vđv là số chẵn
//Input: n là số vđv
//Output: là ma trận biểu diễn lịch thi đấu qua từng ngày của các Vđv
void xuat(int n, int arr[][1000])
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
//hàm xếp lịch và xuất ra bằng ma trận
int arr[1000][1000];
void xeplich(int n)
{
    if (n == 2)
    {
        arr[1][1] = 2;
        arr[2][1] = 1;
    }
    else
    {
        int m = n / 2;
        //xử lý góc trên trái trước rồi từ đó suy ra các góc khác của bảng
        //suy ra từ trường hợp nhỏ nhất và trường hợp nhỏ nhì
        xeplich(m);
        //góc trái trên,từ góc trái trên cộng m
        //vòng ngoài là cột, vòng trong là hàng
        for (int i = 1; i < m; i++)
        {
            for (int j = m + 1; j <= n; j++)
            {
                arr[j][i] = arr[j - m][i] + m;
            }
        }
        //góc phải trên,lấy tổng rồi trừ m
        for (int i = 1; i <= m; i++)
        {
            for (int j = m; j < n; j++)
            {
                if (i + j <= n)
                    arr[i][j] = i + j;
                else
                    arr[i][j] = i + j - m;
            }
        }
        //góc phải dưới,lấy hiệu rồi cộng m
        for (int i = m + 1; i <= n; i++)
        {
            for (int j = m; j < n; j++)
            {
                if (i - j > 0)
                    arr[i][j] = i - j;
                else
                    arr[i][j] = i - j + m;
            }
        }
    }
}
int main()
{
    int n;
    cin >> n;
    xeplich(n);
    xuat(n, arr);
    return 0;
}

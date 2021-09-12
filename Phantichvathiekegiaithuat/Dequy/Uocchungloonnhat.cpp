#include<iostream>

using namespace std;
// int UCLN(int x,int y){
//     if(x==0||y==0) return x+y;
//     if(x==y) return x;
//     else{
//         if(x>y) return UCLN(x-y,y);
//         else return UCLN(x,y-x);
//     }
// }
int UCLN(int x,int y){
    if(x==0||y==0) return x+y;
    else
    //nếu x<y thì sau 1 lần đệ quy sẽ đảo ngược lại
    return UCLN(y,x%y);
}
int main() {
int x,y;
cin>>x>>y;
cout<<UCLN(x,y);
    return 0;
}

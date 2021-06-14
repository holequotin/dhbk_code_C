#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h> 
#include<windows.h>
char transcode1[20]={' '};
//Một số cấu trúc định nghĩa thêm
typedef struct mon
{
    char name[30];
    int code;
    int cost;
    int number;
} mon ;
typedef struct hoadon
{
    int soluongmonan;
    double tongtien;
    mon monan[100];
} hoadon;
typedef struct ban
{
    int trangthai;//Thanh toán hay chưa
    int tongtien;
    mon monan[100];
} ban ;//bool=>int,true=1,false=0

//Màu sắc
void set_color ( int code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}
//Một số chức năng phụ
void check(ban *ban1,int m){
    int dem=0,i;
    for( i=1;i<m;i++){
        dem=dem+ban1->monan[i].number;
    }
    if(dem==0) ban1->trangthai=0;
    else ban1->trangthai=1;//trả về false khi đang trống
}//Hàm gán trạng thái cho bàn
void reset(ban dayban[],int m,int k){
	int i;
    for( i=1;i<=m;i++){
        dayban[k].monan[i].number=0;
    }
}//Hàm rest lại số lượng món trong chuỗi menu
void trangthai(ban dayban[],int m){
    set_color(6);
    printf("                                    ==============================================================\n");
    printf("                                                    CHAO MUNG DEN VOI QUAN TIN DEP TRAI           ");
    printf("\n                                    ==============================================================\n");
    set_color(7);
    printf("\n                                    BAN SO                    TRANG THAI\n");
    printf("                                    ====================================\n");
    int i;
    for( i=1;i<=10;i++){
        check(&dayban[i],m);
        if(dayban[i].trangthai==1){
            set_color(4);
            printf("                                    Ban so %d                   Chua thanh toan\n",i);
            set_color(7);
            printf("                                    -----------------------------------\n");
        }else{
            set_color(10);
            printf("                                    Ban so %d                   Con trong\n",i);
            set_color(7);
            printf("                                    ------------------------------------\n");
        }
    }
}

//Các thao tác với FILE
void xuatfile(FILE *fout){
    char thucdon[80];
    while(fgets(thucdon,80,fout)!=NULL){ 
        printf("%s",thucdon);
    }
}//Hàm xuất toàn bộ thông tin từ file text ra màn hình
void thongtin(FILE *fout,mon *mon1){
	fscanf(fout,"%d",&mon1->code);
	fgets(mon1->name,sizeof(mon1->name),fout);fflush(stdin);
	fscanf(fout,"%d",&mon1->cost);
}

//Các hàm nhập xuất
void xuat(mon mon1){
	printf("                                    %d %s %d\n",mon1.code,mon1.name,mon1.cost);
}
void customer (mon *mon1){
    printf("Nhap code cua mon:");scanf("%d",&mon1->code);
    if(mon1->code!=0) printf("Nhap so luong mon:");scanf("%d",&mon1->number);
}//Hàm nhập món cần đặt (Dùng cho khách hàng)
void nhaphoadon(ban dayban[],int m,int k){
   // reset(dayban[k].monan,m);
   int code,number;
    while (1)
    {
         printf("Nhap ma mon an:");scanf("%d",&code);
        if(code==0) break;
        while (code<0||code>m-1)
        {
            set_color(4);
            printf("MON AN KHONG TON TAI, VUI LONG NHAP MON KHAC:");
            set_color(10);
            printf("\nNhap ma mon an:");
            scanf("%d",&code);
        }
        printf("Nhap so luong mon an:");scanf("%d",&number);
        int i;
        for( i=1;i<m;i++){
            if(code==dayban[k].monan[i].code){
                dayban[k].monan[i].number=number;
            }
        }
    }
    
    printf("Cam on quy khach da chon mon,chuc quy khach ngon mieng <3 <3 <3");
    printf("\n=================================================");
    
}
void xuathoadon(ban dayban[],int m,FILE *fin,int k){
    int tong=0;//dayban[k].
    check(&dayban[k],m);
    set_color(4);
    if(dayban[k].trangthai==0) printf("BAN NAY DANG TRONG\n");
    else{
        system("cls");
        set_color(10);
    if(k!=0){
    printf("BAN DANG THANH TOAN CHO BAN SO: %d",k);
    }
    printf("\n----------------------------------");
    set_color(6);
    printf("\nTHONG TIN CUA HOA DON:");
    fprintf(fin,"%s","\nTHONG TIN CUA HOA DON:");
    set_color(10);
    if(k!=0){
    printf("\nBAN SO: %d",k);
    fprintf(fin,"\nBAN SO: %d",k);
    }else{
        printf("\nDON HANG MANG VE");
    fprintf(fin,"\nDON HANG MANG VE");
    }
    set_color(4);
    printf("\nTEN MON\t\t\t\tSO LUONG\tTHANH TIEN\n");
    fprintf(fin,"%s","\nTEN MON\t\t\t\tSO LUONG\tTHANH TIEN\n");
    set_color(7);
    int i;
    for( i=1;i<m;i++){
        if(dayban[k].monan[i].number!=0){//dayban[k].monan[i].number!=0
            printf("%s\t%d\t\t%d\n",dayban[k].monan[i].name,dayban[k].monan[i].number,dayban[k].monan[i].cost*dayban[k].monan[i].number);
            fprintf(fin,"%s\t%d\t\t%d\n",dayban[k].monan[i].name,dayban[k].monan[i].number,dayban[k].monan[i].cost*dayban[k].monan[i].number);
            tong=tong+dayban[k].monan[i].cost*dayban[k].monan[i].number;
        }
    }
    set_color(10);
    printf("TONG TIEN:%d",tong);
    fprintf(fin,"TONG TIEN:%d",tong);
    if(tong>2000000) tong=tong*0.75;
    printf("\nTONG TIEN KHACH PHAI TRA:%d",tong);
    time_t now;
    time(&now);
    printf("\nTHANH TOAN LUC:%s",ctime(&now));
    set_color(6);
    printf("=========================================================");
    fprintf(fin,"\nTONG TIEN KHACH PHAI TRA:%d",tong);
    fprintf(fin,"\nTHANH TOAN LUC:%s",ctime(&now));
    fprintf(fin,"\n=========================================================");
    reset(dayban,m,k);
    }
}
void nhap(char mk[]){
    char x;//Đây là thằng nhận dữ liệu từ bàn phím và đưa và chuỗi
    int size=0;
    //Enter:13;Backspace:8
    while (x!=13)
    {   
        x=getch();fflush(stdin);//Lấy kí tự
        if(x==13){
            break;
        }
        if(mk[0]=='\0'){
            while (1)
            {
                x=getch();fflush(stdin);
                if(x!=8){
                    break;
                }
            }
            
        }
        if(x==8){
            if(size!=0){
                mk[size]='\0';
            size--;
            printf("\b \b");
            }
        }else{
            printf("%c",x);
            mk[size]=x;
            size++;
            printf("\b \b*");
        }
    } 
}
void nhapmagiaodich(char mk1[]){
    char mk2[20]={' '};
    printf("                                    NHAP MA GIAO DICH:");nhap(mk1);
    printf("\n                                    XAC NHAN MA GIAO DICH:");nhap(mk2);
    while (strcmp(mk1,mk2)!=0)
    {
        printf("\n                                    HAI MA GIAO DICH KHONG GIONG NHAU,VUI LONG NHAP LAI:\n");
        printf("                                    NHAP MA GIAO DICH:");nhap(mk1);
    printf("\n                                    XAC NHAN MA GIAO DICH:");nhap(mk2);
    printf("\n                                    ");
    }
    
}

//Các chức năng
void option1(ban dayban[],int m,int n){
    int k;
    trangthai(dayban,m);
    set_color(10);
    printf("XIN MOI CHON BAN:");scanf("%d",&k);
    while (k<=0||k>10)
    {   set_color(4);
        printf("BAN KHONG TON TAI, VUI LONG CHON BAN KHAC:");
        set_color(10);
        scanf("%d",&k);
    }
    
    check(&dayban[k],m);
    if(dayban[k].trangthai==0){
        system("cls");
    printf("BAN DANG DAT MON CHO BAN SO %d",k);
    set_color(6);
    printf("\n                                    ========================MENU NGAY HOM NAY===================");
    set_color(4);
    printf("\n                                    TEN MON                    GIA TIEN\n");
    set_color(7);
    int i;
        for ( i = 1; i <m; i++)
            {
                xuat(dayban[k].monan[i]);
            }
            set_color(6);
        printf("\n                                    =========================================================\n");
        set_color(10);
    printf("MOI QUY KHACH CHON MON\nNEU KHONG CHON NUA THI QUY KHACH NHAP MA MON LA '0'\n");
        nhaphoadon(dayban,m,k);//=>Viết lại hàm nhập hóa đơn
    }else{

        do{
            printf("BAN NAY DA CO NGUOI, VUI LONG CHON BAN KHAC:");
            scanf("%d",&k);
        }while (dayban[k].trangthai==1);
        system("cls");
         printf("BAN DANG DAT MON CHO BAN SO %d",k);
    set_color(6);
    printf("\n                                    ========================MENU NGAY HOM NAY===================");
    set_color(4);
    printf("\n                                    TEN MON                    GIA TIEN\n");
    set_color(7);
    int i;
        for ( i = 1; i <m; i++)
            {
                xuat(dayban[k].monan[i]);
            }
            set_color(6);
        printf("\n                                    =========================================================\n");
        set_color(10);
    printf("MOI QUY KHACH CHON MON\nNEU KHONG CHON NUA THI QUY KHACH NHAP MA MON LA '0'\n");
        n++;
        nhaphoadon(dayban,m,k);//=>Viết lại hàm nhập hóa đơn
    }
    
        
}
void option2(ban dayban[],int m,int n){
    int k;
    trangthai(dayban,m);
    set_color(10);
    printf("CHON BAN MUON DAT THEM MON:");scanf("%d",&k);
     while (k<=0||k>10)
    {   set_color(4);
        printf("BAN KHONG TON TAI, VUI LONG CHON BAN KHAC:");
        set_color(10);
        scanf("%d",&k);
    }
    system("cls");
    printf("BAN DANG DAT THEM MON CHO BAN SO %d",k);
    set_color(6);
    printf("\n                                    ========================MENU NGAY HOM NAY===================\n");
    set_color(4);
    printf("\n                                    Ten mon                    Gia tien\n");
    set_color(7);
    int i;
        for ( i = 1; i <m; i++)
            {
                xuat(dayban[k].monan[i]);
            }
            set_color(6);
        printf("\n                                    =========================================================\n");
        set_color(10);
    printf("MOI QUY KHACH CHON MON\nNEU KHONG CHON NUA THI QUY KHACH NHAP MA MON LA '0'\n");
        nhaphoadon(dayban,m,k);//=>Viết lại hàm nhập hóa đơn

}
void option4(ban dayban[],int m,FILE *fin){
    int k,dem=0,i;
    for( i=1;i<=10;i++){
        check(&dayban[i],m);
        if(dayban[i].trangthai==1) dem++;
    }
    if(dem!=0){
    trangthai(dayban,m);
    set_color(10);
    printf("CHON BAN MUON THANH TOAN:");scanf("%d",&k);
     while (k<=0||k>10)
    {
        set_color(4);
        printf("BAN KHONG TON TAI, VUI LONG CHON BAN KHAC:");
        set_color(10); 
        scanf("%d",&k);
    }
  //  printf("BAN DANG THANH TOAN CHO BAN SO %d",k);
    xuathoadon(dayban,m,fin,k);
    set_color(6);
    int x;
    printf("\nBAN CO MUON THANH TOAN NUA KHONG??");set_color(6);
    printf("\n\n1/TIEP TUC THANH TOAN                         2/QUAY VE MAN HINH CHINH\n");
    scanf("%d",&x);
    while (x<1||x>2)
    {
        printf("\nVUI LONG CHON LAI CHUC NANG:");
        scanf("%d",&x); 
    }
    if(x==1)  {
        system("cls");
        option4(dayban,m,fin);system("cls");
    }}else{ 
        system("cls");
        set_color(6);
        printf("                                    ================================================================\n");
        printf("                                                    CHAO MUNG DEN VOI QUAN TIN DEP TRAI           ");
        printf("\n                                    ================================================================");
        set_color(10);
        printf("\n\n\n\n                                                    =================================\n                                                    TAT CA CAC BAN DA DUOC THANH TOAN\n                                                    =================================\n");
    getch();}
}
void option5(char transcode1[],FILE *fin){
    fclose(fin);
    char transcode2[20]={' '};
    set_color(10);
     printf("NHAP MA GIAO DICH:");nhap(transcode2);
            if(strcmp(transcode1,transcode2)!=0){
            while(strcmp(transcode2,transcode1)!=0){
                set_color(4);
                printf("\nMA GIAO DICH SAI, VUI LONG NHAP LAI MA GIAO DICH:");
                set_color(10);
                nhap(transcode2);
            }}
            system("cls");
            fopen("D:\\PPL1\\Hoadon.txt","r");
            set_color(6);
            printf("THONG TIN GIAO DICH NGAY HOM NAY:\n");
            set_color(7);
            xuatfile(fin);
            fclose(fin);
            getch();
}
void option3(ban dayban[],int m,FILE *fin){
    printf("BAN DANG DAT MON CHO DON HANG DEM VE");
    set_color(6);
    printf("\n                                    ========================MENU NGAY HOM NAY===================");
    set_color(4);
    printf("\n                                    TEN MON                    GIA TIEN\n");
    set_color(7);
    int i;
        for ( i = 1; i <m; i++)
            {
                xuat(dayban[0].monan[i]);
            }
            set_color(6);
        printf("\n                                    =========================================================\n");
        set_color(10);
    printf("MOI QUY KHACH CHON MON\nNEU KHONG CHON NUA THI QUY KHACH NHAP MA MON LA '0'\n");
        nhaphoadon(dayban,m,0);//=>Viết lại hàm nhập hóa đơn
        xuathoadon(dayban,m,fin,0);
}
void manhinhchinh(mon arr[],int m,int n,ban dayban[],FILE *fin){
    int k,dem=0,i;
    for( i=1;i<=10;i++){
        check(&dayban[i],m);
        if(dayban[i].trangthai==1) dem++;
    }
    set_color(6);
    printf("                                    ==============================================================\n");
    printf("                                                    CHAO MUNG DEN VOI QUAN TIN DEP TRAI           ");
    printf("\n                                    ========================MENU NGAY HOM NAY===================\n");
    printf("\n");
    set_color(4);
    printf("                                    TEN MON                    GIA TIEN");
    printf("\n                                    --------                    -------\n");
     set_color(7);
        for (i = 1; i <m; i++)
            {
                xuat(arr[i]);
            }
        printf("                                    =========================================================\n");
    if(dem==0){
        set_color(6);
    printf("\n                                    1/ DAT BAN MOI                          2/DAT THEM MON\n                                    -------------                            ------------\n                                    3/DAT MANG VE                            4/THANH TOAN\n                                    -------------\n                                    5/KET THUC NGAY\n");
    set_color(10);
    printf("Nhap chuc nang ban muon:");scanf("%d",&k);
    while (k<=0||k>5)
    {
        printf("Ban da nhap sai chuc nang,vui long nhap lai:");scanf("%d",&k);
    }
    switch (k)
    {
    case 1: 
        system("cls");
        option1(dayban,m,n);
        getch();
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    case 2:
        system("cls");
        option2(dayban,m,n);
        getch();
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    case 3:
        system("cls");
        option3(dayban,m,fin);
        getch();
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    case 4:
        system("cls");
        option4(dayban,m,fin);
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    case 5:
        system("cls");
        option5(transcode1,fin);
        getch;
        
        break;
    }
    }else{
        set_color(6);
         printf("\n                                    1/ DAT BAN MOI                          2/DAT THEM MON\n                                    -------------                            ------------\n                                    3/DAT MANG VE                            4/THANH TOAN\n");
         set_color(10);
    printf("Nhap chuc nang ban muon:");scanf("%d",&k);
    while (k<=0||k>4)
    {
        printf("Ban da nhap sai chuc nang,vui long nhap lai:");scanf("%d",&k);
    }
    switch (k)
    {
    case 1: 
        system("cls");
        option1(dayban,m,n);
        getch();
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    case 2:
        system("cls");
        option2(dayban,m,n);
        getch();
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    case 3:
        system("cls");
        option3(dayban,m,fin);
        getch();
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    case 4:
        system("cls");
        option4(dayban,m,fin);
        system("cls");
        manhinhchinh(dayban[k].monan,m,n,dayban,fin);
        break;
    }
    }

}
void saochep(mon arr1[],ban dayban[],int m){
	int i;
    for( i=0;i<=10;i++){
    	int j;
        for( j=1;j<m;j++){
        dayban[i].monan[j]=arr1[j];
        }
    }
}
int main() {
    FILE *fin;
	FILE *fout;
    //"D:\\PPL1\\Hoadon.txt"
fin=fopen("D:\\PPL1\\Hoadon.txt","a");
fout=fopen("D:\\PPL1\\Menu.txt","r");
int n=0,m=0,k;
//
mon arr[100],mon1;
ban dayban[10];
    while(!feof(fout))
{
	m++;
	thongtin(fout,&arr[m]);
    
}//Lấy thông tin từ file ra trục chính
saochep(arr,dayban,m);
int i;
for( i=0;i<=10;i++){
    reset(dayban,m,i);
    check(&dayban[i],m);
}set_color(10);
    printf("                                    *************XIN CHAO NGAY MOI**********\n");
    printf("\n                                    HAY NHAP MA GIAO DICH CUA NGAY HOM NAY\n");
    nhapmagiaodich(transcode1);
    getch();
    system("cls");
    manhinhchinh(dayban[1].monan,m,n,dayban,fin);
    return 0;
}
 

#include <stdio.h>   //标准输入输出库
#include <windows.h> //将用户从键盘获得的输入进行输出
#include <conio.h>   //获得用户键盘的输入
#include <time.h>    //获取系统时间，用于重置随机数种子

#define WIN_SCORE 100   //获胜所需分数(测试时设置高点)

int high, width;//定义边界尺寸
int position_y, position_x;//玩家飞机位置
int bullet_y, bullet_x;//玩家子弹位置
int enemy_y, enemy_x;//敌军飞机
int score;//获得分数
int flag;//玩家飞机状态
int dj_y, dj_x;//敌机子弹

void startup();//数据初始化
void gotoxy(int x, int y);//光标移动到(x,y)位置
void welcometogame();//初始化界面,程序起始界面
int color(int c);//更改文字颜色
void explation();//游戏右侧显示
void scoreandtips();//显示游戏提示
void show();//显示游戏界面
void endgame();//游戏结束
void jieshao();//介绍页面
void wingame();//获胜页面
void bganimation();//自动背景
void bganimation2();//固定背景

/**
 * 更改文字颜色
 */
int color(int c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //更改文字颜色
    return 0;
}

/**
 * 光标移动到(x,y)位置  
 */
void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);//使光标到这个（x，y）的位置，需要调用#include<windows.h>
}

/**
 * 初始化界面,程序起始界面
 */
void welcometogame(){

    bganimation2();
    int n;
    color(15);
    gotoxy(33, 10);
    printf("飞 机 大 战 v3 - c语言carrot群限定版");
    color(11);
    gotoxy(18, 22);
    printf("1.开始游戏");
    gotoxy(38, 22);
    printf("2.游戏说明");
    gotoxy(58, 22);
    printf("3.退出游戏");
    gotoxy(78, 22);
    printf("4.本人介绍");
    gotoxy(40, 27);
    color(3);
    printf("请选择 1 2 3 4:");
    color(14);
    n=getchar();    //输入选项
    if(getchar()==10){//判断第二个字符是否为回车 顺便吃掉
        
    }
    else{
        n=-1;
        fflush(stdin);//清空输入缓冲区
    }
    printf("=%d",n);
    switch (n-48){
    case 1:
        system("cls");
        show();
        break;
    case 2:
        explation();
        break;
    case 3:
        exit(0);
        break;
    case 4:
        jieshao();
        break;
    default:
        color(12);
        gotoxy(40, 28);
        printf("请输入1-4之间的数!");
        _getch();//调用
        system("cls");//清屏
        welcometogame();
    }

}

/**
 * 介绍页面
 */
void jieshao(){
    int i, j = 1;
    system("cls");
    color(10);
    gotoxy(44, 1);
    printf("本人介绍");
    color(2);
    for (i = 3; i <= 28; i++)  //输出上下边框===
    {
        for (j = 6; j <= 80; j++) //输出左右边框||
        {
            gotoxy(j, i);
            if (i == 3 || i == 28) printf("=");
            else if (j == 6 || j == 80) printf("||");
        }
    }
    color(3);
    gotoxy(20, 5);
    printf("作者很帅");
    color(10);
    gotoxy(20, 8);
    printf("很帅");
    color(14);
    gotoxy(20, 11);
    printf("非常帅");
    color(11);
    gotoxy(20, 14);
    printf("非常非常帅");
    color(4);

    gotoxy(20, 20);
    printf("/*****按任意键返回主页面*****/");
    _getch();
    system("cls");
    welcometogame();
}

/**
 * 游戏右侧显示
 */
void explation()
{
    int i, j = 1;
    system("cls");
    color(10);
    gotoxy(44, 1);
    printf("游戏说明");
    color(2);
    for (i = 3; i <= 28; i++)  //输出上下边框===
    {
        for (j = 6; j <= 80; j++) //输出左右边框||
        {
            gotoxy(j, i);
            if (i == 3 || i == 28) printf("=");
            else if (j == 6 || j == 80) printf("||");
        }
    }
    color(3);
    gotoxy(20, 5);
    printf("1. W,A,S,D 分别控制飞机的上下左右移动");
    color(10);
    gotoxy(20, 8);
    printf("2. 按空格发射子弹，打中敌机即可得到一分");
    color(14);
    gotoxy(20, 11);
    printf("3.碰到敌机子弹死亡");
    color(11);
    gotoxy(20, 14);
    printf("4. 界面输入3 ：退出游戏");
    color(4);
    gotoxy(20, 17);
    printf("5. 玩的愉快！！！");
    color(7);
    gotoxy(20, 20);
    printf("/*****按任意键返回主页面*****/");
    _getch();
    system("cls");
    welcometogame();
}

/**
 * 显示游戏提示
 */
void scoreandtips()
{
    gotoxy(50, 8);
    color(14);
    printf("游戏得分：%d ", score);
    gotoxy(50, 10);
    printf("用W A S D 分别控制飞机的移动");
    gotoxy(50, 12);
    printf("按下空格键即为发射炮弹");
    gotoxy(50, 14);
    printf("* 的样子就是敌人的飞机");
}


void HideCursor() // 用于隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/**
 * 数据初始化
 */
void startup(){

    high = 20;
    width = 40;

    position_y = high - 3;
    position_x = width / 2;

    bullet_y = -1;//隐藏初始的子弹位置#2022年3月4日16:31:44
    bullet_x = position_x;

    enemy_y = 0;
    enemy_x = position_x;
    dj_y = 0 ;
    dj_x = enemy_x ;

    score = 0;

    flag = 0;

//    dj_y=-1;//隐藏初始的敌机子弹
//    dj_x=-1;

    HideCursor();
}

/**
 * 显示游戏界面
 */
void show(){
    int i, j, k;
   
    for (i = 0; i <= high; i++)
    {
        for (j = 0; j <= width; j++)
        {

            if ((i == position_y) && (j == position_x) || (i == position_y + 1) && (j == position_x - 1) || (i == position_y + 1) && (j == position_x + 1))
            {
                //  gotoxy(i,j);
                printf("^");
            }
            else if ((i == enemy_y) && (j == enemy_x) || (i == enemy_y - 1) && (j == enemy_x - 1) || (i == enemy_y - 1) && (j == enemy_x + 1))
            {
                //   gotoxy(i,j);
                printf("*");
                
            }
            else if ((i == bullet_y) && (j == bullet_x))
            {
                //   gotoxy(i,j);
                printf("|");//玩家子弹
            }
            else if ((i == dj_y) && (j == dj_x))
             {
             	printf ("|");//敌方子弹
			 }
            else if ((j == width) || (i == high) || (j == 0) || (i == 0))  //打印边界
            {
                //  gotoxy(i,j);
                printf("-");
            }
            else
            {
                //  gotoxy(i,j);
                printf(" ");
            }
        }
        printf("\n");
    }
    
    if ((position_y == enemy_y) && (position_x == enemy_x))
    {

        flag = 1;   //飞机撞毁 游戏结束



    }
    else if((position_y == dj_y) && (position_x == dj_x))
    {

        flag = 1;   //飞机撞毁 游戏结束



    }
    else
    {
        printf("分数 %d", score);
    }
    if (score == WIN_SCORE)
    {
        wingame();
    }


}

/**
 * 固定背景
 */
void bganimation2(){
	int i, j, bj_x1, bj_y1;
    bj_x1 = 47;
    bj_y1 = 14;
     for (i = 0; i <= 100; i++)
    {
        for (j = 0; j <= 30; j++)
        {

            if ((i == bj_x1) && (j == bj_y1) || (i == bj_x1 + 1) && (j == bj_y1 +1) || (i == bj_x1 -1) && (j == bj_y1 + 1))
            {
                gotoxy(i, j);
                color(4);
                printf("**");
            }
         }
         
		 }
}

/**
 * 自动背景
 */
void bganimation(){
    int i, j, bj_x1, bj_y1, bj_x2, bj_y2;
    bj_x1 = 30;
    bj_y1 = 20;
    bj_x2 = 30;
    bj_y2 = 80;
    for (i = 0; i <= 100; i++)
    {
        for (j = 0; j <= 30; j++)
        {

            if ((i == bj_x1) && (j == bj_y1) || (i == bj_x1 + 1) && (j == bj_y1 - 1) || (i == bj_x1 + 1) && (j == bj_y1 + 1))
            {
                gotoxy(i, j);
                printf("^");
            }
            bj_x1--;
            bj_y1++;
            if ((i == bj_x2) && (j == bj_y2) || (i == bj_x2 + 1) && (j == bj_y2 - 1) || (i == bj_x2 + 1) && (j == bj_y2 + 1))
            {
                gotoxy(i, j);
                printf("*");
                
            }
            bj_x2--;
            bj_y2++;
        }
        bj_x1 = 30;
        bj_y1 = 20;
        bj_x2 = 30;
        bj_y2 = 80;

    }
}

/**
 * 获胜页面
 */
void wingame(){
    int i, j = 1;
    system("cls");
    color(10);
    gotoxy(10, 1);
    printf("通关提示");
    color(2);
    for (i = 3; i <= 15; i++)  //输出上下边框===
    {
        for (j = 1; j <= 30; j++) //输出左右边框||
        {
            gotoxy(j, i);
            if (i == 3 || i == 15)
                printf("=");
            else if (j == 1 || j == 30) printf("||");
        }
    }
    color(3);
    gotoxy(8, 5);
    score = 0;
    printf("恭喜你，牛逼，通关了！\n");


    printf("/*****按任意键返回主页面*****/");

    _getch();

    system("cls");

    welcometogame();

}

/**
 * 游戏结束
 */
void endgame(){
    int k, f;
    system("cls");
    printf("游戏结束!!!\n");
    printf("输入1再玩一次,输入2返回主菜单,输入3退出游戏");
    scanf("%d", &k);
    system("cls");
    switch (k)
    {
    case 1:
        printf("重新玩游戏");
        system("cls");
        startup();   // 数据初始化
        show();
        break;
    case 2:
        printf("返回主菜单");
        system("cls");
        welcometogame();
        startup();
        break;
    case 3:
        
        exit(0);
        break;
    default:
        color(12);
        gotoxy(40, 28);
        system("cls");
        printf("输入错误,输入任意键回到主菜单");
        _getch();
        welcometogame();
        startup();
        system("cls");
    }
}


void withoutInpute()
{
    if (bullet_y > 0)
        bullet_y--;
    else {
        bullet_y = -1;
    }
    if ((bullet_y == enemy_y) && (bullet_x == enemy_x)) //子弹命中敌机
    {
        score++;
        bullet_y = -1;
        enemy_y = 1;
        srand( (unsigned int)time(NULL) );     //调用time函数，将伪随机变为真随机； 
        enemy_x = 1 + rand() % (width-1);   //rand随机函数 #2022年3月4日16:48:03
        dj_y = 0 ;
        dj_x = enemy_x ;
      
    }


    static int speed;
    if (speed < 30)  //敌机飞行速度 
        speed++;
    if (speed == 30)
    {
        if (enemy_y < high)
            enemy_y++;
        else
        {
            enemy_y = 0;
            enemy_x = 0; //随机产生一个在方框内的数。
            srand( (unsigned int)time(NULL) );     //调用time函数，将伪随机变为真随机； 
            enemy_x = 1 + rand() % (width-1);   //rand随机函数 #2022年3月4日16:48:03
            dj_y = 0 ;
            dj_x = enemy_x ;
        }
        speed = 0;
    }
    
    static int speed2; //敌机子弹速度
    if(dj_y>=0){//子弹非隐藏状态才能开始计时和飞行(隐藏状态为-1)
        if (speed2 < 10)
            speed2++;
        if (speed2 == 10)
        {
            if (dj_y < high)
                dj_y++;
            else
            {
                dj_y=high+1;
                dj_y=-1;
                dj_x=-1;
            }
            speed2=0;
        }
    }
}
void withInpute()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if ((input == 'w') && position_y > 1)
            position_y--;
        if ((input == 's') && position_y < high - 1)
            position_y++;
        if ((input == 'a') && position_x > 1)
            position_x--;
        if ((input == 'd') && position_x < width - 1)
            position_x++;
        if (input == ' ')
        {
            bullet_y = position_y - 1;
            bullet_x = position_x;
        }
    }
}

int main(void)
{
    system("mode con cols=100 lines=30");  //设置控制台的宽高
    welcometogame();
    startup();
    while (1){
        gotoxy(0, 0);
        show();
        scoreandtips();

        if (flag == 1)
        {
            endgame();
        }
        withoutInpute();
        withInpute();
    }
    return 0;
}

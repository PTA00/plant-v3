#include<stdio.h>
#include<stdio.h>
#include<windows.h>   //将用户从键盘获得的输入进行输出
#include<conio.h>   //获得用户键盘的输入
#include<time.h>
//定义全局变量
int high, width;//定义边界 
int position_x, position_y;//飞机位置
int bullet_x, bullet_y;//子弹位置
int enemy_x, enemy_y;//敌军飞机
int score;//获得分数
int flag;//飞机状态
int dj_x,dj_y;
void gotoxy(int x, int y);//光标移动到(x,y)位置
void welcometogame();//初始化界面
int color(int c);//更改文字颜色
void explation();//游戏右侧显示
void scoreandtips();//显示游戏提示
void show();//显示游戏界面
void endgame();//游戏结束
void jieshao();//介绍页面
void wingame();//获胜页面
void bganimation();
void bganimation2();

/**
 * 文字颜色函数   
 */
int color(int c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //更改文字颜色
    return 0;
}


void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);//使光标到这个（x，y）的位置，需要调用#include<windows.h>
}



void welcometogame(){//开始界面

   bganimation2();
    int n;
    color(15);
    gotoxy(43, 10);
    printf("飞 机 大 战");
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
    scanf("%d", &n);   //输入选项
    switch (n)
    {
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
        printf("请输入1-3之间的数!");
        _getch();//调用
        system("cls");//清屏
        welcometogame();
    }

}

void jieshao()
{
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


void startup()
{
    high = 20;
    width = 40;

    position_x = high - 3;
    position_y = width / 2;

    bullet_x = -1;//隐藏初始的子弹位置#2022年3月4日16:31:44
    bullet_y = position_y;

    enemy_x = 0;
    enemy_y = position_y;

    score = 0;

    flag = 0;

    HideCursor();
}

void show()    //显示界面
{

    int i, j, k;
   
    for (i = 0; i <= high; i++)
    {
        for (j = 0; j <= width; j++)
        {

            if ((i == position_x) && (j == position_y) || (i == position_x + 1) && (j == position_y - 1) || (i == position_x + 1) && (j == position_y + 1))
            {
                //  gotoxy(i,j);
                printf("^");
            }
            else if ((i == enemy_x) && (j == enemy_y) || (i == enemy_x - 1) && (j == enemy_y - 1) || (i == enemy_x - 1) && (j == enemy_y + 1))
            {
                //   gotoxy(i,j);
                printf("*");
                
            }
            else if ((i == bullet_x) && (j == bullet_y))
            {
                //   gotoxy(i,j);
                printf("|");
            }
            else if ((i == dj_x) && (j == dj_y))
             {
             	printf ("|");
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
    
    if ((position_x == enemy_x) && (position_y == enemy_y))
    {

        flag = 1;   //飞机撞毁 游戏结束



    }
    else
    {
        printf("分数 %d", score);
    }
    if (score == 2)
    {
        wingame();
    }


}
void bganimation2()//固定背景
{
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
void bganimation()//自动背景
{
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

void wingame()
{
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

void endgame()
{
    int k, f;
    system("cls");
    printf("游戏结束!!!\n");
    printf("输入1再玩一次，输入2返回主菜单，输入3退出游戏");
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
    case 3:printf("退出成功");
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
    if (bullet_x > 0)
        bullet_x--;
    else {
        bullet_x = -1;
    }
    if ((bullet_x == enemy_x) && (bullet_y == enemy_y)) //子弹命中敌机
    {
        score++;
        bullet_x = -1;
        enemy_x = 1;
        srand( (unsigned int)time(NULL) );     //调用time函数，将伪随机变为真随机； 
        enemy_y = 1 + rand() % (width-1);   //rand随机函数 #2022年3月4日16:48:03
      
    }


    static int speed;
    if (speed < 30)  //敌机的速度 
        speed++;
    if (speed == 30)
    {
        if (enemy_x < high)
            enemy_x++;
        else
        {
            enemy_x = 0;
            enemy_y = 0; //随机产生一个在方框内的数。
            srand( (unsigned int)time(NULL) );     //调用time函数，将伪随机变为真随机； 
            enemy_y = 1 + rand() % (width-1);   //rand随机函数 #2022年3月4日16:48:03
            dj_x =  enemy_x;
            dj_y =  enemy_y;
        }
        speed = 0;
    }
    
    static int speed2; //dji zidang sdu
     if(speed2 < 10)
       speed2++;
     if (speed2 == 10)
     {
     	if (dj_x < high)
     	  dj_x++;
     	  
//     	else
//     	{
//     		dj_x=high+1;
//		 }
	speed2=0;
	 }

}
void withInpute()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if ((input == 'w') && position_x > 1)
            position_x--;
        if ((input == 's') && position_x < high - 2)
            position_x++;
        if ((input == 'a') && position_y > 1)
            position_y--;
        if ((input == 'd') && position_y < width - 1) // #2022年3月4日16:51:02
            position_y++;
        if (input == ' ')
        {
            bullet_x = position_x - 1;
            bullet_y = position_y;
        }
    }
}

int main()
{
    system("mode con cols=100 lines=30");  //设置控制台的宽高
    welcometogame();
    startup();
    while (1)
    {
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


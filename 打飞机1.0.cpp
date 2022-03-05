#include<stdio.h>
#include<stdio.h>
#include<windows.h>   //将用户从键盘获得的输入进行输出 
#include<conio.h>   //获得用户键盘的输入 
//定义全局变量 
int high,width;   //定义边界 
int position_x,position_y;  //飞机位置 
int bullet_x,bullet_y;  //子弹位置 
int enemy_x,enemy_y;  //敌军飞机 
int score;    //获得分数 
int flag;    //飞机状态 
void gotoxy(int x,int y);   //光标移动到(x,y)位置
void welcometogame();     //初始化界面
int color(int c);       //更改文字颜色
void explation();   //游戏右侧显示 
void scoreandtips();  //显示游戏提示 
void show();   //显示游戏界面 
void endgame();   //游戏结束 
void jieshao();
/**
 * 文字颜色函数   
 */
int color(int c)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);    //更改文字颜色
 return 0;
}
  
 
void gotoxy(int x,int y)
{
  COORD c;
  c.X=x;
  c.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
  
  
  
void welcometogame() //开始界面
{
 int n;
 color(15);
 gotoxy(43,10);
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
 gotoxy(40,27);
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
     explation();    //游戏说明函数
     break;
   case 3:
     exit(0);    //退出游戏
     break;
   case 4:
     jieshao();  
     break;
 default:  
  color(12);
  gotoxy(40,28);
  printf("请输入1-3之间的数!");
  _getch();  //输入任意键
  system("cls"); //清屏
  welcometogame();
  }
}
  
void jieshao()
{
    
	printf("作者非常非常帅");
	
 } 
  
void explation() //游戏提示 
{
 int i,j = 1;
  system("cls");
  color(10);
  gotoxy(44,1);
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
  gotoxy(20,5);
  printf("1. W,A,S,D 分别控制飞机的上下左右移动");
  color(10);
  gotoxy(20,8);
  printf("2. 按空格发射子弹，打中敌机即可得到一分");
  color(14);
  gotoxy(20,11);
  printf("3.碰到敌机子弹死亡");
  color(11);
  gotoxy(20,14);
  printf("4. ESC ：退出游戏");
  color(4);
  gotoxy(20,17);
  printf("5. 玩的愉快！！！");
  color(7);
 gotoxy(20,20);
 printf("/*****按任意键返回主页面*****/");
  _getch();       
  system("cls");
  welcometogame();
}
  
void scoreandtips()//游戏侧边提示 
{
 gotoxy(50,8);
 color(14);
 printf("游戏得分：%d ",score);
 gotoxy(50,10);
 printf("用W A S D 分别控制飞机的移动");
 gotoxy(50,12);
 printf("按下空格键即为发射炮弹");
 gotoxy(50,14);
 printf("@ 的样子就是敌人的飞机");
}
  
  
void HideCursor() // 用于隐藏光标
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; // 第二个值为0表示隐藏光标
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
  
  
void startup()   //数据初始化 
{
 high=20;   //定义游戏界面的高度 
 width=40;   //游戏界面的宽度 
  
 position_x=high-3;  //定义飞机的初始位置 
 position_y=width/2;
  
 bullet_x=0;
 bullet_y=position_y; 
  
 enemy_x=0;
 enemy_y=position_y;
  
 score=0;
  
 flag=0;    //飞机完好 
  
 HideCursor();
}
  
void show()    //显示界面 
{
 
 int i,j,k;
 
 for(i=0;i<high;i++)
 {
 for(j=0;j<width;j++)
 {
  if(flag)
  break;
  else if((i==position_x)&&(j==position_y)) //飞机坐标 
  {
  printf("^");
  }
  else if((i==enemy_x)&&(j==enemy_y))  //敌机坐标 
  printf("@");
  else if((i==bullet_x)&&(j==bullet_y))  //子弹坐标 
   printf("|");
  else if ((j==width-1)||(i==high-1)||(j==0)||(i==0))  //打印边界 
  printf("-");
  else
  printf(" ");
 }
 printf("\n"); 
 }
 printf("\n");
 if((position_x==enemy_x)&&(position_y==enemy_y))
 {
  
 flag=1;   //飞机撞毁 游戏结束 
 system("cls");
 
  
 }
 else
 {
  printf("分数 %d",score);
  }
  /** _getch();        //按任意键返回主界面
    system("cls");
    welcometogame();
 */
  
 }
  
void endgame()
{
 int k,f;
 system("cls");
 printf("游戏结束!!!\n");
 printf("输入1再玩一次，输入2返回主菜单，输入3退出游戏");
 scanf("%d",&k);
 system("cls");
 switch(k) 
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
   gotoxy(40,28);
   system("cls");
   printf("输入错误,输入任意键回到主菜单");
   _getch();  //输入任意键
   welcometogame(); 
   startup();   
   system("cls");  //清屏
 } 
}
  
  
void withoutInpute()   //与用户输入无关
{
 if(bullet_x>0)    //子弹上升效果 
 bullet_x--;
 if((bullet_x==enemy_x)&&(bullet_y==enemy_y)) //子弹命中敌机 
 {
 score++;
 bullet_x=-1; 
 enemy_x=1;
 enemy_y=2+rand()%width-2;
 } 
  
  
 static int speed;
 if(speed<30)   //减慢敌机速度，不影响飞机和子弹速度 
 speed++;
 if(speed==30)
 {
 if(enemy_x<high)
  enemy_x++;
 else
 {
  enemy_x=0;
  enemy_y=2+rand()%width-2;
 }
 speed=0;
 }
  
  
  
  
}
void withInpute()   //与用户输入有关 
{
 char input;
 if(kbhit())     //控制飞机方向 
 {
 input=getch();
 if((input=='w')&&position_x>1)
  position_x--; 
 if((input=='s')&&position_x<high-2)
  position_x++; 
 if((input=='a')&&position_y>1)
  position_y--; 
 if((input=='d')&&position_y<width-2)
  position_y++;
 if(input==' ')
 {
  bullet_x=position_x-1;
  bullet_y=position_y;
 }
 }
}
  
int main()
{
 system("mode con cols=100 lines=30");  //设置控制台的宽高
 welcometogame();
 startup();   // 数据初始化
 //explation();
 while(1)  
 {
 gotoxy(0,0);
 show();   
 scoreandtips(); 
 if(flag == 1)
 {
  endgame(); 
 }
 withoutInpute(); // 与用户输入无关的更新
 withInpute();  // 与用户输入有关的更新
 }
 return 0;
 }

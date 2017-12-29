/*贪吃蛇Dome2.1  最后编辑于12.30 机实验16余鑫 16105050133*/

/*用到了：数组，指针，动态内存分配，结构体等知识及WINDOWS的部分API*/
/*         
除了光标设置函数SetConsoleCursorPosition是通过网络查询所得，其他均为原创
*/
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>	//包含清屏函数的头文件
#include<time.h>

typedef struct
{
	
}SnakerTypeDef;

typedef struct
{
	
}AuthorInfoTypeDef;

#define N 20
#define SPEED 100
#define LENGTH_MAX 40	//定义最大蛇身长度
int LENGTH_TARGET=40;	//定义长度目标值

void gotoxy(int x,int y)	//定义gotoxy函数
{ 
	COORD coord; 
	coord.X=x; 
	coord.Y=y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);	//光标定位到xy
}


int main()
{





int testlength=0;	//前缀为test是用来测试debug用的测试变量
int testfood[2]={0,0};	//前缀为test是用来测试用的测试变量
int testtime=0;	//前缀为test是用来测试用的测试变量
int testR[2]={0,0};	//前缀为test是用来测试用的测试变量





	srand(time(0));
	int c=0;	//键盘输入变量
	int x=3;
	int i;	//定义临时循环变量
	int ri,li,r,l;
	int length=6;	//定义蛇身长度变量
	int v[2]={0,1};	//定义并速度变量向右


	int R_Init[7]={2,2,2,2,2,2,2};	//行坐标初始化数值
	int L_Init[7]={7,6,5,4,3,2,1};	//列坐标初始化数值
	int* R=(int*)malloc(LENGTH_MAX*sizeof(int));	//为其分配动态内存，当作数组来用
	int* L=(int*)malloc(LENGTH_MAX*sizeof(int));	//这样可以初始化自定义数组
	for(int i=0;i<7;i++)
	{
		R[i]=R_Init[i];
		L[i]=L_Init[i];
	}
//	int R[LENGTH_MAX]={2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0};	//定义行坐标储存数组变量
//	int L[LENGTH_MAX]={7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0};	//定义列坐标储存数组变量

	int food[2];	//定义食物坐标
	food[0]=rand()%(N-2)+1;	//初始化随机行坐标
	food[1]=rand()%(N-2)+1;	//初始化随机列坐标
	char board[40][40];	//定义棋盘二维数组

	for(i=0;i<N;i++)	//定义上下边界
	{
		board[(N-1)][i]='-';
		board[0][i]='-';
	}

	for(i=0;i<N;i++)	//定义左右边界
	{
		board[i][0]='|';
		board[i][(N-1)]='|';
	}

	printf("\n");
	printf("\n");
	printf("    ----------贪吃蛇Dome2.1---------\n");
	printf("                            --余鑫\n");
	printf("小提示：\nW控制上 S控制下 A控制左 D控制右\n");
	printf("\n     按下任意键开始游戏");
	getch();

	system("cls");	//清屏

	while(1)
	{

testlength=length;

		if(R[0]==0||R[0]==(N-1)||L[0]==0||L[0]==(N-1))	//判断是否触碰到边界
		{
			printf("\n超脱四界之外……你已超脱此棋盘\n           最终长度：%d\n即将退出\n",length);
			goto a;
		}


		for(ri=1;ri<N-1;ri++)
			for(li=1;li<N-1;li++)
				board[ri][li]=' ';	//	定义棋盘内圈为英文空格（外圈为边界）

		board[food[0]][food[1]]='$';	//在棋盘中插入食物$

		for(i=0;i<length;i++)
		{
			r=R[i];
			l=L[i];
			board[r][l]='*';	//在棋盘中插入蛇身*
		}



		gotoxy(1,1);	//定位(清屏)函数
		for(ri=0;ri<N;ri++)	//数组内容最终输出
		{
			printf("\n");
			for(li=0;li<N;li++)
				printf("%c ",board[ri][li]);
		}


		Sleep(SPEED);	//暂停x秒
		c=0;	//重新赋值c
		if(_kbhit()!=0)	//当没有输入时跳过getch语句以让程序流畅进行
		{
			c=getch();	//当有输入时读取键值并保存
		}

		while(_kbhit()!=0)	//手动读取清除键盘缓冲区内容
		{
			i=getch();
		}

		switch(c)	//通过读取键盘字符对速度变量的赋值
		{
		case 119:	//上键键值
			v[0]=-1;
			v[1]=0;
		break;
		case 97:	//左键键值
			v[0]=0;
			v[1]=-1;
		break;
		case 100:	//右键键值
			v[0]=0;
			v[1]=1;
		break;
		case 115:	//下键键值
			v[0]=1;
			v[1]=0;
		break;
		}
testR[0]=R[0];
testR[1]=L[0];
testfood[0]=food[0];
testfood[1]=food[1];

		if((R[0]==food[0])&&(L[0]==food[1]))	//判断是否吃到食物
		{
			length++;	//蛇身长度加一
			srand(time(0));	//使用时间来初始化随机数种子
			food[0]=rand()%(N-2)+1;	//重新分配随机行坐标
			food[1]=rand()%(N-2)+1;	//重新分配随机列坐标
		}

testtime=time(0);

		if(length==LENGTH_MAX)
		{
			gotoxy(5,10);	//移动光标到指定位置（中间）
			printf("给你的耐心一个赞，游戏已通关\n--后续更多版本敬请期待\n");
			goto a;	//吃到最大长度游戏结束，跳转到结束位置
		}

		for(i=length;i>=2;i--)	//蛇身前进
		{
			R[i-1]=R[i-2];
			L[i-1]=L[i-2];
		}

		R[0]=R[0]+v[0];//蛇头前进
		L[0]=L[1]+v[1];

		for(i=1;i<length;i++)
		{
			if((R[0]==R[i])&&(L[0]==L[i]))	//检查蛇头是否与蛇身重合
			{
				gotoxy(5,10);	//移动光标到指定位置（中间）
				printf("你吃到自己了-_-|，游戏结束 - 最终长度是%d\n",length);
				goto a;	//吃到自己游戏结束，跳转到结束位置
			}
		}

/*printf("调试结果：蛇身长：%d	食物随机的行列坐标：%d,%d	时间数函数%d\n蛇头的坐标是：%d,%d\n按任意键继续",testlength,testfood[0],testfood[1],testtime,testR[0],testR[1]);
system("pause");
*/

	}

a:printf("\n\n           ");	//这个，调整最后一句话出现的位置，无功能作用
system("pause");	//暂停一下画面

}



int gameing(int n)	//传入棋盘大小
{


	return 0;
}

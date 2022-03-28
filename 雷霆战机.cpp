/*****************************************
* 其他飞机的产生
* 大BOSS的产生
* 我方飞机的设置
* 其他敌人的设置
* 敌人的进攻
*****************************************/

#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")

//1.定义数据
#define WIDTH 520
#define HEIGHT 800
IMAGE		background1[6];
IMAGE       background2[6];			//设置背景
struct Background
{
	int x = 0, y = 0;		//图片的位置
} back1[6], back2[6];		
bool		isPlay = true;			//判断是否在播放音乐
int			bound = -2;				//游戏关卡
bool		beginIsPlay = true;		//游戏主界面是否绘制
IMAGE mainBack;					//主界面
int frame = 0;						//主界面的变化
int frame_speed = 0;				//变化的速度
bool mainBeginIsPlay = true;		//游戏主界面是否绘制
IMAGE		chooseBackGround[5];	//选择界面背景
int chooseLevel = 1;				//选择界面关卡
int gameLevel = 0;					//选择哪个关卡
bool chooseIsPlay = true;			//选择界面是否运行
bool gameIsPlay = true;				//判断游戏是否进行

//制作游戏选择界面需要的东西
struct Square
{
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
} square1, square2, square3;

//自己的飞机
struct MyPlane 
{
	int x=0, y=0;				//自己飞机的坐标
	IMAGE mimg[2];				//飞机的图片  60 * 62
	int HP = 0;					//飞机的血量
	bool isExist =true;			//飞机是否存活
	int level = 0;				//等级
} myPlane, myPlane1, myPlane2;

//升级
struct Upgrading
{
	int x = 0, y = 0;			//升级物体的位置
	IMAGE uimg[2];				//升级物体的图片
	bool isExist = false;		//是否存在升级的物体
	int x_speed = 0, y_speed = 0;	//飞行的速度
	bool isFall = true;			//是否下落
} upgrading[4];

//大子弹
struct PlayerBullet
{
	int x = 0, y = 0;			//自己大子弹的坐标
	IMAGE bimg[2];				//大子弹的图片  9 * 21
	bool isExist = true;		//大子弹是否存在
	int speed = 0;				//大子弹上升的速读
	int attack = 0;				//每发大子弹对敌人造成的伤害
} myPlane_bullet[100];			//大子弹的数量
unsigned t1, t2;

//小子弹
struct SmallPlayerBullet
{
	int x = 0, y = 0;			//自己小子弹的坐标
	IMAGE sbimg[2];				//小子弹的图片 5 * 11
	bool isExist = true;		//小子弹是否存在
	int speed = 0;				//小子弹上升的速读
	int attack = 0;				//每发小子弹对敌人造成的伤害
} myPlane_smallBullet[200];		//小子弹的数量

//第二类飞机的大子弹
struct Throughout1
{
	int x = 0, y = 0;			//自己第二类飞机的子弹
	IMAGE sbimg[2];				//子弹的图片
	bool isExist = true;		//子弹是否存在
	int speed = 0;				//子弹上升的速度
	int attack = 0;				//每发子弹对敌人造成的伤害
} myPlane1_bullet1[60];			//子弹的数量

//第二类飞机的小子弹
struct Throughout2
{
	int x = 0, y = 0;			//自己第二类飞机的子弹
	IMAGE sbimg[2];				//子弹的图片
	bool isExist = true;		//子弹是否存在
	int speed = 0;				//子弹上升的速度
	int attack = 0;				//每发子弹对敌人造成的伤害
} myPlane1_bullet2[30];			//子弹的数量

//第三类飞机的大子弹'
struct Throughout3 
{
	int x = 0, y = 0;			//自己第三部飞机的子弹
	IMAGE sbimg[2];				//子弹的图片
	bool isExist = true;		//子弹是否存在
	int speed = 0;				//子弹上升的速度
	int attack = 0;				//每发子弹对敌人造成的伤害
} myPlane2_bullet1[30];			//子弹的数量

//第三类飞机的跟踪子弹
struct Track
{
	int x = 0, y = 0;			//跟踪子弹的位置
	IMAGE sbimg[2];				//子弹的图片
	bool isExist = true;		//子弹是否存在
	int x_speed = 0;
	int y_speed = 0;			//子弹的速度
	int attack = 0;				//子弹的伤害
}track_bullet[10];				//子弹的数量
unsigned Ta, Tb;				//什么时候发射跟踪子弹
int track_bulletmove = 0;		//什么时候移动

//小敌机
struct LittleEnemy
{
	int x=0, y=0;				//小敌机的坐标
	IMAGE eimg[2];				//小敌机的图片	91 * 70
	int HP = 0;					//小敌机的血量
	bool isExist = true;		//小敌机是否存活
	int speed = 0;				//小敌机的速度
	int collision = 0;			//小敌机与自己飞机撞击的时候扣除的血量
	bool isStop = true;			//小敌机是否停止
	bool attack = true;			//小敌机是否进攻
	int count = 0;				//记录发生了多少次
	bool isBigAttack[60];		//第二类大子弹贯穿时，子弹不会消失，但不能对其造成伤害
	bool isLittleAttck[30];		//第二类小子弹贯穿时，子弹不会消失，但不能对其造成伤害
	bool isThirdAttack[30];		//第三类小子弹贯穿时，子弹不会消失，但不能对其造成伤害
} littleEnemy1[4];				//小敌机的数量
bool littleEnemy1_creation = true;		//小敌机是否产生
unsigned t3, t4, t5, t6 ,t9, t10;		//其中t3 t4是记录飞机是否产生  t5 t6是记录敌机是否发射子弹  t9 t10 是记录敌机发射完子弹便下落

//中敌机
struct MiddleEnemy
{
	int x = 0, y = 0;				//中敌机的坐标
	IMAGE mimg[2];					//中敌机的图片	91 * 70
	int HP = 0;						//中敌机的血量
	bool isExist = true;			//中敌机是否存活
	int speed = 0;					//中敌机的速度
	int collision = 0;				//中敌机与自己飞机撞击的时候扣除的血量
	bool isStop = true;				//中敌机是否停止
	bool attack = true;				//小敌机是否进攻
	int count = 0;					//记录发生了多少次
	bool isBigAttack[60];		//第二类大子弹贯穿时，子弹不会消失，但不能对其造成伤害
	bool isLittleAttck[30];		//第二类小子弹贯穿时，子弹不会消失，但不能对其造成伤害
	bool isThirdAttack[30];		//第三类小子弹贯穿时，子弹不会消失，但不能对其造成伤害
} middleEnemy1[2], middleEnemy2[2];					//中敌机的数量
bool middleEnemy1_creation1 = true;		//中敌机是否产生
bool middleEnemy1_creation2 = true;		//中敌机是否产生
unsigned t11, t12, t13, t14, t15, t16;		//其中t11 t12是记录飞机是否产生  t13 t14是记录敌机是否发射子弹  t15 t16 是记录敌机发射完子弹便下落

//小敌机的子弹
struct LittleEnemy_Bullet
{
	int x = 0, y = 0;			//小敌机子弹的坐标
	IMAGE ebimg[2];				//小敌机子弹的图片 30 * 75
	int attack = 0;			//小敌机子弹对飞机造成的伤害
	int speed = 0;				//小敌机的速度
	bool isExist = true;		//小敌机是否存在
} littleEnemy_bullet1[20];		//小敌机子弹的数量

//中敌机子弹
struct MiddleEnemy_Bullet
{
	int x = 0, y = 0;			//中敌机子弹的坐标
	IMAGE mbimg[2];				//中敌机子弹的图片		17*73
	int attack = 0;				//中敌机子弹造成的伤害
	int speed = 0;				//中敌机子弹的速度
	bool isExist = true;		//中敌机子弹是否存在
} middleEnemy_bullet1[30];		//中敌机子弹的数量

//BOSS发射的子弹
unsigned tc, td, te, tf;
int bullet_frame = 0;		//用于子弹转化
double a = 0.0;		//弧度
struct BOSS_Bullet
{
	int x = 0, y = 0;			//自己小子弹的坐标
	double vx = 0.0;
	double vy = 0.0;			//小子弹的速度
	IMAGE sbimg[2];				//小子弹的图片 5 * 11
	bool isExist = true;		//小子弹是否存在
	int speed = 0;				//小子弹上升的速读
	int attack = 0;				//每发小子弹对敌人造成的伤害
}Boss_bullet1[100], Boss_bullet2[100], Boss_bullet3[100];				//小敌机的数量

//BOSS
struct BOSS
{
	int x = 0, y = 0;			//BOSS的坐标
	IMAGE eimg[2];				//BOSS的图片	91 * 70
	int HP = 0;					//BOSS的血量
	bool isExist = true;		//BOSS是否存活
	int x_speed = 0;			//BOSS的速度
	int y_speed = 0;			//BOSS的速度
	int collision = 0;			//BOSS与自己飞机撞击的时候扣除的血量
	bool isStop = true;			//BOSS是否停止
	bool attack = true;			//BOSS是否进攻
	bool isMad = false;			//BOSS是否暴走
	bool one = false;			//暴走时只发生一次速度的变换
	int level = 0;				//Boss的等级
	bool isFall = false;		//是否下落
	int count = 0;				//每隔多久移动一下
	bool isBigAttack[60];		//第二类大子弹贯穿时，子弹不会消失，但不能对其造成伤害
	bool isLittleAttck[30];		//第二类小子弹贯穿时，子弹不会消失，但不能对其造成伤害
	bool isThirdAttack[30];		//第三类小子弹贯穿时，子弹不会消失，但不能对其造成伤害
} Boss1;

//游戏主界面
void MainBeginInit()
{
	//加载图片
	loadimage(&mainBack, _T("resource/scene/雷霆战机.jpg"));

	//播放背景音乐
	mciSendString(_T("open resource/music/begin_music.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/begin_music.mp3 repeat"), 0, 0, 0);
}

//游戏主界面描绘
void MainBeginDraw()
{
	putimage(0, 0, &mainBack);
	ExMessage m;        //  定义鼠标信息

	m = getmessage();
	if (m.message == WM_LBUTTONDOWN)
	{
		mainBeginIsPlay = false;
		bound = -3;
		chooseIsPlay = true;
	}
}

//选择关卡界面
void ChooseInit()
{
	//加载图片
	loadimage(&chooseBackGround[0], _T("resource/scene/game1.jpg"));
	loadimage(&chooseBackGround[1], _T("resource/scene/game2.jpg"));
	loadimage(&chooseBackGround[2], _T("resource/scene/game3.jpg"));
	loadimage(&chooseBackGround[3], _T("resource/scene/game4.jpg"));
	loadimage(&chooseBackGround[4], _T("resource/scene/game5.jpg"));

	//播放背景音乐
	mciSendString(_T("open resource/music/begin_music.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/begin_music.mp3 repeat"), 0, 0, 0);
}

//选择关卡描绘
void ChooseDraw()
{
	if (chooseLevel == 1)
	{
		putimage(0, 0, &chooseBackGround[0]);
	}
	if (chooseLevel == 2)
	{
		putimage(0, 0, &chooseBackGround[1]);
	}
	if (chooseLevel == 3)
	{
		putimage(0, 0, &chooseBackGround[2]);
	}
	if (chooseLevel == 4)
	{
		putimage(0, 0, &chooseBackGround[3]);
	}
	if (chooseLevel == 5)
	{
		putimage(0, 0, &chooseBackGround[4]);
	}
}

//选择关卡数据更新
void ChooseUpdate()
{
	ExMessage m;        //  定义鼠标信息
	m = getmessage();
	if (m.message == WM_LBUTTONDOWN)
	{
		if (chooseLevel >= 1)
		{
			if (m.x >= 67 && m.x <= 120 &&
				m.y >= 696 && m.y <= 747)
			{
				gameLevel = 1;
				chooseIsPlay = false;
				bound = -1;
				beginIsPlay = true;
			}
		}
		if (chooseLevel >= 2)
		{
			if (m.x >= 278 && m.x <= 332 &&
				m.y >= 604 && m.y <= 655)
			{
				gameLevel = 2;
				chooseIsPlay = false;
				bound = -1;
				beginIsPlay = true;
			}
		}
		if (chooseLevel >= 3)
		{
			if (m.x >= 112 && m.x <= 165 &&
				m.y >= 484 && m.y <= 537)
			{
				gameLevel = 3;
				chooseIsPlay = false;
				bound = -1;
				beginIsPlay = true;
			}
		}
		if (chooseLevel >= 4)
		{
			if (m.x >= 349 && m.x <= 400 &&
				m.y >= 391 && m.y <= 444)
			{
				gameLevel = 4;
				chooseIsPlay = false;
				bound = -1;
				beginIsPlay = true;
			}
		}
		if (chooseLevel >= 5)
		{
			if (m.x >= 95 && m.x <= 149 &&
				m.y >= 302 && m.y <= 353)
			{
				gameLevel = 5;
				chooseIsPlay = false;
				bound = -1;
				beginIsPlay = true;
			}
			if (m.x >= 330 && m.x <= 382 &&
				m.y >= 182 && m.y <= 233)
			{
				gameLevel = 5;
				chooseIsPlay = false;
				bound = -1;
				beginIsPlay = true;
			}
		}
	}
}

//游戏选择飞机界面初始化
void BeginInit()
{
	//加载背景图
	loadimage(&background1[0], _T("resource/scene/bg6.jpg"),520,800);
	loadimage(&background2[0], _T("resource/scene/bg6.jpg"),520,800);
	back1[0].x = back2[0].x = 0;
	back1[0].y = 0;
	back2[0].y = HEIGHT;

	//加载音乐
	mciSendString(_T("open resource/music/begin_music.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/begin_music.mp3 repeat"), 0, 0, 0);

	//加载自己的飞机
	loadimage(&myPlane.mimg[0], _T("resource/newPlayer/uiPlane0.jpg"));
	loadimage(&myPlane.mimg[1], _T("resource/newPlayer/uiPlane1.jpg"));
	myPlane.x = 110;
	myPlane.y = 459;

	//加载正方形1
	square1.x1 = 90;
	square1.x2 = 190;
	square1.y1 = 440;
	square1.y2 = 540;

	//加载自己的飞机1
	loadimage(&myPlane1.mimg[0], _T("resource/newPlayer/myPlane1(0).jpg"));
	loadimage(&myPlane1.mimg[1], _T("resource/newPlayer/myPlane1(1).jpg"));
	myPlane1.x = 230;
	myPlane1.y = 459;

	//加载正方形2
	square2.x1 = 210;
	square2.x2 = 310;
	square2.y1 = 440;
	square2.y2 = 540;

	//加载自己的飞机2
	loadimage(&myPlane2.mimg[0], _T("resource/newPlayer/myPlane2(0).jpg"));
	loadimage(&myPlane2.mimg[1], _T("resource/newPlayer/myPlane2(1).jpg"));
	myPlane2.x = 350;
	myPlane2.y = 459;

	//加载正方形3
	square3.x1 = 330;
	square3.x2 = 430;
	square3.y1 = 440;
	square3.y2 = 540;

	//加载大子弹
	for (int i = 0; i < 100; i++)
	{
		myPlane_bullet[i].speed = 2;
		myPlane_bullet[i].isExist = false;
		loadimage(&myPlane_bullet[i].bimg[0], _T("resource/newPlayer/bullet0.jpg"));
		loadimage(&myPlane_bullet[i].bimg[1], _T("resource/newPlayer/bullet1.jpg"));
	}
	t1 = GetTickCount();

	//加载小子弹
	for (int i = 0; i < 200; i++)
	{
		myPlane_smallBullet[i].speed = 2;
		myPlane_smallBullet[i].isExist = false;
		loadimage(&myPlane_smallBullet[i].sbimg[0], _T("resource/newPlayer/bullet2.jpg"));
		loadimage(&myPlane_smallBullet[i].sbimg[1], _T("resource/newPlayer/bullet3.jpg"));
	}

	//加载第二类飞机的大子弹
	for (int i = 0; i < 60; i++)
	{
		myPlane1_bullet1[i].speed = 2;
		myPlane1_bullet1[i].isExist = false;
		loadimage(&myPlane1_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(2).jpg"));
		loadimage(&myPlane1_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(3).jpg"));
		myPlane1_bullet1[i].attack = 8;
	}

	//加载第二类飞机的小子弹
	for (int i = 0; i < 30; i++)
	{
		myPlane1_bullet2[i].speed = 2;
		myPlane1_bullet2[i].isExist = false;
		loadimage(&myPlane1_bullet2[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(0).jpg"));
		loadimage(&myPlane1_bullet2[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(1).jpg"));
		myPlane1_bullet2[i].attack = 4;
	}

	//加载第三类飞机的大子弹
	for (int i = 0; i < 30; i++)
	{
		myPlane2_bullet1[i].speed = 2;
		myPlane2_bullet1[i].isExist = false;
		loadimage(&myPlane2_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane2_bullet(0).jpg"));
		loadimage(&myPlane2_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane2_bullet(1).jpg"));
	}
}

//游戏选择飞机界面描绘
void BeginDraw()
{
	BeginBatchDraw();

	//绘制背景
	putimage(0, back1[0].y, &background1[0]);
	putimage(back2[0].x, back2[0].y, &background2[0]);

	//绘制自己的飞机
	putimage(myPlane.x, myPlane.y, &myPlane.mimg[0], SRCPAINT);
	putimage(myPlane.x, myPlane.y, &myPlane.mimg[1], SRCAND);

	//绘制自己的飞机1
	putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[0], SRCPAINT);
	putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[1], SRCAND);

	//绘制自己的飞机2
	putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[0], SRCPAINT);
	putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[1], SRCAND);

	//绘制飞机边框
	setlinecolor(YELLOW);
	rectangle(square1.x1, square1.y1, square1.x2, square1.y2);
	rectangle(square2.x1, square2.y1, square2.x2, square2.y2);
	rectangle(square3.x1, square3.y1, square3.x2, square3.y2);

	//绘制标题
	wchar_t str1[100] = L"Thunder Fighter";
	settextcolor(RGB(100,100,255));
	setbkmode(TRANSPARENT);
	settextstyle(30, 25, _T("FW_BLACK"));
	outtextxy(75, 50, str1);

	//绘制字幕
	wchar_t str[100] = L"Please choose one plane you want to fire......";
	settextcolor(GREEN);
	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("FW_BLACK"));
	outtextxy(100, 590, str);

	//绘制字幕
	wchar_t str2[100] = L"You can click 1 and choose first Plane to fire";
	settextcolor(RED);
	outtextxy(100, 610, str2);

	wchar_t str3[100] = L"You can click 2 and choose second Plane to fire";
	settextcolor(LIGHTCYAN);
	outtextxy(100, 630, str3);

	wchar_t str4[100] = L"You can click 3 and choose third Plane to fire";
	settextcolor(LIGHTMAGENTA);
	outtextxy(100, 650, str4);

	//绘制大子弹
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[0], SRCPAINT);
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[1], SRCAND);
		}
	}

	//绘制小子弹
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[0], SRCPAINT);
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[1], SRCAND);
		}
	}

	//绘制第二类飞机大子弹
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[1], SRCAND);
		}
	}

	//绘制第二类飞机的小子弹
	for (int i = 0; i < 30; i++)
	{
		if (myPlane1_bullet2[i].isExist == true)
		{
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[1], SRCAND);
		}
	}

	//绘制第三类飞机的小子弹
	for (int i = 0; i < 30; i++)
	{
		if (myPlane2_bullet1[i].isExist == true)
		{
			putimage(myPlane2_bullet1[i].x, myPlane2_bullet1[i].y, &myPlane2_bullet1[i].sbimg[0], SRCPAINT);
			putimage(myPlane2_bullet1[i].x, myPlane2_bullet1[i].y, &myPlane2_bullet1[i].sbimg[1], SRCAND);
		}
	}

	EndBatchDraw();
}

//游戏选择飞机界面数据更新
void BeginUpdate()
{
	//地图自己的移动
	if (back1[0].y >= HEIGHT)
	{
		back1[0].y = -HEIGHT;
	}
	if (back1[0].y < HEIGHT)
	{
		back1[0].y++;
	}

	//第二张地图
	if (back2[0].y >= HEIGHT)
	{
		back2[0].y = -HEIGHT;
	}
	if (back2[0].y < HEIGHT)
	{
		back2[0].y++;
	}

	//按键按到1，则选择第一辆飞机出战，按键按到2时，则选择第二辆飞机出战
	char key = ' ';
	if (_kbhit())   //检查按键
	{
		key = _getch();   // 接受按键
		if (key == '1')
		{
			beginIsPlay = false;
			bound = 0;
			gameIsPlay = true;
			myPlane.isExist = true;
			myPlane1.isExist = false;
			myPlane2.isExist = false;
		}
		if (key == '2')
		{
			beginIsPlay = false;
			bound = 0;
			gameIsPlay = true;
			myPlane.isExist = false;
			myPlane1.isExist = true;
			myPlane2.isExist = false;
		}
		if (key == '3')
		{
			beginIsPlay = false;
			bound = 0;
			gameIsPlay = true;
			myPlane.isExist = false;
			myPlane1.isExist = false;
			myPlane2.isExist = true;
		}
	}

	t2 = GetTickCount();
	//我的飞机产生的子弹
	if (t2 - t1 >= 100)
	{
		for (int i = 0; i < 100; i++)
		{
			if (myPlane_bullet[i].isExist == false)
			{
				myPlane_bullet[i].isExist = true;
				myPlane_bullet[i].x = myPlane.x + 26;
				myPlane_bullet[i].y = myPlane.y - 21;
				break;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (myPlane_bullet[i].isExist == false)
			{
				myPlane_bullet[i].isExist = true;
				myPlane_bullet[i].x = myPlane.x + 6;
				myPlane_bullet[i].y = myPlane.y - 21;
				break;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (myPlane_bullet[i].isExist == false)
			{
				myPlane_bullet[i].isExist = true;
				myPlane_bullet[i].x = myPlane.x + 45;
				myPlane_bullet[i].y = myPlane.y - 21;
				break;
			}
		}
		for (int i = 0; i < 200; i++)
		{
			if (myPlane_smallBullet[i].isExist == false)
			{
				myPlane_smallBullet[i].isExist = true;
				myPlane_smallBullet[i].x = myPlane.x + 18;
				myPlane_smallBullet[i].y = myPlane.y - 11;
				break;
			}
		}
		for (int i = 0; i < 200; i++)
		{
			if (myPlane_smallBullet[i].isExist == false)
			{
				myPlane_smallBullet[i].isExist = true;
				myPlane_smallBullet[i].x = myPlane.x + 37;
				myPlane_smallBullet[i].y = myPlane.y - 11;
				break;
			}
		}
		for (int i = 0; i < 60; i++)
		{
			if (myPlane1_bullet1[i].isExist == false)
			{
				myPlane1_bullet1[i].isExist = true;
				myPlane1_bullet1[i].x = myPlane1.x + 2;
				myPlane1_bullet1[i].y = myPlane1.y - 44;
				break;
			}
		}
		for (int i = 0; i < 60; i++)
		{
			if (myPlane1_bullet1[i].isExist == false)
			{
				myPlane1_bullet1[i].isExist = true;
				myPlane1_bullet1[i].x = myPlane1.x + 26;
				myPlane1_bullet1[i].y = myPlane1.y - 62;
				break;
			}
		}
		for (int i = 0; i < 60; i++)
		{
			if (myPlane1_bullet1[i].isExist == false)
			{
				myPlane1_bullet1[i].isExist = true;
				myPlane1_bullet1[i].x = myPlane1.x + 48;
				myPlane1_bullet1[i].y = myPlane1.y - 44;
				break;
			}
		}
		for (int i = 0; i < 30; i++)
		{
			if (myPlane1_bullet2[i].isExist == false)
			{
				myPlane1_bullet2[i].isExist = true;
				myPlane1_bullet2[i].x = myPlane1.x + 15;
				myPlane1_bullet2[i].y = myPlane1.y - 44;
				break;
			}
		}
		for (int i = 0; i < 30; i++)
		{
			if (myPlane1_bullet2[i].isExist == false)
			{
				myPlane1_bullet2[i].isExist = true;
				myPlane1_bullet2[i].x = myPlane1.x + 38;
				myPlane1_bullet2[i].y = myPlane1.y - 44;
				break;
			}
		}
		for (int i = 0; i < 30; i++)
		{
			if (myPlane2_bullet1[i].isExist == false)
			{
				myPlane2_bullet1[i].isExist = true;
				myPlane2_bullet1[i].x = myPlane2.x + 0;
				myPlane2_bullet1[i].y = myPlane2.y - 38;
				break;
			}
		}
		for (int i = 0; i < 30; i++)
		{
			if (myPlane2_bullet1[i].isExist == false)
			{
				myPlane2_bullet1[i].isExist = true;
				myPlane2_bullet1[i].x = myPlane2.x + 36;
				myPlane2_bullet1[i].y = myPlane2.y - 38;
				break;
			}
		}
		t1 = t2;
	}

	//大子弹的移动
	for (int i = 0; i < 100; i++)
	{
		//大子弹存在时，大子弹就会往上飞
		if (myPlane_bullet[i].isExist == true)
		{
			myPlane_bullet[i].y -= myPlane_bullet[i].speed;
		}

		//当大子弹飞出去时，大子弹便消失了
		if (myPlane_bullet[i].y <= 0)
		{
			myPlane_bullet[i].isExist = false;
		}
	}

	//小子弹的移动
	for (int i = 0; i < 200; i++)
	{
		//小子弹存在时，小子弹就会往上飞
		if (myPlane_smallBullet[i].isExist == true)
		{
			myPlane_smallBullet[i].y -= myPlane_bullet[i].speed;
		}

		//当小子弹飞出去时，小子弹便消失了
		if (myPlane_smallBullet[i].y <= 0)
		{
			myPlane_smallBullet[i].isExist = false;
		}
	}

	//第二类大子弹的移动
	for (int i = 0; i < 60; i++)
	{
		//大子弹存在时，大子弹就会往上飞
		if (myPlane1_bullet1[i].isExist == true)
		{
			myPlane1_bullet1[i].y -= myPlane1_bullet1[i].speed;
		}

		//当大子弹飞出去时，大子弹便消失了
		if (myPlane1_bullet1[i].y <= 0)
		{
			myPlane1_bullet1[i].isExist = false;
		}
	}

	//第二类大子弹的移动
	for (int i = 0; i < 30; i++)
	{
		//大子弹存在时，大子弹就会往上飞
		if (myPlane1_bullet2[i].isExist == true)
		{
			myPlane1_bullet2[i].y -= myPlane1_bullet2[i].speed;
		}

		//当大子弹飞出去时，大子弹便消失了
		if (myPlane1_bullet2[i].y <= 0)
		{
			myPlane1_bullet2[i].isExist = false;
		}
	}

	//第三类子弹的移动
	for (int i = 0; i < 30; i++)
	{
		//第三类子弹存在时，子弹就会往上飞
		if (myPlane2_bullet1[i].isExist == true)
		{
			myPlane2_bullet1[i].y -= myPlane2_bullet1[i].speed;
		}

		//当第三类子弹飞出去时，子弹便消失了
		if (myPlane2_bullet1[i].y <= 0)
		{
			myPlane2_bullet1[i].isExist = false;
		}
	}
}

//2.游戏初始化
void GameInit()
{
	//加载背景图
	loadimage(&background1[0], _T("resource/scene/bg0.jpg"));
	loadimage(&background2[0], _T("resource/scene/bg0.jpg"));
	back1[0].x = back2[0].x = 0;
	back1[0].y = 0;
	back2[0].y = HEIGHT;

	//加载背景图
	loadimage(&background1[1], _T("resource/scene/bg1.jpg"));
	loadimage(&background2[1], _T("resource/scene/bg1.jpg"));
	back1[1].x = back2[1].x = 0;
	back1[1].y = 0;
	back2[1].y = HEIGHT;

	//加载背景图
	loadimage(&background1[2], _T("resource/scene/bg2.jpg"));
	loadimage(&background2[2], _T("resource/scene/bg2.jpg"));
	back1[2].x = back2[2].x = 0;
	back1[2].y = 0;
	back2[2].y = HEIGHT;

	//加载背景图
	loadimage(&background1[3], _T("resource/scene/bg3.jpg"));
	loadimage(&background2[3], _T("resource/scene/bg3.jpg"));
	back1[3].x = back2[3].x = 0;
	back1[3].y = 0;
	back2[3].y = HEIGHT;

	//加载背景图
	loadimage(&background1[4], _T("resource/scene/bg4.jpg"));
	loadimage(&background2[4], _T("resource/scene/bg4.jpg"));
	back1[4].x = back2[4].x = 0;
	back1[4].y = 0;
	back2[4].y = HEIGHT;
	srand(time(0));

	//播放背景音乐
	mciSendString(_T("open resource/music/level1.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/level1.mp3 repeat"), 0, 0, 0);

	//加载自己的第一部飞机
	loadimage(&myPlane.mimg[0], _T("resource/newPlayer/uiPlane0.jpg"));
	loadimage(&myPlane.mimg[1], _T("resource/newPlayer/uiPlane1.jpg"));
	myPlane.x = 230;
	myPlane.y = HEIGHT - 90;
	myPlane.HP = 100;
	myPlane.level = 1;

	//加载自己的第二部飞机
	loadimage(&myPlane1.mimg[0], _T("resource/newPlayer/myPlane1(0).jpg"));
	loadimage(&myPlane1.mimg[1], _T("resource/newPlayer/myPlane1(1).jpg"));
	myPlane1.x = 230;
	myPlane1.y = HEIGHT - 90;
	myPlane1.HP = 100;
	myPlane1.level = 1;

	//加载自己的第三部飞机
	loadimage(&myPlane2.mimg[0], _T("resource/newPlayer/myPlane2(0).jpg"));
	loadimage(&myPlane2.mimg[1], _T("resource/newPlayer/myPlane2(1).jpg"));
	myPlane2.x = 230;
	myPlane2.y = HEIGHT - 90;
	myPlane2.HP = 100;
	myPlane2.level = 1;

	//加载飞机升级的物体
	for (int i = 0; i < 4; i++)
	{
		loadimage(&upgrading[i].uimg[0], _T("resource/newPlayer/upgrading(0).jpg"));
		loadimage(&upgrading[i].uimg[1], _T("resource/newPlayer/upgrading(1).jpg"));
		upgrading[i].isExist = false;
	};

	//加载大子弹
	for (int i = 0; i < 100; i++)
	{
		myPlane_bullet[i].speed = 2;
		myPlane_bullet[i].isExist = false;
		loadimage(&myPlane_bullet[i].bimg[0], _T("resource/newPlayer/bullet0.jpg"));
		loadimage(&myPlane_bullet[i].bimg[1], _T("resource/newPlayer/bullet1.jpg"));
		myPlane_bullet[i].attack = 10;
	}
	t1 = GetTickCount();

	//加载小子弹
	for (int i = 0; i < 200; i++)
	{
		myPlane_smallBullet[i].speed = 2;
		myPlane_smallBullet[i].isExist = false;
		loadimage(&myPlane_smallBullet[i].sbimg[0], _T("resource/newPlayer/bullet2.jpg"));
		loadimage(&myPlane_smallBullet[i].sbimg[1], _T("resource/newPlayer/bullet3.jpg"));
		myPlane_smallBullet[i].attack = 5;
	}

	//加载第二类飞机的大子弹
	for (int i = 0; i < 60; i++)
	{
		myPlane1_bullet1[i].speed = 2;
		myPlane1_bullet1[i].isExist = false;
		loadimage(&myPlane1_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(2).jpg"));
		loadimage(&myPlane1_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(3).jpg"));
		myPlane1_bullet1[i].attack = 8;
	}

	//加载第二类飞机的小子弹
	for (int i = 0; i < 30; i++)
	{
		myPlane1_bullet2[i].speed = 2;
		myPlane1_bullet2[i].isExist = false;
		loadimage(&myPlane1_bullet2[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(0).jpg"));
		loadimage(&myPlane1_bullet2[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(1).jpg"));
		myPlane1_bullet2[i].attack = 4;
	}

	//加载第三类飞机的大子弹
	for (int i = 0; i < 30; i++)
	{
		myPlane2_bullet1[i].speed = 2;
		myPlane2_bullet1[i].isExist = false;
		loadimage(&myPlane2_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane2_bullet(0).jpg"));
		loadimage(&myPlane2_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane2_bullet(1).jpg"));
	}

	//加载跟踪子弹
	for (int i = 0; i < 10; i++)
	{
		track_bullet[i].isExist = false;
		loadimage(&track_bullet[i].sbimg[0], _T("resource/newPlayer/myPlane2_bullet(2).jpg"));
		loadimage(&track_bullet[i].sbimg[1], _T("resource/newPlayer/myPlane2_bullet(3).jpg"));
	}
	Ta = GetTickCount();

	//加载小敌机
	for (int i = 0; i < 4; i++)
	{
		littleEnemy1[i].speed = 1;
		littleEnemy1[i].isExist = false;
		loadimage(&littleEnemy1[i].eimg[0], _T("resource/newEnemy/littleEnemy1(0).jpg"));
		loadimage(&littleEnemy1[i].eimg[1], _T("resource/newEnemy/littleEnemy1(1).jpg"));
		littleEnemy1[i].collision = 30;
		littleEnemy1[i].HP = 100;
	}
	littleEnemy1_creation = true;
	t3 = t5 = t9 = GetTickCount();
	
	//加载小敌机子弹
	for (int i = 0; i < 20; i++)
	{
		littleEnemy_bullet1[i].speed = 1;
		littleEnemy_bullet1[i].isExist = false;
		loadimage(&littleEnemy_bullet1[i].ebimg[0], _T("resource/newEnemy/littleEnemy2_bullet(0).jpg"));
		loadimage(&littleEnemy_bullet1[i].ebimg[1], _T("resource/newEnemy/littleEnemy2_bullet(1).jpg"));
		littleEnemy_bullet1[i].attack = 20;
	}

	//加载中敌机
	for (int i = 0; i < 2; i++)
	{
		middleEnemy1[i].speed = 1;
		middleEnemy1[i].isExist = false;
		loadimage(&middleEnemy1[i].mimg[0], _T("resource/newEnemy/middleEnemy1(0).jpg"));
		loadimage(&middleEnemy1[i].mimg[1], _T("resource/newEnemy/middleEnemy1(1).jpg"));
		middleEnemy1[i].collision = 50;
		middleEnemy1[i].HP = 10;
	}
	middleEnemy1_creation1 = true;
	t11 = t13 = t15 = GetTickCount();

	//加载第二类中敌机
	for (int i = 0; i < 2; i++)
	{
		middleEnemy2[i].speed = 1;
		middleEnemy2[i].isExist = false;
		loadimage(&middleEnemy2[i].mimg[0], _T("resource/newEnemy/middleEnemy(0).jpg"));
		loadimage(&middleEnemy2[i].mimg[1], _T("resource/newEnemy/middleEnemy(1).jpg"));
		middleEnemy2[i].collision = 50;
		middleEnemy2[i].HP = 10;
	}
	middleEnemy1_creation2 = true;
	t11 = t13 = t15 = GetTickCount();

	//加载中敌机子弹
	for (int i = 0; i < 30; i++)
	{
		middleEnemy_bullet1[i].speed = 1;
		middleEnemy_bullet1[i].isExist = false;
		loadimage(&middleEnemy_bullet1[i].mbimg[0], _T("resource/newEnemy/littleEnemy1_bullet(0).jpg"));
		loadimage(&middleEnemy_bullet1[i].mbimg[1], _T("resource/newEnemy/littleEnemy1_bullet(1).jpg"));
		middleEnemy_bullet1[i].attack = 30;
	}

	//加载Boss1
	Boss1.isExist = false;
	loadimage(&Boss1.eimg[0], _T("resource/newEnemy/Boss(0).jpg"));
	loadimage(&Boss1.eimg[1], _T("resource/newEnemy/Boss(1).jpg"));
	Boss1.collision = 50;
	Boss1.HP = 1000;
	Boss1.attack = false;

	////加载boss的子弹
	tc = te = GetTickCount();
	for (int i = 0; i < 100; i++)
	{
		loadimage(&Boss_bullet1[i].sbimg[0], _T("resource/newEnemy/BOSS_bullet1(0).jpg"));
		loadimage(&Boss_bullet1[i].sbimg[1], _T("resource/newEnemy/BOSS_bullet1(1).jpg"));
		Boss_bullet1[i].isExist = false;
		Boss_bullet1[i].attack = 20;
	}
	for (int i = 0; i < 100; i++)
	{
		loadimage(&Boss_bullet2[i].sbimg[0], _T("resource/newEnemy/BOSS_bullet1(2).jpg"));
		loadimage(&Boss_bullet2[i].sbimg[1], _T("resource/newEnemy/BOSS_bullet1(3).jpg"));
		Boss_bullet2[i].isExist = false;
		Boss_bullet2[i].attack = 20;
	}
	for (int i = 0; i < 100; i++)
	{
		loadimage(&Boss_bullet3[i].sbimg[0], _T("resource/newEnemy/BOSS_bullet1(4).jpg"));
		loadimage(&Boss_bullet3[i].sbimg[1], _T("resource/newEnemy/BOSS_bullet1(5).jpg"));
		Boss_bullet3[i].isExist = false;
		Boss_bullet3[i].attack = 20;
	}
}

//3.绘制
void GameDraw()
{
	BeginBatchDraw();

	//绘制背景
	if (gameLevel == 1)
	{
		putimage(0, back1[0].y, &background1[0]);
		putimage(back2[0].x, back2[0].y, &background2[0]);
	}
	if (gameLevel == 2)
	{
		putimage(0, back1[1].y, &background1[1]);
		putimage(back2[1].x, back2[1].y, &background2[1]);
	}
	if (gameLevel == 3)
	{
		putimage(0, back1[2].y, &background1[2]);
		putimage(back2[2].x, back2[2].y, &background2[2]);
	}
	if (gameLevel == 4)
	{
		putimage(0, back1[3].y, &background1[3]);
		putimage(back2[3].x, back2[3].y, &background2[3]);
	}
	if (gameLevel == 5||gameLevel == 6)
	{
		putimage(0, back1[4].y, &background1[4]);
		putimage(back2[4].x, back2[4].y, &background2[4]);
	}

	//当自己飞机存活时，绘制自己的飞机
	if (myPlane.isExist == true)
	{
		putimage(myPlane.x, myPlane.y, &myPlane.mimg[0], SRCPAINT);
		putimage(myPlane.x, myPlane.y, &myPlane.mimg[1], SRCAND);
	}

	//绘制大子弹
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[0], SRCPAINT);
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[1], SRCAND);
		}
	}

	//绘制升级的物体
	for (int i = 0; i < 4; i++)
	{
		if (upgrading[i].isExist == true)
		{
			putimage(upgrading[i].x, upgrading[i].y, &upgrading[i].uimg[0], SRCPAINT);
			putimage(upgrading[i].x, upgrading[i].y, &upgrading[i].uimg[1], SRCAND);
		}
	}

	//绘制小子弹
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[0], SRCPAINT);
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[1], SRCAND);
		}
	}

	//当自己第二类飞机存活时，绘制自己的飞机
	if (myPlane1.isExist == true)
	{
		putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[0], SRCPAINT);
		putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[1], SRCAND);
	}

	//绘制第二类飞机大子弹
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[1], SRCAND);
		}
	}

	//绘制第二类飞机的小子弹
	for (int i = 0; i < 30; i++)
	{
		if (myPlane1_bullet2[i].isExist == true)
		{
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[1], SRCAND);
		}
	}

	//当自己第三类飞机存活时，绘制自己的飞机
	if (myPlane2.isExist == true)
	{
		putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[0], SRCPAINT);
		putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[1], SRCAND);
	}

	//绘制第三类飞机的小子弹
	for (int i = 0; i < 30; i++)
	{
		if (myPlane2_bullet1[i].isExist == true)
		{
			putimage(myPlane2_bullet1[i].x, myPlane2_bullet1[i].y, &myPlane2_bullet1[i].sbimg[0], SRCPAINT);
			putimage(myPlane2_bullet1[i].x, myPlane2_bullet1[i].y, &myPlane2_bullet1[i].sbimg[1], SRCAND);
		}
	}

	//绘制第三类飞机的小子弹
	for (int i = 0; i < 15; i++)
	{
		if (track_bullet[i].isExist == true)
		{
			putimage(track_bullet[i].x, track_bullet[i].y, &track_bullet[i].sbimg[0], SRCPAINT);
			putimage(track_bullet[i].x, track_bullet[i].y, &track_bullet[i].sbimg[1], SRCAND);
		}
	}

	//绘制小敌机
	for (int i = 0; i < 4; i++)
	{
		if (littleEnemy1[i].isExist == true)
		{
			putimage(littleEnemy1[i].x, littleEnemy1[i].y, &littleEnemy1[i].eimg[0], SRCPAINT);
			putimage(littleEnemy1[i].x, littleEnemy1[i].y, &littleEnemy1[i].eimg[1], SRCAND);
		}
	}

	//绘制中敌机
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy1[i].isExist == true)
		{
			putimage(middleEnemy1[i].x, middleEnemy1[i].y, &middleEnemy1[i].mimg[0], SRCPAINT);
			putimage(middleEnemy1[i].x, middleEnemy1[i].y, &middleEnemy1[i].mimg[1], SRCAND);
		}
	}

	//绘制第二类中敌机
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy2[i].isExist == true)
		{
			putimage(middleEnemy2[i].x, middleEnemy2[i].y, &middleEnemy2[i].mimg[0], SRCPAINT);
			putimage(middleEnemy2[i].x, middleEnemy2[i].y, &middleEnemy2[i].mimg[1], SRCAND);
		}
	}

	//绘制小敌机子弹
	for (int i = 0; i < 20; i++)
	{
		if (littleEnemy_bullet1[i].isExist == true)
		{
			putimage(littleEnemy_bullet1[i].x, littleEnemy_bullet1[i].y, &littleEnemy_bullet1[i].ebimg[0], SRCPAINT);
			putimage(littleEnemy_bullet1[i].x, littleEnemy_bullet1[i].y, &littleEnemy_bullet1[i].ebimg[1], SRCAND);
		}
	}

	//绘制中敌机子弹
	for (int i = 0; i < 30; i++)
	{
		if (middleEnemy_bullet1[i].isExist == true)
		{
			putimage(middleEnemy_bullet1[i].x, middleEnemy_bullet1[i].y, &middleEnemy_bullet1[i].mbimg[0], SRCPAINT);
			putimage(middleEnemy_bullet1[i].x, middleEnemy_bullet1[i].y, &middleEnemy_bullet1[i].mbimg[1], SRCAND);
		}
	}

	//绘制Boss
	if (Boss1.isExist == true)
	{
		putimage(Boss1.x, Boss1.y, &Boss1.eimg[0], SRCPAINT);
		putimage(Boss1.x, Boss1.y, &Boss1.eimg[1], SRCAND);
	}

	//绘制Boss子弹
	for (int i = 0; i < 100; i++)
	{
		if (Boss_bullet1[i].isExist == true)
		{
			putimage(Boss_bullet1[i].x, Boss_bullet1[i].y, &Boss_bullet1[i].sbimg[0], SRCPAINT);
			putimage(Boss_bullet1[i].x, Boss_bullet1[i].y, &Boss_bullet1[i].sbimg[1], SRCAND);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (Boss_bullet2[i].isExist == true)
		{
			putimage(Boss_bullet2[i].x, Boss_bullet2[i].y, &Boss_bullet2[i].sbimg[0], SRCPAINT);
			putimage(Boss_bullet2[i].x, Boss_bullet2[i].y, &Boss_bullet2[i].sbimg[1], SRCAND);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (Boss_bullet3[i].isExist == true)
		{
			putimage(Boss_bullet3[i].x, Boss_bullet3[i].y, &Boss_bullet3[i].sbimg[0], SRCPAINT);
			putimage(Boss_bullet3[i].x, Boss_bullet3[i].y, &Boss_bullet3[i].sbimg[1], SRCAND);
		}
	}

	//绘制字幕
	if (myPlane.isExist == true)
	{
		//绘制我的飞机血量
		wchar_t str[20] = { 0 };
		settextcolor(GREEN);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("Consolas"));
		wsprintf(str, L"HP：%d", myPlane.HP);
		outtextxy(10, 700, str);
	}

	if (myPlane1.isExist == true)
	{
		//绘制我的第一辆飞机血量
		wchar_t str[20] = { 0 };
		settextcolor(GREEN);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("Consolas"));
		wsprintf(str, L"HP：%d", myPlane1.HP);
		outtextxy(10, 700, str);
	}

	if (myPlane2.isExist == true)
	{
		//绘制我的第一辆飞机血量
		wchar_t str[20] = { 0 };
		settextcolor(GREEN);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("Consolas"));
		wsprintf(str, L"HP：%d", myPlane2.HP);
		outtextxy(10, 700, str);
	}

	EndBatchDraw();
}

//4.数据的更新
void GameUpdate()
{
	if (gameLevel == 1)
	{
		//地图自己的移动
		if (back1[0].y >= HEIGHT)
		{
			back1[0].y = -HEIGHT;
		}
		if (back1[0].y < HEIGHT)
		{
			back1[0].y++;
		}

		//第二张地图
		if (back2[0].y >= HEIGHT)
		{
			back2[0].y = -HEIGHT;
		}
		if (back2[0].y < HEIGHT)
		{
			back2[0].y++;
		}
	}

	if (gameLevel == 2)
	{
		//地图自己的移动
		if (back1[1].y >= HEIGHT)
		{
			back1[1].y = -HEIGHT;
		}
		if (back1[1].y < HEIGHT)
		{
			back1[1].y++;
		}

		//第二张地图
		if (back2[1].y >= HEIGHT)
		{
			back2[1].y = -HEIGHT;
		}
		if (back2[1].y < HEIGHT)
		{
			back2[1].y++;
		}
	}

	if (gameLevel == 3)
	{
		//地图自己的移动
		if (back1[2].y >= HEIGHT)
		{
			back1[2].y = -HEIGHT;
		}
		if (back1[2].y < HEIGHT)
		{
			back1[2].y++;
		}

		//第二张地图
		if (back2[2].y >= HEIGHT)
		{
			back2[2].y = -HEIGHT;
		}
		if (back2[2].y < HEIGHT)
		{
			back2[2].y++;
		}
	}

	if (gameLevel == 4)
	{
		//地图自己的移动
		if (back1[3].y >= HEIGHT)
		{
			back1[3].y = -HEIGHT;
		}
		if (back1[3].y < HEIGHT)
		{
			back1[3].y++;
		}

		//第二张地图
		if (back2[3].y >= HEIGHT)
		{
			back2[3].y = -HEIGHT;
		}
		if (back2[3].y < HEIGHT)
		{
			back2[3].y++;
		}
	}

	if (gameLevel == 5||gameLevel == 6)
	{
		//地图自己的移动
		if (back1[4].y >= HEIGHT)
		{
			back1[4].y = -HEIGHT;
		}
		if (back1[4].y < HEIGHT)
		{
			back1[4].y++;
		}

		//第二张地图
		if (back2[4].y >= HEIGHT)
		{
			back2[4].y = -HEIGHT;
		}
		if (back2[4].y < HEIGHT)
		{
			back2[4].y++;
		}
	}
	
	//自己战机的移动
	if (myPlane.isExist == true)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			myPlane.y--;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			myPlane.y++;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			myPlane.x--;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			myPlane.x++;
		}
	}

	//第二类战机的移动
	if (myPlane1.isExist == true)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			myPlane1.y--;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			myPlane1.y++;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			myPlane1.x--;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			myPlane1.x++;
		}
	}

	//第三类战机的移动
	if (myPlane2.isExist == true)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			myPlane2.y--;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			myPlane2.y++;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			myPlane2.x--;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			myPlane2.x++;
		}
	}

	t2 = GetTickCount();
	//以下为第一类战机
	if (myPlane.isExist == true)
	{
		//等级一产生的子弹
		if (myPlane.level == 1)
		{
			if (t2 - t1 >= 100)
			{
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 26;
						myPlane_bullet[i].y = myPlane.y - 21;
						break;
					}
				}
				t1 = t2;
			}
		}

		//等级二产生的子弹
		if (myPlane.level == 2)
		{
			if (t2 - t1 >= 100)
			{
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 26;
						myPlane_bullet[i].y = myPlane.y - 21;
						break;
					}
				}
				for (int i = 0; i < 200; i++)
				{
					if (myPlane_smallBullet[i].isExist == false)
					{
						myPlane_smallBullet[i].isExist = true;
						myPlane_smallBullet[i].x = myPlane.x + 18;
						myPlane_smallBullet[i].y = myPlane.y - 11;
						break;
					}
				}
				for (int i = 0; i < 200; i++)
				{
					if (myPlane_smallBullet[i].isExist == false)
					{
						myPlane_smallBullet[i].isExist = true;
						myPlane_smallBullet[i].x = myPlane.x + 37;
						myPlane_smallBullet[i].y = myPlane.y - 11;
						break;
					}
				}
				t1 = t2;
			}
		}

		//等级三产生的子弹
		if (myPlane.level == 3)
		{
			if (t2 - t1 >= 100)
			{
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 26;
						myPlane_bullet[i].y = myPlane.y - 21;
						break;
					}
				}
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 6;
						myPlane_bullet[i].y = myPlane.y - 21;
						break;
					}
				}
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 45;
						myPlane_bullet[i].y = myPlane.y - 21;
						t1 = t2;
						break;
					}
				}
			}
		}

		//等级四产生的子弹
		if (myPlane.level >= 4)
		{
			if (t2 - t1 >= 100)
			{
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 26;
						myPlane_bullet[i].y = myPlane.y - 21;
						break;
					}
				}
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 6;
						myPlane_bullet[i].y = myPlane.y - 21;
						break;
					}
				}
				for (int i = 0; i < 100; i++)
				{
					if (myPlane_bullet[i].isExist == false)
					{
						myPlane_bullet[i].isExist = true;
						myPlane_bullet[i].x = myPlane.x + 45;
						myPlane_bullet[i].y = myPlane.y - 21;
						break;
					}
				}
				for (int i = 0; i < 200; i++)
				{
					if (myPlane_smallBullet[i].isExist == false)
					{
						myPlane_smallBullet[i].isExist = true;
						myPlane_smallBullet[i].x = myPlane.x + 18;
						myPlane_smallBullet[i].y = myPlane.y - 11;
						break;
					}
				}
				for (int i = 0; i < 200; i++)
				{
					if (myPlane_smallBullet[i].isExist == false)
					{
						myPlane_smallBullet[i].isExist = true;
						myPlane_smallBullet[i].x = myPlane.x + 37;
						myPlane_smallBullet[i].y = myPlane.y - 11;
						t1 = t2;
						break;
					}
				}
			}
		}
	}

	//以下为第二类战机
	if (myPlane1.isExist == true)
	{
		//等级一产生的子弹
		if (myPlane1.level == 1)
		{
			if (t2 - t1 >= 150)
			{
				for (int i = 0; i < 60; i++)
				{
					if (myPlane1_bullet1[i].isExist == false)
					{
						myPlane1_bullet1[i].isExist = true;
						myPlane1_bullet1[i].x = myPlane1.x + 2;
						myPlane1_bullet1[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isBigAttack[i] = true;
						}
						Boss1.isBigAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 60; i++)
				{
					if (myPlane1_bullet1[i].isExist == false)
					{
						myPlane1_bullet1[i].isExist = true;
						myPlane1_bullet1[i].x = myPlane1.x + 48;
						myPlane1_bullet1[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isBigAttack[i] = true;
						}
						Boss1.isBigAttack[i] = true;
						break;
					}
				}
				t1 = t2;
			}
		}

		//等级二产生的子弹
		if (myPlane1.level == 2)
		{
			if (t2 - t1 >= 150)
			{
				for (int i = 0; i < 60; i++)
				{
					if (myPlane1_bullet1[i].isExist == false)
					{
						myPlane1_bullet1[i].isExist = true;
						myPlane1_bullet1[i].x = myPlane1.x + 2;
						myPlane1_bullet1[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isBigAttack[i] = true;
						}
						Boss1.isBigAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 60; i++)
				{
					if (myPlane1_bullet1[i].isExist == false)
					{
						myPlane1_bullet1[i].isExist = true;
						myPlane1_bullet1[i].x = myPlane1.x + 48;
						myPlane1_bullet1[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isBigAttack[i] = true;
						}
						Boss1.isBigAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane1_bullet2[i].isExist == false)
					{
						myPlane1_bullet2[i].isExist = true;
						myPlane1_bullet2[i].x = myPlane1.x + 15;
						myPlane1_bullet2[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isLittleAttck[i] = true;
						}
						Boss1.isLittleAttck[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane1_bullet2[i].isExist == false)
					{
						myPlane1_bullet2[i].isExist = true;
						myPlane1_bullet2[i].x = myPlane1.x + 38;
						myPlane1_bullet2[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isLittleAttck[i] = true;
						}
						Boss1.isLittleAttck[i] = true;
						break;
					}
				}
				t1 = t2;
			}
		}

		//等级三产生的子弹
		if (myPlane1.level >= 3)
		{
			if (t2 - t1 >= 150)
			{
				for (int i = 0; i < 60; i++)
				{
					if (myPlane1_bullet1[i].isExist == false)
					{
						myPlane1_bullet1[i].isExist = true;
						myPlane1_bullet1[i].x = myPlane1.x + 2;
						myPlane1_bullet1[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isBigAttack[i] = true;
						}
						Boss1.isBigAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 60; i++)
				{
					if (myPlane1_bullet1[i].isExist == false)
					{
						myPlane1_bullet1[i].isExist = true;
						myPlane1_bullet1[i].x = myPlane1.x + 26;
						myPlane1_bullet1[i].y = myPlane1.y - 62;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isBigAttack[i] = true;
						}
						Boss1.isBigAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 60; i++)
				{
					if (myPlane1_bullet1[i].isExist == false)
					{
						myPlane1_bullet1[i].isExist = true;
						myPlane1_bullet1[i].x = myPlane1.x + 48;
						myPlane1_bullet1[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isBigAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isBigAttack[i] = true;
						}
						Boss1.isBigAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane1_bullet2[i].isExist == false)
					{
						myPlane1_bullet2[i].isExist = true;
						myPlane1_bullet2[i].x = myPlane1.x + 15;
						myPlane1_bullet2[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isLittleAttck[i] = true;
						}
						Boss1.isLittleAttck[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane1_bullet2[i].isExist == false)
					{
						myPlane1_bullet2[i].isExist = true;
						myPlane1_bullet2[i].x = myPlane1.x + 38;
						myPlane1_bullet2[i].y = myPlane1.y - 44;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isLittleAttck[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isLittleAttck[i] = true;
						}
						Boss1.isLittleAttck[i] = true;
						break;
					}
				}
				t1 = t2;
			}
		}
	}

	//以下为第三类战机，只发射普通子弹
	if (myPlane2.isExist == true)
	{
		//等级一产生的子弹
		if (myPlane2.level == 1)
		{
			if (t2 - t1 >= 300)
			{
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 0;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 30;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 36;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 30;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				t1 = t2;
			}
		}

		//等级二产生的子弹
		if (myPlane2.level == 2)
		{
			if (t2 - t1 >= 300)
			{
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 0;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 35;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 36;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 35;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				t1 = t2;
			}
		}

		//等级三产生的子弹
		if (myPlane2.level == 3)
		{
			if (t2 - t1 >= 200)
			{
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 0;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 30;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 36;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 30;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				t1 = t2;
			}
		}

		//等级四产生的子弹
		if (myPlane2.level >= 4)
		{
			if (t2 - t1 >= 200)
			{
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 0;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 40;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (myPlane2_bullet1[i].isExist == false)
					{
						myPlane2_bullet1[i].isExist = true;
						myPlane2_bullet1[i].x = myPlane2.x + 36;
						myPlane2_bullet1[i].y = myPlane2.y - 38;
						myPlane2_bullet1[i].attack = 40;
						for (int j = 0; j < 4; j++)
						{
							littleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy1[j].isThirdAttack[i] = true;
						}
						for (int j = 0; j < 2; j++)
						{
							middleEnemy2[j].isThirdAttack[i] = true;
						}
						Boss1.isThirdAttack[i] = true;
						break;
					}
				}
				t1 = t2;
			}
		}

	}

	Tb = GetTickCount();
	//一下为第三类战机，发射跟踪子弹
	if (myPlane2.isExist == true)
	{
		//等级一产生的子弹
		if (myPlane2.level == 1)
		{
			if (Tb - Ta >= 500)
			{
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x - 25;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = -10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 10;
						break;
					}
				}
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x + 60;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = 10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 10;
						break;
					}
				}
				Ta = Tb;
			}
		}

		//等级二产生的子弹
		if (myPlane2.level == 2)
		{
			if (Tb - Ta >= 500)
			{
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x - 25;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = -10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 12;
						break;
					}
				}
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x + 60;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = 10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 12;
						break;
					}
				}
				Ta = Tb;
			}
		}

		//等级三产生的子弹
		if (myPlane2.level == 3)
		{
			if (Tb - Ta >= 500)
			{
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x - 25;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = -10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 15;
						break;
					}
				}
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x + 60;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = 10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 15;
						break;
					}
				}
				Ta = Tb;
			}
		}

		//等级四产生的子弹
		if (myPlane2.level >= 4)
		{
			if (Tb - Ta >= 500)
			{
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x - 25;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = -10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 20;
						break;
					}
				}
				for (int i = 0; i < 10; i++)
				{
					if (track_bullet[i].isExist == false)
					{
						track_bullet[i].isExist = true;
						track_bullet[i].x = myPlane2.x + 60;
						track_bullet[i].y = myPlane2.y + 46;
						track_bullet[i].x_speed = 10;
						track_bullet[i].y_speed = 0;
						track_bullet[i].attack = 20;
						break;
					}
				}
				Ta = Tb;
			}
		}
	}

	//升级物体的移动
	for (int i = 0; i < 4; i++)
	{
		if (upgrading[i].isExist == true)
		{
			upgrading[i].y += upgrading[i].y_speed;
			upgrading[i].x += upgrading[i].x_speed;
		}
	}	

	//当升级的物体到达边界的时候，就反方向的移动
	for (int i = 0; i < 4; i++)
	{
		if (upgrading[i].isFall == false)
		{
			if (upgrading[i].y > HEIGHT - 63 || upgrading[i].y < 0)
			{
				upgrading[i].y_speed = -upgrading[i].y_speed;
			}
			if (upgrading[i].x < 0 || upgrading[i].x > WIDTH - 62)
			{
				upgrading[i].x_speed = -upgrading[i].x_speed;
			}
		}
		if (upgrading[i].isFall == true)
		{
			if (upgrading[i].y <= HEIGHT - 63 && upgrading[i].y >= 0 &&
				upgrading[i].x >= 0 && upgrading[i].x <= WIDTH - 62)
			{
				upgrading[i].isFall = false;
			}
		}
	}

	//如果升级被我的飞机碰到后，我的飞机升级，升级的物体消失
	for (int i = 0; i < 4; i++)
	{
		if (upgrading[i].isExist == true)
		{
			if (myPlane.isExist == true)
			{
				if (upgrading[i].x + 62 > myPlane.x &&
					upgrading[i].x < myPlane.x + 60 &&
					upgrading[i].y + 63 > myPlane.y &&
					upgrading[i].y < myPlane.y + 62)
				{
					upgrading[i].isExist = false;
					myPlane.level += 1;
				}
			}
			if (myPlane1.isExist == true)
			{
				if (upgrading[i].x + 62 > myPlane1.x &&
					upgrading[i].x < myPlane1.x + 60 &&
					upgrading[i].y + 63 > myPlane1.y &&
					upgrading[i].y < myPlane1.y + 62)
				{
					upgrading[i].isExist = false;
					myPlane1.level += 1;
				}
			}
			if (myPlane2.isExist == true)
			{
				if (upgrading[i].x + 62 > myPlane2.x &&
					upgrading[i].x < myPlane2.x + 60 &&
					upgrading[i].y + 63 > myPlane2.y &&
					upgrading[i].y < myPlane2.y + 62)
				{
					upgrading[i].isExist = false;
					myPlane2.level += 1;
				}
			}
		}
	}

	//大子弹的移动
	for (int i = 0; i < 100; i++)
	{
		//大子弹存在时，大子弹就会往上飞
		if (myPlane_bullet[i].isExist == true)
		{
			myPlane_bullet[i].y -= myPlane_bullet[i].speed;
		}

		//当大子弹飞出去时，大子弹便消失了
		if (myPlane_bullet[i].y <= 0)
		{
			myPlane_bullet[i].isExist = false;
		}
	}

	//小子弹的移动
	for (int i = 0; i < 200; i++)
	{
		//小子弹存在时，小子弹就会往上飞
		if (myPlane_smallBullet[i].isExist == true)
		{
			myPlane_smallBullet[i].y -= myPlane_smallBullet[i].speed;
		}

		//当小子弹飞出去时，小子弹便消失了
		if (myPlane_smallBullet[i].y <= 0)
		{
			myPlane_smallBullet[i].isExist = false;
		}
	}

	//第二类大子弹的移动
	for (int i = 0; i < 60; i++)
	{
		//大子弹存在时，大子弹就会往上飞
		if (myPlane1_bullet1[i].isExist == true)
		{
			myPlane1_bullet1[i].y -= myPlane1_bullet1[i].speed;
		}

		//当大子弹飞出去时，大子弹便消失了
		if (myPlane1_bullet1[i].y <= 0)
		{
			myPlane1_bullet1[i].isExist = false;
		}
	}

	//第二类小子弹的移动
	for (int i = 0; i < 30; i++)
	{
		//大子弹存在时，大子弹就会往上飞
		if (myPlane1_bullet2[i].isExist == true)
		{
			myPlane1_bullet2[i].y -= myPlane1_bullet2[i].speed;
		}

		//当大子弹飞出去时，大子弹便消失了
		if (myPlane1_bullet2[i].y <= 0)
		{
			myPlane1_bullet2[i].isExist = false;
		}
	}

	//第三类子弹的移动
	for (int i = 0; i < 30; i++)
	{
		//第三类子弹存在时，子弹就会往上飞
		if (myPlane2_bullet1[i].isExist == true)
		{
			myPlane2_bullet1[i].y -= myPlane2_bullet1[i].speed;
		}

		//当第三类子弹飞出去时，子弹便消失了
		if (myPlane2_bullet1[i].y <= 0)
		{
			myPlane2_bullet1[i].isExist = false;
		}
	}

	//跟踪子弹的移动
	if (myPlane2.isExist == true)
	{
		for (int i = 0; i < 10; i++)
		{
			if (track_bulletmove >= 10)
			{
				//当跟踪子弹存在时，跟踪子弹的移动
				if (track_bullet[i].isExist == true)
				{
					track_bullet[i].y += track_bullet[i].y_speed;
					track_bullet[i].x += track_bullet[i].x_speed;
				}

				//当跟踪子弹超出屏幕时，跟踪子弹消失
				if (track_bullet[i].y <= 0 ||
					track_bullet[i].x <= -25 ||
					track_bullet[i].x >= WIDTH)
				{
					track_bullet[i].isExist = false;
				}
				track_bulletmove = 0;
			}
			else
			{
				track_bulletmove++;
			}
		}
	}

	//跟踪子弹的跟踪效果
	if (myPlane2.isExist == true)
	{
		for (int i = 0; i < 10; i++)
		{
			int x_min = 0;
			int y_min = 0;
			int distance = 0;
			int min = 0;
			int count = -1;
			int w = 0;
			if (track_bullet[i].isExist == true)
			{
				if (littleEnemy1[0].isExist == true ||
					littleEnemy1[1].isExist == true ||
					littleEnemy1[2].isExist == true ||
					littleEnemy1[3].isExist == true ||
					middleEnemy1[0].isExist == true ||
					middleEnemy1[1].isExist == true ||
					middleEnemy2[0].isExist == true ||
					middleEnemy2[1].isExist == true ||
					Boss1.isExist == true)
				{
					//判断小敌机
					for (int j = 0; j < 4; j++)
					{
						if (littleEnemy1[j].isExist == true && w == 0)
						{
							x_min = (littleEnemy1[j].x + 46) - (track_bullet[i].x + 13);
							y_min = (littleEnemy1[j].y + 35) - (track_bullet[i].y + 15);
							distance = x_min * x_min + y_min * y_min;
							min = distance;
							count = j;
							w++;
						}
						else if (littleEnemy1[j].isExist == true && w != 0)
						{
							x_min = (littleEnemy1[j].x + 46) - (track_bullet[i].x + 13);
							y_min = (littleEnemy1[j].y + 35) - (track_bullet[i].y + 15);
							distance = x_min * x_min + y_min * y_min;
							if (min > distance)
							{
								min = distance;
								count = j;
							}
						}
					}

					//判断第一类中敌机
					for (int j = 0; j < 2; j++)
					{
						if (middleEnemy1[j].isExist == true && w == 0)
						{
							x_min = (middleEnemy1[j].x + 62) - (track_bullet[i].x + 13);
							y_min = (middleEnemy1[j].y + 81) - (track_bullet[i].y + 15);
							distance = x_min * x_min + y_min * y_min;
							min = distance;
							count = j+4;
							w++;
						}
						else if (middleEnemy1[j].isExist == true && w != 0)
						{
							x_min = (middleEnemy1[j].x + 62) - (track_bullet[i].x + 13);
							y_min = (middleEnemy1[j].y + 81) - (track_bullet[i].y + 15);
							distance = x_min * x_min + y_min * y_min;
							if (min > distance)
							{
								min = distance;
								count = j+4;
							}
						}
					}

					//判断第二类中敌机
					for (int j = 0; j < 2; j++)
					{
						if (middleEnemy2[j].isExist == true && w == 0)
						{
							x_min = (middleEnemy2[j].x + 60) - (track_bullet[i].x + 13);
							y_min = (middleEnemy2[j].y + 74) - (track_bullet[i].y + 15);
							distance = x_min * x_min + y_min * y_min;
							min = distance;
							count = j + 6;
							w++;
						}
						else if (middleEnemy2[j].isExist == true && w != 0)
						{
							x_min = (middleEnemy2[j].x + 60) - (track_bullet[i].x + 13);
							y_min = (middleEnemy2[j].y + 74) - (track_bullet[i].y + 15);
							distance = x_min * x_min + y_min * y_min;
							if (min > distance)
							{
								min = distance;
								count = j + 6;
							}
						}
					}

					//判断BOSS
					if (Boss1.isExist == true)
					{
						x_min = (Boss1.x + 110) - (track_bullet[i].x + 13);
						y_min = (Boss1.y + 74) - (track_bullet[i].y + 15);
						distance = x_min * x_min + y_min * y_min;
						min = distance;
						count = 8;
					}
				}
				if (count < 4 && count >= 0)
				{
					x_min = (littleEnemy1[count].x + 46) - (track_bullet[i].x + 13);
					y_min = (littleEnemy1[count].y + 35) - (track_bullet[i].y + 15);
				}
				else if (count >= 4 && count < 6)
				{
					x_min = (middleEnemy1[count - 4].x + 62) - (track_bullet[i].x + 13);
					y_min = (middleEnemy1[count - 4].y + 81) - (track_bullet[i].y + 15);
				}
				else if (count >= 6 && count < 8)
				{
					x_min = (middleEnemy2[count - 6].x + 60) - (track_bullet[i].x + 13);
					y_min = (middleEnemy2[count - 6].y + 74) - (track_bullet[i].y + 15);
				}
				else if (count == 8)
				{
					x_min = (Boss1.x + 110) - (track_bullet[i].x + 13);
					y_min = (Boss1.y + 74) - (track_bullet[i].y + 15);
				}

				if (count != -1)
				{
					a = atan2(double(y_min), double(x_min));
					track_bullet[i].x_speed = 15 * cos(a);
					track_bullet[i].y_speed = 15 * sin(a);
				}
				
			}
		}
	}

	//小敌机的产生	91 * 70
	t4 = GetTickCount();
	if (littleEnemy1_creation == true && Boss1.isExist == false)
	{
		if (t4 - t3 >= 3000)
		{
			//飞机均匀的分布
			for (int i = 0; i < 4; i++)
			{
				littleEnemy1[i].isExist = true;
				littleEnemy1[i].isStop = false;
				littleEnemy1[i].attack = true;
				littleEnemy1[i].HP = 100;
				littleEnemy1[i].y = -70;
				if (i == 0)
				{
					littleEnemy1[i].x = 18;
				}
				else if (i == 1)
				{
					littleEnemy1[i].x = 129;
				}
				else if (i == 2)
				{
					littleEnemy1[i].x = 300;
				}
				else if (i == 3)
				{
					littleEnemy1[i].x = 411;
				}
			}
			t3 = t4;
			littleEnemy1_creation = false;
		}
	}

	//间隔多久后小敌机才会再次产生
	if (t4 - t3 >= 15000)
	{
		littleEnemy1_creation = true;
	}

	//小敌机的移动
	for (int i = 0; i < 4; i++)
	{
		//小敌机存在时，自动往下落
		if (littleEnemy1[i].isExist == true && littleEnemy1[i].isStop == false)
		{
			littleEnemy1[i].y += littleEnemy1[i].speed;
			littleEnemy1[i].count = 0;
		}

		//当小敌机下落到200处时		当敌机停止运动的时候，敌机的攻击才会被激发
		if (littleEnemy1[i].y == 200)
		{
			littleEnemy1[i].isStop = true;
			littleEnemy1[i].attack = true;
			littleEnemy1[i].count++;
		}
		else
		{
			littleEnemy1[i].isStop = false;
			littleEnemy1[i].attack = false;
		}

		//当敌机停止运动开始的时候，记录时间t9
		if (littleEnemy1[i].count == 1)
		{
			t9 = GetTickCount();
		}

		//当t10 - t9 >=1500时，敌机开始运动
		t10 = GetTickCount();
		if (littleEnemy1[i].isStop == true && t10 - t9 == 3000)
		{
			littleEnemy1[i].y++;
		}

		//当敌机飞出去时，敌机便消失了
		if (littleEnemy1[i].y >= HEIGHT)
		{
			littleEnemy1[i].isExist = false;
		}
	}

	t6 = GetTickCount();
	//小敌机攻击，发射子弹
	if (littleEnemy1[0].attack == true || littleEnemy1[1].attack == true || littleEnemy1[2].attack == true || littleEnemy1[3].attack == true)
	{
		if (t6 - t5 >= 1600)
		{
			for (int i = 0; i < 4; i++)
			{
				if (littleEnemy1[i].isExist == true)
				{
					for (int j = 0; j < 20; j++)
					{
						if (littleEnemy_bullet1[j].isExist == false)
						{
							littleEnemy_bullet1[j].isExist = true;
							littleEnemy_bullet1[j].x = littleEnemy1[i].x + 30;
							littleEnemy_bullet1[j].y = littleEnemy1[i].y + 70;
							break;
						}
					}
				}
			}
			t5 = t6;
		}
	}

	//小敌机子弹的移动
	for (int i = 0; i < 20; i++)
	{
		if (littleEnemy_bullet1[i].isExist == true)
		{
			littleEnemy_bullet1[i].y++;
		}
	}

	//当小敌机的子弹超过了设定的高度，子弹消失
	for (int i = 0; i < 20; i++)
	{
		if (littleEnemy_bullet1[i].isExist == true)
		{
			if (littleEnemy_bullet1[i].y >= HEIGHT)
			{
				littleEnemy_bullet1[i].isExist = false;
			}
		}
	}

	//第一类中敌机的产生	123 * 161   119 * 147
	t12 = GetTickCount();
	if (middleEnemy1_creation1 == true && middleEnemy1_creation2 == true)
	{
		if (t12 - t11 >= 10000)
		{
			//飞机均匀的分布
			for (int i = 0; i < 2; i++)
			{
				middleEnemy1[i].isExist = true;
				middleEnemy1[i].isStop = false;
				middleEnemy1[i].attack = true;
				middleEnemy1[i].HP = 200;
				if (i == 0)
				{
					middleEnemy1[i].x = 70;
					middleEnemy1[i].y = -167;
				}
				else if (i == 1)
				{
					middleEnemy1[i].x = 327;
					middleEnemy1[i].y = -167;
				}
			}
			t11 = t12;
			middleEnemy1_creation1 = false;
		}
	}

	//第二类中敌机的产生
	if (middleEnemy1_creation1 == false && middleEnemy1_creation2 == true)
	{
		if (t12 - t11 >= 20000)
		{
			//飞机均匀的分布
			for (int i = 0; i < 2; i++)
			{
				middleEnemy2[i].isExist = true;
				middleEnemy2[i].isStop = false;
				middleEnemy2[i].attack = true;
				middleEnemy2[i].HP = 300;
				if (i == 0)
				{
					middleEnemy2[i].x = 70;
					middleEnemy2[i].y = -147;
				}
				else if (i == 1)
				{
					middleEnemy2[i].x = 331;
					middleEnemy2[i].y = -147;
				}
			}
			middleEnemy1_creation2 = false;
		}
	}

	//BOSS的产生
	if (middleEnemy1_creation1 == false && middleEnemy1_creation2 == false)
	{
		if (t12 - t11 >= 30000)
		{
			Boss1.collision = 50;
			Boss1.isExist = true;
			Boss1.isStop = false;
			Boss1.attack = true;
			Boss1.HP = 2500;
			Boss1.x = 150;
			Boss1.y = -174;
			Boss1.isMad = false;
			Boss1.one = true;
			Boss1.isFall = true;
			for (int j = 0; j < 60; j++)
			{
				Boss1.isBigAttack[j] = true;
			}
			for (int j = 0; j < 30; j++)
			{
				Boss1.isLittleAttck[j] = true;
				Boss1.isThirdAttack[j] = true;
			}
			middleEnemy1_creation1 = true;
		}
	}

	//BOSS无暴走
	if (Boss1.isExist == true && Boss1.one == true && Boss1.isMad == false)
	{
		Boss1.x_speed = 1;
		Boss1.y_speed = 1;
		Boss1.one = false;
		Boss1.level = 1;
	}

	//当Boss的血量小于一半
	if (Boss1.isExist == true && Boss1.HP <= 1250 && Boss1.isMad == false)
	{
		Boss1.isMad = true;
		Boss1.one = true;
	}

	//BOSS开始暴走
	if (Boss1.isExist == true && Boss1.one == true && Boss1.isMad == true)
	{
		Boss1.level = 2;
		Boss1.one = false;
		Boss1.x_speed *= 2;
	}

	//Boss暴走
	if (Boss1.isExist == true && Boss1.isMad == true)
	{
		if (t16 - t15 >= 1000)
		{
			for (int i = 0; i < 10; i++)
			{
				middleEnemy_bullet1[i].isExist = true;
				middleEnemy_bullet1[i].x = Boss1.x + 100;
				middleEnemy_bullet1[i].y = Boss1.y + 300;
				break;
			}
			t15 = t16;
		}
	}

	//BOSS的移动
	if (Boss1.isExist == true)
	{
		if (Boss1.isFall == true)
		{
			Boss1.y += 3;
			if (Boss1.y >= 100)
			{
				Boss1.isFall = false;
			}
		}
		if (Boss1.isFall == false)
		{
			if (Boss1.count == 5)
			{
				Boss1.x = Boss1.x_speed + Boss1.x;
				Boss1.y = Boss1.y_speed + Boss1.y;
				Boss1.count = 0;
			}
			Boss1.count++;
		}
	}

	//BOSS的移动范围
	if (Boss1.isExist == true && Boss1.one == false)
	{
		if (Boss1.x <0 || Boss1.x + 220>WIDTH)
		{
			Boss1.x_speed = -Boss1.x_speed;
		}
		if (Boss1.y < 0 || Boss1.y + 174>300)
		{
			Boss1.y_speed = -Boss1.y_speed;
		}
	}

	//Boss的子弹产生
	td = GetTickCount();
	if (Boss1.attack == true)
	{
		if (td - tc >= 500)
		{
			if (Boss1.isExist == true)
			{
				int w = 0;
				for (int j = 0; j < 100; j++)
				{
					if (Boss_bullet1[j].isExist == false && Boss_bullet2[j].isExist == false 
						&& Boss_bullet3[j].isExist == false)
					{
						Boss_bullet1[j].isExist = true;
						if (w == 0)
						{
							Boss_bullet1[j].x = Boss1.x + 27;
							Boss_bullet1[j].y = Boss1.y + 171;
							a = atan2(180.0, (rand() % WIDTH) - 1.0*WIDTH / 3);
							Boss_bullet1[j].vx = 15 * cos(a);
							Boss_bullet1[j].vy = 15 * sin(a);
						}
						else if (w == 1)
						{
							Boss_bullet1[j].x = Boss1.x + 52;
							Boss_bullet1[j].y = Boss1.y + 171;
							a = atan2(200.0, (rand() % WIDTH) - 1.0*WIDTH / 2);
							Boss_bullet1[j].vx = 15 * cos(a);
							Boss_bullet1[j].vy = 15 * sin(a);
						}
						else if (w == 2)
						{
							Boss_bullet1[j].x = Boss1.x + 72;
							Boss_bullet1[j].y = Boss1.y + 168;
							a = atan2(300.0, (rand() % WIDTH) - 1.0*WIDTH / 2);
							Boss_bullet1[j].vx = 15 * cos(a);
							Boss_bullet1[j].vy = 15 * sin(a);
						}
						else if (w == 3)
						{
							Boss_bullet1[j].x = Boss1.x + 137;
							Boss_bullet1[j].y = Boss1.y + 168;
							a = atan2(320.0, (rand() % WIDTH) - 1.0*WIDTH / 4);
							Boss_bullet1[j].vx = 15 * cos(a);
							Boss_bullet1[j].vy = 15 * sin(a);
						}
						else if (w == 4)
						{
							Boss_bullet1[j].x = Boss1.x + 165;
							Boss_bullet1[j].y = Boss1.y + 171;
							a = atan2(220.0, (rand() % WIDTH) - 1.0*WIDTH / 4);
							Boss_bullet1[j].vx = 15 * cos(a);
							Boss_bullet1[j].vy = 15 * sin(a);
						}
						else if (w == 5)
						{
							Boss_bullet1[j].x = Boss1.x + 195;
							Boss_bullet1[j].y = Boss1.y + 171;
							a = atan2(270.0, (rand() % WIDTH) - 1.0*WIDTH / 3);
							Boss_bullet1[j].vx = 15 * cos(a);
							Boss_bullet1[j].vy = 15 * sin(a);
							break;
						}
						w++;
					}
				}
			}
			tc = td;
		}
	}

	//Boss子弹的移动
	if (bullet_frame >= 20)
	{
		for (int i = 0; i < 100; i++)
		{
			if (Boss_bullet1[i].isExist == true)
			{
				Boss_bullet1[i].isExist = false;
				Boss_bullet2[i].isExist = true;
				Boss_bullet2[i].x = int(Boss_bullet1[i].vx) + Boss_bullet1[i].x;
				Boss_bullet2[i].y = int(Boss_bullet1[i].vy) + Boss_bullet1[i].y;
				Boss_bullet2[i].vx = Boss_bullet1[i].vx;
				Boss_bullet2[i].vy = Boss_bullet1[i].vy;
			}
			else if (Boss_bullet2[i].isExist == true)
			{
				Boss_bullet2[i].isExist = false;
				Boss_bullet3[i].isExist = true;
				Boss_bullet3[i].x = int(Boss_bullet2[i].vx) + Boss_bullet2[i].x;
				Boss_bullet3[i].y = int(Boss_bullet2[i].vy) + Boss_bullet2[i].y;
				Boss_bullet3[i].vx = Boss_bullet2[i].vx;
				Boss_bullet3[i].vy = Boss_bullet2[i].vy;
			}
			else if (Boss_bullet3[i].isExist == true)
			{
				Boss_bullet3[i].isExist = false;
				Boss_bullet1[i].isExist = true;
				Boss_bullet1[i].x = int(Boss_bullet3[i].vx) + Boss_bullet3[i].x;
				Boss_bullet1[i].y = int(Boss_bullet3[i].vy) + Boss_bullet3[i].y;
				Boss_bullet1[i].vx = Boss_bullet3[i].vx;
				Boss_bullet1[i].vy = Boss_bullet3[i].vy;
			}
		}
		bullet_frame = 0;
	}
	else
	{
		bullet_frame++;
	}

	//当boss的子弹超出了界面时消失
	for (int i = 0; i < 100; i++)
	{
		if (Boss_bullet1[i].isExist == true)
		{
			if (Boss_bullet1[i].x >= WIDTH || Boss_bullet1[i].x <= -20 ||
				Boss_bullet1[i].y >= HEIGHT)
			{
				Boss_bullet1[i].isExist = false;
			}
		}
		else if (Boss_bullet2[i].isExist == true)
		{
			if (Boss_bullet2[i].x >= WIDTH || Boss_bullet2[i].x <= -20 ||
				Boss_bullet2[i].y >= HEIGHT)
			{
				Boss_bullet2[i].isExist = false;
			}
		}
		else if (Boss_bullet3[i].isExist == true)
		{
			if (Boss_bullet3[i].x >= WIDTH || Boss_bullet3[i].x <= -20 ||
				Boss_bullet3[i].y >= HEIGHT)
			{
				Boss_bullet3[i].isExist = false;
			}
		}
	}

	//当Boss的子弹打中我的飞机
	for (int i = 0; i < 100; i++)
	{
		if (Boss_bullet1[i].isExist == true)
		{
			//我的第一辆飞机
			if (Boss_bullet1[i].x + 20 > myPlane.x &&
				Boss_bullet1[i].x < myPlane.x + 43 &&
				Boss_bullet1[i].y + 20 > myPlane.y &&
				Boss_bullet1[i].y < myPlane.y + 62)
			{
				if (myPlane.isExist == true)
				{
					Boss_bullet1[i].isExist = false;
					myPlane.HP -= Boss_bullet1[i].attack;
				}
			}

			//我的第二辆飞机
			if (Boss_bullet1[i].x + 20 > myPlane1.x &&
				Boss_bullet1[i].x < myPlane1.x + 43 &&
				Boss_bullet1[i].y + 20 > myPlane1.y &&
				Boss_bullet1[i].y < myPlane1.y + 62)
			{
				if (myPlane1.isExist == true)
				{
					Boss_bullet1[i].isExist = false;
					myPlane1.HP -= Boss_bullet1[i].attack;
				}
			}

			//我的第三辆飞机
			if (Boss_bullet1[i].x + 20 > myPlane2.x &&
				Boss_bullet1[i].x < myPlane2.x + 43 &&
				Boss_bullet1[i].y + 20 > myPlane2.y &&
				Boss_bullet1[i].y < myPlane2.y + 62)
			{
				if (myPlane2.isExist == true)
				{
					Boss_bullet1[i].isExist = false;
					myPlane2.HP -= Boss_bullet1[i].attack;
				}
			}
		}

		else if (Boss_bullet2[i].isExist == true)
		{
			//我的第一辆飞机
			if (Boss_bullet2[i].x + 20 > myPlane.x &&
				Boss_bullet2[i].x < myPlane.x + 43 &&
				Boss_bullet2[i].y + 20 > myPlane.y &&
				Boss_bullet2[i].y < myPlane.y + 62)
			{
				if (myPlane.isExist == true)
				{
					Boss_bullet2[i].isExist = false;
					myPlane.HP -= Boss_bullet2[i].attack;
				}
			}

			//我的第二辆飞机
			if (Boss_bullet2[i].x + 20 > myPlane1.x &&
				Boss_bullet2[i].x < myPlane1.x + 43 &&
				Boss_bullet2[i].y + 20 > myPlane1.y &&
				Boss_bullet2[i].y < myPlane1.y + 62)
			{
				if (myPlane1.isExist == true)
				{
					Boss_bullet2[i].isExist = false;
					myPlane1.HP -= Boss_bullet2[i].attack;
				}
			}

			//我的第三辆飞机
			if (Boss_bullet2[i].x + 20 > myPlane2.x &&
				Boss_bullet2[i].x < myPlane2.x + 43 &&
				Boss_bullet2[i].y + 20 > myPlane2.y &&
				Boss_bullet2[i].y < myPlane2.y + 62)
			{
				if (myPlane2.isExist == true)
				{
					Boss_bullet2[i].isExist = false;
					myPlane2.HP -= Boss_bullet2[i].attack;
				}
			}
		}

		else if (Boss_bullet3[i].isExist == true)
		{
			//我的第一辆飞机
			if (Boss_bullet3[i].x + 20 > myPlane.x &&
				Boss_bullet3[i].x < myPlane.x + 43 &&
				Boss_bullet3[i].y + 20 > myPlane.y &&
				Boss_bullet3[i].y < myPlane.y + 62)
			{
				if (myPlane.isExist == true)
				{
					Boss_bullet3[i].isExist = false;
					myPlane.HP -= Boss_bullet3[i].attack;
				}
			}

			//我的第二辆飞机
			if (Boss_bullet3[i].x + 20 > myPlane1.x &&
				Boss_bullet3[i].x < myPlane1.x + 43 &&
				Boss_bullet3[i].y + 20 > myPlane1.y &&
				Boss_bullet3[i].y < myPlane1.y + 62)
			{
				if (myPlane1.isExist == true)
				{
					Boss_bullet3[i].isExist = false;
					myPlane1.HP -= Boss_bullet3[i].attack;
				}
			}

			//我的第三辆飞机
			if (Boss_bullet3[i].x + 20 > myPlane2.x &&
				Boss_bullet3[i].x < myPlane2.x + 43 &&
				Boss_bullet3[i].y + 20 > myPlane2.y &&
				Boss_bullet3[i].y < myPlane2.y + 62)
			{
				if (myPlane2.isExist == true)
				{
					Boss_bullet3[i].isExist = false;
					myPlane2.HP -= Boss_bullet3[i].attack;
				}
			}
		}
	}

	//当我的子弹射中Boss时,Boss血量减少
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			if (Boss1.isExist == true)
			{
				if (myPlane_bullet[i].x + 9 > Boss1.x &&
					myPlane_bullet[i].x < Boss1.x + 220 &&
					myPlane_bullet[i].y + 21 > Boss1.y &&
					myPlane_bullet[i].y < Boss1.y + 174)
				{
					myPlane_bullet[i].isExist = false;
					Boss1.HP -= 10;
				}
			}
		}
	}

	//当小子弹与boss碰撞时，小子弹被摧毁，boss扣血
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			if (Boss1.isExist == true)
			{
				if (myPlane_smallBullet[i].x + 5 > Boss1.x &&
					myPlane_smallBullet[i].x < Boss1.x + 220 &&
					myPlane_smallBullet[i].y + 11 > Boss1.y &&
					myPlane_smallBullet[i].y < Boss1.y + 174)
				{
					Boss1.HP -= 5;
					myPlane_smallBullet[i].isExist = false;
				}
			}
		}
	}

	//当第二类飞机的大子弹与boss碰撞时，大子弹不会继续攻击boss，boss扣血
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			if (Boss1.isExist == true)
			{
				if (myPlane1_bullet1[i].x + 19 > Boss1.x &&
					myPlane1_bullet1[i].x < Boss1.x + 220 &&
					myPlane1_bullet1[i].y + 60 > Boss1.y &&
					myPlane1_bullet1[i].y < Boss1.y + 174 &&
					Boss1.isBigAttack[i] == true)
				{
					Boss1.HP -= myPlane1_bullet1[i].attack;
					Boss1.isBigAttack[i] = false;
				}
			}
		}
	}

	//当第二类飞机的小子弹与boss碰撞时，小子弹不会继续攻击boss，boss扣血
	for (int i = 0; i < 30; i++)
	{
		if (myPlane1_bullet2[i].isExist == true)
		{
			if (Boss1.isExist == true)
			{
				if (myPlane1_bullet2[i].x + 7 > Boss1.x &&
					myPlane1_bullet2[i].x < Boss1.x + 220 &&
					myPlane1_bullet2[i].y + 53 > Boss1.y &&
					myPlane1_bullet2[i].y < Boss1.y + 174 &&
					Boss1.isLittleAttck[i] == true)
				{
					Boss1.HP -= myPlane1_bullet1[i].attack;
					Boss1.isLittleAttck[i] = false;
				}
			}
		}
	}

	//当第三类飞机的子弹与第一类中敌机碰撞时，子弹不会继续攻击该机，中敌机扣血
	for (int i = 0; i < 30; i++)
	{
		if (myPlane2_bullet1[i].isExist == true)
		{
			if (Boss1.isExist == true)
			{
				if (myPlane2_bullet1[i].x + 24 > Boss1.x &&
					myPlane2_bullet1[i].x < Boss1.x + 220 &&
					myPlane2_bullet1[i].y + 78 > Boss1.y &&
					myPlane2_bullet1[i].y < Boss1.y + 174 &&
					Boss1.isThirdAttack[i] == true)
				{
					Boss1.HP -= myPlane2_bullet1[i].attack;
					Boss1.isThirdAttack[i] = false;
				}
			}
		}
	}

	//当跟踪子弹与第二类中敌机碰撞时，子弹被摧毁，中敌机扣血
	for (int i = 0; i < 10; i++)
	{
		if (track_bullet[i].isExist == true)
		{
			if (Boss1.isExist == true)
			{
				if (track_bullet[i].x + 25 > Boss1.x &&
					track_bullet[i].x < Boss1.x + 220 &&
					track_bullet[i].y + 29 > Boss1.y &&
					track_bullet[i].y < Boss1.y + 174)
				{
					Boss1.HP -= track_bullet[i].attack;
					track_bullet[i].isExist = false;
				}
			}
		}
	}

	//当Boss的HP小于0时，Boss死亡
	if (Boss1.HP <= 0)
	{
		Boss1.isExist = false;
		gameIsPlay = false;
		chooseIsPlay = true;
		bound = -3;
		chooseLevel++;
	}
	
	//第一类中敌机的移动
	for (int i = 0; i < 2; i++)
	{
		//中敌机存在时，自动往下落
		if (middleEnemy1[i].isExist == true && middleEnemy1[i].isStop == false)
		{
			middleEnemy1[i].y += middleEnemy1[i].speed;
			middleEnemy1[i].count = 0;
		}

		//当小敌机下落到100处时		当敌机停止运动的时候，敌机的攻击才会被激发
		if (middleEnemy1[i].y == 100)
		{
			middleEnemy1[i].isStop = true;
			middleEnemy1[i].attack = true;
			middleEnemy1[i].count++;
		}
		else
		{
			middleEnemy1[i].isStop = false;
			middleEnemy1[i].attack = false;
		}

		//当敌机停止运动开始的时候，记录时间t9
		if (middleEnemy1[i].count == 1)
		{
			t13 = GetTickCount();
		}

		//当t14 - t13 >=3000时，敌机开始运动
		t14 = GetTickCount();
		if (middleEnemy1[i].isStop == true && t14 - t13 == 3000)
		{
			middleEnemy1[i].y++;
		}

		//当敌机飞出去时，敌机便消失了
		if (middleEnemy1[i].y >= HEIGHT)
		{
			middleEnemy1[i].isExist = false;
		}
	}

	//第二类中敌机的移动
	for (int i = 0; i < 2; i++)
	{
		//中敌机存在时，自动往下落
		if (middleEnemy2[i].isExist == true && middleEnemy2[i].isStop == false)
		{
			middleEnemy2[i].y += middleEnemy2[i].speed;
			middleEnemy2[i].count = 0;
		}

		//当小敌机下落到100处时		当敌机停止运动的时候，敌机的攻击才会被激发
		if (middleEnemy2[i].y == 100)
		{
			middleEnemy2[i].isStop = true;
			middleEnemy2[i].attack = true;
			middleEnemy2[i].count++;
		}
		else
		{
			middleEnemy2[i].isStop = false;
			middleEnemy2[i].attack = false;
		}

		//当敌机停止运动开始的时候，记录时间t9
		if (middleEnemy2[i].count == 1)
		{
			t13 = GetTickCount();
		}

		//当t14 - t13 >=3000时，敌机开始运动
		t14 = GetTickCount();
		if (middleEnemy2[i].isStop == true && t14 - t13 == 3000)
		{
			middleEnemy2[i].y++;
		}

		//当敌机飞出去时，敌机便消失了
		if (middleEnemy2[i].y >= HEIGHT)
		{
			middleEnemy2[i].isExist = false;
		}
	}

	t16 = GetTickCount();
	//第一类中敌机攻击，发射子弹
	if (middleEnemy1[0].attack == true || middleEnemy1[1].attack == true)
	{
		if (t16 - t15 >= 1600)
		{
			for (int i = 0; i < 2; i++)
			{
				if (middleEnemy1[i].isExist == true)
				{
					int w = 0;
					for (int j = 0; j < 30; j++)
					{
						if (middleEnemy_bullet1[j].isExist == false)
						{
							middleEnemy_bullet1[j].isExist = true;
							if (w == 0)
							{
								middleEnemy_bullet1[j].x = middleEnemy1[i].x + 10;
								middleEnemy_bullet1[j].y = middleEnemy1[i].y + 126;
							}
							else if (w == 1)
							{
								middleEnemy_bullet1[j].x = middleEnemy1[i].x + 95;
								middleEnemy_bullet1[j].y = middleEnemy1[i].y + 126;
								break;
							}
							w++;
						}
					}
				}
			}
			t15 = t16;
		}
	}

	//第二类中敌机攻击，发射子弹
	if (middleEnemy2[0].attack == true || middleEnemy2[1].attack == true)
	{
		if (t16 - t15 >= 1600)
		{
			for (int i = 0; i < 2; i++)
			{
				if (middleEnemy2[i].isExist == true)
				{
					int w = 0;
					for (int j = 0; j < 20; j++)
					{
						if (middleEnemy_bullet1[j].isExist == false)
						{
							middleEnemy_bullet1[j].isExist = true;
							if (w == 0)
							{
								middleEnemy_bullet1[j].x = middleEnemy2[i].x + 30;
								middleEnemy_bullet1[j].y = middleEnemy2[i].y + 107;
							}
							else if (w == 1)
							{
								middleEnemy_bullet1[j].x = middleEnemy2[i].x + 72;
								middleEnemy_bullet1[j].y = middleEnemy2[i].y + 107;
								break;
							}
							w++;
						}
					}
				}
			}
			t15 = t16;
		}
	}

	//中敌机子弹的移动
	for (int i = 0; i < 30; i++)
	{
		if (middleEnemy_bullet1[i].isExist == true)
		{
			middleEnemy_bullet1[i].y++;
		}
	}

	//当中敌机的子弹超过了设定的高度，子弹消失
	for (int i = 0; i < 30; i++)
	{
		if (middleEnemy_bullet1[i].isExist == true)
		{
			if (middleEnemy_bullet1[i].y >= HEIGHT)
			{
				middleEnemy_bullet1[i].isExist = false;
			}
		}
	}

	//当大子弹与小敌机碰撞时，大子弹被摧毁，小敌机扣血
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			for (int j = 0; j < 4; j++)
			{
				if (littleEnemy1[j].isExist == true)
				{
					if (myPlane_bullet[i].x + 9 > littleEnemy1[j].x &&
						myPlane_bullet[i].x < littleEnemy1[j].x + 91 &&
						myPlane_bullet[i].y + 21 > littleEnemy1[j].y &&
						myPlane_bullet[i].y < littleEnemy1[j].y + 70)
					{
						myPlane_bullet[i].isExist = false;
						littleEnemy1[j].HP -= 10;
					}
				}
			}
		}
	}

	//当小子弹与小敌机碰撞时，小子弹被摧毁，小敌机扣血
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			for (int j = 0; j < 4; j++)
			{
				if (littleEnemy1[j].isExist == true)
				{
					if (myPlane_smallBullet[i].x + 5 > littleEnemy1[j].x &&
						myPlane_smallBullet[i].x < littleEnemy1[j].x + 91 &&
						myPlane_smallBullet[i].y + 11 > littleEnemy1[j].y &&
						myPlane_smallBullet[i].y < littleEnemy1[j].y + 70)
					{
						littleEnemy1[j].HP -= 5;
						myPlane_smallBullet[i].isExist = false;
					}
				}
			}
		}
	}

	//当大子弹与第一类中敌机碰撞时，大子弹被摧毁，中敌机扣血
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy1[j].isExist == true)
				{
					if (myPlane_bullet[i].x + 9 > middleEnemy1[j].x &&
						myPlane_bullet[i].x < middleEnemy1[j].x + 123 &&
						myPlane_bullet[i].y + 21 > middleEnemy1[j].y &&
						myPlane_bullet[i].y < middleEnemy1[j].y + 161)
					{
						myPlane_bullet[i].isExist = false;
						middleEnemy1[j].HP -= 10;
					}
				}
			}
		}
	}

	//当大子弹与第二类中敌机碰撞时，大子弹被摧毁，中敌机扣血
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy2[j].isExist == true)
				{
					if (myPlane_bullet[i].x + 9 > middleEnemy2[j].x &&
						myPlane_bullet[i].x < middleEnemy2[j].x + 119 &&
						myPlane_bullet[i].y + 21 > middleEnemy2[j].y &&
						myPlane_bullet[i].y < middleEnemy2[j].y + 147)
					{
						myPlane_bullet[i].isExist = false;
						middleEnemy2[j].HP -= 10;
					}
				}
			}
		}
	}

	//当小子弹与第一类中敌机碰撞时，小子弹被摧毁，中敌机扣血
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy1[j].isExist)
				{
					if (myPlane_smallBullet[i].x + 5 > middleEnemy1[j].x &&
						myPlane_smallBullet[i].x < middleEnemy1[j].x + 123 &&
						myPlane_smallBullet[i].y + 11 > middleEnemy1[j].y &&
						myPlane_smallBullet[i].y < middleEnemy1[j].y + 161)
					{
						middleEnemy1[j].HP -= 5;
						myPlane_smallBullet[i].isExist = false;
					}						
				}
			}
		}
	}

	//当小子弹与第二类中敌机碰撞时，小子弹被摧毁，中敌机扣血
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy2[j].isExist == true)
				{
					if (myPlane_smallBullet[i].x + 5 > middleEnemy2[j].x &&
						myPlane_smallBullet[i].x < middleEnemy2[j].x + 119 &&
						myPlane_smallBullet[i].y + 11 > middleEnemy2[j].y &&
						myPlane_smallBullet[i].y < middleEnemy2[j].y + 147)
					{
						middleEnemy2[j].HP -= 5;
						myPlane_smallBullet[i].isExist = false;
					}
				}
			}
		}
	}

	//当第二类飞机的大子弹与小敌机碰撞时，大子弹不会继续攻击该机，小敌机扣血
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			for (int j = 0; j < 4; j++)
			{
				if (littleEnemy1[j].isExist == true)
				{
					if (myPlane1_bullet1[i].x + 19 > littleEnemy1[j].x &&
						myPlane1_bullet1[i].x < littleEnemy1[j].x + 91 &&
						myPlane1_bullet1[i].y + 60 > littleEnemy1[j].y &&
						myPlane1_bullet1[i].y < littleEnemy1[j].y + 70 &&
						littleEnemy1[j].isBigAttack[i] == true)
					{
						littleEnemy1[j].HP -= myPlane1_bullet1[i].attack;
						littleEnemy1[j].isBigAttack[i] = false;
					}
				}
			}
		}
	}

	//当第二类飞机的小子弹与小敌机碰撞时，小子弹不会继续攻击该机，小敌机扣血
	for (int i = 0; i < 30; i++)
	{
		if (myPlane1_bullet2[i].isExist == true)
		{
			for (int j = 0; j < 4; j++)
			{
				if (littleEnemy1[j].isExist == true)
				{
					if (myPlane1_bullet2[i].x + 7 > littleEnemy1[j].x &&
						myPlane1_bullet2[i].x < littleEnemy1[j].x + 91 &&
						myPlane1_bullet2[i].y + 53 > littleEnemy1[j].y &&
						myPlane1_bullet2[i].y < littleEnemy1[j].y + 70 &&
						littleEnemy1[j].isLittleAttck[i] == true)
					{
						littleEnemy1[j].isLittleAttck[i] = false;
						littleEnemy1[j].HP -= myPlane1_bullet2[i].attack;
					}
				}
			}
		}
	}

	//当第二类飞机的大子弹与第一类中敌机碰撞时，大子弹不会继续攻击该机，中敌机扣血
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy1[j].isExist == true)
				{
					if (myPlane1_bullet1[i].x + 19 > middleEnemy1[j].x &&
						myPlane1_bullet1[i].x < middleEnemy1[j].x + 123 &&
						myPlane1_bullet1[i].y + 60 > middleEnemy1[j].y &&
						myPlane1_bullet1[i].y < middleEnemy1[j].y + 161 &&
						middleEnemy1[j].isBigAttack[i] == true)
					{
						middleEnemy1[j].HP -= myPlane1_bullet1[i].attack;
						middleEnemy1[j].isBigAttack[i] = false;
					}
				}
			}
		}
	}

	//当第二类飞机的大子弹与第二类中敌机碰撞时，大子弹不会继续攻击该机，中敌机扣血
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy2[j].isExist == true)
				{
					if (myPlane1_bullet1[i].x + 19 > middleEnemy2[j].x &&
						myPlane1_bullet1[i].x < middleEnemy2[j].x + 119 &&
						myPlane1_bullet1[i].y + 60 > middleEnemy2[j].y &&
						myPlane1_bullet1[i].y < middleEnemy2[j].y + 147 &&
						middleEnemy2[j].isBigAttack[i] == true)
					{
						middleEnemy2[j].HP -= myPlane1_bullet1[i].attack;
						middleEnemy2[j].isBigAttack[i] = false;
					}
				}
			}
		}
	}

	//当第二类飞机的小子弹与第一类中敌机碰撞时，小子弹不会继续攻击该机，中敌机扣血
	for (int i = 0; i < 30; i++)
	{
		if (myPlane1_bullet2[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy1[j].isExist == true)
				{
					if (myPlane1_bullet2[i].x + 7 > middleEnemy1[j].x &&
						myPlane1_bullet2[i].x < middleEnemy1[j].x + 123 &&
						myPlane1_bullet2[i].y + 53 > middleEnemy1[j].y &&
						myPlane1_bullet2[i].y < middleEnemy1[j].y + 161 &&
						middleEnemy1[j].isLittleAttck[i] == true)
					{
						middleEnemy1[j].HP -= myPlane1_bullet1[i].attack;
						middleEnemy1[j].isLittleAttck[i] = false;
					}
				}
			}
		}
	}

	//当第二类飞机的小子弹与第一类中敌机碰撞时，小子弹不会继续攻击该机，中敌机扣血
	for (int i = 0; i < 30; i++){
		if (myPlane1_bullet2[i].isExist == true){
			for (int j = 0; j < 2; j++){
				if (middleEnemy2[j].isExist == true){
					if (myPlane1_bullet2[i].x + 7 > middleEnemy2[j].x &&
						myPlane1_bullet2[i].x < middleEnemy2[j].x + 119 &&
						myPlane1_bullet2[i].y + 53 > middleEnemy2[j].y &&
						myPlane1_bullet2[i].y < middleEnemy2[j].y + 147 &&
						middleEnemy2[j].isLittleAttck[i] == true)
					{
						middleEnemy2[j].HP -= myPlane1_bullet1[i].attack;
						middleEnemy2[j].isLittleAttck[i] = false;
					}
				}
			}
		}
	}

	//当第三类飞机的子弹与小敌机碰撞时，小子弹不会继续攻击该机，小敌机扣血
	for (int i = 0; i < 30; i++)
	{
		if (myPlane2_bullet1[i].isExist == true)
		{
			for (int j = 0; j < 4; j++)
			{
				if (littleEnemy1[j].isExist == true)
				{
					if (myPlane2_bullet1[i].x + 24 > littleEnemy1[j].x &&
						myPlane2_bullet1[i].x < littleEnemy1[j].x + 91 &&
						myPlane2_bullet1[i].y + 78 > littleEnemy1[j].y &&
						myPlane2_bullet1[i].y < littleEnemy1[j].y + 70 &&
						littleEnemy1[j].isThirdAttack[i] == true)
					{
						littleEnemy1[j].isThirdAttack[i] = false;
						littleEnemy1[j].HP -= myPlane2_bullet1[i].attack;
					}
				}
			}
		}
	}

	//当第三类飞机的子弹与第一类中敌机碰撞时，子弹不会继续攻击该机，中敌机扣血
	for (int i = 0; i < 30; i++)
	{
		if (myPlane2_bullet1[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy1[j].isExist == true)
				{
					if (myPlane2_bullet1[i].x + 24 > middleEnemy1[j].x &&
						myPlane2_bullet1[i].x < middleEnemy1[j].x + 123 &&
						myPlane2_bullet1[i].y + 78 > middleEnemy1[j].y &&
						myPlane2_bullet1[i].y < middleEnemy1[j].y + 161 &&
						middleEnemy1[j].isThirdAttack[i] == true)
					{
						middleEnemy1[j].HP -= myPlane2_bullet1[i].attack;
						middleEnemy1[j].isThirdAttack[i] = false;
					}
				}
			}
		}
	}

	//当第三类飞机的小子弹与第二类中敌机碰撞时，子弹不会继续攻击该机，中敌机扣血
	for (int i = 0; i < 30; i++)
	{
		if (myPlane2_bullet1[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy2[j].isExist == true)
				{
					if (myPlane2_bullet1[i].x + 24 > middleEnemy2[j].x &&
						myPlane2_bullet1[i].x < middleEnemy2[j].x + 119 &&
						myPlane2_bullet1[i].y + 78 > middleEnemy2[j].y &&
						myPlane2_bullet1[i].y < middleEnemy2[j].y + 147 &&
						middleEnemy2[j].isThirdAttack[i] == true)
					{
						middleEnemy2[j].HP -= myPlane2_bullet1[i].attack;
						middleEnemy2[j].isThirdAttack[i] = false;
					}
				}
			}
		}
	}

	//当我的跟踪子弹与小敌机碰撞时，子弹消失，小敌机扣血
	for (int i = 0; i < 10; i++)
	{
		if (track_bullet[i].isExist == true)
		{
			for (int j = 0; j < 4; j++)
			{
				if (littleEnemy1[j].isExist == true)
				{
					if (track_bullet[i].x + 25 > littleEnemy1[j].x &&
						track_bullet[i].x < littleEnemy1[j].x + 91 &&
						track_bullet[i].y + 29 > littleEnemy1[j].y &&
						track_bullet[i].y < littleEnemy1[j].y + 70)
					{
						littleEnemy1[j].HP -= track_bullet[i].attack;
						track_bullet[i].isExist = false;
					}
				}
			}
		}
	}

	//当跟踪子弹与第一类中敌机碰撞时，子弹被摧毁，中敌机扣血
	for (int i = 0; i < 10; i++)
	{
		if (track_bullet[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy1[j].isExist == true)
				{
					if (track_bullet[i].x + 25 > middleEnemy1[j].x &&
						track_bullet[i].x < middleEnemy1[j].x + 123 &&
						track_bullet[i].y + 29 > middleEnemy1[j].y &&
						track_bullet[i].y < middleEnemy1[j].y + 161)
					{
						track_bullet[i].isExist = false;
						middleEnemy1[j].HP -= track_bullet[i].attack;
					}
				}
			}
		}
	}

	//当跟踪子弹与第二类中敌机碰撞时，子弹被摧毁，中敌机扣血
	for (int i = 0; i < 10; i++)
	{
		if (track_bullet[i].isExist == true)
		{
			for (int j = 0; j < 2; j++)
			{
				if (middleEnemy2[j].isExist == true)
				{
					if (track_bullet[i].x + 25 > middleEnemy2[j].x &&
						track_bullet[i].x < middleEnemy2[j].x + 119 &&
						track_bullet[i].y + 29 > middleEnemy2[j].y &&
						track_bullet[i].y < middleEnemy2[j].y + 147)
					{
						middleEnemy2[j].HP -= track_bullet[i].attack;
						track_bullet[i].isExist = false;
					}
				}
			}
		}
	}

	//当小敌机的HP<=0是时，小敌机被摧毁，升级物体概率出现
	for (int i = 0; i < 4; i++)
	{
		if (littleEnemy1[i].isExist == true)
		{
			if (littleEnemy1[i].HP <= 0)
			{
				if (rand() % 4 == 0)
				{
					//产生升级物体
					for (int j = 0; j < 4; j++)
					{
						if (upgrading[j].isExist == false)
						{
							upgrading[j].isExist = true;
							upgrading[j].x = littleEnemy1[i].x + 14;
							upgrading[j].y = littleEnemy1[i].y + 3;
							if (upgrading[j].y >= 0)
							{
								upgrading[j].x_speed = -1;
								upgrading[j].y_speed = -1;
								upgrading[j].isFall = false;
							}
							else if (upgrading[j].y < 0)
							{
								upgrading[j].x_speed = 1;
								upgrading[j].y_speed = 1;
								upgrading[j].isFall = true;
							}
							break;
						}
					}
				}
				littleEnemy1[i].isExist = false;
			}
		}
	}

	//当第一类中敌机被摧毁时，概率产生升级物体
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy1[i].isExist == true)
		{
			if (middleEnemy1[i].HP <= 0)
			{
				if (rand() % 3 == 0)
				{
					//产生升级物体
					for (int j = 0; j < 4; j++)
					{
						if (upgrading[j].isExist == false)
						{
							upgrading[j].isExist = true;
							upgrading[j].x = middleEnemy1[i].x + 30;
							upgrading[j].y = middleEnemy1[i].y + 49;
							if (upgrading[j].y >= 0)
							{
								upgrading[j].x_speed = -1;
								upgrading[j].y_speed = -1;
								upgrading[j].isFall = false;
							}
							else if (upgrading[j].y < 0)
							{
								upgrading[j].x_speed = 1;
								upgrading[j].y_speed = 1;
								upgrading[j].isFall = true;
							}
							break;
						}
					}					
				}
				middleEnemy1[i].isExist = false;
			}
		}
	}

	//当第二类中敌机被摧毁时，概率产生升级物体
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy2[i].isExist == true)
		{
			if (middleEnemy2[i].HP <= 0)
			{
				if (rand() % 3 == 0)
				{
					//产生升级物体
					for (int j = 0; j < 4; j++)
					{
						if (upgrading[j].isExist == false)
						{
							upgrading[j].isExist = true;
							upgrading[j].x = middleEnemy2[i].x + 28;
							upgrading[j].y = middleEnemy2[i].y + 42;
							if (upgrading[j].y >= 0)
							{
								upgrading[j].x_speed = -1;
								upgrading[j].y_speed = -1;
								upgrading[j].isFall = false;
							}
							else if (upgrading[j].y < 0)
							{
								upgrading[j].x_speed = 1;
								upgrading[j].y_speed = 1;
								upgrading[j].isFall = true;
							}
							break;
						}
					}
				}
				middleEnemy2[i].isExist = false;
			}
		}
	}

	//当小敌机发射出来的子弹和我们的飞机相碰撞时，我的飞机扣血
	for (int i = 0; i < 20; i++)
	{
		if (littleEnemy_bullet1[i].isExist == true)
		{
			//我的第一类飞机
			if (littleEnemy_bullet1[i].x + 12 > myPlane.x &&
				littleEnemy_bullet1[i].x < myPlane.x + 43 &&
				littleEnemy_bullet1[i].y + 75 > myPlane.y &&
				littleEnemy_bullet1[i].y < myPlane.y + 62)
			{
				if (myPlane.isExist == true)
				{
					littleEnemy_bullet1[i].isExist = false;
					myPlane.HP -= littleEnemy_bullet1[i].attack;
				}
			}

			//我的第二辆飞机
			if (littleEnemy_bullet1[i].x + 12 > myPlane1.x &&
				littleEnemy_bullet1[i].x < myPlane1.x + 43 &&
				littleEnemy_bullet1[i].y + 75 > myPlane1.y &&
				littleEnemy_bullet1[i].y < myPlane1.y + 62)
			{
				//我的飞机
				if (myPlane1.isExist == true)
				{
					littleEnemy_bullet1[i].isExist = false;
					myPlane1.HP -= littleEnemy_bullet1[i].attack;
				}
			}

			//我的第三辆飞机
			if (littleEnemy_bullet1[i].x + 12 > myPlane2.x &&
				littleEnemy_bullet1[i].x < myPlane2.x + 43 &&
				littleEnemy_bullet1[i].y + 75 > myPlane2.y &&
				littleEnemy_bullet1[i].y < myPlane2.y + 62)
			{
				//我的飞机
				if (myPlane2.isExist == true)
				{
					littleEnemy_bullet1[i].isExist = false;
					myPlane2.HP -= littleEnemy_bullet1[i].attack;
				}
			}
		}
	}

	//当中敌机发射出来的子弹和我们的飞机相碰撞时，我的飞机扣血
	for (int i = 0; i < 30; i++)
	{
		if (middleEnemy_bullet1[i].isExist == true)
		{
			//我的第一辆飞机
			if (middleEnemy_bullet1[i].x + 5 > myPlane.x &&
				middleEnemy_bullet1[i].x < myPlane.x + 43 &&
				middleEnemy_bullet1[i].y + 73 > myPlane.y &&
				middleEnemy_bullet1[i].y < myPlane.y + 62)
			{
				if (myPlane.isExist == true)
				{
					middleEnemy_bullet1[i].isExist = false;
					myPlane.HP -= middleEnemy_bullet1[i].attack;
				}
			}

			//我的第二辆飞机
			if (middleEnemy_bullet1[i].x + 5 > myPlane1.x &&
				middleEnemy_bullet1[i].x < myPlane1.x + 43 &&
				middleEnemy_bullet1[i].y + 73 > myPlane1.y &&
				middleEnemy_bullet1[i].y < myPlane1.y + 62)
			{
				if (myPlane1.isExist == true)
				{
					middleEnemy_bullet1[i].isExist = false;
					myPlane1.HP -= middleEnemy_bullet1[i].attack;
				}
			}

			//我的第三辆飞机
			if (middleEnemy_bullet1[i].x + 5 > myPlane2.x &&
				middleEnemy_bullet1[i].x < myPlane2.x + 43 &&
				middleEnemy_bullet1[i].y + 73 > myPlane2.y &&
				middleEnemy_bullet1[i].y < myPlane2.y + 62)
			{
				if (myPlane2.isExist == true)
				{
					middleEnemy_bullet1[i].isExist = false;
					myPlane2.HP -= middleEnemy_bullet1[i].attack;
				}
			}
		}
	}

	//当敌机与我发生碰撞时，我的飞机会扣血，敌机消失
	if (myPlane.isExist == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (littleEnemy1[i].isExist == true)
			{
				if (littleEnemy1[i].x + 91 > myPlane.x &&
					littleEnemy1[i].x < myPlane.x + 43 &&
					littleEnemy1[i].y + 70 > myPlane.y &&
					littleEnemy1[i].y < myPlane.y + 62)
				{
					myPlane.HP -= littleEnemy1[i].collision;
					littleEnemy1[i].isExist = false;
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (middleEnemy1[i].isExist == true)
			{
				if (middleEnemy1[i].x + 123 > myPlane.x &&
					middleEnemy1[i].x < myPlane.x + 43 &&
					middleEnemy1[i].y + 161 > myPlane.y &&
					middleEnemy1[i].y < myPlane.y + 62)
				{
					myPlane.HP -= middleEnemy1[i].collision;
					middleEnemy1[i].isExist = false;
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (middleEnemy2[i].isExist == true)
			{
				if (middleEnemy2[i].x + 123 > myPlane.x &&
					middleEnemy2[i].x < myPlane.x + 43 &&
					middleEnemy2[i].y + 161 > myPlane.y &&
					middleEnemy2[i].y < myPlane.y + 62)
				{
					myPlane.HP -= middleEnemy2[i].collision;
					middleEnemy2[i].isExist = false;
				}
			}
		}
	}

	//当小敌机与我发生碰撞时，我的飞机会扣血，敌机小时
	if (myPlane1.isExist == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (littleEnemy1[i].isExist == true)
			{
				if (littleEnemy1[i].x + 91 > myPlane1.x &&
					littleEnemy1[i].x < myPlane1.x + 43 &&
					littleEnemy1[i].y + 70 > myPlane1.y &&
					littleEnemy1[i].y < myPlane1.y + 62)
				{
					myPlane1.HP -= littleEnemy1[i].collision;
					littleEnemy1[i].isExist = false;
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (middleEnemy1[i].isExist == true)
			{
				if (middleEnemy1[i].x + 123 > myPlane1.x &&
					middleEnemy1[i].x < myPlane1.x + 43 &&
					middleEnemy1[i].y + 161 > myPlane1.y &&
					middleEnemy1[i].y < myPlane1.y + 62)
				{
					myPlane1.HP -= middleEnemy1[i].collision;
					middleEnemy1[i].isExist = false;
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (middleEnemy2[i].isExist == true)
			{
				if (middleEnemy2[i].x + 123 > myPlane1.x &&
					middleEnemy2[i].x < myPlane1.x + 43 &&
					middleEnemy2[i].y + 161 > myPlane1.y &&
					middleEnemy2[i].y < myPlane1.y + 62)
				{
					myPlane1.HP -= middleEnemy2[i].collision;
					middleEnemy2[i].isExist = false;
				}
			}
		}
	}

	//当小敌机与我发生碰撞时，我的飞机会扣血，敌机小时
	if (myPlane2.isExist == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (littleEnemy1[i].isExist == true)
			{
				if (littleEnemy1[i].x + 91 > myPlane2.x &&
					littleEnemy1[i].x < myPlane2.x + 43 &&
					littleEnemy1[i].y + 70 > myPlane2.y &&
					littleEnemy1[i].y < myPlane2.y + 62)
				{
					myPlane2.HP -= littleEnemy1[i].collision;
					littleEnemy1[i].isExist = false;
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (middleEnemy1[i].isExist == true)
			{
				if (middleEnemy1[i].x + 123 > myPlane2.x &&
					middleEnemy1[i].x < myPlane2.x + 43 &&
					middleEnemy1[i].y + 161 > myPlane2.y &&
					middleEnemy1[i].y < myPlane2.y + 62)
				{
					myPlane2.HP -= middleEnemy1[i].collision;
					middleEnemy1[i].isExist = false;
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (middleEnemy2[i].isExist == true)
			{
				if (middleEnemy2[i].x + 123 > myPlane2.x &&
					middleEnemy2[i].x < myPlane2.x + 43 &&
					middleEnemy2[i].y + 161 > myPlane2.y &&
					middleEnemy2[i].y < myPlane2.y + 62)
				{
					myPlane2.HP -= middleEnemy2[i].collision;
					middleEnemy2[i].isExist = false;
				}
			}
		}
	}

	//当自己的飞机HP<=0时，游戏失败，回到选择关卡
	if (myPlane.isExist == true)
	{
		if (myPlane.HP <= 0)
		{
			myPlane.isExist = false;
		}
	}
	if (myPlane1.isExist == true)
	{
		if (myPlane1.HP <= 0)
		{
			myPlane1.isExist = false;
		}
	}
	if (myPlane2.isExist == true)
	{
		if (myPlane2.HP <= 0)
		{
			myPlane2.isExist = false;
		}
	}
	if (myPlane.isExist == false && myPlane1.isExist == false && myPlane2.isExist == false)
	{
		bound = -3;
		gameIsPlay = false;
		chooseIsPlay = true;
	}
}

int main()
{
	initgraph(WIDTH, HEIGHT); //画布的大小

	while (1)
	{
		//游戏主界面
		while (bound == -2)
		{
			MainBeginInit();
			while (mainBeginIsPlay == true)
			{
				MainBeginDraw();
			}
			mciSendString(_T("pause resource/music/begin_music.mp3"), 0, 0, 0);
		}

		//选择关卡界面
		while (bound == -3)
		{
			ChooseInit();
			while (chooseIsPlay == true)
			{
				ChooseDraw();
				ChooseUpdate();
			}
			mciSendString(_T("pause resource/music/begin_music.mp3"), 0, 0, 0);
		}

		//游戏飞机选择界面
		while (bound == -1)
		{
			BeginInit();
			while (beginIsPlay == true)
			{
				BeginDraw();
				BeginUpdate();
			}
			mciSendString(_T("pause resource/music/begin_music.mp3"), 0, 0, 0);
		}

		//游戏界面
		while (bound == 0)
		{
			GameInit();					//初始化数据
			while (gameIsPlay == true)
			{
				GameDraw();				//不断绘画图片
				GameUpdate();			//不断更新数据
				Sleep(1);
			}
			mciSendString(_T("pause resource/music/level1.mp3"), 0, 0, 0);
		}
	}
}

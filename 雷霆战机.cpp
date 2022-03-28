/*****************************************
* �����ɻ��Ĳ���
* ��BOSS�Ĳ���
* �ҷ��ɻ�������
* �������˵�����
* ���˵Ľ���
*****************************************/

#include <stdio.h>
#include <easyx.h>
#include <mmsystem.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")

//1.��������
#define WIDTH 520
#define HEIGHT 800
IMAGE		background1[6];
IMAGE       background2[6];			//���ñ���
struct Background
{
	int x = 0, y = 0;		//ͼƬ��λ��
} back1[6], back2[6];		
bool		isPlay = true;			//�ж��Ƿ��ڲ�������
int			bound = -2;				//��Ϸ�ؿ�
bool		beginIsPlay = true;		//��Ϸ�������Ƿ����
IMAGE mainBack;					//������
int frame = 0;						//������ı仯
int frame_speed = 0;				//�仯���ٶ�
bool mainBeginIsPlay = true;		//��Ϸ�������Ƿ����
IMAGE		chooseBackGround[5];	//ѡ����汳��
int chooseLevel = 1;				//ѡ�����ؿ�
int gameLevel = 0;					//ѡ���ĸ��ؿ�
bool chooseIsPlay = true;			//ѡ������Ƿ�����
bool gameIsPlay = true;				//�ж���Ϸ�Ƿ����

//������Ϸѡ�������Ҫ�Ķ���
struct Square
{
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
} square1, square2, square3;

//�Լ��ķɻ�
struct MyPlane 
{
	int x=0, y=0;				//�Լ��ɻ�������
	IMAGE mimg[2];				//�ɻ���ͼƬ  60 * 62
	int HP = 0;					//�ɻ���Ѫ��
	bool isExist =true;			//�ɻ��Ƿ���
	int level = 0;				//�ȼ�
} myPlane, myPlane1, myPlane2;

//����
struct Upgrading
{
	int x = 0, y = 0;			//���������λ��
	IMAGE uimg[2];				//���������ͼƬ
	bool isExist = false;		//�Ƿ��������������
	int x_speed = 0, y_speed = 0;	//���е��ٶ�
	bool isFall = true;			//�Ƿ�����
} upgrading[4];

//���ӵ�
struct PlayerBullet
{
	int x = 0, y = 0;			//�Լ����ӵ�������
	IMAGE bimg[2];				//���ӵ���ͼƬ  9 * 21
	bool isExist = true;		//���ӵ��Ƿ����
	int speed = 0;				//���ӵ��������ٶ�
	int attack = 0;				//ÿ�����ӵ��Ե�����ɵ��˺�
} myPlane_bullet[100];			//���ӵ�������
unsigned t1, t2;

//С�ӵ�
struct SmallPlayerBullet
{
	int x = 0, y = 0;			//�Լ�С�ӵ�������
	IMAGE sbimg[2];				//С�ӵ���ͼƬ 5 * 11
	bool isExist = true;		//С�ӵ��Ƿ����
	int speed = 0;				//С�ӵ��������ٶ�
	int attack = 0;				//ÿ��С�ӵ��Ե�����ɵ��˺�
} myPlane_smallBullet[200];		//С�ӵ�������

//�ڶ���ɻ��Ĵ��ӵ�
struct Throughout1
{
	int x = 0, y = 0;			//�Լ��ڶ���ɻ����ӵ�
	IMAGE sbimg[2];				//�ӵ���ͼƬ
	bool isExist = true;		//�ӵ��Ƿ����
	int speed = 0;				//�ӵ��������ٶ�
	int attack = 0;				//ÿ���ӵ��Ե�����ɵ��˺�
} myPlane1_bullet1[60];			//�ӵ�������

//�ڶ���ɻ���С�ӵ�
struct Throughout2
{
	int x = 0, y = 0;			//�Լ��ڶ���ɻ����ӵ�
	IMAGE sbimg[2];				//�ӵ���ͼƬ
	bool isExist = true;		//�ӵ��Ƿ����
	int speed = 0;				//�ӵ��������ٶ�
	int attack = 0;				//ÿ���ӵ��Ե�����ɵ��˺�
} myPlane1_bullet2[30];			//�ӵ�������

//������ɻ��Ĵ��ӵ�'
struct Throughout3 
{
	int x = 0, y = 0;			//�Լ��������ɻ����ӵ�
	IMAGE sbimg[2];				//�ӵ���ͼƬ
	bool isExist = true;		//�ӵ��Ƿ����
	int speed = 0;				//�ӵ��������ٶ�
	int attack = 0;				//ÿ���ӵ��Ե�����ɵ��˺�
} myPlane2_bullet1[30];			//�ӵ�������

//������ɻ��ĸ����ӵ�
struct Track
{
	int x = 0, y = 0;			//�����ӵ���λ��
	IMAGE sbimg[2];				//�ӵ���ͼƬ
	bool isExist = true;		//�ӵ��Ƿ����
	int x_speed = 0;
	int y_speed = 0;			//�ӵ����ٶ�
	int attack = 0;				//�ӵ����˺�
}track_bullet[10];				//�ӵ�������
unsigned Ta, Tb;				//ʲôʱ��������ӵ�
int track_bulletmove = 0;		//ʲôʱ���ƶ�

//С�л�
struct LittleEnemy
{
	int x=0, y=0;				//С�л�������
	IMAGE eimg[2];				//С�л���ͼƬ	91 * 70
	int HP = 0;					//С�л���Ѫ��
	bool isExist = true;		//С�л��Ƿ���
	int speed = 0;				//С�л����ٶ�
	int collision = 0;			//С�л����Լ��ɻ�ײ����ʱ��۳���Ѫ��
	bool isStop = true;			//С�л��Ƿ�ֹͣ
	bool attack = true;			//С�л��Ƿ����
	int count = 0;				//��¼�����˶��ٴ�
	bool isBigAttack[60];		//�ڶ�����ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
	bool isLittleAttck[30];		//�ڶ���С�ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
	bool isThirdAttack[30];		//������С�ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
} littleEnemy1[4];				//С�л�������
bool littleEnemy1_creation = true;		//С�л��Ƿ����
unsigned t3, t4, t5, t6 ,t9, t10;		//����t3 t4�Ǽ�¼�ɻ��Ƿ����  t5 t6�Ǽ�¼�л��Ƿ����ӵ�  t9 t10 �Ǽ�¼�л��������ӵ�������

//�ел�
struct MiddleEnemy
{
	int x = 0, y = 0;				//�ел�������
	IMAGE mimg[2];					//�ел���ͼƬ	91 * 70
	int HP = 0;						//�ел���Ѫ��
	bool isExist = true;			//�ел��Ƿ���
	int speed = 0;					//�ел����ٶ�
	int collision = 0;				//�ел����Լ��ɻ�ײ����ʱ��۳���Ѫ��
	bool isStop = true;				//�ел��Ƿ�ֹͣ
	bool attack = true;				//С�л��Ƿ����
	int count = 0;					//��¼�����˶��ٴ�
	bool isBigAttack[60];		//�ڶ�����ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
	bool isLittleAttck[30];		//�ڶ���С�ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
	bool isThirdAttack[30];		//������С�ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
} middleEnemy1[2], middleEnemy2[2];					//�ел�������
bool middleEnemy1_creation1 = true;		//�ел��Ƿ����
bool middleEnemy1_creation2 = true;		//�ел��Ƿ����
unsigned t11, t12, t13, t14, t15, t16;		//����t11 t12�Ǽ�¼�ɻ��Ƿ����  t13 t14�Ǽ�¼�л��Ƿ����ӵ�  t15 t16 �Ǽ�¼�л��������ӵ�������

//С�л����ӵ�
struct LittleEnemy_Bullet
{
	int x = 0, y = 0;			//С�л��ӵ�������
	IMAGE ebimg[2];				//С�л��ӵ���ͼƬ 30 * 75
	int attack = 0;			//С�л��ӵ��Էɻ���ɵ��˺�
	int speed = 0;				//С�л����ٶ�
	bool isExist = true;		//С�л��Ƿ����
} littleEnemy_bullet1[20];		//С�л��ӵ�������

//�ел��ӵ�
struct MiddleEnemy_Bullet
{
	int x = 0, y = 0;			//�ел��ӵ�������
	IMAGE mbimg[2];				//�ел��ӵ���ͼƬ		17*73
	int attack = 0;				//�ел��ӵ���ɵ��˺�
	int speed = 0;				//�ел��ӵ����ٶ�
	bool isExist = true;		//�ел��ӵ��Ƿ����
} middleEnemy_bullet1[30];		//�ел��ӵ�������

//BOSS������ӵ�
unsigned tc, td, te, tf;
int bullet_frame = 0;		//�����ӵ�ת��
double a = 0.0;		//����
struct BOSS_Bullet
{
	int x = 0, y = 0;			//�Լ�С�ӵ�������
	double vx = 0.0;
	double vy = 0.0;			//С�ӵ����ٶ�
	IMAGE sbimg[2];				//С�ӵ���ͼƬ 5 * 11
	bool isExist = true;		//С�ӵ��Ƿ����
	int speed = 0;				//С�ӵ��������ٶ�
	int attack = 0;				//ÿ��С�ӵ��Ե�����ɵ��˺�
}Boss_bullet1[100], Boss_bullet2[100], Boss_bullet3[100];				//С�л�������

//BOSS
struct BOSS
{
	int x = 0, y = 0;			//BOSS������
	IMAGE eimg[2];				//BOSS��ͼƬ	91 * 70
	int HP = 0;					//BOSS��Ѫ��
	bool isExist = true;		//BOSS�Ƿ���
	int x_speed = 0;			//BOSS���ٶ�
	int y_speed = 0;			//BOSS���ٶ�
	int collision = 0;			//BOSS���Լ��ɻ�ײ����ʱ��۳���Ѫ��
	bool isStop = true;			//BOSS�Ƿ�ֹͣ
	bool attack = true;			//BOSS�Ƿ����
	bool isMad = false;			//BOSS�Ƿ���
	bool one = false;			//����ʱֻ����һ���ٶȵı任
	int level = 0;				//Boss�ĵȼ�
	bool isFall = false;		//�Ƿ�����
	int count = 0;				//ÿ������ƶ�һ��
	bool isBigAttack[60];		//�ڶ�����ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
	bool isLittleAttck[30];		//�ڶ���С�ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
	bool isThirdAttack[30];		//������С�ӵ��ᴩʱ���ӵ�������ʧ�������ܶ�������˺�
} Boss1;

//��Ϸ������
void MainBeginInit()
{
	//����ͼƬ
	loadimage(&mainBack, _T("resource/scene/����ս��.jpg"));

	//���ű�������
	mciSendString(_T("open resource/music/begin_music.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/begin_music.mp3 repeat"), 0, 0, 0);
}

//��Ϸ���������
void MainBeginDraw()
{
	putimage(0, 0, &mainBack);
	ExMessage m;        //  ���������Ϣ

	m = getmessage();
	if (m.message == WM_LBUTTONDOWN)
	{
		mainBeginIsPlay = false;
		bound = -3;
		chooseIsPlay = true;
	}
}

//ѡ��ؿ�����
void ChooseInit()
{
	//����ͼƬ
	loadimage(&chooseBackGround[0], _T("resource/scene/game1.jpg"));
	loadimage(&chooseBackGround[1], _T("resource/scene/game2.jpg"));
	loadimage(&chooseBackGround[2], _T("resource/scene/game3.jpg"));
	loadimage(&chooseBackGround[3], _T("resource/scene/game4.jpg"));
	loadimage(&chooseBackGround[4], _T("resource/scene/game5.jpg"));

	//���ű�������
	mciSendString(_T("open resource/music/begin_music.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/begin_music.mp3 repeat"), 0, 0, 0);
}

//ѡ��ؿ����
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

//ѡ��ؿ����ݸ���
void ChooseUpdate()
{
	ExMessage m;        //  ���������Ϣ
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

//��Ϸѡ��ɻ������ʼ��
void BeginInit()
{
	//���ر���ͼ
	loadimage(&background1[0], _T("resource/scene/bg6.jpg"),520,800);
	loadimage(&background2[0], _T("resource/scene/bg6.jpg"),520,800);
	back1[0].x = back2[0].x = 0;
	back1[0].y = 0;
	back2[0].y = HEIGHT;

	//��������
	mciSendString(_T("open resource/music/begin_music.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/begin_music.mp3 repeat"), 0, 0, 0);

	//�����Լ��ķɻ�
	loadimage(&myPlane.mimg[0], _T("resource/newPlayer/uiPlane0.jpg"));
	loadimage(&myPlane.mimg[1], _T("resource/newPlayer/uiPlane1.jpg"));
	myPlane.x = 110;
	myPlane.y = 459;

	//����������1
	square1.x1 = 90;
	square1.x2 = 190;
	square1.y1 = 440;
	square1.y2 = 540;

	//�����Լ��ķɻ�1
	loadimage(&myPlane1.mimg[0], _T("resource/newPlayer/myPlane1(0).jpg"));
	loadimage(&myPlane1.mimg[1], _T("resource/newPlayer/myPlane1(1).jpg"));
	myPlane1.x = 230;
	myPlane1.y = 459;

	//����������2
	square2.x1 = 210;
	square2.x2 = 310;
	square2.y1 = 440;
	square2.y2 = 540;

	//�����Լ��ķɻ�2
	loadimage(&myPlane2.mimg[0], _T("resource/newPlayer/myPlane2(0).jpg"));
	loadimage(&myPlane2.mimg[1], _T("resource/newPlayer/myPlane2(1).jpg"));
	myPlane2.x = 350;
	myPlane2.y = 459;

	//����������3
	square3.x1 = 330;
	square3.x2 = 430;
	square3.y1 = 440;
	square3.y2 = 540;

	//���ش��ӵ�
	for (int i = 0; i < 100; i++)
	{
		myPlane_bullet[i].speed = 2;
		myPlane_bullet[i].isExist = false;
		loadimage(&myPlane_bullet[i].bimg[0], _T("resource/newPlayer/bullet0.jpg"));
		loadimage(&myPlane_bullet[i].bimg[1], _T("resource/newPlayer/bullet1.jpg"));
	}
	t1 = GetTickCount();

	//����С�ӵ�
	for (int i = 0; i < 200; i++)
	{
		myPlane_smallBullet[i].speed = 2;
		myPlane_smallBullet[i].isExist = false;
		loadimage(&myPlane_smallBullet[i].sbimg[0], _T("resource/newPlayer/bullet2.jpg"));
		loadimage(&myPlane_smallBullet[i].sbimg[1], _T("resource/newPlayer/bullet3.jpg"));
	}

	//���صڶ���ɻ��Ĵ��ӵ�
	for (int i = 0; i < 60; i++)
	{
		myPlane1_bullet1[i].speed = 2;
		myPlane1_bullet1[i].isExist = false;
		loadimage(&myPlane1_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(2).jpg"));
		loadimage(&myPlane1_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(3).jpg"));
		myPlane1_bullet1[i].attack = 8;
	}

	//���صڶ���ɻ���С�ӵ�
	for (int i = 0; i < 30; i++)
	{
		myPlane1_bullet2[i].speed = 2;
		myPlane1_bullet2[i].isExist = false;
		loadimage(&myPlane1_bullet2[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(0).jpg"));
		loadimage(&myPlane1_bullet2[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(1).jpg"));
		myPlane1_bullet2[i].attack = 4;
	}

	//���ص�����ɻ��Ĵ��ӵ�
	for (int i = 0; i < 30; i++)
	{
		myPlane2_bullet1[i].speed = 2;
		myPlane2_bullet1[i].isExist = false;
		loadimage(&myPlane2_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane2_bullet(0).jpg"));
		loadimage(&myPlane2_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane2_bullet(1).jpg"));
	}
}

//��Ϸѡ��ɻ��������
void BeginDraw()
{
	BeginBatchDraw();

	//���Ʊ���
	putimage(0, back1[0].y, &background1[0]);
	putimage(back2[0].x, back2[0].y, &background2[0]);

	//�����Լ��ķɻ�
	putimage(myPlane.x, myPlane.y, &myPlane.mimg[0], SRCPAINT);
	putimage(myPlane.x, myPlane.y, &myPlane.mimg[1], SRCAND);

	//�����Լ��ķɻ�1
	putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[0], SRCPAINT);
	putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[1], SRCAND);

	//�����Լ��ķɻ�2
	putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[0], SRCPAINT);
	putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[1], SRCAND);

	//���Ʒɻ��߿�
	setlinecolor(YELLOW);
	rectangle(square1.x1, square1.y1, square1.x2, square1.y2);
	rectangle(square2.x1, square2.y1, square2.x2, square2.y2);
	rectangle(square3.x1, square3.y1, square3.x2, square3.y2);

	//���Ʊ���
	wchar_t str1[100] = L"Thunder Fighter";
	settextcolor(RGB(100,100,255));
	setbkmode(TRANSPARENT);
	settextstyle(30, 25, _T("FW_BLACK"));
	outtextxy(75, 50, str1);

	//������Ļ
	wchar_t str[100] = L"Please choose one plane you want to fire......";
	settextcolor(GREEN);
	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("FW_BLACK"));
	outtextxy(100, 590, str);

	//������Ļ
	wchar_t str2[100] = L"You can click 1 and choose first Plane to fire";
	settextcolor(RED);
	outtextxy(100, 610, str2);

	wchar_t str3[100] = L"You can click 2 and choose second Plane to fire";
	settextcolor(LIGHTCYAN);
	outtextxy(100, 630, str3);

	wchar_t str4[100] = L"You can click 3 and choose third Plane to fire";
	settextcolor(LIGHTMAGENTA);
	outtextxy(100, 650, str4);

	//���ƴ��ӵ�
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[0], SRCPAINT);
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[1], SRCAND);
		}
	}

	//����С�ӵ�
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[0], SRCPAINT);
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[1], SRCAND);
		}
	}

	//���Ƶڶ���ɻ����ӵ�
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[1], SRCAND);
		}
	}

	//���Ƶڶ���ɻ���С�ӵ�
	for (int i = 0; i < 30; i++)
	{
		if (myPlane1_bullet2[i].isExist == true)
		{
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[1], SRCAND);
		}
	}

	//���Ƶ�����ɻ���С�ӵ�
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

//��Ϸѡ��ɻ��������ݸ���
void BeginUpdate()
{
	//��ͼ�Լ����ƶ�
	if (back1[0].y >= HEIGHT)
	{
		back1[0].y = -HEIGHT;
	}
	if (back1[0].y < HEIGHT)
	{
		back1[0].y++;
	}

	//�ڶ��ŵ�ͼ
	if (back2[0].y >= HEIGHT)
	{
		back2[0].y = -HEIGHT;
	}
	if (back2[0].y < HEIGHT)
	{
		back2[0].y++;
	}

	//��������1����ѡ���һ���ɻ���ս����������2ʱ����ѡ��ڶ����ɻ���ս
	char key = ' ';
	if (_kbhit())   //��鰴��
	{
		key = _getch();   // ���ܰ���
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
	//�ҵķɻ��������ӵ�
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

	//���ӵ����ƶ�
	for (int i = 0; i < 100; i++)
	{
		//���ӵ�����ʱ�����ӵ��ͻ����Ϸ�
		if (myPlane_bullet[i].isExist == true)
		{
			myPlane_bullet[i].y -= myPlane_bullet[i].speed;
		}

		//�����ӵ��ɳ�ȥʱ�����ӵ�����ʧ��
		if (myPlane_bullet[i].y <= 0)
		{
			myPlane_bullet[i].isExist = false;
		}
	}

	//С�ӵ����ƶ�
	for (int i = 0; i < 200; i++)
	{
		//С�ӵ�����ʱ��С�ӵ��ͻ����Ϸ�
		if (myPlane_smallBullet[i].isExist == true)
		{
			myPlane_smallBullet[i].y -= myPlane_bullet[i].speed;
		}

		//��С�ӵ��ɳ�ȥʱ��С�ӵ�����ʧ��
		if (myPlane_smallBullet[i].y <= 0)
		{
			myPlane_smallBullet[i].isExist = false;
		}
	}

	//�ڶ�����ӵ����ƶ�
	for (int i = 0; i < 60; i++)
	{
		//���ӵ�����ʱ�����ӵ��ͻ����Ϸ�
		if (myPlane1_bullet1[i].isExist == true)
		{
			myPlane1_bullet1[i].y -= myPlane1_bullet1[i].speed;
		}

		//�����ӵ��ɳ�ȥʱ�����ӵ�����ʧ��
		if (myPlane1_bullet1[i].y <= 0)
		{
			myPlane1_bullet1[i].isExist = false;
		}
	}

	//�ڶ�����ӵ����ƶ�
	for (int i = 0; i < 30; i++)
	{
		//���ӵ�����ʱ�����ӵ��ͻ����Ϸ�
		if (myPlane1_bullet2[i].isExist == true)
		{
			myPlane1_bullet2[i].y -= myPlane1_bullet2[i].speed;
		}

		//�����ӵ��ɳ�ȥʱ�����ӵ�����ʧ��
		if (myPlane1_bullet2[i].y <= 0)
		{
			myPlane1_bullet2[i].isExist = false;
		}
	}

	//�������ӵ����ƶ�
	for (int i = 0; i < 30; i++)
	{
		//�������ӵ�����ʱ���ӵ��ͻ����Ϸ�
		if (myPlane2_bullet1[i].isExist == true)
		{
			myPlane2_bullet1[i].y -= myPlane2_bullet1[i].speed;
		}

		//���������ӵ��ɳ�ȥʱ���ӵ�����ʧ��
		if (myPlane2_bullet1[i].y <= 0)
		{
			myPlane2_bullet1[i].isExist = false;
		}
	}
}

//2.��Ϸ��ʼ��
void GameInit()
{
	//���ر���ͼ
	loadimage(&background1[0], _T("resource/scene/bg0.jpg"));
	loadimage(&background2[0], _T("resource/scene/bg0.jpg"));
	back1[0].x = back2[0].x = 0;
	back1[0].y = 0;
	back2[0].y = HEIGHT;

	//���ر���ͼ
	loadimage(&background1[1], _T("resource/scene/bg1.jpg"));
	loadimage(&background2[1], _T("resource/scene/bg1.jpg"));
	back1[1].x = back2[1].x = 0;
	back1[1].y = 0;
	back2[1].y = HEIGHT;

	//���ر���ͼ
	loadimage(&background1[2], _T("resource/scene/bg2.jpg"));
	loadimage(&background2[2], _T("resource/scene/bg2.jpg"));
	back1[2].x = back2[2].x = 0;
	back1[2].y = 0;
	back2[2].y = HEIGHT;

	//���ر���ͼ
	loadimage(&background1[3], _T("resource/scene/bg3.jpg"));
	loadimage(&background2[3], _T("resource/scene/bg3.jpg"));
	back1[3].x = back2[3].x = 0;
	back1[3].y = 0;
	back2[3].y = HEIGHT;

	//���ر���ͼ
	loadimage(&background1[4], _T("resource/scene/bg4.jpg"));
	loadimage(&background2[4], _T("resource/scene/bg4.jpg"));
	back1[4].x = back2[4].x = 0;
	back1[4].y = 0;
	back2[4].y = HEIGHT;
	srand(time(0));

	//���ű�������
	mciSendString(_T("open resource/music/level1.mp3"), 0, 0, 0);
	mciSendString(_T("play resource/music/level1.mp3 repeat"), 0, 0, 0);

	//�����Լ��ĵ�һ���ɻ�
	loadimage(&myPlane.mimg[0], _T("resource/newPlayer/uiPlane0.jpg"));
	loadimage(&myPlane.mimg[1], _T("resource/newPlayer/uiPlane1.jpg"));
	myPlane.x = 230;
	myPlane.y = HEIGHT - 90;
	myPlane.HP = 100;
	myPlane.level = 1;

	//�����Լ��ĵڶ����ɻ�
	loadimage(&myPlane1.mimg[0], _T("resource/newPlayer/myPlane1(0).jpg"));
	loadimage(&myPlane1.mimg[1], _T("resource/newPlayer/myPlane1(1).jpg"));
	myPlane1.x = 230;
	myPlane1.y = HEIGHT - 90;
	myPlane1.HP = 100;
	myPlane1.level = 1;

	//�����Լ��ĵ������ɻ�
	loadimage(&myPlane2.mimg[0], _T("resource/newPlayer/myPlane2(0).jpg"));
	loadimage(&myPlane2.mimg[1], _T("resource/newPlayer/myPlane2(1).jpg"));
	myPlane2.x = 230;
	myPlane2.y = HEIGHT - 90;
	myPlane2.HP = 100;
	myPlane2.level = 1;

	//���طɻ�����������
	for (int i = 0; i < 4; i++)
	{
		loadimage(&upgrading[i].uimg[0], _T("resource/newPlayer/upgrading(0).jpg"));
		loadimage(&upgrading[i].uimg[1], _T("resource/newPlayer/upgrading(1).jpg"));
		upgrading[i].isExist = false;
	};

	//���ش��ӵ�
	for (int i = 0; i < 100; i++)
	{
		myPlane_bullet[i].speed = 2;
		myPlane_bullet[i].isExist = false;
		loadimage(&myPlane_bullet[i].bimg[0], _T("resource/newPlayer/bullet0.jpg"));
		loadimage(&myPlane_bullet[i].bimg[1], _T("resource/newPlayer/bullet1.jpg"));
		myPlane_bullet[i].attack = 10;
	}
	t1 = GetTickCount();

	//����С�ӵ�
	for (int i = 0; i < 200; i++)
	{
		myPlane_smallBullet[i].speed = 2;
		myPlane_smallBullet[i].isExist = false;
		loadimage(&myPlane_smallBullet[i].sbimg[0], _T("resource/newPlayer/bullet2.jpg"));
		loadimage(&myPlane_smallBullet[i].sbimg[1], _T("resource/newPlayer/bullet3.jpg"));
		myPlane_smallBullet[i].attack = 5;
	}

	//���صڶ���ɻ��Ĵ��ӵ�
	for (int i = 0; i < 60; i++)
	{
		myPlane1_bullet1[i].speed = 2;
		myPlane1_bullet1[i].isExist = false;
		loadimage(&myPlane1_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(2).jpg"));
		loadimage(&myPlane1_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(3).jpg"));
		myPlane1_bullet1[i].attack = 8;
	}

	//���صڶ���ɻ���С�ӵ�
	for (int i = 0; i < 30; i++)
	{
		myPlane1_bullet2[i].speed = 2;
		myPlane1_bullet2[i].isExist = false;
		loadimage(&myPlane1_bullet2[i].sbimg[0], _T("resource/newPlayer/myPlane1_bullet(0).jpg"));
		loadimage(&myPlane1_bullet2[i].sbimg[1], _T("resource/newPlayer/myPlane1_bullet(1).jpg"));
		myPlane1_bullet2[i].attack = 4;
	}

	//���ص�����ɻ��Ĵ��ӵ�
	for (int i = 0; i < 30; i++)
	{
		myPlane2_bullet1[i].speed = 2;
		myPlane2_bullet1[i].isExist = false;
		loadimage(&myPlane2_bullet1[i].sbimg[0], _T("resource/newPlayer/myPlane2_bullet(0).jpg"));
		loadimage(&myPlane2_bullet1[i].sbimg[1], _T("resource/newPlayer/myPlane2_bullet(1).jpg"));
	}

	//���ظ����ӵ�
	for (int i = 0; i < 10; i++)
	{
		track_bullet[i].isExist = false;
		loadimage(&track_bullet[i].sbimg[0], _T("resource/newPlayer/myPlane2_bullet(2).jpg"));
		loadimage(&track_bullet[i].sbimg[1], _T("resource/newPlayer/myPlane2_bullet(3).jpg"));
	}
	Ta = GetTickCount();

	//����С�л�
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
	
	//����С�л��ӵ�
	for (int i = 0; i < 20; i++)
	{
		littleEnemy_bullet1[i].speed = 1;
		littleEnemy_bullet1[i].isExist = false;
		loadimage(&littleEnemy_bullet1[i].ebimg[0], _T("resource/newEnemy/littleEnemy2_bullet(0).jpg"));
		loadimage(&littleEnemy_bullet1[i].ebimg[1], _T("resource/newEnemy/littleEnemy2_bullet(1).jpg"));
		littleEnemy_bullet1[i].attack = 20;
	}

	//�����ел�
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

	//���صڶ����ел�
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

	//�����ел��ӵ�
	for (int i = 0; i < 30; i++)
	{
		middleEnemy_bullet1[i].speed = 1;
		middleEnemy_bullet1[i].isExist = false;
		loadimage(&middleEnemy_bullet1[i].mbimg[0], _T("resource/newEnemy/littleEnemy1_bullet(0).jpg"));
		loadimage(&middleEnemy_bullet1[i].mbimg[1], _T("resource/newEnemy/littleEnemy1_bullet(1).jpg"));
		middleEnemy_bullet1[i].attack = 30;
	}

	//����Boss1
	Boss1.isExist = false;
	loadimage(&Boss1.eimg[0], _T("resource/newEnemy/Boss(0).jpg"));
	loadimage(&Boss1.eimg[1], _T("resource/newEnemy/Boss(1).jpg"));
	Boss1.collision = 50;
	Boss1.HP = 1000;
	Boss1.attack = false;

	////����boss���ӵ�
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

//3.����
void GameDraw()
{
	BeginBatchDraw();

	//���Ʊ���
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

	//���Լ��ɻ����ʱ�������Լ��ķɻ�
	if (myPlane.isExist == true)
	{
		putimage(myPlane.x, myPlane.y, &myPlane.mimg[0], SRCPAINT);
		putimage(myPlane.x, myPlane.y, &myPlane.mimg[1], SRCAND);
	}

	//���ƴ��ӵ�
	for (int i = 0; i < 100; i++)
	{
		if (myPlane_bullet[i].isExist == true)
		{
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[0], SRCPAINT);
			putimage(myPlane_bullet[i].x, myPlane_bullet[i].y, &myPlane_bullet[i].bimg[1], SRCAND);
		}
	}

	//��������������
	for (int i = 0; i < 4; i++)
	{
		if (upgrading[i].isExist == true)
		{
			putimage(upgrading[i].x, upgrading[i].y, &upgrading[i].uimg[0], SRCPAINT);
			putimage(upgrading[i].x, upgrading[i].y, &upgrading[i].uimg[1], SRCAND);
		}
	}

	//����С�ӵ�
	for (int i = 0; i < 200; i++)
	{
		if (myPlane_smallBullet[i].isExist == true)
		{
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[0], SRCPAINT);
			putimage(myPlane_smallBullet[i].x, myPlane_smallBullet[i].y, &myPlane_smallBullet[i].sbimg[1], SRCAND);
		}
	}

	//���Լ��ڶ���ɻ����ʱ�������Լ��ķɻ�
	if (myPlane1.isExist == true)
	{
		putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[0], SRCPAINT);
		putimage(myPlane1.x, myPlane1.y, &myPlane1.mimg[1], SRCAND);
	}

	//���Ƶڶ���ɻ����ӵ�
	for (int i = 0; i < 60; i++)
	{
		if (myPlane1_bullet1[i].isExist == true)
		{
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet1[i].x, myPlane1_bullet1[i].y, &myPlane1_bullet1[i].sbimg[1], SRCAND);
		}
	}

	//���Ƶڶ���ɻ���С�ӵ�
	for (int i = 0; i < 30; i++)
	{
		if (myPlane1_bullet2[i].isExist == true)
		{
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[0], SRCPAINT);
			putimage(myPlane1_bullet2[i].x, myPlane1_bullet2[i].y, &myPlane1_bullet2[i].sbimg[1], SRCAND);
		}
	}

	//���Լ�������ɻ����ʱ�������Լ��ķɻ�
	if (myPlane2.isExist == true)
	{
		putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[0], SRCPAINT);
		putimage(myPlane2.x, myPlane2.y, &myPlane2.mimg[1], SRCAND);
	}

	//���Ƶ�����ɻ���С�ӵ�
	for (int i = 0; i < 30; i++)
	{
		if (myPlane2_bullet1[i].isExist == true)
		{
			putimage(myPlane2_bullet1[i].x, myPlane2_bullet1[i].y, &myPlane2_bullet1[i].sbimg[0], SRCPAINT);
			putimage(myPlane2_bullet1[i].x, myPlane2_bullet1[i].y, &myPlane2_bullet1[i].sbimg[1], SRCAND);
		}
	}

	//���Ƶ�����ɻ���С�ӵ�
	for (int i = 0; i < 15; i++)
	{
		if (track_bullet[i].isExist == true)
		{
			putimage(track_bullet[i].x, track_bullet[i].y, &track_bullet[i].sbimg[0], SRCPAINT);
			putimage(track_bullet[i].x, track_bullet[i].y, &track_bullet[i].sbimg[1], SRCAND);
		}
	}

	//����С�л�
	for (int i = 0; i < 4; i++)
	{
		if (littleEnemy1[i].isExist == true)
		{
			putimage(littleEnemy1[i].x, littleEnemy1[i].y, &littleEnemy1[i].eimg[0], SRCPAINT);
			putimage(littleEnemy1[i].x, littleEnemy1[i].y, &littleEnemy1[i].eimg[1], SRCAND);
		}
	}

	//�����ел�
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy1[i].isExist == true)
		{
			putimage(middleEnemy1[i].x, middleEnemy1[i].y, &middleEnemy1[i].mimg[0], SRCPAINT);
			putimage(middleEnemy1[i].x, middleEnemy1[i].y, &middleEnemy1[i].mimg[1], SRCAND);
		}
	}

	//���Ƶڶ����ел�
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy2[i].isExist == true)
		{
			putimage(middleEnemy2[i].x, middleEnemy2[i].y, &middleEnemy2[i].mimg[0], SRCPAINT);
			putimage(middleEnemy2[i].x, middleEnemy2[i].y, &middleEnemy2[i].mimg[1], SRCAND);
		}
	}

	//����С�л��ӵ�
	for (int i = 0; i < 20; i++)
	{
		if (littleEnemy_bullet1[i].isExist == true)
		{
			putimage(littleEnemy_bullet1[i].x, littleEnemy_bullet1[i].y, &littleEnemy_bullet1[i].ebimg[0], SRCPAINT);
			putimage(littleEnemy_bullet1[i].x, littleEnemy_bullet1[i].y, &littleEnemy_bullet1[i].ebimg[1], SRCAND);
		}
	}

	//�����ел��ӵ�
	for (int i = 0; i < 30; i++)
	{
		if (middleEnemy_bullet1[i].isExist == true)
		{
			putimage(middleEnemy_bullet1[i].x, middleEnemy_bullet1[i].y, &middleEnemy_bullet1[i].mbimg[0], SRCPAINT);
			putimage(middleEnemy_bullet1[i].x, middleEnemy_bullet1[i].y, &middleEnemy_bullet1[i].mbimg[1], SRCAND);
		}
	}

	//����Boss
	if (Boss1.isExist == true)
	{
		putimage(Boss1.x, Boss1.y, &Boss1.eimg[0], SRCPAINT);
		putimage(Boss1.x, Boss1.y, &Boss1.eimg[1], SRCAND);
	}

	//����Boss�ӵ�
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

	//������Ļ
	if (myPlane.isExist == true)
	{
		//�����ҵķɻ�Ѫ��
		wchar_t str[20] = { 0 };
		settextcolor(GREEN);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("Consolas"));
		wsprintf(str, L"HP��%d", myPlane.HP);
		outtextxy(10, 700, str);
	}

	if (myPlane1.isExist == true)
	{
		//�����ҵĵ�һ���ɻ�Ѫ��
		wchar_t str[20] = { 0 };
		settextcolor(GREEN);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("Consolas"));
		wsprintf(str, L"HP��%d", myPlane1.HP);
		outtextxy(10, 700, str);
	}

	if (myPlane2.isExist == true)
	{
		//�����ҵĵ�һ���ɻ�Ѫ��
		wchar_t str[20] = { 0 };
		settextcolor(GREEN);
		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("Consolas"));
		wsprintf(str, L"HP��%d", myPlane2.HP);
		outtextxy(10, 700, str);
	}

	EndBatchDraw();
}

//4.���ݵĸ���
void GameUpdate()
{
	if (gameLevel == 1)
	{
		//��ͼ�Լ����ƶ�
		if (back1[0].y >= HEIGHT)
		{
			back1[0].y = -HEIGHT;
		}
		if (back1[0].y < HEIGHT)
		{
			back1[0].y++;
		}

		//�ڶ��ŵ�ͼ
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
		//��ͼ�Լ����ƶ�
		if (back1[1].y >= HEIGHT)
		{
			back1[1].y = -HEIGHT;
		}
		if (back1[1].y < HEIGHT)
		{
			back1[1].y++;
		}

		//�ڶ��ŵ�ͼ
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
		//��ͼ�Լ����ƶ�
		if (back1[2].y >= HEIGHT)
		{
			back1[2].y = -HEIGHT;
		}
		if (back1[2].y < HEIGHT)
		{
			back1[2].y++;
		}

		//�ڶ��ŵ�ͼ
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
		//��ͼ�Լ����ƶ�
		if (back1[3].y >= HEIGHT)
		{
			back1[3].y = -HEIGHT;
		}
		if (back1[3].y < HEIGHT)
		{
			back1[3].y++;
		}

		//�ڶ��ŵ�ͼ
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
		//��ͼ�Լ����ƶ�
		if (back1[4].y >= HEIGHT)
		{
			back1[4].y = -HEIGHT;
		}
		if (back1[4].y < HEIGHT)
		{
			back1[4].y++;
		}

		//�ڶ��ŵ�ͼ
		if (back2[4].y >= HEIGHT)
		{
			back2[4].y = -HEIGHT;
		}
		if (back2[4].y < HEIGHT)
		{
			back2[4].y++;
		}
	}
	
	//�Լ�ս�����ƶ�
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

	//�ڶ���ս�����ƶ�
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

	//������ս�����ƶ�
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
	//����Ϊ��һ��ս��
	if (myPlane.isExist == true)
	{
		//�ȼ�һ�������ӵ�
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

		//�ȼ����������ӵ�
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

		//�ȼ����������ӵ�
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

		//�ȼ��Ĳ������ӵ�
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

	//����Ϊ�ڶ���ս��
	if (myPlane1.isExist == true)
	{
		//�ȼ�һ�������ӵ�
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

		//�ȼ����������ӵ�
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

		//�ȼ����������ӵ�
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

	//����Ϊ������ս����ֻ������ͨ�ӵ�
	if (myPlane2.isExist == true)
	{
		//�ȼ�һ�������ӵ�
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

		//�ȼ����������ӵ�
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

		//�ȼ����������ӵ�
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

		//�ȼ��Ĳ������ӵ�
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
	//һ��Ϊ������ս������������ӵ�
	if (myPlane2.isExist == true)
	{
		//�ȼ�һ�������ӵ�
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

		//�ȼ����������ӵ�
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

		//�ȼ����������ӵ�
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

		//�ȼ��Ĳ������ӵ�
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

	//����������ƶ�
	for (int i = 0; i < 4; i++)
	{
		if (upgrading[i].isExist == true)
		{
			upgrading[i].y += upgrading[i].y_speed;
			upgrading[i].x += upgrading[i].x_speed;
		}
	}	

	//�����������嵽��߽��ʱ�򣬾ͷ�������ƶ�
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

	//����������ҵķɻ��������ҵķɻ�������������������ʧ
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

	//���ӵ����ƶ�
	for (int i = 0; i < 100; i++)
	{
		//���ӵ�����ʱ�����ӵ��ͻ����Ϸ�
		if (myPlane_bullet[i].isExist == true)
		{
			myPlane_bullet[i].y -= myPlane_bullet[i].speed;
		}

		//�����ӵ��ɳ�ȥʱ�����ӵ�����ʧ��
		if (myPlane_bullet[i].y <= 0)
		{
			myPlane_bullet[i].isExist = false;
		}
	}

	//С�ӵ����ƶ�
	for (int i = 0; i < 200; i++)
	{
		//С�ӵ�����ʱ��С�ӵ��ͻ����Ϸ�
		if (myPlane_smallBullet[i].isExist == true)
		{
			myPlane_smallBullet[i].y -= myPlane_smallBullet[i].speed;
		}

		//��С�ӵ��ɳ�ȥʱ��С�ӵ�����ʧ��
		if (myPlane_smallBullet[i].y <= 0)
		{
			myPlane_smallBullet[i].isExist = false;
		}
	}

	//�ڶ�����ӵ����ƶ�
	for (int i = 0; i < 60; i++)
	{
		//���ӵ�����ʱ�����ӵ��ͻ����Ϸ�
		if (myPlane1_bullet1[i].isExist == true)
		{
			myPlane1_bullet1[i].y -= myPlane1_bullet1[i].speed;
		}

		//�����ӵ��ɳ�ȥʱ�����ӵ�����ʧ��
		if (myPlane1_bullet1[i].y <= 0)
		{
			myPlane1_bullet1[i].isExist = false;
		}
	}

	//�ڶ���С�ӵ����ƶ�
	for (int i = 0; i < 30; i++)
	{
		//���ӵ�����ʱ�����ӵ��ͻ����Ϸ�
		if (myPlane1_bullet2[i].isExist == true)
		{
			myPlane1_bullet2[i].y -= myPlane1_bullet2[i].speed;
		}

		//�����ӵ��ɳ�ȥʱ�����ӵ�����ʧ��
		if (myPlane1_bullet2[i].y <= 0)
		{
			myPlane1_bullet2[i].isExist = false;
		}
	}

	//�������ӵ����ƶ�
	for (int i = 0; i < 30; i++)
	{
		//�������ӵ�����ʱ���ӵ��ͻ����Ϸ�
		if (myPlane2_bullet1[i].isExist == true)
		{
			myPlane2_bullet1[i].y -= myPlane2_bullet1[i].speed;
		}

		//���������ӵ��ɳ�ȥʱ���ӵ�����ʧ��
		if (myPlane2_bullet1[i].y <= 0)
		{
			myPlane2_bullet1[i].isExist = false;
		}
	}

	//�����ӵ����ƶ�
	if (myPlane2.isExist == true)
	{
		for (int i = 0; i < 10; i++)
		{
			if (track_bulletmove >= 10)
			{
				//�������ӵ�����ʱ�������ӵ����ƶ�
				if (track_bullet[i].isExist == true)
				{
					track_bullet[i].y += track_bullet[i].y_speed;
					track_bullet[i].x += track_bullet[i].x_speed;
				}

				//�������ӵ�������Ļʱ�������ӵ���ʧ
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

	//�����ӵ��ĸ���Ч��
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
					//�ж�С�л�
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

					//�жϵ�һ���ел�
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

					//�жϵڶ����ел�
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

					//�ж�BOSS
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

	//С�л��Ĳ���	91 * 70
	t4 = GetTickCount();
	if (littleEnemy1_creation == true && Boss1.isExist == false)
	{
		if (t4 - t3 >= 3000)
		{
			//�ɻ����ȵķֲ�
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

	//�����ú�С�л��Ż��ٴβ���
	if (t4 - t3 >= 15000)
	{
		littleEnemy1_creation = true;
	}

	//С�л����ƶ�
	for (int i = 0; i < 4; i++)
	{
		//С�л�����ʱ���Զ�������
		if (littleEnemy1[i].isExist == true && littleEnemy1[i].isStop == false)
		{
			littleEnemy1[i].y += littleEnemy1[i].speed;
			littleEnemy1[i].count = 0;
		}

		//��С�л����䵽200��ʱ		���л�ֹͣ�˶���ʱ�򣬵л��Ĺ����Żᱻ����
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

		//���л�ֹͣ�˶���ʼ��ʱ�򣬼�¼ʱ��t9
		if (littleEnemy1[i].count == 1)
		{
			t9 = GetTickCount();
		}

		//��t10 - t9 >=1500ʱ���л���ʼ�˶�
		t10 = GetTickCount();
		if (littleEnemy1[i].isStop == true && t10 - t9 == 3000)
		{
			littleEnemy1[i].y++;
		}

		//���л��ɳ�ȥʱ���л�����ʧ��
		if (littleEnemy1[i].y >= HEIGHT)
		{
			littleEnemy1[i].isExist = false;
		}
	}

	t6 = GetTickCount();
	//С�л������������ӵ�
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

	//С�л��ӵ����ƶ�
	for (int i = 0; i < 20; i++)
	{
		if (littleEnemy_bullet1[i].isExist == true)
		{
			littleEnemy_bullet1[i].y++;
		}
	}

	//��С�л����ӵ��������趨�ĸ߶ȣ��ӵ���ʧ
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

	//��һ���ел��Ĳ���	123 * 161   119 * 147
	t12 = GetTickCount();
	if (middleEnemy1_creation1 == true && middleEnemy1_creation2 == true)
	{
		if (t12 - t11 >= 10000)
		{
			//�ɻ����ȵķֲ�
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

	//�ڶ����ел��Ĳ���
	if (middleEnemy1_creation1 == false && middleEnemy1_creation2 == true)
	{
		if (t12 - t11 >= 20000)
		{
			//�ɻ����ȵķֲ�
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

	//BOSS�Ĳ���
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

	//BOSS�ޱ���
	if (Boss1.isExist == true && Boss1.one == true && Boss1.isMad == false)
	{
		Boss1.x_speed = 1;
		Boss1.y_speed = 1;
		Boss1.one = false;
		Boss1.level = 1;
	}

	//��Boss��Ѫ��С��һ��
	if (Boss1.isExist == true && Boss1.HP <= 1250 && Boss1.isMad == false)
	{
		Boss1.isMad = true;
		Boss1.one = true;
	}

	//BOSS��ʼ����
	if (Boss1.isExist == true && Boss1.one == true && Boss1.isMad == true)
	{
		Boss1.level = 2;
		Boss1.one = false;
		Boss1.x_speed *= 2;
	}

	//Boss����
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

	//BOSS���ƶ�
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

	//BOSS���ƶ���Χ
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

	//Boss���ӵ�����
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

	//Boss�ӵ����ƶ�
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

	//��boss���ӵ������˽���ʱ��ʧ
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

	//��Boss���ӵ������ҵķɻ�
	for (int i = 0; i < 100; i++)
	{
		if (Boss_bullet1[i].isExist == true)
		{
			//�ҵĵ�һ���ɻ�
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

			//�ҵĵڶ����ɻ�
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

			//�ҵĵ������ɻ�
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
			//�ҵĵ�һ���ɻ�
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

			//�ҵĵڶ����ɻ�
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

			//�ҵĵ������ɻ�
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
			//�ҵĵ�һ���ɻ�
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

			//�ҵĵڶ����ɻ�
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

			//�ҵĵ������ɻ�
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

	//���ҵ��ӵ�����Bossʱ,BossѪ������
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

	//��С�ӵ���boss��ײʱ��С�ӵ����ݻ٣�boss��Ѫ
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

	//���ڶ���ɻ��Ĵ��ӵ���boss��ײʱ�����ӵ������������boss��boss��Ѫ
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

	//���ڶ���ɻ���С�ӵ���boss��ײʱ��С�ӵ������������boss��boss��Ѫ
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

	//��������ɻ����ӵ����һ���ел���ײʱ���ӵ�������������û����ел���Ѫ
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

	//�������ӵ���ڶ����ел���ײʱ���ӵ����ݻ٣��ел���Ѫ
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

	//��Boss��HPС��0ʱ��Boss����
	if (Boss1.HP <= 0)
	{
		Boss1.isExist = false;
		gameIsPlay = false;
		chooseIsPlay = true;
		bound = -3;
		chooseLevel++;
	}
	
	//��һ���ел����ƶ�
	for (int i = 0; i < 2; i++)
	{
		//�ел�����ʱ���Զ�������
		if (middleEnemy1[i].isExist == true && middleEnemy1[i].isStop == false)
		{
			middleEnemy1[i].y += middleEnemy1[i].speed;
			middleEnemy1[i].count = 0;
		}

		//��С�л����䵽100��ʱ		���л�ֹͣ�˶���ʱ�򣬵л��Ĺ����Żᱻ����
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

		//���л�ֹͣ�˶���ʼ��ʱ�򣬼�¼ʱ��t9
		if (middleEnemy1[i].count == 1)
		{
			t13 = GetTickCount();
		}

		//��t14 - t13 >=3000ʱ���л���ʼ�˶�
		t14 = GetTickCount();
		if (middleEnemy1[i].isStop == true && t14 - t13 == 3000)
		{
			middleEnemy1[i].y++;
		}

		//���л��ɳ�ȥʱ���л�����ʧ��
		if (middleEnemy1[i].y >= HEIGHT)
		{
			middleEnemy1[i].isExist = false;
		}
	}

	//�ڶ����ел����ƶ�
	for (int i = 0; i < 2; i++)
	{
		//�ел�����ʱ���Զ�������
		if (middleEnemy2[i].isExist == true && middleEnemy2[i].isStop == false)
		{
			middleEnemy2[i].y += middleEnemy2[i].speed;
			middleEnemy2[i].count = 0;
		}

		//��С�л����䵽100��ʱ		���л�ֹͣ�˶���ʱ�򣬵л��Ĺ����Żᱻ����
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

		//���л�ֹͣ�˶���ʼ��ʱ�򣬼�¼ʱ��t9
		if (middleEnemy2[i].count == 1)
		{
			t13 = GetTickCount();
		}

		//��t14 - t13 >=3000ʱ���л���ʼ�˶�
		t14 = GetTickCount();
		if (middleEnemy2[i].isStop == true && t14 - t13 == 3000)
		{
			middleEnemy2[i].y++;
		}

		//���л��ɳ�ȥʱ���л�����ʧ��
		if (middleEnemy2[i].y >= HEIGHT)
		{
			middleEnemy2[i].isExist = false;
		}
	}

	t16 = GetTickCount();
	//��һ���ел������������ӵ�
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

	//�ڶ����ел������������ӵ�
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

	//�ел��ӵ����ƶ�
	for (int i = 0; i < 30; i++)
	{
		if (middleEnemy_bullet1[i].isExist == true)
		{
			middleEnemy_bullet1[i].y++;
		}
	}

	//���ел����ӵ��������趨�ĸ߶ȣ��ӵ���ʧ
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

	//�����ӵ���С�л���ײʱ�����ӵ����ݻ٣�С�л���Ѫ
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

	//��С�ӵ���С�л���ײʱ��С�ӵ����ݻ٣�С�л���Ѫ
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

	//�����ӵ����һ���ел���ײʱ�����ӵ����ݻ٣��ел���Ѫ
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

	//�����ӵ���ڶ����ел���ײʱ�����ӵ����ݻ٣��ел���Ѫ
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

	//��С�ӵ����һ���ел���ײʱ��С�ӵ����ݻ٣��ел���Ѫ
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

	//��С�ӵ���ڶ����ел���ײʱ��С�ӵ����ݻ٣��ел���Ѫ
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

	//���ڶ���ɻ��Ĵ��ӵ���С�л���ײʱ�����ӵ�������������û���С�л���Ѫ
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

	//���ڶ���ɻ���С�ӵ���С�л���ײʱ��С�ӵ�������������û���С�л���Ѫ
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

	//���ڶ���ɻ��Ĵ��ӵ����һ���ел���ײʱ�����ӵ�������������û����ел���Ѫ
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

	//���ڶ���ɻ��Ĵ��ӵ���ڶ����ел���ײʱ�����ӵ�������������û����ел���Ѫ
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

	//���ڶ���ɻ���С�ӵ����һ���ел���ײʱ��С�ӵ�������������û����ел���Ѫ
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

	//���ڶ���ɻ���С�ӵ����һ���ел���ײʱ��С�ӵ�������������û����ел���Ѫ
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

	//��������ɻ����ӵ���С�л���ײʱ��С�ӵ�������������û���С�л���Ѫ
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

	//��������ɻ����ӵ����һ���ел���ײʱ���ӵ�������������û����ел���Ѫ
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

	//��������ɻ���С�ӵ���ڶ����ел���ײʱ���ӵ�������������û����ел���Ѫ
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

	//���ҵĸ����ӵ���С�л���ײʱ���ӵ���ʧ��С�л���Ѫ
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

	//�������ӵ����һ���ел���ײʱ���ӵ����ݻ٣��ел���Ѫ
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

	//�������ӵ���ڶ����ел���ײʱ���ӵ����ݻ٣��ел���Ѫ
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

	//��С�л���HP<=0��ʱ��С�л����ݻ٣�����������ʳ���
	for (int i = 0; i < 4; i++)
	{
		if (littleEnemy1[i].isExist == true)
		{
			if (littleEnemy1[i].HP <= 0)
			{
				if (rand() % 4 == 0)
				{
					//������������
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

	//����һ���ел����ݻ�ʱ�����ʲ�����������
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy1[i].isExist == true)
		{
			if (middleEnemy1[i].HP <= 0)
			{
				if (rand() % 3 == 0)
				{
					//������������
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

	//���ڶ����ел����ݻ�ʱ�����ʲ�����������
	for (int i = 0; i < 2; i++)
	{
		if (middleEnemy2[i].isExist == true)
		{
			if (middleEnemy2[i].HP <= 0)
			{
				if (rand() % 3 == 0)
				{
					//������������
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

	//��С�л�����������ӵ������ǵķɻ�����ײʱ���ҵķɻ���Ѫ
	for (int i = 0; i < 20; i++)
	{
		if (littleEnemy_bullet1[i].isExist == true)
		{
			//�ҵĵ�һ��ɻ�
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

			//�ҵĵڶ����ɻ�
			if (littleEnemy_bullet1[i].x + 12 > myPlane1.x &&
				littleEnemy_bullet1[i].x < myPlane1.x + 43 &&
				littleEnemy_bullet1[i].y + 75 > myPlane1.y &&
				littleEnemy_bullet1[i].y < myPlane1.y + 62)
			{
				//�ҵķɻ�
				if (myPlane1.isExist == true)
				{
					littleEnemy_bullet1[i].isExist = false;
					myPlane1.HP -= littleEnemy_bullet1[i].attack;
				}
			}

			//�ҵĵ������ɻ�
			if (littleEnemy_bullet1[i].x + 12 > myPlane2.x &&
				littleEnemy_bullet1[i].x < myPlane2.x + 43 &&
				littleEnemy_bullet1[i].y + 75 > myPlane2.y &&
				littleEnemy_bullet1[i].y < myPlane2.y + 62)
			{
				//�ҵķɻ�
				if (myPlane2.isExist == true)
				{
					littleEnemy_bullet1[i].isExist = false;
					myPlane2.HP -= littleEnemy_bullet1[i].attack;
				}
			}
		}
	}

	//���ел�����������ӵ������ǵķɻ�����ײʱ���ҵķɻ���Ѫ
	for (int i = 0; i < 30; i++)
	{
		if (middleEnemy_bullet1[i].isExist == true)
		{
			//�ҵĵ�һ���ɻ�
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

			//�ҵĵڶ����ɻ�
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

			//�ҵĵ������ɻ�
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

	//���л����ҷ�����ײʱ���ҵķɻ����Ѫ���л���ʧ
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

	//��С�л����ҷ�����ײʱ���ҵķɻ����Ѫ���л�Сʱ
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

	//��С�л����ҷ�����ײʱ���ҵķɻ����Ѫ���л�Сʱ
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

	//���Լ��ķɻ�HP<=0ʱ����Ϸʧ�ܣ��ص�ѡ��ؿ�
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
	initgraph(WIDTH, HEIGHT); //�����Ĵ�С

	while (1)
	{
		//��Ϸ������
		while (bound == -2)
		{
			MainBeginInit();
			while (mainBeginIsPlay == true)
			{
				MainBeginDraw();
			}
			mciSendString(_T("pause resource/music/begin_music.mp3"), 0, 0, 0);
		}

		//ѡ��ؿ�����
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

		//��Ϸ�ɻ�ѡ�����
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

		//��Ϸ����
		while (bound == 0)
		{
			GameInit();					//��ʼ������
			while (gameIsPlay == true)
			{
				GameDraw();				//���ϻ滭ͼƬ
				GameUpdate();			//���ϸ�������
				Sleep(1);
			}
			mciSendString(_T("pause resource/music/level1.mp3"), 0, 0, 0);
		}
	}
}

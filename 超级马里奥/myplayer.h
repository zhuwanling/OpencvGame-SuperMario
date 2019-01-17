// myplayer.h: interface for the myplayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPLAYER_H__418A1883_C5EA_41DD_963A_CAE682637051__INCLUDED_)
#define AFX_MYPLAYER_H__418A1883_C5EA_41DD_963A_CAE682637051__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<cv.h>
#include<highgui.h>

class CMyplayer  
{
	
public:
	int Life();//外界获取人物的生命状态
	void SetMoveGrass(int state);  //当人物与陷阱碰撞后的改变
	void SetMoveJumpwell(int state,int deepstate);//当人物与管道碰撞后的改变
	void JudegeKong(int ko);//当前人物是否需要下落
	void SetMoveJump(int state,int deeepstate);//人物与各种砖块碰撞后的改变
	CvPoint GetNowPlayerPos();//获取当前人物的坐标
	int GetMoveLeftState();//获取当前人物是否有向左走的状态
	int Judegejump();   //获取当前是否再跳。
	int GetMoveRightState();//获取判断当前背景图片滚动条件
	void Move(int width,int height);      //马里奥移动
	void Draw(IplImage *bg);  //将马里奥画在背景图片上
       CMyplayer();
	virtual ~CMyplayer();
	CvPoint   pos;
	int m_life; // 马里奥的生命
	int m_judgejump;//当前是否在跳标记变量；
 
private:
	IplImage *m_player;   //当前应该答应的马里奥图片
	
	int m_speed;     //行走速度
	int m_jumpspeed;  //马里奥跳高的速度；
	
	IplImage * m_playertrsfor[10];  //行走图片集
	int m_MoveRightstate;     //判断当前是否右移动了
	int  m_MoveLeftstate; //判断当前是否想左移动
	int m_stophight; //判断是是否跳到了障碍物上站着
	int m_houre;  //与m_pretime 构成跳所需的间隔；
	int m_pretime;
};

#endif // !defined(AFX_MYPLAYER_H__418A1883_C5EA_41DD_963A_CAE682637051__INCLUDED_)

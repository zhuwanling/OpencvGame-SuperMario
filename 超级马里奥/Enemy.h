// Enemy.h: interface for the CEnemy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMY_H__FD294EF9_4FEE_420A_9529_95451795439E__INCLUDED_)
#define AFX_ENEMY_H__FD294EF9_4FEE_420A_9529_95451795439E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<vector>
#include<cv.h>
#include <highgui.h>
using namespace std;
#include"Obstacle.h"
struct moster 
{
	int x;
	int y;
	int life;
	int tiems;
	int type;
	int movespeed;
	int num;
};
class CEnemy  
{
public:
	void ChangeMoveState(int wh,int state,int deepstate );//怪物碰到障碍物的改变
	void ShowMonster(int distance, IplImage *clonebg);//载入，delete怪物
	void ShowMansterImage(int distance,IplImage *clonebg);//显示怪物到背景上
	CEnemy();
	virtual ~CEnemy();
	vector  <moster> m_nowShowManster;//当前要显示的怪物
	int m_allMonster[200][3]; //所有怪物
	int m_moveDis;  //移动中距离
private :

	IplImage * m_mansterImage[10]; 
	int m_index;//指向怪物加载位置；
     	                     

};

#endif // !defined(AFX_ENEMY_H__FD294EF9_4FEE_420A_9529_95451795439E__INCLUDED_)

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
	void ChangeMoveState(int wh,int state,int deepstate );//���������ϰ���ĸı�
	void ShowMonster(int distance, IplImage *clonebg);//���룬delete����
	void ShowMansterImage(int distance,IplImage *clonebg);//��ʾ���ﵽ������
	CEnemy();
	virtual ~CEnemy();
	vector  <moster> m_nowShowManster;//��ǰҪ��ʾ�Ĺ���
	int m_allMonster[200][3]; //���й���
	int m_moveDis;  //�ƶ��о���
private :

	IplImage * m_mansterImage[10]; 
	int m_index;//ָ��������λ�ã�
     	                     

};

#endif // !defined(AFX_ENEMY_H__FD294EF9_4FEE_420A_9529_95451795439E__INCLUDED_)

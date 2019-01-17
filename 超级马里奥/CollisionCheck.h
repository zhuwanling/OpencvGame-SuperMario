// CollisionCheck.h: interface for the CCollisionCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLISIONCHECK_H__E2CA6E7F_96D5_483D_A0F4_2EBB16B06FE3__INCLUDED_)
#define AFX_COLLISIONCHECK_H__E2CA6E7F_96D5_483D_A0F4_2EBB16B06FE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"Obstacle.h"
class CCollisionCheck  
{
public:
	int CheckGross(CvPoint playerps, CObstacle *temp,int i,int len);   //���������ײ���
	int CheckWell(CvPoint playerps, CObstacle *temp,int i,int len); //��ܵ�����ײ���
	int deep        (CvPoint playerpos,CObstacle * temp); //�Ƿ�Ҫ�����⣨��������뿪�ϰ��

	int JudegCollision(CvPoint playerPos,CObstacle *temp);//�����ϰ�����ײ��⣨����1 2��
	CCollisionCheck();
	virtual ~CCollisionCheck();

};

#endif // !defined(AFX_COLLISIONCHECK_H__E2CA6E7F_96D5_483D_A0F4_2EBB16B06FE3__INCLUDED_)

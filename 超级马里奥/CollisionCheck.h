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
	int CheckGross(CvPoint playerps, CObstacle *temp,int i,int len);   //与陷阱的碰撞检测
	int CheckWell(CvPoint playerps, CObstacle *temp,int i,int len); //与管道的碰撞检测
	int deep        (CvPoint playerpos,CObstacle * temp); //是否要下落检测（及马里奥离开障碍物）

	int JudegCollision(CvPoint playerPos,CObstacle *temp);//所有障碍物碰撞检测（调用1 2）
	CCollisionCheck();
	virtual ~CCollisionCheck();

};

#endif // !defined(AFX_COLLISIONCHECK_H__E2CA6E7F_96D5_483D_A0F4_2EBB16B06FE3__INCLUDED_)

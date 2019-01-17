// Obstacle.h: interface for the CObstacle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBSTACLE_H__6D257ED7_BC79_4FB4_B020_B1FFAB16CD2E__INCLUDED_)
#define AFX_OBSTACLE_H__6D257ED7_BC79_4FB4_B020_B1FFAB16CD2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<vector>
#include<cv.h>
#include<highgui.h>
using namespace std;
struct Obtepy
{
	int x;
	int y;
	int times;
	int tepy;
	int life;
	int change;
};
class CObstacle  
{
public:
	void ShowManey( IplImage *clonebg);    //在带钱砖块上显示金钱
    void ShowObstacle(int distance, IplImage *clonebg);//载入，delet障碍物
	void Showblack(int distance,IplImage *clonebg);//在背景上画出障碍物
	CObstacle();
	virtual ~CObstacle();
/*类型	 block;//1
	 well;//2
	 grass;//3
     maney;//4
	 maneyblock;//5*/
	vector<Obtepy>  m_Ob;  //当前要显示的障碍物

private:
	int m_AllObstacle[2000][3];  //所有障碍物
     int m_Movedis ;//记录所有移动距离；
	 int m_index;//在所有障碍物中读取到哪儿的指标
	 IplImage *m_obImage[20];

};

#endif // !defined(AFX_OBSTACLE_H__6D257ED7_BC79_4FB4_B020_B1FFAB16CD2E__INCLUDED_)

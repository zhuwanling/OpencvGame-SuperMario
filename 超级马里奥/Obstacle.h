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
	void ShowManey( IplImage *clonebg);    //�ڴ�Ǯש������ʾ��Ǯ
    void ShowObstacle(int distance, IplImage *clonebg);//���룬delet�ϰ���
	void Showblack(int distance,IplImage *clonebg);//�ڱ����ϻ����ϰ���
	CObstacle();
	virtual ~CObstacle();
/*����	 block;//1
	 well;//2
	 grass;//3
     maney;//4
	 maneyblock;//5*/
	vector<Obtepy>  m_Ob;  //��ǰҪ��ʾ���ϰ���

private:
	int m_AllObstacle[2000][3];  //�����ϰ���
     int m_Movedis ;//��¼�����ƶ����룻
	 int m_index;//�������ϰ����ж�ȡ���Ķ���ָ��
	 IplImage *m_obImage[20];

};

#endif // !defined(AFX_OBSTACLE_H__6D257ED7_BC79_4FB4_B020_B1FFAB16CD2E__INCLUDED_)

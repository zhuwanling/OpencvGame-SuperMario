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
	int Life();//����ȡ���������״̬
	void SetMoveGrass(int state);  //��������������ײ��ĸı�
	void SetMoveJumpwell(int state,int deepstate);//��������ܵ���ײ��ĸı�
	void JudegeKong(int ko);//��ǰ�����Ƿ���Ҫ����
	void SetMoveJump(int state,int deeepstate);//���������ש����ײ��ĸı�
	CvPoint GetNowPlayerPos();//��ȡ��ǰ���������
	int GetMoveLeftState();//��ȡ��ǰ�����Ƿ��������ߵ�״̬
	int Judegejump();   //��ȡ��ǰ�Ƿ�������
	int GetMoveRightState();//��ȡ�жϵ�ǰ����ͼƬ��������
	void Move(int width,int height);      //������ƶ�
	void Draw(IplImage *bg);  //������»��ڱ���ͼƬ��
       CMyplayer();
	virtual ~CMyplayer();
	CvPoint   pos;
	int m_life; // ����µ�����
	int m_judgejump;//��ǰ�Ƿ�������Ǳ�����
 
private:
	IplImage *m_player;   //��ǰӦ�ô�Ӧ�������ͼƬ
	
	int m_speed;     //�����ٶ�
	int m_jumpspeed;  //��������ߵ��ٶȣ�
	
	IplImage * m_playertrsfor[10];  //����ͼƬ��
	int m_MoveRightstate;     //�жϵ�ǰ�Ƿ����ƶ���
	int  m_MoveLeftstate; //�жϵ�ǰ�Ƿ������ƶ�
	int m_stophight; //�ж����Ƿ��������ϰ�����վ��
	int m_houre;  //��m_pretime ����������ļ����
	int m_pretime;
};

#endif // !defined(AFX_MYPLAYER_H__418A1883_C5EA_41DD_963A_CAE682637051__INCLUDED_)

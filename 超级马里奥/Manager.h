// Manager.h: interface for the CManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANAGER_H__841903BD_74CC_4EA8_815C_549A0CEF8826__INCLUDED_)
#define AFX_MANAGER_H__841903BD_74CC_4EA8_815C_549A0CEF8826__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"GameUI.h"
#include"Myplayer.h"
#include"Obstacle.h"
#include"CollisionCheck.h"
#include"Enemy.h"
class CManager  
{
public:
	void CrossGame();  //ͨ����Ч
	void Draw();//��������ϰ�����ﻭ�ڱ���ͼ�ϣ�clonebg��
	void MonsterCheck();//�����⣨������ײ�����ϰ�����ײ��
	void PlantyCheck(); //�����ϰ����⣨������ײ��
	void GameRuning();//���״̬�ı亯��
	void GameStart();//���״̬�ı亯��
	void CManager::BgRolling();  //ͼƬ����
	void MyplayerMove();//�����ƶ�
	void Run();//������
	CManager();
	virtual ~CManager(); 
	enum GameState {  Gamestart,GameRunning,GameEnd };  //����״̬
private:
    GameState m_state;   
	CEnemy m_enemy;
	IplImage *img;
    CGameUI m_gameui;
    CMyplayer m_play;   //�����������
	CObstacle  m_obstacle; //�谭�Ｐ����� 
	CCollisionCheck  m_check;//�����ײ
	int m_mpo;          //��ͼ��������
	int m_speed;//ͼƬ�����ٶȼ������
    int m_distance;//��¼��ǰ��ǰ���˶��پ���
	int m_statedeep;//����״̬
	IplImage * m_endImage[5];  //��Ϸ����ͼƬ
	IplImage * m_startImage;//��Ϸ��ʼ����
	IplImage * m_house;//��Ϸ��β�ĳǱ�
	int m_lifetime;//�������ӵ�е���������
	IplImage *	m_speak;//��Ϸ˵��ͼƬ
};

#endif // !defined(AFX_MANAGER_H__841903BD_74CC_4EA8_815C_549A0CEF8826__INCLUDED_)

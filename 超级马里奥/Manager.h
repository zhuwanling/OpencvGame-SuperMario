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
	void CrossGame();  //通关特效
	void Draw();//人物，不动障碍物，怪物画在背景图上（clonebg）
	void MonsterCheck();//怪物检测（与人碰撞和与障碍物碰撞）
	void PlantyCheck(); //不动障碍物检测（与人碰撞）
	void GameRuning();//检测状态改变函数
	void GameStart();//检测状态改变函数
	void CManager::BgRolling();  //图片滚动
	void MyplayerMove();//人物移动
	void Run();//总运行
	CManager();
	virtual ~CManager(); 
	enum GameState {  Gamestart,GameRunning,GameEnd };  //运行状态
private:
    GameState m_state;   
	CEnemy m_enemy;
	IplImage *img;
    CGameUI m_gameui;
    CMyplayer m_play;   //我这个玛丽奥
	CObstacle  m_obstacle; //阻碍物及其敌人 
	CCollisionCheck  m_check;//检查碰撞
	int m_mpo;          //地图滚动参数
	int m_speed;//图片滚动速度及其参数
    int m_distance;//记录当前向前走了多少距离
	int m_statedeep;//下落状态
	IplImage * m_endImage[5];  //游戏结束图片
	IplImage * m_startImage;//游戏开始界面
	IplImage * m_house;//游戏结尾的城堡
	int m_lifetime;//马里奥所拥有的生命条数
	IplImage *	m_speak;//游戏说明图片
};

#endif // !defined(AFX_MANAGER_H__841903BD_74CC_4EA8_815C_549A0CEF8826__INCLUDED_)

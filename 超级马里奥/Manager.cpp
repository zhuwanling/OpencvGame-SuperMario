// Manager.cpp: implementation of the CManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Manager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern int speakflag;
CManager::CManager()
{
   img=cvLoadImage(".\\image\\firststage.png");
   m_endImage[0]=cvLoadImage(".\\image\\318757-130G00HI226.jpg");
   m_endImage[1]=cvLoadImage(".\\image\\gameend1.png");
    m_endImage[2]=cvLoadImage(".\\image\\gameend2.png");
   m_startImage=cvLoadImage(".\\image\\start.png");
   m_house=cvLoadImage(".\\image\\firstste.png" );
   m_speak=cvLoadImage(".\\image\\startspeak.png");
	m_gameui.SetBgImage(img);
  m_mpo=0;
  m_speed=10;
  m_distance=0;
  m_state=GameState::Gamestart;
  m_lifetime=3;
}

CManager::~CManager()
{
	cvReleaseImage(&m_endImage[0]);
    cvReleaseImage(&m_endImage[1]);
	cvReleaseImage(&m_endImage[2]);
	cvReleaseImage(&m_startImage);
	cvReleaseImage(&m_house);
	cvReleaseImage(&m_speak);
}

void CManager::Run()
{ 
        while(1)
		{
			if(speakflag==3)   //暂停按钮
			{
				 mciSendString("stop .\\vic\\mario.wav",0,0,0);
				cvWaitKey(0);
				speakflag=0;
				mciSendString("play .\\vic\\mario.wav",0,0,0);
			}
			else if(speakflag==2)  //游戏中结束按钮；
			{
				mciSendString("stop .\\vic\\mario.wav",0,0,0);
				speakflag=0;
			   break;
			}
		if(m_enemy.m_moveDis>10200)   //游戏通关标志
		{
	      CrossGame(); //结束动画显示；
		   break;
		}
			
			if(m_state==GameState::GameEnd)   //游戏没有通关
			{
			cvShowImage("xiao",m_endImage[0]); //GameOver 界面  停留一定时间后返回main函数；
			cvWaitKey(3000);
				break;
			}
		switch(m_state)
		{
	
		case GameState::Gamestart :            //游戏开始界面
			cvShowImage("xiao",m_startImage); 
			GameStart();   //获取键盘鼠标事件在改变游戏状态
			break;
		case GameState::GameRunning:  //游戏进行 
			cvWaitKey(18);
			MyplayerMove();   //人物移动
			MonsterCheck();   //怪物检测（与人碰撞和与障碍物碰撞）
			PlantyCheck();    //不动障碍物检测（与人碰撞）
			Draw();	           //将障碍物，怪物，人物画在背景上
			m_gameui.Show();
			GameRuning();      //游戏状态转换，
           	break;
		}
		}
}

void CManager::MyplayerMove()
{	
	IplImage *temp=m_gameui.GetImageBg();//获取每针显示的纯净背景
    m_play.Move(temp->width,temp->height);	 //人物移动
	if(m_play.GetMoveRightState())  //如果人物在中间前进就滚动背景
	{
		BgRolling();  
	}
}
void CManager::BgRolling()  //背景图片滚动
{
    int i,j;
	IplImage *temp2 =m_gameui.GetNOwbgImage();//标准图
	IplImage * temp=m_gameui.GameNowImage();//滚动图
	m_mpo-= m_speed;
	m_distance+=m_speed;
	if( m_mpo < 0) m_mpo += temp2->width;
	for( i = 85 ; i < temp2->height ; i++)
	{
		for( j = 0 ; j < temp2->width ; j ++)
		{
			int b = CV_IMAGE_ELEM(temp2,uchar,i,j*3+0);
			int g = CV_IMAGE_ELEM(temp2,uchar,i,j*3+1);
			int r = CV_IMAGE_ELEM(temp2,uchar,i,j*3+2);
			
			CV_IMAGE_ELEM(temp,uchar,i,((j+m_mpo)%temp2->width)*3+0) = b;
			CV_IMAGE_ELEM(temp,uchar,i,((j+m_mpo)%temp2->width)*3+1) = g;
			CV_IMAGE_ELEM(temp,uchar,i,((j+m_mpo)%temp2->width)*3+2) = r;
		}
	}
}
void On_mouse(int event, int x, int y, int flags, void *param)
{
    switch(event)
	{
		
	case  CV_EVENT_LBUTTONDOWN:   if(x>590&&x<780&&y<490&&y>430)   //点击里游戏说明按钮
							   {

								   speakflag=1;
							   }
		                       else if((x>140&&x<330&&y>430&&y<490)||(x>760&&x<840&&y>40&&y<80))
							   {
							   speakflag=2;                           
							   }
							   else if(x>660&&x<730&&y>40&&y<80)
							   {
							   speakflag=3;
							   }
		break;
	}
}
void CManager::GameStart()
{
	cvSetMouseCallback("xiao",On_mouse);  //开始界面获取鼠标状态（上一个函数）
	if(speakflag==1)                   
	{
		cvShowImage("xiao",m_speak);
		speakflag=0;
	}
	cvWaitKey(2000);
   	if(GetAsyncKeyState(' ')&0x8000)      //按空格开始游戏
	{
		mciSendString("play .\\vic\\mario.wav",0,0,0);
		m_state = GameState::GameRunning;
		return ;
	}

}


void CManager::GameRuning()
{
  if(!m_play.Life())       //如果当前我死了
  {
	  mciSendString("stop .\\vic\\mario.wav",0,0,0);
	  PlaySound(NULL,NULL,SND_PURGE);  //结束所有声音
	 m_lifetime--;
	  m_play.pos.y-=80;
	   PlaySound(".\\vic\\gameover.wav",NULL,SND_FILENAME | SND_ASYNC);  //死亡音乐；
	 while(m_play.pos.y+60<600)      //播放死亡特效
	 {
    IplImage * img=cvCloneImage(m_gameui.GameNowImage());
    m_enemy.ShowMonster(0,img);
    m_obstacle.Showblack(0,img);
	m_play.Draw(img);
	m_play.pos.y+=10;
	cvShowImage("xiao",img);
	cvReleaseImage(&img);
	cvWaitKey(18);
	 }
	 if(m_lifetime==0)   //三次命全部用完后结束游戏
	 {
	  m_state = GameState::GameEnd;
	 }
	 else                         //否则从当前位置上空复活
	 {
		 m_play.pos.y=0;
		 m_play.m_life=1;
		 m_play.m_judgejump=1;
		 if(m_lifetime==2) cvShowImage("xiao",m_endImage[2]);
		 else if(m_lifetime==1) cvShowImage("xiao",m_endImage[1]);
		 cvWaitKey(3000);
		 mciSendString("play .\\vic\\mario.wav",0,0,0);
	 }
  }
}

void CManager::PlantyCheck()
{
	m_statedeep=m_check.deep(m_play.GetNowPlayerPos(),&m_obstacle) ;  //下落检测（不在任何障碍上返回1）
	int checkstate=m_check.JudegCollision(m_play.GetNowPlayerPos(),&m_obstacle);//马里奥 与不动障碍物碰撞检测
	if(checkstate==4||checkstate==5)       //5代表碰撞带钱的砖块4代表与水泥块
	{
		if(checkstate==5)
		{
		   m_obstacle.ShowManey(m_gameui.GetNowClongbg());  //带钱砖块上方画星星特效
		}
     	m_play.SetMoveJump(1,m_statedeep);   //人物与其碰撞后的反应

	}
	if(checkstate==2)  //与水管碰撞
	{
	m_play.SetMoveJumpwell(1,m_statedeep); //人物与水管碰撞后的反应
	}
	if(checkstate==3)//与地上陷阱碰撞
	{
	m_play.SetMoveGrass(1);  //人物与陷阱碰撞后的反应
	}
	m_play.JudegeKong(m_statedeep);//开始判断人物此时是否要下落
}

void CManager::MonsterCheck()
{
  int i;
  for(i=0;i<m_enemy.m_nowShowManster.size();i++)
  {
	  if(m_enemy.m_nowShowManster[i].type==2)
	  {
        CvPoint  temp;
	    temp.x=m_enemy.m_nowShowManster[i].x;
    	temp.y=m_enemy.m_nowShowManster[i].y;	
	  int m_deepenemy=m_check.deep(temp,&m_obstacle);   //每个怪物的下落检测
      int m_state =m_check.JudegCollision(temp,&m_obstacle); //每个怪物与不动障碍物的检测
    	m_enemy.ChangeMoveState( i,m_state,m_deepenemy);      //怪物对不懂障碍物的反应
	  }
	  int playercenterposx=m_play.pos.x+30;                    //人物中心坐标
	  int playercenterposy=m_play.pos.y+30;
	  int monstercenterposx=m_enemy.m_nowShowManster[i].x+30;     //怪物中心坐标
	  int  monstercenterposy=m_enemy.m_nowShowManster[i].y+30;
	  if(abs(playercenterposx-monstercenterposx)<=45&&abs(playercenterposy-monstercenterposy)<=45)   //人物与怪物碰撞
	  {
		  if(m_enemy.m_nowShowManster[i].type==2&&m_play.pos.y+60<=m_enemy.m_nowShowManster[i].y+40)  //上面碰撞怪物死
		  {
			  m_enemy.m_nowShowManster[i].life=0;
			  m_enemy.m_nowShowManster[i].tiems=4;
			m_play.pos.y=m_enemy.m_nowShowManster[i].y-100;
		  }
		   else   //其他碰撞人物死
		   {
			   m_play.m_life=0;
		   }
	  }
  }
}
void CManager::Draw()
{
	m_enemy.ShowMonster(m_distance,m_gameui.GetNowClongbg());  //当前背景上画要显示的不动障碍物
    m_obstacle.Showblack(m_distance,m_gameui.GetNowClongbg()); //当前背景上画要显示的怪物
	 m_distance=0;
	m_play.Draw(m_gameui.GetNowClongbg());  //画人物；
}

void CManager::CrossGame()   //通关特效
{
	mciSendString("stop .\\vic\\mario.wav",0,0,0);
	PlaySound(".\\vic\\进入城堡.wav",NULL,SND_FILENAME | SND_ASYNC);
	int i=45;
	while(i--)
	{ 
		m_play.pos.x+=8;
		IplImage * img=cvCloneImage(m_house);
		m_play.Draw(img);
		cvShowImage("xiao",img);
		cvReleaseImage(&img);
		cvWaitKey(60);
	}
		cvWaitKey(2000);
}

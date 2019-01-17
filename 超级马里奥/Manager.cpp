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
			if(speakflag==3)   //��ͣ��ť
			{
				 mciSendString("stop .\\vic\\mario.wav",0,0,0);
				cvWaitKey(0);
				speakflag=0;
				mciSendString("play .\\vic\\mario.wav",0,0,0);
			}
			else if(speakflag==2)  //��Ϸ�н�����ť��
			{
				mciSendString("stop .\\vic\\mario.wav",0,0,0);
				speakflag=0;
			   break;
			}
		if(m_enemy.m_moveDis>10200)   //��Ϸͨ�ر�־
		{
	      CrossGame(); //����������ʾ��
		   break;
		}
			
			if(m_state==GameState::GameEnd)   //��Ϸû��ͨ��
			{
			cvShowImage("xiao",m_endImage[0]); //GameOver ����  ͣ��һ��ʱ��󷵻�main������
			cvWaitKey(3000);
				break;
			}
		switch(m_state)
		{
	
		case GameState::Gamestart :            //��Ϸ��ʼ����
			cvShowImage("xiao",m_startImage); 
			GameStart();   //��ȡ��������¼��ڸı���Ϸ״̬
			break;
		case GameState::GameRunning:  //��Ϸ���� 
			cvWaitKey(18);
			MyplayerMove();   //�����ƶ�
			MonsterCheck();   //�����⣨������ײ�����ϰ�����ײ��
			PlantyCheck();    //�����ϰ����⣨������ײ��
			Draw();	           //���ϰ��������ﻭ�ڱ�����
			m_gameui.Show();
			GameRuning();      //��Ϸ״̬ת����
           	break;
		}
		}
}

void CManager::MyplayerMove()
{	
	IplImage *temp=m_gameui.GetImageBg();//��ȡÿ����ʾ�Ĵ�������
    m_play.Move(temp->width,temp->height);	 //�����ƶ�
	if(m_play.GetMoveRightState())  //����������м�ǰ���͹�������
	{
		BgRolling();  
	}
}
void CManager::BgRolling()  //����ͼƬ����
{
    int i,j;
	IplImage *temp2 =m_gameui.GetNOwbgImage();//��׼ͼ
	IplImage * temp=m_gameui.GameNowImage();//����ͼ
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
		
	case  CV_EVENT_LBUTTONDOWN:   if(x>590&&x<780&&y<490&&y>430)   //�������Ϸ˵����ť
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
	cvSetMouseCallback("xiao",On_mouse);  //��ʼ�����ȡ���״̬����һ��������
	if(speakflag==1)                   
	{
		cvShowImage("xiao",m_speak);
		speakflag=0;
	}
	cvWaitKey(2000);
   	if(GetAsyncKeyState(' ')&0x8000)      //���ո�ʼ��Ϸ
	{
		mciSendString("play .\\vic\\mario.wav",0,0,0);
		m_state = GameState::GameRunning;
		return ;
	}

}


void CManager::GameRuning()
{
  if(!m_play.Life())       //�����ǰ������
  {
	  mciSendString("stop .\\vic\\mario.wav",0,0,0);
	  PlaySound(NULL,NULL,SND_PURGE);  //������������
	 m_lifetime--;
	  m_play.pos.y-=80;
	   PlaySound(".\\vic\\gameover.wav",NULL,SND_FILENAME | SND_ASYNC);  //�������֣�
	 while(m_play.pos.y+60<600)      //����������Ч
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
	 if(m_lifetime==0)   //������ȫ������������Ϸ
	 {
	  m_state = GameState::GameEnd;
	 }
	 else                         //����ӵ�ǰλ���Ͽո���
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
	m_statedeep=m_check.deep(m_play.GetNowPlayerPos(),&m_obstacle) ;  //�����⣨�����κ��ϰ��Ϸ���1��
	int checkstate=m_check.JudegCollision(m_play.GetNowPlayerPos(),&m_obstacle);//����� �벻���ϰ�����ײ���
	if(checkstate==4||checkstate==5)       //5������ײ��Ǯ��ש��4������ˮ���
	{
		if(checkstate==5)
		{
		   m_obstacle.ShowManey(m_gameui.GetNowClongbg());  //��Ǯש���Ϸ���������Ч
		}
     	m_play.SetMoveJump(1,m_statedeep);   //����������ײ��ķ�Ӧ

	}
	if(checkstate==2)  //��ˮ����ײ
	{
	m_play.SetMoveJumpwell(1,m_statedeep); //������ˮ����ײ��ķ�Ӧ
	}
	if(checkstate==3)//�����������ײ
	{
	m_play.SetMoveGrass(1);  //������������ײ��ķ�Ӧ
	}
	m_play.JudegeKong(m_statedeep);//��ʼ�ж������ʱ�Ƿ�Ҫ����
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
	  int m_deepenemy=m_check.deep(temp,&m_obstacle);   //ÿ�������������
      int m_state =m_check.JudegCollision(temp,&m_obstacle); //ÿ�������벻���ϰ���ļ��
    	m_enemy.ChangeMoveState( i,m_state,m_deepenemy);      //����Բ����ϰ���ķ�Ӧ
	  }
	  int playercenterposx=m_play.pos.x+30;                    //������������
	  int playercenterposy=m_play.pos.y+30;
	  int monstercenterposx=m_enemy.m_nowShowManster[i].x+30;     //������������
	  int  monstercenterposy=m_enemy.m_nowShowManster[i].y+30;
	  if(abs(playercenterposx-monstercenterposx)<=45&&abs(playercenterposy-monstercenterposy)<=45)   //�����������ײ
	  {
		  if(m_enemy.m_nowShowManster[i].type==2&&m_play.pos.y+60<=m_enemy.m_nowShowManster[i].y+40)  //������ײ������
		  {
			  m_enemy.m_nowShowManster[i].life=0;
			  m_enemy.m_nowShowManster[i].tiems=4;
			m_play.pos.y=m_enemy.m_nowShowManster[i].y-100;
		  }
		   else   //������ײ������
		   {
			   m_play.m_life=0;
		   }
	  }
  }
}
void CManager::Draw()
{
	m_enemy.ShowMonster(m_distance,m_gameui.GetNowClongbg());  //��ǰ�����ϻ�Ҫ��ʾ�Ĳ����ϰ���
    m_obstacle.Showblack(m_distance,m_gameui.GetNowClongbg()); //��ǰ�����ϻ�Ҫ��ʾ�Ĺ���
	 m_distance=0;
	m_play.Draw(m_gameui.GetNowClongbg());  //�����
}

void CManager::CrossGame()   //ͨ����Ч
{
	mciSendString("stop .\\vic\\mario.wav",0,0,0);
	PlaySound(".\\vic\\����Ǳ�.wav",NULL,SND_FILENAME | SND_ASYNC);
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

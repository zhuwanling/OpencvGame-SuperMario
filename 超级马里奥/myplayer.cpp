// myplayer.cpp: implementation of the myplayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myplayer.h"
extern CvPoint junmpposy[40];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define  jump 24
CMyplayer::CMyplayer()
{
    	m_life=1;
     pos.x=200;
	 pos.y=420;
	 m_speed=5;
	 m_pretime=clock();
	 m_playertrsfor[0]=cvLoadImage(".\\image\\0.png");
	 m_playertrsfor[1]=cvLoadImage(".\\image\\1.png");
	 m_playertrsfor[2]=cvLoadImage(".\\image\\2.png");
	 m_playertrsfor[3]=cvLoadImage(".\\image\\3.png");
	 m_playertrsfor[4]=cvLoadImage(".\\image\\4.png");   //载入马里奥行走图片集
	 m_playertrsfor[5]=cvLoadImage(".\\image\\5.png");
	 m_playertrsfor[6]=cvLoadImage(".\\image\\6.png");
     m_playertrsfor[7]=cvLoadImage(".\\image\\7.png");
	 m_playertrsfor[8]=cvLoadImage(".\\image\\8.png");
	 m_playertrsfor[9]=cvLoadImage(".\\image\\9.png");
	 m_player=m_playertrsfor[0];
	 m_jumpspeed=jump;
	 m_judgejump=0;
     m_stophight=0;
  m_houre=0;
	 m_pretime=0;
}
	 
CMyplayer::~CMyplayer()
{
    cvReleaseImage(&m_player);
	for(int i=0;i<=9;i++)
	{
		cvReleaseImage(&m_playertrsfor[i]);
	}
}
//绘制马里奥到bg
void CMyplayer::Draw(IplImage *bg)
{
   for(int i=0;i<m_player->height;i++)
   {
	   for(int j=0;j<m_player->width;j++)
	   {
		   
        int b =CV_IMAGE_ELEM(m_player,uchar,i,j*3+0);
		 int g=CV_IMAGE_ELEM(m_player,uchar,i,j*3+1);
		int r= CV_IMAGE_ELEM(m_player,uchar,i,j*3+2);
		if(b==255&&g==255&&b==255) continue;
		 CV_IMAGE_ELEM(bg,uchar,(i+pos.y),(j+pos.x)*3+0)=b;
		 CV_IMAGE_ELEM(bg,uchar,(i+pos.y),(j+pos.x)*3+1)=g;
		 CV_IMAGE_ELEM(bg,uchar,(i+pos.y),(j+pos.x)*3+2)=r;
	   }
   }
}

 void CMyplayer::Move(int width,int height)   //人物移动 
 {
	m_MoveRightstate=0;
	m_MoveLeftstate=0;
	static int t=-1;
	static int q=4;   //q,t用于判断当前应该显示那张行走图片；
	if(GetAsyncKeyState('A')&0x8000)
	{
	    q++;
		if(q>9)q=5;
		pos.x-=m_speed;
		m_player=m_playertrsfor[q];
		t=-1;
		m_MoveLeftstate=1;
	}
 else if(GetAsyncKeyState('D')&0X8000)
	{
		 t++;
		 if(t>4)t=0;
		 m_player=m_playertrsfor[t];
           pos.x+=m_speed;
		   q=4;
		  if(pos.x>400)   //改变标记屏幕需要滚动      
		  {
			  pos.x-=m_speed;
			  m_MoveRightstate=1;
		  }
	}
  m_houre=clock();
 if	(GetAsyncKeyState('W')&0X8000&&!m_judgejump&&m_houre-m_pretime>400)
	{
		CreateThread(0,0,JumpSound,0,0,0);
	   m_pretime=m_houre;
		m_judgejump=1;
		m_jumpspeed=jump;	  
	} 
	if(m_judgejump)                           //在跳是人物改变
	{
		if(m_jumpspeed>-20)
		m_jumpspeed-=2;
		pos.y-=m_jumpspeed;
		if(pos.y>=420)   //如果回到地面(450)或则上到怪物 停止；
		{
			m_stophight=0;
	       pos.y=420;
		  m_judgejump=0;
		  m_jumpspeed=jump;   
		}
	}
	 if(pos.x<0) pos.x=0;                       //出界判断；
	 if(pos.x>width-1-m_player->width) pos.x=width-1-m_player->width;
	 if(pos.y<0) pos.y=0;
	 if(pos.y>height-1)  pos.y=height-1;
}

 int CMyplayer::GetMoveRightState()
{
  return m_MoveRightstate;
}

int CMyplayer::Judegejump()
{
   return m_judgejump;
}

int CMyplayer::GetMoveLeftState()
{
    return m_MoveLeftstate;
}

CvPoint CMyplayer::GetNowPlayerPos()
{
        return pos;
}

void CMyplayer::SetMoveJump(int state,int deepstate)
{
	if(state)  //如果存在碰撞
	{ 
		int i=0;
		while(junmpposy[i].x!=0)
		{

		if(pos.y>junmpposy[i].y+30)
	   {
		   if(m_jumpspeed>0){ m_jumpspeed=-m_jumpspeed+2;}
		   
	   } 
       
	   else if(pos.y+60<junmpposy[i].y+30&&!deepstate)
	   {
		   m_judgejump=0;
	       m_jumpspeed=jump;
		   pos.y=junmpposy[i].y-60;
		   m_stophight=1;
	   }
	  
	  else if(pos.x<junmpposy[i].x&&pos.x+60>junmpposy[i].x+10&&pos.y+60>junmpposy[i].y)
	   {
		   pos.x-=m_speed;
  
	   }
	   else if(pos.x+60>junmpposy[i].x+60&&pos.x<junmpposy[i].x+50&&pos.y+60>junmpposy[i].y)
	   {
		   pos.x+=m_speed;
	   }
	   i++;
		}
	}
}

void CMyplayer::JudegeKong(int ko)  //人物的下落
{
      if(ko&&pos.x!=420&&m_stophight&&!m_judgejump)
		{
        m_judgejump=1;
		m_jumpspeed=0;
		 m_stophight=0;
		}
}


void CMyplayer::SetMoveJumpwell(int state, int deepstate) //与管道的碰撞人物改变
{

	if(state)  //如果存在碰撞
	{ 
		int i=0;
		while(junmpposy[i].x!=0)
		{
	      if(pos.y+60<junmpposy[i].y+40&&!deepstate)
			{
				m_judgejump=0;
				m_jumpspeed=jump;
				pos.y=junmpposy[i].y-60;
				m_stophight=1;
			}
			
			else if(pos.x<junmpposy[i].x&&pos.x+60>junmpposy[i].x+10&&pos.y+60>junmpposy[i].y)
			{
				pos.x-=m_speed;
			}
			else if(pos.x+60>junmpposy[i].x+108&&pos.x<junmpposy[i].x+108-10&&pos.y+60>junmpposy[i].y)
			{
				pos.x+=m_speed;
			}
			i++;
		}
	}
}

void CMyplayer::SetMoveGrass(int state)//与陷阱的碰撞人物改变
{
     if(state)
	 {
	  m_life=0;
	 }
}

int CMyplayer::Life()  //获取人物生命状态
{
return m_life;
}
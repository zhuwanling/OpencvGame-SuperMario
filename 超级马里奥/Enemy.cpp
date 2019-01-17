// Enemy.cpp: implementation of the CEnemy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Enemy.h"
#include<iostream>
#include<fstream>
extern CvPoint junmpposy[40];
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEnemy::CEnemy()
{
	m_moveDis=0;

	m_mansterImage[0]=cvLoadImage(".\\image\\flower1.png");
	m_mansterImage[1]=cvLoadImage(".\\image\\flower2.png");
	m_mansterImage[2]=cvLoadImage(".\\image\\Mushroom_01.png");
	m_mansterImage[3]=cvLoadImage(".\\image\\Mushroom_02.png");
	m_mansterImage[4]=cvLoadImage(".\\image\\Mushroom_03.png");
	int i=-1;
	ifstream infile("Monster.txt");                                  //载入所有怪物
	while(!infile.eof())
	{ 
		i++;
		infile>>m_allMonster[i][0]>>m_allMonster[i][1]>>m_allMonster[i][2];
		
	}
	infile.close();
	m_index=0;
}

CEnemy::~CEnemy()
{
  cvReleaseImage(&m_mansterImage[0]);
  cvReleaseImage(&m_mansterImage[1]);
  cvReleaseImage(&m_mansterImage[2]);
  cvReleaseImage(&m_mansterImage[3]);
  cvReleaseImage(&m_mansterImage[4]);
}

void CEnemy::ShowMonster(int distance,IplImage *clonebg)
{ 

	int i;
   for(i=m_index;i<200;i++)                                //载入当前要显示的怪物
	  {
	   int flag=0;
	   if(m_allMonster[i][0]*60-m_moveDis<900&&m_allMonster[i][0]*60-m_moveDis>0)
	   {
		   moster temp;
		   temp.x=m_allMonster[i][0]*60-m_moveDis;
		   temp.y=m_allMonster[i][1]*60;
		   temp.life=1;
		   temp.movespeed=10;
		   temp.type=m_allMonster[i][2];
		   temp.num=0;
		   if(m_allMonster[i][2]==0) 
		   {
			   temp.tiems=0;
			   temp.x+=15;
		   }
		  else if(m_allMonster[i][2]==2)  
		   {
			   temp.tiems=2;
		   }
		   m_nowShowManster.push_back(temp);
		   flag=1;
	   }
	   if(!flag)
	   {
	   break;
	   }
   }
   m_index=i;
   m_moveDis+=distance;
   ShowMansterImage(distance,clonebg);     //在背景上画出来       
   for(i=0;i<m_nowShowManster.size();i++)    //消除已经出界的怪物
   {
	   if(m_nowShowManster[i].x<=-60||m_nowShowManster[i].life==0)  
	   {
		   if(m_nowShowManster[i].life==0)
		   {
			   PlaySound(".\\vic\\caidren.wav",NULL,SND_FILENAME | SND_ASYNC);
		   }
		   m_nowShowManster.erase(m_nowShowManster.begin()+i);
	   } 
	   m_nowShowManster[i].x=m_nowShowManster[i].x-distance;
	   m_nowShowManster[i].num++;
	   if(m_nowShowManster[i].tiems==0&&m_nowShowManster[i].num%4==0)  //实现花的上下移动
	   {
		   if(m_nowShowManster[i].num%32==0)
		   {
		   m_nowShowManster[i].tiems=1;
		   m_nowShowManster[i].num=0;
		   }
		   m_nowShowManster[i].y+=15;
	   }
	   else if(m_nowShowManster[i].tiems==1&&m_nowShowManster[i].num%4==0)
	   {
	      
		    if(m_nowShowManster[i].num%32==0)
			{
           m_nowShowManster[i].tiems=0;
		    m_nowShowManster[i].num=0;
			}
		  m_nowShowManster[i].y-=15;
	   }
	    else if(m_nowShowManster[i].tiems==2&&m_nowShowManster[i].num%5==0)  //实现蘑菇怪的走动图片转换
		{
		
               m_nowShowManster[i].tiems=3;
			   m_nowShowManster[i].x-=m_nowShowManster[i].movespeed;
		}
		else if(m_nowShowManster[i].tiems==3&&m_nowShowManster[i].num%5==0)
		{
		
			m_nowShowManster[i].tiems=2;
			m_nowShowManster[i].x-=m_nowShowManster[i].movespeed;
		}
		
   }

}

void CEnemy::ShowMansterImage(int distance, IplImage *clonebg)
{
  int i,j,k;
  IplImage *img;

  for(i=0;i<m_nowShowManster.size();i++)
  {  
	  if(m_nowShowManster[i].tiems==0)  img=m_mansterImage[0];
	  else if(m_nowShowManster[i].tiems==1) img=m_mansterImage[1];
	  else if(m_nowShowManster[i].tiems==2)  img=m_mansterImage[2];
	  else if(m_nowShowManster[i].tiems==3) img=m_mansterImage[3];
	  else if(m_nowShowManster[i].tiems==4) img=m_mansterImage[4];
  for(j=0;j<img->height;j++)
		{ 
	  
	  for(k=0;k<img->width;k++)
	  {  
	    if((k+m_nowShowManster[i].x-distance)<0||(k+m_nowShowManster[i].x-distance)>900||(j+m_nowShowManster[i].y)<0||(j+m_nowShowManster[i].y)>=598) continue; //不打印出界部分
		  int b = CV_IMAGE_ELEM(img,uchar,j,k*3+0);
		  int g = CV_IMAGE_ELEM(img,uchar,j,k*3+1);
		  int r = CV_IMAGE_ELEM(img,uchar,j,k*3+2);
		  if(r==255&&b==255&&g==255) continue;
		  CV_IMAGE_ELEM(clonebg,uchar,j+m_nowShowManster[i].y,(k+m_nowShowManster[i].x-distance)*3+0) = b;
		  CV_IMAGE_ELEM(clonebg,uchar,j+m_nowShowManster[i].y,(k+m_nowShowManster[i].x-distance)*3+1) = g;
		  CV_IMAGE_ELEM(clonebg,uchar,j+m_nowShowManster[i].y,(k+m_nowShowManster[i].x-distance)*3+2) = r;
	  } 
		}  
  }
}

void CEnemy::ChangeMoveState(int wh,int state,int deepstate )   //改变怪物与静态障碍物碰撞后的路径
{
	int i=0;
    if(state==4||state==2)   //怪物与砖块的碰撞及其改变
	{
		while(junmpposy[i].x!=0)
		{
			
		     if(m_nowShowManster[wh].y+60<junmpposy[i].y+30&&!deepstate)
			 {
		    	m_nowShowManster[wh].y=junmpposy[i].y-60;
			 }
			
			else if(m_nowShowManster[wh].x<junmpposy[i].x&&m_nowShowManster[wh].x+60>junmpposy[i].x+10&&m_nowShowManster[wh].y+60>junmpposy[i].y)
			{
				m_nowShowManster[wh].movespeed=-m_nowShowManster[wh].movespeed;
				
			}
			else if(m_nowShowManster[wh].x+60>junmpposy[i].x+60&&m_nowShowManster[wh].x<junmpposy[i].x+110&&m_nowShowManster[wh].y+60>junmpposy[i].y)
			{
				 	m_nowShowManster[wh].movespeed=-m_nowShowManster[wh].movespeed;
			}
			i++;
		}
	}
	if(state==3)   //怪物与陷阱碰撞死亡
	{
        m_nowShowManster[wh].y+=20;
		m_nowShowManster[wh].life=0;
	}
		if(deepstate&&m_nowShowManster[wh].y<420)  //怪物在空中，（要落下）
		{
		   m_nowShowManster[wh].y+=10;
		   if(m_nowShowManster[wh].y>420)
		   {
			   m_nowShowManster[wh].y=420;
		   }
		}
}
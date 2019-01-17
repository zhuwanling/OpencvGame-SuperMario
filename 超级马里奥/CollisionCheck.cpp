// CollisionCheck.cpp: implementation of the CCollisionCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CollisionCheck.h"
extern CvPoint junmpposy[40];
extern int score;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCollisionCheck::CCollisionCheck()
{
}

CCollisionCheck::~CCollisionCheck()
{
} 

int CCollisionCheck::JudegCollision(CvPoint playerPos,CObstacle *temp)    //传进的坐标与静态障碍物的碰撞检测
{
     int i,num=0; 
	 junmpposy[0].x=0; //每次检测变为
	 int len=0;
	 for(i=0;i<temp->m_Ob.size();i++) 
	 {
          int type=temp->m_Ob[i].tepy;
		 if(type==2)                   //与管道的检测
		 {  		  
		  if( CheckWell(playerPos,temp,i,len))
		  {
			  num=2;
			  len++;	 
		  }
		  continue;
		 }
		 else if(type==3)                     //与陷阱的检测
		 {
			 if(	CheckGross(playerPos,temp,i,len))
			 {
				 num=3;
				 len++;
			 }
			 continue;
		 }
		 if(abs(temp->m_Ob[i].x-playerPos.x)>60||abs(temp->m_Ob[i].y-playerPos.y)>60)   //只检测在马里奥周围的砖块
		 {
			 continue;
		 }
		 int playercenterx=playerPos.x+30;
		 int  playercentery=playerPos.y+30;
		
		 int blockcenterx=temp->m_Ob[i].x+30;
		 int blockcentery=temp->m_Ob[i].y+30;
		  if (abs(playercenterx-blockcenterx)<60&&abs(playercentery-blockcentery)<60)
		  { 
			
			  if(temp->m_Ob[i].tepy==4)       //金币的消失
			  {
				  temp->m_Ob[i].times--;
				  PlaySound(".\\vic\\金币.wav",NULL,SND_FILENAME | SND_ASYNC);
				  if(temp->m_Ob[i].times==1)
				  {
                       score+=10;
					  temp->m_Ob[i].life=0;
				  }
				  continue;
			  }
			 else  if(temp->m_Ob[i].tepy==6  && playerPos.y>temp->m_Ob[i].y&&playerPos.y<temp->m_Ob[i].y+60&&playerPos.x< temp->m_Ob[i].x+40&&playerPos.x+40>temp->m_Ob[i].x)
			  {
				 temp->m_Ob[i].times=9;   //泥土的消失
			   temp->m_Ob[i].life=0;
			  }
			else if(temp->m_Ob[i].tepy==5&&playerPos.y>temp->m_Ob[i].y&&playerPos.y<temp->m_Ob[i].y+60&&playerPos.x< temp->m_Ob[i].x+40&&playerPos.x+40>temp->m_Ob[i].x)  
			{
				temp->m_Ob[i].times--;             //带钱砖块的消失
				if(	temp->m_Ob[i].times>0)
				PlaySound(".\\vic\\金币.wav",NULL,SND_FILENAME | SND_ASYNC);
				if(temp->m_Ob[i].times>0)
				{
				junmpposy[len].x=temp->m_Ob[i].x;
			    junmpposy[len++].y=temp->m_Ob[i].y;	  
				num=5;
				continue;
				}
			}
			if(temp->m_Ob[i].x==0) temp->m_Ob[i].x+=1;
			  junmpposy[len].x=temp->m_Ob[i].x;             //记录碰撞物的坐标
			  junmpposy[len++].y=temp->m_Ob[i].y;	   
		       num=4;
		  }


	 }
	
	if(len==0) return 0;
		junmpposy[len].x=0;  //方便检测末尾
 		return num;
}

int CCollisionCheck::deep(CvPoint playerpos, CObstacle *temp)   //检测传入怪物或玛丽奥是否在静态障碍物上
{
   int i;
   for(i=0;i<temp->m_Ob.size();i++)
   {
	 
	  
	   if(temp->m_Ob[i].tepy==3&&playerpos.x<(temp->m_Ob[i].x+120)&&(playerpos.y-temp->m_Ob[i].y)>=-60&&(playerpos.y-temp->m_Ob[i].y)<=0&&playerpos.x+60>temp->m_Ob[i].x+15) 
	   {
		   return 0;
	   }
	    else if(temp->m_Ob[i].tepy==2&&playerpos.x<(temp->m_Ob[i].x+93)&&(playerpos.y-temp->m_Ob[i].y)>=-60&&(playerpos.y-temp->m_Ob[i].y)<=0&&playerpos.x+60>temp->m_Ob[i].x+15)
	   {
		   return 0;
		} 
		else if(abs(temp->m_Ob[i].x-playerpos.x)>60||abs(temp->m_Ob[i].y-playerpos.y)>60)
		{
			continue;
		}
	   else if(playerpos.x<(temp->m_Ob[i].x+45)&&(playerpos.y-temp->m_Ob[i].y)>=-60&&(playerpos.y-temp->m_Ob[i].y)<=0&&playerpos.x+60>temp->m_Ob[i].x+15) 
	   {
		   return 0;
	   }
	  
   }
   return 1;
}
  

   CCollisionCheck::CheckWell(CvPoint playerps, CObstacle *temp,int i,int len)   //管道碰撞检测函数
{
		if(abs(temp->m_Ob[i].x+55-playerps.x)>116||abs(temp->m_Ob[i].y-playerps.y)>60)
		{
			return 0;
		 }
		int playercenterx=playerps.x+30;
		int  playercentery=playerps.y+30;
		int blockcenterx=temp->m_Ob[i].x+54;
		int blockcentery=temp->m_Ob[i].y+59;
		if (abs(playercenterx-blockcenterx)<=84&&abs(playercentery-blockcentery)<=89)
		{ 
			junmpposy[len].y=temp->m_Ob[i].y;
			junmpposy[len++].x=temp->m_Ob[i].x; 
			return 2;
		}
	return 0;
}

int CCollisionCheck::CheckGross(CvPoint playerps, CObstacle *temp,int i,int len)   //陷阱碰撞检测函数
{
		if(abs(temp->m_Ob[i].x+60-playerps.x)>120||abs(temp->m_Ob[i].y-playerps.y)>65)
		{	
			
			return 0;
		 }
		int playercenterx=playerps.x+30;
		int  playercentery=playerps.y+30;
		int blockcenterx=temp->m_Ob[i].x+60;
		int blockcentery=temp->m_Ob[i].y+60;
		if (abs(playercenterx-blockcenterx)<=40&&abs(playercentery-blockcentery)<=90)
		{ 
		
		         return 3;
		}
	
	return 0;
}

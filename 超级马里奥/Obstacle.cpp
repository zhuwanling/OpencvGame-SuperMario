// Obstacle.cpp: implementation of the CObstacle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Obstacle.h"
#include<iostream>
extern CvPoint junmpposy[40];
#include<fstream>
extern int score;
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObstacle::CObstacle()
{  

	int i=-1;
	m_Movedis=0;
	m_index=0;
  m_obImage[0]=cvLoadImage(".\\image\\2.jpg");//block
   m_obImage[1]=cvLoadImage(".\\image\\fuiwfhwu.png");//well
   m_obImage[2]=cvLoadImage(".\\image\\age.jpg");//grass
   	m_obImage[3]=cvLoadImage(".\\image\\coin1.png");//maney1
	m_obImage[4]=cvLoadImage(".\\image\\coin2.png");//many2
	m_obImage[5]=cvLoadImage(".\\image\\coin3.png");//maney3
	m_obImage[6]=cvLoadImage(".\\image\\ob4.png");//maneyblock1
	m_obImage[7]=cvLoadImage(".\\image\\kfowjfjao.jpg");//maneyblock2;
	m_obImage[8]=cvLoadImage(".\\image\\num.jpg");//numblock 6 ;
	m_obImage[9]=cvLoadImage(".\\image\\50f527a.png");
	m_obImage[10]=cvLoadImage(".\\image\\ob12.png");
	ifstream infile("map1.txt");
	while(!infile.eof())
	{ 
		i++;
		infile>>m_AllObstacle[i][0]>>m_AllObstacle[i][1]>> m_AllObstacle[i][2];
		
	}
	infile.close();
	
}

CObstacle::~CObstacle()
{
	cvReleaseImage(&m_obImage[0]);
	cvReleaseImage(&m_obImage[1]);
	cvReleaseImage(&m_obImage[2]);
	cvReleaseImage(&m_obImage[3]);
	cvReleaseImage(&m_obImage[4]);
	cvReleaseImage(&m_obImage[5]);
	cvReleaseImage(&m_obImage[6]);
	cvReleaseImage(&m_obImage[7]);
	cvReleaseImage(&m_obImage[8]);  
	cvReleaseImage(&m_obImage[9]);  
		cvReleaseImage(&m_obImage[10]); 
}

void CObstacle::Showblack(int distance,IplImage *clonebg)
{
	int i;
	  m_Movedis+=distance;//移动的总距离；
	  for(i=m_index;i<2000;i++)//重所有障碍物中载入现在要显示的障碍物
	  {
		
		  int flag=0;
		  if((m_AllObstacle[i][0]*60-m_Movedis)<900&&m_AllObstacle[i][0]*60-m_Movedis>0)
		  { 
			  Obtepy temp;
			  temp.x=m_AllObstacle[i][0]*60-m_Movedis;
			  temp.y=m_AllObstacle[i][1]*60;
			  temp.tepy=m_AllObstacle[i][2];
			  temp.life=1;
			  temp.change=0;
			  if(m_AllObstacle[i][2]==1)  {  m_Ob.push_back(temp);}//转快
			 else if(m_AllObstacle[i][2]==2)  { m_Ob.push_back(temp);}//well
			  else if(m_AllObstacle[i][2]==3){ m_Ob.push_back(temp);}//grass
			  else if(m_AllObstacle[i][2]==4)
			  {
				  
				   temp.times=3;
                   m_Ob.push_back(temp);
			  }
			  else if(m_AllObstacle[i][2]==5)
			  {
				  
				  temp.times=5;
				  m_Ob.push_back(temp);

			  }
			  else if(m_AllObstacle[i][2]==6)
			  {
				  temp.times=8;
				  m_Ob.push_back(temp);
			  }
			 flag=1;
		  }
		  if(!flag) break;
	  }
	     m_index=i;    //记录加载到哪儿了
		 ShowObstacle(distance,clonebg);//显示障碍物
		  for(i=0;i<m_Ob.size();i++)    //消除已经出界的障碍物
		  {
			   
			   
			  if((m_Ob[i].tepy!=3&&m_Ob[i].x<=-60)||m_Ob[i].life==0||(m_Ob[i].tepy==3&&m_Ob[i].x<=-120))
			  {
				  if(m_Ob[i].life==0&&m_Ob[i].tepy==6)
				  {
                      PlaySound(".\\vic\\顶破砖.wav",NULL,SND_FILENAME | SND_ASYNC);
					  score+=10;
				  }
				  m_Ob.erase(m_Ob.begin()+i);
			  }
			  m_Ob[i].x=m_Ob[i].x-distance;
		 }
	
}

 void CObstacle::ShowObstacle(int distance, IplImage *clonebg)
 {
	 int i,j,k;
	 IplImage *img;
	 for(i=0;i<m_Ob.size();i++)
	 {
		 if(m_Ob[i].tepy==1)  img=m_obImage[0];
		 else if(m_Ob[i].tepy==2)  img=m_obImage[1];
		 else if(m_Ob[i].tepy==3) img=m_obImage[2];
		 else if(m_Ob[i].tepy==4)
		 {
			 if(m_Ob[i].times==3) img=m_obImage[3];
			 else if(m_Ob[i].times==2) img=m_obImage[4];
             else if(m_Ob[i].times==1) img=m_obImage[5];
		 }
		 else if(m_Ob[i].tepy==5)
		 {
			 if(m_Ob[i].times>1)
			 {
				m_Ob[i].change++;
				  if(m_Ob[i].change%4==0)
				 img=m_obImage[6];
				  else 
				 img=m_obImage[10];
			 }
			 else img=m_obImage[7];
		 }
		 else if(m_Ob[i].tepy==6)
		 {
			 if(m_Ob[i].times==8)
                  img=m_obImage[8];
			 else  img=m_obImage[9];
		 }
		 for(j=0;j<img->height;j++)
		 { 
			 for(k=0;k<img->width;k++)
			 {
				 if(k+m_Ob[i].x-distance<0||k+m_Ob[i].x-distance>900||j+m_Ob[i].y<0||j+m_Ob[i].y>=598) continue; //不打印出界部分
				 int b = CV_IMAGE_ELEM(img,uchar,j,k*3);
				 int g = CV_IMAGE_ELEM(img,uchar,j,k*3+1);
				 int r = CV_IMAGE_ELEM(img,uchar,j,k*3+2);
				 if(r==255&&b==255&&g==255) continue;
				 CV_IMAGE_ELEM(clonebg,uchar,j+m_Ob[i].y,(k+m_Ob[i].x-distance)*3+0) = b;
				 CV_IMAGE_ELEM(clonebg,uchar,j+m_Ob[i].y,(k+m_Ob[i].x-distance)*3+1) = g;
				 CV_IMAGE_ELEM(clonebg,uchar,j+m_Ob[i].y,(k+m_Ob[i].x-distance)*3+2) = r;
			 } 
		 }        
	 }
 }
 void CObstacle::ShowManey( IplImage *clonebg)
 {
	 int j,k;
	 IplImage *img=m_obImage[3];
	 for(j=0;j<img->height;j++)
		 { 
			 for(k=0;k<img->width;k++)
			 {
				 int b = CV_IMAGE_ELEM(img,uchar,j,k*3);
				 int g = CV_IMAGE_ELEM(img,uchar,j,k*3+1);
				 int r = CV_IMAGE_ELEM(img,uchar,j,k*3+2);
				 if(r==255&&b==255&&g==255) continue;
				 CV_IMAGE_ELEM(clonebg,uchar,j+junmpposy[0].y-60,(k+junmpposy[0].x)*3+0) = b;
				 CV_IMAGE_ELEM(clonebg,uchar,j+junmpposy[0].y-60,(k+junmpposy[0].x)*3+1) = g;
				 CV_IMAGE_ELEM(clonebg,uchar,j+junmpposy[0].y-60,(k+junmpposy[0].x)*3+2) = r;
			 } 
		 }        
 }

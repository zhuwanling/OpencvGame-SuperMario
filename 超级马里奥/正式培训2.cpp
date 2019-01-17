// 正式培训2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"Manager.h"
CvPoint junmpposy[40];  //记录碰撞物体坐标
 int speakflag;   //游戏开始界面是否显示说明界面的标志
 int key1;   //游戏结束后是从新开始还是结束的标志
 int score;   //分数
 void cvText(IplImage* img, const char* text, int x, int y)      //打印分数
 {  
	 CvFont font;  
	 double hscale = 1.0; //hscale字体宽度。如果等于1.0f，字符的宽度是最初的字体宽度 
	 double vscale = 1.0; //scale字体高度。如果等于1.0f，字符的高度是最初的字体高度 
	 int linewidth = 2;  
	 cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC,hscale,vscale,0,linewidth);//CV_FONT_HERSHEY_SCRIPT_SIMPLEX正常字体
	 CvScalar textColor =cvScalar(0,0,0);  
	 CvPoint textPos =cvPoint(x, y);  
	 cvPutText(img,text,textPos,&font,textColor);  
}  
void RestartOn_mouse(int event, int x, int y, int flags, void *param)
{
	extern int key1;
    switch(event)
	{
		
		case  CV_EVENT_LBUTTONDOWN: 
			                if(x>266&&x<580&&y<242&&y>164)
							   {
								   key1=2;
							   }
			                  
		                       else if(x>267&&x<588&&y<419&&y>327)
							   {
								   key1=1;
							   }
		break;
	}
}
int main(int argc, char* argv[])
{
    IplImage * restart=cvLoadImage(".\\image\\END.png");
	cvNamedWindow("xiao",0);
	cvMoveWindow("xiao",200,300);
	int flag=1;
	while(1)                  
	{
		IplImage * img=cvCloneImage(restart);  //一个临时图像避免答应分数污染
	 if(flag==1)   //进入游戏
	 {
		 key1=0;
		 score=0;
      CManager game;
	  game.Run();
	 
	  flag=0;
	 } //结束一场游戏
	 
	  char string[20];
	  _itoa(score,string,10);//把分数转换为char型 10进制
	  cvText(img,"score:",320,120);       //游戏结束后打印分数
	  cvText(img,string,450,120);   
	 cvShowImage("xiao",img);
	 cvReleaseImage(&img);
	 cvSetMouseCallback("xiao",RestartOn_mouse);   //获取用户在结尾界面的点击情况
	if(key1==1)          //表明点击从新开始
	{
	   flag=1;
	}
	else if(key1==2)   //表明点击结束游戏；
	{
	 break;
	}
	cvWaitKey(20);
	}
	cvReleaseImage(&restart);
	cvDestroyAllWindows();
	return 0;
}

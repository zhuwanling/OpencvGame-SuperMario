// ��ʽ��ѵ2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"Manager.h"
CvPoint junmpposy[40];  //��¼��ײ��������
 int speakflag;   //��Ϸ��ʼ�����Ƿ���ʾ˵������ı�־
 int key1;   //��Ϸ�������Ǵ��¿�ʼ���ǽ����ı�־
 int score;   //����
 void cvText(IplImage* img, const char* text, int x, int y)      //��ӡ����
 {  
	 CvFont font;  
	 double hscale = 1.0; //hscale�����ȡ��������1.0f���ַ��Ŀ��������������� 
	 double vscale = 1.0; //scale����߶ȡ��������1.0f���ַ��ĸ߶������������߶� 
	 int linewidth = 2;  
	 cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC,hscale,vscale,0,linewidth);//CV_FONT_HERSHEY_SCRIPT_SIMPLEX��������
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
		IplImage * img=cvCloneImage(restart);  //һ����ʱͼ������Ӧ������Ⱦ
	 if(flag==1)   //������Ϸ
	 {
		 key1=0;
		 score=0;
      CManager game;
	  game.Run();
	 
	  flag=0;
	 } //����һ����Ϸ
	 
	  char string[20];
	  _itoa(score,string,10);//�ѷ���ת��Ϊchar�� 10����
	  cvText(img,"score:",320,120);       //��Ϸ�������ӡ����
	  cvText(img,string,450,120);   
	 cvShowImage("xiao",img);
	 cvReleaseImage(&img);
	 cvSetMouseCallback("xiao",RestartOn_mouse);   //��ȡ�û��ڽ�β����ĵ�����
	if(key1==1)          //����������¿�ʼ
	{
	   flag=1;
	}
	else if(key1==2)   //�������������Ϸ��
	{
	 break;
	}
	cvWaitKey(20);
	}
	cvReleaseImage(&restart);
	cvDestroyAllWindows();
	return 0;
}

// GameUI.cpp: implementation of the CGameUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameUI.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGameUI::CGameUI()
{
}

CGameUI::~CGameUI()
{
  cvReleaseImage(&m_bg);
  cvReleaseImage(&m_rollbg);
  cvReleaseImage(&m_clongbg);
  
}

void CGameUI::Show()
{
   cvShowImage("xiao",m_clongbg);
}

void CGameUI::SetBgImage(IplImage *img)
{
  m_bg=img;
   m_clongbg=cvCreateImage(cvGetSize(m_bg),m_bg->depth,m_bg->nChannels);
   m_rollbg=cvCloneImage(m_bg);
}

IplImage * CGameUI::GetImageBg()  //�õ�һ��ÿ����ʾ�Ĵ�������ͼ
{
   cvCopy(m_rollbg,m_clongbg,NULL);
   return m_clongbg;
}

IplImage * CGameUI::GameNowImage()//�õ�roll�������ı���ͼ������ͼ��
{
    return m_rollbg;
}

IplImage * CGameUI::GetNOwbgImage()//�õ���ͼ�������κθı��ͼ������ͼ
{
    return m_bg;
}


IplImage * CGameUI::GetNowClongbg()  //��ȡ��ǰҪ��ʾ�ı���ͼ
{
    return m_clongbg;
}

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

IplImage * CGameUI::GetImageBg()  //得到一张每针显示的纯净背景图
{
   cvCopy(m_rollbg,m_clongbg,NULL);
   return m_clongbg;
}

IplImage * CGameUI::GameNowImage()//得到roll（滚动的背景图）背景图；
{
    return m_rollbg;
}

IplImage * CGameUI::GetNOwbgImage()//得到底图（不做任何改变的图）背景图
{
    return m_bg;
}


IplImage * CGameUI::GetNowClongbg()  //获取当前要显示的背景图
{
    return m_clongbg;
}

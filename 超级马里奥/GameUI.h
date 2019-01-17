// GameUI.h: interface for the CGameUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEUI_H__3EEF3F3B_232D_444B_8264_396955ECF370__INCLUDED_)
#define AFX_GAMEUI_H__3EEF3F3B_232D_444B_8264_396955ECF370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<cv.h>
#include<highgui.h>
class CGameUI  
{
public:
	IplImage * GetNowClongbg();//获取当前要显示的背景图
	IplImage * GetNOwbgImage();////得到底图（不做任何改变的图）背景图
	IplImage * GameNowImage();//获得每一帧需求的纯净背景图
	IplImage * GetImageBg();  //获得bg
	void SetBgImage(IplImage *img);  //设置背景图片
	void Show();  //显示clongbg
	CGameUI();
	virtual ~CGameUI();
private:
	IplImage *m_bg;//标准底图
	IplImage * m_rollbg;//通过标准地图来实现的滚动图
		IplImage * m_clongbg;//每一针显示的背景图
};

#endif // !defined(AFX_GAMEUI_H__3EEF3F3B_232D_444B_8264_396955ECF370__INCLUDED_)

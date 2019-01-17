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
	IplImage * GetNowClongbg();//��ȡ��ǰҪ��ʾ�ı���ͼ
	IplImage * GetNOwbgImage();////�õ���ͼ�������κθı��ͼ������ͼ
	IplImage * GameNowImage();//���ÿһ֡����Ĵ�������ͼ
	IplImage * GetImageBg();  //���bg
	void SetBgImage(IplImage *img);  //���ñ���ͼƬ
	void Show();  //��ʾclongbg
	CGameUI();
	virtual ~CGameUI();
private:
	IplImage *m_bg;//��׼��ͼ
	IplImage * m_rollbg;//ͨ����׼��ͼ��ʵ�ֵĹ���ͼ
		IplImage * m_clongbg;//ÿһ����ʾ�ı���ͼ
};

#endif // !defined(AFX_GAMEUI_H__3EEF3F3B_232D_444B_8264_396955ECF370__INCLUDED_)


// ISERVER.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "tcpsocket.h"


// CISERVERApp:
// �йش����ʵ�֣������ ISERVER.cpp
//

class CISERVERApp : public CWinApp
{
public:
	CISERVERApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	CObList m_TcpSocketList;
};

extern CISERVERApp theApp;
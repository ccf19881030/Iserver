
// ISERVERDlg.h : 头文件
//

#pragma once
#include "ibsocket.h"
#include "afxcmn.h"
#include "TcpSocket.h"

// CISERVERDlg 对话框
class CISERVERDlg : public CDialogEx
{
// 构造
public:
	CISERVERDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ISERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIbSocket m_Socket;
	CListCtrl m_List;
	

	CTcpSocket m_TcpSocket;
	CListCtrl m_WList;
	afx_msg void OnBnClickedButton1();
	CString HostIp;
	CString HostMaskIp;

	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	void ShowIbeconValue(_RecordsetPtr rs,int index);
	void ShowMaskValue(int index);
	_CommandPtr m_pCommand;
};

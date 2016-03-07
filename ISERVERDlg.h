
// ISERVERDlg.h : ͷ�ļ�
//

#pragma once
#include "ibsocket.h"
#include "afxcmn.h"
#include "TcpSocket.h"

// CISERVERDlg �Ի���
class CISERVERDlg : public CDialogEx
{
// ����
public:
	CISERVERDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ISERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

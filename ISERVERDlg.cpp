
// ISERVERDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ISERVER.h"
#include "ISERVERDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//ˢ���������߳�
DWORD WINAPI ThreadBrush(LPVOID lpPrama)
{
	
	int index;
	CTime time;
	//COleDateTime   tm;  
	//CTimeSpan TimeSpan;
	//CString str;
		CISERVERDlg* Dlg=(CISERVERDlg*)AfxGetApp()->GetMainWnd();
		_RecordsetPtr rs;
		
	while(1)
	{
		
		//time=CTime::GetCurrentTime();
		/*if (Dlg->m_pRecordset->State==adStateOpen)
		{
			Dlg->m_pRecordset->Close();
		}
		
		Dlg->m_pRecordset->Open(_T("SELECT * FROM Ibeacon order by time desc"),Dlg->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);*/

		try
			{
				Dlg->m_pCommand->CommandText=_T("SELECT * FROM Ibeacon order by time desc;");
				rs=Dlg->m_pCommand->Execute(NULL,NULL,adCmdText);
			}
			catch(_com_error e)
			{
				AfxMessageBox(L"���ݿ���� ");
			}
			


		
		if (rs->adoEOF)
		{

		}
		else
		{
			
				index=0;
			rs->MoveFirst();
				
			while(!rs->adoEOF)
			{
				
				////��ȡ���ݿ��е�ʱ����м��ʱ����Ƿ񳬹�һ����
				//str=(CString)Dlg->m_pRecordset->GetCollect(_T("time"));
				//	
				//
				//tm.ParseDateTime(str);  

				//__time32_t st;  
				//
				//tm.GetAsSystemTime((SYSTEMTIME &)st);  

				//CTime ct(st); 
			
				//TimeSpan=time-ct;
				//int g=TimeSpan.GetMinutes();
				
				/*CString s;
				s.Format(L"%d",g);
				AfxMessageBox(s);*/
				
				/*if (g<=1)
				{*/
					
					
					Dlg->ShowIbeconValue(rs,index++);
					
					rs->MoveNext();
					
				//}
				
				
			}
			
		}
		
		Sleep(1000);

		////����ˢ���ر�
		if (Dlg->m_pRecordset->State==adStateOpen)
		{
			
			Dlg->m_pRecordset->Close();
		}
		
		
		if (Dlg->m_WList.GetItemCount()!=0)
			{
				Dlg->m_WList.DeleteAllItems();
			}
		
			Dlg->m_pRecordset->Open(_T("SELECT * FROM IbeaconGateway"),Dlg->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);


		if (Dlg->m_pRecordset->adoEOF)
		{

		}
		else
		{
			index=0;

			Dlg->m_pRecordset->MoveFirst();

			while(!Dlg->m_pRecordset->adoEOF)
			{



				Dlg->ShowMaskValue(index++);
			
				Dlg->m_pRecordset->MoveNext();
			}

			
		}

		if (Dlg->m_pRecordset->State==adStateOpen)
		{
			Dlg->m_pRecordset->Close();
		}
		
		Sleep(1000);//2��ɨ��һ��

		if (Dlg->m_List.GetItemCount()!=0)
		{
			Dlg->m_List.DeleteAllItems();
		}
		
		
			
	}

	return 0;
}






// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CISERVERDlg �Ի���




CISERVERDlg::CISERVERDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CISERVERDlg::IDD, pParent)
	, HostIp(_T(""))
	, HostMaskIp(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CISERVERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);

	DDX_Control(pDX, IDC_LIST2, m_WList);
}

BEGIN_MESSAGE_MAP(CISERVERDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CISERVERDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()






// CISERVERDlg ��Ϣ�������

BOOL CISERVERDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	/*****************************�������*******************************/

	//��ʼ�����ݿ�
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("��ʼ��OLEk��ʧ�ܣ�"));
		return FALSE;
	}
	
	HRESULT hr;
	m_pConnection.CreateInstance(__uuidof(Connection));
	

	//���ӵ����ݿ�
	hr=m_pConnection->Open(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D://Ibeacon.mdb"),_T(""),_T(""),adModeUnknown);
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("���ӵ����ݿ�ʧ�ܣ�"));
		
	}

	hr=m_pCommand.CreateInstance(__uuidof(Command));

	

	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("�����������ʵ��ʧ�ܣ�"));

	}
	m_pCommand->ActiveConnection=m_pConnection;
	//�����������ݿ�ʵ��

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	//�������ݱ�
	//m_pRecordset->Open(_T("SELECT * FROM Ibeacon"),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	//���ڻ�ñ���IP��ַ�͹㲥��ַ
	char name[254];

	gethostname(name,254);
	HOSTENT* host=gethostbyname(name);
	char *p=inet_ntoa(*(struct in_addr*)*host->h_addr_list);
	CString s;
	int count=0;
	UINT i;
	//��ñ���IP
	for (i=0;i<strlen(p);i++)
	{
		s.Format(L"%c",*(p+i));
		HostIp+=s;
		
	}

	for (i=0;i<strlen(p);i++)
	{
		s.Format(L"%c",*(p+i));
		if (s.Compare(L".")==0)
		{
			count++;
		}
		if (count==3)
		{
			HostMaskIp+=".255";
			break;
		}
		else
		{
			HostMaskIp+=s;
		}

	}
	







	m_Socket.Create(10000,SOCK_DGRAM);//����UDP�׽���
	m_TcpSocket.Create(8888,SOCK_STREAM);//����TCP�׽���
	
	
	
	

	m_List.InsertColumn(0,L"������ַ");
	m_List.InsertColumn(1,L"����");
	m_List.InsertColumn(2,L"UUID");
	m_List.InsertColumn(3,L"major");
	m_List.InsertColumn(4,L"minor");
	m_List.InsertColumn(5,L"power");
	m_List.InsertColumn(6,L"ʣ�����");
	m_List.InsertColumn(7,L"��������");
	m_List.InsertColumn(8,L"ɨ��ʱ��");

	m_WList.InsertColumn(0,L"����IP");
	m_WList.InsertColumn(1,L"����MAC��ַ");
	m_WList.InsertColumn(2,L"��������MAC��ַ");
	m_WList.InsertColumn(3,L"��������汾");
	m_WList.InsertColumn(4,L"��������汾");

	m_List.SetColumnWidth(0,120);
	m_List.SetColumnWidth(1,50);
	m_List.SetColumnWidth(2,300);
	m_List.SetColumnWidth(3,50);
	m_List.SetColumnWidth(4,50); 
	m_List.SetColumnWidth(5,50); 
	m_List.SetColumnWidth(6,80); 
	m_List.SetColumnWidth(7,120); 
	m_List.SetColumnWidth(8,150); 


	m_WList.SetColumnWidth(0,150);
	m_WList.SetColumnWidth(1,150);
	m_WList.SetColumnWidth(2,150);
	m_WList.SetColumnWidth(3,150);
	m_WList.SetColumnWidth(4,150);
	m_WList.SetColumnWidth(5,150);

	
	
	
	m_TcpSocket.Listen(20);

	
	BYTE BUF[]={0X55,0XAA,0X00,0X00,0X01};
	m_Socket.SendTo(BUF,5*sizeof(BYTE),10000,HostMaskIp);
	

	CreateThread(NULL,0,ThreadBrush,(LPVOID)NULL,0,NULL);//��������ˢ���������߳�


	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CISERVERDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CISERVERDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CISERVERDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�������ı�֮������������
void CISERVERDlg::OnBnClickedButton1()
{CString IP=HostMaskIp;
INT PORT=10000;
BYTE PFCFG[]={0x55,0xAA,0x00,0x06,0x06,0x00,0x00,0x00,0x00,0x22,0xB8};
char* buf=(char*)HostIp.GetBuffer(HostIp.GetLength());
CString m_buf[4];
int i_buf[4];
for (int i=0;i<=3;i++)
{

	while(*buf!='.')
	{
		m_buf[i]+=(CString)*buf;
		buf++;

	}
	buf++;
	i_buf[i]=_ttoi(m_buf[i]);


	PFCFG[i+5]=(BYTE)i_buf[i];
}


m_Socket.SendTo(PFCFG,sizeof(PFCFG),PORT,IP);
}





void CISERVERDlg::ShowIbeconValue(_RecordsetPtr rs,int index)
{
	int cow;
	try
	{
		
		_variant_t vValue;
		vValue = rs->GetCollect(_T("IMac"));
		
		if (vValue.vt!=VT_NULL)
		{
			cow=m_List.InsertItem(index,(CString)vValue);
		}
			
		vValue = rs->GetCollect(_T("RSSI"));
		
		if (vValue.vt!=VT_NULL)
		{
			m_List.SetItemText(cow,1,(CString)vValue);
		}
		
		
		vValue = rs->GetCollect(_T("UUID"));
		
			if (vValue.vt!=VT_NULL)
			{
				m_List.SetItemText(cow,2,(CString)vValue);
			}
		

		vValue = rs->GetCollect(_T("major"));
		if (vValue.vt!=VT_NULL)
		{
			m_List.SetItemText(cow,3,(CString)vValue);
		}
		
		
		vValue = rs->GetCollect(_T("minor"));
			if (vValue.vt!=VT_NULL)
			{
				m_List.SetItemText(cow,4,(CString)vValue);
			}
		

		vValue = rs->GetCollect(_T("power"));
			if (vValue.vt!=VT_NULL)
			{
					m_List.SetItemText(cow,5,(CString)vValue);
			}
	

		vValue = rs->GetCollect(_T("Electric"));
		if (vValue.vt!=VT_NULL)
		{
			m_List.SetItemText(cow,6,(CString)vValue);
		}
		

		vValue = rs->GetCollect(_T("Gateway"));
		if (vValue.vt!=VT_NULL)
		{
			m_List.SetItemText(cow,7,(CString)vValue);
		}
	

		vValue = rs->GetCollect(_T("time"));
		if (vValue.vt!=VT_NULL)
		{
			m_List.SetItemText(cow,8,(CString)vValue);
		}
		
	

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	
}


void CISERVERDlg::ShowMaskValue(int index)
{
	int cow;
	try
	{
		_variant_t vValue;
		vValue = m_pRecordset->GetCollect(_T("Ip"));
		if (vValue.vt!=VT_NULL)
		{
			cow=m_WList.InsertItem(index,(CString)vValue);
		}
		

		vValue = m_pRecordset->GetCollect(_T("Mac"));
		if (vValue.vt!=VT_NULL)
		{
			m_WList.SetItemText(cow,1,(CString)vValue);
		}
			

		vValue = m_pRecordset->GetCollect(_T("IbeaMac"));
		if (vValue.vt!=VT_NULL)
		{
			m_WList.SetItemText(cow,2,(CString)vValue);
		}
		

		vValue = m_pRecordset->GetCollect(_T("Major"));
		if (vValue.vt!=VT_NULL)
		{
			m_WList.SetItemText(cow,3,(CString)vValue);
		}
		

		vValue = m_pRecordset->GetCollect(_T("Minor"));
		if (vValue.vt!=VT_NULL)
		{
			m_WList.SetItemText(cow,4,(CString)vValue);
		}
		
		

	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
}

// TcpSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ISERVER.h"
#include "TcpSocket.h"
#include "ISERVERDlg.h"
#include "windows.h"
// CTcpSocket
BYTE PFIBEACON[]={0x55,0xAA,0x00,0x00,0x0D};
BYTE APINFO[]={0x55,0xAA,0x00,0x00,0x09};
CTcpSocket::CTcpSocket()
{
}

CTcpSocket::~CTcpSocket()
{
}



//����CStringת����byte�Ľ��װ 
void   xString2Byte(BYTE*   bytes,int   nByteSize,CString   str) 
{ 

	BYTE   tmp; 
	BYTE   ntmp; 
	int   bcount=0; 
	int i;
	TCHAR *p=str.GetBuffer(str.GetLength());
	TCHAR *q=p;
	int flag=0;
	CString s;
	CString t;
	for (i=0;i<=str.ReverseFind(':');i++)
	{
		if (*p==':'&&flag==0)
		{
			
			if((p-q)==1)
			{
				
				s+=L"0";
				s+=(CString)*(p-1);
			}
			else
			{
				s+=(CString)*(p-2);
				s+=(CString)*(p-1);
			}
			flag=1;
			q=p;
		}else if (*p==':'&&flag==1)
		{
			if((p-q)==2)
			{
				
				s+=L"0";
				s+=(CString)*(p-1);
			}
			else
			{
				s+=(CString)*(p-2);
				s+=(CString)*(p-1);
			}
			flag=1;
			q=p;
		}
		
		p++;
	}


		if (str.GetLength()-1-str.ReverseFind(':')==2)
		{
			s+=str[str.ReverseFind(':')+1];
			s+=str[str.ReverseFind(':')+2];
		}
		else
		{
			s+="0";
			s+=str[str.GetLength()-1];
		
		}

	str=s;
	
	
	for(i=0;i<nByteSize*2;i++) 
	{ 
		int a=str[i]; 
		
		if(a>=48&&a<=57) 
		{ 
			a=a-48; 
		} 
		else if(a>=65&&a<=70) 
		{ 
			a=a-55; 
		} 
		else if(a>=97&&a<=122) 
		{ 
			a=a-87; 
		} 
		
		tmp=a; 
		
		if(i%2==0) 
			ntmp=tmp<<4; 
		else 
		{ 
			ntmp=(ntmp|tmp); 
			bytes[bcount]=ntmp; 
			bcount++; 
		} 
	} 
}






int TcpFlag=0;

int ThreadFun(LPVOID lpPrama)
{	
	UINT16 BatCount=0;
	BYTE IConData[15]={0x55,0xAA,0X00,0X0A,0X15};
	BYTE IConnect[15]={0x55,0xAA,0X00,0X0A,0X10};
	BYTE DIS_IBEACON[11]={0x55,0xAA,0X00,0X06,0X12};
	CTcpSocket* ConSocket=(CTcpSocket*)lpPrama;
	//int Cow;
	CISERVERApp* pApp=(CISERVERApp*)AfxGetApp();
	CISERVERDlg* pDlg=(CISERVERDlg*)AfxGetApp()->GetMainWnd();
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	

	BYTE sBuf[254]={0};
	CString str;
	CString tmp;
	CString IbMac;
	CString RSSI;
	CString UUID;
	CString Major;
	int MajorU;
	CString Minor;
	int MinorU;
	CString Power;
	CString m_time;
	CString IPMAC;//��������
	CString Major_Version;//���ص�
	CString Minor_Version;//���ص�
	CString Imac;//����������ַ
	BYTE BAT[6];
	BYTE rssi;
	UINT Connect_Mutex=0;
	int i;
	int flag=0;
	CString AnaIp;
	UINT AnaPort;
	ConSocket->GetPeerName((CString &)AnaIp,(UINT &)AnaPort);
	
	while (1)
	{
		if (m_pRecordset->State==adStateOpen)
		{
			m_pRecordset->Close();
		}
	
		//��ջ���
		str.Empty();
		IbMac.Empty();
		RSSI.Empty();
		UUID.Empty();
		Major.Empty();
		Minor.Empty();
		Power.Empty();
		Minor_Version.Empty();
		Major_Version.Empty();
		Imac.Empty();
		tmp.Empty();
		IPMAC.Empty();
		memset(sBuf,0,sizeof(sBuf));
		memset(&MajorU,0,sizeof(MajorU));
		memset(&MinorU,0,sizeof(MinorU));
		i=0;

		while(1)
		{
			memset(sBuf,0,sizeof(sBuf));
			if (ConSocket->Receive(sBuf,254*sizeof(BYTE))>0)
			{
				
				break;
			}
		}
		
		
		
	//���յ�������Ϣ
	if(sBuf[4]==0x0E)
	{	
			
		
		//����MAC��ַ
		for (i=5;i<=10;i++)
		{
			//IConnect[i]=sBuf[i];
			str.Format(L"%X",sBuf[i]);
			tmp+=str;
			if (i!=10)
			{
				tmp+=':';
			}
		}

		IbMac=tmp;
		tmp.Empty();
		
		//����RSSIֵ
		CString s;
		CString r;
		float ci=0.0;
		rssi=abs((char)sBuf[11]);
		ci=((float)rssi-70)/40;
		ci=pow(10,ci);
		
		RSSI.Format(L"%0.1fm",ci);

		//����UUIDֵ
		for(i=12;i<=27;i++)
		{
			UUID.Format(L"%X",sBuf[i]);
			tmp+=UUID;
			if (i!=27)
			{
				tmp+=' ';
			}
		}
		UUID=tmp;

		//����Major
		MajorU=sBuf[28];
		MajorU=MajorU<<8;
		MajorU=MajorU|sBuf[29];
		Major.Format(L"%d",MajorU);

		//����Minor
		MinorU=sBuf[30];
		MinorU=MinorU<<8;//�õ���8λ
		MinorU=MinorU|sBuf[31];//�õ���8λ
		Minor.Format(L"%d",MinorU);
			
		//����Meas power
		Power.Format(L"%d",(char)sBuf[32]);
		
		//�����������أ����ǽ���SOCKET
		for (i=0;i<=pDlg->m_WList.GetItemCount();i++)
		{
			if (AnaIp.Compare(pDlg->m_WList.GetItemText(i,0))==0)
			{

				IPMAC+=AnaIp;
				IPMAC+=L"(";
				IPMAC+=pDlg->m_WList.GetItemText(i,1);
				IPMAC+=L")";

				break;
			}




		}
		//����ɨ�赽��ʱ��
		CTime time=CTime::GetCurrentTime();
		m_time=time.Format(L"%Y-%m-%d %X");

	
		
		//�������ݿ�

	m_pRecordset->Open(_T("SELECT * FROM Ibeacon"),pDlg->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		flag=0;
		_variant_t vValue;
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveFirst();

			while (!m_pRecordset->adoEOF)
			{

				vValue = m_pRecordset->GetCollect(_T("IMac"));
				if (IbMac.Compare(CString(vValue))==0)
				{


					m_pRecordset->Update(_variant_t("time"),(_variant_t)m_time);
					m_pRecordset->Update(_variant_t("RSSI"),(_variant_t)RSSI);
					m_pRecordset->Update(_variant_t("Major"),(_variant_t)Major);
					m_pRecordset->Update(_variant_t("Minor"),(_variant_t)Minor);

					flag=1;
					break;
				}
				m_pRecordset->MoveNext();
			}

		}
		
			
		
		
		if (flag==0)
		{
			try
			{
				m_pRecordset->AddNew();


			}
			catch(_com_error e)
			{
				AfxMessageBox(e.ErrorMessage());
			}

			try
			{

				m_pRecordset->PutCollect(_T("IMac"),(_variant_t)IbMac);

				m_pRecordset->PutCollect(_T("RSSI"),(_variant_t)RSSI);

				m_pRecordset->PutCollect(_T("UUID"),(_variant_t)UUID);


				m_pRecordset->PutCollect(_T("major"),(_variant_t)Major);

				m_pRecordset->PutCollect(_T("minor"),(_variant_t)Minor);

				m_pRecordset->PutCollect(_T("power"),(_variant_t)Power);
				m_pRecordset->PutCollect(_T("Gateway"),(_variant_t)AnaIp);

				m_pRecordset->PutCollect(_T("time"),(_variant_t)m_time);
				m_pRecordset->Update();

				m_pRecordset->MoveFirst();
			}
			catch(_com_error e)
			{
				AfxMessageBox(e.ErrorMessage());
			}

		}
			
			
		



		



		++TcpFlag;

		
			
		

	}
	//���յ�������Ϣ
	else if (sBuf[4]==0x0A)
	{
	
		CString vValue;
		if (m_pRecordset->State==adStateOpen)
		{
			m_pRecordset->Close();
		}
		int flag=0;
		m_pRecordset->Open(_T("SELECT * FROM IbeaconGateway;"),pDlg->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		
		
		
		

		

		//��������Major_Version
		for (i=5;i<=7;i++)
		{
			str.Format(L"%X",sBuf[i]);
			tmp+=str;
			if (i!=7)
			{
				tmp+='.';
			}

		}
		Major_Version=tmp;
		tmp.Empty();

		//��������Minor_Version
		for (i=14;i<=16;i++)
		{
			str.Format(L"%X",sBuf[i]);
			tmp+=str;
			if (i!=16)
			{
				tmp+='.';
			}

		}
		Minor_Version=tmp;
		tmp.Empty();

		//������������MAC��ַ
		for (i=8;i<=13;i++)
		{
			str.Format(L"%X",sBuf[i]);
			tmp+=str;
			if (i!=13)
			{
				tmp+=':';
			}
			
		}
		Imac=tmp;
		
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveFirst();
			while (!m_pRecordset->adoEOF)
			{

				vValue=(CString)m_pRecordset->GetCollect(_T("Ip"));
				if (vValue.Compare(AnaIp)==0)
				{
					m_pRecordset->PutCollect(_T("IbeaMac"),_variant_t(Imac));
					m_pRecordset->PutCollect(_T("Major"),_variant_t(Major_Version));
					m_pRecordset->PutCollect(_T("Minor"),_variant_t(Minor_Version));

					m_pRecordset->Update();
					break;
				}
				m_pRecordset->MoveNext();
			}
		}
		
		
		
		
		
		
		
		

	}

	else if (sBuf[4]==0x0F)
	{	
		//������ݿ��Ƿ���Ҫ���µ�ص�������Ҫ�������������������Ҫ�ͼ�������ɨ������
		//���ͻ�ȡ������Ϣ������
		
		
		if (m_pRecordset->State==adStateOpen)
		{
			m_pRecordset->Close();
		}
		try
		{
			m_pRecordset->Open(_T("SELECT * FROM Ibeacon where Electric is null;"),pDlg->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		}
		catch(ErrorPtr e)
		{
			
		}
		
		_variant_t vValue;

		//���Ͷ�ȡ����
		if (!m_pRecordset->adoEOF)
		{
			
			m_pRecordset->MoveFirst();
			CString s=(CString)m_pRecordset->GetCollect(_T("IMac"));
			if (s.GetLength()!=0)
			{
				xString2Byte(BAT,sizeof(BAT),s);//���װ����
				for (i=0;i<=5;i++)
				{
					IConnect[i+5]=BAT[i];
				}
				for (i=11;i<=14;i++)
				{
					IConnect[i]=0;
				}
				
				ConSocket->Send(IConnect,sizeof(IConnect));
				
			}
		}
		
		else
		{
			
					
			ConSocket->Send(PFIBEACON,5*sizeof(BYTE));
		}
		

	}
	 //���������ж��Ƿ�����������
	else if (sBuf[4]==0x11&&sBuf[5]==0x00)
	{
		
		Connect_Mutex++;
	}
	else if (sBuf[4]==0x13&&sBuf[11]==0x00)
	{
		
		Connect_Mutex++;
	}
	else if (sBuf[4]==0x14&&sBuf[11]==0x00)
	{
	

		if (Connect_Mutex!=2)
		{
			AfxMessageBox(L"��������ʧ��");
		}
		else//�������ӳɹ�
		{
			//��ѯ���ʣ�����
	
			for (i=5;i<=10;i++)
			{
				IConData[i]=BAT[i-5];
			}
			IConData[11]=0x18;
			IConData[12]=0x0F;
			IConData[13]=0x2A;
			IConData[14]=0x19;

			CString s;
			tmp.Empty();
			for (i=0;i<=14;i++)
			{
				s.Format(L"%X",IConData[i]);
				tmp+=s;
				tmp+=" ";
			}
			Connect_Mutex=0;

			ConSocket->Send(IConData,sizeof(IConData));
		}
	}
	else if (sBuf[4]==0x11&&sBuf[5]==0x31)//��ʾ��ǰ�Ѿ����Ӻ���
	{
		
		
		for (i=5;i<=10;i++)
		{
			IConData[i]=BAT[i-5];
		}
		IConData[11]=0x18;
		IConData[12]=0x0F;
		IConData[13]=0x2A;
		IConData[14]=0x19;



		ConSocket->Send(IConData,sizeof(IConData));
	}
	else if (sBuf[4]==0x16)
	{
		
		CString Bat;
		Bat.Format(L"%d",sBuf[5]);
		
		if (m_pRecordset->State==adStateOpen)
		{
			m_pRecordset->Close();
		}
		
		try
		{
			m_pRecordset->Open(_T("SELECT * FROM Ibeacon where Electric is null;"),pDlg->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		}
		catch(ErrorPtr e)
		{
			AfxMessageBox(L"gghghhghg");
		}

		_variant_t vValue;
		
		//����д�����ݿ�
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveFirst();
					
			m_pRecordset->PutCollect(_T("Electric"),_variant_t(Bat));
			m_pRecordset->Update();


			//�Ͽ�����
			for (i=0;i<=5;i++)
			{
				DIS_IBEACON[i+5]=BAT[i];
			}

			ConSocket->Send(DIS_IBEACON,sizeof(DIS_IBEACON));

			BatCount++;
	
			////������һ��
			
			_RecordsetPtr rs;
				
			try
			{
				pDlg->m_pCommand->CommandText=_T("SELECT * FROM Ibeacon where Electric is null;");
				rs=pDlg->m_pCommand->Execute(NULL,NULL,adCmdText);
			}
			catch(_com_error e)
			{
				AfxMessageBox(L"���ݿ���� ");
			}
			

			if (!rs->adoEOF)
			{
				rs->MoveFirst();
				CString s=(CString)rs->GetCollect(_T("IMac"));
				if (s.GetLength()!=0)
				{
					xString2Byte(BAT,sizeof(BAT),s);//���װ����
					for (i=0;i<=5;i++)
					{
						IConnect[i+5]=BAT[i];
					}
					for (i=11;i<=14;i++)
					{
						IConnect[i]=0;
					}

					ConSocket->Send(IConnect,sizeof(IConnect));
				}
			}
			else
			{
				ConSocket->Send(PFIBEACON,5*sizeof(BYTE));
			}
			
			
			
		}
	


		
	}
	

	if (m_pRecordset->State==adStateOpen)
	{
		m_pRecordset->Close();
	}

	}
	


	return 0;

}
// CTcpSocket ��Ա����


void CTcpSocket::OnAccept(int nErrorCode)
{	
	
	
	//��̬����CTcpSocket����
	CTcpSocket* pSocket=new CTcpSocket;
	Accept(*pSocket);
	
	CISERVERApp* pApp=(CISERVERApp*)AfxGetApp();
	pApp->m_TcpSocketList.AddTail(pSocket);
	CISERVERDlg* pDlg=(CISERVERDlg*)AfxGetMainWnd();
			

	CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFun,pSocket,0,0);

	Sleep(500);
	//��ȡ������Ϣ������
	pSocket->Send(APINFO,5*sizeof(BYTE));
	Sleep(500);
	//���ͻ�ȡ������Ϣ������
	pSocket->Send(PFIBEACON,5*sizeof(BYTE));
	

	CAsyncSocket::OnAccept(nErrorCode);
}





// IbSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ISERVER.h"
#include "IbSocket.h"
#include "ISERVERDlg.h"

// IbSocket

CIbSocket::CIbSocket()
{
}

CIbSocket::~CIbSocket()
{
}


// IbSocket 成员函数



void CIbSocket::OnReceive(int nErrorCode)
{
	
	CString tmp;
	CString DIP;//接收到的用于显示的IP
	CString DMAC;
	_RecordsetPtr rs;
	BYTE sBuf[255]={0};
	int i=0;
	LVITEM item={0};
	CString sRemoteIP=L"255.255.255.255";
	UINT Port=10000;
	
	ReceiveFrom(sBuf,254*sizeof(BYTE),sRemoteIP,Port);
	CISERVERDlg* pDlg=(CISERVERDlg*)AfxGetMainWnd();
	
	if(sBuf[4]==0x02)
	{	
			
		int i;
		for(i=5;i<=8;i++)
		{
			tmp.Format(L"%d",sBuf[i]);
			if(i!=8)
			{
				tmp+='.';
			}
			DIP+=tmp;
		}
		for(i=9;i<=14;i++)
		{
			tmp.Format(L"%d",sBuf[i]);
			if(i!=14)
			{
				tmp+=':';
			}
			DMAC+=tmp;
		}
			int col	;
			CString s;
			int flag=0;
			
			if (pDlg->m_pRecordset->State==adStateOpen)
			{
				pDlg->m_pRecordset->Close();
			}
			   	
			
		pDlg->m_pRecordset->Open(_T("SELECT * FROM IbeaconGateway"),pDlg->m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		/*try
			{
				pDlg->m_pCommand->CommandText=_T("SELECT * FROM IbeaconGateway;");
				rs=pDlg->m_pCommand->Execute(NULL,NULL,adCmdText);
			}
			catch(_com_error e)
			{
				AfxMessageBox(L"数据库出错 ");
			}
		*/
		
		if (!pDlg->m_pRecordset->adoEOF)
		{
			pDlg->m_pRecordset->MoveFirst();
		
			while(!pDlg->m_pRecordset->adoEOF)
			{
				s=(CString)pDlg->m_pRecordset->GetCollect(_T("Ip"));
				if (s.Compare(DIP)==0)
				{
					flag=1;
					break;
				}
				pDlg->m_pRecordset->MoveNext();
					
			}
			
			if (flag==0)
			{
				
				pDlg->m_pRecordset->AddNew();
				pDlg->m_pRecordset->PutCollect(_T("Ip"),_variant_t(DIP));
				pDlg->m_pRecordset->PutCollect(_T("Mac"),_variant_t(DMAC));
				pDlg->m_pRecordset->Update();
				
			}

		 }
		else
		{
			
				try
			{
				pDlg->m_pRecordset->AddNew();


			}
			catch(_com_error e)
			{
				AfxMessageBox(e.ErrorMessage());
			}
				
		
		
				//try
				//{
					pDlg->m_pRecordset->PutCollect(_T("Ip"),_variant_t(DIP));
					pDlg->m_pRecordset->PutCollect(_T("Mac"),_variant_t(DMAC));
					pDlg->m_pRecordset->Update();
				//}
				//catch(_com_error e)
				//{
				//	AfxMessageBox(e.ErrorMessage());
				//}


			
				/*pDlg->m_pCommand->CommandText=_T("Insert into IbeaconGateway (Ip,Mac) values (NULL,NULL);");
			
				rs=pDlg->m_pCommand->Execute(NULL,NULL,adCmdText);
					AfxMessageBox(L"nn");
*/
		}
			
		
			

		

		
	}
	
	
	
	
	
	
	

	CAsyncSocket::OnReceive(nErrorCode);
}



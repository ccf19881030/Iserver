#pragma once

// CTcpSocket ����Ŀ��

class CTcpSocket : public CAsyncSocket
{
public:
	CTcpSocket();
	virtual ~CTcpSocket();
	virtual void OnAccept(int nErrorCode);


};



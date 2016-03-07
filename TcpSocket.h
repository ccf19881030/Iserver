#pragma once

// CTcpSocket ÃüÁîÄ¿±ê

class CTcpSocket : public CAsyncSocket
{
public:
	CTcpSocket();
	virtual ~CTcpSocket();
	virtual void OnAccept(int nErrorCode);


};



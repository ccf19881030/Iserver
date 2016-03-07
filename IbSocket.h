#pragma once

// IbSocket ÃüÁîÄ¿±ê

class CIbSocket : public CAsyncSocket
{
public:
	CIbSocket();
	virtual ~CIbSocket();
	virtual void OnReceive(int nErrorCode);
};



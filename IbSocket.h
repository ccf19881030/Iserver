#pragma once

// IbSocket ����Ŀ��

class CIbSocket : public CAsyncSocket
{
public:
	CIbSocket();
	virtual ~CIbSocket();
	virtual void OnReceive(int nErrorCode);
};



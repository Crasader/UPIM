#pragma once
class CCustSvrMng
{
public:
	CCustSvrMng();
	~CCustSvrMng();

	// ��ʼ��
	BOOL Init(CADODatabase* pAdoDb);

	long LoadEmpInfo(CADODatabase* pAdoDb);
	long GetEmpInfo(long nBegin, LPSPUPIMID pUPID, long nSize);

protected:
	vector<SPUPIMID>	m_vtEmpInfo;
	CCriticalSection	m_csEmp;
};


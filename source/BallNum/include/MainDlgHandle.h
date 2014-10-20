#pragma once

__interface IMainDlgHandle
{
	virtual void InsertNumMgs(const char* szTitle, uint32 src[], uint8 len) = 0;
	virtual void InsertMsg(const std::string&)=0;
};

class ShowMainMessage
{
public:
	static ShowMainMessage* share();
	void Init(IMainDlgHandle*);

	void InsertMsg(const std::string&);
	void InsertNumMgs(const char* szTitle, uint32 src[], uint8 len);
private:
	ShowMainMessage();
	~ShowMainMessage();

private:
	static ShowMainMessage* m_gSelf;
	IMainDlgHandle* m_handle;
};


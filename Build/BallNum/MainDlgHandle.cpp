#include "stdafx.h"
#include "MainDlgHandle.h"

ShowMainMessage* ShowMainMessage::m_gSelf = NULL;
ShowMainMessage::ShowMainMessage()
{
}

ShowMainMessage::~ShowMainMessage()
{
}

ShowMainMessage* ShowMainMessage::share()
{
	if (!m_gSelf)
		m_gSelf = new ShowMainMessage;

	return m_gSelf;
}

void ShowMainMessage::Init(IMainDlgHandle* pHandle)
{
	m_handle = pHandle;
}

void ShowMainMessage::InsertNumMgs(const char* szTitle, uint32 src[], uint8 len)
{
	if (m_handle)
		m_handle->InsertNumMgs(szTitle, src, len);
}

#pragma once

__interface IMainDlgHandle
{
	virtual void InsertNumMgs(const char* szTitle, uint32 src[], uint8 len)=0;
};
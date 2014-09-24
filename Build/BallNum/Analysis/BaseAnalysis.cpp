#include "stdafx.h"
#include "BaseAnalysis.h"

BaseAnalysis* BaseAnalysis::m_gSelf=NULL;
BaseAnalysis::BaseAnalysis() 
{
}

BaseAnalysis::~BaseAnalysis()
{
}

BaseAnalysis* BaseAnalysis::share()
{
	if (!m_gSelf)
		m_gSelf = new BaseAnalysis;

	return m_gSelf;
}



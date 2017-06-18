#include "SymbolTool.h"

SymbolTool* SymbolTool::m_pSelf = NULL;

SymbolTool::SymbolTool(void)
{
	m_currentType = SYMBOL_NONE;
	m_pSymbolBase = NULL;
}

SymbolTool::~SymbolTool(void)
{
}

SymbolTool* SymbolTool::ins()
{
	if (m_pSelf == NULL)
	{
		m_pSelf = new SymbolTool;
	}
	return m_pSelf;
}

void SymbolTool::destory()
{
	if (m_pSelf != NULL)
	{
		delete m_pSelf;
		m_pSelf = NULL;
	}
}


void SymbolTool::selectTool(SymbolType type)
{
	m_pSymbolBase = NULL;
	switch(type)
	{
	
	case SYMBOL_STRIP:
		{
			m_currentType = SYMBOL_STRIP;
			break;
		}
	default: SYMBOL_NONE;
		break;
	} 
}

void SymbolTool::cancelTool()
{
	m_currentType = SYMBOL_NONE;
}


bool SymbolTool::isStart()
{
	if (m_currentType != SYMBOL_NONE)
	{
		return true;
	}
	else
	{
		return false;
	}
}


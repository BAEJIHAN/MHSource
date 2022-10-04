#pragma once

#include "GameInfo.h"

class CObjectManager
{
public:
	bool Init();

private:
	Check_Type	m_CheckType;
	bool		m_IsCheck;

public:
	Check_Type GetCheckType() const
	{
		return m_CheckType;
	}

public:
	void SaveCheckToPointFunc(Check_Type Type);
	
public:
	void LoadCheckToPointFunc(class CMernos* Obj);

private:
	DECLARE_SINGLE(CObjectManager)
};


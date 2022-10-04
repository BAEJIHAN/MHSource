
#include "ObjectManager.h"
#include "Mernos.h"

DEFINITION_SINGLE(CObjectManager)

CObjectManager::CObjectManager()	:
	m_CheckType(Check_Type::StageToLoading),
	m_IsCheck(false)
{

}

CObjectManager::~CObjectManager()
{

}

bool CObjectManager::Init()
{
	return true;
}

void CObjectManager::SaveCheckToPointFunc(Check_Type Type)
{
	m_CheckType = Type;

	m_IsCheck = true;
}

void CObjectManager::LoadCheckToPointFunc(CMernos* Obj)
{
	// 저장된게 없다면 로드할게 없다는 의미이기때문에 리턴
	if (!m_IsCheck)
		return;

	Obj->SetCheckToPointType(m_CheckType);

	// 로드를 완료했다면 체크를 다시 false로 돌려줌
	m_IsCheck = false;
}

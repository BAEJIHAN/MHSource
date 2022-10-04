
#include "StartSceneMode.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "../ClientManager3D.h"
#include "../UI/StartWindow.h"
#include "../Object/EventManager.h"

CStartSceneMode::CStartSceneMode() :
	m_First(false)
{
	SetTypeID<CStartSceneMode>();

	CEventManager::GetInst()->ClearAllCallback();
}

CStartSceneMode::~CStartSceneMode()
{
}

bool CStartSceneMode::Init()
{
	if (!CSceneMode::Init())
		return false;

	LoadSound();

	CreateMaterial();

	CreateParticle();

	m_StartWindow = m_Scene->GetViewport()->CreateWidgetWindow<CStartWindow>("StartWindow");

	return true;
}

void CStartSceneMode::Update(float DeltaTime)
{
	CSceneMode::Update(DeltaTime);

	if (!m_First)
	{
		m_First = true;

		CClientManager3D::GetInst()->BGMSoundStop();
		CResourceManager::GetInst()->SoundPlay("MainMenu");
	}
}

void CStartSceneMode::CreateMaterial()
{
}

void CStartSceneMode::CreateParticle()
{
}


void CStartSceneMode::LoadSound()
{
	CResourceManager::GetInst()->LoadSound("UI", false, "UIButtonMouseOn", "UI/UIButtonMouseOnSound.ogg");
	CResourceManager::GetInst()->LoadSound("UI", false, "UIEffect", "UI/UIEffectSound.ogg");
	CResourceManager::GetInst()->LoadSound("UI", false, "UIButtonClick", "UI/UIButtonClickSound.ogg");
	CResourceManager::GetInst()->LoadSound("UI", false, "UIStartButtonClick", "UI/StartButtonClickSound.ogg");
}

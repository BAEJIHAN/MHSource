
#include "LoadingThread.h"
#include "StartSceneMode.h"
#include "TownSceneMode.h"
#include "MainSceneMode.h"
#include "Scene/SceneManager.h"
#include "../Object/EventManager.h"

CLoadingThread::CLoadingThread()
{
}

CLoadingThread::~CLoadingThread()
{
}

bool CLoadingThread::Init()
{
	if (!CThread::Init())
	{
		return false;
	}

	return true;
}

void CLoadingThread::Run()
{
	CSceneManager::GetInst()->CreateNextScene(false);
	
	Stage_Type Type = CEventManager::GetInst()->GetLoadStageType();

	switch (Type)
	{
	case Stage_Type::None:
	{
		CStartSceneMode* SceneMode = CSceneManager::GetInst()->CreateSceneModeEmpty<CStartSceneMode>(false);
		SceneMode->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);
		SceneMode->Init();
		break;
	}
	case Stage_Type::Town:
	{
		CTownSceneMode* SceneMode = CSceneManager::GetInst()->CreateSceneModeEmpty<CTownSceneMode>(false);
		SceneMode->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);
		SceneMode->Init();
		break;
	}
	case Stage_Type::Stage1:
	case Stage_Type::Stage2:
	{
		CMainSceneMode* MainScene = CSceneManager::GetInst()->CreateSceneModeEmpty<CMainSceneMode>(false);
		MainScene->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);
		MainScene->Init();
		break;
	}
	default:
		break;
	}
	
	AddMessage(true, 1.f);
}

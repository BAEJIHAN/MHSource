
#include "LoadingSceneMode.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "Scene/SceneResource.h"
#include "Scene/SceneManager.h"
#include "../Object/EventManager.h"
#include "LoadingThread.h"
#include "../ClientManager3D.h"

CLoadingSceneMode::CLoadingSceneMode() :
	m_LoadingThread(nullptr),
	m_LoadingWidget(nullptr),
	m_IsComplete(false)
{
	SetTypeID<CLoadingSceneMode>();
}

CLoadingSceneMode::~CLoadingSceneMode()
{
	SAFE_DELETE(m_LoadingThread);
}

bool CLoadingSceneMode::Init()
{
	m_LoadingWidget = m_Scene->GetViewport()->CreateWidgetWindow<CLoadingWindow>("LoadingWindow");

	// 로딩 스레드 생성
	m_LoadingThread = CThread::CreateThread<CLoadingThread>("LoadingThread");

	m_LoadingThread->Start();

	return true;
}

void CLoadingSceneMode::Update(float DeltaTime)
{
	CSceneMode::Update(DeltaTime);

	CThreadQueue<LoadingMessage>* Queue = m_LoadingThread->GetLoadingQueue();

	if (!Queue->empty())
	{
		LoadingMessage	Msg = Queue->front();

		Queue->pop();

		m_LoadingWidget->SetLoadingPercent(Msg.Percent);

		if (Msg.Complete)
		{
			m_IsComplete = true;
		}
	}

	if (m_IsComplete && m_LoadingWidget->IsFadeOutCompleted())
	{
		CEventManager::GetInst()->CallEvent("SceneFadeInStart");

		CSceneManager::GetInst()->ChangeNextScene();
	}
}

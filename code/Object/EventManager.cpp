
#include "EventManager.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Component/CameraComponent.h"

DEFINITION_SINGLE(CEventManager)

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
	ClearAllCallback();

	m_mapEvent.clear();
}

bool CEventManager::Init()
{
	// AddEventName 함수로 사용할 Key값을 등록하시면 됩니다

	AddEventName("BossDead");				// 보스몬스터 죽음 시작
	AddEventName("BossDeadEnd");			// 보스몬스터 죽음 종료
	AddEventName("PlayerMonsterContant");	// 몬스터와 접촉 시작
	AddEventName("PlayerMonsterRelease");	// 몬스터와 접촉 해제
	AddEventName("QuestAcept");				// 퀘스트 수락 이후 메르노스 소환 장면
	AddEventName("SceneFadeInStart");		// 씬 전환 후, FadeIn 시작
	AddEventName("SceneFadeOutStart");		// 씬 전환 직전에 FadeOut 시작


	CInput::GetInst()->SetKeyCallback<CEventManager>("Shake", Key_State::KeyState_Down, this, &CEventManager::ShakeOn);


	return true;
}

void CEventManager::ShakeOn()
{
	CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera()->ShakeOn();
}

#include "QuestSubWindow2.h"
#include "MainWindow.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Input.h"
#include "HDR.h"
#include "../Object/Player.h"
#include "../Object/Mernos.h"
#include "../Object/EventManager.h"
#include "../Object/ObjectManager.h"

CQuestSubWindow2::CQuestSubWindow2()
{
	SetTypeID<CQuestSubWindow2>();
}

CQuestSubWindow2::CQuestSubWindow2(const CQuestSubWindow2& Window) :
	CWidgetWindow(Window)
{
}

CQuestSubWindow2::~CQuestSubWindow2()
{
}

void CQuestSubWindow2::Start()
{
	CWidgetWindow::Start();
}

bool CQuestSubWindow2::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution r = CEngine::GetInst()->GetRS();
	Vector2 rs((float)r.Width, (float)r.Height);
	SetPos(rs.x / 2, 0.f);

	SetSize(640.f, 700.f);

	SetZOrder(5);

	BackFrame = CreateWidget<CImage>("BackFrame");
	BackFrame->SetTexture("QuestBack2", TEXT("UI/QuestBack2.png"));
	BackFrame->SetSize(640.f, 700.f);
	BackFrame->SetPos(0.f, 0.f);
	BackFrame->SetZOrder(0);



	BackBar1 = CreateWidget<CImage>("BackBar1");
	BackBar1->SetTexture("BackBar1", TEXT("UI/BackBar1.png"));
	BackBar1->SetSize(500.f, 50.f);
	BackBar1->SetPos(60.f, 600.f);
	BackBar1->SetZOrder(1);

	BossText = CreateWidget<CText>("Text1");
	BossText->SetSize(500.f, 50.f);
	BossText->SetPos(80.f, 600.f);
	BossText->SetText(TEXT("날으는 자에게 두려움은 없다"));
	BossText->SetColor(0.f, 0.f, 0.f);
	BossText->SetZOrder(2);

	BossImage = CreateWidget<CImage>("BossImage");
	BossImage->SetTexture("Rathalos", TEXT("UI/Rathalos.png"));
	BossImage->SetSize(480.f, 249.f);
	BossImage->SetPos(90.f, 300.f);
	BossImage->SetZOrder(1);



	MonsterText = CreateWidget<CText>("MonsterText");
	MonsterText->SetSize(200.f, 50.f);
	MonsterText->SetPos(40.f, 220.f);
	MonsterText->SetText(TEXT("등장 몬스터"));
	MonsterText->SetColor(0.f, 0.f, 0.f);
	MonsterText->SetZOrder(2);

	barnosicon = CreateWidget<CImage>("barnosicon");
	barnosicon->SetTexture("barnosicon", TEXT("UI/barnosicon.png"));
	barnosicon->SetSize(60.f, 60.f);
	barnosicon->SetPos(40.f, 180.f);
	barnosicon->SetZOrder(1);

	StartButton = CreateWidget<CButton>("StartButton");
	StartButton->SetSize(600.f, 70.f);
	StartButton->SetPos(25.f, 100.f);
	StartButton->SetTexture(Button_State::Click, "RaStartClick", TEXT("UI/BackBarOnMouse.png"));
	StartButton->SetTexture(Button_State::Disable, "RaStartDisable", TEXT("UI/BackBar2.png"));
	StartButton->SetTexture(Button_State::MouseOn, "RaStartMouseOn", TEXT("UI/BackBarOnMouse.png"));
	StartButton->SetTexture(Button_State::Normal, "RaStartNormal", TEXT("UI/BackBar2.png"));
	StartButton->SetZOrder(1);
	StartButton->SetClickCallback<CQuestSubWindow2>(this, &CQuestSubWindow2::ButtonCallBack);
	StartButton->SetSound(Button_Sound_State::MouseOn, "UIButtonMouseOn");
	StartButton->SetSound(Button_Sound_State::Click, "UIStartButtonClick");

	StartText = CreateWidget<CText>("Text2");
	StartText->SetSize(600.f, 50.f);
	StartText->SetPos(45.f, 110.f);
	StartText->SetText(TEXT("퀘스트 수주"));
	StartText->SetColor(0.f, 0.f, 0.f);
	StartText->SetZOrder(2);

	m_Player = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();


	return true;
}

void CQuestSubWindow2::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CQuestSubWindow2::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CQuestSubWindow2::Render()
{
	CWidgetWindow::Render();
}

void CQuestSubWindow2::ButtonCallBack()
{
	if (m_Player)
	{
		CEventManager::GetInst()->CallEvent("QuestAcept");
		CEventManager::GetInst()->SetStageType(Stage_Type::Stage2);

		Vector3 PlayerPos = m_Player->GetWorldPos();

		PlayerPos.y += 15.f;

		Vector3 PlayerDir = m_Player->GetWorldAxis(AXIS::AXIS_Z);

		CMernos* Mernos = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMernos>("Mernos");
		Mernos->SetWorldPos(PlayerPos + PlayerDir * 30.f);

		CObjectManager::GetInst()->SaveCheckToPointFunc(Check_Type::LoadingToStage);

		Destroy();
	}
}







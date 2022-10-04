#include "QuestSubWindow1.h"
#include "MainWindow.h"
#include "QuestWindow.h"
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

CQuestSubWindow1::CQuestSubWindow1()
{
	SetTypeID<CQuestSubWindow1>();
}

CQuestSubWindow1::CQuestSubWindow1(const CQuestSubWindow1& Window) :
	CWidgetWindow(Window)
{
}

CQuestSubWindow1::~CQuestSubWindow1()
{
}

void CQuestSubWindow1::Start()
{
	CWidgetWindow::Start();
}

bool CQuestSubWindow1::Init()
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
	BossText->SetText(TEXT("³­ÆøÇÑ ³ð, ´õ ³¯¶Ù´Ù"));
	BossText->SetColor(0.f, 0.f, 0.f);
	BossText->SetZOrder(2);



	BossImage = CreateWidget<CImage>("BossImage");
	BossImage->SetTexture("Anjanath", TEXT("UI/Anjanath.png"));
	BossImage->SetSize(291.f, 320.f);
	BossImage->SetPos(150.f, 250.f);
	BossImage->SetZOrder(1);



	MonsterText = CreateWidget<CText>("MonsterText");
	MonsterText->SetSize(200.f, 50.f);
	MonsterText->SetPos(40.f, 220.f);
	MonsterText->SetText(TEXT("µîÀå ¸ó½ºÅÍ"));
	MonsterText->SetColor(0.f, 0.f, 0.f);
	MonsterText->SetZOrder(2);

	vespoidicon = CreateWidget<CImage>("vespoidicon");
	vespoidicon->SetTexture("vespoidicon", TEXT("UI/vespoidicon.png"));
	vespoidicon->SetSize(60.f, 60.f);
	vespoidicon->SetPos(40.f, 180.f);
	vespoidicon->SetZOrder(1);

	jagrasicon = CreateWidget<CImage>("jagrasicon");
	jagrasicon->SetTexture("jagrasicon", TEXT("UI/jagrasicon.png"));
	jagrasicon->SetSize(60.f, 60.f);
	jagrasicon->SetPos(90.f, 180.f);
	jagrasicon->SetZOrder(1);

	kestodonicon = CreateWidget<CImage>("kestodonicon");
	kestodonicon->SetTexture("kestodonicon", TEXT("UI/kestodonicon.png"));
	kestodonicon->SetSize(60.f, 60.f);
	kestodonicon->SetPos(140.f, 180.f);
	kestodonicon->SetZOrder(1);



	StartButton = CreateWidget<CButton>("StartButton");
	StartButton->SetSize(600.f, 70.f);
	StartButton->SetPos(25.f, 100.f);
	StartButton->SetTexture(Button_State::Click, "AnStartClick", TEXT("UI/BackBarOnMouse.png"));
	StartButton->SetTexture(Button_State::Disable, "AnStartDisable", TEXT("UI/BackBar2.png"));
	StartButton->SetTexture(Button_State::MouseOn, "AnStartMouseOn", TEXT("UI/BackBarOnMouse.png"));
	StartButton->SetTexture(Button_State::Normal, "AnStartNormal", TEXT("UI/BackBar2.png"));
	StartButton->SetZOrder(1);
	StartButton->SetClickCallback<CQuestSubWindow1>(this, &CQuestSubWindow1::ButtonCallBack);
	StartButton->SetSound(Button_Sound_State::MouseOn, "UIButtonMouseOn");
	StartButton->SetSound(Button_Sound_State::Click, "UIStartButtonClick");

	StartText = CreateWidget<CText>("Text2");
	StartText->SetSize(600.f, 50.f);
	StartText->SetPos(45.f, 110.f);	
	StartText->SetText(TEXT("Äù½ºÆ® ¼öÁÖ"));
	StartText->SetColor(0.f, 0.f, 0.f);
	StartText->SetZOrder(2);

	m_Player = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();

	return true;
}

void CQuestSubWindow1::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CQuestSubWindow1::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CQuestSubWindow1::Render()
{
	CWidgetWindow::Render();
}

void CQuestSubWindow1::ButtonCallBack()
{
	if (m_Player)
	{
		CEventManager::GetInst()->CallEvent("QuestAcept");
		CEventManager::GetInst()->SetStageType(Stage_Type::Stage1);

		Vector3 PlayerPos = m_Player->GetWorldPos();

		PlayerPos.y += 15.f;

		Vector3 PlayerDir = m_Player->GetWorldAxis(AXIS::AXIS_Z);

		//m_Player->SetWorldRot(m_Player->GetWorldRot() * PlayerDir);

		CMernos* Mernos = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMernos>("Mernos");
		Mernos->SetWorldPos(PlayerPos + PlayerDir * 30.f);

		CObjectManager::GetInst()->SaveCheckToPointFunc(Check_Type::LoadingToStage);

		//m_Player->SetESCEnable(false);

		Destroy();
	}
}







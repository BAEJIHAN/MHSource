#include "ExplainWindow.h"
#include "Engine.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
#include "../Object/EventManager.h"
#include "../ClientManager3D.h"

CExplainWindow::CExplainWindow()
{
}

CExplainWindow::CExplainWindow(const CExplainWindow& Window) :
	CWidgetWindow(Window)
{
}

CExplainWindow::~CExplainWindow()
{
}

void CExplainWindow::SetText(const TCHAR* Text)
{
	m_Text->SetText(Text);
}

void CExplainWindow::Start()
{
	CWidgetWindow::Start();
}

bool CExplainWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(500.f, 200.f);

	Resolution RS = CEngine::GetInst()->GetRS();

	Vector2 vectorRS = Vector2((float)RS.Width, (float)RS.Height);

	// Window의 Width Size가 항상 가운데정렬로 맞춰주도록.
	SetPos(vectorRS.x / 2.f - (GetWindowSize().x / 2.f), vectorRS.y / 2.f - 310.f);

	m_Text = CreateWidget<CText>("ExplainText");
	m_BackImage = CreateWidget<CImage>("BackImage");
	m_UnderImage = CreateWidget<CImage>("UnderImage");


	m_Text->SetZOrder(4);
	m_Text->SetSize(500.f, 100.f);
	m_Text->SetAlignH(TEXT_ALIGN_H::Center);
	m_Text->SetAlignV(TEXT_ALIGN_V::Middle);
	m_Text->SetAlphaEnable(true);
	m_Text->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_Text->SetFontSize(20.f);
	m_Text->SetText(TEXT("테스트 출력중입니다."));


	m_BackImage->SetZOrder(3);
	m_BackImage->SetSize(500.f, 100.f);
	m_BackImage->SetTexture("WindowTextBackImage", TEXT("UI/TextBackImage.png"));

	m_UnderImage->SetZOrder(2);
	m_UnderImage->SetSize(480.f, 20.f);
	m_UnderImage->SetPos(20.f, 20.f);
	m_UnderImage->SetTexture("WindowUnderBarImage", TEXT("UI/TextUnderImage.png"));

	CEventManager::GetInst()->AddEventCallback<CExplainWindow>("BossDead", this, &CExplainWindow::QuestClearPopUp);
	CEventManager::GetInst()->AddEventCallback<CExplainWindow>("BossDeadEnd", this, &CExplainWindow::PopUpEnd);

	m_Visibility = false;

	return true;
}

void CExplainWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CExplainWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CExplainWindow::Render()
{
	CWidgetWindow::Render();
}

void CExplainWindow::QuestClearPopUp()
{
	SetVisibility(true);

	Resolution RS = CEngine::GetInst()->GetRS();

	Vector2 vectorRS = Vector2((float)RS.Width, (float)RS.Height);

	SetPos(vectorRS.x / 2.f - (GetWindowSize().x / 2.f), vectorRS.y / 2.f);

	SetText(TEXT("메인 타겟을 달성했습니다."));

	switch (CEventManager::GetInst()->GetLoadStageType())
	{
	case Stage_Type::Stage1:
		CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::QuestComplete);
		break;
	case Stage_Type::Stage2:
		CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::FinalQuestComplete);
		break;
	}
}

void CExplainWindow::PopUpEnd()
{
	SetVisibility(false);

	Resolution RS = CEngine::GetInst()->GetRS();

	Vector2 vectorRS = Vector2((float)RS.Width, (float)RS.Height);

	SetPos(vectorRS.x / 2.f - (GetWindowSize().x / 2.f), vectorRS.y / 2.f - 310.f);
}

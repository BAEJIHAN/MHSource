#include "QuestWindow.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Input.h"
#include "QuestSubWindow1.h"
#include "QuestSubWindow2.h"
#include "../Object/EventManager.h"



CQuestWindow::CQuestWindow()
{
	SetTypeID<CQuestWindow>();
}

CQuestWindow::CQuestWindow(const CQuestWindow& Window) :
	CWidgetWindow(Window)
{
}

CQuestWindow::~CQuestWindow()
{
}

void CQuestWindow::Start()
{
	CWidgetWindow::Start();
}

bool CQuestWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution r = CEngine::GetInst()->GetRS();
	Vector2 rs((float)r.Width, (float)r.Height);
	SetPos(0.f , 0.f  );

	SetSize(640.f, 700.f);

	SetZOrder(5);

	BackFrame = CreateWidget<CImage>("BackFrame");
	BackFrame->SetTexture("QuestBack1", TEXT("UI/QuestBack1.png"));
	BackFrame->SetSize(640.f, 700.f);
	BackFrame->SetPos(0.f, 0.f);
	BackFrame->SetZOrder(0);

	QuestText1 = CreateWidget<CText>("QuestText1");
	QuestText1->SetSize(500.f, 50.f);
	QuestText1->SetPos(85.f, 500.f);
	QuestText1->SetText(TEXT("난폭한 놈, 더 날뛰다"));
	
	QuestText1->SetColor(0.f, 0.f, 0.f);
	QuestText1->SetZOrder(2);

	QuestButton1 = CreateWidget<CButton>("QuestButton1");
	QuestButton1->SetSize(500.f, 50.f);
	QuestButton1->SetPos(65.f, 500.f); 
	QuestButton1->SetTexture(Button_State::Click, "BackBarOnMouse", TEXT("UI/BackBarOnMouse.png"));
	QuestButton1->SetTexture(Button_State::Disable, "QuestButton1", TEXT("UI/BackBar1.png"));
	QuestButton1->SetTexture(Button_State::MouseOn, "BackBarOnMouse", TEXT("UI/BackBarOnMouse.png"));
	QuestButton1->SetTexture(Button_State::Normal, "QuestButton1", TEXT("UI/BackBar1.png"));
	QuestButton1->SetZOrder(1);
	QuestButton1->SetClickCallback<CQuestWindow>(this, &CQuestWindow::ButtonCallBack1);
	QuestButton1->SetSound(Button_Sound_State::MouseOn, "UIButtonMouseOn");
	QuestButton1->SetSound(Button_Sound_State::Click, "UIButtonClick");
	//BackBarOnMouse
	QuestText2 = CreateWidget<CText>("QuestText2");
	QuestText2->SetSize(500.f, 50.f);
	QuestText2->SetPos(85.f, 150.f);
	QuestText2->SetText(TEXT("날으는 자에게 두려움은 없다"));
	QuestText2->SetColor(0.f, 0.f, 0.f);
	QuestText2->SetZOrder(2);	

	QuestButton2 = CreateWidget<CButton>("QuestButton2");
	QuestButton2->SetSize(500.f, 50.f);
	QuestButton2->SetPos(65.f, 150.f);
	QuestButton2->SetTexture(Button_State::Click, "BackBarOnMouse", TEXT("UI/BackBarOnMouse.png"));
	QuestButton2->SetTexture(Button_State::Disable, "QuestButton2", TEXT("UI/BackBar1.png"));
	QuestButton2->SetTexture(Button_State::MouseOn, "BackBarOnMouse", TEXT("UI/BackBarOnMouse.png"));
	QuestButton2->SetTexture(Button_State::Normal, "QuestButton2", TEXT("UI/BackBar1.png"));	
	QuestButton2->SetZOrder(1);
	QuestButton2->SetClickCallback<CQuestWindow>(this, &CQuestWindow::ButtonCallBack2);
	QuestButton2->SetSound(Button_Sound_State::MouseOn, "UIButtonMouseOn");
	QuestButton2->SetSound(Button_Sound_State::Click, "UIButtonClick");


	CEventManager::GetInst()->AddEventCallback<CQuestWindow>("QuestAcept", this, &CQuestWindow::QuestAcept);

	return true;
}

void CQuestWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CQuestWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CQuestWindow::Render()
{
	CWidgetWindow::Render();
}

void CQuestWindow::ButtonCallBack1()
{
	
	if (pSubWindow2)
	{
		pSubWindow2->SetVisibility(false);
		pSubWindow2->Disable();
	}

	if (!GetViewport()->FindWidgetWindow<CQuestSubWindow1>("QuestSubWindow1"))
	{
		pSubWindow1=GetViewport()->CreateWidgetWindow<CQuestSubWindow1>("QuestSubWindow1");
		
		
		
	}
	else if(GetViewport()->FindWidgetWindow<CQuestSubWindow1>("QuestSubWindow1"))
	{
		if (pSubWindow1->IsVisibility())
		{
			pSubWindow1->SetVisibility(false);
			pSubWindow1->Disable();
		}
		else
		{
			pSubWindow1->SetVisibility(true);
			pSubWindow1->Enable();
		}
	}
}

void CQuestWindow::ButtonCallBack2()
{
	if (pSubWindow1)
	{
		pSubWindow1->SetVisibility(false);
		pSubWindow1->Disable();
	}

	if (!GetViewport()->FindWidgetWindow<CQuestSubWindow2>("QuestSubWindow2"))
	{
		pSubWindow2 = GetViewport()->CreateWidgetWindow<CQuestSubWindow2>("QuestSubWindow2");



	}
	else if (GetViewport()->FindWidgetWindow<CQuestSubWindow2>("QuestSubWindow2"))
	{
		if (pSubWindow2->IsVisibility())
		{
			pSubWindow2->SetVisibility(false);
			pSubWindow2->Disable();
		}
		else
		{
			pSubWindow2->SetVisibility(true);
			pSubWindow2->Enable();
		}
	}
}

void CQuestWindow::QuestAcept()
{
	Destroy();
}








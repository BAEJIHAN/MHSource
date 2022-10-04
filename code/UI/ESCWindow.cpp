
#include "ESCWindow.h"
#include "Input.h"
#include "Engine.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
#include "Widget/Button.h"
#include "Scene/Viewport.h"
#include "ExplainWindow.h"
#include "../Object/EventManager.h"
#include "../Object/ObjectManager.h"
#include "HDR.h"
#include "HDRWindow.h"
CESCWindow::CESCWindow() :
	m_CurrMenuIndex(0),
	m_FocusingIndex(-1)
{
	SetTypeID<CESCWindow>();
	m_vecMenuIconButton.resize(1);
	m_vecSystemButton.resize(2);
	m_vecButtonText.resize(2);
}

CESCWindow::~CESCWindow()
{
}

void CESCWindow::FadeDestroy()
{
	CWidgetWindow::FadeDestroy();

	GetViewport()->FindWidgetWindow<CWidgetWindow>("ExplainWindow")->SetVisibility(false);

	GetViewport()->FindWidgetWindow<CWidgetWindow>("ExplainWindow")->SetVisibility(false);

	if (CHDR::GetInst()->GetIsWindowOn())
	{
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->SetVisibility(false);
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Disable();
		CHDR::GetInst()->SetIsWindowOn(false);
	}
}

void CESCWindow::Start()
{
	CWidgetWindow::Start();
}

bool CESCWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution RS = CEngine::GetInst()->GetRS();

	Vector2 vectorRS = Vector2((float)RS.Width, (float)RS.Height);

	SetSize(400.f, 300.f);

	SetPos(vectorRS.x / 2.f - 640.f, vectorRS.y / 2.f - 100.f);

	SetZOrder(4);

	CreateWidgets(Vector2(400.f, 300.f));

	return true;
}

void CESCWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_Enable)
	{
		m_TitleImage->StartPaperBurn();
	}

	TrackingButton();
}

void CESCWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CESCWindow::Render()
{
	CWidgetWindow::Render();
}

//Vector2(400.f, 300.f)
void CESCWindow::CreateWidgets(Vector2 WindowSize)
{
	m_TitleImage = CreateWidget<CImage>("MenuTitleImage");
	m_TitleLine = CreateWidget<CImage>("MenuTitleLine");
	m_ButtonBackImage = CreateWidget<CImage>("ButtonBackImage");
	m_ButtonFocusImage = CreateWidget<CImage>("ButtonFocusImage");

	m_TitleImage->SetZOrder(2);
	m_TitleLine->SetZOrder(3);
	m_ButtonBackImage->SetZOrder(2);
	m_ButtonFocusImage->SetZOrder(3);

	m_TitleImage->SetPos(0.f, WindowSize.y / 2.f + 140.f);
	m_TitleLine->SetPos(0.f, WindowSize.y / 2.f + 130.f);
	m_ButtonBackImage->SetPos(WindowSize.x / 2.f - 120.f, WindowSize.y / 2.f - 120.f);
	m_ButtonFocusImage->SetPos(WindowSize.x / 2.f, WindowSize.y / 2.f);

	m_TitleImage->SetSize(350.f, 58.f);
	m_TitleLine->SetSize(350.f, 80.f);
	m_ButtonBackImage->SetSize(200.f, 350.f);
	m_ButtonFocusImage->SetSize(150.f, 50.f);

	m_TitleImage->SetTexture("ESCMenuTitleBar", TEXT("UI/escMenu_titleBar.png"));
	m_TitleLine->SetTexture("ESCMenuTitleLine", TEXT("UI/escMenu_titleBar_Line.png"));
	m_ButtonBackImage->SetTexture("ButtonBackImage", TEXT("UI/escMenu_ButtonBack_RGB.png"));
	m_ButtonFocusImage->SetTexture("ButtonFocusImage", TEXT("UI/escMenu_ButtonFocus.png"));

	m_TitleImage->SetUsePaperBurn(true);
	m_TitleImage->SetInverse(true);
	m_TitleImage->SetFinishTime(1.f);

	m_TitleLine->SetFadeInTime(0.5f);
	m_TitleLine->SetFadeState(Widget_Fade_State::FadeIn);
	m_ButtonBackImage->SetFadeInTime(0.5f);
	m_ButtonBackImage->SetFadeState(Widget_Fade_State::FadeIn);

	// vecMenuIconButton 초기화
	size_t vecSize = m_vecMenuIconButton.size();

	for (size_t i = 0; i < vecSize; ++i)
	{
		char Number[4] = "";
		sprintf_s(Number, "%d", (int)i);

		char Name[32] = "ESCMenuIconButton_";
		strcat_s(Name, Number);

		m_vecMenuIconButton[i] = CreateWidget<CButton>(Name);

		m_vecMenuIconButton[i]->SetZOrder(4);
		m_vecMenuIconButton[i]->SetPos(100.f + (i * 60.f), WindowSize.y / 2.f + 150.f);
		m_vecMenuIconButton[i]->SetSize(40.f, 40.f);

		switch (i)
		{
		case 0:
			m_vecMenuIconButton[i]->SetTexture(Button_State::Normal, "OptionIcon", TEXT("UI/option_icon.png"));
			m_vecMenuIconButton[i]->SetTexture(Button_State::MouseOn, "OptionIcon", TEXT("UI/option_icon.png"));
			m_vecMenuIconButton[i]->SetTexture(Button_State::Click, "OptionIcon", TEXT("UI/option_icon.png"));
			m_vecMenuIconButton[i]->SetTexture(Button_State::Disable, "OptionIcon", TEXT("UI/option_icon.png"));
			break;
		case 1:
			m_vecMenuIconButton[i]->SetTexture(Button_State::Normal, "ItemEquippedIcon", TEXT("UI/itemAndEquip_icon.png"));
			m_vecMenuIconButton[i]->SetTexture(Button_State::MouseOn, "ItemEquippedIcon", TEXT("UI/itemAndEquip_icon.png"));
			m_vecMenuIconButton[i]->SetTexture(Button_State::Click, "ItemEquippedIcon", TEXT("UI/itemAndEquip_icon.png"));
			m_vecMenuIconButton[i]->SetTexture(Button_State::Disable, "ItemEquippedIcon", TEXT("UI/itemAndEquip_icon.png"));
			break;
		}

		m_vecMenuIconButton[i]->SetTextureTint(Button_State::MouseOn, Vector4(0.49f, 0.89f, 0.36f, 1.f));
		m_vecMenuIconButton[i]->SetTextureTint(Button_State::Normal, Vector4(0.58f, 0.69f, 0.80f, 0.8f));

		m_vecMenuIconButton[i]->SetClickCallback<CESCWindow>(this, &CESCWindow::MenuIconClickCallback);
	}



	// vecSystemButton 초기화
	vecSize = m_vecSystemButton.size();

	for (size_t i = 0; i < vecSize; ++i)
	{
		char Number[4] = "";
		sprintf_s(Number, "%d", (int)i);

		char Name[32] = "ESCSystemButton_";
		strcat_s(Name, Number);

		m_vecSystemButton[i] = CreateWidget<CButton>(Name);

		m_vecSystemButton[i]->SetZOrder(4);

		m_vecSystemButton[i]->SetPos(WindowSize.x / 2.f - 90.f, WindowSize.y / 2.f + 90.f - (i * 55.f));
		m_vecSystemButton[i]->SetSize(150.f, 40.f);
		m_vecSystemButton[i]->SetFadeInTime(1.0f);
		m_vecSystemButton[i]->SetFadeState(Widget_Fade_State::FadeIn);


		char TextName[32] = "ESCButtonText_";
		strcat_s(TextName, Number);

		m_vecButtonText[i] = CreateWidget<CText>(TextName);

		m_vecButtonText[i]->SetZOrder(6);

		m_vecButtonText[i]->SetPos(WindowSize.x / 2.f - 90.f, WindowSize.y / 2.f + 90.f - (i * 55.f));
		m_vecButtonText[i]->SetSize(150.f, 40.f);
		m_vecButtonText[i]->SetAlignH(TEXT_ALIGN_H::Left);
		m_vecButtonText[i]->SetAlignV(TEXT_ALIGN_V::Middle);
		m_vecButtonText[i]->SetAlphaEnable(true);
		m_vecButtonText[i]->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.9f));
		m_vecButtonText[i]->SetFontSize(15.f);
		m_vecButtonText[i]->SetFadeInTime(1.5f);
		m_vecButtonText[i]->SetFadeState(Widget_Fade_State::FadeIn);
	}


	m_ButtonFocusImage->SetTextureTint(Vector4(0.f, 5.f, 0.f, 1.f));
	m_ButtonFocusImage->Enable(false);

	SetSystemMenu();

	Enable(false);
}

void CESCWindow::TrackingButton()
{
	Vector2 MousePos = CInput::GetInst()->GetMouseUIPos();

	size_t Size = m_vecSystemButton.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecSystemButton[i]->GetButtonState() == Button_State::MouseOn &&
			m_vecSystemButton[i]->IsMouseHovered())
		{
			// 현재 마우스와 겹친버튼과 이전 겹친버튼하고 다를때만 Focus이미지 이동.
			if (m_FocusingIndex != i)
			{
				m_ButtonFocusImage->Enable(true);

				m_ButtonFocusImage->SetPos(m_vecSystemButton[i]->GetWindowPos());

				m_vecButtonText[i]->SetColor(Vector4().White);

				SetExplainText((int)i);
			}
		}

		else
		{
			m_vecButtonText[i]->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.9f));
		}
	}
}

void CESCWindow::SetExplainText(int MenuIndex)
{
	CExplainWindow* Window = (CExplainWindow*)GetViewport()->FindWidgetWindow<CWidgetWindow>("ExplainWindow");

	if (!m_FadeDestroy && (!Window->IsEnable() || !Window->IsVisibility()))
	{
		Window->FadeEnable(true);
		Window->SetVisibility(true);
	}

	switch (MenuIndex)
	{
	case 0:
		if (m_CurrMenuIndex == 0)
		{
			Window->SetText(TEXT("게임 옵션을 설정합니다."));
		}
		break;
	case 1:
		if (m_CurrMenuIndex == 0)
		{
			Window->SetText(TEXT("게임을 종료합니다."));
		}
		break;
	}

}

void CESCWindow::MenuIconClickCallback()
{
	Vector2 MousePos = CInput::GetInst()->GetMouseUIPos();

	size_t Size = m_vecMenuIconButton.size();

	for (int i = 0; i < 2; ++i)
	{
		m_vecSystemButton[i]->ButtonEnable(true);
	}

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecMenuIconButton[i]->CollisionMouse(MousePos))
		{
			switch (i)
			{
				// Set menu to System
			case 0:
				SetSystemMenu();
				break;
			}

			m_CurrMenuIndex = (int)i;
			break;
		}
	}

	GetViewport()->FindWidgetWindow<CWidgetWindow>("ExplainWindow")->SetVisibility(false);
	m_ButtonFocusImage->Enable(false);
}


void CESCWindow::ExitCallback()
{
	// StartScene으로 전환.
	CEventManager::GetInst()->SetStageType(Stage_Type::None);
	CObjectManager::GetInst()->SaveCheckToPointFunc(Check_Type::None);
	
	CEventManager::GetInst()->CallEvent("SceneFadeOutStart");

	//HDR 창이 열려있으면 닫음
	if (CHDR::GetInst()->GetIsWindowOn())
	{
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->SetVisibility(false);
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Disable();

		CHDR::GetInst()->SetIsWindowOn(false);
	}

	if(GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow"))
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Destroy();
}

void CESCWindow::OptionCallback()
{
	if (!CHDR::GetInst()->GetIsWindowOn())
	{
		if (!GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow"))
		{
			GetViewport()->CreateWidgetWindow<CHDRWindow>("HDRWindow");
			CHDR::GetInst()->SetIsWindowOn(true);
		}
		else
		{
			CHDR::GetInst()->SetIsWindowOn(true);
			GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->SetVisibility(true);
			GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Enable();
		}
	}
	else if (CHDR::GetInst()->GetIsWindowOn())
	{
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->SetVisibility(false);
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Disable();
		CHDR::GetInst()->SetIsWindowOn(false);
	}
}

void CESCWindow::SetSystemMenu()
{
	for (int i = 0; i < 2; ++i)
	{
		switch (i)
		{
		case 0:
			m_vecSystemButton[i]->SetClickCallback<CESCWindow>(this, &CESCWindow::OptionCallback);
			m_vecButtonText[i]->SetText(TEXT("옵션"));
			break;
		case 1:
			m_vecSystemButton[i]->SetClickCallback<CESCWindow>(this, &CESCWindow::ExitCallback);
			m_vecButtonText[i]->SetText(TEXT("게임 종료"));
			break;
		}
	}
}

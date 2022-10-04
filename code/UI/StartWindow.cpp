
#include "StartWindow.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
#include "Widget/Button.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/SceneManager.h"
#include "../Scene/MainSceneMode.h"
#include "../Scene/LoadingSceneMode.h"
#include "Engine.h"
#include "Input.h"
#include "HDRWindow.h"
#include "HDR.h"
#include "../Object/EventManager.h"

CStartWindow::CStartWindow() :
	m_LightStart(false),
	m_TitleStart(false),
	m_PressStart(false),
	m_LoadingStart(false),
	m_FocusingIndex(-1)
{
	SetTypeID<CStartWindow>();

	m_vecMenuButton.resize(3);
	m_vecButtonText.resize(3);
}

CStartWindow::~CStartWindow()
{

}

void CStartWindow::Start()
{
	CWidgetWindow::Start();
}

bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(1280.f, 720.f);

	SetZOrder(2);

	InitWidgets(Vector2(1280.f, 720.f));

	CResourceManager::GetInst()->SoundPlay("MainMenu");

	return true;
}

void CStartWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (!m_TitleStart)
	{
		if (m_BackgroundImage->GetOpacity() >= 1.f)
		{
			m_TitleStart = true;
			m_EmblemImage->Enable(true);
			m_LogoImage->Enable(true);

			m_EmblemImage->StartPaperBurn();
		}
	}

	if (!m_LightStart)
	{
		if (m_LogoImage->GetOpacity() >= 1.f)
		{
			m_LightStart = true;
			m_LightEffectImage->Enable(true);
			
			m_EyeLightImage->Enable(true);
			//m_LightEffectImage->SetFadeIn(true);
			//m_EyeLightImage->SetFadeIn(true, true);
		}
	}

	if (m_LightStart)
	{
		if (m_EyeLightImage->GetOpacity() >= 1.f)
		{
			m_PressStart = true;
			m_EyeLightImage->SetFadeState(Widget_Fade_State::FadeOut);
			m_EyeLightImage->SetFadeOutTime(0.5f);
		}
	}

	if (m_EyeLightImage->IsEnable())
	{
		Vector2 Pos = m_EyeLightImage->GetPos();
		Vector2 Size = m_EyeLightImage->GetSize();
		
		Size += 250.f * DeltaTime;
		
		Pos -= (250.f * DeltaTime) / 2.f;
		
		float Angle = m_EyeLightImage->GetAngle();

		m_EyeLightImage->SetAngle(100.f * DeltaTime);

		m_EyeLightImage->SetSize(Size);
		m_EyeLightImage->SetPos(Pos);
	}

	if (m_TextBackImage->IsEnable())
	{
		TrackingButton();
	}

	if (m_LoadingStart)
	{
		if (m_ButtonFocusImage->GetOpacity() <= 0.f)
		{
			CSceneManager::GetInst()->CreateNextScene();
			CSceneManager::GetInst()->CreateSceneMode<CLoadingSceneMode>(false);
		}
	}
}

void CStartWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CStartWindow::Render()
{
	CWidgetWindow::Render();
}

void CStartWindow::InitWidgets(Vector2 WindowSize)
{
	m_BackgroundImage = CreateWidget<CImage>("Background");
	m_EmblemImage = CreateWidget<CImage>("EmblemImage");
	m_LogoImage = CreateWidget<CImage>("LogoImage");
	m_LightEffectImage = CreateWidget<CImage>("LightEffectImage");
	m_EyeLightImage = CreateWidget<CImage>("EyeLightImage");
	m_TextBackImage = CreateWidget<CImage>("TextBackImage");
	m_ButtonFocusImage = CreateWidget<CImage>("FocusImage");

	m_BackgroundImage->SetZOrder(2);
	m_EmblemImage->SetZOrder(3);
	m_LogoImage->SetZOrder(4);
	m_LightEffectImage->SetZOrder(6);
	m_EyeLightImage->SetZOrder(6);
	m_TextBackImage->SetZOrder(2);
	m_ButtonFocusImage->SetZOrder(3);

	m_BackgroundImage->SetSize(WindowSize);
	m_EmblemImage->SetSize(300.f, 300.f);
	m_LogoImage->SetSize(512.f, 128.f);
	m_LightEffectImage->SetSize(128.f, 128.f);
	m_EyeLightImage->SetSize(256.f, 256.f);
	m_TextBackImage->SetSize(350.f, 720.f);
	m_ButtonFocusImage->SetSize(250.f, 50.f);
	
	m_BackgroundImage->SetPos(WindowSize.x / 2.f - WindowSize.x / 2.f, WindowSize.y / 2.f - WindowSize.y / 2.f);
	m_EmblemImage->SetPos(WindowSize.x / 2.f - 150.f, WindowSize.y / 2.f);
	m_LogoImage->SetPos(WindowSize.x / 2.f - 256.f, WindowSize.y / 2.f - 100.f);
	m_LightEffectImage->SetPos(m_EmblemImage->GetWindowPos().x + 84.f, m_EmblemImage->GetWindowPos().y + 139.f);
	m_EyeLightImage->SetPos(m_EmblemImage->GetWindowPos().x + 23.f, m_EmblemImage->GetWindowPos().y + 84.f);
	m_TextBackImage->SetPos(WindowSize.x / 2.f - WindowSize.x / 2.f, WindowSize.y / 2.f - WindowSize.y / 2.f);
	
	m_BackgroundImage->SetTexture("StartBackgroundImage", TEXT("UI/StartScene/StartBackground.png"));
	m_EmblemImage->SetTexture("StartEmblemImage", TEXT("UI/StartScene/Emblem_Image.png"));
	m_LogoImage->SetTexture("TitleLogoImage", TEXT("UI/StartScene/Title_Image_WithLine.png"));
	m_LightEffectImage->SetTexture("LogoImageEffect1", TEXT("UI/StartScene/Emblem_Light.png"));
	m_EyeLightImage->SetTexture("UILightEffect2", TEXT("UI/StartScene/light_007.png"));
	m_TextBackImage->SetTexture("ShallowBlack", TEXT("UI/StartScene/title_bg.png"));
	m_ButtonFocusImage->SetTexture("ButtonFocusImage", TEXT("UI/escMenu_ButtonFocus.png"));

	size_t Size = m_vecMenuButton.size();

	for (size_t i = 0; i < Size; ++i)
	{
		char Number[4] = "";
		sprintf_s(Number, "%d", (int)i);

		char Name[32] = "StartMenuButton_";
		strcat_s(Name, Number);

		m_vecMenuButton[i] = CreateWidget<CButton>(Name);

		m_vecMenuButton[i]->SetZOrder(4);
		m_vecMenuButton[i]->SetSize(150.f, 50.f);
		m_vecMenuButton[i]->SetPos(100.f, WindowSize.y / 2.f + 200.f - (i * 60.f));
		m_vecMenuButton[i]->SetSound(Button_Sound_State::MouseOn, "UIButtonMouseOn");
		m_vecMenuButton[i]->SetSound(Button_Sound_State::Click, "UIButtonClick");

		char TextName[32] = "ButtonText_";
		strcat_s(TextName, Number);

		m_vecButtonText[i] = CreateWidget<CText>(TextName);

		m_vecButtonText[i]->SetZOrder(3);
		m_vecButtonText[i]->SetSize(150.f, 50.f);
		m_vecButtonText[i]->SetPos(100.f, WindowSize.y / 2.f + 200.f - (i * 60.f));
		m_vecButtonText[i]->SetAlignH(TEXT_ALIGN_H::Left);
		m_vecButtonText[i]->SetAlignV(TEXT_ALIGN_V::Middle);
		m_vecButtonText[i]->SetAlphaEnable(true);
		m_vecButtonText[i]->SetColor(Vector4(0.7f, 0.7f, 0.7f, 1.0f));
		m_vecButtonText[i]->SetFontSize(25.f);
		

		switch (i)
		{
		case 0:
			m_vecMenuButton[i]->SetClickCallback<CStartWindow>(this, &CStartWindow::StartButtonCallback);
			m_vecMenuButton[i]->SetSound(Button_Sound_State::Click, "UIStartButtonClick");
			m_vecButtonText[i]->SetText(TEXT("게임 시작"));
			break;
		case 1:
			m_vecMenuButton[i]->SetClickCallback<CStartWindow>(this, &CStartWindow::OptionButtonCallback);
			m_vecButtonText[i]->SetText(TEXT("옵션"));
			break;
		case 2:
			m_vecMenuButton[i]->SetClickCallback<CStartWindow>(this, &CStartWindow::ExitButtonCallback);
			m_vecButtonText[i]->SetText(TEXT("게임 종료"));
			break;
		}
	}

	m_BackgroundImage->SetClickCallback<CStartWindow>(this, &CStartWindow::PressClickCallback);

	auto	iter = m_WidgetList.begin();
	auto	iterEnd = m_WidgetList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetFadeState(Widget_Fade_State::FadeIn);
		(*iter)->SetFadeInTime(1.f);
		(*iter)->SetOpacity(0.f);
		(*iter)->Enable(false);
	}

	m_BackgroundImage->Enable(true);
	m_BackgroundImage->SetFadeInTime(2.f);

	m_EmblemImage->SetUsePaperBurn(true);
	m_EmblemImage->SetInverse(true);
	m_EmblemImage->SetFinishTime(2.f);
	
	m_EyeLightImage->SetFadeInTime(0.5f);

	m_ButtonFocusImage->SetTextureTint(Vector4(0.f, 5.f, 0.f, 1.f));
	m_ButtonFocusImage->SetFadeInTime(0.f);
}

void CStartWindow::TrackingButton()
{
	Vector2 MousePos = CInput::GetInst()->GetMouseUIPos();

	size_t Size = m_vecMenuButton.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecMenuButton[i]->GetButtonState() == Button_State::MouseOn &&
			m_vecMenuButton[i]->IsEnable())
		{
			// 현재 마우스와 겹친버튼과 이전 겹친버튼하고 다를때만 Focus이미지 이동.
			if (m_FocusingIndex != i)
			{
				m_FocusingIndex = (int)i;

				m_ButtonFocusImage->Enable(true);

				m_ButtonFocusImage->SetPos(m_vecMenuButton[i]->GetWindowPos());

				m_vecButtonText[i]->SetColor(Vector4().White);

				//SetExplainText((int)i);
			}
		}

		else
		{
			m_vecButtonText[i]->SetColor(Vector4(0.7f, 0.7f, 0.7f, 1.0f));
		}
	}
}

void CStartWindow::PressClickCallback()
{
	if (!m_PressStart)
		return;

	GetViewport()->GetScene()->GetResource()->SoundPlay("UIEffect");

	m_PressStart = false;
	
	m_EmblemImage->SetFadeState(Widget_Fade_State::FadeOut);
	m_LogoImage->SetFadeState(Widget_Fade_State::FadeOut);
	m_LightEffectImage->SetFadeState(Widget_Fade_State::FadeOut);
	m_EyeLightImage->SetFadeState(Widget_Fade_State::FadeOut);

	m_EmblemImage->SetFadeOutTime(0.4f);
	m_LogoImage->SetFadeOutTime(0.4f);
	m_LightEffectImage->SetFadeOutTime(0.4f);
	m_EyeLightImage->SetFadeOutTime(0.4f);

	m_TextBackImage->Enable(true);
	m_TextBackImage->SetFadeInTime(0.5f);

	size_t Size = m_vecMenuButton.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMenuButton[i]->Enable(true);
		m_vecMenuButton[i]->SetFadeInTime(1.f);
		m_vecButtonText[i]->Enable(true);
		m_vecButtonText[i]->SetFadeInTime(1.f);
	}

}

void CStartWindow::StartButtonCallback()
{
	m_LoadingStart = true;

	CEventManager::GetInst()->SetStageType(Stage_Type::Town);
	
	size_t Size = m_vecMenuButton.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecMenuButton[i]->ButtonEnable(false);
		m_vecMenuButton[i]->SetFadeState(Widget_Fade_State::FadeOut);
		m_vecMenuButton[i]->SetFadeOutTime(0.3f);
		m_vecButtonText[i]->SetFadeState(Widget_Fade_State::FadeOut);
		m_vecButtonText[i]->SetFadeOutTime(0.3f);
	}

	m_ButtonFocusImage->SetFadeState(Widget_Fade_State::FadeOut);
	m_ButtonFocusImage->SetFadeOutTime(0.5f);

	//HDR 창이 열려있으면 닫음
	if (CHDR::GetInst()->GetIsWindowOn())
	{
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->SetVisibility(false);
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Disable();
		CHDR::GetInst()->SetIsWindowOn(false);
	}

	if (GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow"))
	{
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Destroy();
	}
}

void CStartWindow::OptionButtonCallback()
{
	//HDR 옵션
	if (!CHDR::GetInst()->GetIsWindowOn())
	{
		if (!GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow"))
		{
			GetViewport()->CreateWidgetWindow<CHDRWindow>("HDRWindow");
			GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Enable();
			CHDR::GetInst()->SetIsWindowOn(true);
		}
		else
		{
			CHDR::GetInst()->SetIsWindowOn(true);
			GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->SetVisibility(true);
			GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Enable();
		}
	}
	else if(CHDR::GetInst()->GetIsWindowOn())
	{
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->SetVisibility(false);
		GetViewport()->FindWidgetWindow<CHDRWindow>("HDRWindow")->Disable();
		CHDR::GetInst()->SetIsWindowOn(false);
		
	}
	// Sound 조절, 그래픽관련 옵션 조정?
}

void CStartWindow::ExitButtonCallback()
{
	CEngine::GetInst()->Exit();
}

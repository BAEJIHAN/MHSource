
#include "PlayerHUD.h"
#include "Engine.h"
#include "Input.h"
#include "Widget/Image.h"
#include "Widget/ProgressBar.h"
#include "../Object/Player.h"
#include "Scene/SceneManager.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "../Object/TargetingCamera.h"

CPlayerHUD::CPlayerHUD() :
	m_Player(nullptr),
	m_ColorG(1.f),
	m_ColorB(1.f),
	m_Inverse(true)
{
	SetTypeID<CPlayerHUD>();
}

CPlayerHUD::CPlayerHUD(const CPlayerHUD& Window) :
	CWidgetWindow(Window)
{
	m_Player = Window.m_Player;
}

CPlayerHUD::~CPlayerHUD()
{
}

void CPlayerHUD::SetHPBar(float HP)
{
	m_HPBar->SetPercent(HP);
}

void CPlayerHUD::SetSPBar(float SP)
{
	m_SPBar->SetPercent(SP);
}

void CPlayerHUD::Start()
{
	CWidgetWindow::Start();
}

bool CPlayerHUD::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution RS = CEngine::GetInst()->GetRS();

	Vector2 vectorRS = Vector2((float)RS.Width, (float)RS.Height);

	SetSize(400.f, 300.f);

	SetPos(vectorRS.x / 2.f - 570.f, vectorRS.y / 2.f - 20.f);

	SetZOrder(3);

	CreateWidgets(Vector2(400.f, 300.f));

	return true;
}

void CPlayerHUD::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (!m_Player)
		m_Player = (CPlayer*)(CSceneManager::GetInst()->GetPlayerObject());

	else
	{
		float Stamina = m_Player->GetPlayerStamina();
		float MaxStamina = m_Player->GetPlayerMaxStamina();

		float Percent = Stamina / MaxStamina;

		SetSPBar(Percent);

		float HP = m_Player->GetPlayerHP();
		float MaxHP = m_Player->GetPlayerMaxHP();

		Percent = HP / MaxHP;

		SetHPBar(Percent);

		if (m_Player->GetHitBreath())
		{
			if (m_Inverse)
			{
				m_ColorG -= DeltaTime;
				m_ColorB -= DeltaTime;
			}

			else
			{
				m_ColorG += DeltaTime;
				m_ColorB += DeltaTime;
			}

			if (m_ColorG <= 0.f || m_ColorB <= 0.f)
			{
				m_Inverse = false;
			}
			else if(m_ColorG >= 1.f || m_ColorB >= 1.f)
			{
				m_Inverse = true;
			}
			m_HPBar->SetTextureTint(Vector4(1.f, m_ColorG, m_ColorB, 1.f));
		}

		else
		{
			m_HPBar->SetTextureTint(Vector4(1.f, 1.f, 1.f, 1.f));
		}
	}

}

void CPlayerHUD::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerHUD::Render()
{
	CWidgetWindow::Render();
}

void CPlayerHUD::CreateWidgets(Vector2 WindowSize)
{
	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	m_SPBar = CreateWidget<CProgressBar>("HPBar");
	m_HPBarBack = CreateWidget<CImage>("HPBarBack");
	m_SPBarBack = CreateWidget<CImage>("SPBarBack");
	

	m_HPBar->SetZOrder(3);	// 데미지를 입은 HP의 일정수준 자동회복할 수 있는 기능이 존재함.
	m_SPBar->SetZOrder(2);
	m_HPBarBack->SetZOrder(1);
	m_SPBarBack->SetZOrder(1);

	m_HPBarBack->SetPos(0.f, 300.f);
	m_HPBarBack->SetSize(369.f, 25.f);
	m_HPBarBack->SetTexture("GaugeBarTexture", TEXT("HUD/GaugeBarBack.png"));

	m_SPBarBack->SetPos(5.f, 270.f);
	m_SPBarBack->SetSize(270.f, 25.f);
	m_SPBarBack->SetTexture("GaugeBarTexture", TEXT("HUD/GaugeBarBack.png"));

	m_HPBar->SetPos(m_HPBarBack->GetWindowPos().x + 15.f, m_HPBarBack->GetWindowPos().y);
	m_HPBar->SetSize(m_HPBarBack->GetWindowSize().x - 25.f, m_HPBarBack->GetWindowSize().y);	// HP사이즈에 따라 Size 조절해야함.
	m_HPBar->SetDir(ProgressBar_Dir::RightToLeft);
	m_HPBar->SetTexture("HPBarTexture", TEXT("HUD/HPBar.png"));

	m_SPBar->SetPos(m_SPBarBack->GetWindowPos().x + 10.f, m_SPBarBack->GetWindowPos().y);
	m_SPBar->SetSize(m_SPBarBack->GetWindowSize().x - 20.f, m_SPBarBack->GetWindowSize().y);
	m_SPBar->SetDir(ProgressBar_Dir::RightToLeft);
	m_SPBar->SetTexture("SPBarTexture", TEXT("HUD/SPBar.png"));

}


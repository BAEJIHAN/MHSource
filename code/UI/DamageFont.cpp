
#include "DamageFont.h"
#include "Engine.h"
#include "Device.h"
#include "Widget/Number.h"
#include "Scene/SceneManager.h"
#include "../Object/Player.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"

CDamageFont::CDamageFont()	:
	m_Distance(0.f),
	m_DeltaTime(0.f),
	m_FontSizeX(15.f),
	m_FontSizeY(25.f),
	m_ColorTimeR(1.f),
	m_ColorTimeG(0.4f),
	m_ColorTimeB(0.f),
	m_ColorTimeA(1.f),
	m_ArrowCoatingState(Coating_State::Normal)
{
	SetTypeID<CDamageFont>();
}

CDamageFont::CDamageFont(const CDamageFont& Window) :
	CWidgetWindow(Window)
{
}

CDamageFont::~CDamageFont()
{
}


void CDamageFont::SetDamageNumber(int Number)
{
	m_Damage->SetNumber(Number);
}

void CDamageFont::Start()
{
	CWidgetWindow::Start();

	m_Player = (CPlayer*)CSceneManager::GetInst()->GetPlayerObject();

	if (m_Player)
	{
		Vector3 PlayerPos = m_Player->GetWorldPos();

		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		m_Damage->SetSize(m_FontSizeX, m_FontSizeY);

		Matrix ViewPos = Camera->GetViewMatrix();

		Matrix ProjPos = Camera->GetProjMatrix();

		Matrix matWorld, matRotation, matPosition;

		matWorld.Identity();

		matRotation.Rotation(m_Rotation);

		matPosition.Translation(m_HitPos);

		matWorld = matRotation * matPosition;

		Matrix matWVP = matWorld * ViewPos * ProjPos;

		Vector4 WorldToScreen = Vector4(0.f, 0.f, 0.f, 1.f);
		
		Vector4 ConvertVector = XMVector4Transform(WorldToScreen.Convert(), matWVP.m);

		float WorldToScreenX = ConvertVector.x / ConvertVector.w;
		float WorldToScreenY = ConvertVector.y / ConvertVector.w;
		float WorldToScreenZ = ConvertVector.z / ConvertVector.w;

		// -1 ~ 1 구간을 0 ~ 1 구간으로 변경
		float ScreenNormalX = (WorldToScreenX + 1.f) * 0.5f;
		float ScreenNormalY = (WorldToScreenY + 1.f) * 0.5f;
		ScreenNormalY = 1.f - ScreenNormalY;

		Resolution RS = CDevice::GetInst()->GetResolution();

		float ScreenX = ScreenNormalX * RS.Width;
		float ScreenY = ScreenNormalY * RS.Height;

		m_Damage->SetPos(ScreenX, ScreenY);
	}

}

bool CDamageFont::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	//SetSize(30.f, 30.f);

	m_Damage = CreateWidget<CNumber>("DamageFont");
	std::vector<TCHAR*> vecFileName;

	for (int i = 0; i < 10; ++i)
	{
		TCHAR* FileName = new TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("UI/Number/Number%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Damage->SetTexture("Number", vecFileName);
	m_Damage->AddFrameData(10);

	//m_Damage->SetPos(600.f, 100.f);

	//m_Damage->SetNumber(5);

	m_Damage->SetZOrder(5);
	//m_Damage->SetTextureTint(255, 255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}

	return true;
}

void CDamageFont::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	m_DeltaTime += DeltaTime;

	if (m_DeltaTime >= 1.5f)
		Destroy();

	switch (m_ArrowCoatingState)
	{
	case Coating_State::Normal:
	{

	}
		break;
	case Coating_State::Strong:
	{

	}
		break;
	case Coating_State::Explosion:
	{
		if (m_DeltaTime >= 0.6f)
		{
			m_ColorTimeG += DeltaTime;

			if (m_ColorTimeG >= 0.9f)
			{
				m_ColorTimeB += DeltaTime * 3.f;

				if (m_ColorTimeB >= 0.7f)
					m_ColorTimeA -= DeltaTime * 4.f;
			}
		}

		if (m_ColorTimeG >= 1.f)
			m_ColorTimeG = 1.f;

		if (m_ColorTimeB >= 1.f)
			m_ColorTimeB = 1.f;

		if (m_ColorTimeA <= 0.f)
			m_ColorTimeA = 0.f;

		m_Damage->SetTextureTint(Vector4(m_ColorTimeR, m_ColorTimeG, m_ColorTimeB, m_ColorTimeA));
	}
		break;
	}
}

void CDamageFont::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CDamageFont::Render()
{
	CWidgetWindow::Render();
}


#include "CarvingWindow.h"
#include "Device.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
#include "../Object/Player.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Component/CameraComponent.h"

CCarvingWindow::CCarvingWindow()	:
	m_Player(nullptr),
	m_CenterUIFadeOut(false),
	m_FadeOpacity(1.f),
	m_Monster(Monster_Name::None)
{
}

CCarvingWindow::CCarvingWindow(const CCarvingWindow& Window) :
	CWidgetWindow(Window)
{
}

CCarvingWindow::~CCarvingWindow()
{
}

void CCarvingWindow::Start()
{
	CWidgetWindow::Start();

	switch (m_Monster)
	{
	case Monster_Name::Barnos:
		m_Icon = CreateWidget<CImage>("BarnosIcon");
		m_Icon->SetTexture("BarnosIcon", TEXT("UI/Carving/BarnosIcon.dds"));

		m_MonsterName->SetText(TEXT("바르노스"));
		//m_MonsterName->SetSize()
		break;
	case Monster_Name::Jagras:
		m_Icon = CreateWidget<CImage>("JagrasIcon");
		m_Icon->SetTexture("JagrasIcon", TEXT("UI/Carving/JagrasIcon.dds"));

		m_MonsterName->SetText(TEXT("자그라스"));
		break;
	case Monster_Name::Kestodon:
		m_Icon = CreateWidget<CImage>("KestodonIcon");
		m_Icon->SetTexture("KestodonIcon", TEXT("UI/Carving/KestodonIcon.dds"));

		m_MonsterName->SetText(TEXT("케스토돈"));
		break;
	case Monster_Name::Vespoid:
		m_Icon = CreateWidget<CImage>("VespoidIcon");
		m_Icon->SetTexture("VespoidIcon", TEXT("UI/Carving/VespoidIcon.dds"));

		m_MonsterName->SetText(TEXT("베스포이드"));
		break;
	case Monster_Name::Anjanath:
		m_Icon = CreateWidget<CImage>("AnjanathIcon");
		m_Icon->SetTexture("AnjanathIcon", TEXT("UI/Carving/AnjanathIcon.dds"));

		m_MonsterName->SetText(TEXT("안자냐프"));
		break;
	case Monster_Name::Rathalos:
		m_Icon = CreateWidget<CImage>("RathalosIcon");
		m_Icon->SetTexture("RathalosIcon", TEXT("UI/Carving/RathalosIcon.dds"));

		m_MonsterName->SetText(TEXT("리오레우스"));
		break;
	}
}

bool CCarvingWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(400.f, 200.f);

	m_CarvingCenter = CreateWidget<CImage>("CarvingCenter");

	m_CarvingCenter->SetTexture("CarvingCenter", TEXT("UI/Carving/CarvingCenterUI.dds"));
	m_CarvingCenter->SetSize(170.f, 80.f);
	m_CarvingCenter->SetTextureTint(Vector4(1.f, 0.65f, 0.f, 1.f));

	m_CarvingEffect = CreateWidget<CImage>("CarvingEffect");
	m_CarvingEffect->SetTexture("CarvingEffect", TEXT("UI/Carving/CarvingCenterEffect.dds"));
	m_CarvingEffect->SetSize(84.f, 85.f);
	m_CarvingEffect->SetTextureTint(Vector4(1.f, 0.65f, 0.f, 1.f));
	m_CarvingEffect->SetZOrder(2);

	m_FButtonImage = CreateWidget<CImage>("FButtonImage");
	m_FButtonImage->SetTexture("FButtonImage", TEXT("UI/Carving/FButton.dds"));
	m_FButtonImage->SetSize(30.f, 30.f);
	m_FButtonImage->SetZOrder(3);

	m_MonsterName = CreateWidget<CText>("IconText");
	m_MonsterName->SetSize(100.f, 30.f);
	m_MonsterName->SetFontSize(15.f);
	m_MonsterName->SetColor(1.f, 1.f, 1.f);
	m_MonsterName->SetShadowEnable(true);
	m_MonsterName->SetShadowColor(0.f, 0.f, 0.f);

	m_Player = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetSceneMode()->GetPlayerObject();

	return true;
}

void CCarvingWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_Player)
	{
		Vector3 PlayerPos = m_Player->GetWorldPos();

		PlayerPos.y += 7.f;

		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

		Matrix ViewPos = Camera->GetViewMatrix();

		Matrix ProjPos = Camera->GetProjMatrix();

		Matrix matWorld, matRotation, matPosition;

		matWorld.Identity();

		matRotation.Rotation(m_Player->GetWorldRot());

		matPosition.Translation(PlayerPos);

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

		m_CarvingCenter->SetPos(ScreenX, ScreenY);
		m_CarvingEffect->SetPos(ScreenX - 15.f, ScreenY - 2.f);
		m_Icon->SetPos(ScreenX + 1.f, ScreenY + 15.f);
		m_FButtonImage->SetPos(ScreenX + 28.f, ScreenY + 10.f);

		switch (m_Monster)
		{
		case Monster_Name::Barnos:
			m_MonsterName->SetPos(ScreenX + 60.f, ScreenY + 35.f);
			break;
		case Monster_Name::Jagras:
			m_MonsterName->SetPos(ScreenX + 60.f, ScreenY + 35.f);
			break;
		case Monster_Name::Kestodon:
			m_MonsterName->SetPos(ScreenX + 60.f, ScreenY + 35.f);
			break;
		case Monster_Name::Vespoid:
			m_MonsterName->SetPos(ScreenX + 52.f, ScreenY + 35.f);
			break;
		case Monster_Name::Anjanath:
			m_MonsterName->SetPos(ScreenX + 60.f, ScreenY + 35.f);
			break;
		case Monster_Name::Rathalos:
			m_MonsterName->SetPos(ScreenX + 52.f, ScreenY + 35.f);
			break;
		}

	}

	if (m_CenterUIFadeOut)
	{
		m_FadeOpacity -= DeltaTime;

		if (m_FadeOpacity <= 0.f)
			m_FadeOpacity = 0.f;

		m_MonsterName->SetOpacity(m_FadeOpacity);
		m_MonsterName->SetShadowOpacity(m_FadeOpacity);
	}
}

void CCarvingWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CCarvingWindow::Render()
{
	CWidgetWindow::Render();
}


#include "CarvingRightWindow.h"
#include "Device.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

CCarvingRightWindow::CCarvingRightWindow() :
	m_Player(nullptr),
	m_BoolNewUIEnable(false),
	m_DestroyTime(0.f),
	m_Monster(Monster_Name::None)
{
}

CCarvingRightWindow::CCarvingRightWindow(const CCarvingRightWindow& Window) :
	CWidgetWindow(Window)
{
}

CCarvingRightWindow::~CCarvingRightWindow()
{
}

void CCarvingRightWindow::Start()
{
	CWidgetWindow::Start();

	switch (m_Monster)
	{
	case Monster_Name::Barnos:
		m_Icon = CreateWidget<CImage>("BarnosRandomIcon");
		m_Icon->SetTexture("BarnosRandomIcon", TEXT("UI/Carving/BarnosRandomIcon.dds"));
		m_Icon->SetSize(50.f, 50.f);
		m_Icon->SetPos(m_CarvingRight->GetPos().x + 7.f, m_CarvingRight->GetPos().y + 21.f);

		m_MonsterName->SetText(TEXT("바르노스의 ?"));
		m_MonsterName->SetPos(m_CarvingRight->GetPos().x + 60.f, m_CarvingRight->GetPos().y + 40.f);
		//m_MonsterName->SetSize()
		break;
	case Monster_Name::Jagras:
		m_Icon = CreateWidget<CImage>("JagrasRandomIcon");
		m_Icon->SetTexture("JagrasRandomIcon", TEXT("UI/Carving/JagrasRandomIcon.dds"));
		m_Icon->SetSize(50.f, 50.f);
		m_Icon->SetPos(m_CarvingRight->GetPos().x + 7.f, m_CarvingRight->GetPos().y + 21.f);
		m_Icon->SetZOrder(2);

		m_MonsterName->SetText(TEXT("자그라스의 ?"));
		m_MonsterName->SetPos(m_CarvingRight->GetPos().x + 60.f, m_CarvingRight->GetPos().y + 40.f);
		break;
	case Monster_Name::Kestodon:
		m_Icon = CreateWidget<CImage>("KestodonRandomIcon");
		m_Icon->SetTexture("KestodonRandomIcon", TEXT("UI/Carving/KestodonRandomIcon.dds"));
		m_Icon->SetSize(50.f, 50.f);
		m_Icon->SetPos(m_CarvingRight->GetPos().x + 7.f, m_CarvingRight->GetPos().y + 21.f);
		m_Icon->SetZOrder(2);

		m_MonsterName->SetText(TEXT("케스토돈의 ?"));
		m_MonsterName->SetPos(m_CarvingRight->GetPos().x + 60.f, m_CarvingRight->GetPos().y + 40.f);
		break;
	case Monster_Name::Vespoid:
		m_Icon = CreateWidget<CImage>("VespoidRandomIcon");
		m_Icon->SetTexture("VespoidRandomIcon", TEXT("UI/Carving/VespoidRandomIcon.dds"));
		m_Icon->SetSize(50.f, 50.f);
		m_Icon->SetPos(m_CarvingRight->GetPos().x + 7.f, m_CarvingRight->GetPos().y + 21.f);
		m_Icon->SetZOrder(2);

		m_MonsterName->SetText(TEXT("베스포이드의 ?"));
		m_MonsterName->SetPos(m_CarvingRight->GetPos().x + 53.f, m_CarvingRight->GetPos().y + 40.f);
		break;
	case Monster_Name::Anjanath:
		m_Icon = CreateWidget<CImage>("BossRandomIcon");
		m_Icon->SetTexture("BossRandomIcon", TEXT("UI/Carving/BossRandomIcon.dds"));
		m_Icon->SetSize(50.f, 50.f);
		m_Icon->SetPos(m_CarvingRight->GetPos().x + 7.f, m_CarvingRight->GetPos().y + 21.f);
		m_Icon->SetZOrder(2);

		m_MonsterName->SetText(TEXT("안자냐프의 ?"));
		m_MonsterName->SetPos(m_CarvingRight->GetPos().x + 60.f, m_CarvingRight->GetPos().y + 40.f);
		break;
	case Monster_Name::Rathalos:
		m_Icon = CreateWidget<CImage>("BossRandomIcon");
		m_Icon->SetTexture("BossRandomIcon", TEXT("UI/Carving/BossRandomIcon.dds"));
		m_Icon->SetSize(50.f, 50.f);
		m_Icon->SetPos(m_CarvingRight->GetPos().x + 7.f, m_CarvingRight->GetPos().y + 21.f);
		m_Icon->SetZOrder(2);

		m_MonsterName->SetText(TEXT("리오레우스의 ?"));
		m_MonsterName->SetPos(m_CarvingRight->GetPos().x + 53.f, m_CarvingRight->GetPos().y + 40.f);
		break;
	}
}

bool CCarvingRightWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(400.f, 200.f);

	m_CarvingRight = CreateWidget<CImage>("CarvingRight");
	m_CarvingRight->SetTexture("CarvingRight", TEXT("UI/Carving/CarvingCenterUI.dds"));
	m_CarvingRight->SetSize(200.f, 90.f);
	m_CarvingRight->SetTextureTint(Vector4(1.f, 0.65f, 0.f, 1.f));
	m_CarvingRight->SetPos(1100.f, 290.f);
	m_CarvingRight->SetZOrder(1);

	m_BackImage = CreateWidget<CImage>("CarvingBackIcon");
	m_BackImage->SetTexture("CarvingBack", TEXT("UI/Carving/BackBlackIcon.dds"));
	m_BackImage->SetPos(m_CarvingRight->GetPos().x - 5.f, m_CarvingRight->GetPos().y + 8.f);
	m_BackImage->SetSize(75.f, 75.f);

	m_MonsterName = CreateWidget<CText>("IconText");
	m_MonsterName->SetSize(120.f, 30.f);
	m_MonsterName->SetFontSize(15.f);
	m_MonsterName->SetColor(1.f, 1.f, 1.f);
	m_MonsterName->SetShadowEnable(true);
	m_MonsterName->SetShadowColor(0.f, 0.f, 0.f);
	m_MonsterName->SetZOrder(2);


	return true;
}

void CCarvingRightWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	m_DestroyTime += DeltaTime;

	// 해당 윈도우는 무조건 5초뒤에 사라진다.
	if (m_DestroyTime >= 7.f)
	{
		this->FadeDestroy();
	}

	// 해당 UI가 표시되고 있는 상태에서 갈무리를 한 번 더하게되면 동일한 자리에 생기기 때문에
	// 방지를 위해 해당 윈도우의 Y값을 일정량 높힌다.
	if (m_BoolNewUIEnable)
	{
		m_BoolNewUIEnable = false;

		this->SetPos(this->GetWindowPos().x, this->GetWindowPos().y + 65.f);
	}
}

void CCarvingRightWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CCarvingRightWindow::Render()
{
	CWidgetWindow::Render();
}

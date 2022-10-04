
#include "MinimapWindow.h"
#include "Engine.h"
#include "Widget/Image.h"
#include "MiniMap.h"
#include "GameObject/GameObject.h"
#include "Component/Arm.h"
#include "Component/Transform.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "../Object/EventManager.h"
#include "../Object/Monster.h"
#include "../Object/Anjanath.h"
#include "../Object/Rathalos.h"
#include "../Object/Barnos.h"
#include "../Object/Vespoid.h"
#include "../Object/Kestodon.h"
#include "../Object/Jagras.h"
#include "../Scene/MainSceneMode.h"


CMinimapWindow::CMinimapWindow() :
	m_Count(0)
{
	SetTypeID<CMinimapWindow>();
}

CMinimapWindow::~CMinimapWindow()
{
}

void CMinimapWindow::SetMapSize(Vector2 Size)
{
	m_Minimap->SetMapSize(Size);
}

void CMinimapWindow::Start()
{
	CWidgetWindow::Start();

	m_PlayerObj = GetViewport()->GetScene()->GetPlayerObject();

	m_CameraArm = m_PlayerObj->FindComponentFromType<CArm>();

	std::list<CSharedPtr<class CGameObject>> ObjList = GetViewport()->GetScene()->GetObjectList();

	auto	iter = ObjList.begin();
	auto	iterEnd = ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		size_t Type = (*iter)->GetTypeID();

		CImage* Icon = nullptr;

		if (Type == typeid(CBarnos).hash_code())
		{
			Icon = CreateWidget<CImage>((*iter)->GetName());
			Icon->SetTexture("BarnosIcon", TEXT("UI/Carving/BarnosIcon.dds"));
			Icon->SetZOrder(5);
			Icon->SetCenterPivot(true);
			Icon->SetSize(Vector2(40.f, 40.f));

			m_vecMonsterUI.push_back(Icon);
			m_vecMonsterObj.push_back(*iter);
		}

		else if (Type == typeid(CVespoid).hash_code())
		{
			Icon = CreateWidget<CImage>((*iter)->GetName());
			Icon->SetTexture("VespoidIcon", TEXT("UI/Carving/VespoidIcon.dds"));
			Icon->SetZOrder(5);
			Icon->SetCenterPivot(true);
			Icon->SetSize(Vector2(40.f, 40.f));

			m_vecMonsterUI.push_back(Icon);
			m_vecMonsterObj.push_back(*iter);
		}

		else if (Type == typeid(CJagras).hash_code())
		{
			Icon = CreateWidget<CImage>((*iter)->GetName());
			Icon->SetTexture("JagrasIcon", TEXT("UI/Carving/JagrasIcon.dds"));
			Icon->SetZOrder(5);
			Icon->SetCenterPivot(true);
			Icon->SetSize(Vector2(40.f, 40.f));

			m_vecMonsterUI.push_back(Icon);
			m_vecMonsterObj.push_back(*iter);
		}

		else if (Type == typeid(CKestodon).hash_code())
		{
			Icon = CreateWidget<CImage>((*iter)->GetName());
			Icon->SetTexture("KestodonIcon", TEXT("UI/Carving/KestodonIcon.dds"));
			Icon->SetZOrder(5);
			Icon->SetCenterPivot(true);
			Icon->SetSize(Vector2(40.f, 40.f));

			m_vecMonsterUI.push_back(Icon);
			m_vecMonsterObj.push_back(*iter);
		}

		else if (Type == typeid(CAnjanath).hash_code())
		{
			Icon = CreateWidget<CImage>((*iter)->GetName());
			Icon->SetTexture("AnjanathIcon", TEXT("UI/Carving/AnjanathIcon.dds"));
			Icon->SetZOrder(5);
			Icon->SetCenterPivot(true);

			m_vecMonsterUI.push_back(Icon);
			m_vecMonsterObj.push_back(*iter);
		}

		else if (Type == typeid(CRathalos).hash_code())
		{
			Icon = CreateWidget<CImage>((*iter)->GetName());
			Icon->SetTexture("RathalosIcon", TEXT("UI/Carving/RathalosIcon.dds"));
			Icon->SetZOrder(5);
			Icon->SetCenterPivot(true);

			m_vecMonsterUI.push_back(Icon);
			m_vecMonsterObj.push_back(*iter);
		}
	}
}

bool CMinimapWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution RS = CEngine::GetInst()->GetRS();

	Vector2 vectorRS = Vector2((float)RS.Width, (float)RS.Height);

	SetSize(300.f, 300.f);

	SetPos(vectorRS.x / 2.f - 600.f, vectorRS.y / 2.f - 320.f);

	SetZOrder(3);

	CreateWidgets(Vector2(300.f, 300.f));

	CEventManager::GetInst()->AddEventCallback<CMinimapWindow>("PlayerMonsterContant", this, &CMinimapWindow::PlayerContantSpotted);
	CEventManager::GetInst()->AddEventCallback<CMinimapWindow>("PlayerMonsterRelease", this, &CMinimapWindow::PlayerContantRelease);

	return true;
}

void CMinimapWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	
	float PlayerRotY = m_PlayerObj->GetRelativeRot().y - 180.f;
	float CameraRotY = m_CameraArm->GetRelativeRot().y;

	m_PlayerIcon->SetAngle(-PlayerRotY);
	m_PlayerViewImage->SetAngle(-CameraRotY);

	CalcMonsters();
}

void CMinimapWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}
	
void CMinimapWindow::Render()
{
	CWidgetWindow::Render();
}

void CMinimapWindow::CreateWidgets(Vector2 WindowSize)
{
	m_Minimap = CreateWidget<CMinimap>("MinimapWidget");
	m_MinimapFrame = CreateWidget<CImage>("MinimapFrame");
	m_PlayerIcon = CreateWidget<CImage>("MinimapPlayerIcon");
	m_PlayerViewImage = CreateWidget<CImage>("PlayerViewRange");
	m_NorthIcon = CreateWidget<CImage>("NorthIcon");
	m_ContantRing = CreateWidget<CImage>("ContantRing");

	m_Minimap->SetSize(200.f, 200.f);
	m_Minimap->SetPos(50.f, 50.f);
	m_Minimap->SetTexture("MinimapFrame", TEXT("UI/Minimap.png"));
	m_Minimap->SetZOrder(2);

	m_MinimapFrame->SetSize(250.f, 250.f);
	m_MinimapFrame->SetPos(m_Minimap->GetWindowPos() - 25.f);
	m_MinimapFrame->SetTexture("MinimapFrame", TEXT("UI/Minimap.png"));
	m_MinimapFrame->SetZOrder(1);

	m_ContantRing->SetSize(270.f, 270.f);
	m_ContantRing->SetPos(m_Minimap->GetWindowPos() - 35.f);
	m_ContantRing->SetTexture("ContantRing", TEXT("UI/ContantRing.png"));
	m_ContantRing->SetTextureTint(Vector4().Red);
	m_ContantRing->SetOpacity(0.f);
	m_ContantRing->SetZOrder(5);

	m_NorthIcon->SetSize(25.f, 25.f);
	m_NorthIcon->SetPos(m_Minimap->GetWindowPos().x + 85.f, m_Minimap->GetWindowPos().y + 170.f);
	m_NorthIcon->SetTexture("NorthIcon", TEXT("UI/NorthN.png"));
	m_NorthIcon->SetZOrder(3);

	m_PlayerIcon->SetSize(30.f, 30.f);
	m_PlayerIcon->SetPos(m_Minimap->GetWindowPos() + 100.f);
	m_PlayerIcon->SetTexture("MinimapPlayerIcon", TEXT("UI/minimap_player.png"));
	m_PlayerIcon->SetZOrder(4);
	m_PlayerIcon->SetCenterPivot(true);
	
	m_PlayerViewImage->SetSize(180.f, 180.f);
	m_PlayerViewImage->SetPos(m_Minimap->GetWindowPos() + 100.f);
	m_PlayerViewImage->SetTexture("PlayerViewImage", TEXT("UI/minimap_player_view.png"));
	m_PlayerViewImage->SetZOrder(5);
	m_PlayerViewImage->SetCenterPivot(true);
}

void CMinimapWindow::CalcMonsters()
{
	Vector3 PlayerPos = m_PlayerObj->GetWorldPos();

	size_t Size = m_vecMonsterUI.size();

	float MinimapSize = m_Minimap->GetMinimapSize();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecMonsterObj[i] && m_vecMonsterObj[i]->IsActive())
		{
			Vector3 Pos = m_vecMonsterObj[i]->GetWorldPos();

			Pos.y = 0.f;
			PlayerPos.y = 0.f;

			float Dist = PlayerPos.Distance(Pos);

			if (Dist < MinimapSize - 40.f)
			{
				if (!m_vecMonsterUI[i]->IsEnable())
				{
					m_vecMonsterUI[i]->Enable(true);
				}

				Vector3 Dir = Pos - PlayerPos;

				Dir.Normalize();
				
				float NormalizeDist = Dist / (MinimapSize - 40.f);

				Vector2 MonsterIconPos = Vector2(Dir.x * (NormalizeDist * 100.f), Dir.z * (NormalizeDist * 100.f));

				m_vecMonsterUI[i]->SetPos(m_PlayerIcon->GetWindowPos() + MonsterIconPos);
			}

			else
			{
				m_vecMonsterUI[i]->Enable(false);
				m_vecMonsterUI[i]->SetPos(0.f, 0.f);
			}
		}

		else
		{
			if (m_vecMonsterUI[i] && m_vecMonsterUI[i]->IsEnable())
			{
				m_vecMonsterUI[i]->Enable(false);
				m_vecMonsterUI[i]->SetPos(0.f, 0.f);
			}
		}

	}
}

void CMinimapWindow::PlayerContantSpotted()
{
	if (m_Count <= 0)
	{
		m_ContantRing->SetFadeState(Widget_Fade_State::FadeIn);
		m_ContantRing->SetFadeInTime(0.3f);
		m_ContantRing->SetDuration(1.5f);
		m_ContantRing->SetFadeOutTime(0.3f);
		m_ContantRing->SetFadeLoop(true);

		if (!m_ContantRing->IsEnable())
		{
			m_ContantRing->Enable(true);
		}
	}

	++m_Count;
}

void CMinimapWindow::PlayerContantRelease()
{
	if (m_Count >= 0)
	{
		--m_Count;

		if (m_Count == 0)
		{
			m_ContantRing->SetFadeLoop(false);
			m_ContantRing->SetFadeOutTime(2.f);
		}
	}
}


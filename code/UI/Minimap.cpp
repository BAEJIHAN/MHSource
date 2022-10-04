
#include "Minimap.h"
#include "Widget/WidgetWindow.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Input.h"
#include "Resource/Shader/WidgetConstantBuffer.h"
#include "Resource/Shader/MinimapShader.h"
#include "../Object/EventManager.h"

CMinimap::CMinimap() :
	m_ClipMapSize(300.f, 300.f),
	m_MapTextureSize(229.f, 229.f)
{
}

CMinimap::~CMinimap()
{
}

bool CMinimap::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CMinimap::SetMapTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName))
			return false;

		m_SrcMapTexture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
		m_MinimapTexture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture("EngineTexture");
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		m_SrcMapTexture = CResourceManager::GetInst()->FindTexture(Name);
		m_MinimapTexture = CResourceManager::GetInst()->FindTexture("EngineTexture");
	}
	
	SetUseTexture(true);

	return true;
}

bool CMinimap::SetTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, FullPath))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}


	SetUseTexture(true);

	return true;
}

bool CMinimap::SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName,
	const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, vecFileName, PathName))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CMinimap::SetTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, vecFullPath))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}


	SetUseTexture(true);

	return true;
}

void CMinimap::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CMinimap::SetTextureTint(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CMinimap::Start()
{
	CWidget::Start();

	if (!m_Info.vecFrameData.empty())
		m_Info.FrameTime = m_Info.PlayTime / m_Info.vecFrameData.size();

	m_MapTextureSize = m_MapSize;

	switch (CEventManager::GetInst()->GetLoadStageType())
	{
		case Stage_Type::Town:
		{
			SetMapTexture("TownMapTexture", TEXT("UI/Map/TownScene_Minimap.png"));
			break;
		}
		case Stage_Type::Stage1:
		{
			SetMapTexture("1StageMapTexture", TEXT("UI/Map/1Stage_Minimap.png"));
			break;
		}
		case Stage_Type::Stage2:
		{
			SetMapTexture("2StageMapTexture", TEXT("UI/Map/2Stage_Minimap.png"));
			break;
		}
	}
}

bool CMinimap::Init()
{
	if (!CWidget::Init())
		return false;

	m_Shader = CResourceManager::GetInst()->FindShader("MinimapShader");

	return true;
}

void CMinimap::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	CGameObject* Player = nullptr;

	if (m_Owner->GetViewport())
		Player = m_Owner->GetViewport()->GetScene()->GetPlayerObject();

	if (!Player)
	{
		return;
	}
	
	// 미니맵이 Teemo로 변경됐을경우, 오류 발생한 것.
	// 	   아래 사항이 수정됐는지 확인할 것.
	// 
	// 1. 지형의 Map Size가 변경됐는가?
	// 2. Minimap Texture의 크기가 변경됐는가?
	// 3. 플레이어 위치가 -값인가?

	m_PlayerPos = Vector2(Player->GetWorldPos().x, Player->GetWorldPos().z);

	if (m_PlayerPrevPos.Distance(m_PlayerPos) < 1.f)
	{
		return;
	}

	Vector2 MinimapLT = Vector2(m_PlayerPos.x - (m_ClipMapSize.x / 2.f), 
		m_MapTextureSize.y - (m_PlayerPos.y + (m_ClipMapSize.y / 2.f)));

	// 미니맵 경계선 Offset 설정
	MinimapLT += (m_ClipMapSize / 2.f);

	if( MinimapLT.x < 0.f || MinimapLT.y < 0.f ||
		MinimapLT.x > (float)m_SrcMapTexture->GetWidth() - (m_ClipMapSize.x / 2.f) ||
		MinimapLT.y > (float)m_SrcMapTexture->GetHeight() - (m_ClipMapSize.y / 2.f))
	{
		return;
	}

	
	Rect CropRect = { (size_t)MinimapLT.x, (size_t)MinimapLT.y, (size_t)m_ClipMapSize.x, (size_t)m_ClipMapSize.y };

	HRESULT hr = CopyRectangle(*m_SrcMapTexture->GetTextureImage()->GetImage(0, 0, 0), CropRect,
		*m_MinimapTexture->GetTextureImage()->GetImage(0, 0, 0), TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, 0, 0);

	m_MinimapTexture->ReleaseResourceView();
	m_MinimapTexture->CreateResource(0);

	m_PlayerPrevPos = m_PlayerPos;
}

void CMinimap::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CMinimap::Render()
{
	if (m_Info.Texture)
	{
		m_Info.Texture->SetShader(0, (int)Buffer_Shader_Type::Pixel, 0);
	}
	
	if (m_MinimapTexture)
	{
		m_MinimapTexture->SetShader(4, (int)Buffer_Shader_Type::Pixel, 0);
	}
	
	m_Tint = m_Info.Tint;

	CWidget::Render();
}

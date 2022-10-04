
#include "LandScapeObj.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "../UI/MinimapWindow.h"

CLandScapeObj::CLandScapeObj()	:
	m_CountX(500),
	m_CountZ(500),
	m_First(false)
{
	SetTypeID<CLandScapeObj>();
}

CLandScapeObj::CLandScapeObj(const CLandScapeObj& obj) :
	CGameObject(obj)
{
	m_LandScape	 = (CLandScape*)FindComponent("LandScape");

	m_CountX = obj.m_CountX;
	m_CountZ = obj.m_CountZ;

	m_First = false;
}

CLandScapeObj::~CLandScapeObj()
{
}

bool CLandScapeObj::Init()
{
	m_LandScape = CreateComponent<CLandScape>("LandScape");
	m_LandScape->AddMaterial("LandScape");
	m_LandScape->SetDetailLevel(30.f);
	m_LandScape->SetSplatCount(4);

	return true;
}

void CLandScapeObj::Update(float DeltaTime)
{
	if (!m_First)
	{
		m_First = true;

		m_LandScape->CreateLandScape("LandScape", 300, 300);

		m_Scene->GetNavigation3DManager()->SetNavData(m_LandScape);

		// MinimapWindow내 지형사이즈 초기화.
		CMinimapWindow* Window = (CMinimapWindow*)m_Scene->GetViewport()->FindWidgetWindow<CWidgetWindow>("MinimapWindow");

		if (Window)
			Window->SetMapSize(Vector2((float)300, (float)300));
	}

	CGameObject::Update(DeltaTime);
}

void CLandScapeObj::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CLandScapeObj* CLandScapeObj::Clone()
{
	return DBG_NEW CLandScapeObj(*this);
}

void CLandScapeObj::Load(FILE* File)
{
	fread(&m_CountX, sizeof(int), 1, File);
	fread(&m_CountZ, sizeof(int), 1, File);

	m_LandScape->Load(File);

	m_First = true;

	// MinimapWindow내 지형사이즈 초기화.
	CMinimapWindow* Window = (CMinimapWindow*)m_Scene->GetViewport()->FindWidgetWindow<CWidgetWindow>("MinimapWindow");

	if (Window)
		Window->SetMapSize(Vector2((float)m_CountX, (float)m_CountZ));
}

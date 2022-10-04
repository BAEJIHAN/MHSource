
#include "FlightCamera.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "Player.h"
#include "../UI/DebugWindow.h"
#include "LandScapeObj.h"

CFlightCamera::CFlightCamera() :
	m_FlightSpeed(30.f),
	m_ESCButton(false)
{
	SetTypeID<CFlightCamera>();
}

CFlightCamera::CFlightCamera(const CFlightCamera& obj) :
	CGameObject(obj)
{
	m_Arm = (CArm*)FindComponent("Arm");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
}

CFlightCamera::~CFlightCamera()
{
}

bool CFlightCamera::Init()
{
	m_Arm = CreateComponent<CArm>("Arm");

	m_Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

	m_Arm->AddChild(m_Camera);

	m_Camera->SetInheritRotX(true);
	m_Camera->SetInheritRotY(true);
	m_Camera->SetInheritRotZ(true);


	Resolution RS = CEngine::GetInst()->GetRS();

	m_CenterPoint.x = (LONG)(RS.Width / 2);
	m_CenterPoint.y = (LONG)(RS.Height / 2);

	ClientToScreen(CEngine::GetInst()->GetWindowHandle(), &m_CenterPoint);

	SetCursorPos(m_CenterPoint.x, m_CenterPoint.y);

	CInput::GetInst()->SetKeyCallback<CFlightCamera>("RunFront", KeyState_Push, this, &CFlightCamera::MoveFront);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("RunBack", KeyState_Push, this, &CFlightCamera::MoveBack);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("RunLeft", KeyState_Push, this, &CFlightCamera::MoveLeft);
	CInput::GetInst()->SetKeyCallback<CFlightCamera>("RunRight", KeyState_Push, this, &CFlightCamera::MoveRight);

	CInput::GetInst()->SetKeyCallback<CFlightCamera>("ESC", KeyState_Down, this, &CFlightCamera::ESC);

	return true;
}

void CFlightCamera::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	RotationX(DeltaTime);
}

void CFlightCamera::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFlightCamera* CFlightCamera::Clone()
{
	return new CFlightCamera(*this);
}

void CFlightCamera::Render()
{
	CGameObject::Render();
}

void CFlightCamera::MoveFront(float DeltaTime)
{
	Vector3 CamZ = m_Camera->GetWorldAxis(AXIS::AXIS_Z);

	m_Arm->AddWorldPos(CamZ * m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveBack(float DeltaTime)
{
	Vector3 CamZ = m_Camera->GetWorldAxis(AXIS::AXIS_Z);

	m_Arm->AddWorldPos(CamZ * -m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveLeft(float DeltaTime)
{
	Vector3 CamX = m_Camera->GetWorldAxis(AXIS::AXIS_X);

	m_Arm->AddWorldPos(CamX * -m_FlightSpeed * DeltaTime);
}

void CFlightCamera::MoveRight(float DeltaTime)
{
	Vector3 CamX = m_Camera->GetWorldAxis(AXIS::AXIS_X);

	m_Arm->AddWorldPos(CamX * m_FlightSpeed * DeltaTime);
}

void CFlightCamera::RotationX(float DeltaTime)
{
	if (!m_ESCButton)
	{
		POINT MousePoint = {};

		GetCursorPos(&MousePoint);

		m_MouseMove.y += (float)(MousePoint.x - m_CenterPoint.x) / 5.f;
		m_MouseMove.x += (float)(MousePoint.y - m_CenterPoint.y) / 5.f;

		m_Arm->SetRelativeRotationY(m_MouseMove.y);
		m_Arm->SetRelativeRotationX(m_MouseMove.x);

		if (m_MouseMove.x >= 89.f)
		{
			m_MouseMove.x = 89.f;
			m_Arm->SetRelativeRotationX(m_MouseMove.x);
		}

		else if (m_MouseMove.x <= -89.f)
		{
			m_MouseMove.x = -89.f;
			m_Arm->SetRelativeRotationX(m_MouseMove.x);
		}

		SetCursorPos(m_CenterPoint.x, m_CenterPoint.y);
	}
}

void CFlightCamera::ESC(float DeltaTime)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);

	if (m_ESCButton)
	{
		m_ESCButton = false;

		CEngine::GetInst()->ShowUICursor(false);


		return;
	}

	if (!m_ESCButton)
	{
		m_ESCButton = true;

		POINT MousePoint = {};

		GetCursorPos(&MousePoint);

		SetCursorPos((int)m_CenterPoint.x, (int)m_CenterPoint.y);

		CEngine::GetInst()->ShowUICursor(true);
	}
}

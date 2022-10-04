
#include "TargetingCamera.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "Component/AnimationMeshComponent.h"
#include "EventManager.h"

CTargetingCamera::CTargetingCamera() :
	m_CameraAliveTime(4.f),
	m_CameraAliveTimeAcc(0.f),
	m_MoveSpeed(2.5f),
	m_CamDist(0.f),
	m_CamRotSpeed(25.f),
	m_IsBossDeadCam(false),
	m_RotateCamStart(true),
	m_TargetOffset(Vector3().Zero),
	m_TargetPos(Vector3().Zero),
	m_Dir(Vector3().Axis[AXIS::AXIS_Y])
{
}

CTargetingCamera::~CTargetingCamera()
{
}

void CTargetingCamera::RotationStart()
{
	CEventManager::GetInst()->CallEvent("SceneFadeOutStart");

	m_RotateCamStart = true;
}

void CTargetingCamera::Start()
{
	CGameObject::Start();

	if (m_TargetObj)
	{
		SetWorldPos(m_TargetObj->GetWorldPos());

		m_Camera->SetTargetMode(true);
	}

	else
	{
		m_Camera->SetTargetMode(true);
	}
}

bool CTargetingCamera::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}	
	
	m_Arm = CreateComponent<CArm>("TargetArm");
	m_Camera = CreateComponent<CCameraComponent>("TargetCamera");

	m_Scene->GetCameraManager()->KeepCamera();
	m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	m_Camera->SetInheritRot(true);

	m_Arm->AddChild(m_Camera);
	m_Arm->SetTransformState(Transform_State::Falling);
	
	SetMoveDir(Vector3(0.7f, 0.7f, 0.7f));

	return true;
}

void CTargetingCamera::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_CameraAliveTimeAcc += DeltaTime;

	if (m_CameraAliveTimeAcc >= m_CameraAliveTime)
	{
		if (m_Camera)
		{
			m_Camera->SetTargetMode(false);

			m_Scene->GetCameraManager()->ReturnCamera();
			m_TargetObj = nullptr;
		}

		Destroy();

		return;
	}

	LookAt(DeltaTime);

	Move(DeltaTime);
}

void CTargetingCamera::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CTargetingCamera::Render()
{
	CGameObject::Render();
}

void CTargetingCamera::LookAt(float DeltaTime)
{
	if (m_IsBossDeadCam)
	{
		if (!m_TargetObj)
			return;

		CAnimationMeshComponent* Mesh = (CAnimationMeshComponent*)m_TargetObj->GetRootComponent();

		if (Mesh && Mesh->CheckType<CAnimationMeshComponent>())
		{
			Vector3 TargetPos = {};

			if (!m_TargetSocketName.empty())
			{
				TargetPos = Mesh->GetSocketPos(m_TargetSocketName) + m_TargetOffset;
			}

			Vector3 CamPos = m_CamFixedPos;

			CamPos.y += m_CamDist;

			Vector3 CamUpVector = GetRelativeAxis(AXIS::AXIS_Y);

			Matrix ViewMat = {};

			ViewMat.m = XMMatrixLookAtLH(CamPos.Convert(), TargetPos.Convert(), CamUpVector.Convert());

			if (m_Camera)
			{
				m_Camera->SetViewMatrix(ViewMat);
			}
		}
	}
}

void CTargetingCamera::Move(float DeltaTime)
{
	if (m_IsBossDeadCam)
	{
		if (m_Dir != Vector3().Zero)
			m_CamFixedPos += (m_Dir * m_MoveSpeed * DeltaTime);
	}
}

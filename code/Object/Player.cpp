
#include "Player.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Bow.h"
#include "BowBox.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "FlightCamera.h"
#include "ChargingParticle.h"
#include "../UI/PlayerHUD.h"
#include "../UI/ESCWindow.h"
#include "BowVfx.h"
#include "HealFlower.h"
#include "HealEffect.h"
#include "../UI/PlayerHUD.h"
#include "Barnos.h"
#include "Jagras.h"
#include "Kestodon.h"
#include "Vespoid.h"
#include "Anjanath.h"
#include "Rathalos.h"
#include "../UI/BottleSlotWindow.h"
#include "../UI/CarvingWindow.h"
#include "../UI/CarvingRightWindow.h"
#include "../UI/QuestWindow.h"
#include "../UI/QuestSubWindow1.h"
#include "../UI/QuestSubWindow2.h"
#include "Widget/Image.h"
#include "Widget/Text.h"
#include "NormalArrowBillboard.h"
#include "FlameEffect.h"
#include "HitBreathEffect.h"
#include "Collision/Collision.h"
#include "TownSign.h"
#include "EventManager.h"
#include "../Scene/TownSceneMode.h"

CPlayer::CPlayer() :
	m_hWnd(nullptr),
	m_ChargingCount(0),
	m_QuickShotCount(0),
	m_ArrowCount(0),
	m_CorrectionAngle(3),
	m_MouseDPI(10.f),
	m_RotationSpeed(500.f),
	m_QuickMoveSpeed(10.f),
	m_MouseRotAccY(0.f),
	m_MouseRotAccX(0.f),
	m_EvadeTime(0.f),
	m_ChargingTime(200.f),
	m_DrawWeaponTime(0.f),
	m_DrawToSheateWalkTime(0.f),
	m_ArmRotAccY(0.f),
	m_CameraDist(10.f),
	m_JoomTime(0.f),
	m_ReturnChargingCountTime(1.8f),
	m_ReloadTime(0.8f),
	m_DragonSpeed(20.f),
	m_EvadeShotSpeed(20.f),
	m_HitBreathTime(5.f),
	m_FrontDown(false),
	m_BackDown(false),
	m_LeftDown(false),
	m_RightDown(false),
	m_ESCButton(false),
	m_RunQuickFrontDown(false),
	m_RunQuickBackDown(false),
	m_RunQuickLeftDown(false),
	m_RunQuickRightDown(false),
	m_ChargingEnable(false),
	m_EvadeEnable(false),
	m_DrawWeaponEnable(false),
	m_DrawWalkToSheatheEnable(false),
	m_JoomEnable(false),
	m_ReturnEnable(false),
	m_ShotEnable(false),
	m_DragonShotEnable(false),
	m_EvadeFrontShotEnable(false),
	m_EvadeBackShotEnable(false),
	m_EvadeLeftShotEnable(false),
	m_EvadeRightShotEnable(false),
	m_EvadeChangeAttack(false),
	m_HealEnable(false),
	m_TrippingEnable(false),
	m_MonsterCollision(false),
	m_CarvingEnable(false),
	m_RollEnable(false),
	m_IsHitBreath(false),
	m_IsRoaring(false),
	m_QuickShotEnable(false),
	m_PowerShotEnable(false),
	m_IsFieldCollision(false),
	m_IsSignCollision(false),
	m_IsQuestAcept(false),
	m_IsJump(false),
	m_HealObjName{},
	m_BarnosName{},
	m_JagrasName{},
	m_KestodonName{},
	m_VespoidName{},
	m_AnjanthName{},
	m_RathalosName{},
	m_FieldObjName{},
	m_FieldBoxName{},
	m_CoatingState(Coating_State::None),
	m_JoomState(Player_Joom_State::None),
	m_CenterPoint{},
	m_FlightMode(false)
{
	SetTypeID<CPlayer>();

	m_PlayerInfo = new PlayerInfo;
}

CPlayer::CPlayer(const CPlayer& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("PlayerMeshComponent");
	//m_Sphere = (CColliderSphere*)FindComponent("Sphere");
	m_Face = (CStaticMeshComponent*)FindComponent("PlayerFaceMeshComponent");
	m_ColliderBox = (CColliderBox3D*)FindComponent("PlayerBox");
	m_Arm = (CArm*)FindComponent("Arm");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_NavAgent = (CNavAgent*)FindComponent("NavAgent");
}

CPlayer::~CPlayer()
{
	SAFE_DELETE(m_PlayerInfo);
}

bool CPlayer::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("PlayerMeshComponent");
	m_Face = CreateComponent<CStaticMeshComponent>("PlayerFaceMeshComponent");
	//m_Sphere = CreateComponent<CColliderSphere>("Sphere");
	m_ColliderBox = CreateComponent<CColliderBox3D>("PlayerBox");
	m_SlidingBox = CreateComponent<CColliderBox3D>("SlidingBox");
	m_CamPosBox = CreateComponent<CColliderBox3D>("CamPosBox");
	m_Arm = CreateComponent<CArm>("Arm");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_NavAgent = CreateComponent<CNavAgent>("NavAgent");

	// 메쉬에 Arm을 달아주고 
	m_Mesh->AddChild(m_Arm);
	//m_Mesh->AddChild(m_Sphere);

	// Arm에 카메라를 달아주는 형식
	m_Arm->AddChild(m_Camera);
	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->AddChild(m_SlidingBox);
	m_Mesh->AddChild(m_CamPosBox);

	m_CamPosBox->SetRelativePos(-3.f, 7.f, -7.f);
	m_CamPosBox->Set3DExtent(0.5f, 0.5f, 0.5f);
	m_CamPosBox->SetCollisionProfile("NPC");
	m_CamPosBox->SetInheritParentRotationPosY(true);

	m_ColliderBox->Set3DExtent(2.f, 4.5f, 1.f);
	m_ColliderBox->SetOffset(0.f, 4.5f, 0.f);
	m_ColliderBox->SetCollisionProfile("Player");
	m_SlidingBox->Set3DExtent(0.5f, 0.5f, 0.5f);
	m_SlidingBox->SetOffset(0.f, 3.f, 0.f);
	m_SlidingBox->SetCollisionProfile("PlayerSliding");

	// 카메라는 부모의 회전에 영향을 받아야함 그래야 부모를 공전함
	m_Camera->SetInheritRotX(true);
	m_Camera->SetInheritRotY(true);
	m_Camera->SetInheritRotZ(true);

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("PlayerMesh");
	//m_Mesh->SetReceiveDecal(false);
	m_Mesh->CreateAnimationInstance<CPlayerAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(0.f, -2.f, 0.f);
	m_Mesh->SetWorldRotation(Vector3(0.f, 180.f, 0.f));
	m_Mesh->SetPivot(0.5f, 0.f, 0.5f);
	//m_Sphere->SetCollisionProfile("Player");
	//m_Sphere->SetInfo(m_Mesh->GetRelativePos(), 2.f);

	m_Face->SetMesh("PlayerFaceMesh");
	m_Face->SetRelativeRotation(90.f, 0.f, 0.f);
	//m_Face->SetRelativeRotationZ(45.f);
	m_Face->SetRelativePos(0.f, -4.f, -12.f);
	m_Face->SetTransformState(Transform_State::None);
	m_Mesh->AddChild(m_Face, "PlayerFace");

	m_Bow = m_Scene->CreateGameObject<CBow>("Bow");
	m_Bow->SetRelativeRotation(0.f, 0.f, 90.f);
	m_Bow->SetRelativePos(-10.f, 0.f, 0.f);
	m_Mesh->AddChild(m_Bow, "BackBow");

	m_BowBox = m_Scene->CreateGameObject<CBowBox>("BowBox");
	m_BowBox->SetRelativeRotation(0.f, 30.f, 0.f);
	m_Mesh->AddChild(m_BowBox, "BowBox");

	// 8
	m_Arm->SetOffset(0.f, 8.f, 0.f);
	m_Arm->SetRelativeRotation(15.f, 0.f, 0.f);
	m_Arm->SetTargetDistance(m_CameraDist);

	SetKeyCallback();
	SetNotify();

	Resolution RS = CEngine::GetInst()->GetRS();
	m_hWnd = CEngine::GetInst()->GetWindowHandle();


	m_CenterPoint.x = (LONG)(RS.Width / 2);
	m_CenterPoint.y = (LONG)(RS.Height / 2);

	ClientToScreen(m_hWnd, &m_CenterPoint);
	
	SetCursorPos(m_CenterPoint.x, m_CenterPoint.y);

	ShowCursor(false);

	//SetPhysicsSimulate(true);

	m_ColliderBox->AddCollisionCallback<CPlayer>(Collision_State::Begin, this, &CPlayer::CollisionBegin);
	m_ColliderBox->AddCollisionCallback<CPlayer>(Collision_State::End, this, &CPlayer::CollisionEnd);
	m_SlidingBox->AddCollisionCallback<CPlayer>(Collision_State::Begin, this, &CPlayer::SlidingCollisionBegin);
	m_SlidingBox->AddCollisionCallback<CPlayer>(Collision_State::End, this, &CPlayer::SlidingCollisionEnd);

	m_PlayerHUD = m_Scene->GetViewport()->CreateWidgetWindow<CPlayerHUD>("PlayerHUD");

	CEventManager::GetInst()->AddEventCallback<CPlayer>("QuestAcept", this, &CPlayer::QuestAcept);

	CEngine::GetInst()->ShowUICursor(false);

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	// 마우스 회전
	MouseRotation(DeltaTime);

	m_ArmRotAccY = m_MouseRotAccY;

	if (m_ArmRotAccY > 360.f)
	{
		m_ArmRotAccY -= 360.f;
	}

	else if (m_ArmRotAccY < 0.f)
	{
		m_ArmRotAccY += 360.f;
	}


	/*CCameraComponent* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

	Matrix matWV = m_Mesh->GetWorldMatrix() * Camera->GetViewMatrix();

	matWV.Transpose();

	Ray ForwardRay = CInput::GetInst()->GetRay(matWV);

	ForwardRay.Dir.z *= -1.f;*/


	/*CGameObject* PickObj = nullptr;

	/*if (m_Scene->ForwardRayCollision(PickObj))
	{
		int a = 0;
	}*/

	MoveEnableUpdate(DeltaTime);

	CollisionFieldObjUpdate(DeltaTime);

	BossRoaringUpdate(DeltaTime);

	StaminaFunc(DeltaTime);

	/*CGameObject* Obje = m_Scene->FindObject("FieldObj");

	m_Scene->Picking(Obje);*/

	/*if (CInput::GetInst()->GetWheelDir())
	{
		float Length = m_Arm->GetTargetDistance() +
			CInput::GetInst()->GetWheelDir() * 0.4f;

		m_Arm->SetTargetDistance(Length);
	}*/

	// 시프트 회피동작시
	if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade"))
	{
		EvadeUpdate(DeltaTime);
	}

	// 무기 든 상태 시프트 회피동작시
	if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvadeToDrawedWalkStart") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvadeToDrawedWalk"))
	{
		EvadeWalkUpdate(DeltaTime);
	}

	// 무기 들고있다가 등으로 넣음
	Sheathe(DeltaTime);

	DrawToSheatWalkUpdate(DeltaTime);

	ChargingUpdate(DeltaTime);

	DragonShotUpdate(DeltaTime);

	// 줌인 아웃 스위치문
	switch (m_JoomState)
	{
	case Player_Joom_State::JoomIn:
		ChargingJoomInUpdate(DeltaTime);
		break;
	case Player_Joom_State::JoomOut:
		ChargingJoomOutUpdate(DeltaTime);
		break;
	}

	EvadeShotUpdate(DeltaTime);

	DrawedWalkAndSheatheUpdate(DeltaTime);

	ReturnChargingCountUpdate(DeltaTime);

	HitUpdate(DeltaTime);
	HitRollUpdate(DeltaTime);

	if (m_ShotEnable)
	{
		m_ReloadTime -= DeltaTime;

		if (m_ReloadTime <= 0.f)
		{
			m_ShotEnable = false;
			m_ReloadTime = 0.7f;
		}
	}

	/*CGameObject* PickObj = nullptr;

	if (m_Scene->Picking(PickObj))
	{
		int a = 0;
	}*/
}

void CPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::MouseRotation(float DeltaTime)
{
	if (!m_ESCButton)
	{
		POINT MousePoint = {};

		GetCursorPos(&MousePoint);

		m_MouseRotAccY += (float)(MousePoint.x - m_CenterPoint.x) / m_MouseDPI;
		m_MouseRotAccX += (float)(MousePoint.y - m_CenterPoint.y) / m_MouseDPI;

		m_Arm->SetRelativeRotationY(m_MouseRotAccY);
		m_Arm->SetRelativeRotationX(m_MouseRotAccX);

		// Rot게산 편하기 위해서 360도 이상 넘어가면 0으로 초기화
		if (m_MouseRotAccY > 360.f)
		{
			m_MouseRotAccY -= 360.f;

			m_Arm->SetRelativeRotationY(m_MouseRotAccY);
		}

		else if (m_MouseRotAccY < 0.f)
		{
			m_MouseRotAccY += 360.f;

			m_Arm->SetRelativeRotationY(m_MouseRotAccY);
		}

		if (m_MouseRotAccX > 90.f)
		{
			m_MouseRotAccX = 90.f;

			m_Arm->SetRelativeRotationX(m_MouseRotAccX);
		}

		else if (m_MouseRotAccX < -90.f)
		{
			m_MouseRotAccX = -90.f;

			m_Arm->SetRelativeRotationX(m_MouseRotAccX);
		}

		float MeshRotY = m_Mesh->GetRelativeRot().y;

		if (MeshRotY > 360.f)
		{
			MeshRotY -= 360.f;

			m_Mesh->SetRelativeRotationY(MeshRotY);
		}

		else if (MeshRotY < 0.f)
		{
			MeshRotY += 360.f;

			m_Mesh->SetRelativeRotationY(MeshRotY);
		}
		SetCursorPos(m_CenterPoint.x, m_CenterPoint.y);
		
	}
}

void CPlayer::MoveFrontDown(float DeltaTime)
{
	m_FrontDown = true;
}

void CPlayer::MoveBackDown(float DeltaTime)
{
	m_BackDown = true;
}

void CPlayer::MoveLeftDown(float DeltaTime)
{
	m_LeftDown = true;
}

void CPlayer::MoveRightDown(float DeltaTime)
{
	m_RightDown = true;
}

void CPlayer::MoveFront(float DeltaTime)
{
	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvadeToDrawedWalkStart") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHWalkAndDrawWeapon") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWeaponToCharging") &&
		CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
		CheckAnimationFunc(false, "BHDown3"))
	{
		m_FrontDown = true;

		if (!m_ChargingEnable)
		{
			if (!m_DrawWeaponEnable)
			{
				// 앞으로 달리기
				if (m_FrontDown && !m_LeftDown && !m_RightDown && !m_BackDown)
				{
					RunFunc(DeltaTime, 0.f);
				}
				// 정면 왼쪽으로 달리기
				else if (m_FrontDown && m_LeftDown)
				{
					RunFunc(DeltaTime, 45.f);
				}
				// 정면 오른쪽 달리기
				else if (m_FrontDown && m_RightDown)
				{
					RunFunc(DeltaTime, -45.f);
				}
			}

			if (m_DrawWeaponEnable && !m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHSheathe") &&
				CheckAnimationFunc(false, "BHDrawWeapon") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHWalkAndDrawWeapon"))
			{
				// 무기를 들고있고 줌 우클릭 안 하였을 경우
				if (!m_JoomEnable)
				{
					// 정면으로 무기 들고 달리기
					if (m_FrontDown && !m_LeftDown && !m_RightDown && !m_BackDown)
					{
						DrawRunFunc(DeltaTime, 0.f);
					}
					// 정면 왼쪽
					else if (m_FrontDown && m_LeftDown)
					{

						DrawRunFunc(DeltaTime, 45.f);
					}
					// 정면 오른쪽
					else if (m_FrontDown && m_RightDown)
					{

						DrawRunFunc(DeltaTime, -45.f);
					}
				}

				// 무기를 들고있고 줌 우클릭 하였을 경우
				else
				{
					// 정면으로 무기 들고 달리기
					if (m_FrontDown && !m_LeftDown && !m_RightDown && !m_BackDown)
					{
						JoomWalkFunc(DeltaTime, "BHAimWalkFront", m_PlayerInfo->Speed / 2.f, 0.f);
					}
					// 정면 왼쪽
					else if (m_FrontDown && m_LeftDown)
					{

						JoomWalkFunc(DeltaTime, "BHAimWalkFront", m_PlayerInfo->Speed / 2.f, -m_PlayerInfo->Speed / 2.f);
					}
					// 정면 오른쪽
					else if (m_FrontDown && m_RightDown)
					{

						JoomWalkFunc(DeltaTime, "BHAimWalkFront", m_PlayerInfo->Speed / 2.f, m_PlayerInfo->Speed / 2.f);
					}
				}
			}
		}

		else
		{
			if (!m_DrawWeaponEnable)
			{
			}

			else
			{
				if (!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWeaponToCharging"))
				{
					if (!m_JoomEnable)
					{
						if (m_FrontDown && !m_LeftDown && !m_RightDown && !m_BackDown)
						{
							ChargingWalkFunc(DeltaTime, 0.f);
						}
						// 정면 왼쪽으로 달리기
						else if (m_FrontDown && m_LeftDown)
						{
							ChargingWalkFunc(DeltaTime, 45.f);
						}
						// 정면 오른쪽 달리기
						else if (m_FrontDown && m_RightDown)
						{
							ChargingWalkFunc(DeltaTime, -45.f);
						}
					}

					else
					{
						// 정면으로 무기 들고 달리기
						if (m_FrontDown && !m_LeftDown && !m_RightDown && !m_BackDown)
						{
							ChargingJoomFunc(DeltaTime, "BHAimChargingWalkFront", m_PlayerInfo->Speed / 2.f, 0.f);
						}
						// 정면 왼쪽
						else if (m_FrontDown && m_LeftDown)
						{
							ChargingJoomFunc(DeltaTime, "BHAimChargingWalkFront", m_PlayerInfo->Speed / 2.f, -m_PlayerInfo->Speed / 2.f);
						}
						// 정면 오른쪽
						else if (m_FrontDown && m_RightDown)
						{
							ChargingJoomFunc(DeltaTime, "BHAimChargingWalkFront", m_PlayerInfo->Speed / 2.f, m_PlayerInfo->Speed / 2.f);
						}
					}
				}
			}
		}
	}
}


void CPlayer::MoveBack(float DeltaTime)
{
	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvadeToDrawedWalkStart") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHWalkAndDrawWeapon") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWeaponToCharging") &&
		CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
		CheckAnimationFunc(false, "BHDown3"))
	{
		m_BackDown = true;

		if (!m_ChargingEnable)
		{
			if (!m_DrawWeaponEnable)
			{
				if (m_BackDown && !m_LeftDown && !m_RightDown && !m_FrontDown)
				{
					RunFunc(DeltaTime, 180.f);
				}
				else if (m_BackDown && m_LeftDown)
				{

					RunFunc(DeltaTime, 135.f);
				}
				else if (m_BackDown && m_RightDown)
				{

					RunFunc(DeltaTime, 225.f);
				}
			}

			if (m_DrawWeaponEnable && !m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHSheathe") &&
				CheckAnimationFunc(false, "BHDrawWeapon") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHWalkAndDrawWeapon"))
			{
				// 무기를 들고있고 줌 우클릭 안 하였을 경우
				if (!m_JoomEnable)
				{
					if (m_BackDown && !m_LeftDown && !m_RightDown && !m_FrontDown)
					{

						DrawRunFunc(DeltaTime, 180.f);
					}
					else if (m_BackDown && m_LeftDown)
					{

						DrawRunFunc(DeltaTime, 135.f);
					}
					else if (m_BackDown && m_RightDown)
					{

						DrawRunFunc(DeltaTime, 225.f);
					}
				}

				else
				{
					// 무기든 상태이고 줌 상태일때 뒤로 걷는모션
					if (m_BackDown && !m_LeftDown && !m_RightDown && !m_FrontDown)
					{
						JoomWalkFunc(DeltaTime, "BHAimWalkBack", -m_PlayerInfo->Speed / 2.f, 0.f);
					}

					else if (m_BackDown && m_LeftDown)
					{

						JoomWalkFunc(DeltaTime, "BHAimWalkBack", -m_PlayerInfo->Speed / 2.f, -m_PlayerInfo->Speed / 2.f);
					}

					else if (m_BackDown && m_RightDown)
					{
						JoomWalkFunc(DeltaTime, "BHAimWalkBack", -m_PlayerInfo->Speed / 2.f, m_PlayerInfo->Speed / 2.f);
					}
				}
			}
		}
		else
		{
			if (!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWeaponToCharging"))
			{
				if (!m_JoomEnable)
				{
					if (m_BackDown && !m_LeftDown && !m_RightDown && !m_FrontDown)
					{
						ChargingWalkFunc(DeltaTime, 180.f);
					}
					// 정면 왼쪽으로 달리기
					else if (m_BackDown && m_LeftDown)
					{
						ChargingWalkFunc(DeltaTime, 135.f);
					}
					// 정면 오른쪽 달리기
					else if (m_BackDown && m_RightDown)
					{
						ChargingWalkFunc(DeltaTime, 225.f);
					}
				}

				else
				{
					// 무기든 상태이고 줌 상태일때 뒤로 걷는모션
					if (m_BackDown && !m_LeftDown && !m_RightDown && !m_FrontDown)
					{
						ChargingJoomFunc(DeltaTime, "BHAimChargingWalkBack", -m_PlayerInfo->Speed / 2.f, 0.f);
					}

					else if (m_BackDown && m_LeftDown)
					{

						ChargingJoomFunc(DeltaTime, "BHAimChargingWalkBack", -m_PlayerInfo->Speed / 2.f, -m_PlayerInfo->Speed / 2.f);
					}

					else if (m_BackDown && m_RightDown)
					{
						ChargingJoomFunc(DeltaTime, "BHAimChargingWalkBack", -m_PlayerInfo->Speed / 2.f, m_PlayerInfo->Speed / 2.f);
					}
				}
			}
		}
	}
}

void CPlayer::MoveLeft(float DeltaTime)
{
	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvadeToDrawedWalkStart") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHWalkAndDrawWeapon") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWeaponToCharging") &&
		CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
		CheckAnimationFunc(false, "BHDown3"))
	{
		m_LeftDown = true;

		if (!m_ChargingEnable)
		{
			if (!m_DrawWeaponEnable)
			{
				if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
				{

					RunFunc(DeltaTime, 90.f);
				}
			}

			if (m_DrawWeaponEnable && !m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHSheathe") &&
				CheckAnimationFunc(false, "BHDrawWeapon") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHWalkAndDrawWeapon"))
			{
				// 무기를 들고있고 줌 우클릭 안 하였을 경우
				if (!m_JoomEnable)
				{
					if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
					{
						DrawRunFunc(DeltaTime, 90.f);
					}
				}

				else
				{
					if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
					{
						JoomWalkFunc(DeltaTime, "BHAimWalkLeft", 0.f, -m_PlayerInfo->Speed / 2.f);
					}
				}
			}
		}
		else
		{
			if (!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWeaponToCharging"))
			{
				if (!m_JoomEnable)
				{
					if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
					{
						ChargingWalkFunc(DeltaTime, 90.f);
					}
				}

				else
				{
					if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
					{
						ChargingJoomFunc(DeltaTime, "BHAimChargingWalkLeft", 0.f, -m_PlayerInfo->Speed / 2.f);
					}
				}
			}
		}
	}
}

void CPlayer::MoveRight(float DeltaTime)
{
	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvadeToDrawedWalkStart") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHWalkAndDrawWeapon") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWeaponToCharging") &&
		CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
		CheckAnimationFunc(false, "BHDown3"))
	{
		m_RightDown = true;

		if (!m_ChargingEnable)
		{
			if (!m_DrawWeaponEnable)
			{
				if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
				{

					RunFunc(DeltaTime, 270.f);
				}
			}

			if (m_DrawWeaponEnable && !m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHSheathe") &&
				CheckAnimationFunc(false, "BHDrawWeapon") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHWalkAndDrawWeapon"))
			{
				if (!m_JoomEnable)
				{
					if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
					{

						DrawRunFunc(DeltaTime, 270.f);
					}
				}

				else
				{
					if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
					{
						JoomWalkFunc(DeltaTime, "BHAimWalkRight", 0.f, m_PlayerInfo->Speed / 2.f);
					}
				}
			}
		}
		else
		{
			if (!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWeaponToCharging"))
			{
				if (!m_JoomEnable)
				{
					if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
					{
						ChargingWalkFunc(DeltaTime, 270.f);
					}
				}

				else
				{
					if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
					{
						ChargingJoomFunc(DeltaTime, "BHAimChargingWalkRight", 0.f, m_PlayerInfo->Speed / 2.f);
					}
				}
			}
		}
	}
}

void CPlayer::MoveFrontUp(float DeltaTime)
{
	m_FrontDown = false;
	m_RunQuickFrontDown = false;

	if (!m_ChargingEnable)
	{
		if (!m_DrawWeaponEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHRunQuick") ||
					CheckAnimationFunc(true, "BHRun") || 
					CheckAnimationFunc(true, "BHRunStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
		}
		else
		{
			if (!m_JoomEnable)
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHDrawedWalk") || 
						CheckAnimationFunc(true, "BHDrawedWalkStart")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkEnd");
			}

			else
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHAimWalkFront")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
			}
		}
	}

	else
	{
		if (!m_JoomEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHChargingWalk") || 
					CheckAnimationFunc(true, "BHDrawnWalkToChargingStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalkEnd");
		}

		else
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHAimChargingWalkFront")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
		}
	}
}

void CPlayer::MoveBackUp(float DeltaTime)
{
	m_BackDown = false;
	m_RunQuickBackDown = false;


	if (!m_ChargingEnable)
	{
		if (!m_DrawWeaponEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHRunQuick") ||
					CheckAnimationFunc(true, "BHRun") || 
					CheckAnimationFunc(true, "BHRunStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
		}
		else
		{
			if (!m_JoomEnable)
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHDrawedWalk") || 
						CheckAnimationFunc(true, "BHDrawedWalkStart")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkEnd");
			}

			else
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHAimWalkBack")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
			}
		}
	}

	else
	{
		if (!m_JoomEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHChargingWalk") || 
					CheckAnimationFunc(true, "BHDrawnWalkToChargingStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalkEnd");
		}

		else
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHAimChargingWalkBack")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
		}
	}
}

void CPlayer::MoveLeftUp(float DeltaTime)
{
	m_LeftDown = false;
	m_RunQuickLeftDown = false;

	if (!m_ChargingEnable)
	{
		if (!m_DrawWeaponEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHRunQuick") ||
					CheckAnimationFunc(true, "BHRun") || 
					CheckAnimationFunc(true, "BHRunStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
		}
		else
		{
			if (!m_JoomEnable)
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHDrawedWalk") || 
						CheckAnimationFunc(true, "BHDrawedWalkStart")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkEnd");
			}

			else
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHAimWalkLeft")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
			}
		}
	}

	else
	{
		if (!m_JoomEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHChargingWalk") || 
					CheckAnimationFunc(true, "BHDrawnWalkToChargingStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalkEnd");
		}

		else
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHAimChargingWalkLeft")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
		}
	}
}

void CPlayer::MoveRightUp(float DeltaTime)
{
	m_RightDown = false;
	m_RunQuickRightDown = false;

	if (!m_ChargingEnable)
	{
		if (!m_DrawWeaponEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHRunQuick") ||
					CheckAnimationFunc(true, "BHRun") || 
					CheckAnimationFunc(true, "BHRunStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
		}
		else
		{
			if (!m_JoomEnable)
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHDrawedWalk") || 
						CheckAnimationFunc(true, "BHDrawedWalkStart")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkEnd");
			}

			else
			{
				if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
					(CheckAnimationFunc(true, "BHAimWalkRight")))
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
			}
		}
	}

	else
	{
		if (!m_JoomEnable)
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHChargingWalk") || 
					CheckAnimationFunc(true, "BHDrawnWalkToChargingStart")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalkEnd");
		}

		else
		{
			if ((!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown) &&
				(CheckAnimationFunc(true, "BHAimChargingWalkRight")))
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
		}
	}
}

void CPlayer::RunQuickFront(float DeltaTime)
{
	if (m_PlayerInfo->Stamina < 10.f)
	{
		RunQuickFrontUp(DeltaTime);
		return;
	}

	else
	{
		if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
			CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
			CheckAnimationFunc(false, "BHDown3"))
		{
			m_RunQuickFrontDown = true;

			if (!m_DrawWeaponEnable)
			{
				if (m_RunQuickFrontDown && !m_RunQuickLeftDown && !m_RunQuickRightDown)
				{
					RunQuickFunc(DeltaTime, 0.f);
				}
				else if (m_RunQuickFrontDown && m_RunQuickLeftDown)
				{

					RunQuickFunc(DeltaTime, 45.f);
				}
				else if (m_RunQuickFrontDown && m_RunQuickRightDown)
				{

					RunQuickFunc(DeltaTime, -45.f);
				}
			}
			if (m_DrawWeaponEnable && !m_DrawWalkToSheatheEnable &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShotStart") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShotStart") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShot") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShot"))
			{
				m_DrawWeaponTime = 7.f;
				m_DrawToSheateWalkTime = 0.f;
				m_DrawWalkToSheatheEnable = true;
			}
		}
	}
}

void CPlayer::RunQuickBack(float DeltaTime)
{
	if (m_PlayerInfo->Stamina < 10.f)
	{
		RunQuickBackUp(DeltaTime);
		return;
	}

	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
		CheckAnimationFunc(false, "BHDown3"))
	{
		m_RunQuickBackDown = true;

		if (!m_DrawWeaponEnable)
		{
			if (m_RunQuickBackDown && !m_RunQuickLeftDown && !m_RunQuickRightDown)
			{
				RunQuickFunc(DeltaTime, 190.f);
			}
			else if (m_RunQuickBackDown && m_RunQuickLeftDown)
			{
				RunQuickFunc(DeltaTime, 135.f);
			}
			else if (m_RunQuickBackDown && m_RunQuickRightDown)
			{
				RunQuickFunc(DeltaTime, 225.f);
			}
		}
		if (m_DrawWeaponEnable && !m_DrawWalkToSheatheEnable &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShotStart") &&
			!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShotStart") &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShot") &&
			!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShot"))
		{
			m_DrawWeaponTime = 7.f;
			m_DrawToSheateWalkTime = 0.f;
			m_DrawWalkToSheatheEnable = true;
		}
	}
}

void CPlayer::RunQuickLeft(float DeltaTime)
{
	if (m_PlayerInfo->Stamina < 10.f)
	{
		RunQuickLeftUp(DeltaTime);
		return;
	}

	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
		CheckAnimationFunc(false, "BHDown3"))
	{
		m_RunQuickLeftDown = true;

		if (!m_DrawWeaponEnable)
		{
			if (!m_RunQuickFrontDown && !m_RunQuickBackDown && m_RunQuickLeftDown && !m_RunQuickRightDown)
			{
				RunQuickFunc(DeltaTime, 90.f);
			}
		}
		if (m_DrawWeaponEnable && !m_DrawWalkToSheatheEnable &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShotStart") &&
			!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShotStart") &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShot") &&
			!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShot"))
		{
			m_DrawWeaponTime = 7.f;
			m_DrawToSheateWalkTime = 0.f;
			m_DrawWalkToSheatheEnable = true;
		}
	}
}

void CPlayer::RunQuickRight(float DeltaTime)
{
	if (m_PlayerInfo->Stamina < 10.f)
	{
		RunQuickRightUp(DeltaTime);
		return;
	}

	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		CheckAnimationFunc(false, "BHUp1") && CheckAnimationFunc(false, "BHDown1") &&
		CheckAnimationFunc(false, "BHDown3"))
	{
		m_RunQuickRightDown = true;

		if (!m_DrawWeaponEnable)
		{
			if (!m_RunQuickFrontDown && !m_RunQuickBackDown && !m_RunQuickLeftDown && m_RunQuickRightDown)
			{

				RunQuickFunc(DeltaTime, 270.f);
			}
		}

		if (m_DrawWeaponEnable && !m_DrawWalkToSheatheEnable &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShotStart") &&
			!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShotStart") &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShot") &&
			!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShot"))
		{
			m_DrawWeaponTime = 7.f;
			m_DrawToSheateWalkTime = 0.f;
			m_DrawWalkToSheatheEnable = true;
		}
	}
}

void CPlayer::RunQuickFrontUp(float DeltaTime)
{
	m_FrontDown = false;
	m_RunQuickFrontDown = false;

	if (!m_RunQuickFrontDown && !m_RunQuickBackDown && !m_RunQuickLeftDown && !m_RunQuickRightDown &&
		(m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunQuick") ||
			m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRun")
			|| m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart")))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
	}
}

void CPlayer::RunQuickBackUp(float DeltaTime)
{
	m_BackDown = false;
	m_RunQuickBackDown = false;

	if (!m_RunQuickFrontDown && !m_RunQuickBackDown && !m_RunQuickLeftDown && !m_RunQuickRightDown &&
		(m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunQuick") ||
			m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRun")
			|| m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart")))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
	}
}

void CPlayer::RunQuickLeftUp(float DeltaTime)
{
	m_LeftDown = false;
	m_RunQuickLeftDown = false;

	if (!m_RunQuickFrontDown && !m_RunQuickBackDown && !m_RunQuickLeftDown && !m_RunQuickRightDown &&
		(m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunQuick") ||
			m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRun")
			|| m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart")))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
	}
}

void CPlayer::RunQuickRightUp(float DeltaTime)
{
	m_RightDown = false;
	m_RunQuickRightDown = false;

	if (!m_RunQuickFrontDown && !m_RunQuickBackDown && !m_RunQuickLeftDown && !m_RunQuickRightDown &&
		(m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunQuick") ||
			m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRun")
			|| m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart")))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunEnd");
	}
}

void CPlayer::EvadeClick(float DeltaTime)
{
	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;

	if (m_PlayerInfo->Stamina < 20.f)
		return;

	if (m_EvadeFrontShotEnable || m_EvadeBackShotEnable || 
		m_EvadeLeftShotEnable || m_EvadeRightShotEnable)
	{
		return;
	}

	if (CheckAnimationFunc(true, "BHEvade") ||
		CheckAnimationFunc(true, "BHDrawedEvade") ||
		CheckAnimationFunc(true, "BHDragonShotStart") || 
		CheckAnimationFunc(true, "BHDragonShot") ||
		CheckAnimationFunc(true, "BHRollByFrontStart") ||
		CheckAnimationFunc(true, "BHRollByFrontEnd") ||
		CheckAnimationFunc(true, "BHRollOverToIdle") ||
		m_QuickShotEnable || m_PowerShotEnable ||
		m_ChargingEnable || m_JoomEnable)
	{
		return;
	}

	CResourceManager::GetInst()->SoundStop("ChargingLoop");

	if (((CAnimationMeshComponent*)m_Bow->GetRootComponent())->GetAnimationInstance()->CheckCurrentAnimation("BowChargingStart") ||
		((CAnimationMeshComponent*)m_Bow->GetRootComponent())->GetAnimationInstance()->CheckCurrentAnimation("BowChargingLoop"))
	{
		((CAnimationMeshComponent*)m_Bow->GetRootComponent())->GetAnimationInstance()->ChangeAnimation("BowChargingToIdle");
	}

	if (!m_DrawWeaponEnable)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHEvade");
		m_ChargingEnable = false;
		m_EvadeEnable = true;
		m_EvadeTime = 0.f;
		m_PlayerInfo->Stamina -= 20.f;
		CResourceManager::GetInst()->SoundPlay("EvadeSound");
	}

	else
	{
		if (!((CAnimationMeshComponent*)m_Bow->GetRootComponent())->GetAnimationInstance()->CheckCurrentAnimation("BowClose"))
		{
			if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
			{
				if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawWeapon") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHSheathe") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHWalkAndDrawWeapon") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWeaponToCharging") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedToChargingStart") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargingIdleLoop"))
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedEvade");
					m_ChargingEnable = false;
					m_EvadeEnable = true;
					m_EvadeTime = 0.f;
					m_PlayerInfo->Stamina -= 20.f;
					CResourceManager::GetInst()->SoundPlay("EvadeSound");
				}
			}

			else
			{
				if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHWalkAndDrawWeapon") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkAndSheathe") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWeaponToCharging") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedToChargingStart") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkFront") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkBack") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkLeft") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkRight") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargingWalk") &&
					!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawnWalkToChargingStart") && 
					CheckAnimationFunc(false, "BHAimIdle") &&
					CheckAnimationFunc(false, "BHAimWalkFront") &&
					CheckAnimationFunc(false, "BHAimWalkBack") &&
					CheckAnimationFunc(false, "BHAimWalkLeft") &&
					CheckAnimationFunc(false, "BHAimWalkRight") &&
					CheckAnimationFunc(false, "BHChargedShotIdle") &&
					CheckAnimationFunc(false, "BHFullChargedShotIdle"))
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedEvade");
					m_ChargingEnable = false;
					m_EvadeEnable = true;
					m_EvadeTime = 0.f;
					m_PlayerInfo->Stamina -= 20.f;
					CResourceManager::GetInst()->SoundPlay("EvadeSound");
				}
			}
		}
	}
}


void CPlayer::ShotStart(float DeltaTime)
{
	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;

	if (m_PlayerInfo->Stamina < 10.f)
		return;

	if (m_ESCButton)
		return;

	if (m_EvadeFrontShotEnable || m_EvadeBackShotEnable ||
		m_EvadeLeftShotEnable || m_EvadeRightShotEnable)
	{
		m_ChargingEnable = true;
		m_EvadeChangeAttack = true;

		return;
	}

	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvadeToDrawedWalkStart") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHWalkAndDrawWeapon") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHQuickShot") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHQuickShot") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHPowerShot") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHPowerShot") && 
		CheckAnimationFunc(false, "BHDragonShotStart") && CheckAnimationFunc(false, "BHDragonShot") &&
		CheckAnimationFunc(false, "BHRollByFrontStart") &&
			CheckAnimationFunc(false, "BHRollByFrontEnd") &&
			CheckAnimationFunc(false, "BHRollOverToIdle"))
	{
		if (m_ShotEnable)
			return;

		if (!m_DrawWeaponEnable)
		{
			if (!m_JoomEnable)
			{
				m_DrawWeaponEnable = true;
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawWeapon");

				if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
				{
					//m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWeaponToCharging");
					ChangeBowFunc("BowLeftHand", "BowOpen");
					m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
					m_Bow->SetRelativePos(2.f, 0.f, 0.f);
					//ChargingShotDownFunc();
					CResourceManager::GetInst()->SoundPlay("DrawBow");
					//CResourceManager::GetInst()->SoundPlay("ChargingLoop");
					//CResourceManager::GetInst()->SoundPlay("ArrowDrop");



				}
				else
				{
					//m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWeaponToCharging");
					ChangeBowFunc("BowLeftHand", "BowOpen");
					m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
					m_Bow->SetRelativePos(2.f, 0.f, 0.f);
					//ChargingShotDownFunc();
					CResourceManager::GetInst()->SoundPlay("DrawBow");
					//CResourceManager::GetInst()->SoundPlay("ChargingLoop");
					//CResourceManager::GetInst()->SoundPlay("ArrowDrop");
				}
			}
		}
		else
		{
			m_ChargingEnable = true;

			if (!m_JoomEnable)
			{
				if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingStartIdleFirst");
					m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
					ChargingShotDownFunc();
					CResourceManager::GetInst()->SoundPlay("ChargingLoop");
					CResourceManager::GetInst()->SoundPlay("ChargingStart");
					CResourceManager::GetInst()->SoundPlay("ArrowDrop");

				}
				else
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawnWalkToChargingStart");
					m_Bow->SetRelativeRotation(0.f, 0.f, 0.f);
					m_Bow->SetRelativePos(2.f, 0.f, 0.f);
					ChargingShotDownFunc();
					CResourceManager::GetInst()->SoundPlay("ChargingLoop");
					CResourceManager::GetInst()->SoundPlay("ChargingStart");
					CResourceManager::GetInst()->SoundPlay("ArrowDrop");

				}
			}
			else
			{
				if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingStartIdleFirst");
					m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
					ChargingShotDownFunc();
					CResourceManager::GetInst()->SoundPlay("ChargingLoop");
					CResourceManager::GetInst()->SoundPlay("ChargingStart");
					CResourceManager::GetInst()->SoundPlay("ArrowDrop");

				}
				else
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingStartIdleFirst");
					m_Bow->SetRelativeRotation(0.f, 0.f, 0.f);
					m_Bow->SetRelativePos(2.f, 0.f, 0.f);
					ChargingShotDownFunc();
					CResourceManager::GetInst()->SoundPlay("ChargingLoop");
					CResourceManager::GetInst()->SoundPlay("ChargingStart");
					CResourceManager::GetInst()->SoundPlay("ArrowDrop");

				}
			}
		}
	}
}

void CPlayer::BowCharging(float DeltaTime)
{
	//if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedIdle"))
	//{
	//	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingStartIdleFirst");
	//	//ChangeBowFunc("BowLeftHand", "BowChargingStart");
	//	m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
	//	m_Bow->SetRelativePos(2.f, 0.f, 0.f);
	//}
}

void CPlayer::ShotEnd(float DeltaTime)
{
	/*if (m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHEvade") ||
		m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedEvadeToDrawedWalkStart"))
	{
		m_ChargingEnable = false;
	}*/

	/*if (m_ChargingParticle)
	{
		m_Mesh->DeleteChild(m_ChargingParticle);
		m_ChargingParticle->Destroy();
	}*/

	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;

	if (CheckAnimationFunc(true, "BHChargingFrontStep") || CheckAnimationFunc(true, "BHChargingFrontStepShot") ||
		CheckAnimationFunc(true, "BHChargingBackStep") || CheckAnimationFunc(true, "BHChargingBackStepShot") ||
		CheckAnimationFunc(true, "BHChargingLeftStep") || CheckAnimationFunc(true, "BHChargingLeftStepShot") ||
		CheckAnimationFunc(true, "BHChargingRightStep") || CheckAnimationFunc(true, "BHChargingRightStepShot"))
	{
		m_ChargingEnable = false;
	}
	m_Bow->SetRimLightEnable(false);
	if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargingStartIdleFirst") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawnWalkToChargingStart") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWeaponToCharging") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedToChargingStart"))
	{
		ChangeBowFunc("BowLeftHand", "BowShot");
		m_DrawWeaponTime = 0.f;
		m_ChargingTime = 200.f;

		ChargingShotUpFunc();
		CResourceManager::GetInst()->SoundStop("ChargingLoop");
		CResourceManager::GetInst()->SoundPlay("ArrowShoot");
		CResourceManager::GetInst()->SoundPlay("PlayerShot1");

		BowEffectVfxEndFunc();


	}

	else if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargingIdleLoop") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargingWalk") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargingWalkEnd") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkFront") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkBack") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkLeft") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimChargingWalkRight"))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargedShotIdle");
		ChangeBowFunc("BowLeftHand", "BowShot");
		m_DrawWeaponTime = 0.f;
		m_ChargingTime = 200.f;

		/*int Numb = rand() % (2 - 1 + 1) + 1;

		if (Numb == 1)
		{
			CResourceManager::GetInst()->SoundPlay("PlayerShot1");
		}
		else
		{
			CResourceManager::GetInst()->SoundPlay("PlayerShot2");
		}*/

		ChargingShotUpFunc();
		CResourceManager::GetInst()->SoundStop("ChargingLoop");
		CResourceManager::GetInst()->SoundPlay("ArrowShoot");
		CResourceManager::GetInst()->SoundPlay("ArrowShotHight");
		BowEffectVfxEndFunc();
		CResourceManager::GetInst()->SoundPlay("PlayerShot2");

	}
}

void CPlayer::ChargingJoomDown(float DeltaTime)
{
	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;

	if(m_QuickShotEnable || m_PowerShotEnable)
	{
		return;
	}

	CEngine::GetInst()->ShowUICursor(true);

	if (!m_DrawWeaponEnable)
	{
		m_JoomEnable = true;
		m_JoomState = Player_Joom_State::JoomIn;
		CEngine::GetInst()->SetMouseState(Mouse_State::State2);
	}
	else
	{
		CEngine::GetInst()->SetMouseState(Mouse_State::State3);
		if (!m_ChargingEnable && CheckAnimationFunc(false, "BHChargingFrontStep") &&
			CheckAnimationFunc(false, "BHChargingBackStep")&&
			CheckAnimationFunc(false, "BHChargingLeftStep")&&
			CheckAnimationFunc(false, "BHChargingRightStep") &&
			CheckAnimationFunc(false, "BHDrawedEvade") &&
			CheckAnimationFunc(false, "BHTrippingByFront") &&
			CheckAnimationFunc(false, "BHTrippingToIdle") &&
			CheckAnimationFunc(false, "BHRollByFrontStart") &&
			CheckAnimationFunc(false, "BHRollByFrontEnd") &&
			CheckAnimationFunc(false, "BHRollOverToIdle") &&
			CheckAnimationFunc(false, "BHDragonShotStart") &&
			CheckAnimationFunc(false, "BHDragonShot"))
		{
			m_JoomEnable = true;
			m_JoomState = Player_Joom_State::JoomIn;
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
		}
		else
		{
			m_JoomEnable = true;
			m_JoomState = Player_Joom_State::JoomIn;
		}
	}
}

void CPlayer::ChargingJoomUp(float DeltaTime)
{
	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;

	m_JoomEnable = false;
	m_JoomState = Player_Joom_State::JoomOut;
	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);
	m_DrawWeaponTime = 0.f;

	CEngine::GetInst()->ShowUICursor(false);

	if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimIdle"))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
	}
}

void CPlayer::EvadeShotDown(float DeltaTime)
{
	if (m_PlayerInfo->Stamina < 20.f)
		return;

	if (m_JoomEnable && (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimIdle") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimWalkFront") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimWalkBack") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimWalkLeft") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHAimWalkRight") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargedShotIdle") ||
		m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargedShotIdle")))
	{
		if (m_FrontDown && !m_LeftDown && !m_RightDown && !m_BackDown)
		{
			m_EvadeFrontShotEnable = true;
		}
		else if (!m_FrontDown && m_BackDown && !m_LeftDown && !m_RightDown)
		{
			m_EvadeBackShotEnable = true;
		}
		else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
		{
			m_EvadeLeftShotEnable = true;
		}
		else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
		{
			m_EvadeRightShotEnable = true;
		}
		else
		{
			return;
		}


		m_PlayerInfo->Stamina -= 20.f;
		CResourceManager::GetInst()->SoundPlay("BowChargingCount");
		m_ChargingCount = 0;
		ChargingShotDownFunc();
		m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
		m_Bow->SetRimLightEnable(true);
		m_Bow->SetCount(0);
		CResourceManager::GetInst()->SoundPlay("ChargingLoop");
		CResourceManager::GetInst()->SoundPlay("ChargingStart");

		BowEffectVfxStartFunc();

		
	}
}

void CPlayer::QuickShotDown(float DeltaTime)
{
	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;

	if (!m_EvadeChangeAttack && !m_EvadeFrontShotEnable &&
		!m_EvadeBackShotEnable && !m_EvadeLeftShotEnable && !m_EvadeRightShotEnable && !m_EvadeEnable
		 && !m_DrawWalkToSheatheEnable)
	{
		if (m_QuickShotCount == 0)
		{
			if (m_DrawWeaponEnable)
			{
				if (CheckAnimationFunc(false, "BHQuickShot") && CheckAnimationFunc(false, "BHPowerShot") &&
					!m_ChargingEnable)
				{
					++m_ChargingCount;
					m_PlayerInfo->Stamina -= 10.f;
					m_DrawWeaponTime = 0.f;
					m_ReturnChargingCountTime = 1.8f;
					m_ReturnEnable = false;
					m_QuickShotEnable = true;
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHQuickShot");
					ChangeBowFunc("BowLeftHand", "BowChargingStart");
					for (int i = 0; i < 3; ++i)
					{
						char Name[64] = {};

						sprintf_s(Name, "QuickArrow%d", i);

						CArrow* Arrow = m_Scene->CreateGameObject<CArrow>(Name);
						Arrow->SetRelativeRotation(i * 15 + 75.f, 30.f, 0.f);
						Arrow->SetArrowState(Arrow_State::Charging);
						Arrow->SetArrowCoatingState(m_CoatingState);
						Arrow->SetArrowAngle(-m_MouseRotAccX);
						m_Mesh->AddChild(Arrow, "BowRightHand");
					}
				}
			}
		}

		else
		{
			if (m_DrawWeaponEnable)
			{
				if (CheckAnimationFunc(false, "BHQuickShot") && CheckAnimationFunc(false, "BHPowerShot") &&
					!m_ChargingEnable)
				{
					m_PlayerInfo->Stamina -= 10.f;
					m_ChargingCount = 0;
					m_DrawWeaponTime = 0.f;
					m_ReturnChargingCountTime = 1.8f;
					m_ReturnEnable = false;
					m_PowerShotEnable = true;
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHPowerShot");
					for (int i = 0; i < 5; ++i)
					{
						char Name[64] = {};

						sprintf_s(Name, "QuickArrow%d", i);

						CArrow* Arrow = m_Scene->CreateGameObject<CArrow>(Name);
						Arrow->SetRelativeRotation(i * 5 + 80.f, 30.f, 0.f);
						Arrow->SetArrowState(Arrow_State::Charging);
						Arrow->SetArrowCoatingState(m_CoatingState);
						Arrow->SetArrowAngle(-m_MouseRotAccX);
						m_Mesh->AddChild(Arrow, "BowRightHand");
					}
				}
			}
		}
	}
}

void CPlayer::DrawWeapon(float DeltaTime)
{
	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;

	if (m_IsRoaring)
		return;

	if (!m_DrawWeaponEnable)
	{
		m_DrawWeaponEnable = true;

		if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHIdle"))
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawWeapon");

			ChangeBowFunc("BowLeftHand", "BowOpen");
			m_Bow->SetRelativeRotation(0.f, 0.f, 0.f);
			m_Bow->SetRelativePos(2.f, 0.f, 0.f);
			CResourceManager::GetInst()->SoundPlay("DrawBow");
		}
		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHWalkAndDrawWeapon");

			ChangeBowFunc("BowLeftHand", "BowOpen");
			m_Bow->SetRelativeRotation(0.f, 0.f, 0.f);
			m_Bow->SetRelativePos(2.f, 0.f, 0.f);
			CResourceManager::GetInst()->SoundPlay("DrawBow");
		}
	}

	if (m_DrawWeaponEnable)
	{
		if (m_PlayerInfo->Stamina < 20.f)
			return;

		if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedIdle") || 
			m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalk") ||
			m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkStart") ||
			m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkEnd"))
		{
			//m_DragonShotEnable = true;
			m_PlayerInfo->Stamina -= 30.f;
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDragonShotStart");
			CDragonArrow* Arrow = m_Scene->CreateGameObject<CDragonArrow>("DragonArrow");
			Arrow->SetRelativeRotation(90.f, 30.f, 0.f);
			Arrow->SetArrowState(DragonArrow_State::Charging);
			m_Mesh->AddChild(Arrow, "BowRightHand");
			CResourceManager::GetInst()->SoundPlay("DragonStart");
		}
	}
}

void CPlayer::Sheathe(float DeltaTime)
{
	if (m_JoomEnable)
	{
		m_DrawWeaponTime = 0.f;

		return;
	}

	if (m_DrawWeaponEnable)
	{
		m_DrawWeaponTime += DeltaTime;

		if (m_DrawWeaponTime >= 7.f)
		{
			// 걷고있을 때랑 가만히 있을때랑 무기 집어넣는 모션이 다름
			if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
			{
				if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedIdle"))
				{
					m_DrawWeaponTime = 0.f;
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHSheathe");
					((CAnimationMeshComponent*)m_Bow->GetRootComponent())->GetAnimationInstance()->ChangeAnimation("BowBack");
					CResourceManager::GetInst()->SoundPlay("SheatheBow");
				}
			}

			else
			{
				if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalk") ||
					m_RunQuickFrontDown || m_RunQuickBackDown || m_RunQuickLeftDown || m_RunQuickRightDown)
				{
					m_DrawWeaponTime = 0.f;
					m_DrawToSheateWalkTime = 0.f;
					m_DrawWalkToSheatheEnable = true;

					m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkAndSheathe");
					((CAnimationMeshComponent*)m_Bow->GetRootComponent())->GetAnimationInstance()->ChangeAnimation("BowBack");
					CResourceManager::GetInst()->SoundPlay("SheatheBow");
				}
			}
		}
	}
}

void CPlayer::PotionDown(float DeltaTime)
{
}

void CPlayer::CoatingDown(float DeltaTime)
{
	if (m_Scene->GetSceneMode()->CheckType<CTownSceneMode>())
		return;
	if (CheckAnimationFunc(true, "BHDrawedIdle") || CheckAnimationFunc(true, "BHDrawedWalk") || 
		CheckAnimationFunc(true, "BHDrawedWalkStart") || CheckAnimationFunc(true, "BHDrawedWalkEnd"))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHCoating");

		m_DrawWeaponTime = 0.f;

		m_BottleWindow = m_Scene->GetViewport()->FindWidgetWindow<CBottleSlotWindow>("BottleSlotWindow");

		m_CoatingState = m_BottleWindow->UsingBottle(true);
	}
}

void CPlayer::InteractionDown(float DeltaTime)
{
	HealFlowerInteractionFunc();

	MonsterCarvingFunc();

	SignInteractionFunc();
}

void CPlayer::ESC(float DeltaTime)
{
	if (m_IsQuestAcept)
		return;

	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);

	m_QuestWindow = m_Scene->GetViewport()->FindWidgetWindow<CQuestWindow>("QuestWindow");

	if (!m_QuestWindow)
	{
		if (m_ESCButton)
		{
			m_ESCButton = false;

			CEngine::GetInst()->ShowUICursor(false);

			CWidgetWindow* ESCWindow = m_Scene->GetViewport()->FindWidgetWindow<CWidgetWindow>("ESCWindow");// ->FadeDestroy();

			if (ESCWindow)
				ESCWindow->FadeDestroy();

			return;
		}

		if (!m_ESCButton)
		{
			m_ESCButton = true;

			POINT MousePoint = {};

			GetCursorPos(&MousePoint);

			SetCursorPos((int)m_CenterPoint.x, (int)m_CenterPoint.y);

			CEngine::GetInst()->ShowUICursor(true);

			m_Scene->GetViewport()->CreateWidgetWindow<CESCWindow>("ESCWindow")->FadeEnable(true);
		}
	}

	else
	{
		m_ESCButton = false;

		CEngine::GetInst()->ShowUICursor(false);

		m_QuestWindow->Destroy();

		CQuestSubWindow1* Quest1 = m_Scene->GetViewport()->FindWidgetWindow<CQuestSubWindow1>("QuestSubWindow1");
		CQuestSubWindow2* Quest2 = m_Scene->GetViewport()->FindWidgetWindow<CQuestSubWindow2>("QuestSubWindow2");

		if (Quest1)
			Quest1->Destroy();

		if (Quest2)
			Quest2->Destroy();
	}
}

void CPlayer::ShotStartAddNotify()
{
	ChangeBowFunc("BowLeftHand", "BowChargingStart");
}

void CPlayer::ShotWalkStartAddNotify()
{
	ChangeBowFunc("BowLeftHand", "BowChargingStart");
}

void CPlayer::DrowedWeaponToChargingAddNotify()
{
	ChangeBowFunc("BowLeftHand", "BowChargingStart");
}

void CPlayer::IdleSheatheAddnotify()
{
	ChangeBowFunc("BackBow", "BowBack");
	m_Bow->SetRelativeRotation(0.f, 0.f, 90.f);
}

void CPlayer::WalkSheatheAddNotify()
{
	ChangeBowFunc("BackBow", "BowBack");
	m_Bow->SetRelativeRotation(0.f, 0.f, 90.f);
}

void CPlayer::QuickShotAddNotify()
{
	m_QuickShotCount = 2;
	m_QuickShotEnable = false;
	ChangeBowFunc("BowLeftHand", "BowShot");
	CResourceManager::GetInst()->SoundPlay("ArrowShoot");
	CResourceManager::GetInst()->SoundPlay("ArrowShotHight");
	CameraShakeFunc(0.3f, 0.03f);

	for (int i = 0; i < 3; ++i)
	{
		char Name[64] = {};

		sprintf_s(Name, "QuickArrow%d", i);
		CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

		if (Arrow)
		{
			Arrow->SetWorldPos(m_Mesh->GetWorldPos().x, m_Mesh->GetWorldPos().y + 7.4f, m_Mesh->GetWorldPos().z);
			Arrow->SetRelativeRotation(m_Mesh->GetWorldRot().x, m_Mesh->GetWorldRot().y - 5.f + i * 5.f, m_Mesh->GetWorldRot().z);
			Arrow->SetArrowState(Arrow_State::Flying);
			m_Mesh->DeleteChild(Arrow);
		}
	}
}

void CPlayer::PowerShotAddNotify()
{
	m_QuickShotCount = 0;
	m_PowerShotEnable = false;
	ChangeBowFunc("BowLeftHand", "BowShot");
	CResourceManager::GetInst()->SoundPlay("PowerShot");
	CResourceManager::GetInst()->SoundPlay("ArrowShoot");
	CResourceManager::GetInst()->SoundPlay("ArrowShotHight");
	CameraShakeFunc(0.5f, 0.03f);

	m_Bow->SetRimLightEnable(true);
	m_Bow->SetLoopEnable(true);

	for (int i = 0; i < 5; ++i)
	{
		char Name[64] = {};

		sprintf_s(Name, "QuickArrow%d", i);
		CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

		if (Arrow)
		{
			Arrow->SetWorldPos(m_Mesh->GetWorldPos().x, m_Mesh->GetWorldPos().y + 7.4f, m_Mesh->GetWorldPos().z);
			Arrow->SetRelativeRotation(m_Mesh->GetWorldRot().x, m_Mesh->GetWorldRot().y - 10.f + i * 5.f, m_Mesh->GetWorldRot().z);
			Arrow->SetArrowState(Arrow_State::Flying);
			m_Mesh->DeleteChild(Arrow);
		}
	}
}

void CPlayer::DragonShotStartAddNotify()
{
	ChangeBowFunc("BowLeftHand", "BowChargingStart");
	m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
	m_Bow->SetRelativePos(2.f, 0.f, 0.f);
	m_Bow->SetRimLightEnable(true);
	m_Bow->SetLoopEnable(true);
	m_Bow->SetTime(0.5f);
	CResourceManager::GetInst()->SoundPlay("DragonCharge");

	m_ChargingParticle = m_Scene->CreateGameObject<CChargingParticle>("ChargingParticle");

	m_Camera->ShakeOn(0.05f, 2.2f, true);
}

void CPlayer::DragonShotAddNotify()
{
	m_DragonShotEnable = true;
}

void CPlayer::EvadeFrontShotChangeAddNotify()
{
	if (m_EvadeChangeAttack)
	{
		if (m_ChargingEnable)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingFrontStep");
		}
		else
		{
			ChargingShotUpFunc();
			BowEffectVfxEndFunc();

			CResourceManager::GetInst()->SoundStop("ChargingLoop");
			CResourceManager::GetInst()->SoundPlay("ArrowShoot");

			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingFrontStepShot");
			//m_EvadeFrontShotEnable = false;
		}
		m_EvadeChangeAttack = false;
	}
	/*else
	{


		m_Bow->SetRimLightEnable(false);
	}*/
}

void CPlayer::EvadeBackShotChangeAddNotify()
{
	if (m_EvadeChangeAttack)
	{
		if (m_ChargingEnable)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingBackStep");
		}
		else
		{
			ChargingShotUpFunc();
			BowEffectVfxEndFunc();

			CResourceManager::GetInst()->SoundStop("ChargingLoop");
			CResourceManager::GetInst()->SoundPlay("ArrowShoot");

			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingBackStepShot");
			//m_EvadeBackShotEnable = false;
		}
		m_EvadeChangeAttack = false;
	}
}

void CPlayer::EvadeLeftShotChangeAddNotify()
{
	if (m_EvadeChangeAttack)
	{
		if (m_ChargingEnable)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingLeftStep");
		}
		else
		{
			ChargingShotUpFunc();
			BowEffectVfxEndFunc();

			CResourceManager::GetInst()->SoundStop("ChargingLoop");
			CResourceManager::GetInst()->SoundPlay("ArrowShoot");

			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingLeftStepShot");
			//m_EvadeLeftShotEnable = false;
		}
		m_EvadeChangeAttack = false;
	}
}

void CPlayer::EvadeRightShotChangeAddNotify()
{
	if (m_EvadeChangeAttack)
	{
		if (m_ChargingEnable)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingRightStep");
		}
		else
		{
			ChargingShotUpFunc();
			BowEffectVfxEndFunc();

			CResourceManager::GetInst()->SoundStop("ChargingLoop");
			CResourceManager::GetInst()->SoundPlay("ArrowShoot");

			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingRightStepShot");
			//m_EvadeRightShotEnable = false;
		}
		m_EvadeChangeAttack = false;
	}
}

void CPlayer::EvadeShotAddNotify()
{
	m_EvadeFrontShotEnable = false;
	m_EvadeBackShotEnable = false;
	m_EvadeLeftShotEnable = false;
	m_EvadeRightShotEnable = false;
	m_EvadeChangeAttack = false;
}

void CPlayer::TrippingByFrontAddNotify()
{
	m_TrippingEnable = false;
}

void CPlayer::RollByFrontAddNotify()
{
	m_RollEnable = false;
}

void CPlayer::RunSoundNotify()
{
	int LandMatType = CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->CheckCellMat(m_Mesh->GetWorldPos());

	switch (LandMatType)
	{
	case 0:
		CResourceManager::GetInst()->SoundPlay("DirtStep1");
		break;
	case 1:
		CResourceManager::GetInst()->SoundPlay("SandStep1");
		break;
	case 2:
		CResourceManager::GetInst()->SoundPlay("StoneStep1");
		break;
	}
}

void CPlayer::CoatingSoundNotify()
{
	CResourceManager::GetInst()->SoundPlay("Remove_coating");
}

void CPlayer::CarvingSoundStartNotify()
{
	CResourceManager::GetInst()->SoundPlay("Carving");
}

void CPlayer::ShotEndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
}

void CPlayer::RunStartNotify()
{
	if ((m_FrontDown || m_BackDown || m_LeftDown || m_RightDown) &&
		(!m_RunQuickFrontDown || !m_RunQuickBackDown || !m_RunQuickLeftDown || !m_RunQuickRightDown))
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRun");


	if ((m_RunQuickFrontDown || m_RunQuickBackDown || m_RunQuickLeftDown || m_RunQuickRightDown) &&
		(!m_FrontDown || !m_BackDown || !m_LeftDown || !m_RightDown))
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunQuick");
}

void CPlayer::RunEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
}

void CPlayer::EvadeEndNotify()
{
	m_EvadeEnable = false;

	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
}

void CPlayer::DrawedEvadeEndNotify()
{
	m_EvadeEnable = false;

	if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");

	else
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkStart");

}

void CPlayer::DrawedEvadeToWalkStartEndNotify()
{
	m_EvadeEnable = false;

	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedEvadeToDrawedWalk");
}

void CPlayer::DrawedEvadeToWalkEndNotify()
{
	m_EvadeEnable = false;

	if (m_FrontDown || m_BackDown || m_LeftDown || m_RightDown)
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalk");

	else
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
}

void CPlayer::DrawWeaponEndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
}

void CPlayer::SheathEndNotify()
{
	m_DrawWeaponTime = 0.f;
	m_DrawWeaponEnable = false;
	m_DrawWalkToSheatheEnable = false;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
}

void CPlayer::WalkSheathEndNotify()
{
	m_DrawWeaponTime = 0.f;
	m_DrawWeaponEnable = false;
	m_DrawWalkToSheatheEnable = false;

	if (m_FrontDown || m_BackDown || m_LeftDown || m_RightDown)
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunStart");

	else
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
}

void CPlayer::DrawWalkStartEndNotify()
{
	if (m_FrontDown || m_BackDown || m_LeftDown || m_RightDown)
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalk");

	else
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkEnd");
}

void CPlayer::DrawWalkEndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
}

void CPlayer::WalkAndDrawEndNotify()
{
	if (m_FrontDown || m_BackDown || m_LeftDown || m_RightDown)
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkStart");

	else
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
}

void CPlayer::DrawedWeaponToChargingEnd()
{
	if (m_FrontDown || m_BackDown || m_LeftDown || m_RightDown)
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalk");

	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedToChargingStart");
		m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
		m_Bow->SetRelativePos(2.f, 0.f, 0.f);
	}
	//m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingStartIdle");
}

void CPlayer::DrawedToChargingStartEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
}

void CPlayer::ChargingStartIdleFirstEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
}

void CPlayer::ChargedShotEnd()
{
	m_ChargingEnable = false;

	if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
	{
		if (!m_JoomEnable)
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");

		else
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
	}

	else
	{
		if (m_JoomEnable)
		{
			if (m_FrontDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 왼쪽으로 달리기
			else if (m_FrontDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 오른쪽 달리기
			else if (m_FrontDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			else if (m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 왼쪽으로 달리기
			else if (m_BackDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 오른쪽 달리기
			else if (m_BackDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 왼쪽 달리기
			else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkLeft");
			}
			// 오른쪽 달리기
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkRight");
			}
		}
		else
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalk");
	}
	//ChangeBowFunc("BowLeftHand", "BowOpen");
}

void CPlayer::FullChargedShotEnd()
{
	m_ChargingEnable = false;
	if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
	{
		if (!m_JoomEnable)
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");

		else
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
	}

	else
	{
		if (m_JoomEnable)
		{
			if (m_FrontDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 왼쪽으로 달리기
			else if (m_FrontDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 오른쪽 달리기
			else if (m_FrontDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			else if (m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 왼쪽으로 달리기
			else if (m_BackDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 오른쪽 달리기
			else if (m_BackDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 왼쪽 달리기
			else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkLeft");
			}
			// 오른쪽 달리기
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkRight");
			}
		}
		else
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalk");
	}
}

void CPlayer::DrawnWalkToChargingStartEnd()
{
	if (m_FrontDown || m_BackDown || m_LeftDown || m_RightDown)
	{
		if (!m_JoomEnable)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalk");
		}

		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalk");
		}
	}

	else
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalkEnd");
}

void CPlayer::ChargingWalkEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
}

void CPlayer::QuickShotEnd()
{
	if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
	{
		if (m_JoomEnable)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
		}

		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
		}
	}
	else
	{
		if (m_JoomEnable)
		{
			if (m_FrontDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 왼쪽으로 달리기
			else if (m_FrontDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 오른쪽 달리기
			else if (m_FrontDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			else if (m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 왼쪽으로 달리기
			else if (m_BackDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 오른쪽 달리기
			else if (m_BackDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 왼쪽 달리기
			else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkLeft");
			}
			// 오른쪽 달리기
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkRight");
			}
		}
		else
		{
			if (m_FrontDown || m_LeftDown || m_RightDown || m_BackDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalk");
			}

			else
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
			}
		}
	}
}

void CPlayer::PowerShotEnd()
{

	m_Bow->SetRimLightEnable(false);
	if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
	{
		if (m_JoomEnable)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
		}

		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
		}
	}
	else
	{
		if (m_JoomEnable)
		{
			if (m_FrontDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 왼쪽으로 달리기
			else if (m_FrontDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			// 정면 오른쪽 달리기
			else if (m_FrontDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			else if (m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 왼쪽으로 달리기
			else if (m_BackDown && m_LeftDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 뒤 오른쪽 달리기
			else if (m_BackDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			// 왼쪽 달리기
			else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkLeft");
			}
			// 오른쪽 달리기
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkRight");
			}
		}
		else
		{
			if (m_FrontDown || m_LeftDown || m_RightDown || m_BackDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalk");
			}

			else
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
			}
		}
	}
}

void CPlayer::DragonShotStartEnd()
{
	if (m_ChargingParticle)
	{
		m_ChargingParticle->SetParticleAlive(0);
		m_ChargingParticle->Destroy();
	}

	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDragonShot");

	ChangeBowFunc("BowLeftHand", "BowShot");
	CDragonArrow* Arrow = (CDragonArrow*)m_Scene->FindObject("DragonArrow");

	if (Arrow)
	{
		m_Mesh->DeleteChild(Arrow);
		Arrow->SetWorldPos(m_Mesh->GetWorldPos().x, m_Mesh->GetWorldPos().y + 4.4f, m_Mesh->GetWorldPos().z);
		Arrow->SetRelativeRotation(m_Mesh->GetWorldRot());
		Arrow->SetArrowState(DragonArrow_State::Flying);

		m_DragonShotEnable = false;

		CResourceManager::GetInst()->SoundPlay("DragonShot");
	}

	CameraShakeFunc(1.5f, 0.3f);
}

void CPlayer::DragonShotEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");

	m_Bow->SetRimLightEnable(false);
}

void CPlayer::EvadeShotEnd()
{
	if (m_ChargingEnable)
	{
		if (m_JoomEnable)
		{
			if (m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimChargingWalkFront");
			}
			else if (!m_FrontDown && m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimChargingWalkBack");
			}
			else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimChargingWalkLeft");
			}
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimChargingWalkRight");
			}
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargingIdleLoop");
			}
		}

		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalk");
		}
	}
	else
	{
		if (m_JoomEnable)
		{
			if (m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
			}
			else if (!m_FrontDown && m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
			}
			else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkLeft");
			}
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkRight");
			}
			else if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
			}
		}
		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
		}
		CResourceManager::GetInst()->SoundStop("ChargingLoop");
		DestroyArrowFunc();
		BowEffectVfxEndFunc();

		m_Bow->SetRimLightEnable(false);
	}
	m_EvadeFrontShotEnable = false;
	m_EvadeBackShotEnable = false;
	m_EvadeLeftShotEnable = false;
	m_EvadeRightShotEnable = false;

	m_EvadeChangeAttack = false;

	//m_Bow->SetRimLightEnable(false);
}

void CPlayer::EvadeRealShotEnd()
{
	if (m_JoomEnable)
	{
		if (m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkFront");
		}
		else if (!m_FrontDown && m_BackDown && !m_LeftDown && !m_RightDown)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkBack");
		}
		else if (!m_FrontDown && !m_BackDown && m_LeftDown && !m_RightDown)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkLeft");
		}
		else if (!m_FrontDown && !m_BackDown && !m_LeftDown && m_RightDown)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimWalkRight");
		}
		else if (!m_FrontDown && !m_BackDown && !m_LeftDown && !m_RightDown)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHAimIdle");
		}
	}
	else
	{
		ChargingShotUpFunc();
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
	}
	m_EvadeFrontShotEnable = false;
	m_EvadeBackShotEnable = false;
	m_EvadeLeftShotEnable = false;
	m_EvadeRightShotEnable = false;
	m_EvadeChangeAttack = false;
}

void CPlayer::CoatingEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
}

void CPlayer::CarvingStartEnd()
{
	if (m_HealEnable)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHCarvingEnd");

		m_HealEnable = false;
		m_PlayerInfo->HP += 30.f;

		if (m_PlayerInfo->HP > m_PlayerInfo->MaxHP)
		{
			m_PlayerInfo->HP = m_PlayerInfo->MaxHP;
		}

		CHealFlower* Flower = (CHealFlower*)m_Scene->FindObject(m_HealObjName);

		// 충돌체를 미리 지워버린다.
		Flower->FindComponent("HealFlowerBox")->Destroy();

		CHealEffect* Effect = m_Scene->CreateGameObject<CHealEffect>("HealEffect");

		Vector3 Pos = Flower->GetWorldPos();

		Pos.y += 5.f;

		Effect->SetWorldPos(Pos);

		if (Flower)
			Flower->SetDestroyEnable(true);
	}

	else if (m_MonsterCollision)
	{
		if (!m_ColliderObj)
			return;

		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHCarvingEnd");

		/*CBarnos* Barnos = (CBarnos*)m_Scene->FindObject(m_BarnosName);
		CJagras* Jagras = (CJagras*)m_Scene->FindObject(m_JagrasName);
		CKestodon* Kestodon = (CKestodon*)m_Scene->FindObject(m_KestodonName);
		CVespoid* Vespoid = (CVespoid*)m_Scene->FindObject(m_VespoidName);
		CAnjanath* Anjanath = (CAnjanath*)m_Scene->FindObject(m_AnjanthName);
		CRathalos* Rathalos = (CRathalos*)m_Scene->FindObject(m_RathalosName);*/

		if (m_ColliderObj->CheckType<CBarnos>())
			((CBarnos*)m_ColliderObj)->SetIsCarved(true);

		if (m_ColliderObj->CheckType<CJagras>())
			((CJagras*)m_ColliderObj)->SetIsCarved(true);

		if (m_ColliderObj->CheckType<CKestodon>())
			((CKestodon*)m_ColliderObj)->SetIsCarved(true);

		if (m_ColliderObj->CheckType<CVespoid>())
			((CVespoid*)m_ColliderObj)->SetIsCarved(true);

		m_CarvingWindow->SetUIFadeEnable(true);
		m_CarvingWindow->FadeDestroy();
		m_CarvingEnable = true;

		m_CarvingRightWindow = m_Scene->GetViewport()->FindWidgetWindow<CCarvingRightWindow>("CarvingRightWindow");

		if (!m_CarvingRightWindow)
		{
			m_CarvingRightWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingRightWindow>("CarvingRightWindow");
		}

		else
		{
			m_CarvingRightWindow->SetNewUIEnable(true);
			m_CarvingRightWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingRightWindow>("CarvingRightWindow");
		}

		if (m_ColliderObj->CheckType<CBarnos>())
			m_CarvingRightWindow->SetMonsterName(Monster_Name::Barnos);

		else if (m_ColliderObj->CheckType<CJagras>())
			m_CarvingRightWindow->SetMonsterName(Monster_Name::Jagras);

		else if (m_ColliderObj->CheckType<CKestodon>())
			m_CarvingRightWindow->SetMonsterName(Monster_Name::Kestodon);

		else if (m_ColliderObj->CheckType<CVespoid>())
			m_CarvingRightWindow->SetMonsterName(Monster_Name::Vespoid);

		else if (m_ColliderObj->CheckType<CAnjanath>())
		{
			m_CarvingRightWindow->SetMonsterName(Monster_Name::Anjanath);
			((CAnjanath*)m_ColliderObj)->SetDestroyCarvingCollider();

			m_ColliderObj = nullptr;
		}

		else if (m_ColliderObj->CheckType<CRathalos>())
		{
			m_CarvingRightWindow->SetMonsterName(Monster_Name::Rathalos);
			((CRathalos*)m_ColliderObj)->SetDestroyCarvingCollider();

			m_ColliderObj = nullptr;
		}
	}
}

void CPlayer::CarvingEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
}

void CPlayer::TrippingByFrontEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHTrippingToIdle");
}

void CPlayer::TrippingToIdleEnd()
{
	if (m_DrawWeaponEnable)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
	}

	if (m_DrawWeaponEnable)
	{
		m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
	}

	m_Bow->SetWorldScale(0.7f, 1.f, 0.7f);
}

void CPlayer::RollByFrontStartEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRollByFrontEnd");
}

void CPlayer::RollByFrontEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRollOverToIdle");
}

void CPlayer::RollOverToIdleEnd()
{
	if (m_DrawWeaponEnable)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
	}

	if (m_DrawWeaponEnable)
	{
		m_Bow->SetRelativeRotation(0.f, 0.f, -5.f);
	}

	m_Bow->SetWorldScale(0.7f, 1.f, 0.7f);
}

void CPlayer::PlugEarsStartNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHPlugEarsToIdle");
}

void CPlayer::PlugEarsEndNotify()
{
	if (m_DrawWeaponEnable)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedIdle");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
	}
}

void CPlayer::BHDown3EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BHIdle");
}

void CPlayer::SetKeyCallback()
{
	// 일반 달리기
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunFront", Key_State::KeyState_Down, this, &CPlayer::MoveFrontDown);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunFront", Key_State::KeyState_Push, this, &CPlayer::MoveFront);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunFront", Key_State::KeyState_Up, this, &CPlayer::MoveFrontUp);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunBack", Key_State::KeyState_Down, this, &CPlayer::MoveBackDown);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunBack", Key_State::KeyState_Push, this, &CPlayer::MoveBack);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunBack", Key_State::KeyState_Up, this, &CPlayer::MoveBackUp);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunLeft", Key_State::KeyState_Down, this, &CPlayer::MoveLeftDown);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunLeft", Key_State::KeyState_Push, this, &CPlayer::MoveLeft);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunLeft", Key_State::KeyState_Up, this, &CPlayer::MoveLeftUp);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunRight", Key_State::KeyState_Down, this, &CPlayer::MoveRightDown);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunRight", Key_State::KeyState_Push, this, &CPlayer::MoveRight);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunRight", Key_State::KeyState_Up, this, &CPlayer::MoveRightUp);

	// 빠른 달리기 
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickFront", Key_State::KeyState_Push, this, &CPlayer::RunQuickFront);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickFront", Key_State::KeyState_Up, this, &CPlayer::RunQuickFrontUp);
	CInput::GetInst()->SetShiftKey("RunQuickFront", true);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickBack", Key_State::KeyState_Push, this, &CPlayer::RunQuickBack);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickBack", Key_State::KeyState_Up, this, &CPlayer::RunQuickBackUp);
	CInput::GetInst()->SetShiftKey("RunQuickBack", true);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickLeft", Key_State::KeyState_Push, this, &CPlayer::RunQuickLeft);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickLeft", Key_State::KeyState_Up, this, &CPlayer::RunQuickLeftUp);
	CInput::GetInst()->SetShiftKey("RunQuickLeft", true);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickRight", Key_State::KeyState_Push, this, &CPlayer::RunQuickRight);
	CInput::GetInst()->SetKeyCallback<CPlayer>("RunQuickRight", Key_State::KeyState_Up, this, &CPlayer::RunQuickRightUp);
	CInput::GetInst()->SetShiftKey("RunQuickRight", true);

	// 공격
	CInput::GetInst()->SetKeyCallback<CPlayer>("Attack", Key_State::KeyState_Down, this, &CPlayer::ShotStart);
	CInput::GetInst()->SetKeyCallback<CPlayer>("Attack", Key_State::KeyState_Push, this, &CPlayer::BowCharging);
	CInput::GetInst()->SetKeyCallback<CPlayer>("Attack", Key_State::KeyState_Up, this, &CPlayer::ShotEnd);
	CInput::GetInst()->SetKeyCallback<CPlayer>("AttackJoom", Key_State::KeyState_Down, this, &CPlayer::ChargingJoomDown);
	CInput::GetInst()->SetKeyCallback<CPlayer>("AttackJoom", Key_State::KeyState_Up, this, &CPlayer::ChargingJoomUp);

	// 퀵샷 커맨드
	CInput::GetInst()->SetKeyCallback<CPlayer>("QuickShot", Key_State::KeyState_Down, this, &CPlayer::QuickShotDown);

	// 회피샷 커맨드
	CInput::GetInst()->SetKeyCallback<CPlayer>("EvadeShot", Key_State::KeyState_Down, this, &CPlayer::EvadeShotDown);

	// 스페이스바 회피 구르기
	CInput::GetInst()->SetKeyCallback<CPlayer>("Evade", Key_State::KeyState_Down, this, &CPlayer::EvadeClick);
	CInput::GetInst()->SetKeyCallback<CPlayer>("EvadeShift", Key_State::KeyState_Down, this, &CPlayer::EvadeClick);
	CInput::GetInst()->SetShiftKey("EvadeShift", true);

	// Draw
	CInput::GetInst()->SetKeyCallback<CPlayer>("DrawWeapon", Key_State::KeyState_Down, this, &CPlayer::DrawWeapon);

	// Potion
	CInput::GetInst()->SetKeyCallback<CPlayer>("Potion", Key_State::KeyState_Down, this, &CPlayer::PotionDown);

	// Coating
	CInput::GetInst()->SetKeyCallback<CPlayer>("Coating", Key_State::KeyState_Down, this, &CPlayer::CoatingDown);

	// Coating
	CInput::GetInst()->SetKeyCallback<CPlayer>("Interaction", Key_State::KeyState_Down, this, &CPlayer::InteractionDown);


	// ESC버튼
	CInput::GetInst()->SetKeyCallback<CPlayer>("ESC", Key_State::KeyState_Down, this, &CPlayer::ESC);
}

void CPlayer::SetNotify()
{
	// 노티파이들
	// Add
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingStartIdleFirst", "ChargingStart", 15, this, &CPlayer::ShotStartAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawnWalkToChargingStart", "ChargingWalkStart", 25, this, &CPlayer::ShotWalkStartAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawnWalkToChargingStart", "ChargingWalkStartEnd", 94, this, &CPlayer::DrawnWalkToChargingStartEnd);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWeaponToCharging", "DrawedWeaponToCharging", 26, this, &CPlayer::DrowedWeaponToChargingAddNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHSheathe", "Sheathe", 55, this, &CPlayer::IdleSheatheAddnotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkAndSheathe", "WalkSheathe", 55, this, &CPlayer::WalkSheatheAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHQuickShot", "QuickShot", 35, this, &CPlayer::QuickShotAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHPowerShot", "PowerShot", 15, this, &CPlayer::PowerShotAddNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDragonShotStart", "DragonShotStart", 85, this, &CPlayer::DragonShotStartAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDragonShot", "DragonShot", 5, this, &CPlayer::DragonShotAddNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingFrontStep", "EvadeFront", 47, this, &CPlayer::EvadeFrontShotChangeAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingBackStep", "EvadeBack", 47, this, &CPlayer::EvadeBackShotChangeAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingLeftStep", "EvadeLeft", 47, this, &CPlayer::EvadeLeftShotChangeAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingRightStep", "EvadeRight", 47, this, &CPlayer::EvadeRightShotChangeAddNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingFrontStepShot", "EvadeFrontShot", 15, this, &CPlayer::EvadeShotAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingBackStepShot", "EvadeBackShot", 15, this, &CPlayer::EvadeShotAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingLeftStepShot", "EvadeLeftShot", 15, this, &CPlayer::EvadeShotAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHChargingRightStepShot", "EvadeRightShot", 15, this, &CPlayer::EvadeShotAddNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHTrippingByFront", "TrippingByFront", 30, this, &CPlayer::TrippingByFrontAddNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRollByFrontEnd", "RollByFrontEnd", 50, this, &CPlayer::RollByFrontAddNotify);

	// Add Sound Notify;
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunStart", "RunLoopSound", 20, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunStart", "RunLoopSound", 44, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunStart", "RunLoopSound", 66, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRun", "RunLoopSound", 20, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRun", "RunLoopSound", 46, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunQuick", "RunLoopSound", 20, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunQuick", "RunLoopSound", 46, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunEnd", "RunLoopSound", 4, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunEnd", "RunLoopSound", 19, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHRunEnd", "RunLoopSound", 39, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalk", "RunLoopSound", 19, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalk", "RunLoopSound", 42, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkStart", "RunLoopSound", 34, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkStart", "RunLoopSound", 54, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkStart", "RunLoopSound", 74, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkStart", "RunLoopSound", 94, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkEnd", "RunLoopSound", 4, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkEnd", "RunLoopSound", 23, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkEnd", "RunLoopSound", 47, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkAndSheathe", "RunLoopSound", 15, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkAndSheathe", "RunLoopSound", 45, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkAndSheathe", "RunLoopSound", 68, this, &CPlayer::RunSoundNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHDrawedWalkAndSheathe", "RunLoopSound", 95, this, &CPlayer::RunSoundNotify);

	// Coating Sound
	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHCoating", "CoatingRemove", 25, this, &CPlayer::CoatingSoundNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHCarvingStart", "BHCarvingStart", 25, this, &CPlayer::CarvingSoundStartNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CPlayer>("BHCarvingStart", "BHCarvingStart", 200, this, &CPlayer::CarvingSoundStartNotify);
	//End
	//m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHShot", this, &CPlayer::ShotEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHRunStart", this, &CPlayer::RunStartNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHRunEnd", this, &CPlayer::RunEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHEvade", this, &CPlayer::EvadeEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedEvade", this, &CPlayer::DrawedEvadeEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedEvadeToDrawedWalkStart", this, &CPlayer::DrawedEvadeToWalkStartEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedEvadeToDrawedWalk", this, &CPlayer::DrawedEvadeToWalkEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawWeapon", this, &CPlayer::DrawWeaponEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHSheathe", this, &CPlayer::SheathEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedWalkAndSheathe", this, &CPlayer::WalkSheathEndNotify);

	// Draw
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedWalkStart", this, &CPlayer::DrawWalkStartEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedWalkEnd", this, &CPlayer::DrawWalkEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHWalkAndDrawWeapon", this, &CPlayer::WalkAndDrawEndNotify);

	// Charging
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedWeaponToCharging", this, &CPlayer::DrawedWeaponToChargingEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawedToChargingStart",
		this, &CPlayer::DrawedToChargingStartEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingStartIdleFirst", this, &CPlayer::ChargingStartIdleFirstEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargedShotIdle", this, &CPlayer::ChargedShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHFullChargedShotIdle", this, &CPlayer::FullChargedShotEnd);
	//m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDrawnWalkToChargingStart", this, &CPlayer::DrawnWalkToChargingStartEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingWalkEnd", this, &CPlayer::ChargingWalkEnd);


	// Quick Shot
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHQuickShot", this, &CPlayer::QuickShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHPowerShot", this, &CPlayer::PowerShotEnd);

	// Dragon Shot
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDragonShotStart", this, &CPlayer::DragonShotStartEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDragonShot", this, &CPlayer::DragonShotEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingFrontStep", this, &CPlayer::EvadeShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingBackStep", this, &CPlayer::EvadeShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingLeftStep", this, &CPlayer::EvadeShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingRightStep", this, &CPlayer::EvadeShotEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingFrontStepShot", this, &CPlayer::EvadeRealShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingBackStepShot", this, &CPlayer::EvadeRealShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingLeftStepShot", this, &CPlayer::EvadeRealShotEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHChargingRightStepShot", this, &CPlayer::EvadeRealShotEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHCoating", this, &CPlayer::CoatingEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHCarvingStart", this, &CPlayer::CarvingStartEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHCarvingEnd", this, &CPlayer::CarvingEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHTrippingByFront", this, &CPlayer::TrippingByFrontEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHTrippingToIdle", this, &CPlayer::TrippingToIdleEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHRollByFrontStart", this, &CPlayer::RollByFrontStartEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHRollByFrontEnd", this, &CPlayer::RollByFrontEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHRollOverToIdle", this, &CPlayer::RollOverToIdleEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHPlugEarsStart", this, &CPlayer::PlugEarsStartNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHPlugEarsToIdle", this, &CPlayer::PlugEarsEndNotify);
	
	m_Mesh->GetAnimationInstance()->SetEndFunction<CPlayer>("BHDown3", this, &CPlayer::BHDown3EndNotify);
}

void CPlayer::EvadeUpdate(float DeltaTime)
{
	m_EvadeTime += DeltaTime;

	if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
	{
		if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
			AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed - 10.f + (m_EvadeTime * 13.f)) * DeltaTime);

		else
			AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed - 10.f + (m_EvadeTime * 13.f)) * DeltaTime);
		//m_Mesh->AddRelativePos(GetWorldAxis(AXIS::AXIS_Z) * (m_PlayerInfo->Speed - 10.f + (m_EvadeTime * 13.f)) * DeltaTime);
	}
}

void CPlayer::EvadeWalkUpdate(float DeltaTime)
{
	m_EvadeTime += DeltaTime;

	if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
	{
		if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
			AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed - 10.f + (m_EvadeTime * 9.f)) * DeltaTime);

		else
			AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed - 10.f + (m_EvadeTime * 9.f)) * DeltaTime);
		//m_Mesh->AddRelativePos(GetWorldAxis(AXIS::AXIS_Z) * (m_PlayerInfo->Speed - 10.f + (m_EvadeTime * 9.f)) * DeltaTime);
	}
}

void CPlayer::DrawToSheatWalkUpdate(float DeltaTime)
{
	if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalk"))
	{
		if (m_DrawWalkToSheatheEnable)
		{
			m_DrawToSheateWalkTime += DeltaTime;

			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed + (m_DrawToSheateWalkTime * 7.f)) * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed + (m_DrawToSheateWalkTime * 7.f)) * DeltaTime);
			//m_Mesh->AddRelativePos(GetWorldAxis(AXIS::AXIS_Z) * (m_PlayerInfo->Speed + (m_DrawToSheateWalkTime * 7.f)) * DeltaTime);
		}
	}
}

void CPlayer::ChargingUpdate(float DeltaTime)
{
	// 여기가 문제임
	if ((m_PlayerInfo->Stamina <= 10.f) && m_ChargingEnable)
	{
		m_ChargingEnable = false;

		ChargingShotUpFunc();
		BowEffectVfxEndFunc();
		ChangeBowFunc("BowLeftHand", "BowShot");
		CResourceManager::GetInst()->SoundStop("ChargingLoop");
		CResourceManager::GetInst()->SoundPlay("ArrowShoot");
		m_DrawWeaponTime = 0.f;

		return;
	}
	// 차징 시간
	if (m_ChargingEnable)
	{
		if (m_ChargingCount < 2)
		{
			m_DrawWeaponTime = 0.f;

			m_ChargingTime -= DeltaTime * 200.f;

			if (m_ChargingTime <= 0.f)
			{
				++m_ChargingCount;
				m_ChargingTime = 200.f;

				char Name[32] = {};

				CBowVfx* BowVFX = (CBowVfx*)m_Scene->FindObject("BowVfx");

				if (!BowVFX)
					BowEffectVfxStartFunc();

				while (true)
				{
					sprintf_s(Name, "Arrow%d", m_ChargingCount + m_ArrowCount);

					CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

					if (Arrow)
					{
						++m_ArrowCount;
					}

					else
					{
						break;
					}
				}

				CArrow* Arrow = m_Scene->CreateGameObject<CArrow>(Name);
				Arrow->SetRelativeRotation(90.f, 30.f, 0.f);
				Arrow->SetArrowState(Arrow_State::Charging);
				Arrow->SetArrowCoatingState(m_CoatingState);
				m_Mesh->AddChild(Arrow, "BowRightHand");
				CResourceManager::GetInst()->SoundPlay("BowChargingCount");
				m_Bow->SetRimLightEnable(true);
				m_Bow->SetCharging1To2(true);
				m_Bow->SetFirstCharg(true);

				//if (m_ChargingCount == 1)
				//{
				//	m_Bow->SetFirstCharg(true);
				//}

				//else if (m_ChargingCount == 2)
				//{
				//	m_Bow->SetCharging1To2(true);
				//}
			}
		}
	}
}

void CPlayer::DrawedWalkAndSheatheUpdate(float DeltaTime)
{
	if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkAndSheathe"))
	{
		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed + 6.f) * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed + 6.f) * DeltaTime);
			//AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed + 6.f) * DeltaTime);
		}
	}
}

void CPlayer::ChargingJoomInUpdate(float DeltaTime)
{
	if (m_JoomEnable)
	{
		JoomRotationFunc(DeltaTime, 0.f);

		m_JoomTime += DeltaTime;

		if (m_JoomTime >= 0.5f)
			m_JoomTime = 0.5f;

		if (m_JoomTime < 0.5f)
			m_Camera->AddRelativePos(GetWorldAxis(AXIS_MAX) * 15.f * DeltaTime);
	}
}

void CPlayer::ChargingJoomOutUpdate(float DeltaTime)
{
	if (!m_JoomEnable)
	{
		m_JoomTime -= DeltaTime;

		if (m_JoomTime <= 0.f)
			m_JoomTime = 0.f;

		if (m_JoomTime > 0.f)
			m_Camera->AddRelativePos(GetWorldAxis(AXIS_MAX) * -15.f * DeltaTime);
	}
}

void CPlayer::ReturnChargingCountUpdate(float DeltaTime)
{
	if (m_ReturnEnable)
	{
		if (m_ChargingCount > 0)
		{
			m_ReturnChargingCountTime -= DeltaTime;

			if (m_ReturnChargingCountTime <= 0.f)
			{
				m_ChargingCount = 0;
				m_ReturnChargingCountTime = 1.8f;
			}
		}
	}
}

void CPlayer::DragonShotUpdate(float DeltaTime)
{
	if (m_DragonShotEnable)
	{
		m_DragonSpeed -= DeltaTime * 15.f;

		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * 1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * m_DragonSpeed * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * m_DragonSpeed * DeltaTime);
			//m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_Z) * m_DragonSpeed * DeltaTime);
		}

		if (m_DragonSpeed <= 0.f)
		{
			m_DragonSpeed = 20.f;

			m_DragonShotEnable = false;
		}
	}
}

void CPlayer::EvadeShotUpdate(float DeltaTime)
{
	if (m_EvadeFrontShotEnable)
	{
		if (CheckAnimationFunc(false, "BHChargingFrontStepShot"))
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingFrontStep");

		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * -m_EvadeShotSpeed * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * -m_EvadeShotSpeed * DeltaTime);
			//m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_Z) * -m_EvadeShotSpeed * DeltaTime);
		}
	}

	else if (m_EvadeBackShotEnable)
	{
		if (CheckAnimationFunc(false, "BHChargingBackStepShot"))
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingBackStep");

		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * m_EvadeShotSpeed * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * m_EvadeShotSpeed * DeltaTime);
			//m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_Z) * m_EvadeShotSpeed * DeltaTime);
		}
	}

	else if (m_EvadeLeftShotEnable)
	{
		if (CheckAnimationFunc(false, "BHChargingLeftStepShot"))
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingLeftStep");

		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_X) * m_EvadeShotSpeed * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * m_EvadeShotSpeed * DeltaTime);
			//m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_X) * m_EvadeShotSpeed * DeltaTime);
		}
	}

	else if (m_EvadeRightShotEnable)
	{
		if (CheckAnimationFunc(false, "BHChargingRightStepShot"))
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingRightStep");

		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_X) * -m_EvadeShotSpeed * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * -m_EvadeShotSpeed * DeltaTime);
			//m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_X) * -m_EvadeShotSpeed * DeltaTime);
		}
	}
}

void CPlayer::HitUpdate(float DeltaTime)
{
	if (m_TrippingEnable && CheckAnimationFunc(true, "BHTrippingByFront"))
	{
		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * 5.f * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * 5.f * DeltaTime);
		}

		m_DrawWeaponTime = 0.f;
	}

	if (m_IsHitBreath)
	{
		float HP = m_PlayerInfo->HP;

		HP -= DeltaTime * 3.f;

		m_PlayerInfo->HP = HP;

		m_HitBreathTime -= DeltaTime;

		if (m_HitBreathTime <= 0.f)
		{
			m_HitBreathTime = 5.f;
			m_IsHitBreath = false;
		}
	}
}

void CPlayer::HitRollUpdate(float DeltaTime)
{
	if (m_RollEnable && (CheckAnimationFunc(true, "BHRollByFrontStart") || CheckAnimationFunc(true, "BHRollByFrontEnd")))
	{
		if (CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * 1.5f))
		{
			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * 7.f * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * 7.f * DeltaTime);
			//m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_Z) * 7.f * DeltaTime);
		}
		m_DrawWeaponTime = 0.f;
	}
}

void CPlayer::MoveEnableUpdate(float DeltaTime)
{
	//Vector3 Dir = m_Mesh->GetWorldPos() - m_PrevPos;

	//float GetY = CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetY(m_Mesh->GetWorldPos());

	//float GetNextY = CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetY(m_Mesh->GetWorldPos() * Dir * 10.f);
	//
	//if (GetY - GetNextY >= 1.f)
	//{
	//	m_MoveEnable = false;
	//}


}

void CPlayer::CameraRayUpdate(float DeltaTime)
{
	
}

void CPlayer::BossRoaringUpdate(float DeltaTime)
{
	
	CAnjanath* Anjanath = (CAnjanath*)m_Scene->FindObject("Anjanath1");
	CRathalos* Rathalos = (CRathalos*)m_Scene->FindObject("Rathalos");

	if (Anjanath)
	{
		if (Anjanath->IsRoaring())
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHPlugEarsStart");
			m_Bow->SetRimLightEnable(false);
			DestroyArrowFunc();

			m_IsRoaring = true;
		}
		else
		{
			m_IsRoaring = false;
		}
	}

	if (Rathalos)
	{
		if (Rathalos->IsRoaring())
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHPlugEarsStart");
			m_Bow->SetRimLightEnable(false);
			DestroyArrowFunc();
			m_IsRoaring = true;
		}
		else
		{
			m_IsRoaring = false;

		}
	}

}

void CPlayer::CollisionFieldObjUpdate(float DeltaTime)
{
	if (m_IsFieldCollision)
	{
		Vector3 PlayerPos = m_Mesh->GetWorldPos();

		CGameObject* FieldObj = m_Scene->FindObject(m_FieldObjName);

		CSharedPtr<CColliderBox3D> Box = FieldObj->FindComponentFromType<CColliderBox3D>();

		Box_Type Type = Box->GetBoxType();

		switch (Type)
		{
		case Box_Type::Cube:
			// 정육면체에 대한 슬라이딩 벡터 처리
			CubeCollisionFunc(FieldObj, Box);
			break;
		case Box_Type::Cuboid:
			// 직육면체에 대한 슬라이딩 벡터 처리
			CuboidCollisionFunc(FieldObj, Box, DeltaTime);
			break;
		}
	}
}

void CPlayer::SignInteractionFunc()
{
	if (m_IsSignCollision)
	{
		m_ESCButton = true;

		POINT MousePoint = {};

		GetCursorPos(&MousePoint);

		SetCursorPos((int)m_CenterPoint.x, (int)m_CenterPoint.y);

		CEngine::GetInst()->ShowUICursor(true);

		m_QuestWindow = m_Scene->GetViewport()->FindWidgetWindow<CQuestWindow>("QuestWindow");

		if (!m_QuestWindow)
		{
			m_QuestWindow = m_Scene->GetViewport()->CreateWidgetWindow<CQuestWindow>("QuestWindow");
		}
	}
}

void CPlayer::RunFunc(float DeltaTime, float Rot)
{
	if (!CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
	{
		int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

		if (Rotation > 360)
		{
			Rotation -= 360;
		}

		else if (Rotation < 0)
		{
			Rotation += 360;
		}

		if (Rotation < 180 - m_CorrectionAngle || Rotation > 180 + m_CorrectionAngle)
		{
			// 플레이어가 좌에서 우로 회전 전방
			if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
			{
				m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
			}
			// 플레이어가 우에서 좌로 회전 전방
			if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
			{
				m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
			}
		}
	}
	
	else
	{
		if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHIdle"))
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunStart");
		}

		if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart"))
		{
			int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

			if (Rotation > 360)
			{
				Rotation -= 360;
			}

			else if (Rotation < 0)
			{
				Rotation += 360;
			}

			// 좌우 보정을 해주어 떨리는것을 방지해줌
			if (Rotation < 180 - m_CorrectionAngle || Rotation > 180 + m_CorrectionAngle)
			{
				// 플레이어가 좌에서 우로 회전 전방
				if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
				}
				// 플레이어가 우에서 좌로 회전 전방
				if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
				}
			}

			// 보정된 각도로 들어오게되면 강제로 설정된 각도로 세팅해준다
			else if (Rot == 0 || Rot == 180)
				m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

			else if (Rot == 90 || Rot == 270)
				m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

			//m_Velocity += GetWorldAxis(AXIS_Z) * m_PlayerInfo->Speed * DeltaTime;

			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * m_PlayerInfo->Speed * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * m_PlayerInfo->Speed * DeltaTime);

		}

		if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunEnd") &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart") &&
			!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHIdle") &&
			CheckAnimationFunc(false, "BHTrippingByFront") &&
			CheckAnimationFunc(false, "BHTrippingToIdle") &&
			CheckAnimationFunc(false, "BHRollByFrontStart") &&
			CheckAnimationFunc(false, "BHRollByFrontEnd") &&
			CheckAnimationFunc(false, "BHRollOverToIdle") &&
			CheckAnimationFunc(false, "BHPlugEarsStart") &&
			CheckAnimationFunc(false, "BHPlugEarsToIdle"))
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRun");

			int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

			if (Rotation > 360)
			{
				Rotation -= 360;
			}

			else if (Rotation < 0)
			{
				Rotation += 360;
			}

			if (Rotation < 180 - m_CorrectionAngle || Rotation > 180 + m_CorrectionAngle)
			{
				// 플레이어가 좌에서 우로 회전 전방
				if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
				}
				// 플레이어가 우에서 좌로 회전 전방
				if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
				}
			}

			else if (Rot == 0 || Rot == 180)
				m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

			else if (Rot == 90 || Rot == 270)
				m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

			if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
				AddWorldPos(GetWorldAxis(AXIS_Z) * m_PlayerInfo->Speed * DeltaTime);

			else
				AddWorldPos(m_SlidingVec * m_PlayerInfo->Speed * DeltaTime);

			Vector3 Test = GetWorldAxis(AXIS_Z);

			int a = 0;
		}
	}
}

void CPlayer::DrawRunFunc(float DeltaTime, float Rot)
{
	if (!m_JoomEnable)
	{
		if (!CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

			if (Rotation > 360)
			{
				Rotation -= 360;
			}

			else if (Rotation < 0)
			{
				Rotation += 360;
			}

			if (Rotation < 177 || Rotation > 183)
			{
				// 플레이어가 좌에서 우로 회전 전방
				if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
				}
				// 플레이어가 우에서 좌로 회전 전방
				if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
				}
			}
		}

		else
		{
			if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedIdle"))
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkStart");
			}

			if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkStart"))
			{
				int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

				if (Rotation > 360)
				{
					Rotation -= 360;
				}

				else if (Rotation < 0)
				{
					Rotation += 360;
				}

				if (Rotation < 177 || Rotation > 183)
				{
					// 플레이어가 좌에서 우로 회전 전방
					if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
					}
					// 플레이어가 우에서 좌로 회전 전방
					if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
					}
				}

				else if (Rot == 0 || Rot == 180)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

				else if (Rot == 90 || Rot == 270)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

				//m_Velocity += GetWorldAxis(AXIS_Z) * m_PlayerInfo->Speed * DeltaTime;

				if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
					AddWorldPos(GetWorldAxis(AXIS_Z) * m_PlayerInfo->Speed * DeltaTime);

				else
					AddWorldPos(m_SlidingVec * m_PlayerInfo->Speed * DeltaTime);
			}

			if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkEnd") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkStart") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedWalkAndSheathe") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedEvadeToDrawedWalk") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargedShotIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHChargedShotIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargedShotIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHFullChargedShotIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHQuickShot") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHQuickShot") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHPowerShot") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHPowerShot") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedEvade") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedEvade") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShotStart") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShotStart") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDragonShot") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDragonShot") &&
				CheckAnimationFunc(false, "BHChargingFrontStep") &&
				CheckAnimationFunc(false, "BHChargingBackStep") &&
				CheckAnimationFunc(false, "BHChargingLeftStep") &&
				CheckAnimationFunc(false, "BHChargingRightStep") &&
				CheckAnimationFunc(false, "BHChargingFrontStepShot") &&
				CheckAnimationFunc(false, "BHChargingBackStepShot") &&
				CheckAnimationFunc(false, "BHChargingLeftStepShot") &&
				CheckAnimationFunc(false, "BHChargingRightStepShot") &&
				CheckAnimationFunc(false, "BHCoating") &&
				CheckAnimationFunc(false, "BHTrippingByFront") &&
				CheckAnimationFunc(false, "BHTrippingToIdle") &&
				CheckAnimationFunc(false, "BHRollByFrontStart") &&
				CheckAnimationFunc(false, "BHRollByFrontEnd") &&
				CheckAnimationFunc(false, "BHRollOverToIdle") &&
				CheckAnimationFunc(false, "BHPlugEarsStart") &&
				CheckAnimationFunc(false, "BHPlugEarsToIdle"))
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalk");

				int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

				if (Rotation > 360)
				{
					Rotation -= 360;
				}

				else if (Rotation < 0)
				{
					Rotation += 360;
				}

				if (Rotation < 177 || Rotation > 183)
				{
					// 플레이어가 좌에서 우로 회전 전방
					if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
					}
					// 플레이어가 우에서 좌로 회전 전방
					if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
					}
				}

				else if (Rot == 0 || Rot == 180)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

				else if (Rot == 90 || Rot == 270)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

				//m_Velocity += GetWorldAxis(AXIS_Z) * m_PlayerInfo->Speed * DeltaTime;

				if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
					AddWorldPos(GetWorldAxis(AXIS_Z) * m_PlayerInfo->Speed * DeltaTime);

				else
					AddWorldPos(m_SlidingVec * m_PlayerInfo->Speed * DeltaTime);
			}
		}
	}
}

void CPlayer::RunQuickFunc(float DeltaTime, float Rot)
{
	if (!m_JoomEnable)
	{
		if (!CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

			if (Rotation > 360)
			{
				Rotation -= 360;
			}

			else if (Rotation < 0)
			{
				Rotation += 360;
			}

			if (Rotation < 177 || Rotation > 183)
			{
				// 플레이어가 좌에서 우로 회전 전방
				if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
				}
				// 플레이어가 우에서 좌로 회전 전방
				if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
				}
			}
		}
		
		else
		{
			if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHIdle"))
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunStart");
			}

			if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart"))
			{
				int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

				if (Rotation > 360)
				{
					Rotation -= 360;
				}

				else if (Rotation < 0)
				{
					Rotation += 360;
				}

				if (Rotation < 177 || Rotation > 183)
				{
					// 플레이어가 좌에서 우로 회전 전방
					if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
					}
					// 플레이어가 우에서 좌로 회전 전방
					if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
					}
				}

				else if (Rot == 0 || Rot == 180)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

				else if (Rot == 90 || Rot == 270)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

				//m_Velocity += GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed - m_QuickMoveSpeed) * DeltaTime;

				if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
					AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed - m_QuickMoveSpeed) * DeltaTime);

				else
					AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed - m_QuickMoveSpeed) * DeltaTime);
			}

			if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunEnd") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHRunStart") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHIdle") &&
				CheckAnimationFunc(false, "BHTrippingByFront") &&
				CheckAnimationFunc(false, "BHTrippingToIdle") &&
				CheckAnimationFunc(false, "BHRollByFrontStart") &&
				CheckAnimationFunc(false, "BHRollByFrontEnd") &&
				CheckAnimationFunc(false, "BHRollOverToIdle") &&
				CheckAnimationFunc(false, "BHPlugEarsStart") &&
				CheckAnimationFunc(false, "BHPlugEarsToIdle"))
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRunQuick");

				int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

				if (Rotation > 360)
				{
					Rotation -= 360;
				}

				else if (Rotation < 0)
				{
					Rotation += 360;
				}

				if (Rotation < 177 || Rotation > 183)
				{
					// 플레이어가 좌에서 우로 회전 전방
					if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
					}
					// 플레이어가 우에서 좌로 회전 전방
					if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
					}
				}

				else if (Rot == 0 || Rot == 180)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

				else if (Rot == 90 || Rot == 270)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

				//m_Velocity += GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed - m_QuickMoveSpeed) * DeltaTime;

				if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
					AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed - m_QuickMoveSpeed) * DeltaTime);

				else
					AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed - m_QuickMoveSpeed) * DeltaTime);
			}
		}
	}
}

void CPlayer::ChangeBowFunc(const std::string& SocketName, const std::string& AnimationName)
{
	m_Mesh->DeleteChild(m_Bow);
	m_Mesh->AddChild(m_Bow, SocketName);
	((CAnimationMeshComponent*)m_Bow->GetRootComponent())->GetAnimationInstance()->ChangeAnimation(AnimationName);
}

void CPlayer::ChargingWalkFunc(float DeltaTime, float Rot)
{
	/*if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawedIdle"))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHDrawedWalkStart");
	}*/

	if (!m_JoomEnable)
	{
		if (!CSceneManager::GetInst()->GetScene()->GetNavigation3DManager()->GetMoveEnable(m_Mesh->GetWorldPos() + GetWorldAxis(AXIS_Z) * -1.5f))
		{
			int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

			if (Rotation > 360)
			{
				Rotation -= 360;
			}

			else if (Rotation < 0)
			{
				Rotation += 360;
			}

			if (Rotation < 177 || Rotation > 183)
			{
				// 플레이어가 좌에서 우로 회전 전방
				if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
				}
				// 플레이어가 우에서 좌로 회전 전방
				if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
				{
					m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
				}
			}
		}

		else
		{
			if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawnWalkToChargingStart") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargedShotIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargedShotIdle"))
			{
				int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

				if (Rotation > 360)
				{
					Rotation -= 360;
				}

				else if (Rotation < 0)
				{
					Rotation += 360;
				}

				if (Rotation < 178 || Rotation > 182)
				{
					// 플레이어가 좌에서 우로 회전 전방
					if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
					}
					// 플레이어가 우에서 좌로 회전 전방
					if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
					}
				}

				else if (Rot == 0 || Rot == 180)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

				else if (Rot == 90 || Rot == 270)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

				//m_Velocity += GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed + 5.f) * DeltaTime;

				if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
					AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed + 5.f) * DeltaTime);

				else
					AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed + 5.f) * DeltaTime);
			}

			if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawnWalkToChargingStart") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargingStartIdleFirst") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawnWalkToChargingStart") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargedShotIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargedShotIdle") &&
				!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWeaponToCharging") &&
				CheckAnimationFunc(false, "BHChargingFrontStep") &&
				CheckAnimationFunc(false, "BHChargingBackStep") &&
				CheckAnimationFunc(false, "BHChargingLeftStep") &&
				CheckAnimationFunc(false, "BHChargingRightStep") &&
				CheckAnimationFunc(false, "BHPlugEarsStart") &&
				CheckAnimationFunc(false, "BHPlugEarsToIdle"))
			{
				m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargingWalk");

				int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

				if (Rotation > 360)
				{
					Rotation -= 360;
				}

				else if (Rotation < 0)
				{
					Rotation += 360;
				}

				if (Rotation < 178 || Rotation > 182)
				{
					// 플레이어가 좌에서 우로 회전 전방
					if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);
					}
					// 플레이어가 우에서 좌로 회전 전방
					if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
					{
						m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
					}
				}

				else if (Rot == 0 || Rot == 180)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

				else if (Rot == 90 || Rot == 270)
					m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);

				//m_Velocity += GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed + 5.f) * DeltaTime;

				if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
					AddWorldPos(GetWorldAxis(AXIS_Z) * (m_PlayerInfo->Speed + 5.f) * DeltaTime);

				else
					AddWorldPos(m_SlidingVec * (m_PlayerInfo->Speed + 5.f) * DeltaTime);
			}
		}
	}

	else
	{

	}
}

void CPlayer::JoomRotationFunc(float DeltaTime, float Rot)
{
	if (m_DrawWeaponEnable && !m_EvadeFrontShotEnable && 
		!m_EvadeBackShotEnable && !m_EvadeLeftShotEnable && !m_EvadeRightShotEnable)
	{
		int Rotation = (int)(m_Mesh->GetWorldRot().y - m_ArmRotAccY + Rot);

		if (Rotation > 360)
		{
			Rotation -= 360;
		}

		else if (Rotation < 0)
		{
			Rotation += 360;
		}

		if (Rotation < 178 || Rotation > 182)
		{
			// 플레이어가 좌에서 우로 회전 전방
			if ((Rotation < 0 && Rotation > -180) || Rotation > 180)
			{
				m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * -m_RotationSpeed * DeltaTime);

			}
			// 플레이어가 우에서 좌로 회전 전방
			if ((Rotation >= 0 && Rotation <= 180) || Rotation <= -180)
			{
				m_Mesh->AddWorldRotation(GetWorldAxis(AXIS::AXIS_Y) * m_RotationSpeed * DeltaTime);
			}
		}

		else if (Rot == 0 || Rot == 180)
			m_Mesh->SetWorldRotationY(m_ArmRotAccY - 180.f + Rot);

		else if (Rot == 90 || Rot == 270)
			m_Mesh->SetWorldRotationY(m_ArmRotAccY + Rot);
	}
}

void CPlayer::JoomWalkFunc(float DeltaTime, const std::string& Name, float Speed1, float Speed2)
{
	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawnWalkToChargingStart") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargingStartIdleFirst") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHChargingStartIdleFirst") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawnWalkToChargingStart") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargedShotIdle") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHFullChargedShotIdle") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWeaponToCharging") &&
		CheckAnimationFunc(false, "BHDrawedWalkAndSheathe") &&
		CheckAnimationFunc(false, "BHQuickShot") &&
		CheckAnimationFunc(false, "BHPowerShot") &&
		CheckAnimationFunc(false, "BHChargedShotIdle") &&
		CheckAnimationFunc(false, "BHDrawedEvade") &&
		CheckAnimationFunc(false, "BHChargingFrontStep") &&
		CheckAnimationFunc(false, "BHChargingBackStep") &&
		CheckAnimationFunc(false, "BHChargingLeftStep") &&
		CheckAnimationFunc(false, "BHChargingRightStep") &&
		CheckAnimationFunc(false, "BHChargingFrontStepShot") &&
		CheckAnimationFunc(false, "BHChargingBackStepShot") &&
		CheckAnimationFunc(false, "BHChargingLeftStepShot") &&
		CheckAnimationFunc(false, "BHChargingRightStepShot") &&
		CheckAnimationFunc(false, "BHTrippingByFront") &&
		CheckAnimationFunc(false, "BHTrippingToIdle") &&
		CheckAnimationFunc(false, "BHRollByFrontStart") &&
		CheckAnimationFunc(false, "BHRollByFrontEnd") &&
		CheckAnimationFunc(false, "BHRollOverToIdle") &&
		CheckAnimationFunc(false, "BHDragonShotStart") &&
		CheckAnimationFunc(false, "BHDragonShot") &&
		CheckAnimationFunc(false, "BHPlugEarsStart") &&
		CheckAnimationFunc(false, "BHPlugEarsToIdle"))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation(Name);

		if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
		{
			AddWorldPos(GetWorldAxis(AXIS_Z) * Speed1 * DeltaTime);
			AddWorldPos(GetWorldAxis(AXIS_X) * Speed2 * DeltaTime);
		}

		else
			AddWorldPos(m_SlidingVec * m_PlayerInfo->Speed / 2.f * DeltaTime);
	}
}

void CPlayer::ChargingJoomFunc(float DeltaTime, const std::string& Name, float Speed1, float Speed2)
{
	if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawnWalkToChargingStart") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargedShotIdle") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargedShotIdle"))
	{
		if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
		{
			AddWorldPos(GetWorldAxis(AXIS_Z) * Speed1 * DeltaTime);
			AddWorldPos(GetWorldAxis(AXIS_X) * Speed2 * DeltaTime);
		}

		else
			AddWorldPos(m_SlidingVec * m_PlayerInfo->Speed / 2.f * DeltaTime);
	}
	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHDrawnWalkToChargingStart") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargingStartIdleFirst") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHChargingStartIdleFirst") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawnWalkToChargingStart") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHFullChargedShotIdle") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHFullChargedShotIdle") &&
		!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("BHChargedShotIdle") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWeaponToCharging") &&
		!m_Mesh->GetAnimationInstance()->CheckChangeAnimation("BHDrawedWalkAndSheathe") &&
		CheckAnimationFunc(false, "BHChargingFrontStep") &&
		CheckAnimationFunc(false, "BHChargingBackStep") &&
		CheckAnimationFunc(false, "BHChargingLeftStep") &&
		CheckAnimationFunc(false, "BHChargingRightStep") &&
		CheckAnimationFunc(false, "BHChargingFrontStepShot") &&
		CheckAnimationFunc(false, "BHChargingBackStepShot") &&
		CheckAnimationFunc(false, "BHChargingLeftStepShot") &&
		CheckAnimationFunc(false, "BHChargingRightStepShot") &&
		CheckAnimationFunc(false, "BHTrippingByFront") &&
		CheckAnimationFunc(false, "BHTrippingToIdle") &&
		CheckAnimationFunc(false, "BHRollByFrontStart") &&
		CheckAnimationFunc(false, "BHRollByFrontEnd") &&
		CheckAnimationFunc(false, "BHRollOverToIdle") &&
		CheckAnimationFunc(false, "BHPlugEarsStart") &&
		CheckAnimationFunc(false, "BHPlugEarsToIdle"))
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation(Name);

		if (m_SlidingVec.x == 0.f && m_SlidingVec.y == 0.f && m_SlidingVec.z == 0.f)
		{
			AddWorldPos(GetWorldAxis(AXIS_Z) * Speed1 * DeltaTime);
			AddWorldPos(GetWorldAxis(AXIS_X) * Speed2 * DeltaTime);
		}

		else
			AddWorldPos(m_SlidingVec * m_PlayerInfo->Speed / 2.f * DeltaTime);
	}
}
void CPlayer::ChargingShotDownFunc()
{
	if (m_ChargingCount == 0)
	{
		char Name[32] = {};

		while (true)
		{
			sprintf_s(Name, "Arrow%d", m_ArrowCount);

			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				++m_ArrowCount;
			}
			else
			{
				break;
			}
		}

		CArrow* Arrow = m_Scene->CreateGameObject<CArrow>(Name);
		Arrow->SetRelativeRotation(90.f, 30.f, 0.f);
		Arrow->SetArrowState(Arrow_State::Charging);
		Arrow->SetArrowCoatingState(m_CoatingState);
		m_Mesh->AddChild(Arrow, "BowRightHand");
		m_ReturnChargingCountTime = 1.8f;
		m_ReturnEnable = false;

	}

	else if (m_ChargingCount == 1)
	{
		for (int i = 0; i < m_ArrowCount + 2;)
		{
			char Name[64] = {};

			sprintf_s(Name, "Arrow%d", i);
			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				++m_ArrowCount;
				++i;

				continue;
			}

			Arrow = m_Scene->CreateGameObject<CArrow>(Name);
			Arrow->SetRelativeRotation(90.f, 30.f, 0.f);
			Arrow->SetArrowState(Arrow_State::Charging);
			Arrow->SetArrowCoatingState(m_CoatingState);
			m_Mesh->AddChild(Arrow, "BowRightHand");
			m_ReturnChargingCountTime = 1.8f;
			m_ReturnEnable = false;

			++i;
		}
	}

	else if (m_ChargingCount == 2)
	{
		for (int i = 0; i < m_ArrowCount + 3;)
		{
			char Name[64] = {};

			sprintf_s(Name, "Arrow%d", i);

			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				++m_ArrowCount;
				++i;

				continue;
			}
			Arrow = m_Scene->CreateGameObject<CArrow>(Name);
			Arrow->SetRelativeRotation(90.f, 30.f, 0.f);
			Arrow->SetArrowState(Arrow_State::Charging);
			Arrow->SetArrowCoatingState(m_CoatingState);
			m_Mesh->AddChild(Arrow, "BowRightHand");
			m_ReturnChargingCountTime = 1.8f;
			m_ReturnEnable = false;

			++i;
		}
	}
}

void CPlayer::ChargingShotUpFunc()
{
	if (m_ChargingCount == 0)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargedShotIdle");

		char Name[32] = {};

		sprintf_s(Name, "Arrow%d", m_ArrowCount);

		CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

		if (Arrow)
		{
			m_Mesh->DeleteChild(Arrow);
			Arrow->SetWorldPos(m_Mesh->GetWorldPos().x, m_Mesh->GetWorldPos().y + 7.4f, m_Mesh->GetWorldPos().z);
			Arrow->SetRelativeRotation(m_Mesh->GetWorldRot().x, m_Mesh->GetWorldRot().y + 1.f, m_Mesh->GetWorldRot().z);
			Arrow->SetArrowState(Arrow_State::Flying);
			Arrow->SetArrowAngle(-m_MouseRotAccX);
			switch (m_CoatingState)
			{
			case Coating_State::Normal:
			{
				//char EffectName[32] = {};
				//
				//sprintf_s(EffectName, "NormalEffect%d", m_ArrowCount);
				//
				//CNormalArrowBillboard* Normal = m_Scene->CreateGameObject<CNormalArrowBillboard>(EffectName);
				//Arrow->GetRootComponent()->AddChild(Normal);
			}
			break;
			case Coating_State::Strong:
				break;
			case Coating_State::Explosion:
				break;
			}
		}

		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		++m_ChargingCount;
		m_QuickShotCount = 2;
		m_ReturnEnable = true;
		CameraShakeFunc(0.2f, 0.03f);

		
	}
	else if (m_ChargingCount == 1)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHChargedShotIdle");
		for (int i = m_ArrowCount; i < m_ArrowCount + 2;)
		{
			int j = i - m_ArrowCount;

			char Name[64] = {};

			sprintf_s(Name, "Arrow%d", i);
			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				m_Mesh->DeleteChild(Arrow);
				Arrow->SetWorldPos(m_Mesh->GetWorldPos().x, m_Mesh->GetWorldPos().y + 7.4f, m_Mesh->GetWorldPos().z);
				Arrow->SetRelativeRotation(m_Mesh->GetWorldRot().x -1.f + i * 2.f, m_Mesh->GetWorldRot().y + 0.5f + j * 2.f, m_Mesh->GetWorldRot().z);
				Arrow->SetArrowState(Arrow_State::Flying);
				Arrow->SetArrowAngle(-m_MouseRotAccX);

				switch (m_CoatingState)
				{
				case Coating_State::Normal:
				{
					//char EffectName[32] = {};
					//
					//sprintf_s(EffectName, "NormalEffect%d", i);
					//
					//CNormalArrowBillboard* Normal = m_Scene->CreateGameObject<CNormalArrowBillboard>(EffectName);
					//Arrow->GetRootComponent()->AddChild(Normal);
				}
				break;
				case Coating_State::Strong:
					break;
				case Coating_State::Explosion:
					break;
				}

				++i;
			}
		}
		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_QuickShotCount = 2;
		m_ReturnEnable = true;
		CameraShakeFunc(0.2f, 0.03f);
	}

	else if (m_ChargingCount == 2)
	{
 		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHFullChargedShotIdle");
		for (int i = m_ArrowCount; i < m_ArrowCount + 3;)
		{
			int j = i - m_ArrowCount;
			char Name[64] = {};
			float RotXNumb = 3.f;

			if (j == 2)
				RotXNumb = 0.f;

			sprintf_s(Name, "Arrow%d", i);
			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				m_Mesh->DeleteChild(Arrow);
				// 3개의 화살이 삼각형모양으로 날라가도록 설정
				Arrow->SetWorldPos(m_Mesh->GetWorldPos().x, m_Mesh->GetWorldPos().y + 7.4f, m_Mesh->GetWorldPos().z);
				Arrow->SetRelativeRotation(m_Mesh->GetWorldRot().x - 1.5f + j * RotXNumb, m_Mesh->GetWorldRot().y + j * 1.5f, m_Mesh->GetWorldRot().z);
				Arrow->SetArrowState(Arrow_State::Flying);
				Arrow->SetArrowAngle(-m_MouseRotAccX);
				++i;
			}
		}

		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_QuickShotCount = 2;
		m_ReturnEnable = true;
		CameraShakeFunc(0.3f, 0.03f);
	}
}

void CPlayer::EvadeChargingShotUpFunc()
{
	if (m_ChargingCount == 0)
	{
		char Name[32] = {};

		sprintf_s(Name, "Arrow%d", m_ArrowCount);

		CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

		if (Arrow)
		{
			m_Mesh->DeleteChild(Arrow);
			Arrow->Destroy();
		}

		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_ReturnEnable = true;
	}
	else if (m_ChargingCount == 1)
	{
		for (int i = m_ArrowCount; i < m_ArrowCount + 2; ++i)
		{
			char Name[64] = {};

			sprintf_s(Name, "Arrow%d", i);
			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				m_Mesh->DeleteChild(Arrow);
				Arrow->Destroy();
			}
		}
		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_ReturnEnable = true;
	}

	else if (m_ChargingCount == 2)
	{
		for (int i = m_ArrowCount; i < m_ArrowCount + 3; ++i)
		{
			char Name[64] = {};
			float RotXNumb = 3.f;

			if (i == 2)
				RotXNumb = 0.f;

			sprintf_s(Name, "Arrow%d", i);
			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				m_Mesh->DeleteChild(Arrow);
				Arrow->SetDestroyEnabel(true);
			}
		}

		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_QuickShotCount = 2;
		m_ReturnEnable = true;
	}
}

void CPlayer::BowEffectVfxStartFunc()
{
	CBowVfx* BowVfx = m_Scene->CreateGameObject<CBowVfx>("BowVfx");
	BowVfx->SetWorldPos(m_Mesh->GetWorldPos().x, m_Mesh->GetWorldPos().y + 6.5f, m_Mesh->GetWorldPos().z + 7.f);
	m_Mesh->AddChild(BowVfx, "BowLeftHand");
	BowVfx->SetRelativeRotationX(90.f);
	BowVfx->SetRelativeRotationZ(160.f);
	BowVfx->SetRelativePos(0.f, 200.f, 0.f);
	BowVfx->SetRelativeScale(0.2f, 0.1f, 1.f);
}

void CPlayer::BowEffectVfxEndFunc()
{
	CBowVfx* BowVfx = (CBowVfx*)m_Scene->FindObject("BowVfx");

	if (BowVfx)
	{
		m_Mesh->DeleteChild(BowVfx);
		BowVfx->Destroy();
	}
}

bool CPlayer::CheckAnimationFunc(bool Enable, const std::string& Name)
{
	if (Enable)
	{
		if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation(Name) ||
			m_Mesh->GetAnimationInstance()->CheckChangeAnimation(Name))
		{
			return true;
		}
	}

	else
	{
		if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation(Name) &&
			!m_Mesh->GetAnimationInstance()->CheckChangeAnimation(Name))
		{
			return true;
		}
	}

	return false;
}

void CPlayer::HealFlowerInteractionFunc()
{
	if (m_HealEnable)
	{
		if (CheckAnimationFunc(true, "BHIdle"))
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHCarvingStart");
		}

		else
		{
			m_DrawWeaponTime = 7.f;
		}
	}
}

void CPlayer::MonsterCarvingFunc()
{
	if (m_MonsterCollision)
	{
		if (CheckAnimationFunc(true, "BHIdle"))
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("BHCarvingStart");
		}

		else
		{
			m_DrawWeaponTime = 7.f;
		}
	}
}

void CPlayer::StaminaFunc(float DeltaTime)
{
	bool ShiftEnable = CInput::GetInst()->GetShiftEnable();

	if (!ShiftEnable)
	{
		m_RunQuickFrontDown = false;
		m_RunQuickBackDown = false;
		m_RunQuickLeftDown = false;
		m_RunQuickRightDown = false;
	}

	if (!m_ChargingEnable && (m_RunQuickFrontDown || m_RunQuickBackDown ||
		m_RunQuickLeftDown || m_RunQuickRightDown))
	{
		m_PlayerInfo->Stamina -= DeltaTime * 3.f;

		if (m_PlayerInfo->Stamina < 0)
		{
			m_PlayerInfo->Stamina = 0;
		}
	}

	else if (m_ChargingEnable)
	{
		m_PlayerInfo->Stamina -= DeltaTime * 4.f;

		if (m_PlayerInfo->Stamina <= 0)
		{
			ChargingShotUpFunc();
			BowEffectVfxEndFunc();
			CResourceManager::GetInst()->SoundStop("ChargingLoop");
			m_PlayerInfo->Stamina = 0;
		}
	}

	else
	{
		m_PlayerInfo->Stamina += DeltaTime * 15.f;

		if (m_PlayerInfo->Stamina > m_PlayerInfo->MaxStamina)
			m_PlayerInfo->Stamina = m_PlayerInfo->MaxStamina;
	}
}

void CPlayer::CameraShakeFunc(float Strength, float Time)
{
	m_Camera->SetShakeStrength(Strength);

	m_Camera->SetShakeTime(Time);

	m_Camera->ShakeOn(Strength, Time);
}

void CPlayer::DestroyArrowFunc()
{
	if (m_ChargingCount == 0)
	{
		char Name[32] = {};

		sprintf_s(Name, "Arrow%d", m_ArrowCount);

		CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

		if (Arrow)
		{
			m_Mesh->DeleteChild(Arrow);
			Arrow->Destroy();
		}

		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_ReturnEnable = true;
	}
	else if (m_ChargingCount == 1)
	{
		for (int i = m_ArrowCount; i < m_ArrowCount + 2; ++i)
		{
			char Name[64] = {};

			sprintf_s(Name, "Arrow%d", i);
			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				m_Mesh->DeleteChild(Arrow);
				Arrow->Destroy();
			}
		}
		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_ReturnEnable = true;
	}

	else if (m_ChargingCount == 2)
	{
		for (int i = m_ArrowCount; i < m_ArrowCount + 3; ++i)
		{
			char Name[64] = {};
			float RotXNumb = 3.f;

			if (i == 2)
				RotXNumb = 0.f;

			sprintf_s(Name, "Arrow%d", i);
			CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

			if (Arrow)
			{
				m_Mesh->DeleteChild(Arrow);
				Arrow->SetDestroyEnabel(true);
			}
		}

		m_ShotEnable = true;
		m_ChargingEnable = false;
		m_ReturnChargingCountTime = 1.8f;
		//m_ReturnQuickTime = 0.7f;
		m_ArrowCount = 0;
		m_ChargingCount = 0;
		m_ReturnEnable = true;
	}

	if (m_QuickShotEnable)
	{
		if (m_QuickShotEnable)
		{
			m_QuickShotCount = 0;
			m_QuickShotEnable = false;
			ChangeBowFunc("BowLeftHand", "BowShot");

			for (int i = 0; i < 3; ++i)
			{
				char Name[64] = {};

				sprintf_s(Name, "QuickArrow%d", i);
				CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

				if (Arrow)
				{
					m_Mesh->DeleteChild(Arrow);
					Arrow->Destroy();
				}
			}
		}
	}

	if (m_PowerShotEnable)
	{
		if (m_QuickShotEnable)
		{
			m_QuickShotCount = 0;
			m_PowerShotEnable = false;
			ChangeBowFunc("BowLeftHand", "BowShot");

			for (int i = 0; i < 5; ++i)
			{
				char Name[64] = {};

				sprintf_s(Name, "QuickArrow%d", i);
				CArrow* Arrow = (CArrow*)m_Scene->FindObject(Name);

				if (Arrow)
				{
					m_Mesh->DeleteChild(Arrow);
					Arrow->Destroy();
				}
			}
		}
	}

	m_DragonShotEnable = false;
	CDragonArrow* Arrow = (CDragonArrow*)m_Scene->FindObject("DragonArrow");

	if (Arrow)
	{
		m_Mesh->DeleteChild(Arrow);
		Arrow->Destroy();
		ChangeBowFunc("BowLeftHand", "BowShot");
		CResourceManager::GetInst()->SoundStop("DragonCharge");
	}
	
}

void CPlayer::CollisionToTrippingFunc(float Damage)
{
	if (CheckAnimationFunc(false, "BHTrippingByFront") &&
		CheckAnimationFunc(false, "BHTrippingToIdle"))
	{
		m_PlayerInfo->HP -= Damage;

		m_TrippingEnable = true;
		m_EvadeFrontShotEnable = false;
		m_EvadeBackShotEnable = false;
		m_EvadeLeftShotEnable = false;
		m_EvadeRightShotEnable = false;
		m_EvadeChangeAttack = false;
		m_EvadeEnable = false;
		m_DrawWalkToSheatheEnable = false;

		if (m_DrawWeaponEnable)
		{
			m_Bow->SetRelativeRotation(90.f, -30.f, -120.f);
			m_Bow->SetWorldScale(0.7f, 1.5f, 1.2f);
			m_Bow->SetRimLightEnable(false);
			EvadeChargingShotUpFunc();
			BowEffectVfxEndFunc();
			DestroyArrowFunc();

			m_ChargingEnable = false;
			ChangeBowFunc("BowLeftHand", "BowShot");

			if (m_ChargingParticle)
			{
				m_ChargingParticle->Destroy();
			}
		}

		if (CheckAnimationFunc(true, "BHSheathe") || CheckAnimationFunc(true, "BHDrawedWalkAndSheathe"))
		{
			ChangeBowFunc("BackBow", "BowBack");
			m_Bow->SetRelativeRotation(0.f, 0.f, 90.f);
			m_Bow->SetWorldScale(0.7f, 1.f, 0.7f);

			m_DrawWeaponEnable = false;
		}

		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHTrippingByFront");

		CResourceManager::GetInst()->SoundStop("ChargingLoop");
	}
}

void CPlayer::CollisionToRollFunc(float Damage)
{
	if (CheckAnimationFunc(false, "BHRollByFrontStart") &&
		CheckAnimationFunc(false, "BHRollByFrontEnd") &&
		CheckAnimationFunc(false, "BHRollOverToIdle"))
	{
		m_PlayerInfo->HP -= Damage;

		m_RollEnable = true;
		m_EvadeFrontShotEnable = false;
		m_EvadeBackShotEnable = false;
		m_EvadeLeftShotEnable = false;
		m_EvadeRightShotEnable = false;
		m_EvadeChangeAttack = false;
		m_EvadeEnable = false;
		m_DrawWalkToSheatheEnable = false;

		if (m_DrawWeaponEnable)
		{
			m_Bow->SetRelativeRotation(90.f, 30.f, -90.f);
			m_Bow->SetWorldScale(1.5f, 1.2f, 1.5f);
			m_Bow->SetRimLightEnable(false);

			EvadeChargingShotUpFunc();
			BowEffectVfxEndFunc();
			DestroyArrowFunc();

			m_ChargingEnable = false;
			ChangeBowFunc("BowLeftHand", "BowShot");

			if (m_ChargingParticle)
				m_ChargingParticle->Destroy();

			
		}

		if (CheckAnimationFunc(true, "BHSheathe") || CheckAnimationFunc(true, "BHDrawedWalkAndSheathe"))
		{
			ChangeBowFunc("BackBow", "BowBack");
			m_Bow->SetRelativeRotation(0.f, 0.f, 90.f);
			m_Bow->SetWorldScale(0.7f, 1.f, 0.7f);

			m_DrawWeaponEnable = false;
		}



		m_Mesh->GetAnimationInstance()->ChangeAnimation("BHRollByFrontStart");

		CResourceManager::GetInst()->SoundStop("ChargingLoop");
	}
}

void CPlayer::CubeCollisionFunc(CGameObject* FieldObj, class CColliderBox3D* Box)
{
	Vector3 PlayerPos = m_Mesh->GetWorldPos();
	Vector3 PlayerDir = m_Mesh->GetWorldAxis(AXIS_Z);
	//PlayerDir *= -1.f;

	if (FieldObj->GetRootComponent()->GetTransformState() == Transform_State::None)
	{
		/*if (((int)Box->GetInfo().Length.x == (int)Box->GetInfo().Length.y) &&
			((int)Box->GetInfo().Length.y == (int)Box->GetInfo().Length.z))
			PlayerPos.y += Box->GetInfo().Length.x;*/
	}

	PlayerPos.y += 1.f;

	std::vector<CollisionBoxInfo>	vecInfo;

	CollisionBoxInfo Info = {};

	for (int i = 0; i < 8; ++i)
	{
		float Dist = (PlayerPos.Distance(Box->GetInfo().Pos[i]));
		Info.Dist = Dist;
		Info.Numb = i;

		vecInfo.push_back(Info);
	}

	std::sort(vecInfo.begin(), vecInfo.end(), SortPos);

	if (vecInfo[0].Numb == 0 || vecInfo[0].Numb == 1 ||
		vecInfo[0].Numb == 2 || vecInfo[0].Numb == 3)
	{
		if (vecInfo[1].Numb == 0 || vecInfo[1].Numb == 1 ||
			vecInfo[1].Numb == 2 || vecInfo[1].Numb == 3)
		{
			if (vecInfo[2].Numb == 0 || vecInfo[2].Numb == 1 ||
				vecInfo[2].Numb == 2 || vecInfo[2].Numb == 3)
			{
				if (vecInfo[3].Numb == 0 || vecInfo[3].Numb == 1 ||
					vecInfo[3].Numb == 2 || vecInfo[3].Numb == 3)
				{
					float PlayerAngle = PlayerDir.Angle(Box->GetInfo().NearNormal);
					if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
					{
						float PDotN = PlayerDir.Dot(Box->GetInfo().NearNormal);
						m_SlidingVec = PlayerDir - Box->GetInfo().NearNormal * PDotN;
					}
					else
					{
						m_SlidingVec = Vector3(0.f, 0.f, 0.f);
					}
				}
			}
		}
	}

	if (vecInfo[0].Numb == 4 || vecInfo[0].Numb == 5 ||
		vecInfo[0].Numb == 6 || vecInfo[0].Numb == 7)
	{
		if (vecInfo[1].Numb == 4 || vecInfo[1].Numb == 5 ||
			vecInfo[1].Numb == 6 || vecInfo[1].Numb == 7)
		{
			if (vecInfo[2].Numb == 4 || vecInfo[2].Numb == 5 ||
				vecInfo[2].Numb == 6 || vecInfo[2].Numb == 7)
			{
				if (vecInfo[3].Numb == 4 || vecInfo[3].Numb == 5 ||
					vecInfo[3].Numb == 6 || vecInfo[3].Numb == 7)
				{
					float PlayerAngle = PlayerDir.Angle(Box->GetInfo().FarNormal);
					if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
					{
						float PDotN = PlayerDir.Dot(Box->GetInfo().FarNormal);
						m_SlidingVec = PlayerDir - Box->GetInfo().FarNormal * PDotN;
					}
					else
					{
						m_SlidingVec = Vector3(0.f, 0.f, 0.f);
					}
				}
			}
		}
	}

	if (vecInfo[0].Numb == 1 || vecInfo[0].Numb == 5 ||
		vecInfo[0].Numb == 3 || vecInfo[0].Numb == 7)
	{
		if (vecInfo[1].Numb == 1 || vecInfo[1].Numb == 5 ||
			vecInfo[1].Numb == 3 || vecInfo[1].Numb == 7)
		{
			if (vecInfo[2].Numb == 1 || vecInfo[2].Numb == 5 ||
				vecInfo[2].Numb == 3 || vecInfo[2].Numb == 7)
			{
				if (vecInfo[3].Numb == 1 || vecInfo[3].Numb == 5 ||
					vecInfo[3].Numb == 3 || vecInfo[3].Numb == 7)
				{
					float PlayerAngle = PlayerDir.Angle(Box->GetInfo().RightNormal);
					if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
					{
						float PDotN = PlayerDir.Dot(Box->GetInfo().RightNormal);
						m_SlidingVec = PlayerDir - Box->GetInfo().RightNormal * PDotN;
					}
					else
					{
						m_SlidingVec = Vector3(0.f, 0.f, 0.f);
					}
				}
			}
		}
	}

	if (vecInfo[0].Numb == 4 || vecInfo[0].Numb == 0 ||
		vecInfo[0].Numb == 2 || vecInfo[0].Numb == 6)
	{
		if (vecInfo[1].Numb == 4 || vecInfo[1].Numb == 0 ||
			vecInfo[1].Numb == 2 || vecInfo[1].Numb == 6)
		{
			if (vecInfo[2].Numb == 4 || vecInfo[2].Numb == 0 ||
				vecInfo[2].Numb == 2 || vecInfo[2].Numb == 6)
			{
				if (vecInfo[3].Numb == 4 || vecInfo[3].Numb == 0 ||
					vecInfo[3].Numb == 2 || vecInfo[3].Numb == 6)
				{
					float PlayerAngle = PlayerDir.Angle(Box->GetInfo().LeftNormal);
					if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
					{
						float PDotN = PlayerDir.Dot(Box->GetInfo().LeftNormal);
						m_SlidingVec = PlayerDir - Box->GetInfo().LeftNormal * PDotN;
					}
					else
					{
						m_SlidingVec = Vector3(0.f, 0.f, 0.f);
					}
				}
			}
		}
	}

	if (vecInfo[0].Numb == 4 || vecInfo[0].Numb == 5 ||
		vecInfo[0].Numb == 0 || vecInfo[0].Numb == 1)
	{
		if (vecInfo[1].Numb == 4 || vecInfo[1].Numb == 5 ||
			vecInfo[1].Numb == 0 || vecInfo[1].Numb == 1)
		{
			if (vecInfo[2].Numb == 4 || vecInfo[2].Numb == 5 ||
				vecInfo[2].Numb == 0 || vecInfo[2].Numb == 1)
			{
				if (vecInfo[3].Numb == 4 || vecInfo[3].Numb == 5 ||
					vecInfo[3].Numb == 0 || vecInfo[3].Numb == 1)
				{
					float PlayerAngle = PlayerDir.Angle(Box->GetInfo().TopNormal);
					if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
					{
						float PDotN = PlayerDir.Dot(Box->GetInfo().TopNormal);
						m_SlidingVec = PlayerDir - Box->GetInfo().TopNormal * PDotN;
					}
					else
					{
						m_SlidingVec = Vector3(0.f, 0.f, 0.f);
					}
				}
			}
		}
	}

	if (vecInfo[0].Numb == 6 || vecInfo[0].Numb == 7 ||
		vecInfo[0].Numb == 2 || vecInfo[0].Numb == 3)
	{
		if (vecInfo[1].Numb == 6 || vecInfo[1].Numb == 7 ||
			vecInfo[1].Numb == 2 || vecInfo[1].Numb == 3)
		{
			if (vecInfo[2].Numb == 6 || vecInfo[2].Numb == 7 ||
				vecInfo[2].Numb == 2 || vecInfo[2].Numb == 3)
			{
				if (vecInfo[3].Numb == 6 || vecInfo[3].Numb == 7 ||
					vecInfo[3].Numb == 2 || vecInfo[3].Numb == 3)
				{
					float PlayerAngle = PlayerDir.Angle(Box->GetInfo().BottomNormal);
					if ((PlayerAngle < 90.f) && (PlayerAngle > -90.f))
					{
						float PDotN = PlayerDir.Dot(Box->GetInfo().BottomNormal);
						m_SlidingVec = PlayerDir - Box->GetInfo().BottomNormal * PDotN;
					}
					else
					{
						m_SlidingVec = Vector3(0.f, 0.f, 0.f);
					}
				}
			}
		}
	}
}

void CPlayer::CuboidCollisionFunc(CGameObject* FieldObj, class CColliderBox3D* Box, float DeltaTime)
{
	Vector3 PlayerPos = m_Mesh->GetWorldPos();
	Vector3 PlayerDir = m_Mesh->GetWorldAxis(AXIS_Z) * -1.f;
	//PlayerDir *= -1.f;
	Vector3 AxisDir = m_Mesh->GetWorldAxis(AXIS_Z);

	if (((FieldObj->GetWorldRot().x <= -89.f) && (FieldObj->GetWorldRot().x >= -91.f))
		|| ((FieldObj->GetWorldRot().x >= 269.f) && (FieldObj->GetWorldRot().x <= 271.f)))
	{
		if ((PlayerDir.z > 0.f) && (Box->GetInfo().Pos[0].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[1].x > PlayerPos.x) && (PlayerPos.z < Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				//Vector3 AxisDir = m_Mesh->GetWorldAxis(AXIS_Z);
				float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if ((PlayerDir.z < 0.f) && (Box->GetInfo().Pos[2].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[3].x > PlayerPos.x) && (PlayerPos.z > Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if ((PlayerDir.x > 0.f) && (Box->GetInfo().Pos[0].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[2].z > PlayerPos.z) && (PlayerPos.x < Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if ((PlayerDir.x < 0.f) && (Box->GetInfo().Pos[1].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[3].z > PlayerPos.z) && (PlayerPos.x > Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}

	}
	else if (((FieldObj->GetWorldRot().x >= 89.f) && (FieldObj->GetWorldRot().x <= 91.f))
		|| ((FieldObj->GetWorldRot().x <= -269.f) && (FieldObj->GetWorldRot().x >= -271.f)))
	{
		if ((PlayerDir.z > 0.f) && (Box->GetInfo().Pos[2].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[3].x > PlayerPos.x) && (PlayerPos.z < Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if ((PlayerDir.z < 0.f) && (Box->GetInfo().Pos[0].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[1].x > PlayerPos.x) && (PlayerPos.z > Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if ((PlayerDir.x > 0.f) && (Box->GetInfo().Pos[2].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[0].z > PlayerPos.z) && (PlayerPos.x < Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}

		else if ((PlayerDir.x < 0.f) && (Box->GetInfo().Pos[2].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[0].z > PlayerPos.z) && (PlayerPos.x > Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}
	}
	else if (FieldObj->GetWorldRot().x == 0.f || FieldObj->GetWorldRot().x == 360.f)
	{
		if ((PlayerDir.z > 0.f) && (Box->GetInfo().Pos[2].x - 0.1f < PlayerPos.x) &&
			(Box->GetInfo().Pos[3].x + 0.1f > PlayerPos.x) && (PlayerPos.z < Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.z < 0.f) && (Box->GetInfo().Pos[6].x - 0.1f < PlayerPos.x) &&
			(Box->GetInfo().Pos[7].x + 0.1f > PlayerPos.x) && (PlayerPos.z > Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x > 0.f) && (Box->GetInfo().Pos[2].z - 0.1f < PlayerPos.z) &&
			(Box->GetInfo().Pos[6].z + 0.1f > PlayerPos.z) && (PlayerPos.x < Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x < 0.f) && (Box->GetInfo().Pos[3].z - 0.1f < PlayerPos.z) &&
			(Box->GetInfo().Pos[7].z + 0.1f > PlayerPos.z) && (PlayerPos.x > Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}

	}

	else if (((FieldObj->GetWorldRot().z <= -89.f) && (FieldObj->GetWorldRot().z >= -91.f))
		|| ((FieldObj->GetWorldRot().z >= 269.f) && (FieldObj->GetWorldRot().z <= 271.f)))
	{
		if ((PlayerDir.z > 0.f) && (Box->GetInfo().Pos[0].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[2].x > PlayerPos.x) && (PlayerPos.z < Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.z < 0.f) && (Box->GetInfo().Pos[0].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[2].x > PlayerPos.x) && (PlayerPos.z > Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x > 0.f) && (Box->GetInfo().Pos[0].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[4].z > PlayerPos.z) && (PlayerPos.x < Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x < 0.f) && (Box->GetInfo().Pos[0].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[4].z > PlayerPos.z) && (PlayerPos.x > Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}
	}

	else if (((FieldObj->GetWorldRot().z >= 89.f) && (FieldObj->GetWorldRot().z <= 91.f))
		|| ((FieldObj->GetWorldRot().z <= -269.f) && (FieldObj->GetWorldRot().z >= -271.f)))
	{
		if ((PlayerDir.z > 0.f) && (Box->GetInfo().Pos[3].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[1].x > PlayerPos.x) && (PlayerPos.z < Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.z < 0.f) && (Box->GetInfo().Pos[3].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[1].x > PlayerPos.x) && (PlayerPos.z > Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x > 0.f) && (Box->GetInfo().Pos[3].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[7].z > PlayerPos.z) && (PlayerPos.x < Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().BottomNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().BottomNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().BottomNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x < 0.f) && (Box->GetInfo().Pos[3].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[7].z > PlayerPos.z) && (PlayerPos.x > Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().TopNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().TopNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().TopNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}
	}

	else if (((FieldObj->GetWorldRot().y >= 89.f) && (FieldObj->GetWorldRot().y <= 91.f))
		|| ((FieldObj->GetWorldRot().y <= -269.f) && (FieldObj->GetWorldRot().y >= -271.f)))
	{
		if ((PlayerDir.z > 0.f) && (Box->GetInfo().Pos[7].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[3].x > PlayerPos.x) && (PlayerPos.z < Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.z < 0.f) && (Box->GetInfo().Pos[7].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[3].x > PlayerPos.x) && (PlayerPos.z > Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x > 0.f) && (Box->GetInfo().Pos[2].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[3].z > PlayerPos.z) && (PlayerPos.x < Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x < 0.f) && (Box->GetInfo().Pos[2].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[3].z > PlayerPos.z) && (PlayerPos.x > Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}
	}

	else if (((FieldObj->GetWorldRot().y <= -89.f) && (FieldObj->GetWorldRot().y >= -91.f))
		|| ((FieldObj->GetWorldRot().y >= 269.f) && (FieldObj->GetWorldRot().y <= 271.f)))
	{
		if ((PlayerDir.z > 0.f) && (Box->GetInfo().Pos[2].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[6].x > PlayerPos.x) && (PlayerPos.z < Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().RightNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().RightNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().RightNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.z < 0.f) && (Box->GetInfo().Pos[2].x < PlayerPos.x) &&
			(Box->GetInfo().Pos[6].x > PlayerPos.x) && (PlayerPos.z > Box->GetInfo().Center.z))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().LeftNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().LeftNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().LeftNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x > 0.f) && (Box->GetInfo().Pos[7].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[6].z > PlayerPos.z) && (PlayerPos.x < Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().NearNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().NearNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().NearNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else if ((PlayerDir.x < 0.f) && (Box->GetInfo().Pos[7].z < PlayerPos.z) &&
			(Box->GetInfo().Pos[6].z > PlayerPos.z) && (PlayerPos.x > Box->GetInfo().Center.x))
		{
			int PlayerAngle = (int)AxisDir.Angle(Box->GetInfo().FarNormal);
			if ((PlayerAngle <= 90) && (PlayerAngle >= -90))
			{
				float PDotN = AxisDir.Dot(Box->GetInfo().FarNormal);
				m_SlidingVec = AxisDir - Box->GetInfo().FarNormal * PDotN;
			}
			else
			{
				m_SlidingVec = Vector3(0.f, 0.f, 0.f);
			}
		}
		else
		{
			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}
	}
	else
	{
		Vector3 Dir = Vector3(m_Mesh->GetWorldPos() - FieldObj->GetWorldPos());
		Dir.Normalize();
		Dir *= -1;
		m_Mesh->AddWorldPos(Dir * m_PlayerInfo->Speed * DeltaTime * 2.f);
	}
}

void CPlayer::DeleteObjName(const std::string& ObjName)
{
	auto iter = m_vecFieldObjName.begin();
	auto iterEnd = m_vecFieldObjName.end();

	int Count = static_cast<int>(m_vecFieldObjName.size());

	for (int i = 0; i < Count; ++i, ++iter)
	{
		if (m_vecFieldObjName[i] == ObjName)
		{
			m_vecFieldObjName.erase(iter);
			return;
		}
	}
}

void CPlayer::DeleteBoxName(const char* BoxName)
{
	auto iter = m_vecFieldBoxName.begin();
	auto iterEnd = m_vecFieldBoxName.end(); 

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == BoxName)
		{
			m_vecFieldBoxName.erase(iter);
			return;
		}
	}
}

void CPlayer::CollisionBegin(const CollisionResult& Result)
{
	if (Result.Dest->GetGameObject()->CheckType<CHealFlower>())
	{
		strcpy_s(m_HealObjName, Result.Dest->GetGameObject()->GetName().c_str());

		m_HealEnable = true;
	}

	if (Result.Dest->GetGameObject()->CheckType<CBarnos>())
	{
		if (Result.Dest->GetName() == "ColliderHead")
		{
			CBarnos* Barnos = (CBarnos*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

			if (Barnos)
			{
				if (Barnos->GetIsAttacking())
				{
					CollisionToTrippingFunc(10.f);
				}
			}
		}
		if (Result.Dest->GetName() == "ColliderCarving")
		{
			strcpy_s(m_BarnosName, Result.Dest->GetGameObject()->GetName().c_str());

			m_ColliderObj = m_Scene->FindObject(m_BarnosName);

			m_MonsterCollision = true;

			m_CarvingWindow = m_Scene->GetViewport()->FindWidgetWindow<CCarvingWindow>("CarvingWindow");

			if (!m_CarvingWindow)
			{
				m_CarvingWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingWindow>("CarvingWindow");
				m_CarvingWindow->SetMonsterName(Monster_Name::Barnos);
			}

			else
			{
				m_CarvingWindow->SetVisibility(true);
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CJagras>())
	{
		if (Result.Dest->GetName() == "ColliderHeadAttack")
		{
			CJagras* Jagras = (CJagras*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

			if (Jagras && Jagras->GetIsAttacking())
			{
				CollisionToTrippingFunc(15.f);
			}
		}
		if (Result.Dest->GetName() == "ColliderCarving")
		{
			strcpy_s(m_JagrasName, Result.Dest->GetGameObject()->GetName().c_str());

			m_ColliderObj = m_Scene->FindObject(m_JagrasName);

			m_MonsterCollision = true;

			m_CarvingWindow = m_Scene->GetViewport()->FindWidgetWindow<CCarvingWindow>("CarvingWindow");

			if (!m_CarvingWindow)
			{
				m_CarvingWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingWindow>("CarvingWindow");
				m_CarvingWindow->SetMonsterName(Monster_Name::Jagras);
			}

			else
			{
				m_CarvingWindow->SetVisibility(true);
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CKestodon>())
	{
		if (Result.Dest->GetName() == "ColliderHeadAttack")
		{
			CKestodon* Kestodon = (CKestodon*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

			if (Kestodon)
			{
				if (Kestodon->GetIsAttacking())
				{
					CollisionToRollFunc(10.f);
				}
			}
		}
		if (Result.Dest->GetName() == "ColliderCarving")
		{
			strcpy_s(m_KestodonName, Result.Dest->GetGameObject()->GetName().c_str());

			m_ColliderObj = m_Scene->FindObject(m_KestodonName);

			m_MonsterCollision = true;

			m_CarvingWindow = m_Scene->GetViewport()->FindWidgetWindow<CCarvingWindow>("CarvingWindow");

			if (!m_CarvingWindow)
			{
				m_CarvingWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingWindow>("CarvingWindow");
				m_CarvingWindow->SetMonsterName(Monster_Name::Kestodon);
			}

			else
			{
				m_CarvingWindow->SetVisibility(true);
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CVespoid>())
	{
		if (Result.Dest->GetName() == "ColliderAttack")
		{
			CVespoid* Vespoid = (CVespoid*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

			if (Vespoid)
			{
				if (Vespoid->GetIsAttacking())
				{
					CollisionToTrippingFunc(10.f);
				}
			}
		}
		if (Result.Dest->GetName() == "ColliderCarving")
		{
			strcpy_s(m_VespoidName, Result.Dest->GetGameObject()->GetName().c_str());

			m_ColliderObj = m_Scene->FindObject(m_VespoidName);

			m_MonsterCollision = true;

			m_CarvingWindow = m_Scene->GetViewport()->FindWidgetWindow<CCarvingWindow>("CarvingWindow");

			if (!m_CarvingWindow)
			{
				m_CarvingWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingWindow>("CarvingWindow");
				m_CarvingWindow->SetMonsterName(Monster_Name::Vespoid);
			}

			else
			{
				m_CarvingWindow->SetVisibility(true);
			}
		}
	}
	// 보스
	if (Result.Dest->GetGameObject()->CheckType<CAnjanath>())
	{
		//strcpy_s(m_AnjanthName, Result.Dest->GetGameObject()->GetName().c_str());

		CAnjanath* Anjanath = (CAnjanath*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

		if (Result.Dest->GetName() == "ChargeCollider")
		{
			if (Anjanath)
			{
				if (Anjanath->IsChargeAttacking())
				{
					CollisionToRollFunc(25.f);
				}
			}
		}

		if (Result.Dest->GetName() == "BiteCollider")
		{
			if (Anjanath)
			{
				if (Anjanath->IsBiteAttacking())
				{
					CollisionToRollFunc(25.f);
				}
			}
		}

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			strcpy_s(m_AnjanthName, Result.Dest->GetGameObject()->GetName().c_str());

			m_ColliderObj = m_Scene->FindObject(m_AnjanthName);

			m_MonsterCollision = true;

			m_CarvingWindow = m_Scene->GetViewport()->FindWidgetWindow<CCarvingWindow>("CarvingWindow");

			if (!m_CarvingWindow)
			{
				m_CarvingWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingWindow>("CarvingWindow");
				m_CarvingWindow->SetMonsterName(Monster_Name::Anjanath);
			}

			else
			{
				m_CarvingWindow->SetVisibility(true);
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CRathalos>())
	{
		//strcpy_s(m_RathalosName, Result.Dest->GetGameObject()->GetName().c_str());

		if (Result.Dest->GetName() == "BiteCollider")
		{
			CRathalos* Rathalos = (CRathalos*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

			if (Rathalos)
			{
				if (Rathalos->IsAttacking())
				{
					CollisionToRollFunc(25.f);
				}
			}
		}

		if (Result.Dest->GetName() == "ChargeCollider")
		{
			CRathalos* Rathalos = (CRathalos*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

			if (Rathalos)
			{
				if (Rathalos->IsAttacking())
				{
					CollisionToRollFunc(25.f);
				}
			}
		}

		if (Result.Dest->GetName() == "TailAttackCollider")
		{
			CRathalos* Rathalos = (CRathalos*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName());

			if (Rathalos)
			{
				if (Rathalos->IsAttacking())
				{
					CollisionToRollFunc(25.f);
				}
			}
		}

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			strcpy_s(m_RathalosName, Result.Dest->GetGameObject()->GetName().c_str());

			m_ColliderObj = m_Scene->FindObject(m_RathalosName);

			m_MonsterCollision = true;

			m_CarvingWindow = m_Scene->GetViewport()->FindWidgetWindow<CCarvingWindow>("CarvingWindow");

			if (!m_CarvingWindow)
			{
				m_CarvingWindow = m_Scene->GetViewport()->CreateWidgetWindow<CCarvingWindow>("CarvingWindow");
				m_CarvingWindow->SetMonsterName(Monster_Name::Rathalos);
			}

			else
			{
				m_CarvingWindow->SetVisibility(true);
			}
		}
	}



	if (Result.Dest->GetGameObject()->CheckType<CFlameEffect>())
	{
		CHitBreathEffect* HitEffect = (CHitBreathEffect*)m_Scene->FindObject("HitBreathEffect");

		if (!HitEffect)
		{
			HitEffect = m_Scene->CreateGameObject<CHitBreathEffect>("HitBreathEffect");

			m_IsHitBreath = true;
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CTownSign>())
	{
		m_IsSignCollision = true;
	}

	//if (Result.Dest->GetCollisionProfile()->Name == "FieldObj")
	//{
	//	m_IsFieldCollision = true;

	//	strcpy_s(m_FieldObjName, Result.Dest->GetGameObject()->GetName().c_str());
	//	//strcpy_s(m_FieldBoxName, Result.Dest->GetName().c_str());

	//	m_vecFieldObjName.push_back(m_FieldObjName);
	//	//m_vecFieldBoxName.push_back(m_FieldBoxName);
	//}
}

void CPlayer::CollisionEnd(const CollisionResult& Result)
{
	m_ColliderObj = nullptr;

	if (Result.Dest->GetGameObject()->CheckType<CHealFlower>())
	{
		m_HealEnable = false;
	}

	if (Result.Dest->GetGameObject()->CheckType<CBarnos>())
	{
		memset(m_BarnosName, 0, sizeof(char) * 64);

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			if (m_CarvingWindow)
			{
				m_CarvingWindow->FadeDestroy();
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CJagras>())
	{
		memset(m_JagrasName, 0, sizeof(char) * 64);

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			if (m_CarvingWindow)
			{
				m_CarvingWindow->FadeDestroy();
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CKestodon>())
	{
		memset(m_KestodonName, 0, sizeof(char) * 64);

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			if (m_CarvingWindow)
			{
				m_CarvingWindow->FadeDestroy();
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CVespoid>())
	{
		memset(m_VespoidName, 0, sizeof(char) * 64);

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			if (m_CarvingWindow)
			{
				m_CarvingWindow->FadeDestroy();
			}
		}
	}

	// 보스
	if (Result.Dest->GetGameObject()->CheckType<CAnjanath>())
	{
		memset(m_AnjanthName, 0, sizeof(char) * 64);

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			if (m_CarvingWindow)
			{
				m_CarvingWindow->FadeDestroy();
			}
		}
	}

	if (Result.Dest->GetGameObject()->CheckType<CRathalos>())
	{
		memset(m_RathalosName, 0, sizeof(char) * 64);

		if (Result.Dest->GetName() == "ColliderCarving")
		{
			if (m_CarvingWindow)
			{
				m_CarvingWindow->FadeDestroy();
			}
		}
	}


	if (Result.Dest->GetGameObject()->CheckType<CTownSign>())
	{
		m_IsSignCollision = false;
	}
	//if (Result.Dest->GetCollisionProfile()->Name == "FieldObj")
	//{
	//	DeleteObjName(Result.Dest->GetGameObject()->GetName());

	//	int Count = static_cast<int>(m_vecFieldObjName.size());

	//	if (Count == 0)
	//	{
	//		m_IsFieldCollision = false;

	//		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	//	}

	//	//char Name[32] = {};
	//	//memset(m_FieldObjName, 0, sizeof(char) * 32);
	//	//strcpy_s(Name, Result.Dest->GetName());

	//	//DeleteBoxName(Result.Dest->GetName().c_str());

	//	//m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	//}
}

void CPlayer::SlidingCollisionBegin(const CollisionResult& Result)
{
	if (Result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		m_IsFieldCollision = true;

		m_Obj = Result.Dest->GetGameObject();

		//char ObjName[32] = {};

		strcpy_s(m_FieldObjName, Result.Dest->GetGameObject()->GetName().c_str());
		//strcpy_s(m_FieldBoxName, Result.Dest->GetName().c_str());

		//m_vecFieldObjName.push_back(Result.Dest->GetGameObject()->GetName());
		//m_vecFieldBoxName.push_back(m_FieldBoxName);
	}
}

void CPlayer::SlidingCollisionEnd(const CollisionResult& Result)
{
	if (Result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		//DeleteObjName(Result.Dest->GetGameObject()->GetName());

		m_Obj = nullptr;

		//int Count = static_cast<int>(m_vecFieldObjName.size());

		m_IsFieldCollision = false;

		/*m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		if (Count == 0)
		{
			m_IsFieldCollision = false;

			m_SlidingVec = Vector3(0.f, 0.f, 0.f);
		}*/

		//char Name[32] = {};
		memset(m_FieldObjName, 0, sizeof(char) * 32);
		//strcpy_s(Name, Result.Dest->GetName());

		//DeleteBoxName(Result.Dest->GetName().c_str());

		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}

void CPlayer::QuestAcept()
{
	m_IsQuestAcept = true;

	CEngine::GetInst()->ShowUICursor(false);
}

bool CPlayer::SortPos(const CollisionBoxInfo& Begin, const CollisionBoxInfo& End)
{
	return Begin.Dist < End.Dist;
}


void CPlayer::FlightCallback(float DeltaTime)
{
	m_FlightMode = !m_FlightMode;

	CInput::GetInst()->ClearCallback();

	if (m_FlightMode)
	{
		CInput::GetInst()->SetKeyCallback<CPlayer>("FlightCamera", Key_State::KeyState_Down, this, &CPlayer::FlightCallback);

		m_Scene->CreateGameObject<CFlightCamera>("FlightCamera");

		m_Camera = nullptr;
	}

	else
	{
		SetKeyCallback();

		m_Camera = m_Scene->GetCameraManager()->GetCurrentCamera();

		m_Scene->FindObject("FlightCamera")->Destroy();

		m_Arm->AddChild(m_Camera);
	}
}

void CPlayer::MovePoint(float DeltaTime)
{
	Vector3 Point = m_Scene->GetNavigation3DManager()->GetPickingPos();

	Move(Point);
}

#include "Vespoid.h"
#include "VespoidAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "Collision/Collision.h"
#include "../ClientManager3D.h"

CVespoid::CVespoid()
{
	SetTypeID<CVespoid>();
	IdleTime = 0.f;
	MoveTime= 0.f;
	AttackTime= 0.f;
	StartAttackTime= 0.f;
	EndAttackTime= 0.f;

	attacktype = 0;
	MoveDist = 0.f;
	ChaseAccTime = 0.f;
	ChaseIdleTime = 0.f;

	HP = 150;

	pPlayer = nullptr;

	IsLegUp = false;

}

CVespoid::CVespoid(const CVespoid& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");

}

CVespoid::~CVespoid()
{
}

bool CVespoid::Init()
{


	


	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");
	

	ColliderUpperBody = CreateComponent<CColliderBox3D>("ColliderUpperBody");
	ColliderLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerBody");

	ColliderAttack = CreateComponent<CColliderBox3D>("ColliderAttack");


	ColliderUpperBody->Set3DExtent(2.0f, 1.0f, 2.0f);
	ColliderLowerBody->Set3DExtent(1.0f, 1.0f, 1.0f);
	
	ColliderAttack->Set3DExtent(0.5f, 1.5f, 0.5f);	

	ColliderUpperBody->SetCollisionProfile("Monster");
	ColliderLowerBody->SetCollisionProfile("Monster");
	
	ColliderAttack->SetCollisionProfile("MonsterAttack");

	ColliderUpperBody->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::OnCollisionBegin);
	ColliderUpperBody->AddCollisionCallback(Collision_State::End, this, &CVespoid::OnCollisionEnd);
	ColliderLowerBody->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::OnCollisionBegin);
	ColliderLowerBody->AddCollisionCallback(Collision_State::End, this, &CVespoid::OnCollisionEnd);
	
	ColliderAttack->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::AttackOnCollisionBegin);
	ColliderAttack->AddCollisionCallback(Collision_State::End, this, &CVespoid::AttackOnCollisionEnd);








	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_State = Transform_State::None;
	m_Mesh->SetMesh("VespoidMesh");
	m_Mesh->CreateAnimationInstance<CVespoidAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(10.f, 10.f, 10.f);
	m_Mesh->SetRelativeRotation(Vector3(250.f, 180.f, 180.f));

	m_Mesh->AddChild(ColliderUpperBody, "UpperBody");
	m_Mesh->AddChild(ColliderLowerBody, "LowerBody");	
	m_Mesh->AddChild(ColliderAttack, "Attack");

	
	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(4.0f, 4.0f, 4.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	ColliderSliding = CreateComponent<CColliderBox3D>("ColliderSliding");
	ColliderSliding->Set3DExtent(2.0f, 2.0f, 2.0f);
	ColliderSliding->SetOffset(0.0f, 2.0f, 0.0f);
	ColliderSliding->SetCollisionProfile("MonsterSliding");
	m_Mesh->AddChild(ColliderSliding);
	ColliderSliding->Enable(true);
	ColliderSliding->AddCollisionCallback(Collision_State::Begin, this, &CVespoid::SlidingOnCollisionBegin);
	ColliderSliding->AddCollisionCallback(Collision_State::End, this, &CVespoid::SlidingOnCollisionEnd);
	
	SetNotify();



	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CVespoid::IDLEStay, &CVespoid::IDLEStart, &CVespoid::IDLEEnd);
	FSM.CreateState("Move", this, &CVespoid::MOVEStay, &CVespoid::MOVEStart, &CVespoid::MOVEEnd);	
	FSM.CreateState("GetHit", this, &CVespoid::GETHITStay, &CVespoid::GETHITStart, &CVespoid::GETHITEnd);
	FSM.CreateState("Attack", this, &CVespoid::ATTACKStay, &CVespoid::ATTACKStart, &CVespoid::ATTACKEnd);
	FSM.CreateState("Death", this, &CVespoid::DEATHStay, &CVespoid::DEATHStart, &CVespoid::DEATHEnd);
	FSM.CreateState("Scream", this, &CVespoid::SCREAMStay, &CVespoid::SCREAMStart, &CVespoid::SCREAMEnd);
	FSM.CreateState("Chase", this, &CVespoid::CHASEStay, &CVespoid::CHASEStart, &CVespoid::CHASEEnd);
	FSM.CreateState("FadeOut", this, &CVespoid::FADEOUTStay, &CVespoid::FADEOUTStart, &CVespoid::FADEOUTEnd);

	
	CResourceManager::GetInst()->LoadSound("Vespoid", true, "VespoidWing" + std::to_string(VespoidCount), "Monster/Vespoid/wing.ogg", SOUND_PATH);
	WingSound = CResourceManager::GetInst()->FindSound("VespoidWing" + std::to_string(VespoidCount));
	
	++VespoidCount;


	
	
	this;

	return true;
}

void CVespoid::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
	//상태 변경
	FSM.ChangeState("Idle");
}

void CVespoid::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();

	if (Dist.Length() < 40.f && IsIdle && !IsDead)
	{
		CurScreamTime += DeltaTime;
	}

	if (ScreamThreshold < CurScreamTime && IsIdle)
	{
		FSM.ChangeState("Scream");
	}

	
	FSM.Update();//Update에서 매 프레임마다 fsm 상태 갱신
	
	if (!IsDead)
	{
		YPosCorrection();
	}

	if (IsOnFieldCol)
	{
		FieldCollision(DeltaTime);
		CheckStuck();
	}
	
}

void CVespoid::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);



	
}

CVespoid* CVespoid::Clone()
{
	return new CVespoid(*this);
}



Vector3 CVespoid::FindNextMovePoint()
{
	Vector3 DestVec;
	
	int rannum = rand() % 2;


	if (1 == rannum)
	{		
		DestVec.x = GetWorldPos().x - (rand() % 10 + 8);
	}
	else
	{
		DestVec.x = GetWorldPos().x + (rand() % 10 + 8);
	}

	if (1 == rannum)
	{		
		DestVec.z = (GetWorldPos().z) - (rand() % 10 + 8);
	}
	else
	{		
		DestVec.z = GetWorldPos().z + (rand() % 10 + 8);
	}


	//y값

	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec);

	if (1 == rannum)
	{
		DestVec.y = GetWorldPos().y + (rand() % 10);
	}
	else
	{		
		DestVec.y = GetWorldPos().y - (rand() % 10);
	}


	if (DestVec.y <= y + 6)
	{
		DestVec.y = y + 6;
	}


	MoveDist = Vector3(DestVec - GetWorldPos()).Length();



	return DestVec;

}

Vector3 CVespoid::FindPlayerAroundPos()
{
	Vector3 DestVec;

	int rannum = rand() % 2;

	if (1 == rannum)
	{
		DestVec.x = pPlayer->GetWorldPos().x - (rand() % 2 + 1);
	}
	else
	{
		DestVec.x = pPlayer->GetWorldPos().x + (rand() % 2 + 1);
	}




	if (1 == rannum)
	{		
		DestVec.z = (pPlayer->GetWorldPos().z) - (rand() % 2 + 1);
	}
	else
	{		
		DestVec.z = pPlayer->GetWorldPos().z + (rand() % 2 + 1);
	}

	DestVec.y = pPlayer->GetWorldPos().y + (rand() % 2)+2;

	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec);
	if (DestVec.y <= y + 6)
	{
		DestVec.y = y + 6;
	}

	MoveDist = Vector3(DestVec - GetWorldPos()).Length();

	return DestVec;
}

void CVespoid::YPosCorrection()
{
	Vector3 DestVec = GetWorldPos();
	DestVec.y = 0;
	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec) + 5;

	if (GetWorldPos().y <= y)
	{
		Vector3 t = GetWorldPos();
		t.y = y;
		SetWorldPos(t);
	}
}

void CVespoid::FieldCollision(float DeltaTime)
{
	Vector3 Dir = Vector3(pFieldObj->GetWorldPos() - GetWorldPos());
	Dir.Normalize();
	Dir *= -1;
	AddWorldPos(Dir * CurSpeed * DeltaTime);

}

void CVespoid::CheckStuck()
{
	float t1 = Vector3(DestMovePoint - pFieldObj->GetWorldPos()).Length();
	float t2 = (float)sqrt(pow(FieldColInfo.Length.x, 2) + pow(FieldColInfo.Length.y, 2) + pow(FieldColInfo.Length.z, 2));

	if (t1 < t2)
	{
		if (IsChase)
		{

			DestMovePoint = FindPlayerAroundPos();
			RotateTo(DestMovePoint);
		}
		else
		{

			DestMovePoint = FindNextMovePoint();
			RotateTo(DestMovePoint);

		}
	}
}



void CVespoid::SetNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidlegup", this, &CVespoid::LegUpEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidattack1", this, &CVespoid::ToIdleNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidattack2", this, &CVespoid::ToIdleNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoiddeath1", this, &CVespoid::Death1EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidscream", this, &CVespoid::ScreamEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CVespoid>("vespoidhit1", this, &CVespoid::GetHitEndNotify);
}

void CVespoid::LegUpEndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoidfly3");
}


void CVespoid::Death1EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("vespoiddeath2");
	AddWorldPos(Vector3(0, -1, 0));
}

void CVespoid::ToIdleNotify()
{
	FSM.ChangeState("Idle");
}

void CVespoid::ScreamEndNotify()
{
	FSM.ChangeState("Chase");
}

void CVespoid::GetHitEndNotify()
{
	if (IsIdle)
	{
		FSM.ChangeState("Scream");
	}
	else
	{
		FSM.ChangeState("Chase");
	}
}

void CVespoid::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetGameObject()->CheckType<CArrow>())
	{
		if (IsDead)
			return;

		if (HP <= 0)
		{
			FSM.ChangeState("Death");
		}
		else
		{
			if (AccDamage >= Threshold)
			{
				FSM.ChangeState("GetHit");
				AccDamage = 0.f;

				CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
			}
		}


	}
	if (result.Dest->GetGameObject()->CheckType<CDragonArrow>())
	{
		if (IsDead)
			return;

		CDragonArrow* dragonarrow = (CDragonArrow*)result.Dest->GetGameObject();

		if (2 != (int)dragonarrow->GetDragonArrowState())
			return;

		
		if (HP <= 0)
		{
			FSM.ChangeState("Death");
		}
		else
		{
			if (!IsStun)
			{
				FSM.ChangeState("GetHit");
			}
		}
	}
}

void CVespoid::OnCollisionEnd(const CollisionResult& result)
{
}

void CVespoid::AttackOnCollisionBegin(const CollisionResult& result)
{
	std::string t = result.Dest->GetGameObject()->GetName();
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		if (IsAttacking)
		{

		}
	}
}

void CVespoid::AttackOnCollisionEnd(const CollisionResult& result)
{
}

void CVespoid::SlidingOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		IsOnFieldCol = true;
		pFieldObj = result.Dest->GetGameObject();
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();
		strcpy_s(m_FieldObjName, result.Dest->GetGameObject()->GetName().c_str());

	}
}

void CVespoid::SlidingOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		pFieldObj = nullptr;
		IsOnFieldCol = false;
		memset(m_FieldObjName, 0, sizeof(char) * 32);
		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}



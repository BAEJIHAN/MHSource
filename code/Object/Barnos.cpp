#include "Barnos.h"
#include "BarnosAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "Resource/ResourceManager.h"
#include "Collision/Collision.h"

CBarnos::CBarnos()
{
	SetTypeID<CBarnos>();
	IdleTime = 0.f;
	MoveTime = 0.f;
	AttackTime = 0.f;

	ChaseIdleTime = 0.f;

	HP = 200.f;

	pPlayer = nullptr;

	IsAscending = false;

}

CBarnos::CBarnos(const CBarnos& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");

}

CBarnos::~CBarnos()
{
}


bool CBarnos::Init()
{




	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");

	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderBody1 = CreateComponent<CColliderBox3D>("ColliderBody1");
	ColliderBody2 = CreateComponent<CColliderBox3D>("ColliderBody2");
	ColliderBody3 = CreateComponent<CColliderBox3D>("ColliderBody3");
	ColliderBody4 = CreateComponent<CColliderBox3D>("ColliderBody4");
	ColliderRightWing1 = CreateComponent<CColliderBox3D>("ColliderRightWing1");
	ColliderRightWing2 = CreateComponent<CColliderBox3D>("ColliderRightWing2");
	ColliderRightWing3 = CreateComponent<CColliderBox3D>("ColliderRightWing3");
	ColliderRightWing4 = CreateComponent<CColliderBox3D>("ColliderRightWing4");
	ColliderRightWing5 = CreateComponent<CColliderBox3D>("ColliderRightWing5");
	ColliderLeftWing1 = CreateComponent<CColliderBox3D>("ColliderLeftWing1");
	ColliderLeftWing2 = CreateComponent<CColliderBox3D>("ColliderLeftWing2");
	ColliderLeftWing3 = CreateComponent<CColliderBox3D>("ColliderLeftWing3");
	ColliderLeftWing4 = CreateComponent<CColliderBox3D>("ColliderLeftWing4");
	ColliderLeftWing5 = CreateComponent<CColliderBox3D>("ColliderLeftWing5");

	ColliderLeftFoot = CreateComponent<CColliderBox3D>("ColliderLeftFoot");
	ColliderRightFoot = CreateComponent<CColliderBox3D>("ColliderRightFoot");

	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");
	ColliderLeftFootAttack = CreateComponent<CColliderBox3D>("ColliderLeftFootAttack");
	ColliderRightFootAttack = CreateComponent<CColliderBox3D>("ColliderRightFootAttack");

	ColliderHead->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderBody1->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody2->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderBody3->Set3DExtent(2.f, 2.f, 2.f);
	ColliderBody4->Set3DExtent(1.5f, 1.5f, 1.5f);
	ColliderRightWing1->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing2->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing3->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing4->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderRightWing5->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing1->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing2->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing3->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing4->Set3DExtent(2.3f, 2.3f, 2.3f);
	ColliderLeftWing5->Set3DExtent(2.3f, 2.3f, 2.3f);

	ColliderLeftFoot->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderRightFoot->Set3DExtent(2.5f, 2.5f, 2.5f);

	ColliderHeadAttack->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderLeftFootAttack->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderRightFootAttack->Set3DExtent(2.5f, 2.5f, 2.5f);

	ColliderHead->SetCollisionProfile("Monster");
	ColliderBody1->SetCollisionProfile("Monster");
	ColliderBody2->SetCollisionProfile("Monster");
	ColliderBody3->SetCollisionProfile("Monster");
	ColliderBody4->SetCollisionProfile("Monster");
	ColliderRightWing1->SetCollisionProfile("Monster");
	ColliderRightWing2->SetCollisionProfile("Monster");
	ColliderRightWing3->SetCollisionProfile("Monster");
	ColliderRightWing4->SetCollisionProfile("Monster");
	ColliderRightWing5->SetCollisionProfile("Monster");
	ColliderLeftWing1->SetCollisionProfile("Monster");
	ColliderLeftWing2->SetCollisionProfile("Monster");
	ColliderLeftWing3->SetCollisionProfile("Monster");
	ColliderLeftWing4->SetCollisionProfile("Monster");
	ColliderLeftWing5->SetCollisionProfile("Monster");
	ColliderLeftFoot->SetCollisionProfile("Monster");
	ColliderRightFoot->SetCollisionProfile("Monster");

	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");
	ColliderLeftFootAttack->SetCollisionProfile("MonsterAttack");
	ColliderRightFootAttack->SetCollisionProfile("MonsterAttack");

	//collider callback
	ColliderHead->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderHead->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody1->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody1->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody2->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody2->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody3->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody3->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderBody4->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderBody4->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing1->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing1->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing2->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing2->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing3->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing3->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing4->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing4->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightWing5->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightWing5->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing1->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing1->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing2->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing2->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing3->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing3->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing4->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing4->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftWing5->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftWing5->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderLeftFoot->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderLeftFoot->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);
	ColliderRightFoot->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::OnCollisionBegin);
	ColliderRightFoot->AddCollisionCallback(Collision_State::End, this, &CBarnos::OnCollisionEnd);

	ColliderHeadAttack->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::AttackOnCollisionBegin);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::End, this, &CBarnos::AttackOnCollisionEnd);
	ColliderLeftFootAttack->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::AttackOnCollisionBegin);
	ColliderLeftFootAttack->AddCollisionCallback(Collision_State::End, this, &CBarnos::AttackOnCollisionEnd);
	ColliderRightFootAttack->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::AttackOnCollisionBegin);
	ColliderRightFootAttack->AddCollisionCallback(Collision_State::End, this, &CBarnos::AttackOnCollisionEnd);





	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_State = Transform_State::None;
	m_Mesh->SetMesh("BarnosMesh");
	m_Mesh->CreateAnimationInstance<CBarnosAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(20.f, 10.f, 10.f);
	m_Mesh->SetRelativeRotation(Vector3(250.f, 180.f, 180.f));

	ColliderCarving = CreateComponent<CColliderBox3D>("ColliderCarving");
	ColliderCarving->Set3DExtent(6.0f, 6.0f, 6.0f);
	ColliderCarving->SetCollisionProfile("Carving");
	m_Mesh->AddChild(ColliderCarving);
	ColliderCarving->Enable(false);

	ColliderSliding = CreateComponent<CColliderBox3D>("ColliderSliding");
	ColliderSliding->Set3DExtent(3.0f, 3.0f, 3.0f);
	ColliderSliding->SetOffset(0.0f, 3.0f, 0.0f);
	ColliderSliding->SetCollisionProfile("MonsterSliding");
	m_Mesh->AddChild(ColliderSliding);
	ColliderSliding->Enable(true);
	ColliderSliding->AddCollisionCallback(Collision_State::Begin, this, &CBarnos::SlidingOnCollisionBegin);
	ColliderSliding->AddCollisionCallback(Collision_State::End, this, &CBarnos::SlidingOnCollisionEnd);

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderBody1, "Body1");
	m_Mesh->AddChild(ColliderBody2, "Body2");
	m_Mesh->AddChild(ColliderBody3, "Body3");
	m_Mesh->AddChild(ColliderBody4, "Body4");

	m_Mesh->AddChild(ColliderRightWing1, "RightWing1");
	m_Mesh->AddChild(ColliderRightWing2, "RightWing2");
	m_Mesh->AddChild(ColliderRightWing3, "RightWing3");
	m_Mesh->AddChild(ColliderRightWing4, "RightWing4");
	m_Mesh->AddChild(ColliderRightWing5, "RightWing5");

	m_Mesh->AddChild(ColliderLeftWing1, "LeftWing1");
	m_Mesh->AddChild(ColliderLeftWing2, "LeftWing2");
	m_Mesh->AddChild(ColliderLeftWing3, "LeftWing3");
	m_Mesh->AddChild(ColliderLeftWing4, "LeftWing4");
	m_Mesh->AddChild(ColliderLeftWing5, "LeftWing5");

	m_Mesh->AddChild(ColliderLeftFoot, "RightFoot");
	m_Mesh->AddChild(ColliderRightFoot, "LeftFoot");

	m_Mesh->AddChild(ColliderHeadAttack, "Head");
	m_Mesh->AddChild(ColliderLeftFootAttack, "RightFoot");
	m_Mesh->AddChild(ColliderRightFootAttack, "LeftFoot");

	SetNotify();

	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CBarnos::IDLEStay, &CBarnos::IDLEStart, &CBarnos::IDLEEnd);
	FSM.CreateState("IdleMove", this, &CBarnos::IDLEMOVEStay, &CBarnos::IDLEMOVEStart, &CBarnos::IDLEMOVEEnd);
	FSM.CreateState("Chase", this, &CBarnos::CHASEStay, &CBarnos::CHASEStart, &CBarnos::CHASEEnd);
	FSM.CreateState("GetHit", this, &CBarnos::GETHITStay, &CBarnos::GETHITStart, &CBarnos::GETHITEnd);
	FSM.CreateState("Scream", this, &CBarnos::SCREAMStay, &CBarnos::SCREAMStart, &CBarnos::SCREAMEnd);
	FSM.CreateState("Attack1", this, &CBarnos::ATTACK1Stay, &CBarnos::ATTACK1Start, &CBarnos::ATTACK1End);
	FSM.CreateState("Attack2", this, &CBarnos::ATTACK2Stay, &CBarnos::ATTACK2Start, &CBarnos::ATTACK2End);
	FSM.CreateState("Attack3", this, &CBarnos::ATTACK3Stay, &CBarnos::ATTACK3Start, &CBarnos::ATTACK3End);
	FSM.CreateState("Death", this, &CBarnos::DEATHStay, &CBarnos::DEATHStart, &CBarnos::DEATHEnd);
	FSM.CreateState("FadeOut", this, &CBarnos::FADEOUTStay, &CBarnos::FADEOUTStart, &CBarnos::FADEOUTEnd);

	CResourceManager::GetInst()->LoadSound("Barnos", true, "BarnosWing1" + std::to_string(BarnosCount), "Monster/Barnos/wing1.ogg", SOUND_PATH);
	CResourceManager::GetInst()->LoadSound("Barnos", true, "BarnosWing2" + std::to_string(BarnosCount), "Monster/Barnos/wing2.ogg", SOUND_PATH);
	WingSound1 = CResourceManager::GetInst()->FindSound("BarnosWing1" + std::to_string(BarnosCount));
	WingSound2 = CResourceManager::GetInst()->FindSound("BarnosWing2" + std::to_string(BarnosCount));
	++BarnosCount;

	

	this;

	return true;
}

void CBarnos::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();

	//상태 변경
	FSM.ChangeState("Idle");
}

void CBarnos::Update(float DeltaTime)
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
	



	FSM.Update();

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

void CBarnos::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBarnos* CBarnos::Clone()
{
	return new CBarnos(*this);
}


Vector3 CBarnos::FindNextMovePoint()
{
	Vector3 DestVec;
	int rannum = rand() % 2;

	
	//x값
	if (1==rannum)
	{
		
		DestVec.x = GetWorldPos().x - (rand() % 10 + 8);
	}
	else
	{
		
		DestVec.x = GetWorldPos().x + (rand() % 10 + 8);
	}



	//z값

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


	if (DestVec.y > GetWorldPos().y)
	{
		IsAscending = true;
	}

	return DestVec;
}
Vector3 CBarnos::FindPlayerAroundPos()
{
	Vector3 DestVec;
	int rannum = rand() % 2;

	//x값
	if (1== rannum)
	{		
		DestVec.x = pPlayer->GetWorldPos().x - (rand() % 5 + 2);
	}
	else
	{	
		DestVec.x = pPlayer->GetWorldPos().x + (rand() % 5 + 2);
	}

	
	//z값
	if (1 == rannum)
	{

		DestVec.z = (pPlayer->GetWorldPos().z) - (rand() % 5 + 2);
	}
	else
	{		
		DestVec.z = pPlayer->GetWorldPos().z + (rand() % 5 + 2);
	}

	//y값
	
	DestVec.y = pPlayer->GetWorldPos().y + (rand() % 2);

	float y = m_Scene->GetNavigation3DManager()->GetY(DestVec);
	if (DestVec.y <= y + 6)
	{
		DestVec.y = y + 6;
	}
	return DestVec;
}

void CBarnos::YPosCorrection()
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

void CBarnos::FieldCollision(float DeltaTime)
{
	Vector3 Dir = Vector3(pFieldObj->GetWorldPos() - GetWorldPos());
	Dir.Normalize();
	Dir *= -1;
	AddWorldPos(Dir * CurSpeed * DeltaTime);	
}

void CBarnos::CheckStuck()
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

void CBarnos::SetNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosgliding", this, &CBarnos::FlyNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnoshitdead", this, &CBarnos::DeadNotify1);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosroll", this, &CBarnos::DeadNotify2);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnoshit", this, &CBarnos::GetHitEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosscream", this, &CBarnos::ScreamEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosattack1", this, &CBarnos::AttackEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosattack2", this, &CBarnos::AttackEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBarnos>("barnosattack3", this, &CBarnos::AttackEndNotify);

}

void CBarnos::FlyNotify()
{
	if (IsIdle)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosfly1");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosfly2");
	}




}

void CBarnos::DeadNotify1()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosroll");

}

void CBarnos::DeadNotify2()
{
	AddWorldRotationX(20);
	AddWorldRotationY(80.f);
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosdead");
	CResourceManager::GetInst()->SoundPlay("BarnosDeath");

}

void CBarnos::ToIdleNotify()
{
	FSM.ChangeState("Idle");
}

void CBarnos::ScreamEndNotify()
{
	FSM.ChangeState("Chase");
}

void CBarnos::AttackEndNotify()
{
	FSM.ChangeState("IdleMove");
}

void CBarnos::GetHitEndNotify()
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




void CBarnos::OnCollisionBegin(const CollisionResult& result)
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

void CBarnos::OnCollisionEnd(const CollisionResult& result)
{
}

void CBarnos::AttackOnCollisionBegin(const CollisionResult& result)
{
	std::string t = result.Dest->GetGameObject()->GetName();
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		if (IsAttacking)
		{

		}
	}
}

void CBarnos::AttackOnCollisionEnd(const CollisionResult& result)
{
}

void CBarnos::SlidingOnCollisionBegin(const CollisionResult& result)
{	
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		IsOnFieldCol = true;

		pFieldObj = result.Dest->GetGameObject();
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();
		strcpy_s(m_FieldObjName, result.Dest->GetGameObject()->GetName().c_str());

	}
}

void CBarnos::SlidingOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		pFieldObj = nullptr;
		IsOnFieldCol = false;

		memset(m_FieldObjName, 0, sizeof(char) * 32);
		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}


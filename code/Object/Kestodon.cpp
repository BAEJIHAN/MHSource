#include "Kestodon.h"
#include "KestodonAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Arrow.h"
#include "DragonArrow.h"
#include "Collision/Collision.h"

CKestodon::CKestodon() 
{
	SetTypeID<CKestodon>();
	IdleTime = 0.f;
	MoveTime = 0.f;
	AttackTime = 0.f;
	DodgeTime = 0.f;
	
	pPlayer = nullptr;

	IsCharging = false;
	IsDodged = false;
	
	MoveSpeed = 5;
	HP = 250.f;	
}

CKestodon::CKestodon(const CKestodon& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("Mesh");
	
}

CKestodon::~CKestodon()
{
}

bool CKestodon::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("Mesh");
	
	ColliderHead = CreateComponent<CColliderBox3D>("ColliderHead");
	ColliderUpperBody = CreateComponent<CColliderBox3D>("ColliderUpperBody");
	ColliderLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerBody");
	ColliderLowerLowerBody = CreateComponent<CColliderBox3D>("ColliderLowerLowerBody");
	ColliderTail = CreateComponent<CColliderBox3D>("ColliderTail");
	ColliderLeftLeg = CreateComponent<CColliderBox3D>("ColliderLeftLeg");
	ColliderRightLeg = CreateComponent<CColliderBox3D>("ColliderRightLeg");
	ColliderHeadAttack = CreateComponent<CColliderBox3D>("ColliderHeadAttack");

	ColliderHead->Set3DExtent(2.5f, 2.5f, 2.5f);
	ColliderUpperBody->Set3DExtent(2.f, 2.f, 2.f);
	ColliderLowerBody->Set3DExtent(3.f, 3.f, 3.f);
	ColliderLowerLowerBody->Set3DExtent(2.f, 2.f, 2.f);
	ColliderTail->Set3DExtent(2.f, 2.f, 2.f);
	ColliderLeftLeg->Set3DExtent(1.2f, 1.8f, 1.2f);
	ColliderRightLeg->Set3DExtent(1.2f, 1.8f, 1.2f);
	ColliderHeadAttack->Set3DExtent(2.5f, 2.5f, 2.5f);
	
	ColliderHead->SetCollisionProfile("Monster");
	ColliderUpperBody->SetCollisionProfile("Monster");
	ColliderLowerBody->SetCollisionProfile("Monster");
	ColliderLowerLowerBody->SetCollisionProfile("Monster");
	ColliderTail->SetCollisionProfile("Monster");
	ColliderLeftLeg->SetCollisionProfile("Monster");
	ColliderRightLeg->SetCollisionProfile("Monster");
	ColliderHeadAttack->SetCollisionProfile("MonsterAttack");
	
	ColliderHead->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderHead->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderUpperBody->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderUpperBody->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderLowerBody->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderLowerBody->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderLowerLowerBody->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderLowerLowerBody->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderTail->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderTail->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderLeftLeg->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderLeftLeg->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderRightLeg->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::OnCollisionBegin);
	ColliderRightLeg->AddCollisionCallback(Collision_State::End, this, &CKestodon::OnCollisionEnd);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::AttackOnCollisionBegin);
	ColliderHeadAttack->AddCollisionCallback(Collision_State::End, this, &CKestodon::AttackOnCollisionEnd);
	

	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::Ground);
	m_State = Transform_State::Ground;
	m_Mesh->SetMesh("KestodonMesh");
	m_Mesh->CreateAnimationInstance<CKestodonAnimation>();

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(40.f, 0.f, 10.f);
	m_Mesh->SetRelativeRotation(Vector3(270.f, 180.f, 180.f));
	m_Mesh->SetRelativePos(60.f, 0.f, 60.f);

	m_Mesh->AddChild(ColliderHead, "Head");
	m_Mesh->AddChild(ColliderUpperBody, "UpperBody");
	m_Mesh->AddChild(ColliderLowerBody, "LowerBody");
	m_Mesh->AddChild(ColliderLowerLowerBody, "LowerLowerBody");
	m_Mesh->AddChild(ColliderTail, "Tail");
	m_Mesh->AddChild(ColliderLeftLeg, "LeftLeg");
	m_Mesh->AddChild(ColliderRightLeg, "RightLeg");
	m_Mesh->AddChild(ColliderHeadAttack, "Head");

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
	ColliderSliding->AddCollisionCallback(Collision_State::Begin, this, &CKestodon::SlidingOnCollisionBegin);
	ColliderSliding->AddCollisionCallback(Collision_State::End, this, &CKestodon::SlidingOnCollisionEnd);
	

	SetNotify();

	

	//fsm에 함수포인터를 이용해 상태 생성 
	FSM.CreateState("Idle", this, &CKestodon::IDLEStay, &CKestodon::IDLEStart, &CKestodon::IDLEEnd);
	FSM.CreateState("Move", this, &CKestodon::MOVEStay, &CKestodon::MOVEStart, &CKestodon::MOVEEnd);
	FSM.CreateState("Attack1", this, &CKestodon::ATTACK1Stay, &CKestodon::ATTACK1Start, &CKestodon::ATTACK1End);
	FSM.CreateState("Attack2", this, &CKestodon::ATTACK2Stay, &CKestodon::ATTACK2Start, &CKestodon::ATTACK2End);
	FSM.CreateState("Death", this, &CKestodon::DEATHStay, &CKestodon::DEATHStart, &CKestodon::DEATHEnd);

	FSM.CreateState("Dodge", this, &CKestodon::DODGEStay, &CKestodon::DODGEStart, &CKestodon::DODGEEnd);
	FSM.CreateState("Scream", this, &CKestodon::SCREAMStay, &CKestodon::SCREAMStart, &CKestodon::SCREAMEnd);
	FSM.CreateState("GetHit", this, &CKestodon::GETHITStay, &CKestodon::GETHITStart, &CKestodon::GETHITEnd);
	FSM.CreateState("FadeOut", this, &CKestodon::FADEOUTStay, &CKestodon::FADEOUTStart, &CKestodon::FADEOUTEnd);



	CResourceManager::GetInst()->LoadSound("Kestodon", true, "KestodonCharge"+std::to_string(KestodonCount), "Monster/Kestodon/charge.ogg", SOUND_PATH);
	AttackSound = CResourceManager::GetInst()->FindSound("KestodonCharge" + std::to_string(KestodonCount));
	++KestodonCount;
	

	this;

	return true;
}

void CKestodon::Start()
{
	CGameObject::Start();

	pPlayer = (CPlayer*)CSceneManager::GetInst()->GetScene()->GetPlayerObject();
	//상태 변경
	FSM.ChangeState("Idle");

}

void CKestodon::Update(float DeltaTime)
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
		
	if (IsOnFieldCol)
	{
		FieldCollision(DeltaTime);
		CheckStuck();
	}

	
}

void CKestodon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CKestodon* CKestodon::Clone()
{
	return new CKestodon(*this);
}

Vector3 CKestodon::FindNextMovePoint()
{
	Vector3 DestVec = GetWorldPos();
	int rannum = rand() % 2;
	if (rannum == 1)
	{
		
		DestVec.x = GetWorldPos().x - (rand() % 10 + 8);
	}
	else
	{
		
		DestVec.x = GetWorldPos().x + (rand() % 10 + 8);
	}

	if (rannum == 1)
	{
		
		DestVec.z = GetWorldPos().z - (rand() % 10 + 8);
	}
	else
	{		
		DestVec.z = GetWorldPos().z + (rand() % 10 + 8);
	}

	return DestVec;
}

Vector3 CKestodon::FindPlayerAroundPos()
{
	Vector3 DestVec;	

	int rannum = rand() % 2;

	if (rannum == 1)
	{
		
		DestVec.x = pPlayer->GetWorldPos().x - (rand() % 5 + 2);
	}
	else
	{		
		DestVec.x = pPlayer->GetWorldPos().x + (rand() % 5 + 2);
	}
	

	if (rannum == 1)
	{	
		DestVec.z = (pPlayer->GetWorldPos().z) - (rand() % 5 + 2);
	}
	else
	{		
		DestVec.z = pPlayer->GetWorldPos().z + (rand() % 5 + 2);
	}
	return DestVec;
}

void CKestodon::TakeNestAction()
{
	int t = rand() % 4;
	if (0 == t)
	{
		if (true == IsDodged)
		{
			FSM.ChangeState("Move");
			IsDodged = false;
		}
		else
		{
			FSM.ChangeState("Dodge");
		}
	}
	else
	{
		FSM.ChangeState("Move");
		IsDodged = false;
	}
}

void CKestodon::TakeAttack()
{
	
	FSM.ChangeState("Attack2");

	int r = rand() % 2;
	if (r == 0)
	{
		FSM.ChangeState("Attack1");
	}
	else if (r == 1)
	{
		FSM.ChangeState("Attack2");
	}

	
}

void CKestodon::FieldCollision(float DeltaTime)
{
	Vector3 Dir=Vector3(pFieldObj->GetWorldPos()-GetWorldPos());
	Dir.Normalize();
	Dir *= -1;
	AddWorldPos(Dir * CurSpeed * DeltaTime);

	
	
	
	
	
}

void CKestodon::CheckStuck()
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


void CKestodon::SetNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack1", this, &CKestodon::Attack1EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack2", this, &CKestodon::Attack2EndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack3", this, &CKestodon::Attack3EndNotify);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonscream2", this, &CKestodon::ScreamEndNotify);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattack4", this, &CKestodon::TakeNestAction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodonattackc", this, &CKestodon::TakeNestAction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodondodgeback1", this, &CKestodon::TakeNestAction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodongethit1", this, &CKestodon::GetHitEndNotify);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CKestodon>("kestodongethit2", this, &CKestodon::GetHitEndNotify);
}
void CKestodon::Attack1EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattack2");
	
}
void CKestodon::Attack2EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattack3");
	
}
void CKestodon::Attack3EndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattack4");
	
}

void CKestodon::ToIdleNotify()
{
	FSM.ChangeState("Idle");
}

void CKestodon::ScreamEndNotify()
{
	FSM.ChangeState("Move");
}



void CKestodon::GetHitEndNotify()
{
	if (IsChase)
	{
		TakeNestAction();
	}
	else
	{
		FSM.ChangeState("Scream");
	}
}

void CKestodon::OnCollisionBegin(const CollisionResult& result)
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

void CKestodon::OnCollisionEnd(const CollisionResult& result)
{
	
}

void CKestodon::AttackOnCollisionBegin(const CollisionResult& result)
{
	
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		if (IsAttacking)
		{

		}
	}
}

void CKestodon::AttackOnCollisionEnd(const CollisionResult& result)
{
}

void CKestodon::SlidingOnCollisionBegin(const CollisionResult& result)
{
	/*if ("FieldObj" == result.Dest->GetCollisionProfile()->Name)
	{
		
		pTestObj = result.Dest->GetGameObject();
		IsOnFieldCol = true;
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();

	}*/

	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		IsOnFieldCol = true;
		FieldColInfo = ((CColliderBox3D*)result.Dest)->GetInfo();
		pFieldObj = result.Dest->GetGameObject();
		strcpy_s(m_FieldObjName, result.Dest->GetGameObject()->GetName().c_str());
		
	}
}

void CKestodon::SlidingOnCollisionEnd(const CollisionResult& result)
{
	/*if ("FieldObj" == result.Dest->GetCollisionProfile()->Name)
	{		
		pTestObj = nullptr;
		IsOnFieldCol = false;
	}*/

	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		pFieldObj = nullptr;
		IsOnFieldCol = false;

		memset(m_FieldObjName, 0, sizeof(char) * 32);
		m_SlidingVec = Vector3(0.f, 0.f, 0.f);
	}
}

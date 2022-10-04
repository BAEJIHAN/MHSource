#include "Barnos.h"
#include "Engine.h"
#include "Player.h"
#include "Resource/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "EventManager.h"
#include "../ClientManager3D.h"
#include "../Scene/MainSceneMode.h"
void CBarnos::IDLEStart()
{

	IdleTime = 0;
	if (IsChase)
	{		
		RotateTo(pPlayer->GetWorldPos());
	}	
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosidle1");	
	ChaseIdleTime = (float)(rand() % 10) / 5.2f + 2.0f;

	m_Mesh->SetTransformState(Transform_State::None);
	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();

	if (Dist.Length() < 60.f)
	{
		WingSound1->Play();		
	}
	
	
}

void CBarnos::IDLEStay()
{

	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	IdleTime += DeltaTime;
	
	if (IsChase)
	{
		
		if (IdleTime >= ChaseIdleTime)
		{			
			FSM.ChangeState("Chase");			
		}
	}
	else
	{
		if (IdleTime >= 5)
		{
			FSM.ChangeState("IdleMove");
		}
	}
	
}

void CBarnos::IDLEEnd()
{
	IdleTime = 0;
	if (WingSound1->IsPlay())
		WingSound1->Stop();
	
}

void CBarnos::IDLEMOVEStart()
{
	
	IsMoving = true;
	DestMovePoint = FindNextMovePoint();
	RotateTo(DestMovePoint);
	if (IsAscending)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosascending");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosgliding");
	}

	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();

	if (Dist.Length() < 60.f)
	{
		WingSound1->Play();
	}
}

void CBarnos::IDLEMOVEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	Move(DestMovePoint);
	CurSpeed = MoveSpeed;
	if (false == IsMoving)
	{
		if (IsChase)
		{
			FSM.ChangeState("Chase"); 
		}
		else
		{
			FSM.ChangeState("Idle");
		}
		
	}
		

}

void CBarnos::IDLEMOVEEnd()
{
	CurSpeed = 0;
	IsAscending = false;
	IsMoving = false;
	if (WingSound1->IsPlay())
		WingSound1->Stop();
}







void CBarnos::CHASEStart()
{
	IsMoving = true;
	WingSound2->Play();
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosgliding");
	DestMovePoint = FindPlayerAroundPos();
	RotateTo(DestMovePoint);
}

void CBarnos::CHASEStay()
{

	Move(DestMovePoint);
	CurSpeed = MoveSpeed;
	if (false == IsMoving)
	{
		Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();
		
		if (Dist.Length() > 20.f)
		{
			FSM.ChangeState("Attack2");
		}
		else
		{			
			int r = rand() % 2;
			if (r == 0)
			{
				FSM.ChangeState("Attack1");
			}
			else if (r == 1)
			{
				FSM.ChangeState("Attack3");
			}
			
		}		
	}
}

void CBarnos::CHASEEnd()
{

	if (WingSound2->IsPlay())
		WingSound2->Stop();
	CurSpeed = 0;
}

void CBarnos::GETHITStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnoshit");
	MoveSpeed = 30;
	IsChase = true;
	CResourceManager::GetInst()->SoundPlay("BarnosHit", this);
	IsStun = true;
}

void CBarnos::GETHITStay()
{
}

void CBarnos::GETHITEnd()
{
	IsStun = false;
}

void CBarnos::SCREAMStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	MoveSpeed = 30;
	IsIdle = false;
	IsChase = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosscream");
	RotateTo(pPlayer->GetWorldPos());
	CResourceManager::GetInst()->SoundPlay("BarnosScream", this);
	CEventManager::GetInst()->CallEvent("PlayerMonsterContant");
	CClientManager3D::GetInst()->GetMainScene()->AddMonsterAggro();
}

void CBarnos::SCREAMStay()
{
}

void CBarnos::SCREAMEnd()
{
	CResourceManager::GetInst()->SoundStop("BarnosScream");
}

void CBarnos::ATTACK1Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	
	RotateTo(pPlayer->GetWorldPos());
	AttackTime = 0;
	
	CResourceManager::GetInst()->SoundPlay("BarnosAttack1", this);
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosattack1");
}

void CBarnos::ATTACK1Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (AttackTime >= 0.1f)
	{
		IsAttacking = true;
	}
}

void CBarnos::ATTACK1End()
{
	AttackTime = 0;
	IsAttacking = false;
	CResourceManager::GetInst()->SoundStop("BarnosAttack1");
}

void CBarnos::ATTACK2Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);

	RotateTo(pPlayer->GetWorldPos());
	AttackTime = 0;
	IsAttacking = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosattack2");
	CResourceManager::GetInst()->SoundPlay("BarnosAttack2", this);
}

void CBarnos::ATTACK2Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;

	
	if (AttackTime <= 1.5f)
	{
		Vector3 t = GetWorldAxis(AXIS::AXIS_Y);
		t.y = 0;		

		
		AddWorldPos(t * (MoveSpeed + 10) * DeltaTime);
		CurSpeed = (MoveSpeed + 10);

		
	
	}
	else
	{
		CurSpeed = 0;
	}
}

void CBarnos::ATTACK2End()
{
	AttackTime = 0;
	IsAttacking = false;
	CResourceManager::GetInst()->SoundStop("BarnosAttack2");
	CurSpeed = 0;
}

void CBarnos::ATTACK3Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	RotateTo(pPlayer->GetWorldPos());
	AttackTime = 0;
	IsAttacking = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnosattack3");
	CResourceManager::GetInst()->SoundPlay("BarnosAttack3", this);
}

void CBarnos::ATTACK3Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	AttackTime += DeltaTime;
	if (AttackTime >= 0.2f)
	{
		IsAttacking = true;
	}
}

void CBarnos::ATTACK3End()
{ 
	CResourceManager::GetInst()->SoundStop("BarnosAttack3");
	AttackTime = 0;
	IsAttacking = false;
}


void CBarnos::DEATHStart()
{
	IsDead = true;
	Vector3 DestVec = GetWorldPos();
	DestVec.y = 0;
	DeathYpos = m_Scene->GetNavigation3DManager()->GetY(DestVec);
	CurYPos = GetWorldPos().y;

	m_Mesh->GetAnimationInstance()->ChangeAnimation("barnoshitdead");

	m_Mesh->DeleteChild(ColliderHead);
	m_Mesh->DeleteChild(ColliderBody1);
	m_Mesh->DeleteChild(ColliderBody2);
	m_Mesh->DeleteChild(ColliderBody3);
	m_Mesh->DeleteChild(ColliderBody4);
	m_Mesh->DeleteChild(ColliderRightWing1);
	m_Mesh->DeleteChild(ColliderRightWing2);
	m_Mesh->DeleteChild(ColliderRightWing3);
	m_Mesh->DeleteChild(ColliderRightWing4);
	m_Mesh->DeleteChild(ColliderRightWing5);
	m_Mesh->DeleteChild(ColliderLeftWing1);
	m_Mesh->DeleteChild(ColliderLeftWing2);
	m_Mesh->DeleteChild(ColliderLeftWing3);
	m_Mesh->DeleteChild(ColliderLeftWing4);
	m_Mesh->DeleteChild(ColliderLeftWing5);
	m_Mesh->DeleteChild(ColliderLeftFoot);
	m_Mesh->DeleteChild(ColliderRightFoot);
	m_Mesh->DeleteChild(ColliderHeadAttack);
	m_Mesh->DeleteChild(ColliderLeftFootAttack);
	m_Mesh->DeleteChild(ColliderRightFootAttack);

	ColliderHead->Destroy();
	ColliderBody1->Destroy();
	ColliderBody2->Destroy();
	ColliderBody3->Destroy();
	ColliderBody4->Destroy();
	ColliderRightWing1->Destroy();
	ColliderRightWing2->Destroy();
	ColliderRightWing3->Destroy();
	ColliderRightWing4->Destroy();
	ColliderRightWing5->Destroy();
	ColliderLeftWing1->Destroy();
	ColliderLeftWing2->Destroy();
	ColliderLeftWing3->Destroy();
	ColliderLeftWing4->Destroy();
	ColliderLeftWing5->Destroy();
	ColliderLeftFoot->Destroy();
	ColliderRightFoot->Destroy();
	ColliderHeadAttack->Destroy();
	ColliderLeftFootAttack->Destroy();
	ColliderRightFootAttack->Destroy();

	ColliderCarving->Enable(true);

	CEventManager::GetInst()->CallEvent("PlayerMonsterRelease");
	CClientManager3D::GetInst()->GetMainScene()->SubMonsterAggro();
}

void CBarnos::DEATHStay()
{
	if (DeathYpos < CurYPos)
	{
		float DeltaTime = CEngine::GetInst()->GetDeltaTime();
		CurYPos -= DeltaTime*10;
		Vector3 t = GetWorldPos();
		t.y = CurYPos;
		SetWorldPos(t);
	}
	
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	DeathTime += DeltaTime;
	if (IsCarved)
	{
		FSM.ChangeState("FadeOut");
	}
	if (DeathTime > 30.f)
	{
		FSM.ChangeState("FadeOut");
	}
}

void CBarnos::DEATHEnd()
{
	DeathTime = 0;
}

void CBarnos::FADEOUTStart()
{
	m_Mesh->SetLayerName("Effect");
	IsFading = true;
}

void CBarnos::FADEOUTStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	FadeOpacity -= (float)(DeltaTime * 0.1);
	m_Mesh->SetOpacity(FadeOpacity, 0);
	m_Mesh->SetOpacity(FadeOpacity, 1);
	m_Mesh->SetOpacity(FadeOpacity, 2);
	m_Mesh->SetOpacity(FadeOpacity, 3);
	m_Mesh->SetOpacity(FadeOpacity, 4);



	if (FadeOpacity <= 0.1f)
	{
		Destroy();
	}
}

void CBarnos::FADEOUTEnd()
{
}



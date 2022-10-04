#include "Jagras.h"
#include "Engine.h"
#include "Player.h"
#include "Resource/ResourceManager.h"
#include "EventManager.h"
#include "../ClientManager3D.h"
#include "../Scene/MainSceneMode.h"

void CJagras::IDLEStart()
{
	IdleTime = 0;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasidle");

	Vector3 Dist = pPlayer->GetWorldPos() - GetWorldPos();

	if (Dist.Length() < 60.f)
	{
		CResourceManager::GetInst()->SoundPlay("JagrasIdle", this);
	}
	
	
}

void CJagras::IDLEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	IdleTime += DeltaTime;
	if (IdleTime >= 4.f)
	{
		FSM.ChangeState("Move");		
	}
	
}

void CJagras::IDLEEnd()
{
	CResourceManager::GetInst()->SoundStop("JagrasIdle");
	IdleTime = 0;
}

void CJagras::MOVEStart()
{
	IsMoving = true;
	if (IsChase)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("jagraschase");
		DestMovePoint = FindPlayerAroundPos();
		RotateTo(DestMovePoint);
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasmove");
		DestMovePoint = FindNextMovePoint();
		RotateTo(DestMovePoint);
		
	}
	
}

void CJagras::MOVEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	Move(DestMovePoint);
	CurSpeed = MoveSpeed;
	if (false == IsMoving)
	{
		if (IsChase)
		{
			TakeAttack();
			
		}
		else
		{
			FSM.ChangeState("Idle");
		}
		
	}
		
}

void CJagras::MOVEEnd()
{
	CurSpeed = 0;
	IsMoving = false;
}



void CJagras::GETHITStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	
	int r = rand() % 2;
	if (0 == r)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrashit1");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrashit2");
	}

	MoveSpeed = 30;
	
	CResourceManager::GetInst()->SoundPlay("JagrasHit", this);
	IsStun = true;
}

void CJagras::GETHITStay()
{
}

void CJagras::GETHITEnd()
{
	IsStun = false;
}

void CJagras::SCREAMStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	MoveSpeed = 30;
	IsIdle = false;
	IsChase = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasscream");
	RotateTo(pPlayer->GetWorldPos());
	CResourceManager::GetInst()->SoundPlay("JagrasScream", this);
	CEventManager::GetInst()->CallEvent("PlayerMonsterContant");
	CClientManager3D::GetInst()->GetMainScene()->AddMonsterAggro();
}

void CJagras::SCREAMStay()
{
}

void CJagras::SCREAMEnd()
{
	CResourceManager::GetInst()->SoundStop("JagrasScream");
}
void CJagras::DODGEStart()
{
	IsDodged = true;
	DodgeTime = 0;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasdodgeback"); 
	RotateTo(pPlayer->GetWorldPos());
}
void CJagras::DODGEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	DodgeTime += DeltaTime;
	if (DodgeTime>=0.2f && DodgeTime <= 0.6f)
	{
		Vector3 t = GetWorldAxis(AXIS::AXIS_Y);
		t.y = 0;
		t.x = -t.x;
		t.z = -t.z;
		
		
		AddWorldPos(t * (MoveSpeed + 40) * DeltaTime);
		CurSpeed = (MoveSpeed + 40);

		

	}
	if (DodgeTime >= 1.5f)
	{
		DodgeTime = 0;
		CurSpeed = 0;
	}

}
void CJagras::DODGEEnd()
{
	CurSpeed = 0;
}
void CJagras::ATTACK1Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	RotateTo(pPlayer->GetWorldPos());	
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasattack1");
	CResourceManager::GetInst()->SoundPlay("JagrasAttack1", this);

}

void CJagras::ATTACK1Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	


	if (Attack1Move)
	{
		Vector3 t = GetWorldAxis(AXIS::AXIS_Y);
		t.y = 0;
	

		
		AddWorldPos(t * (MoveSpeed + 15) * DeltaTime);
		CurSpeed = (MoveSpeed + 15);

		
	}
	else
	{
		CurSpeed = 0;
	}
}

void CJagras::ATTACK1End()
{
	CResourceManager::GetInst()->SoundStop("JagrasAttack1");
	Attack1Move = false;
	IsAttacking = false;
	CurSpeed = 0;
}

void CJagras::ATTACK2Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	RotateTo(pPlayer->GetWorldPos());
	AttackTime = 0;
	CResourceManager::GetInst()->SoundPlay("JagrasAttack2", this);
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasattackb");
	
}

void CJagras::ATTACK2Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 0.7f)
	{
		IsAttacking = true;
	}

	if (AttackTime>=0.7f && AttackTime<=1.2f)
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

void CJagras::ATTACK2End()
{
	CResourceManager::GetInst()->SoundStop("JagrasAttack2");
	AttackTime = 0;
	IsAttacking = false;
	CurSpeed = 0;
}

void CJagras::ATTACK3Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	RotateTo(pPlayer->GetWorldPos());
	AttackTime = 0;
	IsAttacking = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasattackc");
	CResourceManager::GetInst()->SoundPlay("JagrasAttack3", this);
}

void CJagras::ATTACK3Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 0.7f)
	{
		IsAttacking = true;
	}

	if (AttackTime >= 0.7f && AttackTime <= 1.2f)
	{
		Vector3 t = GetWorldAxis(AXIS::AXIS_Y);
		t.y = 0;
		

		
		AddWorldPos(t * MoveSpeed * DeltaTime);
		CurSpeed = MoveSpeed;

		
	}
	else
	{
		CurSpeed = 0;
	}
}


void CJagras::ATTACK3End()
{
	AttackTime = 0;
	CResourceManager::GetInst()->SoundStop("JagrasAttack3");
	CurSpeed = 0;
}

void CJagras::DEATHStart()
{
	int t = rand() % 2;
	if (0 == t)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasdeath1");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("jagrasdeath2");
	}
	IsDead = true;
	CResourceManager::GetInst()->SoundPlay("JagrasDeath", this);

	m_Mesh->DeleteChild(ColliderHead);
	m_Mesh->DeleteChild(ColliderBody1);
	m_Mesh->DeleteChild(ColliderBody2);
	m_Mesh->DeleteChild(ColliderBody3);
	m_Mesh->DeleteChild(ColliderBody4);
	m_Mesh->DeleteChild(ColliderBody5);
	m_Mesh->DeleteChild(ColliderTail1);
	m_Mesh->DeleteChild(ColliderTail2);
	m_Mesh->DeleteChild(ColliderRightFrontLeg);
	m_Mesh->DeleteChild(ColliderLeftFrontLeg);
	m_Mesh->DeleteChild(ColliderRightBackLeg);
	m_Mesh->DeleteChild(ColliderLeftBackLeg);
	m_Mesh->DeleteChild(ColliderHeadAttack);
	m_Mesh->DeleteChild(ColliderLeftArmAttack);
	m_Mesh->DeleteChild(ColliderRightArmAttack);

	ColliderHead->Destroy();
	ColliderBody1->Destroy();
	ColliderBody2->Destroy();
	ColliderBody3->Destroy();
	ColliderBody4->Destroy();
	ColliderBody5->Destroy();
	ColliderTail1->Destroy();
	ColliderTail2->Destroy();
	ColliderRightFrontLeg->Destroy();
	ColliderLeftFrontLeg->Destroy();
	ColliderRightBackLeg->Destroy();
	ColliderLeftBackLeg->Destroy();
	ColliderHeadAttack->Destroy();
	ColliderLeftArmAttack->Destroy();
	ColliderRightArmAttack->Destroy();

	ColliderCarving->Enable(true);

	CEventManager::GetInst()->CallEvent("PlayerMonsterRelease");
	CClientManager3D::GetInst()->GetMainScene()->SubMonsterAggro();
}

void CJagras::DEATHStay()
{
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

void CJagras::DEATHEnd()
{
	DeathTime = 0;
}

void CJagras::FADEOUTStart()
{
	m_Mesh->SetLayerName("Effect");
	IsFading = true;
}

void CJagras::FADEOUTStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	FadeOpacity -= (float)(DeltaTime * 0.1);
	m_Mesh->SetOpacity(FadeOpacity, 0);
	m_Mesh->SetOpacity(FadeOpacity, 1);
	m_Mesh->SetOpacity(FadeOpacity, 2);
	

	if (FadeOpacity <= 0.1f)
	{
		Destroy();
	}
}

void CJagras::FADEOUTEnd()
{
}


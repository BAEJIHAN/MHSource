#include "Kestodon.h"
#include "Engine.h"
#include "Player.h"
#include "Resource/ResourceManager.h"
#include "EventManager.h"
#include "../ClientManager3D.h"
#include "../Scene/MainSceneMode.h"
void CKestodon::IDLEStart()
{
	IdleTime = 0;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonidle1");
	
	
}

void CKestodon::IDLEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	IdleTime += DeltaTime;
	if (IdleTime >= 8)
	{
		FSM.ChangeState("Move");
	}
}

void CKestodon::IDLEEnd()
{
	IdleTime = 0;
}



void CKestodon::MOVEStart()
{
	

	IsMoving = true;
	if (IsChase)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonmove2");
		DestMovePoint = FindPlayerAroundPos();
		RotateTo(DestMovePoint);
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonmove1");
		DestMovePoint = FindNextMovePoint();
		RotateTo(DestMovePoint);

	}
}

void CKestodon::MOVEStay()
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

void CKestodon::MOVEEnd()
{
	CurSpeed = 0;
}

void CKestodon::ATTACK1Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	RotateTo(pPlayer->GetWorldPos());
	AttackTime = 0;

	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattack1");
}

void CKestodon::ATTACK1Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	

	AttackTime += DeltaTime;

	if (AttackTime >= 0.5f)
	{
		IsAttacking = true;
	}

	if (AttackTime >= 2.3f && AttackTime <=4.5f)
	{
		Vector3 t = GetWorldAxis(AXIS::AXIS_Y);
		t.y = 0;
	


		
		AddWorldPos(t * (MoveSpeed + 20) * DeltaTime);
		CurSpeed = (MoveSpeed + 20);
		


		if (!IsCharging)
		{			
			AttackSound->Play();			
			IsCharging = true;
		}
	}
	if (AttackTime > 5.5f)
	{
		
		if (AttackSound->IsPlay())
		{
			AttackSound->Stop();
		}
		IsCharging = false;
		IsAttacking=false;
		CurSpeed = 0;
	}
}

void CKestodon::ATTACK1End()
{
	
	if (AttackSound->IsPlay())
	{
		AttackSound->Stop();
	}
	IsCharging = false;
	IsAttacking = false;
	CurSpeed = 0;
}

void CKestodon::ATTACK2Start()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	RotateTo(pPlayer->GetWorldPos());
	AttackTime = 0;

	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonattackc");
}

void CKestodon::ATTACK2Stay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();

	AttackTime += DeltaTime;

	if (AttackTime >= 2.1f)
	{
		IsAttacking = true;
	}

	if (AttackTime >= 2.4f && AttackTime <= 3.2f)
	{
		Vector3 t = GetWorldAxis(AXIS::AXIS_Y);
		t.y = 0;
	

		
		AddWorldPos(t * (MoveSpeed + 20) * DeltaTime);
		CurSpeed = (MoveSpeed + 20);



		if (!IsCharging )
		{
			
			

			if (AttackSound->IsPlay())
			{
				AttackSound->Stop();
			}

			AttackSound->Play();
			
			IsCharging = true;
		}
	

	}

	if (AttackTime > 3.6f)
	{
		
		
		if (AttackSound->IsPlay())
		{
			AttackSound->Stop();
		}

		IsCharging = false;
		IsAttacking=false;
		CurSpeed = 0;
	}

	
}

void CKestodon::ATTACK2End()
{
	
	if (AttackSound->IsPlay())
	{
		AttackSound->Stop();
	}
	
	IsCharging = false;
	IsAttacking = 0;
	CurSpeed = 0;
}

void CKestodon::GETHITStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	
	int r = rand() % 2;
	if (0 == r)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodongethit1");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodongethit2");
	}

	MoveSpeed = 15.f;	
	CResourceManager::GetInst()->SoundPlay("KestodonHit", this);
	IsStun = true;
}

void CKestodon::GETHITStay()
{
}

void CKestodon::GETHITEnd()
{
	CResourceManager::GetInst()->SoundStop("KestodonHit");
	IsStun = false;
}

void CKestodon::SCREAMStart()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::MonsterBattle);
	MoveSpeed = 20;
	IsIdle = false;
	IsChase = true;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodonscream2");
	RotateTo(pPlayer->GetWorldPos());
	CResourceManager::GetInst()->SoundPlay("KestodonScream", this);
	CEventManager::GetInst()->CallEvent("PlayerMonsterContant");
	CClientManager3D::GetInst()->GetMainScene()->AddMonsterAggro();
}

void CKestodon::SCREAMStay()
{
}

void CKestodon::SCREAMEnd()
{
	CResourceManager::GetInst()->SoundStop("KestodonScream");
}

void CKestodon::DODGEStart()
{
	IsDodged = true;
	DodgeTime = 0;
	m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodondodgeback1");
	RotateTo(pPlayer->GetWorldPos());

}

void CKestodon::DODGEStay()
{
	float DeltaTime = CEngine::GetInst()->GetDeltaTime();
	DodgeTime += DeltaTime;
	if (DodgeTime >= 0.2f && DodgeTime <= 0.6f)
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

void CKestodon::DODGEEnd()
{
	CurSpeed = 0;
}

void CKestodon::DEATHStart()
{
	int t = rand() % 2;
	if (0 == t)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodondeath1");
	}
	else
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("kestodondeath2");
	}
	IsDead = true;
	CResourceManager::GetInst()->SoundPlay("KestodonDeath", this);

	m_Mesh->DeleteChild(ColliderHead);
	m_Mesh->DeleteChild(ColliderUpperBody);
	m_Mesh->DeleteChild(ColliderLowerBody);
	m_Mesh->DeleteChild(ColliderLowerLowerBody);
	m_Mesh->DeleteChild(ColliderTail);
	m_Mesh->DeleteChild(ColliderLeftLeg);
	m_Mesh->DeleteChild(ColliderRightLeg);
	m_Mesh->DeleteChild(ColliderHeadAttack);

	ColliderHead->Destroy();
	ColliderUpperBody->Destroy();
	ColliderLowerBody->Destroy();
	ColliderLowerLowerBody->Destroy();
	ColliderTail->Destroy();
	ColliderLeftLeg->Destroy();
	ColliderRightLeg->Destroy();
	ColliderHeadAttack->Destroy();

	ColliderCarving->Enable(true);
	
	CEventManager::GetInst()->CallEvent("PlayerMonsterRelease");
	CClientManager3D::GetInst()->GetMainScene()->SubMonsterAggro();
}

void CKestodon::DEATHStay()
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

void CKestodon::DEATHEnd()
{
	DeathTime = 0;
}

void CKestodon::FADEOUTStart()
{
	m_Mesh->SetLayerName("Effect");
	IsFading = true;
}

void CKestodon::FADEOUTStay()
{
	float DeltaTime=CEngine::GetInst()->GetDeltaTime();
	FadeOpacity -= (float)(DeltaTime*0.1);
	m_Mesh->SetOpacity(FadeOpacity, 0);
	m_Mesh->SetOpacity(FadeOpacity, 1);
	m_Mesh->SetOpacity(FadeOpacity, 2);
	m_Mesh->SetOpacity(FadeOpacity, 3);

	if (FadeOpacity <= 0.1f)
	{
		Destroy();
	}
}

void CKestodon::FADEOUTEnd()
{
}


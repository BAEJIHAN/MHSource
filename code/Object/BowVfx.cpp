
#include "BowVfx.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Resource/Material/Material.h"


CBowVfx::CBowVfx()
{
	SetTypeID<CBowVfx>();
}

CBowVfx::CBowVfx(const CBowVfx& obj)
{
	m_VFXMesh = (CStaticMeshComponent*)FindComponent("BowVfx");
	m_PaperBurn1 = (CPaperBurnComponent*)FindComponent("PaperBurn1");
	m_PaperBurn2 = (CPaperBurnComponent*)FindComponent("PaperBurn2");
}

CBowVfx::~CBowVfx()
{
}

bool CBowVfx::Init()
{
	m_VFXMesh = CreateComponent<CStaticMeshComponent>("BowVfx");
	m_PaperBurn1 = CreateComponent<CPaperBurnComponent>("PaperBurn1");
	m_PaperBurn2 = CreateComponent<CPaperBurnComponent>("PaperBurn2");

	SetRootComponent(m_VFXMesh);

	m_VFXMesh->SetMesh("BowVfxMesh");
	m_VFXMesh->SetLayerName("Effect");
	//m_VFXMesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_VFXMesh->SetRelativeScale(10.05f, 10.05f, 10.05f);
	m_VFXMesh->SetWorldRotationY(180.f);
	m_VFXMesh->SetOpacity(0.8f, 0);
	m_VFXMesh->SetOpacity(0.8f, 1);
	m_VFXMesh->GetMaterial(0)->SetShader("EffectShader");
	m_VFXMesh->GetMaterial(0)->SetRenderState("NoneCull");
	m_VFXMesh->GetMaterial(1)->SetShader("EffectShader");
	m_VFXMesh->GetMaterial(1)->SetRenderState("NoneCull");
	m_VFXMesh->GetTransform()->SetTransformState(Transform_State::None);

	for (int i = 0; i < 2; ++i)
	{
		m_VFXMesh->SetBaseColor(0.8f, 0.f, 0.f, 0.8f, i);
	}
	m_PaperBurn1->SetMaterial(m_VFXMesh->GetMaterial(0));
	m_PaperBurn1->SetBurnTexture("VFX1", TEXT("Vfx/BC7_md_wp11_000_BM.dds"));
	m_PaperBurn1->StartPaperBurn();
	m_PaperBurn1->SetFinishTime(1.f);
	m_PaperBurn1->SetInverse(true);
	m_PaperBurn1->SetInLineColor(1.f, 0.f, 0.f, 1.f);
	m_PaperBurn1->SetCenterLineColor(1.f, 0.7f, 0.f, 1.f);
	m_PaperBurn1->SetOutLineColor(1.f, 0.4f, 0.f, 1.f);
	m_PaperBurn1->SetFinishCallback<CBowVfx>(this, &CBowVfx::EndNotify);

	m_PaperBurn2->SetMaterial(m_VFXMesh->GetMaterial(1));
	m_PaperBurn2->SetBurnTexture("VFX2", TEXT("Vfx/BC7_md_wp11_001_BM.dds"));
	m_PaperBurn2->StartPaperBurn();
	m_PaperBurn2->SetFinishTime(1.f);
	m_PaperBurn2->SetInverse(true);
	m_PaperBurn2->SetInLineColor(1.f, 0.f, 0.f, 1.f);
	m_PaperBurn2->SetCenterLineColor(1.f, 0.7f, 0.f, 1.f);
	m_PaperBurn2->SetOutLineColor(1.f, 0.4f, 0.f, 1.f);
	m_PaperBurn2->SetFinishCallback<CBowVfx>(this, &CBowVfx::EndNotify);

	/*m_PaperBurn3->SetMaterial(m_VFXMesh->GetMaterial(2));
	m_PaperBurn3->SetBurnTexture("VFX1", TEXT("Vfx/BC7_md_wp11_000_BM.dds"));
	m_PaperBurn3->StartPaperBurn();
	m_PaperBurn3->SetFinishCallback<CBowVfx>(this, &CBowVfx::EndNotify);*/

	//m_Player = (CPlayer*)m_Scene->GetPlayerObject();


	return true;
}

void CBowVfx::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());

	if (m_Player)
	{
		//m_VFXMesh->AddRelativeRotationY(100.f * DeltaTime);
	}
}

void CBowVfx::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBowVfx* CBowVfx::Clone()
{
	return new CBowVfx(*this);
}

void CBowVfx::EndNotify()
{
	m_PaperBurn1->SetFilter(0.f);
	m_PaperBurn2->SetFilter(0.f);
}

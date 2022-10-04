
#include "DamageFont.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"

CDamageFont::CDamageFont()
{
}

CDamageFont::CDamageFont(const CDamageFont& obj)
{
}

CDamageFont::~CDamageFont()
{
}

bool CDamageFont::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("DamageFont");

	SetRootComponent(m_Billboard);

	return true;
}

void CDamageFont::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

CDamageFont* CDamageFont::Clone()
{
	return new CDamageFont(*this);
}

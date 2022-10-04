#include "KestodonAnimation.h"


CKestodonAnimation::CKestodonAnimation()
{
	SetTypeID<CKestodonAnimation>();
}

CKestodonAnimation::CKestodonAnimation(const CKestodonAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CKestodonAnimation::~CKestodonAnimation()
{
}


bool CKestodonAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("kestodonmain", "kestodonmain", true, 2.f);
	AddAnimation("kestodon1", "kestodonmove1", true, 6.f);
	AddAnimation("kestodon2", "kestodon2", true, 1.5f);//폐기
	AddAnimation("kestodon3", "kestodon3", true, 1.5f);//폐기
	AddAnimation("kestodon4", "kestodonmovestop1", true, 1.5f);
	AddAnimation("kestodon5", "kestodonmovestop2", true, 1.5f);
	AddAnimation("kestodon6", "kestodonmove2", true, 2.5f);
	AddAnimation("kestodon7", "kestodonchase", true, 1.5f);//달리면서 울기
	AddAnimation("kestodon8", "kestodon8", true, 1.5f);//달리면서 울기
	AddAnimation("kestodon9", "kestodondodgeback1", true, 1.5f);
	AddAnimation("kestodon10", "kestodondodgeback2", true, 1.5f);
	AddAnimation("kestodon11", "kestodon11", true, 1.5f);//달리면서 울기
	AddAnimation("kestodon12", "kestodon12", true, 1.5f);//폐기
	AddAnimation("kestodon13", "kestodon13", true, 1.5f);//폐기
	AddAnimation("kestodon14", "kestodonattack1", true, 0.5f);
	AddAnimation("kestodon15", "kestodonattack2", true, 2.4f);
	AddAnimation("kestodon16", "kestodonattack3", true, 1.2f);
	AddAnimation("kestodon17", "kestodonattack4", true, 5.f);
	AddAnimation("kestodon18", "kestodonattackb", true, 6.f);
	AddAnimation("kestodon19", "kestodonscream1", true, 4.f);
	AddAnimation("kestodon20", "kestodongethit1", true, 4.f);
	AddAnimation("kestodon21", "kestodongethit2", true, 4.f);
	AddAnimation("kestodon22", "kestodondeath1", false, 4.f);
	AddAnimation("kestodon23", "kestodon23", true, 1.5f);//바닥에서 비틀거리기
	AddAnimation("kestodon24", "kestodon24", true, 3.0f);//일어남
	AddAnimation("kestodon25", "kestodondeath2", false, 4.f);
	AddAnimation("kestodon26", "kestodon26", true, 6.0f);//공격
	AddAnimation("kestodon27", "kestodonattackc", true, 6.0f);//공격
	AddAnimation("kestodon28", "kestodonscream2", true, 6.f);
	AddAnimation("kestodon29", "kestodonidle1", true, 8.f);
	




	return true;
}

CKestodonAnimation* CKestodonAnimation::Clone()
{
	return new CKestodonAnimation(*this);
}

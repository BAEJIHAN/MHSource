#include "JagrasAnimation.h"

CJagrasAnimation::CJagrasAnimation()
{
	SetTypeID<CJagrasAnimation>();
}

CJagrasAnimation::CJagrasAnimation(const CJagrasAnimation& Anim) :
	CAnimationSequenceInstance(Anim)
{
}

CJagrasAnimation::~CJagrasAnimation()
{
}

/*

*/

bool CJagrasAnimation::Init()
{
	if (!CAnimationSequenceInstance::Init())
		return false;

	AddAnimation("jagrasmain", "jagrasmain", true, 1.5f);//Æó±â
	AddAnimation("jagras1", "jagras1", true, 1.5f);//Æó±â
	AddAnimation("jagras2", "jagras2", true, 1.5f);//Æó±â
	AddAnimation("jagras3", "jagras3", true, 1.5f);//Æó±â
	AddAnimation("jagras4", "jagras4", true, 1.5f);//Æó±â
	AddAnimation("jagras5", "jagrasmove", true, 6.f);
	AddAnimation("jagras6", "jagrasdodgeleft", true, 1.5f);
	AddAnimation("jagras7", "jagrasdodgeright", true, 1.5f);
	AddAnimation("jagras8", "jagrasdodgeback", true, 1.5f);
	AddAnimation("jagras9", "jagrasattackup1", true, 1.5f);
	AddAnimation("jagras10", "jagrasattackup2", true, 1.5f);
	AddAnimation("jagras11", "jagrasattackup3", true, 1.5f);
	AddAnimation("jagras12", "jagraschase", true, 1.5f);//»¡¸® ÀÌµ¿
	AddAnimation("jagras13", "jagras13", true, 2.0f);//»¡¸® ÀÌµ¿
	AddAnimation("jagras14", "jagras14", true, 1.5f);//»¡¸® ÀÌµ¿ ¿ÞÂÊ
	AddAnimation("jagras15", "jagras15", true, 1.5f);//»¡¸® ÀÌµ¿ ¿À¸¥ÂÊ
	AddAnimation("jagras16", "jagrasattack1", true, 1.2f);
	AddAnimation("jagras17", "jagrasattack2", true, 1.2f);
	AddAnimation("jagras18", "jagrasattack3", true, 1.2f);
	AddAnimation("jagras19", "jagrasattackb", true, 3.f);//°ø°Ý
	AddAnimation("jagras20", "jagrasattackc", true, 3.f);//°ø°Ý
	AddAnimation("jagras21", "jagrasattack4", true, 1.2f);
	AddAnimation("jagras22", "jagrasattack5", true, 0.5f);
	AddAnimation("jagras23", "jagras23", true, 1.5f);//Æó±â
	AddAnimation("jagras24", "jagrasattack6", true, 1.2f);
	AddAnimation("jagras25", "jagrashit1", true, 2.5f); //ÇÇ°Ý
	AddAnimation("jagras26", "jagrashit2", true, 2.5f); //ÇÇ°Ý
	AddAnimation("jagras27", "jagrasroll", true, 1.5f);
	AddAnimation("jagras28", "jagrasstandup", true, 1.5f);
	AddAnimation("jagras29", "jagrasdeath1", false, 2.5f);
	AddAnimation("jagras30", "jagrasparalysis", true, 1.5f);
	AddAnimation("jagras31", "jagrasparalysisretore", true, 1.5f);
	AddAnimation("jagras32", "jagras32", true, 3.f);//ÇÇ°Ý ÈÄ ¿ï±â
	AddAnimation("jagras33", "jagrasdeath2", false, 4.5f);
	AddAnimation("jagras34", "jagrasidle", true, 4.f);
	AddAnimation("jagras35", "jagrasscream", true, 4.f);
	
	




	return true;
}

CJagrasAnimation* CJagrasAnimation::Clone()
{
	return new CJagrasAnimation(*this);
}

#pragma once
#include "Scene/SceneMode.h"
class CStartSceneMode :
	public CSceneMode
{
public:
	CStartSceneMode();
	~CStartSceneMode();

private:
	CSharedPtr<class CStartWindow> m_StartWindow;
	std::function<void(bool, float)> m_LoadingFunction;
	bool    m_First;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void CreateMaterial();
	void CreateParticle();
	void LoadSound();

public:
	template <typename T>
	void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
	{
		m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};


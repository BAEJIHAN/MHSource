#pragma once

#include "GameInfo.h"

/// <summary>
/// 사전에 이벤트 키워드로 사용할 키값을 EventManager에 등록해둡니다(AddEventName).
/// 각 오브젝트가 해당 이벤트 키워드에 함수를 등록(AddEventCallback)하고,
/// 나중에 특정 오브젝트가 해당하는 이벤트(CallEvent) 함수를 호출할 경우,
/// 해당 이벤트 키워드로 바인딩된 함수를 모두 호출합니다. 
/// </summary>
class CEventManager
{
public:
	bool Init();

private:
	std::unordered_map<std::string, std::list<std::function<void()>>> m_mapEvent;

private:
	Stage_Type		m_LoadStageType;

public:
	void SetStageType(Stage_Type Type)
	{
		m_LoadStageType = Type;
	}

public:
	Stage_Type GetLoadStageType() const
	{
		return m_LoadStageType;
	}

public:
	/*
	* Name을 Key값으로 해당 Key값에 바인딩된 함수를 **모두** 호출합니다.
	*/
	void CallEvent(const std::string& Name)
	{
		auto	iter = m_mapEvent[Name].begin();
		auto	iterEnd = m_mapEvent[Name].end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)();
		}
	}



public:
	void ClearAllCallback()
	{
		auto	iter = m_mapEvent.begin();
		auto	iterEnd = m_mapEvent.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.clear();
		}
	}

	/*
	* KeyName을 Key값으로 함수를 등록.
	* 만약 등록되지않은 Key값이라면 즉시 추가해줌.
	*/
public:
	template <typename T>
	void AddEventCallback(const std::string& KeyName, T* Obj, void(T::* Func)())
	{
		auto	iter = m_mapEvent.find(KeyName);

		if (iter != m_mapEvent.end())
		{
			iter->second.push_back(std::bind(Func, Obj));
		}

		else
		{
			std::list<std::function<void()>> List;

			List.push_back(std::bind(Func, Obj));

			m_mapEvent.insert(std::make_pair(KeyName, List));
		}

	}

private:
	void AddEventName(const std::string& KeyName)
	{
		auto iter = m_mapEvent.find(KeyName);

		if (iter == m_mapEvent.end())
		{
			std::list<std::function<void()>> List;

			m_mapEvent.insert(std::make_pair(KeyName, List));
		}
	}

private:
	void ShakeOn();

	DECLARE_SINGLE(CEventManager)
};


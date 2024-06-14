#include "SpawnManeger.h"

void Spawn::Update()
{
	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->Update();
	}
}

void Spawn::Draw()
{
	for (int i = 0; i < m_objList.size(); ++i)
	{
		m_objList[i]->DrawUnLit();
	}
}

void Spawn::Init()
{

}

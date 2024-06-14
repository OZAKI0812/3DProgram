#include "Sun.h"

void Sun::Update()
{
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);
}

void Sun::Init()
{
	m_model->Load("Asset/Data/LessonData/Planets/sun.gltf");
}

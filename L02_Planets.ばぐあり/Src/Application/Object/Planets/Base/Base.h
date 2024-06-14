#pragma once

class  PlanetBase :public KdGameObject
{
public:
	PlanetBase(){}
	~PlanetBase()override {}

	void Update()override;
	void DrawLit()override;
protected:
	void Init()override;
	KdModelData *m_model;
}
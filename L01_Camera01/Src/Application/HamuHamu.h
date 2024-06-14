#pragma once

class HamuHamu :public KdGameObject
{
public:
	HamuHamu();
	~HamuHamu()override;

	void Init()override;
	void Update()override;
	void DrawLit()override;
	//overrideは省略できるが、overrideは付けよう

private:
	std::shared_ptr<KdSquarePolygon>m_spPoly = nullptr;
};
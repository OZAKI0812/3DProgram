#pragma once
#include"../Base/Base.h"
class Sun:public PlanetBase
{
public:
	Sun() { Init(); }
	~Sun()override{}

	void Update()override;
	void DrawLit()override;
private:
	void Init()override;
};


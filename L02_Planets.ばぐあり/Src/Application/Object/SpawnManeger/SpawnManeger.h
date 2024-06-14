#pragma once;
class KdGameObject;
class Spawn
{
public:
	void Update();
	void Draw();
private:
	void Init();
	std::vector<std::shared_ptr<KdGameObject>>m_objList;
private:
	Spawn() { Init(); }
	~Spawn() {}
public:
	static Spawn& GetInstance()
	{
		static Spawn instance;
		return instance;
	}
};
#define SPAWN Spawn::GetInstance()
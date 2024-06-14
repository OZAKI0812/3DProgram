#include "Character.h"
#include"../../main.h"
#include"../../main.h"
void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Character::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		//①マウス座標を取得する
		POINT _mousePos;
		GetCursorPos(&_mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

		std::shared_ptr<KdCamera>_camera = m_wpCamera.lock();
		if (_camera)
		{
			Math::Vector3 _camPos = _camera->GetCameraMatrix().Translation();
			Math::Vector3 _rayDir = Math::Vector3::Zero;
			float _rayRange = 100;
			//②レイの発射方向を求める(_rayDir)
			_camera->
				GenerateRayInfoFromClientPos(_mousePos, _camPos, _rayDir, _rayRange);

			//③実際にレイを飛ばして衝突位置を求める
			const std::shared_ptr<KdGameObject>_terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				Math::Vector3 _endRayPos = _camPos + (_rayDir * _rayRange);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, _camPos, _endRayPos);
				//実際の当たり判定の処理
				std::list<KdCollider::CollisionResult>_results;
				_terrain->Intersects(_rayInfo,&_results);
				//欠課が１つでも返って来ていたら
				if (_results.size())
				{
					for (const KdCollider::CollisionResult& results : _results)
					{
						m_TargetPos = results.m_hitPos;
					}
				}
			}
		}
	}
	// キャラクターの移動速度(真似しちゃダメですよ)
	float			moveSpd = 0.05f;
	Math::Vector3	nowPos = GetPos();
	Math::Vector3	moveVec = m_TargetPos - nowPos;

	if (moveVec.Length() < moveSpd)moveSpd = moveVec.Length();	//大量に使うと重い
	//if (moveVec.LengthSquared() < moveSpd)moveSpd = moveVec.Length();
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}


/*if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }*/

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	
	std::shared_ptr<KdCamera>spCamera = m_wpCamera.lock();
	if (spCamera)
	{
		Math::Vector3 pos = GetPos();
		Math::Vector3 resultPos = Math::Vector3::Zero;
		spCamera->ConvertWorldToScreenDetail(pos, resultPos);

		KdShaderManager::Instance().m_spriteShader.DrawCircle(resultPos.x, resultPos.y+100, 10, &kRedColor);
	}
}
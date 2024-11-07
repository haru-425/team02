#include "enemy.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/input_manager.h"
#include "../GameLib/obj2d_data.h"

#include <windowsx.h>
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "system.h"



#include <vector>
#include <algorithm>



using namespace input;

// �v���C���[�̏�Ԃ��Ǘ�����ϐ�
int enemy_state;
int enemy_timer;
enum class ENEMY_TYPE {
	JUMP,
};
class ENEMY {
private:
public:
	ENEMY_TYPE type;
	int timer;

	float angle;
	float speed;
	float trackingRange;
	VECTOR2 BasePosition;
	VECTOR2 position;
	float initialSpeed;
	VECTOR2 scale;
	VECTOR2 texPos;
	VECTOR2 texSize;
	VECTOR2 pivot;
	VECTOR4 color;

	ENEMY(VECTOR2 pos, float angl, float ini_Speed) {
		timer = 0;
		BasePosition = pos;
		angle = angl;
		initialSpeed = ini_Speed;
		position = pos + launch_alculate_position(initialSpeed, angle, 0);
		type = ENEMY_TYPE::JUMP;
		scale = { E_SCALE, E_SCALE };
		texPos = { ENEMY_TEX_W * int(type), 0 };
		texSize = { ENEMY_TEX_W, ENEMY_TEX_H };
		pivot = { ENEMY_PIVOT_X, ENEMY_PIVOT_Y };
		color = { 1.000f, 1.0f, 1.0f, 1.0f };
		trackingRange = 0;
		speed = 0;
	}


};

float spawnPointIncreaseValue = 1;
VECTOR2 spawnPoint;

std::vector<ENEMY> enemy;
//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void enemy_init()
{
	// �v���C���[�̏�Ԃ�������
	enemy_state = 0;
	enemy_timer = 0;
	spawnPoint = { 0,float(SCREEN_H) };
}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void enemy_deinit()
{
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void enemy_update()
{
	switch (enemy_state)
	{
	case 0:
		//////// �����ݒ� ////////

		// ���̏�ԂɑJ��
		++enemy_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////

		// ���̏�ԂɑJ��
		++enemy_state;
		/*fallthrough*/

	case 2:
		enemy_act();
		enemy_timer++;
		if (enemy_timer % 60 == 0)
		{

			enemy.push_back(ENEMY(spawnPoint, 2.0f, 0.0f));
		}
		break;
	}
}

//--------------------------------------
//  �v���C���[�̕`�揈��
//--------------------------------------
void enemy_render()
{
	std::for_each(enemy.begin(), enemy.end(), [](ENEMY i) {


		});

	//�ȉ�debagu�p
	for (auto& enemy : enemy) {

		debug::setString("enemy[]%d:pos%f.%f", enemy.timer, enemy.position.x, enemy.position.y);
	}

	debug::setString("enemytimer%d", enemy_timer);
}
//--------------------------------------
//  �v���C���[�̍s������
//--------------------------------------
void enemy_act()
{
	spawnPoint.x += spawnPointIncreaseValue;
	if (spawnPoint.x <= 0 || spawnPoint.x >= SCREEN_W)
	{
		spawnPointIncreaseValue *= -1;
	}

	//�v�f���������[�v
	for (auto& enemy : enemy) {
		enemy.timer++;
		enemy.position = enemy.BasePosition + launch_alculate_position(enemy.initialSpeed, enemy.angle, enemy.timer);
	}
	enemy.erase(std::remove_if(enemy.begin(), enemy.end(),
		[](const ENEMY& enemy)
		{
			return enemy.position.y > SCREEN_H + 20;
		}),
		enemy.end());
}

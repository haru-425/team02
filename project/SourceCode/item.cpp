#include "item.h"
#include "../GameLib/game_lib.h"
#include "../GameLib/input_manager.h"
#include "../GameLib/obj2d_data.h"

#include <windowsx.h>
#include "common.h"
#include "audio.h"
#include "m_scene.h"
#include "system.h"
#include <time.h>
#include<stdlib.h>


#include <vector>
#include <algorithm>

Sprite* sprItem;

using namespace input;

// �v���C���[�̏�Ԃ��Ǘ�����ϐ�
int item_state;
int item_timer;

std::vector<ITEM> item;
//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void item_init()
{
	// �v���C���[�̏�Ԃ�������
	item_state = 0;
	item_timer = 0;

}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void item_deinit()
{

	safe_delete(sprItem);

}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void item_update()
{
	switch (item_state)
	{
	case 0:
		//////// �����ݒ� ////////
		sprItem = sprite_load(L"./Data/Images/Entity/Enemy/Enemy.png");
		// ���̏�ԂɑJ��
		++item_state;
		/*fallthrough*/

	case 1:
		//////// �p�����[�^�̐ݒ� ////////
		item_spawn({ 380.0f,380.0f }, ITEM_TYPE::ExplosionRangeCloseUp, 100.0f);
		// ���̏�ԂɑJ��
		++item_state;
		/*fallthrough*/

	case 2:
		item_act();

		item_timer++;
		break;
	}
}

//--------------------------------------
//  �v���C���[�̕`�揈��
//--------------------------------------
void item_render()
{
	for (auto& items : item) {
		//primitive::circle(items.position.x, items.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
		sprite_render(sprItem,
			items.position.x + 5, items.position.y - 5,
			items.scale.x, items.scale.y,
			items.texPos.x, items.texPos.y,
			items.texSize.x, items.texSize.y,
			items.pivot.x, items.pivot.y,
			items.angle,
			items.color.x, items.color.y, items.color.z, items.color.w);

	}

}
//--------------------------------------
//  �v���C���[�̍s������
//--------------------------------------
void item_act()
{
	for (auto& items : item) {
		//primitive::circle(enemy.position.x, enemy.position.y, 15, 1, 1, 0, 1, 0.4f, 0.6f, 1.0f);
		items.timer -= 1.0f;
		items.scale -= { 1.0f / items.timer, 1.0f / items.timer };
	}



	auto item_it = std::remove_if(item.begin(), item.end(),
		[](const ITEM& items) { return items.scale.x <= 0; });
	item.erase(item_it, item.end());
}



void item_spawn(VECTOR2 _pos, ITEM_TYPE _type) {
	item.push_back(ITEM(_pos, _type, 60 * 3.0f));
}
void item_spawn(VECTOR2 _pos, ITEM_TYPE _type, float _time) {

	item.push_back(ITEM(_pos, _type, 60.0f * _time));
}

//------< インクルード >---------------------------------------------------------
#include "scene_tutorial.h"
//------< 定数 >----------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
S_SCENE tutorial_state;
int tutorial_timer;
int tutorial_progress;
float tutorial_clicktime = 0;
float tutorial_force = 0.0f;
float tutorial_angle = 0.0f;
float tutorial_click_times = 0;
VECTOR3 tutorial_color;
PLAYER tutorial_player;
extern Bomb bomb;
extern std::vector<Bomb_range> range_Box;
Button next_button;
Button return_button;
extern Sprite* sprFRAME_GAME;
extern Sprite* sprBG_GAME;
extern Sprite* sprBG_TITLE;
extern Sprite* sprEnemy;
Sprite* tutorial_No1;
Sprite* tutorial_No2;
Sprite* tutorial_No3;
Sprite* tutorial_No4;
Sprite* tutorial_No5;

void tutorial_init()
{
	tutorial_progress = 0;
	tutorial_timer = 0;
	tutorial_state.state = tutorial_state.INITIALIZE;
	tutorial_click_times = 0;
	next_button.tutorial_next_button_set();
	return_button.tutorial_buck_button_set();
}
void tutorial_deinit()
{
	safe_delete(sprFRAME_GAME);
	safe_delete(sprBG_GAME);
	safe_delete(tutorial_No1);
	safe_delete(tutorial_No2);
	safe_delete(tutorial_No3);
	safe_delete(tutorial_No4);
	safe_delete(tutorial_No5);
	safe_delete(sprEnemy);
	//music::stop(0);

}

void tutorial_update()
{
	switch (tutorial_state.state)
	{
	case tutorial_state.INITIALIZE:
		tutorial_state.state = tutorial_state.B_TRANSIATON;
		sprFRAME_GAME = sprite_load(L"./Data/Images/BG/frame2.png");
		sprBG_GAME = sprite_load(L"./Data/Images/BG/game.png");
		sprBG_TITLE = sprite_load(L"./Data/Images/BG/title01.png");
		sprEnemy = sprite_load(L"./Data/Images/Entity/Enemy/Enemy.png");
		tutorial_No1 = sprite_load(L"./Data/Images/UI/tutorial_1.png");
		tutorial_No2 = sprite_load(L"./Data/Images/UI/tutorial_2.png");
		tutorial_No3 = sprite_load(L"./Data/Images/UI/tutorial_3.png");
		tutorial_No4 = sprite_load(L"./Data/Images/UI/tutorial_4.png");
		tutorial_No5 = sprite_load(L"./Data/Images/UI/tutorial_5.png");
	case tutorial_state.B_TRANSIATON:
		if (true)
		{
			tutorial_state.state = tutorial_state.PARAMETER;
		}
		break;

	case tutorial_state.PARAMETER:

		GameLib::setBlendMode(Blender::BS_ALPHA);

		tutorial_state.state = tutorial_state.NORMAL;

	case tutorial_state.NORMAL:

		switch (tutorial_progress)
		{
		case 0://初期化
			tutorial_player.player_time = 0;
			tutorial_player.position = VECTOR2(500.0f, 350.0f);
			tutorial_player.strat_position = player.position;
			tutorial_player.hp = PLAYER_MAX_HP;
			tutorial_player.damege_invincible = false;
			tutorial_player.bomb_reinforce_item = 0;
			tutorial_progress++;
			bomb_init();
		case 1:
			tutorial_player.player_time = 0.1f;
			player_act(tutorial_player);
			bomb_update(tutorial_player);
			if (STATE(0) & L_CLICK && tutorial_clicktime <= BOMB_MAX_CHARGE)
			{
				tutorial_clicktime += 0.2;
			}
			if (TRG_RELEASE(0) & L_CLICK)
			{
				tutorial_clicktime = 0;
			}
			break;

		case 2:
			tutorial_player.player_time = 0;
			tutorial_player.position = VECTOR2(500.0f, 350.0f);
			tutorial_player.strat_position = player.position;
			tutorial_player.hp = PLAYER_MAX_HP;
			tutorial_player.damege_invincible = false;
			tutorial_player.bomb_reinforce_item = 0;
			tutorial_progress++;
		case 3:
			tutorial_player.player_time += 0.1f;
			player_act(tutorial_player);
			bomb_update(tutorial_player);
			if (STATE(0) & L_CLICK && tutorial_clicktime <= BOMB_MAX_CHARGE)
			{
				tutorial_clicktime += 0.2;
			}
			if (TRG_RELEASE(0) & L_CLICK)
			{
				tutorial_clicktime = 0;
			}
			break;
		case 4:
			bomb_deinit();
			enemy_init();
			tutorial_player.position = VECTOR2(5000.0f, 3500.0f);
			tutorial_player.strat_position = player.position;
			tutorial_progress++;
		case 5:
			enemy_update();
			break;

		case 6:
			tutorial_timer++;
			enemy_update();
			if (tutorial_timer % 800 == 0) magnetic_force = { rand() % 1000 / 100.0f - 5.0f,rand() % 1000 / 1000.0f - 0.5f };
			break;
		case 7:
			enemy_deinit();
			tutorial_progress++;
		case 8:

			if (return_button.rect_click(return_button) && TRG_RELEASE(0) & L_CLICK)//タイトル画面への移動ボタン
			{
				tutorial_state.state = tutorial_state.F_TRANSITION;
			}
			break;
		default:
			break;
		}
		if (next_button.rect_click(next_button) && TRG_RELEASE(0) & L_CLICK&& tutorial_progress!=8)
		{
			tutorial_progress++;
		}
		debug::setString("%d", tutorial_progress);
		break;
	case tutorial_state.F_TRANSITION:
		if (tutorial_timer >= 240)
		{
			nextScene = SCENE_TYPE::TITLE;
		}

	}
	tutorial_timer++;
}


void tutorial_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);
	
	sprite_render(sprBG_GAME, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f);

	if (STATE(0) & L_CLICK && tutorial_clicktime&& bomb.bomb_state==0)
	{
		primitive::circle(tutorial_player.position.x, tutorial_player.position.y, BOMB_BLAST_MAX_INIT_RANGE + (tutorial_clicktime * 5), 1, 1, 0, 0.0f, 0.2f, 0.4f, 0.2f);
	}
	primitive::circle(tutorial_player.position.x, tutorial_player.position.y, 10, 1, 1, 0, 1, 0, 1);

	for (auto& range : range_Box) {
		primitive::circle(range.judg_position.x, range.judg_position.y, range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, range.bomb_blast_range / range.bomb_blast_max_range, 0, 1, 1, 1, 0.2f);
	}

	primitive::circle(tutorial_player.position.x, tutorial_player.position.y, BOMB_BLAST_MAX_INIT_RANGE + (tutorial_click_times * 5), 1, 1, 0, 0.0f, 0.2f, 0.4f, 0.2f);

	primitive::circle(bomb.bomb_position.x, bomb.bomb_position.y, 10, 1, 1);
	
	for (int i = 0; i < 120; i++)
	{
		primitive::circle(edge_reflecting(
			tutorial_player.position + LaunchCalculatePosition(
				-tracking(
					cursor_position(
					), tutorial_player.position
				), bomb.bomb_speed, i * 0.5f
			)
		).x,
			edge_reflecting(tutorial_player.position + LaunchCalculatePosition(-tracking(cursor_position(), tutorial_player.position), bomb.bomb_speed, i * 0.5f)).y,
			3,
			1, 1,
			0,
			1, 1, 1, 0.5f);
	}
		if (tutorial_progress==5|| tutorial_progress == 6)
		{
			enemy_render();
		}
	sprite_render(sprFRAME_GAME, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f, 0, 0, 1920, 1080);
	
	primitive::rect(1030, 640, 100, 40);
	switch (tutorial_progress)
	{
	case 1:
		sprite_render(tutorial_No1, 680, -15);
		break;

	case 3:
		sprite_render(tutorial_No2, 680, 0);
		break;
	case 5:
		sprite_render(tutorial_No3, 720, 0);
		break;

	case 6:
		sprite_render(tutorial_No4, 720, 0);
		break;
	case 8:
		sprite_render(sprBG_TITLE, 0, 0);
		primitive::rect(0, 0, 1280, 720, 0, 0, 0, 0, 0, 0, 0.8);
		sprite_render(tutorial_No5, 0, 0);
		primitive::rect(880, 640, 100, 40);
		break;
	default:
		break;
	}
}

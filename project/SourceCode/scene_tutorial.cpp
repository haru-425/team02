//------< インクルード >---------------------------------------------------------
#include "scene_tutorial.h"
//------< 定数 >----------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
S_SCENE tutorial_state;
int tutorial_timer;
int tutorial_progress;
float tutorial_force = 0.0f;
float tutorial_angle = 0.0f;
float tutorial_click_times = 0;
VECTOR3 tutorial_color;
PLAYER tutorial_player;
extern Bomb bomb;
extern std::vector<Bomb_range> range_Box;
Button next_button;
Button buck_button;
extern Sprite* sprFRAME_GAME;

void tutorial_init()
{
	tutorial_progress = 0;
	tutorial_timer = 0;
	tutorial_state.state = tutorial_state.INITIALIZE;
	tutorial_click_times = 0;
	next_button.tutorial_next_button_set();
	buck_button.tutorial_buck_button_set();
}
void tutorial_deinit()
{

	//music::stop(0);

}

void tutorial_update()
{
	switch (tutorial_state.state)
	{
	case tutorial_state.INITIALIZE:
		tutorial_state.state = tutorial_state.B_TRANSIATON;
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
			tutorial_progress=2;
			bomb_init();
		case 1:
			player_act(tutorial_player);
			bomb_update();
			break;
		case 2:
			player_act(tutorial_player);
			bomb_update();
			break;
		default:
			break;
		}

		break;
	case tutorial_state.F_TRANSITION:
		if (tutorial_timer >= 240)
		{
			nextScene = SCENE_TYPE::GAME;
		}

	}
	tutorial_timer++;
}


void tutorial_render()
{
	// 画面を青で塗りつぶす
	GameLib::clear(0.3f, 0.5f, 1.0f);
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
	primitive::rect(800,500,100,50);
	sprite_render(sprFRAME_GAME, 0, 0, SCREEN_W / 1920.0f, SCREEN_H / 1080.0f, 0, 0, 1920, 1080);
}

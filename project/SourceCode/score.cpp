
#include "m_scene.h"

int score = 0;

int dia_timer;

extern float SCORE_DIAMETER = 1;

void score_init() {
	dia_timer = 0;
}

void score_act();
void score_update() {
	score_act();
}
void score_render() {

	switch (curScene)
	{
	case SCENE_TYPE::START:
		break;

	case SCENE_TYPE::TITLE:
		break;

	case SCENE_TYPE::GAME:
		//debug::setString("score%d", score);
		break;

	case SCENE_TYPE::TUTORIAL:
		break;
	}


}
void score_deinit() {
	switch (curScene)
	{
	case SCENE_TYPE::START:
		break;

	case SCENE_TYPE::TITLE:
		break;

	case SCENE_TYPE::GAME:
		break;

	case SCENE_TYPE::TUTORIAL:
		break;
	}

}
void score_act() {
	switch (curScene)
	{
	case SCENE_TYPE::START:

		break;

	case SCENE_TYPE::TITLE:
		break;

	case SCENE_TYPE::GAME:
		if (dia_timer >= 0)
		{
			dia_timer--;
			ITEM_EFFECT_TRANSPARENCY[int(ITEM_TYPE::ScoreTwoTimes)] = 1.0f;
		}
		else
			ITEM_EFFECT_TRANSPARENCY[int(ITEM_TYPE::ScoreTwoTimes)] = 0.1f;
		if (dia_timer == 0)
		{
			SCORE_DIAMETER = 1;
		}
		break;

	case SCENE_TYPE::TUTORIAL:
		break;
	}

}
void score_set(int _score) {

	score = _score;

}

void score_add(int _score) {

	score += _score * SCORE_DIAMETER;

}
void score_diameter_set(int _diameter, int _time) {
	SCORE_DIAMETER = _diameter;
	dia_timer = _time;
}

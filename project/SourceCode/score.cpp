
#include "m_scene.h"

int score = 0;



extern float SCORE_DIAMETER = 1;

void score_init() {

}
void score_update() {

}
void score_render() {

	switch (curScene)
	{
	case SCENE_TYPE::START:
		break;

	case SCENE_TYPE::TITLE:
		break;

	case SCENE_TYPE::GAME:
		debug::setString("score%d", score);
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
void score_diameter_set(int _diameter) {
	SCORE_DIAMETER = _diameter;
}

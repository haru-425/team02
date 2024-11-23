#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

// 定数の定義
//
enum BGM {
	BGM_TITLE,
	BGM_GAME,
	BGM_RESULT,
};
// XWBの種類
#define XWB_SOUNDS          0

// SYSTEMの効果音
#define XWB_SOUND_HIT     0
#define XWB_SOUND_THROW     1
#define XWB_SOUND_ITEM_ACQUISITION     2
#define XWB_SOUND_BOMB     3
#define XWB_SOUND_BUTTON     4
#define XWB_SOUND_RETURN_BUTTON     5
#define XWB_SOUND_FIRE     6
#define XWB_SOUND_HEALING     7

// 関数のプロトタイプ宣言
void audio_init();
void audio_deinit();

#endif//AUDIO_H

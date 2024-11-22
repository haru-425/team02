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
#define XWB_SYSTEM          0
#define XWB_STAGE1          1

#define XWB_LIVE            2

// SYSTEMの効果音
#define XWB_SYSTEM_KATI     0
#define XWB_SYSTEM_START    1

// STAGE1の効果音
#define XWB_STAGE1_COIN     0
#define XWB_STAGE1_JUMP     1
#define XWB_STAGE1_SHOT     2
#define XWB_STAGE1_MISSILE  3
#define XWB_STAGE1_LASER    4

// LIVEの効果音
#define XWB_quiz1           0
#define XWB_tin             1
#define XWB_pi              2
#define XWB_quiz2           3
#define XWB_quiz3           4

// 関数のプロトタイプ宣言
void audio_init();
void audio_deinit();

#endif//AUDIO_H

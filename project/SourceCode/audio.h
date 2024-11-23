#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

// �萔�̒�`
//
enum BGM {
	BGM_TITLE,
	BGM_GAME,
	BGM_RESULT,
};
// XWB�̎��
#define XWB_SOUNDS          0

// SYSTEM�̌��ʉ�
#define XWB_SOUND_HIT     0
#define XWB_SOUND_THROW     1
#define XWB_SOUND_ITEM_ACQUISITION     2
#define XWB_SOUND_BOMB     3
#define XWB_SOUND_BUTTON     4
#define XWB_SOUND_RETURN_BUTTON     5
#define XWB_SOUND_FIRE     6
#define XWB_SOUND_HEALING     7

// �֐��̃v���g�^�C�v�錾
void audio_init();
void audio_deinit();

#endif//AUDIO_H

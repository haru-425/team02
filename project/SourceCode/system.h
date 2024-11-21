#pragma once
#include "../GameLib/game_lib.h"
#include "m_scene.h"
#include "audio.h"
#include "common.h"

#include <cmath>
#include <vector>


using namespace std;

extern VECTOR2 magnetic_force;

//trackingperson��target�����������̊p�x��Ԃ��֐�
float tracking(VECTOR2 target, VECTOR2 tracking_person);
//�x�N�g����P�ʃx�N�g����
VECTOR2 unit_vectorization(VECTOR2 vec);

//�����Ɗp�x���ƍ��̎��Ԃ�n���Ƃ��̎��̈ʒu��Ԃ�
VECTOR2 LaunchCalculatePosition(float angle, float force, float time);
VECTOR2 LaunchCalculatePosition(float angle, float force, float time, float gravity);

float LaunchCalculateRotation(float angle, float force, float time);
float LaunchCalculateRotation(float angle, float force, float time, float gravity);

VECTOR2 magnetic_force_suction(VECTOR2 target_BasePos, VECTOR2 magnetic_force);

VECTOR2 cursor_position();

VECTOR2 edge_reflecting(VECTOR2 pos);


//��]�����`�Ƃ̓����蔻��

bool intersectRectCircle(VECTOR2 rec_center, VECTOR2 size, float angle, VECTOR2 cir_center, float radius);//��]�����`�Ƌ�`�̓����蔻��

bool isColliding(VECTOR2 _center, VECTOR2  _size, VECTOR2 rot_center, VECTOR2  rot_size, float angle);
//--------------------------------------------------------------
// ��`�|���S���`��
//--------------------------------------------------------------
//VECTOR2 center		���S�_
//float	  radius		���a
//float	  startAngle	�J�n�p�x(Degree)
//float	  endAngle	�I���p�x(Degree)
//int	  polygon	�~�̕�����
//VECTOR4  color		�F (r, g, b, a)
//--------------------------------------------------------------
void draw_fan_triangle_quad(VECTOR2 center, float radius, float startAngle, float endAngle, int polygon, VECTOR4 color);

bool isCircleColliding(const VECTOR2 a_position, float a_radius, VECTOR2 b_position, float b_radius);

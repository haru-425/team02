#pragma once
//trackingperson��target�����������̊p�x��Ԃ��֐�
float tracking(VECTOR2 target, VECTOR2 tracking_person);
//�x�N�g����P�ʃx�N�g����
VECTOR2 unit_vectorization(VECTOR2 vec);

//�����Ɗp�x���ƍ��̎��Ԃ�n���Ƃ��̎��̈ʒu��Ԃ�
VECTOR2 LaunchCalculatePosition(float angle, float force, float time);

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

#pragma once
//trackingperson��target�����������̊p�x��Ԃ��֐�
float tracking(VECTOR2 target, VECTOR2 tracking_person);
//�x�N�g����P�ʃx�N�g����
VECTOR2 unit_vectorization(VECTOR2 vec);

//�����Ɗp�x���ƍ��̎��Ԃ�n���Ƃ��̎��̈ʒu��Ԃ�
VECTOR2 launch_alculate_position(double initialSpeed, double angle, double time);
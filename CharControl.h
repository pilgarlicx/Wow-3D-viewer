//1��27�� ���� ��Ҫ���������ģ�͵� ��ת �ƶ� ������
#ifndef _CHAR_CONTROL_H_
#define _CHAR_CONTROL_H_
#include <d3d9.h>
#include "enums.h"
#include "vector3d.h"
class CharacterModel;
//����Ǽ򵥵�Animate��  ��ʱ����ʵ��λ�ƺ���ת
class MyAnimate
{
public:
	//Ĭ�Ϲ��캯��
	MyAnimate(){
		is_anim_end_ = false; d_ = 0.1f;
	}
	//Speed Ϊ ÿ����ٵ�λ  d����� +- 0.1f Ĭ��
	MyAnimate(const Vec3D& start,const Vec3D& end,const Vec3D& speed,FLOAT d = 0.1f);
	//dt ms��λ ��� �Ѿ�����end �� ����end��״̬ dt msΪ��λ
	void Update(int dt);
	//�������ò���
	void ResetParam(const Vec3D& art,const Vec3D& end,const Vec3D& speed,FLOAT d = 0.1f);
	//�õ���ǰ��״̬
	Vec3D GetCurrent();
	//�����Ƿ����
	bool IsAnimEnd();
private:
	Vec3D start_;
	Vec3D end_;
	Vec3D current_;
	bool is_anim_end_;
	Vec3D speed_;
	FLOAT d_;
};
class CharControl
{
public:
	//��ǰ����Ġ�B �@���������S������
	enum CHAR_STATUS{
		CHAR_STATUS_STAND,  //ԭ�ز���
		CHAR_STATUS_RUN,  //�����Ƅ�
		CHAR_STATUS_ATTACK, //�����ƶ�
		CHAR_STATUS_CAST, //����ʩ��
	};
public:
	//1��28�ռ����� ��ʼλ�úͳ�ʼƫ��
	CharControl(CharacterModel& model,const Vec3D& position,const Vec3D& rotation):model_(model) {
		position_ = position;
		rot_ = rotation;
		current_anim_id_ = 19; //Run
		current_anim_frame_ = 0;
		time_last_ = -1;
		current_status_ = CHAR_STATUS_STAND;
		current_cast_ = NULL;
		current_spell_frame_ = 0;
	}
	//�����@����Ļ�ϵ��c �Ƿ���x�д�Ŀ��
	//distance ��ҕ�ǵ��@��ģ�͵ľ��x 
	//cord world �� ��������c���������� distance��cord_world�����Ԟ��
	bool IsIntersect(int x,int y,FLOAT* distance,Vec3D* cord_world);
	void Update();  //���� Char�ĸ��N��Ϣ
	void Draw(LPDIRECT3DDEVICE9 d3d_device);  //����ģ�ͺ͸��N����Ч��

	//�Ƅӵ�xyz �@�e�Ⱥ��ε��M�ЄӮ�
	void MoveTo(FLOAT x,FLOAT y,FLOAT z);
	//�����Test�õ� Attack һ��
	void Attack();
	//ͬ��
	void Cast(CharacterModel* current_cast);
private:
	CharacterModel& model_;
	int current_anim_id_; //��ǰ�ĄӮ�̖ ����]�ЄӮ� �t�O��-1
	int current_anim_frame_; //��ǰ�Ӯ��Ď���

	//������Ϣ
	MyAnimate pos_anim_;
	MyAnimate rot_anim_;

	//λ�úͽǶ���Ϣ
	Vec3D position_;
	Vec3D rot_;
	//�ϴ��ƄӄӮ������c
	Vec3D last_position_;
	//�����Ƅӵ�Ŀ�ĵ�
	Vec3D target_position_;

	//�ϴ΄Ӯ����ŵĕr�g
	int time_last_;

	//��ǰ������̎�Ġ�B
	CHAR_STATUS current_status_;
	//��ǰ�����ͷŵķ���
	CharacterModel* current_cast_;
	//��ǰ������֡��
	int current_spell_frame_;
};

#endif
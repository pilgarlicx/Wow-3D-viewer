#ifndef _RAY_H_
#define _RAY_H_
#include <d3d9.h>
#include <d3dx9math.h>
#include "vector3d.h"
#include "enums.h"
//�ȷ������� �Ժ������
#define D3DFVF_3VERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE )
struct V3VERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;        // The vertex color
};

//1��25�� �򵥵����߼��
class RayDetect
{
public:
	//x yΪ������ ����ꡱ��x y���� ������ڴ��ڵ�����
	RayDetect(int x,int y):x_(x),y_(y) {}
	//����Ƿ��ĳ��ģ���ཻ ����true ����distance��ֵ ���distance��λ��
	//������ཻ ����false distance��������޸�
	//vetexesΪ���� indexesΪ������ ÿ3����һ��������
	//������ 123 2 3 4 ����2�������� �����Ϊ�˺�Model��BoundingVolumn��Ӧ
	//1��29�� coords_world �ļ��� ���Ԟ�� �齻�c����������
	// Vec3D char_potion Vec3D char_rotation  �� ��ǰ��������������׃�Q�����D 
	// �Դˁ�õ�����׃�Q��� ������ͨ�^d3ddevice �@����춙z�y����ԭ�c������ ���r��Ψһ���k��
	// If char_pos and char_rot. either is NULL ,We'll use The D3dDevice as the way to get
	// the world matrix
	bool Intersect(Vec3D* vetexes,int num_vetexes,uint16* indexes,int num_indexes,FLOAT* distance,Vec3D* coords_world,Vec3D* char_pos ,Vec3D* char_rot);
	//һ�����ذ汾 ����test  p_out Ϊ����
	bool Intersect(V3VERTEX* vetexes,int num_vetexes,FLOAT* distance,D3DXVECTOR3* p_out);


private:
	//����x y��ֵ �����һ������ ������ߵ����걻ת�������������� �±ߵķֱ���Ӧ����
	//����������任 �ӽǱ任 ͶӰ�任����
	//1��29�ոĄ� ���world_matrix Not NULL �t�����~����world matrix ��t��d3d device��
	void Dir(D3DXMATRIX* new_world_matrix);
	int x_;
	int y_;
	D3DXVECTOR3 ray_position_; //�������
	D3DXVECTOR3 ray_dir_;  //���߷���
};
#endif
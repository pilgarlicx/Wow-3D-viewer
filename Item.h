//1��17�� ���������Ⱦ item ������ĳ������ʲô��
//��Ϊ���ܺ�Character�Ĵ�����ͬ �������ȼ̳��� Character
#ifndef _ITEM_H_
#define _ITEM_H_
#include "enums.h"
#include "Character.h"

class ItemModel:public CharacterModel
{
public:
	ItemModel(const wxString& model_name,LPDIRECT3DDEVICE9 device):CharacterModel(model_name,device){}
	virtual void Draw();
protected:
	//��д�⼸�������� ʹ��ʲôҲ����
	virtual void InitBodyTexture(MPQFile& f,MPQFile& g);
	//��ʼ�� Hair������ ԭ��������Body
	virtual void InitHairTexture(MPQFile& f,MPQFile& g);
	//��ʼ�� Capde������ ������Body
	//����Item��˵ Cape����TextureItem
	virtual void InitCapeTexture(MPQFile& f,MPQFile& g);
	//1��29����д
	virtual void calcBones(ssize_t anim, size_t time);

};



#endif
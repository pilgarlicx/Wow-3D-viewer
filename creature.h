#ifndef _CREATURE_H_
#define _CREATURE_H_
//1��18�� Ԓ�����
#include "enums.h"
#include "Character.h"

class CreatureModel:public CharacterModel
{
public:
	CreatureModel(const wxString& model_name,LPDIRECT3DDEVICE9 device):CharacterModel(model_name,device){}
	virtual void Draw();
protected:
	//��д�⼸�������� ʹ��ʲôҲ����
	virtual void InitBodyTexture(MPQFile& f,MPQFile& g);
	//��ʼ�� Hair������ ԭ��������Body
	virtual void InitHairTexture(MPQFile& f,MPQFile& g);
	//��ʼ�� Capde������ ������Body
	//����Item��˵ Cape����TextureItem
	virtual void InitCapeTexture(MPQFile& f,MPQFile& g);

};

#endif
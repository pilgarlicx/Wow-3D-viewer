#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//1��16�� ��Ҫ������������ģ��
//ToDO�� ������� ��NPC��ģ�͹���һЩ����
#include "mpq.h"
#include "raw_model.h"
#include "vector3d.h"
#include "wx/wx.h"
#include "animated.h"
#include "enums.h"
#include "texture.h"
#include "bone.h"

//ͨ�^һ����λ ������ �ϳ�һ���µļy���ļ�������Ϣ
wxString makeItemTexture(int region, const wxString name);
class ParticleSystem;
class RibbonEmitter;
class TextureAnim;
class CharControl;
class CharacterModel
{
public:
	//���Modelname Ӧ���� Character\\Bloodelf\\female\\bloodelffemale.m2 ����
	CharacterModel(const wxString& model_name,LPDIRECT3DDEVICE9 device):model_name_(model_name),d3d_device_(device){
		vetex_buffer_ = NULL;index_buffer_ = NULL;hasParticles_ = false;bounding_buffer_ = NULL;bounding_index_ = NULL;bounds = NULL;boundTris = NULL;
		current_anim_frame_ = 0;
	}
	//��ʼ��ģ�� ����ֻ�о�̬�� ������Ϣʲô���Ժ�̬ģ�͸㶨��˵
	//������ʼ������ index �������� �����
	void Init(); 
	//�����ʼ������ ���������Ӧ�������� ����Ϊ�˷��� ��ʱ�ŵ����� ��������һ��protype
	void InitAnimation();
	//Animate ������Ƴ��@����� �{����Ⱦ��һ�� //�@�e���漰����cλ�õ�׃��
	//frame ָ��Ҫ���ڼ�֡ ��caller��֤frame����Խ��
	void Animate(int anim_id,int frame); 
	//�����ʼ�����Ӻ�ribbonϵͳ ribbon���ڲ�����
	void InitParticle();
	//�������ӵ�״̬  ���� Ϊ ���Ӷ��� ����Ĳ���Ӧ��Ϊ��һ֡��ʱ������ms�� /1000.0
	void UpdateParticle(FLOAT dt);
	//�@����animate()�б��{�� �������е�Bones 1��29 ItemModel��д�˺���
	virtual void calcBones(ssize_t anim, size_t time);
	//����ģ�� �F��ֻ���o�Bģ�� ����ֻ���@һ���������r TODO ���ӄӮ���Ϣ
	virtual void Draw();
	//1��24�� ���� ���������ײ����Bounding Triangles�Ļ���
	void DrawBoundingVolume();

	//1��25��
	//����Ƿ��ཻ ����ӡһЩ��Ϣ
	//��������������ʱ�򱻵���
	//�����ǵ���Ļ�ϵĵ�ͨ��GetCurrentPos Ȼ��ScreenToClient�õ�
	//1��28�� ԭ�θ�׃
	//����ཻ ����distance ���������˵Ľ��c distance ��cords_world���Ԟ��
	//x y ����Ļ������(���ڣ�
	bool InterSect(int x,int y,FLOAT* distance,Vec3D* cords_world,Vec3D* char_pos,Vec3D* char_rot);

	//1��27�ռ��� ����anim��id һ���м�֡��
	uint32 FrameCount(int anim_id);
	

protected:
	//��������Ժ��Ǽ̳���Model�� �����±ߺ��������Ǽ̳����� 
	//��д��protected
	//��ʼ������
	//f��ģ�͵�MPQ�ļ�
	void InitVertex(MPQFile& f);
	//��ʼ������
	//f��ģ�͵�MPQ�ļ� gӦ����ģ�͵�һЩLOD��Ϣ ����ʲô����������Ӧ�ö�������ļ���
	void InitIndex(MPQFile& f,MPQFile& g);
	//��ʼ������
	void InitTexture(MPQFile& f,MPQFile& g);
	//��ʼ��GeoSet �� Passes
	void InitGeoSet(MPQFile& f,MPQFile& g);
	//��ʼ�� Body������ ��InitTexture�е��� ����漰�������Blend
	virtual void InitBodyTexture(MPQFile& f,MPQFile& g);
	//��ʼ�� Hair������ ԭ��������Body
	virtual void InitHairTexture(MPQFile& f,MPQFile& g);
	//��ʼ�� Capde������ ������Body
	virtual void InitCapeTexture(MPQFile& f,MPQFile& g);
	//��ʼ��Bounding����Ϣ ��Init�б�����
	virtual void InitBounding(MPQFile& f,MPQFile& g);

	//���������� �������� ��ɫ �������� д�� ��Ⱦ�豸��
	void FillVetex(MPQFile& f);
	//����Index
	void FillIndex(MPQFile& f,MPQFile& g);
	//��Ҫ����������Ĵ���
	void FillTexture(MPQFile& f,MPQFile& g);
protected:  
	//ģ����  ���ǹ��캯���е� ����Character ��������.m2���Ǹ�
	wxString model_name_;
	//�������������ͷ����Ϣ
	ModelHeader model_header_;
	Vec3D* vertices_;  //��������
	Vec2D* texCoords;  //��c�y������
	Vec3D* normals_;  //����������
	ModelColor* colors_;  //��ɫ
	ModelTransparency* trans_; //͸����Ϣ
	uint32			*globalSequences_; //��֪����ʲô��
	int count_vetices_; //��c�Ĕ���
	uint16* indices_ ;  //����
	int count_indices_; //index number
	float rad; //�뾶
	unsigned int * textures_; //�����id����
	wxArrayString TextureList; //����texture���ֵģ�debug��֪����
	int specialTextures[TEXTURE_MAX];  //�����texture ֻ��������ģ������
	unsigned int replaceTextures[TEXTURE_MAX];
	bool useReplaceTextures[TEXTURE_MAX];
	//ģ������
	ModelType modelType;

	// ���ÿ��Ҫ��Ⱦ�ĵط���ͬ �����RenderPass�@���
	std::vector<ModelRenderPass> passes_;
	std::vector<ModelGeoset> geosets_;

	//���ﱣ����� Animation��Ϣ �Ժ�Ҫ�ŵ�AnimModel���������
	ModelAnimation *anims; //�����
	int16 *animLookups;
	Bone *bones;
	MPQFile *animfiles;
	uint32			*globalSequences;  //�@����������ʲ�N
	int16 keyBoneLookup[BONE_MAX];  //һ�� ��λ-�� ���^id��ӳ�䑪ԓ��
	//Particle And Ribbon ��Ϣ
	ParticleSystem* particleSystems_;
	bool hasParticles_;
	RibbonEmitter	*ribbons_;
	//���������
	uint16 *boundTris; //�����bounding��������
	Vec3D *bounds;   //����Ƕ��㼯��

	//texanmiation 1��26��
	TextureAnim		*texAnims;
	//1��29�� ��Ҫ������transparency�Ķ�������
	int current_anim_frame_;


protected:
	//��Щ�Ǻ�D3D�йص�
	LPDIRECT3DVERTEXBUFFER9 vetex_buffer_;
	LPDIRECT3DINDEXBUFFER9 index_buffer_;
	LPDIRECT3DDEVICE9      d3d_device_;

	//��ײ�����ص�
	LPDIRECT3DVERTEXBUFFER9 bounding_buffer_;
	LPDIRECT3DINDEXBUFFER9 bounding_index_;

	friend class ParticleSystem;
	friend class RibbonEmitter;
	friend class CharControl;
};



#endif
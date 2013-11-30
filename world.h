#ifndef _WORLD_H_
#define _WORLD_H_
#include <vector>
#include <map>
#include <wx/wx.h>
#include <d3d9.h>
#include <d3dx9shader.h>
#include "vector3d.h"

#define  UNITSIZE (1.0f)

//1��31�� Test�� 
//��Ⱦħ�F�еĵ��� ��֪���ܲ��ܳ��Y�� 
//2��3�� ���� ��Ҫ����춵�����Ⱦ�� shader 
//�Y���������f���^�T��
class World
{
public:
	//���캯�� ָ���ļ���
	//x_ y_ �� ���˳��
	//
	//����:
	// World("world\\maps\\Kalimdor\\Kalimdor_35_50",0,0)
	//
	World(char* name,int x,int y){
		start_x_ = x; 
		start_y_ = y;
		char buffer_name[1024];
		sprintf(buffer_name,"%s.adt",name);
		map_name_ = buffer_name;
		sprintf(buffer_name,"%s_tex0.adt",name);
		tex_0_name_ = buffer_name;
	}
	void InitShader();
	void Draw();
	void InitADT();
private:
	
	void PrepareAlphaMap();
	wxString map_name_;  //��ͼ������
	wxString tex_0_name_; //����tex0.adt�е�����
	//x_ y_����ȷ����ͼtile����ʼ����
	int start_x_,start_y_;
	

	//һЩ�洢����ı���
	std::vector<Vec3D> terrain_;
	std::vector<Vec3D> terrain_normal_;
	std::vector<Vec2D> terrain_uv_;
	LPDIRECT3DTEXTURE9      pTexture0_; // Our texture
	LPDIRECT3DTEXTURE9      pTexture1_; // Our texture
	LPDIRECT3DTEXTURE9      pTexture2_;
	//���λ �� tex1 ��͸���� ��֮�� tex2 ��֮�� tex3 ��һλ����
	//LPDIRECT3DTEXTURE9 alpha_texs_[64][64];

	//�@���� ��һ��Chunck texture id �� texture�ăȴ��е�id�Č�����
	std::map<int,int> tex_id_map;

	LPDIRECT3DVERTEXBUFFER9 terrain_buffer_pass0;  //�����ʱ�����Tile���еĶ���

	//�±���Shader��Ϣ ����Static ����
	static IDirect3DPixelShader9*  Terrain_shader;  //P shader
	static  IDirect3DVertexShader9*  Terrain_shader_vetex;  //V Shader

	static  D3DXHANDLE Samp0Handle;
	static  D3DXHANDLE Samp1Handle;
	static  D3DXHANDLE Samp2Handle;
	static  D3DXHANDLE Samp3Handle;
	static  D3DXHANDLE SampAlphaHandle;  //isolated
	//static  D3DXHANDLE AlphamapHandle;
	static  D3DXHANDLE SampShadowHandle;

	static  D3DXCONSTANT_DESC Samp0Desc;
	static  D3DXCONSTANT_DESC Samp1Desc;
	static  D3DXCONSTANT_DESC Samp2Desc;
	static  D3DXCONSTANT_DESC Samp3Desc;
	static  D3DXCONSTANT_DESC SampAlphaDesc;
	static  D3DXCONSTANT_DESC SampShadowDesc;

	//V Shader �Ĳ���
	static  D3DXHANDLE Vetex_matWorldViewProj;
	static  D3DXHANDLE Vetex_matInverseWorld;
	static  D3DXHANDLE Vetex_vLightDirection;

	static  LPD3DXCONSTANTTABLE TransformConstantTableVetex;
	//��Щ��Alpha Blend ��ص�
	std::vector<int> maps_;  //����� 16��16�� Chunck ����˳���Ӧ������id
	//�±��� �������йص�
	//�����ȼٶ� alpha map �� 32*64���ֽڵ� ÿ���ֽ���2��alpha ��Ӧ��64*64������ Ӧ�ö�Ӧ�����256��256 ��ÿ4*4���� ��һ��alpha  0��0 1111��1.0 1111��15
	FLOAT alpha_maps_[256][3][64][64];
 
	//�@��ӛ��� ÿ��alpha map  offset ==> �ڎׂ�alphamap��һһ����
	std::map<int,int> alpha_offset_to_index_[256];
	//�Q����ÿ����Ⱦ ��Ⱦ��Щ�y�� �Ўׂ��y��� ��֮ǰ��ö���0 ����Ч�������� ���Ժ��� ������Ҫ�õ�Vertex Shader
	struct _RenderTexture{
		int tex_layers;   //�м�������
		bool use_alpha_map; //�Ƿ�ʹ��alpha
		LPDIRECT3DTEXTURE9 textures[4];  //����Ĳ����� //û�о���NULL
		int map_to_alpha[4];  //һ��ӳ�� ��һ���Ӧ�ڼ���alpha_texture	 ���� g_alpha_offset_to_index Ӌ��
		LPDIRECT3DTEXTURE9 alpha_texture; //Alpha �� �����ʱ�Ķ�Ϊ D3DXVECTOR4
		//�Ƿ�ʹ�� shadow
		bool use_shadow;
		//shadow map ���� WowMapview �����ӦλΪ1�Ļ� shadow_map��ӦֵΪ85 ����AlphaMap�� ������Ӧ������
		unsigned  char shadow_map[64 * 64];
		LPDIRECT3DTEXTURE9 shadow_texture;

		//D3DXVECTOR4 alpha_maps[64*64]; 
	};

	_RenderTexture passes_[256];
	//��ȡ AlphaMap�ĺ���
	int ReadAlphaMapCompressed(char* buffer,size_t start_offset,int start,int which_map);
	int ReadAlphaMapUnCompressed(char* buffer,int start_offset,size_t alpha_map_size_byte,int start,int which_map);


public:
	static void InitPShader();
	static void InitVShader();
};




#endif


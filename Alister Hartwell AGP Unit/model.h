#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include "objfilemodel.h"


class Model
{
private:
	ID3D11Device*			m_pD3DDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ObjFileModel*			m_pObject;
	ID3D11VertexShader*		m_pVShader;
	ID3D11PixelShader*		m_pPShader;
	ID3D11InputLayout*		m_pInputLayout;
	ID3D11Buffer*			m_pConstantBuffer;

	float m_x, m_y, m_z;
	float m_xangle, m_zangle, m_yangle;
	float m_scale;

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context);

	ObjFileModel *m_pObject;

	int LoadObjModel(char* filename);

};
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
	float m_dx, m_dy, m_dz;
	XMVECTOR	m_directional_light_shines_from;
	XMVECTOR	m_directional_light_colour;
	XMVECTOR	m_ambient_light_colour;

	const float DegreesToRadian = 0.01745329251;
	const float RadianToDegrees = 57.2957795131; // Both of these constants are used to save on calculation times since division is expensive

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context);
	~Model();

	

	int LoadObjModel(char* filename);
	void Draw(XMMATRIX* view, XMMATRIX* projection);


	////////////////////////////////////////////////////////
	//Object manipulation
	////////////////////////////////////////////////////////


	//Set Functions
	void SetXPos(float x);
	void SetYPos(float y);
	void SetZPos(float z);

	void SetXRot(float x);
	void SetYRot(float y);
	void SetZRot(float z);

	void SetScale(float x);

	void SetLighting(XMVECTOR shineFrom, XMVECTOR colour, XMVECTOR ambientLight);
	

	//Get Functions
	float GetXPos();
	float GetYPos();
	float GetZPos();

	float GetXRot();
	float GetYRot();
	float GetZRot();

	float GetScale();

	XMVECTOR GetShineFrom();
	XMVECTOR GetLightColour();
	XMVECTOR GetAmbientLight();

	//Incremental Functions
	void IncXPos(float x);
	void IncYPos(float y);
	void IncZPos(float z);

	void IncXRot(float x);
	void IncYRot(float y);
	void IncZRot(float z);

	void IncScale(float x);

	void LookAt_XZ(float x, float z);

};
#include "model.h"

struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;	//64 Bytes
	XMVECTOR directional_light_vector; //16 Bytes
	XMVECTOR directional_light_colour; //16 Bytes
	XMVECTOR ambient_light_colour; //16 Bytes
}; //Total size = 112 Bytes


Model::Model(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_pD3DDevice = device;
	m_pImmediateContext = context;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 10.0f;

	m_xangle = 0.0f;
	m_yangle = 0.0f;
	m_zangle = 0.0f;

	m_scale = 1.0f;



}

Model::~Model()
{
	delete m_pObject;

	if (m_pInputLayout)			 m_pInputLayout->Release();
	if (m_pVShader)				 m_pVShader->Release(); 
	if (m_pPShader)				 m_pPShader->Release(); 
	if (m_pConstantBuffer)		 m_pConstantBuffer->Release();
}

int Model::LoadObjModel(char * filename)
{
	HRESULT hr = S_OK;
	m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	if (m_pObject->filename == "FILE NOT LOADED") return S_FALSE;
	
	
	ID3DBlob *VS, *PS, *error;

	hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelVS", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0) // Check for a compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();

		if (FAILED(hr)) // Don't fail if error
			return hr;

	}

	hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelPS", "ps_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0) // Check for a compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();

		if (FAILED(hr)) // Don't fail if error
			return hr;

	}

	// Create shader objects

	hr = m_pD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVShader);

	if (FAILED(hr))
		return hr;

	hr = m_pD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPShader);

	if (FAILED(hr))
		return hr;

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);


	// Create and set the input layout object
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);

	if (FAILED(hr))
		return hr;

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	// Create Constant buffer
	D3D11_BUFFER_DESC				constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));

	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT; // Can use UpdateSubresource() to update
	constant_buffer_desc.ByteWidth = 112; // Must be a multiple of 16, calculate from Constant buffer struct
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Use as a constant buffer

	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &m_pConstantBuffer);

	if (FAILED(hr))
		return hr;

	return 0;
}

void Model::Draw(XMMATRIX * view, XMMATRIX * projection)
{
	XMMATRIX world, transpose;

	world = XMMatrixRotationX(XMConvertToRadians(m_xangle));
	world *= XMMatrixRotationY(XMConvertToRadians(m_yangle));
	world *= XMMatrixRotationZ(XMConvertToRadians(m_zangle));

	world *= XMMatrixScaling(m_scale, m_scale, m_scale);

	world *= XMMatrixTranslation(m_x, m_y, m_z);

	transpose = XMMatrixTranspose(world);

	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.WorldViewProjection = world*(*view)*(*projection); //(*view) this dereferences the pointer

	model_cb_values.directional_light_colour = m_directional_light_colour;
	model_cb_values.ambient_light_colour = m_ambient_light_colour;

	model_cb_values.directional_light_vector = XMVector3Transform(m_directional_light_shines_from, transpose);
	model_cb_values.directional_light_vector = XMVector3Normalize(model_cb_values.directional_light_vector);

	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	m_pObject->Draw();
}


////////////////////////////////////////////////////////
//Object manipulation
////////////////////////////////////////////////////////

//Set Functions
void Model::SetXPos(float x)
{
	m_x = x;
}

void Model::SetYPos(float y)
{
	m_y = y;
}

void Model::SetZPos(float z)
{
	m_z = z;
}

void Model::SetXRot(float x)
{
	m_xangle = x;
}

void Model::SetYRot(float y)
{
	m_yangle = y;
}

void Model::SetZRot(float z)
{
	m_zangle = z;
}

void Model::SetScale(float x)
{
	m_scale = x;
}

void Model::SetLighting(XMVECTOR shineFrom, XMVECTOR colour, XMVECTOR ambientLight)
{
	m_directional_light_shines_from = shineFrom;
	m_directional_light_colour = colour;
	m_ambient_light_colour = ambientLight;
}


//Get Functions
float Model::GetXPos()
{
	return m_x;
}

float Model::GetYPos()
{
	return m_y;
}

float Model::GetZPos()
{
	return m_z;
}

float Model::GetXRot()
{
	return m_xangle;
}

float Model::GetYRot()
{
	return m_yangle;
}

float Model::GetZRot()
{
	return m_zangle;
}

float Model::GetScale()
{
	return m_scale;
}

XMVECTOR Model::GetShineFrom()
{
	return m_directional_light_shines_from;
}

XMVECTOR Model::GetLightColour()
{
	return m_directional_light_colour;
}

XMVECTOR Model::GetAmbientLight()
{
	return m_ambient_light_colour;
}


//Incremental Functions
void Model::IncXPos(float x)
{
	m_x += x;
}

void Model::IncYPos(float y)
{
	m_y += y;
}

void Model::IncZPos(float z)
{
	m_z += z;
}

void Model::IncXRot(float x)
{
	m_xangle += x;
}

void Model::IncYRot(float y)
{
	m_yangle += y;
}

void Model::IncZRot(float z)
{
	m_zangle += z;
}

void Model::IncScale(float x)
{
	m_scale += x;
}

void Model::LookAt_XZ(float x, float z)
{
	m_dx = x - m_x;
	m_dz = z - m_z;

	m_yangle = atan2(m_dx, m_dz) * RadianToDegrees;
}

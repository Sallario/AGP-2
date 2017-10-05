#include "model.h"

struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;	//64 Bytes
}; //Total size = 64 Bytes


Model::Model(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_pD3DDevice = device;
	m_pImmediateContext = context;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;

	m_xangle = 0.0f;
	m_yangle = 0.0f;
	m_zangle = 0.0f;

	m_scale = 1.0f;
}

int Model::LoadObjModel(char * filename)
{
	HRESULT hr = S_OK;
	m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	if (m_pObject->filename == "FILE NOT LOADED") return S_FALSE;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Set up and create vertex buffer
	//D3D11_BUFFER_DESC				bufferDesc;
	//ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	//bufferDesc.Usage = D3D11_USAGE_DYNAMIC; // Allows the buffer to be dynamically accessed by the CPU and GPU
	//bufferDesc.ByteWidth = sizeof(vertices); // Total size of the buffer, 36 vertices
	//bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Use as a vetex buffer
	//bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Allow the CPU write access

	//hr = m_pD3DDevice->CreateBuffer(&bufferDesc, NULL, &m_pVBuffer); // Create the buffer

	//if (FAILED(hr)) // Return error code on failure
	//	return hr;

	//// Create Constant buffer
	//D3D11_BUFFER_DESC				constant_buffer_desc;
	//ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));

	//constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT; // Can use UpdateSubresource() to update
	//constant_buffer_desc.ByteWidth = 128; // Must be a multiple of 16, calculate from Constant buffer struct
	//constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // Use as a constant buffer

	//hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &m_pConstantBuffer0);

	//if (FAILED(hr))
	//	return hr;


	//// Copy the vertices into the buffer
	//D3D11_MAPPED_SUBRESOURCE ms;

	//// Lock the buffer to allow writing
	//m_pImmediateContext->Map(m_pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	//// Copy the data
	//memcpy(ms.pData, vertices, sizeof(vertices));

	//// Unlock the buffer
	//m_pImmediateContext->Unmap(m_pVertexBuffer, NULL);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	return 0;
}

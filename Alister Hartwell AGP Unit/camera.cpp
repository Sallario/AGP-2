#include "camera.h"

Camera::Camera(float initX, float initY, float initZ, float initRot)
{
	m_x = initX;
	m_y = initY;
	m_z = initZ;

	m_camera_angle = initRot;


}

//Camera::Camera()
//{
//	
//
//	m_positionX = 0.0f;
//	m_positionY = 0.0f;
//	m_positionZ = 0.0f;
//
//	m_rotationX = 0.0f;
//	m_rotationY = 0.0f;
//	m_rotationZ = 0.0f;
//
//	m_frameTime = 0.0f;
//
//	m_forwardSpeed = 0.0f;
//	m_backwardSpeed = 0.0f;
//	m_upwardSpeed = 0.0f;
//	m_downwardSpeed = 0.0f;
//	m_leftTurnSpeed = 0.0f;
//	m_rightTurnSpeed = 0.0f;
//	m_lookUpSpeed = 0.0f;
//	m_lookDownSpeed = 0.0f;
//}
//
//void Camera::Render()
//{
//	//D3DXVECTOR3 up, position, lookAt;
//	float yaw, pitch, roll;
//	//D3DXMATRIX rotationMatrix;
//	XMMATRIX roationMatrix;
//	XMVECTOR m_position, m_lookat, m_up;
//
//	// Setup the vector that points upwards.
//	m_up.x = 0.0f;
//	m_up.y = 1.0f;
//	m_up.z = 0.0f;
//
//	// Setup the position of the camera in the world.
//	m_position = XMVectorSet(m_positionX, m_positionY, m_positionZ);
//	
//	
//	// Setup where the camera is looking by default.
//	
//	m_lookat = XMVectorSet(0.0f, 0.0f, 1.0f);
//	
//
//	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
//	pitch = m_rotationX * 0.0174532925f;
//	yaw = m_rotationY * 0.0174532925f;
//	roll = m_rotationZ * 0.0174532925f;
//
//	// Create the rotation matrix from the yaw, pitch, and roll values.
//	XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
//	//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
//
//	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
//	
//	//D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &rotationMatrix);
//	//D3DXVec3TransformCoord(&m_up, &m_up, &rotationMatrix);
//
//	// Translate the rotated camera position to the location of the viewer.
//	m_lookAt = XMVectorAdd(m_position, m_lookat);
//
//	// Finally create the view matrix from the three updated vectors.
//	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_lookAt, &m_up);
//
//	return;
//}





void Camera::RotateCamera(float DegreesOfRotation)
{
	m_camera_angle += DegreesOfRotation;

	/*m_dx = sinf(m_camera_angle * DegreesToRadian);
	m_dz = cosf(m_camera_angle * DegreesToRadian);*/


}

void Camera::Forward(float distance)
{
	m_x += m_dx * distance;
	m_z += m_dz * distance;

}

XMMATRIX Camera::GetViewMatrix()
{
	m_dx = sinf(m_camera_angle * DegreesToRadian);
	m_dz = cosf(m_camera_angle * DegreesToRadian);

	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
	m_lookat = XMVectorSet(m_x + m_dx, m_y, m_z + m_dz, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	return XMMatrixLookAtLH(m_position, m_lookat, m_up);

}

void Camera::UpdateDXDZ()
{
	m_dx = sinf(m_camera_angle * DegreesToRadian);
	m_dz = cosf(m_camera_angle * DegreesToRadian);
}

void Camera::UpdateDXDZ(float step)
{
	m_x += (step * m_dx);
	m_z += (step * m_dz);

	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
	m_lookat = XMVectorSet(m_x + m_dx, m_y, m_z + m_dz, 0.0f);
	//SetVectors();
}

void Camera::SetRotate()
{
	//Just in case I need it. Delete if not needed
}

void Camera::SetVectors()
{
	SetPosition();
	SetLook();

}

void Camera::SetPosition()
{
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
}

void Camera::SetLook()
{
	m_lookat = XMVectorSet(m_x + m_dx, m_y, m_z + m_dz, 0.0f);
}

void Camera::SetView()
{
	m_view = XMMatrixLookAtLH(m_position, m_lookat, m_up);
}


//void Camera::SetPosition(float x, float y, float z)
//{
//	m_positionX = x;
//	m_positionY = y;
//	m_positionZ = z;
//	return;
//}
//
//
//void Camera::SetRotation(float x, float y, float z)
//{
//	m_rotationX = x;
//	m_rotationY = y;
//	m_rotationZ = z;
//	return;
//}
//
//void Camera::GetPosition(float& x, float& y, float& z)
//{
//	x = m_positionX;
//	y = m_positionY;
//	z = m_positionZ;
//	return;
//}
//
//
//void Camera::GetRotation(float& x, float& y, float& z)
//{
//	x = m_rotationX;
//	y = m_rotationY;
//	z = m_rotationZ;
//	return;
//}
//
//void Camera::SetFrameTime(float time)
//{
//	m_frameTime = time;
//	return;
//}
//
//void Camera::MoveForward(bool keydown)
//{
//	float radians;
//
//
//	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_forwardSpeed += m_frameTime * 0.001f;
//
//		if (m_forwardSpeed > (m_frameTime * 0.03f))
//		{
//			m_forwardSpeed = m_frameTime * 0.03f;
//		}
//	}
//	else
//	{
//		m_forwardSpeed -= m_frameTime * 0.0007f;
//
//		if (m_forwardSpeed < 0.0f)
//		{
//			m_forwardSpeed = 0.0f;
//		}
//	}
//
//	// Convert degrees to radians.
//	radians = m_rotationY * 0.0174532925f;
//
//	// Update the position.
//	m_positionX += sinf(radians) * m_forwardSpeed;
//	m_positionZ += cosf(radians) * m_forwardSpeed;
//
//	return;
//}
//
//void Camera::MoveBackward(bool keydown)
//{
//	float radians;
//
//
//	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_backwardSpeed += m_frameTime * 0.001f;
//
//		if (m_backwardSpeed > (m_frameTime * 0.03f))
//		{
//			m_backwardSpeed = m_frameTime * 0.03f;
//		}
//	}
//	else
//	{
//		m_backwardSpeed -= m_frameTime * 0.0007f;
//
//		if (m_backwardSpeed < 0.0f)
//		{
//			m_backwardSpeed = 0.0f;
//		}
//	}
//
//	// Convert degrees to radians.
//	radians = m_rotationY * 0.0174532925f;
//
//	// Update the position.
//	m_positionX -= sinf(radians) * m_backwardSpeed;
//	m_positionZ -= cosf(radians) * m_backwardSpeed;
//
//	return;
//}
//
//void Camera::MoveUpward(bool keydown)
//{
//	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_upwardSpeed += m_frameTime * 0.003f;
//
//		if (m_upwardSpeed > (m_frameTime * 0.03f))
//		{
//			m_upwardSpeed = m_frameTime * 0.03f;
//		}
//	}
//	else
//	{
//		m_upwardSpeed -= m_frameTime * 0.002f;
//
//		if (m_upwardSpeed < 0.0f)
//		{
//			m_upwardSpeed = 0.0f;
//		}
//	}
//
//	// Update the height position.
//	m_positionY += m_upwardSpeed;
//
//	return;
//}
//
//void Camera::MoveDownward(bool keydown)
//{
//	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_downwardSpeed += m_frameTime * 0.003f;
//
//		if (m_downwardSpeed > (m_frameTime * 0.03f))
//		{
//			m_downwardSpeed = m_frameTime * 0.03f;
//		}
//	}
//	else
//	{
//		m_downwardSpeed -= m_frameTime * 0.002f;
//
//		if (m_downwardSpeed < 0.0f)
//		{
//			m_downwardSpeed = 0.0f;
//		}
//	}
//
//	// Update the height position.
//	m_positionY -= m_downwardSpeed;
//
//	return;
//}
//
//void Camera::TurnLeft(bool keydown)
//{
//	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_leftTurnSpeed += m_frameTime * 0.01f;
//
//		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
//		{
//			m_leftTurnSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_leftTurnSpeed -= m_frameTime* 0.005f;
//
//		if (m_leftTurnSpeed < 0.0f)
//		{
//			m_leftTurnSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationY -= m_leftTurnSpeed;
//
//	// Keep the rotation in the 0 to 360 range.
//	if (m_rotationY < 0.0f)
//	{
//		m_rotationY += 360.0f;
//	}
//
//	return;
//}
//
//void Camera::TurnRight(bool keydown)
//{
//	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_rightTurnSpeed += m_frameTime * 0.01f;
//
//		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
//		{
//			m_rightTurnSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_rightTurnSpeed -= m_frameTime* 0.005f;
//
//		if (m_rightTurnSpeed < 0.0f)
//		{
//			m_rightTurnSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationY += m_rightTurnSpeed;
//
//	// Keep the rotation in the 0 to 360 range.
//	if (m_rotationY > 360.0f)
//	{
//		m_rotationY -= 360.0f;
//	}
//
//	return;
//}
//
//void Camera::LookUpward(bool keydown)
//{
//	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_lookUpSpeed += m_frameTime * 0.01f;
//
//		if (m_lookUpSpeed > (m_frameTime * 0.15f))
//		{
//			m_lookUpSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_lookUpSpeed -= m_frameTime* 0.005f;
//
//		if (m_lookUpSpeed < 0.0f)
//		{
//			m_lookUpSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationX -= m_lookUpSpeed;
//
//	// Keep the rotation maximum 90 degrees.
//	if (m_rotationX > 90.0f)
//	{
//		m_rotationX = 90.0f;
//	}
//
//	return;
//}
//
//void Camera::LookDownward(bool keydown)
//{
//	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
//	if (keydown)
//	{
//		m_lookDownSpeed += m_frameTime * 0.01f;
//
//		if (m_lookDownSpeed > (m_frameTime * 0.15f))
//		{
//			m_lookDownSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_lookDownSpeed -= m_frameTime* 0.005f;
//
//		if (m_lookDownSpeed < 0.0f)
//		{
//			m_lookDownSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationX += m_lookDownSpeed;
//
//	// Keep the rotation maximum 90 degrees.
//	if (m_rotationX < -90.0f)
//	{
//		m_rotationX = -90.0f;
//	}
//
//	return;
//}
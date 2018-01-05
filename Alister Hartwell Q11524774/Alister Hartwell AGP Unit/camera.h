#pragma once

#include <math.h>
#include <d3d11.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

class Camera
{
private:
	float m_x, m_y, m_z, m_dx, m_dz, m_camera_rotation, m_camera_angle;

	XMVECTOR m_position, m_lookat, m_up;
	XMMATRIX m_view;

	const float DegreesToRadian = 0.01745329251;
	const float RadianToDegrees = 57.2957795131; // Both of these constants are used to save on calculation times since division is expensive
												 //const XMVECTOR m_up = XMVECTOR(0.0f, 1.0f, 0.0f, 0.0f);
												 //const XMFLOAT4 m_up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f); //Expermiemnting with optimisation

	void UpdateDXDZ();
	void UpdateDXDZ(float stepForward);
	void SetRotate();
	void SetVectors();
	void SetPosition();
	void SetLook();
	void SetView();

	/*float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;*/

public:
	Camera(float initX, float initY, float initZ, float initRot);
	/*Camera();
	void Render();*/

	void RotateCamera(float DegreesOfRotation);
	void Forward(float distance);

	float GetX();
	float GetY();
	float GetZ();

	XMMATRIX GetViewMatrix();

	/*void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void GetPosition(float&, float&, float&);
	void GetRotation(float&, float&, float&);

	void SetFrameTime(float);

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);*/

};

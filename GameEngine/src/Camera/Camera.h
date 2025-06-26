#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

private:
	float m_cameraSpeed = 0.1f;
};
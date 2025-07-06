#pragma once

namespace Math
{
	struct Vector3
	{
	public:
		float x, y, z;
	};

	class Matrix4D
	{
	public:
		Matrix4D(float inital);
		Matrix4D(float x, float y, float z);
		Matrix4D(float x, float y, float z, float w);

		void Translation(float tx, float ty, float tz);

		float* Flatten();

		std::string toString();

	private:
		float m_Matrix[4][4] = {};
	};

}
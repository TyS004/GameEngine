#include "gepch.h"
#include "Math.h"

namespace Math
{
	Matrix4D::Matrix4D(float inital)
	{
		for (int i = 0; i < 4; ++i)
		{
			m_Matrix[i][i] = 1.0f;
		}
		std::cout << toString();
	}

	std::string Matrix4D::toString()
	{
		std::string result;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result += std::to_string(m_Matrix[i][j]) + " ";
			}
			result += "\n";
		}
		return result;
	}

	float* Matrix4D::Flatten()
	{
		float flat[16]{};
		for (int col = 0; col < 4; ++col)
		{
			for (int row = 0; row < 4; ++row)
			{
				flat[col * 4 + row] = m_Matrix[row][col];
			}
		}
		return flat;
	}

	void Matrix4D::Translation(float tx, float ty, float tz)
	{
		m_Matrix[3][0] = tx;
		m_Matrix[3][1] = ty;
		m_Matrix[3][2] = tz;
	}

	// TRS (TRANSFORM, ROTATION, SCALE)
	Matrix4D Transform(Matrix4D matrix, Vector3 vector)
	{
		return Matrix4D(1.0f);
	}
}

std::ostream& operator<<(std::ostream& out, Math::Matrix4D matrix)
{
	out << matrix.toString();
	return out;
}

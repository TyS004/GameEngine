#pragma once

#include "gepch.h"

namespace GameEngine
{
	struct Entity
	{
		uint32_t m_ID;
	};

	struct TransformComponet
	{
		float x, y, z;
		float yaw, pitch, roll;
	};

	struct MeshComponet
	{

	};
}
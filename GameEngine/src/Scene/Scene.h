#pragma once

#include "ECS/Componets.h"

namespace GameEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		std::vector<TransformComponet> GetTransforms();
		std::vector<MeshComponet> GetMeshes();
		std::vector<TagComponet> GetTags();

	private:
		std::vector<TransformComponet> m_transforms;
		std::vector<MeshComponet> m_meshes;
		std::vector<TagComponet> m_tags;
	};
}
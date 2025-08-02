#include "gepch.h"
#include "Scene/Scene.h"
#include "ECS/Entity.h"

namespace GameEngine
{
	Scene::Scene()
	{
		m_transforms.reserve(5);
		m_tags.push_back(TagComponet("Cube"));
	}

	Scene::~Scene()
	{

	}

	std::vector<TransformComponet> Scene::GetTransforms()
	{
		return m_transforms;
	}

	std::vector<MeshComponet> Scene::GetMeshes()
	{
		return m_meshes;
	}

	std::vector<TagComponet> Scene::GetTags()
	{
		return m_tags;
	}
}
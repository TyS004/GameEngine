#include "gepch.h"

#include "Entity.h"

namespace GameEngine
{
	uint32_t Entity::Entity_ID = 0;

	Entity::Entity(Scene* scene)
	{
		m_ID = Entity_ID++;
		m_Scene = scene;
	}

	Entity::~Entity()
	{
		delete m_Scene;
	}
	
	void Entity::AddTransformComponet()
	{
		m_Scene->GetTransforms().emplace_back();
	}

	void Entity::AddMeshComponet()
	{
		m_Scene->GetMeshes().emplace_back();
	}

	void Entity::AddTagComponet(const std::string& tag)
	{
	}

	uint32_t Entity::GetID()
	{
		return m_ID;
	}
}
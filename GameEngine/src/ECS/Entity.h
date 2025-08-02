#pragma once

#include "Scene/Scene.h"

namespace GameEngine
{
    class Entity
    {
    public:
        Entity(Scene* scene);
        ~Entity();

        void AddTransformComponet();
        void AddMeshComponet();
        void AddTagComponet(const std::string& tag);

        uint32_t GetID();

        static uint32_t Entity_ID;

    private:
        uint32_t m_ID;
        Scene* m_Scene;
    };
}
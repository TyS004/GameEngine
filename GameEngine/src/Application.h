#pragma once

#include "Graphics/Window/Window.h"
#include "Graphics/OpenGL/OpenGL.h"

#include "Logging/Log.h"

#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Input/Input.h"

#include "Objects/Object.h"

#include "Camera/Camera.h"

#include "Math/Math.h"

#include "UI/UIElements/UIElement.h"
#include "UI/UI.h"

#include "Graphics/Buffer/Texture.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
	void DrawObjects();
	void UpdateWindows();
	void OnEvent(Event& e);

	bool OnWindowClose(WindowCloseEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);
	bool OnMouseButtonPressed(MousePressedEvent& e);
	bool OnMouseMoved(MouseMovedEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);
	
	//UI / ImGUI
	void OnImGuiSliderChanged(const UIElement& element);
	void OnImGuiButtonPressed(const UIElement& element);

	//Editor Side (Need to Change Project Architecture)
	//void CreateObject(float x, float y, float z);

private:
	bool m_Running = true;

	uint32_t m_ActiveWindow = 0;
	uint32_t m_SelectedObject = 0;

	std::vector<Window*> m_Windows;
	std::vector<Object*> m_Objects;

	OpenGL* m_Renderer;
	Shader* m_Shader;
	Camera* m_Camera;
	UI* m_UI;

	std::unordered_map<std::string, float> m_SliderValues;

	float m_lastXPos, m_lastYPos;
	bool firstMouse = true;
};

//template <typename T>
//void Application::OnSliderChanged(const Slider<T>& slider)
//{
//	Object* currentObj = m_Objects[m_SelectedObject];
//
//	if (slider.GetName() == "X Position")
//	{
//		currentObj->Translate(slider.GetData(), currentObj->getTransform().y, currentObj->getTransform().z, *m_Shader);
//		INFO(slider.GetData());
//	}
//	else if (slider.GetName() == "Y Position")
//	{
//		currentObj->Translate(currentObj->getTransform().x, slider.GetData(), currentObj->getTransform().z, *m_Shader);
//	}
//	else if (slider.GetName() == "Z Position")
//	{
//		currentObj->Translate(currentObj->getTransform().x, currentObj->getTransform().y, slider.GetData(), *m_Shader);
//	}
//}
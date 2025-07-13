#pragma once

#ifdef _WIN32
	#include <Windows.h>
#endif

#include <string>
#include <chrono>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <utility>
#include <filesystem>
#include <vector>

#include <functional>

//Vendor
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <stb_image.h>
#pragma once
#include <string>
#include "ImGuiEasing/ImGuiEasingDefine.h"

#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	enum class IMGUIEASING_API ImguiEasingErrorCode
	{
		Unknown = -1,
		Ok,
		SDL_Init_Fail,
		SDL_GL_SetAttribute_Fail,
		SDL_CreateWindow_Fail,
		SDL_GL_CreateContext_Fail,
		Imgui_CreateContext_Fail,
		ImGui_ImplSDL2_InitForOpenGL_Fail,
		ImGui_ImplOpenGL2_Init_Fail,
	};

	struct IMGUIEASING_API ImguiEasingError
	{
		ImguiEasingErrorCode code;
		std::string comment;
	};
}
#pragma warning(default: 4251)
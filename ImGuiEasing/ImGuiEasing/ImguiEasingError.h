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
	};

	extern "C++"
	{
		static const std::string ToString_ImguiEasing_ErrorCode(ImguiEasingErrorCode code)
		{
			switch (code)
			{
			case ImguiEasingErrorCode::Ok:
				return "Ok";
			case ImguiEasingErrorCode::SDL_Init_Fail:
				return "SDL_Init_Fail";
			case ImguiEasingErrorCode::SDL_GL_SetAttribute_Fail:
				return "SDL_GL_SetAttribute_Fail";
			case ImguiEasingErrorCode::SDL_CreateWindow_Fail:
				return "SDL_CreateWindow_Fail";
			default:
				break;
			}
			return "Unknown";
		}
	}

	struct IMGUIEASING_API ImguiEasingError
	{
		ImguiEasingErrorCode code;
		std::string comment;
	};
}
#pragma warning(default: 4251)
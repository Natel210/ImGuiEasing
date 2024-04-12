#pragma once
#include "ImGuiEasing/UiComponentBase.h"
/// <summary>
/// This is a current clock component.											<para/>
/// Provides a clunky design for Item().										<para/>
/// When modifying the UI contents, refer to the Item() section and inherit it.	<para/>
/// </summary>
class CurrentClockUIComponent : public ImGuiEasing::UiComponentBase
{
protected:
	/// <summary> User Custom </summary>
	void Item() final;
public:
	CurrentClockUIComponent(const std::string& name);
	virtual ~CurrentClockUIComponent() = default;
};


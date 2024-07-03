#pragma once
#include <string>
#include "ImGuiEasing/ViewBase.h"
class MenuController : public ImGuiEasing::ViewBase
{
protected:
	/// <summary> Options like SetNextWindowPos </summary>
	void SetNextWindowOption() override;
	/// <summary> Begin applying options 
	/// such as PushStyleVar, PushStyleVar </summary>
	void ApplyCustomStyle() override;
	/// <summary> End applying options like PopStyleVar, PopStyleVar, 
	/// must match the declaration count of ApplyCustomStyle </summary>
	void UnapplyCustomStyle() override;
protected:
	/// <summary> Is it to operate inside the window?
	/// e.g., childWindow </summary>
	void WindowItem() override;
	/// <summary> Additional tasks after creating the window </summary>
	void RenderAfter() override;
public:
	MenuController(const char* name);
	~MenuController();

};


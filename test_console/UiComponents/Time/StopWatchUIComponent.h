#pragma once
#include "ImGuiEasing/UiComponentBase.h"
#include "UiComponents/Combo/ComboUiComponent.h"
#include "Utility/Time/StopWatch.h"
//#include "Lucid/Common/UI/Components/BaseItems/ComboUiComponent.h"

/// <summary>
/// This is a stopWatch component.												<para/>
/// Provides a clunky design for Item().										<para/>
/// When modifying the UI contents, refer to the Item() section and inherit it.	<para/>
/// </summary>
class StopWatchUIComponent : public ImGuiEasing::UiComponentBase
{
protected:
	/// <summary> User Custom </summary>
	void Item() final;
public:
	virtual std::shared_ptr<ImGuiEasing::StopWatch> StopWatch() final;
	virtual void StopWatch(std::shared_ptr<ImGuiEasing::StopWatch> stopWatch) final;
private:
	virtual void Output_Time() final;
	virtual void Output_Seconds() final;
	virtual void Output_Milliseconds() final;

public:
	StopWatchUIComponent(const std::string& name, std::shared_ptr<ImGuiEasing::StopWatch> stopWatch = nullptr);
	virtual ~StopWatchUIComponent() = default;
private:
	std::shared_ptr<ImGuiEasing::StopWatch> _stopWatch;
	std::shared_ptr<ImGuiEasing::ComboUiComponent> _combo;
};

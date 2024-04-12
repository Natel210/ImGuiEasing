#pragma once
#include "ImGuiEasing/UiComponentBase.h"
#include <vector>
#include <string>
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary>
	/// simple combo box
	/// </summary>
	class IMGUIEASING_API ComboUiComponent : public UiComponentBase
	{

	protected:
		/// <summary> Sub-implementation </summary>
		void Item() override;

	public:
		void ItemList(const std::vector<std::string>& list);
		_NODISCARD std::vector<std::string> ItemList() const;
	private:
		void SelectedString(const std::string selectedString);
	public:
		_NODISCARD std::string SelectedString() const;
	public:
		ComboUiComponent(std::string name, std::string defaultString);
		~ComboUiComponent() = default;
	private:
		std::string _selectedString;
		std::vector<std::string> _list;
	};

}
#pragma warning(default: 4251)
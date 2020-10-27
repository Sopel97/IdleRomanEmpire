#include "HorizontalLayout.h"
#include <iostream>

namespace ire::core::widgets
{
	WidgetType const HorizontalLayout::m_type = WidgetType::create<HorizontalLayout>("Horizontal Layout");

	HorizontalLayout::HorizontalLayout(const sf::Vector2f& size)
		: BoxLayout{size}
	{
		//updateWidgets();
	}
	std::unique_ptr<HorizontalLayout> HorizontalLayout::create(const sf::Vector2f& size)
	{
		return std::make_unique<HorizontalLayout>(size);
	}
	void HorizontalLayout::updateWidgets()
	{
		// # Calculate size of widget
		const auto size = getSize();
		const auto sizeOfVector = m_widgets.size();
		const auto width = (size.x / sizeOfVector) - ((m_margins.getLeftMargin() + m_margins.getRightMargin() + (m_spaces * (sizeOfVector - 1))) / sizeOfVector);
		const auto height = size.y - m_margins.getTopMargin() - m_margins.getBottomMargin();

		auto position = getPosition();
		// # Calculate position of widget
		for (std::size_t i = 0; i < sizeOfVector; ++i)
		{
			const auto positionOfNextWidgetX = m_margins.getLeftMargin() + (width * i) + (m_spaces * i);
			const auto positionOfNextWidgetY = m_margins.getTopMargin();
			m_widgets[i].get()->setPosition(position + sf::Vector2f{positionOfNextWidgetX, positionOfNextWidgetY});
			m_widgets[i].get()->setSize(width, height);
		}
	}
}
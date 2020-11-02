#include "ClickableWidget.h"
#include "WidgetType.h"

namespace ire::core::gui
{
	WidgetType const ClickableWidget::m_type = WidgetType::create<ClickableWidget>("ClickableWidget");

	ClickableWidget::ClickableWidget()
	{
	}

	void ClickableWidget::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
		updateWidget();
	}
	void ClickableWidget::setPosition(const sf::Vector2f& position)
	{
		Widget::setPosition(position);
		updateWidget();
	}
	void ClickableWidget::draw(sf::RenderTarget& target)
	{
	}
}
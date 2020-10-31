#include <catch2/catch.hpp>

#include "core/widgets/Button.h"
#include "../Testsutils.h"

TEST_CASE("[Button]")
{
	auto button = ire::core::widgets::Button::create();

	SECTION("WidgetType")
	{
		REQUIRE(button->getType().getName() == "Button");
	}
	SECTION("Name")
	{
		button->setWidgetName("Button1");
		REQUIRE(button->getWidgetName() == "Button1");
	}
	SECTION("Position and Size")
	{
		button->setPosition({ 40, 50 });
		button->setSize({ 100, 200 });

		REQUIRE(areAlmostEqual<sf::Vector2f>(button->getPosition(), sf::Vector2f({ 40, 50 })));
		REQUIRE(areAlmostEqual<sf::Vector2f>(button->getSize(), sf::Vector2f({ 100, 200 })));
	}
}
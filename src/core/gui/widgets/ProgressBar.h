#ifndef IRE_PROGRESSBAR_H
#define IRE_PROGRESSBAR_H

#include "ClickableWidget.h"

#include "core/resource/Resource.h"
#include "core/resource/FontResourceLoader.h"
#include "core/resource/ResourceManager.h"

namespace ire::core::gui
{
    struct ProgressBar : ClickableWidget
    {
        enum class FillDirection
        {
            LeftToRight,
            RightToLeft,
            TopToBottom,
            BottomToTop,
            // CounterClockwise,
            // Clockwise
        };

        enum class VerticalTextAlignment
        {
            Top,
            Center,
            Bottom
        };

        ProgressBar();

        static std::unique_ptr<ProgressBar> create(const std::string& text = "");

        void draw(sf::RenderTarget& target) override;

        void updateWidget() override;

        void setMinimum(uint64_t minimum);
        const uint64_t getMinimum() const;

        const std::string getMinimumString() const;
        void setMinimumTextCharacterSize(unsigned int minimumTextCharacterSize);
        const unsigned int getMinimumTextCharacterSize() const;
        void setMinimumTextVerticalAlignment(VerticalTextAlignment minimymTextVerticalAlignment);
        const std::string getMinimumTextVerticalAlignmentString() const;
        void setMinimumVisibility(bool isMinimumVisible);
        const bool isMinimumVisible() const;
        void setMinimumTextFillColor(sf::Color minimumTextFillColor);
        const sf::Color getMinimumTextFillColor() const;

        void setMaximum(uint64_t maximum);
        const uint64_t getMaximum() const;

        void setMaximumTextCharacterSize(unsigned int maximumTextCharacterSize);
        const unsigned int getMaximumTextCharacterSize() const;
        void setMaximumTextVerticalAlignment(VerticalTextAlignment maximumTextVerticalAlignment);
        const std::string getMaximumTextVerticalAlignmentString() const;
        void setMaximumVisibility(bool isMaximumVisible);
        const bool isMaximumVisible() const;
        void setMaximumTextFillColor(sf::Color maximumTextFillColor);
        const sf::Color getMaximumTextFillColor() const;

        void setValue(uint64_t value);
        const uint64_t getValue() const;
        void setValueTextCharacterSize(unsigned int valueTextCharacterSize);
        const unsigned int getValueTextCharacterSize() const;
        void setValueTextVerticalAlignment(VerticalTextAlignment valueTextVerticalAlignment);
        const std::string getValueTextVerticalAlignmentString() const;
        void setValueVisibility(bool isValueVisible);
        const bool isValueVisible() const;
        void setValueTextFillColor(sf::Color valueTextFillColor);
        const sf::Color getValueTextFillColor() const;

        const uint64_t getPercent() const;
        void setPercentTextCharacterSize(unsigned int percentTextCharacterSize);
        const unsigned int getPercentTextCharacterSize() const;
        void setPercentTextVerticalAlignment(VerticalTextAlignment percentTextVerticalAlignment);
        const std::string getPercentTextVerticalAlignmentString() const;
        void setPercentVisibility(bool isPercentVisible);
        const bool isPercentVisible() const;
        void setPercentTextFillColor(sf::Color percentTextFillColor);
        const sf::Color getPercentTextFillColor() const;

        void setMainTextString(std::string string);
        const std::string getMainString() const;
        void setMainTextCharacterSize(unsigned int mainTextCharacterSize);
        const unsigned int getMainTextCharacterSize() const;
        void setMainTextVerticalAlignment(VerticalTextAlignment mainTextVerticalAlignment);
        const std::string getMainTextVerticalAlignmentString() const;
        void setMainVisibility(bool isMainVisible);
        const bool isMainVisible() const;
        void setMainTextFillColor(sf::Color mainTextFillColor);
        const sf::Color getMainTextFillColor() const;

        void setProgressFillColor(sf::Color barFillColor);
        const sf::Color getProgressFillColor() const;

        void setBackgroundFillColor(sf::Color backgroundFillColor);
        const sf::Color getBackgroundFillColor() const;

        void setFillDirection(FillDirection fillDirection);
        const FillDirection getFillDirection() const;

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }

    private:
        struct Text
        {
            sf::Text m_text;
            std::string m_textString;
            unsigned int m_characterSize{ 15 };
            VerticalTextAlignment m_textVerticalAlignement = VerticalTextAlignment::Center;
            bool m_isTextVisible = false;
            sf::Color m_textFillColor = sf::Color::Black;

            Text();
        };
        ResourcePtr<sf::Font> m_font;

        Text m_maximumText;
        uint64_t m_minimum{ 0 };
        void setMaximumTextString(std::string string);

        Text m_minimumText;
        uint64_t m_maximum{ 100 };
        void setMinimumTextString(std::string string);

        Text m_valueText;
        uint64_t m_value{ 50 };
        void setValueTextString(std::string string);

        Text m_percentText;
        const float calculatePercent() const;
        void setPercentTextString(std::string percentTextString);

        Text m_mainText;

        sf::RectangleShape m_backgroundShape;
        sf::Color m_backgroundFillColor;

        sf::RectangleShape m_progressShape;
        sf::Color m_progressFillColor;

        void setTextString(Text& text, std::string string);
        const std::string getTextString(Text text) const;
        void setCharacterSize(Text& text, unsigned int characterSize);
        const unsigned int getCharacterSize(Text text) const;
        void setVerticalAlignment(Text& text, VerticalTextAlignment verticalAlignment);
        const std::string getVerticalAlignmentString(Text text) const;
        void setVisibility(Text& text, bool isVisible);
        const bool isVisible(Text text) const;
        void setFillColor(Text& text, sf::Color color);
        const sf::Color getFillColor(Text text) const;

        void updateMainTextPosition();
        void updateMaximumTextPosition();
        void updateMinimumTextPosition();
        void updateValueTextPosition();
        void updatePercentTextPosition();

        void updateTextPosition(Text& text, float xPosition, float yPosition = 0);

        void updateMainTextString();
        void updateMaximumTextString();
        void updateMinimumTextString();
        void updateValueTextString();
        void updatePercentTextString();

        void updateFillDirection();
        void invertBarsColors();
        FillDirection m_fillDirection = FillDirection::LeftToRight;
    };
}
#endif //!IRE_PROGRESSBAR_H
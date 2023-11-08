
#include "TextBox.h"
#define BACK_SPACE 8

TextBox::TextBox() : limit(50)
{
   
    textarea.setCharacterSize(40); //will adjust later
    font.loadFromFile("Fonts/batmfa__.ttf");
    textarea.setFont(font);
  
    textarea.setFillColor(sf::Color(140, 140, 140));
}
bool TextBox::checklimit()
{
    return (text.length() < limit);
}
void TextBox::deleteChar()
{
    if (text.length() > 0)
        text.erase(text.length() - 1);
}
void TextBox::Render(sf::RenderWindow* window)
{
    textarea.setPosition((780 - textarea.getGlobalBounds().width) / 2, (780 - textarea.getGlobalBounds().height) / 2);
    window->draw(textarea);
}
void TextBox::processInputs(unsigned int inputchar)
{
    if (inputchar == BACK_SPACE)
        deleteChar();
    else if (checklimit())
    {
        text += char(inputchar);
        textarea.setString(text + "_");
    }
}
std::string TextBox::getText() const
{
    return text;
}
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, 
           const std::string& value, const sf::Font& font);
    
    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const;
    const std::string& getValue() const;

private:
    sf::RectangleShape shape;
    sf::Text text;
    std::string value;
};

class Calculator {
public:
    Calculator();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleButtonClick(const std::string& buttonValue);
    double calculate(const std::string& expression);
    std::vector<std::string> tokenize(const std::string& expression);
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);
    double evaluatePostfix(const std::vector<std::string>& postfix);
    bool isOperator(const std::string& token) const;
    int getPrecedence(const std::string& op) const;
    bool isNumber(const std::string& s) const;

    sf::RenderWindow window;
    sf::Font font;
    sf::Text displayText;
    std::string currentInput;
    std::vector<Button> buttons;
};

#endif // CALCULATOR_H
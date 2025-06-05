#include "Calculator.h"
#include <stack>
#include <queue>
#include <sstream>
#include <cmath>
#include <cctype>

// Button implementation
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, 
               const std::string& value, const sf::Font& font) 
    : value(value) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(100, 100, 100));

    text.setFont(font);
    text.setString(value);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(position.x + size.x/2.0f,
                     position.y + size.y/2.0f);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}

bool Button::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

const std::string& Button::getValue() const {
    return value;
}

// Calculator implementation
Calculator::Calculator() : window(sf::VideoMode(400, 600), "Calculator"), currentInput("") {
    // Try multiple font locations
    const std::vector<std::string> fontPaths = {
        "arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/tahoma.ttf",
        "C:/Windows/Fonts/verdana.ttf"
    };

    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            break;
        }
    }

    displayText.setFont(font);
    displayText.setCharacterSize(48);
    displayText.setFillColor(sf::Color::White);
    displayText.setPosition(20, 20);
    displayText.setString("0");

    std::vector<std::vector<std::string>> buttonLayout = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"},
        {"C", "(", ")", "^"}
    };

    float startX = 20, startY = 100;
    float buttonWidth = 80, buttonHeight = 80, gap = 10;

    for (int row = 0; row < buttonLayout.size(); ++row) {
        for (int col = 0; col < buttonLayout[row].size(); ++col) {
            float x = startX + col * (buttonWidth + gap);
            float y = startY + row * (buttonHeight + gap);
            buttons.emplace_back(
                sf::Vector2f(x, y),
                sf::Vector2f(buttonWidth, buttonHeight),
                buttonLayout[row][col],
                font
            );
        }
    }
}

void Calculator::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Calculator::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (auto& button : buttons) {
                    if (button.contains(mousePos)) {
                        handleButtonClick(button.getValue());
                    }
                }
            }
        }
    }
}

void Calculator::update() {
    displayText.setString(currentInput.empty() ? "0" : currentInput);
}

void Calculator::render() {
    window.clear(sf::Color(50, 50, 50));
    
    // Draw display background
    sf::RectangleShape displayBackground(sf::Vector2f(360, 70));
    displayBackground.setPosition(20, 20);
    displayBackground.setFillColor(sf::Color(30, 30, 30));
    window.draw(displayBackground);
    
    window.draw(displayText);
    
    // Draw buttons
    for (auto& button : buttons) {
        button.draw(window);
    }
    
    window.display();
}

void Calculator::handleButtonClick(const std::string& buttonValue) {
    if (buttonValue == "C") {
        currentInput.clear();
    } else if (buttonValue == "=") {
        try {
            double result = calculate(currentInput);
            currentInput = std::to_string(result);
            // Remove trailing zeros
            size_t dotPos = currentInput.find('.');
            if (dotPos != std::string::npos) {
                currentInput.erase(currentInput.find_last_not_of('0') + 1, std::string::npos);
                if (currentInput.back() == '.') {
                    currentInput.pop_back();
                }
            }
        } catch (const std::exception& e) {
            currentInput = "Error";
        }
    } else {
        currentInput += buttonValue;
    }
}

double Calculator::calculate(const std::string& expression) {
    auto tokens = tokenize(expression);
    auto postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}

std::vector<std::string> Calculator::tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string currentToken;
    
    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        
        if (isspace(c)) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            continue;
        }
        
        if (isOperator(std::string(1, c)) || c == '(' || c == ')') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, c));
            continue;
        }
        
        currentToken += c;
    }
    
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }
    
    return tokens;
}

std::vector<std::string> Calculator::infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> postfix;
    std::stack<std::string> opStack;
    
    for (const auto& token : tokens) {
        if (isNumber(token)) {
            postfix.push_back(token);
        } else if (token == "(") {
            opStack.push(token);
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // Remove '('
        } else if (isOperator(token)) {
            while (!opStack.empty() && opStack.top() != "(" && 
                   getPrecedence(opStack.top()) >= getPrecedence(token)) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    
    while (!opStack.empty()) {
        postfix.push_back(opStack.top());
        opStack.pop();
    }
    
    return postfix;
}

double Calculator::evaluatePostfix(const std::vector<std::string>& postfix) {
    std::stack<double> operandStack;
    
    for (const auto& token : postfix) {
        if (isNumber(token)) {
            operandStack.push(std::stod(token));
        } else if (isOperator(token)) {
            if (operandStack.size() < 2) {
                throw std::runtime_error("Not enough operands");
            }
            
            double b = operandStack.top(); operandStack.pop();
            double a = operandStack.top(); operandStack.pop();
            double result;
            
            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Division by zero");
                result = a / b;
            }
            else if (token == "^") result = pow(a, b);
            else throw std::runtime_error("Unknown operator");
            
            operandStack.push(result);
        }
    }
    
    if (operandStack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    
    return operandStack.top();
}

bool Calculator::isOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

int Calculator::getPrecedence(const std::string& op) const {
    if (op == "^") return 4;
    if (op == "*" || op == "/") return 3;
    if (op == "+" || op == "-") return 2;
    return 0;
}

bool Calculator::isNumber(const std::string& s) const {
    std::istringstream iss(s);
    double d;
    iss >> d;
    return iss.eof() && !iss.fail();
}
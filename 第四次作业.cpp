#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>


// 生成随机整数
int GenerateIntegers(int maxNum) {
    return rand() % maxNum + 1;
}

// 生成随机小数
float GenerateDecimal(int maxNum) {
    return (float)(rand() % maxNum) / 10.0f;
}

// 生成四则运算题目(整数)
using std::string; auto GenerateExpression(int maxNum, bool allowDecimal, bool allowBrackets, std::vector<char> operators) {
    string expression;
    int num1, num2;
    char op1, op2;

    num1 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);
    num2 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);
    op1 = operators[rand() % operators.size()];
    op2 = operators[rand() % operators.size()];

    expression += std::to_string(num1) + " " + op1 + " " + std::to_string(num2);

    if (allowBrackets && rand() % 2 == 0) {
        expression = "(" + expression + ")";
    }

    expression += " " + string(1, op2) + " ";

    num1 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);
    num2 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);

    expression += std::to_string(num1) + " " + op2 + " " + std::to_string(num2);

    return  expression;
}
//生成四则运算（小数）
using std::string; auto FloatGenerateExpression(int maxNum, bool allowDecimal, bool allowBrackets, std::vector<char> operators) {
    string expression;
    float num1, num2;
    char op1, op2;
    double roundedNum;

    // 计算0.01，也就是10的-2次方
    double scale = std::pow(10.0, 2);
    num1 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);
    num2 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);

    op1 = operators[rand() % operators.size()];
    op2 = operators[rand() % operators.size()];

    expression += std::to_string(num1) + " " + op1 + " " + std::to_string(num2);

    if (allowBrackets && rand() % 2 == 0) {
        expression = "(" + expression + ")";
    }

    expression += " " + string(1, op2) + " ";

    num1 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);
    num2 = allowDecimal ? GenerateDecimal(maxNum * 10) : GenerateIntegers(maxNum);

    expression += std::to_string(num1) + " " + op2 + " " + std::to_string(num2);

    return  expression;
}
// 输出到文件
void outputToFile(string filename, std::vector<string> expressions) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (const auto& expression : expressions) {
            outputFile << expression << std::endl;
        }
        outputFile.close();
        std::cout << "题目已成功输出到文件：" << filename << std::endl;
    }
    else {
        std::cerr << "无法打开文件：" << filename << std::endl;
    }
}

int main() {
    srand(time(0));

    int numQuestions, maxNum;
    bool allowDecimal, allowBrackets;
    std::vector<char> operators;
    std::vector<string> expressions;

    std::cout << "请输入题目数量：";
    std::cin >> numQuestions;
    std::cout << "请输入最大数值：";
    std::cin >> maxNum;
    std::cout << "是否允许使用小数？(1: 是，0: 否)：";
    std::cin >> allowDecimal;
    std::cout << "是否允许使用括号？(1: 是，0: 否)：";
    std::cin >> allowBrackets;

    char op;
    std::cout << "请选择运算符（+ - * /，用空格隔开）：";
    while (std::cin >> op) {
        operators.push_back(op);
        if (std::cin.get() == '\n') {
            break;
        }
    }
    if (allowDecimal == 1) {
        for (int i = 0; i < numQuestions; ++i) {
            expressions.push_back(FloatGenerateExpression(maxNum, allowDecimal, allowBrackets, operators));
        }
    }
    if (allowDecimal == 0) {
        for (int i = 0; i < numQuestions; ++i) {
            expressions.push_back(GenerateExpression(maxNum, allowDecimal, allowBrackets, operators));
        }
    }
    // 输出到文件
    string filename = "math_sizeyunsuan.txt";
    outputToFile(filename, expressions);

    return 0;
}
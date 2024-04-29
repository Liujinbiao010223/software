#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>


// �����������
int GenerateIntegers(int maxNum) {
    return rand() % maxNum + 1;
}

// �������С��
float GenerateDecimal(int maxNum) {
    return (float)(rand() % maxNum) / 10.0f;
}

// ��������������Ŀ(����)
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
//�����������㣨С����
using std::string; auto FloatGenerateExpression(int maxNum, bool allowDecimal, bool allowBrackets, std::vector<char> operators) {
    string expression;
    float num1, num2;
    char op1, op2;
    double roundedNum;

    // ����0.01��Ҳ����10��-2�η�
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
// ������ļ�
void outputToFile(string filename, std::vector<string> expressions) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (const auto& expression : expressions) {
            outputFile << expression << std::endl;
        }
        outputFile.close();
        std::cout << "��Ŀ�ѳɹ�������ļ���" << filename << std::endl;
    }
    else {
        std::cerr << "�޷����ļ���" << filename << std::endl;
    }
}

int main() {
    srand(time(0));

    int numQuestions, maxNum;
    bool allowDecimal, allowBrackets;
    std::vector<char> operators;
    std::vector<string> expressions;

    std::cout << "��������Ŀ������";
    std::cin >> numQuestions;
    std::cout << "�����������ֵ��";
    std::cin >> maxNum;
    std::cout << "�Ƿ�����ʹ��С����(1: �ǣ�0: ��)��";
    std::cin >> allowDecimal;
    std::cout << "�Ƿ�����ʹ�����ţ�(1: �ǣ�0: ��)��";
    std::cin >> allowBrackets;

    char op;
    std::cout << "��ѡ���������+ - * /���ÿո��������";
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
    // ������ļ�
    string filename = "math_sizeyunsuan.txt";
    outputToFile(filename, expressions);

    return 0;
}
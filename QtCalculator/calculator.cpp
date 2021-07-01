#include "calculator.hpp"
Calculator::Calculator(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);
    QFormLayout *formLayout = new QFormLayout;
    QLineEdit* input = new QLineEdit(this);
    QLabel* output = new QLabel("", this);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    formLayout->addRow("Input: ", input);
    formLayout->addRow("Output: ", output);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(2);
    QList<QString> values({ "7", "8", "9", "/", "4", "5", "6", "*", "1", "2", "3", "-", "0", "reset", "=", "+" });
    int pos = 0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            QPushButton *btn = new QPushButton(values[pos], this);
            btn->setFixedSize(40, 40);
            gridLayout->addWidget(btn, i, j);
            if (values[pos] == "=") {
                connect(btn, &QPushButton::clicked, [input, output]() {
                    QByteArray expression = input->text().toLatin1();
                    int answer = 0;
                    int workNumber = 0;
                    bool noNumber = true;
                    int fail = 0;
                    int oper = 2;
                    auto Result{[&answer, &oper, &workNumber, &fail]() {
                            if (oper == 0) {
                                answer -= workNumber;
                            }
                            else if (oper == 1) {
                                answer *= workNumber;
                            }
                            else if (oper == 2) {
                                answer += workNumber;
                            }
                            else if (oper == 3) {
                                if (workNumber == 0) {
                                    fail = 2;
                                    return;
                                }
                                answer /= workNumber;
                            }
                            workNumber = 0;
                        } };
                    for (int i = 0; i < expression.size() && !fail; ++i) {
                        if (expression[i] == '-') {
                            if (noNumber) {
                                if (i == 0) {
                                    oper = 0;
                                }
                                else {
                                    fail = 1;
                                }
                            }
                            else {
                                Result();
                                oper = 0;
                                noNumber = true;
                            }
                        }
                        else if (expression[i] == '*') {
                            if (noNumber) {
                                fail = 1;
                            }
                            else {
                                Result();
                                oper = 1;
                                noNumber = true;
                            }
                        }
                        else if (expression[i] == '+') {
                            if (noNumber) {
                                if (i == 0) {
                                    oper = 2;
                                }
                                else {
                                    fail = 1;
                                }
                            }
                            else {
                                Result();
                                oper = 2;
                                noNumber = true;
                            }
                        }
                        else if (expression[i] == '/') {
                            if (noNumber) {
                                fail = 1;
                            }
                            else {
                                Result();
                                oper = 3;
                                noNumber = true;
                            }
                        }
                        else if ('0' <= expression[i] && expression[i] <= '9') {
                            workNumber *= 10;
                            workNumber += expression[i] - '0';
                            noNumber = false;
                        }
                        else {
                            fail = 1;
                        }
                    }
                    if (fail == 0) {
                        Result();
                    }
                    if (fail != 0) {
                        output->setText((fail == 1? "Error! Wrong input!" : "Error division by zero!"));
                    }
                    else {
                        output->clear();
                        output->setText(QString::number(answer));
                    }
                });
            }
            else if (values[pos] == "reset") {
                connect(btn, &QPushButton::clicked, [input, output]() {
                    input->clear();
                    output->clear();
                });
            }
            else {
                connect(btn, &QPushButton::clicked, [input, values, pos]() {
                    QString number = input->text();
                    number.append(values[pos]);
                    input->setText(number);
                });
            }
            pos++;
        }
    }
    vbox->addLayout(formLayout);
    vbox->addLayout(gridLayout);
    setLayout(vbox);
}

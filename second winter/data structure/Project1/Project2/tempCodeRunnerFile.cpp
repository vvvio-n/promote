#include "Assistance.h"	// 实用程序软件包
#include "Polynomial.h"	// 多项式类
int main(void)
{
    char c = '1';
    Polynomial A, B, fc;
    bool hasA = false, hasB = false;
    PolyItem it;

    while (c != '0') {
        cout << "1. 输入多项式 A" << endl;
        cout << "2. 输入多项式 B" << endl;
        cout << "3. 显示多项式 A 和 B" << endl;
        cout << "4. 计算 A + B" << endl;
        cout << "5. 计算 A - B" << endl;
        cout << "6. 计算 A * B" << endl;
        cout << "7. 计算 d(A) 和 d(B)" << endl;
        cout << "8. 综合运算: A + B + d(A) + d(B)" << endl;
        cout << "9. 计算综合运算在 x 的值" << endl;
        cout << "0. 退出" << endl;
        cout << endl << "选择功能(0~9):" << endl;
        cin >> c;
        switch (c) {
        case '1':
            cout << "输入多项式 A:" << endl;
            A.input();
            hasA = true;
            break;
        case '2':
            cout << "输入多项式 B:" << endl;
            B.input();
            hasB = true;
            break;
        case '3':
            if (hasA) {
                cout << "多项式 A: ";
                A.Display();
                cout << endl;
            }
            else {
                cout << "多项式 A: 未输入！" << endl;
            }
            if (hasB) {
                cout << "多项式 B: ";
                B.Display();
                cout << endl;
            }
            else {
                cout << "多项式 B: 未输入！" << endl;
            }
            break;
        case '4':
            if (hasA && hasB) {
                cout << "A + B = ";
                (A + B).Display();
                cout << endl;
            }
            else {
                cout << "请先输入两个多项式！" << endl;
            }
            break;
        case '5':
            if (hasA && hasB) {
                cout << "A - B = ";
                (A - B).Display();
                cout << endl;

            }
            else {
                cout << "请先输入两个多项式！" << endl;
            }
            break;
        case '6':
            if (hasA && hasB) {
                cout << "A * B = ";
                (A * B).Display();
                cout << endl;

            }
            else {
                cout << "请先输入两个多项式！" << endl;
            }
            break;
        case '7':
            if (hasA) {
                cout << "d(A) = ";
                A.derivative().Display();
                cout << endl;

            }
            else {
                cout << "多项式 A 未输入！" << endl;
            }
            if (hasB) {
                cout << "d(B) = ";
                B.derivative().Display();
                cout << endl;

            }
            else {
                cout << "多项式 B 未输入！" << endl;
            }
            break;
        case '8':
            if (hasA && hasB) {
                Polynomial result = A + B + A.derivative() + B.derivative();
                cout << "A + B + d(A) + d(B) = ";
                result.Display();
                cout << endl;

            }
            else {
                cout << "请先输入两个多项式！" << endl;
            }
            break;
        case '9':
            if (hasA && hasB) {
                double x;
                cout << "输入 x 的值: ";
                cin >> x;
                double result = (A + B + A.derivative() + B.derivative()).evaluate(x);
                cout << "综合运算在 x = " << x << " 时的值: " << fixed << setprecision(2) << result << endl;
            }
            else {
                cout << "请先输入两个多项式！" << endl;
            }
            break;
        }
    }
    system("PAUSE");				// 调用库函数system()
    return 0;						// 返回值0, 返回操作系统
}

#include "Assistance.h"	// ʵ�ó��������
#include "Polynomial.h"	// ����ʽ��
int main(void)
{
    char c = '1';
    Polynomial A, B, fc;
    bool hasA = false, hasB = false;
    PolyItem it;

    while (c != '0') {
        cout << "1. �������ʽ A" << endl;
        cout << "2. �������ʽ B" << endl;
        cout << "3. ��ʾ����ʽ A �� B" << endl;
        cout << "4. ���� A + B" << endl;
        cout << "5. ���� A - B" << endl;
        cout << "6. ���� A * B" << endl;
        cout << "7. ���� d(A) �� d(B)" << endl;
        cout << "8. �ۺ�����: A + B + d(A) + d(B)" << endl;
        cout << "9. �����ۺ������� x ��ֵ" << endl;
        cout << "0. �˳�" << endl;
        cout << endl << "ѡ����(0~9):" << endl;
        cin >> c;
        switch (c) {
        case '1':
            cout << "�������ʽ A:" << endl;
            A.input();
            hasA = true;
            break;
        case '2':
            cout << "�������ʽ B:" << endl;
            B.input();
            hasB = true;
            break;
        case '3':
            if (hasA) {
                cout << "����ʽ A: ";
                A.Display();
                cout << endl;
            }
            else {
                cout << "����ʽ A: δ���룡" << endl;
            }
            if (hasB) {
                cout << "����ʽ B: ";
                B.Display();
                cout << endl;
            }
            else {
                cout << "����ʽ B: δ���룡" << endl;
            }
            break;
        case '4':
            if (hasA && hasB) {
                cout << "A + B = ";
                (A + B).Display();
                cout << endl;
            }
            else {
                cout << "����������������ʽ��" << endl;
            }
            break;
        case '5':
            if (hasA && hasB) {
                cout << "A - B = ";
                (A - B).Display();
                cout << endl;

            }
            else {
                cout << "����������������ʽ��" << endl;
            }
            break;
        case '6':
            if (hasA && hasB) {
                cout << "A * B = ";
                (A * B).Display();
                cout << endl;

            }
            else {
                cout << "����������������ʽ��" << endl;
            }
            break;
        case '7':
            if (hasA) {
                cout << "d(A) = ";
                A.derivative().Display();
                cout << endl;

            }
            else {
                cout << "����ʽ A δ���룡" << endl;
            }
            if (hasB) {
                cout << "d(B) = ";
                B.derivative().Display();
                cout << endl;

            }
            else {
                cout << "����ʽ B δ���룡" << endl;
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
                cout << "����������������ʽ��" << endl;
            }
            break;
        case '9':
            if (hasA && hasB) {
                double x;
                cout << "���� x ��ֵ: ";
                cin >> x;
                double result = (A + B + A.derivative() + B.derivative()).evaluate(x);
                cout << "�ۺ������� x = " << x << " ʱ��ֵ: " << fixed << setprecision(2) << result << endl;
            }
            else {
                cout << "����������������ʽ��" << endl;
            }
            break;
        }
    }
    system("PAUSE");				// ���ÿ⺯��system()
    return 0;						// ����ֵ0, ���ز���ϵͳ
}

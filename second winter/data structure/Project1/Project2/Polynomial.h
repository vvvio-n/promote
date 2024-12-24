#pragma once
#pragma once
#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include "LinkList.h"
#include"PolyItem.h"
#include "Assistance.h"	
#include <graphics.h>
#include <tchar.h>  
#include <cwchar>  
#include <iostream>  
using namespace std;

// ����ʽ��
class Polynomial {
protected:
    LinkList<PolyItem> polyList; // ����ʽ��ɵ����Ա�

public:
    Polynomial() {}                   // �޲ι��캯��
    ~Polynomial() {}                  // ��������
    Polynomial(const Polynomial& copy); // ���ƹ��캯��
    Polynomial(const LinkList<PolyItem>& copyLinkList); // ת�����캯��
    int Length() const;               // �����ʽ������             
    bool IsZero() const;              // �ж϶���ʽ�Ƿ�Ϊ0
    void SetZero();                   // ������ʽ��Ϊ0
    void input();
    void Display();                   // ��ʾ����ʽ
    void InsItem(const PolyItem& item); // ����һ��
    Polynomial operator +(const Polynomial& p) const; // �ӷ����������
    Polynomial operator -(const Polynomial& p) const;
    Polynomial operator *(const Polynomial& p) const;
    Polynomial& operator =(const Polynomial& copy); // ��ֵ�������
    Polynomial& operator =(const LinkList<PolyItem>& copyLinkList); // ��ֵ�������
    Polynomial derivative();
    double evaluate(double x) const; // ��ֵ
};

// ����ʽ���ʵ�ֲ���
Polynomial::Polynomial(const Polynomial& copy) { // ���ƹ��캯��
    polyList = copy.polyList;
}

Polynomial::Polynomial(const LinkList<PolyItem>& copyLinkList) { // ת�����캯��
    polyList = copyLinkList;
}

int Polynomial::Length() const { // ���ض���ʽ������
    return polyList.GetLength();
}

bool Polynomial::IsZero() const { // ����ʽΪ0���򷵻�true�����򷵻�false
    return polyList.IsEmpty();
}

void Polynomial::SetZero() { // ������ʽ��Ϊ0
    polyList.Clear();
}

void Polynomial::input() {
    polyList.Clear();
    double coef;
    int expn;
    
    while (true) {
        cout << "������ϵ����ָ�� (ϵ�� ָ��)���������������0 0��" << endl;

        if (!(cin >> coef >> expn)) {                       // ����������Ƿ���ڴ���
            cout << "��Ч���룬��������Ч�����֣�" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        if (cin.peek() != '\n') {                           // ����Ƿ��ж�������
            cout << "���棺��⵽�������룬ϵͳ�����Զ������롣" << endl;
            cin.ignore(100, '\n');
        }
        if (coef == 0 && expn == 0) {                       // �����������
            break;
        }
        if (expn < 0) {                                     // У��ָ���Ƿ�Ϊ����
            cout << "ָ������Ϊ���������������룡" << endl;
            continue;
        }
        // ����Ϸ���
        PolyItem newItem(coef, expn);
        InsItem(newItem);
        cout << "����ɹ���" << endl;
    }
    cout << "������ɡ�" << endl;
}

void Polynomial::Display() {
    // ��ʼ��ͼ�ν���
    initgraph(1000, 600);
    cleardevice();

    int pos = 1;
    PolyItem it;
    bool isFirst = true;
    Status status = polyList.GetElem(pos, it);

    // ��ʼλ��
    int xPos = 50;
    int yPos = 200;
    const int maxWidth = 900; // ÿ�������

    while (status == ENTRY_FOUND) {
        wchar_t text[100] = L"";
        // �������
        if (it.coef > 0 && pos > 1) {
            wcscat_s(text, sizeof(text) / sizeof(wchar_t), L"+");
        }
        else if (it.coef < 0) {
            wcscat_s(text, sizeof(text) / sizeof(wchar_t), L"-");
        }
        // ����ϵ��
        if (it.coef != 0) {
            if (it.coef != -1 && it.coef != 1) {
                swprintf_s(text + wcslen(text), sizeof(text) / sizeof(wchar_t) - wcslen(text), L"%.1f", fabs(it.coef));
            }
            else if (it.coef == -1 && it.expn != 0) {
                wcscat_s(text, sizeof(text) / sizeof(wchar_t), L"-");
            }
            else if ((it.coef == -1 || it.coef == 1) && it.expn == 0) {
                wcscat_s(text, sizeof(text) / sizeof(wchar_t), L"1.0");
            }
        }
        // ��⻻��
        if (xPos + wcslen(text) * 8 > maxWidth) {
            xPos = 50;
            yPos += 50;
        }
        // ����ϵ������
        outtextxy(xPos, yPos, text);
        xPos += wcslen(text) * 8;
        // ����ָ��
        if (it.expn > 1) {
            wchar_t xText[] = L"x";
            outtextxy(xPos, yPos, xText);
            xPos += wcslen(xText) * 8;
            wchar_t expnText[10];
            swprintf_s(expnText, sizeof(expnText) / sizeof(wchar_t), L"%d", it.expn);
            outtextxy(xPos, yPos - 10, expnText); // �ϱ���ʾ
            xPos += wcslen(expnText) * 8;
        }
        else if (it.expn == 1) {
            wchar_t xText[] = L"x";
            outtextxy(xPos, yPos, xText);
            xPos += wcslen(xText) * 8;
        }
        // ��ȡ��һ��
        status = polyList.GetElem(++pos, it);
        isFirst = false;
    }
    // �������ʽ���㣬��ʾ "0"
    if (isFirst) {
        wchar_t zeroText[] = L"0";
        outtextxy(50, 200, zeroText);
    }
    // �ȴ��û����������ر�ͼ�δ���
    system("pause");
    closegraph();
}


void Polynomial::InsItem(const PolyItem& node) {
    if (node.coef == 0) return; // ���ϵ��Ϊ0���򲻲���

    int pos = 1;
    PolyItem it;
    Status status = polyList.GetElem(pos, it);

    // ���Ҳ���λ��
    while (status == ENTRY_FOUND && it.expn > node.expn) {
        pos++;
        status = polyList.GetElem(pos, it);
    }

    if (status == ENTRY_FOUND && it.expn == node.expn) {
        // ָͬ����ϲ�ϵ��
        PolyItem mergedNode(it.coef + node.coef, it.expn);
        if (mergedNode.coef != 0) {
            polyList.SetElem(pos, mergedNode); // ������
        }
        else {
            PolyItem dummy;
            polyList.DeleteElem(pos, dummy); // ���ϵ���ϲ���Ϊ0����ɾ������
        }
    }
    else {
        // ��������
        polyList.InsertElem(pos, node);
    }
}

Polynomial& Polynomial::operator =(const Polynomial& copy) { // ��ֵ���������
    if (this == &copy)
        return *this;
    polyList = copy.polyList;
    return *this;
}

Polynomial& Polynomial::operator =(const LinkList<PolyItem>& copyLinkList) { // ��ֵ���������
    polyList = copyLinkList;
    return *this;
}



Polynomial Polynomial::operator +(const Polynomial& p) const { // �ӷ����������
    LinkList<PolyItem> la = polyList; // ��ǰ����ʽ��Ӧ�����Ա�
    LinkList<PolyItem> lb = p.polyList; // ����ʽp��Ӧ�����Ա�
    LinkList<PolyItem> lc; // �Ͷ���ʽ��Ӧ�����Ա�
    int aPos = 1, bPos = 1;
    PolyItem aNode, bNode;
    Status aStatus, bStatus;

    aStatus = la.GetElem(aPos++, aNode); // ȡ��la�ĵ�1�� 
    bStatus = lb.GetElem(bPos++, bNode); // ȡ��lb�ĵ�1��

    while (aStatus == ENTRY_FOUND && bStatus == ENTRY_FOUND) {
        if (aNode.expn > bNode.expn) { // la�е���aNodeָ���ϴ�
            lc.InsertElem(aNode); // ��aNode׷�ӵ�lc�ı�β 
            aStatus = la.GetElem(aPos++, aNode); // ȡ��la����һ��
        }
        else if (aNode.expn < bNode.expn) { // lb�е���bNodeָ���ϴ�
            lc.InsertElem(bNode); // ��bNode׷�ӵ�lc�ı�β
            bStatus = lb.GetElem(bPos++, bNode); // ȡ��lb����һ��
        }
        else { // la�е���aNode��lb�е���bNodeָ�����
            PolyItem sumItem(aNode.coef + bNode.coef, aNode.expn);
            if (sumItem.coef != 0)
                lc.InsertElem(sumItem); // ������ĺ�׷�ӵ�lc�ı�β
            aStatus = la.GetElem(aPos++, aNode); // ȡ��la����һ��
            bStatus = lb.GetElem(bPos++, bNode); // ȡ��lb����һ��
        }
    }

    while (aStatus == ENTRY_FOUND) { // ��la��ʣ����׷�ӵ�lc�ĺ���
        lc.InsertElem(aNode); // ��aNode׷�ӵ�lc�ĺ���
        aStatus = la.GetElem(aPos++, aNode); // ȡ��la����һ��
    }

    while (bStatus == ENTRY_FOUND) { // ��lb��ʣ����׷�ӵ�lc�ĺ���
        lc.InsertElem(bNode); // ��bNode׷�ӵ�lc�ĺ���
        bStatus = lb.GetElem(bPos++, bNode); // ȡ��lb����һ��
    }

    Polynomial fc; // �Ͷ���ʽ
    fc.polyList = lc;

    return fc;
}

Polynomial Polynomial::operator -(const Polynomial& p) const { //�������������
    LinkList<PolyItem> la = polyList, lb = p.polyList, lc;
    int aPos = 1, bPos = 1;
    PolyItem aItem, bItem;
    Status aStatus = la.GetElem(aPos++, aItem);
    Status bStatus = lb.GetElem(bPos++, bItem);

    while (aStatus == ENTRY_FOUND || bStatus == ENTRY_FOUND) {
        if (aStatus == ENTRY_FOUND && (bStatus != ENTRY_FOUND || aItem.expn > bItem.expn)) {
            lc.InsertElem(aItem); 
            aStatus = la.GetElem(aPos++, aItem); 
        }
        else if (bStatus == ENTRY_FOUND && (aStatus != ENTRY_FOUND || aItem.expn < bItem.expn)) {
            PolyItem subItem(-bItem.coef, bItem.expn);
            lc.InsertElem(subItem);
            bStatus = lb.GetElem(bPos++, bItem); 
        }
        else if (aItem.expn == bItem.expn) {
            PolyItem diffItem(aItem.coef - bItem.coef, aItem.expn);
            if (diffItem.coef != 0) lc.InsertElem(diffItem);
            aStatus = la.GetElem(aPos++, aItem); 
            bStatus = lb.GetElem(bPos++, bItem);
        }
    } 
    Polynomial fc;
    fc.polyList = lc;
    return fc;
}


Polynomial Polynomial::operator *(const Polynomial& p) const {
    LinkList<PolyItem> la = polyList;  
    LinkList<PolyItem> lb = p.polyList; 
    LinkList<PolyItem> lc;
    int aPos = 1, bPos = 1;
    PolyItem aItem, bItem;

    // ������һ������ʽ
    while (la.GetElem(aPos++, aItem) == ENTRY_FOUND) {
        bPos = 1;
        // �����ڶ�������ʽ
        while (lb.GetElem(bPos++, bItem) == ENTRY_FOUND) {
            PolyItem productItem(aItem.coef * bItem.coef, aItem.expn + bItem.expn);
            int pos = 1;
            bool found = false;
            PolyItem cItem;
            // �����Ƿ�������ָͬ������
            while (lc.GetElem(pos, cItem) == ENTRY_FOUND) {
                if (cItem.expn == productItem.expn) {
                    // ����ҵ���ָͬ������ϲ�ϵ��
                    cItem.coef += productItem.coef;
                    if (cItem.coef != 0) {
                        lc.InsertElem(cItem);  // ����ϲ������
                    } else {
                        lc.DeleteElem(pos, cItem);  // ϵ��Ϊ0ʱɾ������
                    }
                    found = true;
                    break;
                }
                pos++;
            }
            // ���û���ҵ���ָͬ�����������µĳ˻���
            if (!found && productItem.coef != 0) {
                lc.InsertElem(productItem);
            }
        }
    }
    Polynomial fc;
    fc.polyList = lc;  // ���ؽ��
    return fc;
}

Polynomial Polynomial::derivative() { // ��
    LinkList<PolyItem> la = polyList, lc;
    int pos = 1;
    PolyItem item;
    Status astatus = la.GetElem(pos++, item);
    while (astatus == ENTRY_FOUND) {
        PolyItem productItem(item.coef * item.expn, item.expn - 1);
        lc.InsertElem(productItem);
        astatus = la.GetElem(pos++, item);  // ȡ��la����һ��
    }
    Polynomial fc;                             // �������ʽ
    fc.polyList = lc;
    return fc;
}

double Polynomial::evaluate(double x) const { // ����ʽ��ֵ
    LinkList<PolyItem> la = polyList;
    double sum = 0;
    int pos = 1;
    PolyItem item;
    Status status = la.GetElem(pos++, item);
    while (status == ENTRY_FOUND) {
        sum += item.coef * pow(x, item.expn);
        status = polyList.GetElem(pos++, item);
    }
    return sum;
}

#endif

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

// 多项式类
class Polynomial {
protected:
    LinkList<PolyItem> polyList; // 多项式组成的线性表

public:
    Polynomial() {}                   // 无参构造函数
    ~Polynomial() {}                  // 析构函数
    Polynomial(const Polynomial& copy); // 复制构造函数
    Polynomial(const LinkList<PolyItem>& copyLinkList); // 转换构造函数
    int Length() const;               // 求多项式的项数             
    bool IsZero() const;              // 判断多项式是否为0
    void SetZero();                   // 将多项式置为0
    void input();
    void Display();                   // 显示多项式
    void InsItem(const PolyItem& item); // 插入一项
    Polynomial operator +(const Polynomial& p) const; // 加法运算符重载
    Polynomial operator -(const Polynomial& p) const;
    Polynomial operator *(const Polynomial& p) const;
    Polynomial& operator =(const Polynomial& copy); // 赋值语句重载
    Polynomial& operator =(const LinkList<PolyItem>& copyLinkList); // 赋值语句重载
    Polynomial derivative();
    double evaluate(double x) const; // 求值
};

// 多项式类的实现部分
Polynomial::Polynomial(const Polynomial& copy) { // 复制构造函数
    polyList = copy.polyList;
}

Polynomial::Polynomial(const LinkList<PolyItem>& copyLinkList) { // 转换构造函数
    polyList = copyLinkList;
}

int Polynomial::Length() const { // 返回多项式的项数
    return polyList.GetLength();
}

bool Polynomial::IsZero() const { // 多项式为0，则返回true，否则返回false
    return polyList.IsEmpty();
}

void Polynomial::SetZero() { // 将多项式置为0
    polyList.Clear();
}

void Polynomial::input() {
    polyList.Clear();
    double coef;
    int expn;
    
    while (true) {
        cout << "请输入系数和指数 (系数 指数)，输入结束请输入0 0：" << endl;

        if (!(cin >> coef >> expn)) {                       // 检查输入流是否存在错误
            cout << "无效输入，请输入有效的数字！" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        if (cin.peek() != '\n') {                           // 检查是否有额外输入
            cout << "警告：检测到额外输入，系统将忽略额外输入。" << endl;
            cin.ignore(100, '\n');
        }
        if (coef == 0 && expn == 0) {                       // 输入结束条件
            break;
        }
        if (expn < 0) {                                     // 校验指数是否为负数
            cout << "指数不能为负数，请重新输入！" << endl;
            continue;
        }
        // 插入合法项
        PolyItem newItem(coef, expn);
        InsItem(newItem);
        cout << "输入成功！" << endl;
    }
    cout << "输入完成。" << endl;
}

void Polynomial::Display() {
    // 初始化图形界面
    initgraph(1000, 600);
    cleardevice();

    int pos = 1;
    PolyItem it;
    bool isFirst = true;
    Status status = polyList.GetElem(pos, it);

    // 起始位置
    int xPos = 50;
    int yPos = 200;
    const int maxWidth = 900; // 每行最大宽度

    while (status == ENTRY_FOUND) {
        wchar_t text[100] = L"";
        // 处理符号
        if (it.coef > 0 && pos > 1) {
            wcscat_s(text, sizeof(text) / sizeof(wchar_t), L"+");
        }
        else if (it.coef < 0) {
            wcscat_s(text, sizeof(text) / sizeof(wchar_t), L"-");
        }
        // 处理系数
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
        // 检测换行
        if (xPos + wcslen(text) * 8 > maxWidth) {
            xPos = 50;
            yPos += 50;
        }
        // 绘制系数部分
        outtextxy(xPos, yPos, text);
        xPos += wcslen(text) * 8;
        // 处理指数
        if (it.expn > 1) {
            wchar_t xText[] = L"x";
            outtextxy(xPos, yPos, xText);
            xPos += wcslen(xText) * 8;
            wchar_t expnText[10];
            swprintf_s(expnText, sizeof(expnText) / sizeof(wchar_t), L"%d", it.expn);
            outtextxy(xPos, yPos - 10, expnText); // 上标显示
            xPos += wcslen(expnText) * 8;
        }
        else if (it.expn == 1) {
            wchar_t xText[] = L"x";
            outtextxy(xPos, yPos, xText);
            xPos += wcslen(xText) * 8;
        }
        // 获取下一项
        status = polyList.GetElem(++pos, it);
        isFirst = false;
    }
    // 如果多项式是零，显示 "0"
    if (isFirst) {
        wchar_t zeroText[] = L"0";
        outtextxy(50, 200, zeroText);
    }
    // 等待用户按任意键后关闭图形窗口
    system("pause");
    closegraph();
}


void Polynomial::InsItem(const PolyItem& node) {
    if (node.coef == 0) return; // 如果系数为0，则不插入

    int pos = 1;
    PolyItem it;
    Status status = polyList.GetElem(pos, it);

    // 查找插入位置
    while (status == ENTRY_FOUND && it.expn > node.expn) {
        pos++;
        status = polyList.GetElem(pos, it);
    }

    if (status == ENTRY_FOUND && it.expn == node.expn) {
        // 同指数项，合并系数
        PolyItem mergedNode(it.coef + node.coef, it.expn);
        if (mergedNode.coef != 0) {
            polyList.SetElem(pos, mergedNode); // 更新项
        }
        else {
            PolyItem dummy;
            polyList.DeleteElem(pos, dummy); // 如果系数合并后为0，则删除该项
        }
    }
    else {
        // 插入新项
        polyList.InsertElem(pos, node);
    }
}

Polynomial& Polynomial::operator =(const Polynomial& copy) { // 赋值运算符重载
    if (this == &copy)
        return *this;
    polyList = copy.polyList;
    return *this;
}

Polynomial& Polynomial::operator =(const LinkList<PolyItem>& copyLinkList) { // 赋值运算符重载
    polyList = copyLinkList;
    return *this;
}



Polynomial Polynomial::operator +(const Polynomial& p) const { // 加法运算符重载
    LinkList<PolyItem> la = polyList; // 当前多项式对应的线性表
    LinkList<PolyItem> lb = p.polyList; // 多项式p对应的线性表
    LinkList<PolyItem> lc; // 和多项式对应的线性表
    int aPos = 1, bPos = 1;
    PolyItem aNode, bNode;
    Status aStatus, bStatus;

    aStatus = la.GetElem(aPos++, aNode); // 取出la的第1项 
    bStatus = lb.GetElem(bPos++, bNode); // 取出lb的第1项

    while (aStatus == ENTRY_FOUND && bStatus == ENTRY_FOUND) {
        if (aNode.expn > bNode.expn) { // la中的项aNode指数较大
            lc.InsertElem(aNode); // 将aNode追加到lc的表尾 
            aStatus = la.GetElem(aPos++, aNode); // 取出la的下一项
        }
        else if (aNode.expn < bNode.expn) { // lb中的项bNode指数较大
            lc.InsertElem(bNode); // 将bNode追加到lc的表尾
            bStatus = lb.GetElem(bPos++, bNode); // 取出lb的下一项
        }
        else { // la中的项aNode和lb中的项bNode指数相等
            PolyItem sumItem(aNode.coef + bNode.coef, aNode.expn);
            if (sumItem.coef != 0)
                lc.InsertElem(sumItem); // 将两项的和追加到lc的表尾
            aStatus = la.GetElem(aPos++, aNode); // 取出la的下一项
            bStatus = lb.GetElem(bPos++, bNode); // 取出lb的下一项
        }
    }

    while (aStatus == ENTRY_FOUND) { // 将la的剩余项追加到lc的后面
        lc.InsertElem(aNode); // 将aNode追加到lc的后面
        aStatus = la.GetElem(aPos++, aNode); // 取出la的下一项
    }

    while (bStatus == ENTRY_FOUND) { // 将lb的剩余项追加到lc的后面
        lc.InsertElem(bNode); // 将bNode追加到lc的后面
        bStatus = lb.GetElem(bPos++, bNode); // 取出lb的下一项
    }

    Polynomial fc; // 和多项式
    fc.polyList = lc;

    return fc;
}

Polynomial Polynomial::operator -(const Polynomial& p) const { //减法运算符重载
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

    // 遍历第一个多项式
    while (la.GetElem(aPos++, aItem) == ENTRY_FOUND) {
        bPos = 1;
        // 遍历第二个多项式
        while (lb.GetElem(bPos++, bItem) == ENTRY_FOUND) {
            PolyItem productItem(aItem.coef * bItem.coef, aItem.expn + bItem.expn);
            int pos = 1;
            bool found = false;
            PolyItem cItem;
            // 查找是否已有相同指数的项
            while (lc.GetElem(pos, cItem) == ENTRY_FOUND) {
                if (cItem.expn == productItem.expn) {
                    // 如果找到相同指数的项，合并系数
                    cItem.coef += productItem.coef;
                    if (cItem.coef != 0) {
                        lc.InsertElem(cItem);  // 插入合并后的项
                    } else {
                        lc.DeleteElem(pos, cItem);  // 系数为0时删除该项
                    }
                    found = true;
                    break;
                }
                pos++;
            }
            // 如果没有找到相同指数的项，则插入新的乘积项
            if (!found && productItem.coef != 0) {
                lc.InsertElem(productItem);
            }
        }
    }
    Polynomial fc;
    fc.polyList = lc;  // 返回结果
    return fc;
}

Polynomial Polynomial::derivative() { // 求导
    LinkList<PolyItem> la = polyList, lc;
    int pos = 1;
    PolyItem item;
    Status astatus = la.GetElem(pos++, item);
    while (astatus == ENTRY_FOUND) {
        PolyItem productItem(item.coef * item.expn, item.expn - 1);
        lc.InsertElem(productItem);
        astatus = la.GetElem(pos++, item);  // 取出la的下一项
    }
    Polynomial fc;                             // 结果多项式
    fc.polyList = lc;
    return fc;
}

double Polynomial::evaluate(double x) const { // 多项式求值
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

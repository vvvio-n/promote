#ifndef KEEPACCOUNT_H
#define KEEPACCOUNT_H
#include "LinkList.h"
#include <iomanip>

//KeepAccount.h
    //此处写各种类的声明  以及数据如何存放才能实现case1和case2的功能

class BWB{
    public:
        void Setpay(const double &food=0,const double &entertain=0,const double &life =0,const double &others = 0);
        void Setincome(const double &income=0);
        void SetBalance();
        friend class Date;           //允许 Date 类访问 BWB 类的私有成员
        template<typename T>
        friend class LinkList;
        void Show();
    protected:
        double pay,income,balance,food,entertain,life,others;
};

class Date{
     public:
        void AppendBWB(const BWB &b);
        void Set(const int &month,const int &day);
        void Show();
        void OutfileD(const char *filename);
        template<typename T>
        friend class LinkList;
     protected:
        int month,day;
        LinkList<BWB> link;
};





#endif

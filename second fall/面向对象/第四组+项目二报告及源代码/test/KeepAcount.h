#ifndef KEEPACCOUNT_H
#define KEEPACCOUNT_H
#include "LinkList.h"
#include <iomanip>

//KeepAccount.h
    //�˴�д�����������  �Լ�������δ�Ų���ʵ��case1��case2�Ĺ���

class BWB{
    public:
        void Setpay(const double &food=0,const double &entertain=0,const double &life =0,const double &others = 0);
        void Setincome(const double &income=0);
        void SetBalance();
        friend class Date;           //���� Date ����� BWB ���˽�г�Ա
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

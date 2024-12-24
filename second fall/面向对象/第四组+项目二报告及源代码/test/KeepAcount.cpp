#include "KeepAcount.h"
#include <iomanip>
#include<fstream>
using namespace std;

void Date::Set(const int &Month,const int &Day)
{
	month=Month;
	day=Day;
}

void BWB::Setpay(const double &Food,const double &Entertain,const double &Life,const double &Others)
{
	food = Food;
	entertain = Entertain;
	life = Life;
	others = Others;
	pay=food+entertain+life+others;
}

void BWB::Setincome(const double &Income){
    income=Income;
    balance=income-pay;//����Ľ���
}

void Date::Show(){
    cout<<setw(3)<<month<<"��"<<setw(3)<<day<<"��";
    cout<<"  �Ե�:"<<setw(5)<<link.head->data.food<<"  ���:"<<setw(5)<<link.head->data.entertain;
    cout<<"  �õ�:"<<setw(5)<<link.head->data.life<<"  ����:"<<setw(5)<<link.head->data.others;
    cout<<"  ��֧��"<<setw(5)<<link.head->data.pay<<"  ������"<<setw(5)<<link.head->data.income;
    cout<<"  ���ս���Ϊ��"<<link.head->data.balance<<endl;
}

void Date::OutfileD(const char *filename){
    ofstream outfile("out.txt",ios::app);
//	if(outfile.fail())
//		return 0;
    outfile<<month<<"_"<<day<<"_";
    outfile<<"__food:"<<link.head->data.food<<"__entertain:"<<link.head->data.entertain;
    outfile<<"__life:"<<link.head->data.life<<"__others:"<<link.head->data.others;
    outfile<<"__pay:"<<link.head->data.pay<<"__income:"<<link.head->data.income;
    outfile<<"__balance:"<<link.head->data.balance<<endl;
//    if()
        outfile.close();
}

void BWB::Show(){
}

void Date::AppendBWB(const BWB &b)
{
//	double x;
	BWB y(b);
//	if(link.NumNodes()==0)
//		x = 0;
//	else
//	{
//		link.GoBottom();
//		x = link.CurData().balance;
//	}
//	y.balance = x + b.money;	// �������
	link.Append(y);				// ���һ����ˮ��¼
}




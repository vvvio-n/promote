#include "LinkList.h"
#include "KeepAcount.h"
#include <conio.h>
#include<ctime>
#include<cstdlib>

using namespace std;

void KATest(){
//    time_t x;
//    LinkList<Date> uLink;//����ʱhead=null,cur_node=null,num=0
//    Date xDate;
//    Node<Date> *pU;
//    BWB xBWB;
//    int choice,year,month,day;
//    double pay,income,balance,food,entertain,life,others,asset=0;
//    char id[80],str[80];

while(true){
        time_t x;
        LinkList<Date> uLink;//����ʱhead=null,cur_node=null,num=0
        Date xDate;
        Node<Date> *pU;
        BWB xBWB;
        int choice,year,month,day;
        double pay,income,balance,food,entertain,life,others,asset=0;
        char id[80],str[80];

        cout<<"~~O(��_��)O~~С";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��";x=clock();while(clock()<x+250){}
        cout<<"��\n";

    cout<<"��������������������������������������������������������100%"<<endl;
    cout<<"��ӭ�������ӼӼ��ˣ��������ɾ���ǰ������������(��^O^��)"<<endl<<endl;
    cout<<"��¼-�����������û�����";
    cin>>id;//�Ӽ��̻�ȡ�ַ�����id�У���80����������ֹ��ֹͣ
    cout<<endl<<"��������ݣ�";
    cin>>year;


while(true){
    cout<<endl;
    cout<<"1�������ɼ���"<<endl;
    cout<<"2���������Լ����˵ķṦΰҵ"<<endl;
    cout<<"0�����ҽ��˳���¼"<<endl;
    cout<<"��Ҫ��";
    choice=getche()-'0';
    cout<<endl<<endl;
    if(choice<=0)    break;

    switch(choice){
        case 1:
        cout<<"������������(��ʽ��:8 25)��";
        cin>>month>>day;
        //cin.getline(str, 80);//�����з�
            //�˴�ʵ���������ݵĲ���ͼ���(��д֧���ٷֱ��Զ����㺯����)�����ѡ���Ƿ����
        xDate.Set(month,day);
        uLink.AppendDate(xDate);
        cout << "Ǯ��ʹʹ��Ǯ����ȥ����(��ʽ��55 38.5 88 0)"<<endl<<"�Ե� ��� ���� ����"<<endl;
        cin >> food>>entertain>>life>>others;
        //cin.getline(str, 80);
        xBWB.Setpay(food,entertain,life,others);//������һ����ֵ��BWB
        cout<<"��ô����������ǣ�(����������0)��";
        cin >> income;
        xBWB.Setincome(income);//����һ��bwb�����б�������ֵ���
        uLink.CurData().AppendBWB(xBWB);

            break;

        case 2:
            //�˴������û�ѡ������ĸ�ʽ ����Ҫ�����·ݵ�   ����Ҫ�����뻹��֧��   ����Ҫ��ʲô���͵�֧��ռ�İٷֱ�
            cout << endl;
            cout <<"�������뿴���ǣ�"<<endl;
			cout << "1 -- �ҵ�������֧ �Ҷ�Ҫ��" << endl;
			cout << "2 -- ĳ�·ݸ���֧���ٷֱ�" << endl;
			cout << "3 -- ĳ������֧�����" << endl;
			cout<<"0������������ ����"<<endl;
			cout << "��ѡ��:";
			choice = getche() - '0';
			cout << endl;
			if(choice<=0) break;
			switch(choice)
			{
			case 1:
			    cout<<endl<<id<<"  "<<year<<endl;
                cout << uLink<< endl;
                uLink.Save("OUTPUT.txt");
                cout<<"С���ոհ����˰ѱ���ļ�¼�������ޣ���ȥ������~(,,^w^,,)~"<<endl;
                break;
			case 2:
			    int temmon;
			    cout<<endl<<"������Ҫ��ѯ���·�"<<endl;
			    cin>>temmon;
			    cout<<"������"<<temmon<<"�������ﻨ��Ǯ���ɣ�"<<endl;
                uLink.Perctg(temmon);
			    break;
			case 3:
			    int temMon;
			    cout<<endl<<"������Ҫ��ѯ���·�"<<endl;
			    cin>>temMon;
			    cout<<temMon<<"�����룺"<<uLink.SearchMonthIncome(temMon)<<endl;
			    cout<<temMon<<"��֧����"<<uLink.SearchMonthPay(temMon)<<endl;
			    cout<<temMon<<"�½��ࣺ"<<uLink.SearchMonthBalance(temMon)<<endl;
                break;
			}

            break;

    }
}
    break;
    uLink.FreeList();

}


}

#include "LinkList.h"
#include "KeepAcount.h"
#include <conio.h>
#include<ctime>
#include<cstdlib>

using namespace std;

void KATest(){
//    time_t x;
//    LinkList<Date> uLink;//创建时head=null,cur_node=null,num=0
//    Date xDate;
//    Node<Date> *pU;
//    BWB xBWB;
//    int choice,year,month,day;
//    double pay,income,balance,food,entertain,life,others,asset=0;
//    char id[80],str[80];

while(true){
        time_t x;
        LinkList<Date> uLink;//创建时head=null,cur_node=null,num=0
        Date xDate;
        Node<Date> *pU;
        BWB xBWB;
        int choice,year,month,day;
        double pay,income,balance,food,entertain,life,others,asset=0;
        char id[80],str[80];

        cout<<"~~O(∩_∩)O~~小";x=clock();while(clock()<x+250){}
        cout<<"吸";x=clock();while(clock()<x+250){}
        cout<<"很";x=clock();while(clock()<x+250){}
        cout<<"快";x=clock();while(clock()<x+250){}
        cout<<"就";x=clock();while(clock()<x+250){}
        cout<<"加";x=clock();while(clock()<x+250){}
        cout<<"载";x=clock();while(clock()<x+250){}
        cout<<"好";x=clock();while(clock()<x+250){}
        cout<<"啦";x=clock();while(clock()<x+250){}
        cout<<"！\n";

    cout<<"————————————————————————————100%"<<endl;
    cout<<"欢迎光临吸加加记账！财务自由就在前方，请继续坚持(★^O^★)"<<endl<<endl;
    cout<<"登录-请输入您的用户名：";
    cin>>id;//从键盘获取字符放入id中，到80个或遇到终止符停止
    cout<<endl<<"请输入年份：";
    cin>>year;


while(true){
    cout<<endl;
    cout<<"1——自律记账"<<endl;
    cout<<"2——看看自己记账的丰功伟业"<<endl;
    cout<<"0——我将退出登录"<<endl;
    cout<<"我要：";
    choice=getche()-'0';
    cout<<endl<<endl;
    if(choice<=0)    break;

    switch(choice){
        case 1:
        cout<<"请输入日期喵(格式如:8 25)：";
        cin>>month>>day;
        //cin.getline(str, 80);//处理换行符
            //此处实现链表数据的插入和计算(编写支出百分比自动计算函数等)，最后选择是否存盘
        xDate.Set(month,day);
        uLink.AppendDate(xDate);
        cout << "钱包痛痛，钱花出去啦：(格式如55 38.5 88 0)"<<endl<<"吃的 玩的 日用 其他"<<endl;
        cin >> food>>entertain>>life>>others;
        //cin.getline(str, 80);
        xBWB.Setpay(food,entertain,life,others);//创建了一条有值的BWB
        cout<<"那么今天的收入是？(若无请输入0)：";
        cin >> income;
        xBWB.Setincome(income);//现在一个bwb里所有变量都赋值完毕
        uLink.CurData().AppendBWB(xBWB);

            break;

        case 2:
            //此处先让用户选择输出的格式 比如要看几月份的   或者要看收入还是支出   或者要看什么类型的支出占的百分比
            cout << endl;
            cout <<"请问你想看的是？"<<endl;
			cout << "1 -- 我的所有收支 我都要看" << endl;
			cout << "2 -- 某月份各种支出百分比" << endl;
			cout << "3 -- 某月总收支和余额" << endl;
			cout<<"0——按错了喵 返回"<<endl;
			cout << "我选择:";
			choice = getche() - '0';
			cout << endl;
			if(choice<=0) break;
			switch(choice)
			{
			case 1:
			    cout<<endl<<id<<"  "<<year<<endl;
                cout << uLink<< endl;
                uLink.Save("OUTPUT.txt");
                cout<<"小吸刚刚帮主人把宝贵的记录存盘了噢！快去看看吧~(,,^w^,,)~"<<endl;
                break;
			case 2:
			    int temmon;
			    cout<<endl<<"输入想要查询的月份"<<endl;
			    cin>>temmon;
			    cout<<"看看你"<<temmon<<"月在哪里花的钱最多吧！"<<endl;
                uLink.Perctg(temmon);
			    break;
			case 3:
			    int temMon;
			    cout<<endl<<"输入想要查询的月份"<<endl;
			    cin>>temMon;
			    cout<<temMon<<"月收入："<<uLink.SearchMonthIncome(temMon)<<endl;
			    cout<<temMon<<"月支出："<<uLink.SearchMonthPay(temMon)<<endl;
			    cout<<temMon<<"月结余："<<uLink.SearchMonthBalance(temMon)<<endl;
                break;
			}

            break;

    }
}
    break;
    uLink.FreeList();

}


}

#include<fstream>
#include<ctype.h>
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
using namespace std;

class account //the definition of class used in the program
{   public: int acno; char name[50]; 
    int deposit;
    char type;
    
    void create_account() //function to get data from user
    {   cout<<"\nEnter The account No. :"; 
        cin>>acno;
        cout<<"\n\nEnter The Name of The account Holder : ";
        gets(name);
        cout<<"\nEnter Type of The account (C/S) : ";
        cin>>type;
        type=toupper(type);
        cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current): ";
        cin>>deposit;
        cout<<"\n\n\nAccount Created..";
    }

    void show_account() //function to show data on screen
    {   cout<<"\nAccount No. : "<<acno; 
        cout<<"\nAccount Holder Name : "<<name; 
        cout<<"\nType of Account : "<<type;
        cout<<"\nBalance amount : "<<deposit;
    }

    void modify_accnt() //function to get new data from user

    {   cout<<"\nThe account No."<<acno; 
        cout<<"\n\nEnter The Name of The account Holder : ";
        gets(name);
        cout<<"\nEnter Type of The account (C/S) : "; 
        cin>>type;
        type=toupper(type); cout<<"\nEnter The amount : "; 
        cin>>deposit;
    }

    void dep(int x) //function to accept amount and add to balance amount
    {   deposit+=x;
    }

    void draw(int x) //function to accept amount and subtract from balance amount
    {   deposit-=x;
    }

    void report() //function to show data in tabular format 
    {    cout<<acno<<setw(15)<<""<<name<<setw(15); 
        cout<<""<<type<<setw(10)<<deposit<<endl;
    }

    int showacno() //function to show account number
    {   return acno;
    }

    int showdeposit() //function to show balance amount 
    { return deposit;
    }    
    
    char showtype() //function to show type of account
    {   return type;
    }

};



//	function to write in file 
void write_account()
{   account ac; 
    ofstream outFile; 
    outFile.open("account.dat",ios::binary|ios::app); 
    ac.create_account();
    outFile.write((char *) &ac, sizeof(account)); 
    outFile.close();
}



//	function to read specific record from file 
void display_sp(int n)
{   account ac; 
    int flag=0; 
    ifstream inFile; 
    inFile.open("account.dat",ios::binary); 
    if(!inFile)
    {   cout<<"File could not be open !! Press any Key...";
        return;
    }

    cout<<"\nBALANCE DETAILS\n"; 
    while(inFile.read((char *) &ac, sizeof(account))) 
    {   if(ac.acno==n)
        {   ac.show_account();
            flag=1;
        }
    }

    inFile.close();
    if(flag==0)
        cout<<"\n\nAccount number does not exist";

}
 
 

//	function to modify record of file 
void modify_account(int n)
{   int found=0; 
    account ac; 
    fstream File; 
    File.open("account.dat",ios::binary|ios::in|ios::out); 
    if(!File)
    {   cout<<"File could not be open !! Press any Key...";
        return;
    }

    while(File.read((char *) &ac, sizeof(account)) && found==0)
    {   if(ac.acno==n)
        {   ac.show_account(); 
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify_accnt();
            int pos=(-1)*sizeof(account); 
            File.seekp(pos,ios::cur); 
            File.write((char *) &ac, sizeof(account)); 
            cout<<"\n\n\t Record Updated"; 
            found=1;
        }
    }

    File.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";

}



//	function to delete record of file 
void delete_account(int n)
{   account ac; 
    ifstream inFile; 
    ofstream outFile; 
    inFile.open("account.dat",ios::binary); 
    if(!inFile)
    {   cout<<"File could not be open !! Press any Key...";
        return;
    }

    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg); 
    while(inFile.read((char *) &ac, sizeof(account))) 
    {   if(ac.acno!=n)
        {   outFile.write((char *) &ac, sizeof(account));
        }
    }

    inFile.close();
    outFile.close();
    remove("account.dat"); 
    rename("Temp.dat","account.dat"); 
    cout<<"\n\n\tRecord Deleted ..";

}
 
 



//	function to display all accounts deposit list 
void display_all()
{   account ac; 
    ifstream inFile; 
    inFile.open("account.dat",ios::binary); 
    if(!inFile)
    {   cout<<"File could not be open !! Press any Key...";
        return;
    }
    
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n"; 
    cout<<"A/c no. NAME Type Balance\n"; 
    while(inFile.read((char *) &ac, sizeof(account))) 
    {   ac.report();
    }

    inFile.close();

}



//	function to deposit and withdraw amounts 
void deposit_withdraw(int n, int option)
{   int amt;
    int found=0; 
    account ac; 
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out); 
    if(!File)
    {   cout<<"File could not be open !! Press any Key...";
        return;
    }

    while(File.read((char *) &ac, sizeof(account)) && found==0)
    {   if(ac.acno==n)
        {   ac.show_account();
            if(option==1)
            {   cout<<"\n\n\tTO DEPOSIT AMOUNT "; 
                cout<<"\n\nEnter The amount to be deposited";
                cin>>amt;
               ac.dep(amt);
            }
            if(option==2)
            {   cout<<"\n\n\tTO WITHDRAW AMOUNT";
                cout<<"\n\nEnter The amount to be withdraw";
                cin>>amt;
                int bal=ac.showdeposit()-amt; 
                if((bal<500 && ac.showtype()=='S') || (bal<1000 && ac.showtype()=='C')) 
                    cout<<"Insufficient balance"; 
                else
                    ac.draw(amt);
            }

            int pos=(-1)* sizeof(ac); 
            File.seekp(pos,ios::cur); 
            File.write((char *) &ac, sizeof(account)); 
            cout<<"\n\n\t Record Updated"; 
            found=1;
        }
    }
    File.close();
    if(found==0)    
        cout<<"\n\n Record Not Found ";

}



//the main function of the program 

void main()
{   char ch; 
    int num; 
    clrscr(); 
    do
    {   clrscr(); 
        cout<<"\n\n\n\tMAIN MENU"; 
        cout<<"\n\n\t01. NEW ACCOUNT"; 
        cout<<"\n\n\t02. DEPOSIT AMOUNT"; 
        cout<<"\n\n\t03. WITHDRAW AMOUNT"; 
        cout<<"\n\n\t04. BALANCE ENQUIRY"; 
        cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST"; 
        cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;
        clrscr();
        switch(ch)
        {   case '1':
                write_account(); 
                break;

            case '2':
                cout<<"\n\n\tEnter The account No. : "; 
                cin>>num;
                deposit_withdraw(num, 1);
                break;

            case '3':
                cout<<"\n\n\tEnter The account No. : "; 
                cin>>num;
                deposit_withdraw(num, 2);
                break;

            case '4':
                cout<<"\n\n\tEnter The account No. : "; 
                cin>>num;
                display_sp(num);
                break;

            case '5':
                display_all();
                break;

            case '6':
                cout<<"\n\n\tEnter The account No. : "; 
                cin>>num;
                delete_account(num);
                break;

            case '7':
                cout<<"\n\n\tEnter The account No. : "; 
                cin>>num;
                modify_account(num);
                break;

            case '8':
                cout<<"\n\n\tThanks for using Bank Management System";
                break;
                default :cout<<"\a";

        }
        getch();
    }while(ch!='8');

}
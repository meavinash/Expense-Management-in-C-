#include<iostream>
#include<string.h>
#include<fstream>

using namespace std;


class client{
protected:
    string pass;

public:
    void set_pass(){
        cout<<"Enter the  password:\n";
        cin>>pass;
    }

    string get_pass(){
        return pass;
    }



};  


class expense{
public:
    char date[20];
    char title[20];
    double exp;

public:

    void set_data(){
        cout<<"\nDate should be in the format\n i.e. day/moth/year eg 12/5/2018\n";
        cout<<"Enter the whole date\n";
        cin>>date;
        cout<<"Give title for expense\n";
        cin>>title;
        cout<<"Enter the total expense\n";
        cin>>exp;
    }

    void get_data(){
        cout<<"\tDate :: ";
        cout<<date;
        cout<<"\tTitle :: ";
        cout<<title;
        cout<<"\tExpense :: ";
        cout<<exp;
    }

};



//function header file
int check(client &);
bool Login(client &);
void menu();
//header files above

// main program
int count=0;
double tot=0;
int main()
{

    char ch;
    int opt;// option for the user to get
    client obj;
    //logic behind password and login
    do{
        cout<<"\n\t Press 1: Update password\n\t Press 2: Login\n";
        cin>>opt;
        if(opt==1){
            ofstream fs;
            fs.open("pass.txt");
            cout<<"Create a Password:\n";
            obj.set_pass();
            fs<<obj.get_pass();
            fs.close();
        }
        else if(opt==2){
            check(obj);
        }

        else{
            cout<<"*Incorrect Password*\n";
        }
        cout<<"\nDo you want to access Login again?(y/n)\n";
        cin>>ch;
    }while(ch=='y' || ch=='Y');// loop until the user want it

    return 0;
}

//send signal about login
bool Login(client &obj){

    string tpass;
    ifstream ff("pass.txt");  //this is shortcut method
    ff>>tpass;
    cout<<"Enter the Login-password: \n";
    obj.set_pass();
    if(tpass==obj.get_pass()){
        return 1;//login sigal 1
    }
    else
        return 0; //login sigal 0

}

int check(client &obj){
//you should declare here
    if(Login(obj)){
        cout<<"\n\nYou are Logged-in\n";
        menu();

    }
    else{
        count++;//counter for login no.
        if(count==4){
            cout<<"*You are out of chances*\n \nProgram will close....\n";
            return 1;
        }
        cout<<"\t*Incorrect Password\n ";
        cout<<"You have "<<(4-count)<<" chances left\n";
        check(obj);

    }
}

void menu(){
    int ch;
    int n;
    int i;
    char choice;
  	char  dd[20];
    int flag=0;

    
    do {
        expense exe;
        fstream fp;
        fp.open("Expense.dat",ios::app | ios::out | ios::in | ios::binary);
        cout << "\n --------------------------------------- \n";
        cout << "Welcome to the Expense Management System" << endl;
        cout << "1.Enter the expense.\n";
        cout << "2.Display all the expenses.\n";
        cout << "3.Find expense for a particular date.\n";
        cout << "4.Display the total expenditure.\n";
        cout << "\nEnter the choice :: \n";
        cin >> ch;
        switch (ch) {
            case 1:
                exe.set_data();
                fp.write(reinterpret_cast<char *>(&exe), sizeof(expense));
                fp.close();
                break;

            case 2:
            	fp.seekg(0,ios::beg);
                cout << "All the expenses are listed below ::\n";
                fp.read(reinterpret_cast<char *>(&exe), sizeof(expense));
                exe.get_data();
                while (fp.read(reinterpret_cast<char *>(&exe), sizeof(expense)))
                {
                	cout<<"\n";
                    exe.get_data();
     
                }
				break;

            case 3:
            cout<<"Enter the date:\n";
            cin>>dd;
            fp.seekg(0,ios::beg);
            while (fp.read(reinterpret_cast<char *>(&exe), sizeof(expense)))
                {
                	if(strcmp(exe.date,dd)==0)
                	{
                    flag=1;
                	exe.get_data();	
                	}
                    cout<<"\n";
                }
                if(flag==0){
                cout<<"Kindly Enter The Correct Date\n";
                }
               // fp.close();
                break;
            case 4:
            	fp.seekg(0,ios::beg);
                while (fp.read(reinterpret_cast<char *>(&exe), sizeof(expense)))
                {
                    tot+=exe.exp;

                }
                cout << "The Total Expenditure is ::\n"<<tot<<endl;
               // fp.close();
                break;


        }
        cout<<"\nDo you want to access the Main Menu?(y/n)\n";
        cin>>choice;
    }while(choice =='Y' || choice =='y');
}

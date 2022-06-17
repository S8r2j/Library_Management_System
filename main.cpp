#include <iostream>
#include <mysql.h>
#include <sstream>
#include <cstring>
#include <ctime>
#include <windows.h>

using namespace std;

class library{
	private:
		string password;
		string collegeid;
		string student_name;
		string college;
		string faculty;
		string date;
		string booknum;
		string bookname;
	public:
		void getandcheck(MYSQL* conn)
		{
			stringstream ss;
			MYSQL_RES* res;
			cout<<"\t\t\tEnter your college id(IN BLOCK LETTERS): ";
			getline(cin>>ws,collegeid);
			cout<<"\n\t\t\tEnter your password: ";
			getline(cin>>ws,password);
			ss<<"select* from login_data where Id='"+collegeid+"' and Password='"+password+"'";
			string query=ss.str();
			const char* q= query.c_str();
			mysql_query(conn,q);
			res=mysql_store_result(conn);
			my_ulonglong count=mysql_num_rows(res);
			if(count==1)
			{
				if(collegeid!="PURADMIN001")
				studentlibrary(collegeid, conn);
				else
				{
					adminlibrary(conn);
				}
			}
			else
			{
				cout<<"\n\t\t\tCollegeID or Password is incorrect\n";
			}
		}
		void studentlibrary(string id, MYSQL* conn)
		{
			if(conn)
			{
				MYSQL_ROW row;
				MYSQL_RES* res;
				stringstream s;
				s<<"select * from student_details where CollegeId='"+id+"'";
				string query=s.str();
				const char* q= query.c_str();
				int qstate=mysql_query(conn,q);
				if(!qstate)
				{
					res=mysql_store_result(conn);
					int count=mysql_num_fields(res);
					cout<<"\n\n";
					while(row=mysql_fetch_row(res))
					{
						for(int i=0;i<count;i++)
						{
							cout<<"\t\t"<<row[i];
						}
						cout<<"\n";
					}
				}
				bookrecord(id, conn);
			}
		}
		void bookrecord(string id, MYSQL* conn)
		{
			if(conn)
			{
				MYSQL_ROW row;
				MYSQL_RES* res;
				stringstream sss;
				string book="Book Number";
				string bok="Book Name";
				sss<<"select Date, BookNumber, BookName from book_record where Id='"+id+"'";
				string query=sss.str();
				const char* q= query.c_str();
				int qstate=mysql_query(conn,q);
				if(!qstate)
				{
					res= mysql_store_result(conn);
					int count=mysql_num_fields(res);
					cout<<"\n\n";
					cout<<"\t\tDate\t\t\tBook Number\t\tBook Name\n";
					while(row=mysql_fetch_row(res))
					{
						for(int i=0;i<count;i++)
						{
							cout<<"\t\t"<<row[i];
						}
						cout<<"\n";
					}
				}
			}
		}
		void adminlibrary(MYSQL* conn)
		{
			int choice=0;
			cout<<"\n\n\t\t\tWhat do you want to do?\n";
			cout<<"\t\t\t1. Register new student\n";
			cout<<"\t\t\t2. Add the withdrawn book\n";
			cout<<"\t\t\t3. Renew the withdrawn book\n";
			cout<<"\t\t\t4. Return the withdrawn book\n\t\t\t";
			cin>>choice;
			switch(choice)
			{
				case 1: {
					cout<<"\t\t\tEnter the full name:\t";
					getline(cin>>ws,student_name);
					cout<<"\n\t\t\tEnter the college name:\t";
					getline(cin>>ws,college);
					cout<<"\n\t\t\tEnter the college roll numberIIN BLOCK LETTERS):\t";
					cin>>collegeid;
					cout<<"\n\t\t\tEnter the faculty:\t";
					cin>>faculty;
					cout<<"\n\t\t\tCreate the password:\t";
					cin>>password;
					string repassword;
					cout<<"\n\t\t\tRe-Enter the password:\t";
					cin>>repassword;
					while(repassword!=password)
					{
						cout<<"\n\t\t\tEnter the password carefully!!!\n";
						cout<<"\n\t\t\tCreate the password:\t";
						cin>>password;
						cout<<"\n\t\t\tRe-Enter the password:\t";
						cin>>repassword;
					}
					stringstream ss;
					ss<<"insert into student_details values('"+student_name+"', '"+college+"', '"+faculty+"', '"+collegeid+"')";
					string query = ss.str();
					const char* q= query.c_str();
					int qstate=mysql_query(conn,q);
					if(!qstate)
					{
						cout<<"\n\t\t\tNew student is registered\n";
					}
					stringstream sss;
					sss<<"insert into login_data values('"+collegeid+"', '"+password+"')";
					string uery=sss.str();
					const char* r=uery.c_str();
					mysql_query(conn,r);
					break;
				}
				case 2:{
					cout<<"\n\t\t\tEnter the students college id:\t";
					cin>>collegeid;
					int num=0;
					cout<<"\n\t\t\tHow many book(s) are withdrawn?:\t";
					cin>>num;
					for(int i=0;i<num;i++)
					{
						stringstream ss;
//						time_t now= time(0);    //for real time date
//						char* dt= ctime(&now);  //for now we take date from user
						cout<<"\n\t\t\tEnter date of entry:\t";
						getline(cin>>ws,date);
						cout<<"\n\t\t\tEnter book code number:\t";
						cin>>booknum;
						cout<<"\n\t\t\tEnter the book name:\t";
						getline(cin>>ws,bookname);
						ss<<"insert into book_record values('"+collegeid+"', '"+booknum+"', '"+bookname+"', '"+date+"')";
						string query=ss.str();
						const char* q= query.c_str();
						int qstate= mysql_query(conn,q);
						if(!qstate)
						{
							cout<<"\t\t\tBook added successfully\n";
						}
					}
					break;
				}
				case 3:{
					
					break;
				}
			}
		}
};

int main() {
	
	MYSQL* conn;
	conn= mysql_init(0);
	conn= mysql_real_connect(conn,"localhost","root","","student_library",3306,NULL,0);
	library lib;
	lib.getandcheck(conn);
	return 0;
}

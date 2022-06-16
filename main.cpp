#include <iostream>
#include <mysql.h>
#include <sstream>
#include <cstring>
#include <windows.h>

using namespace std;

class library{
	private:
		string password;
		string collegeid;
		stringstream ss;
	public:
		void getandcheck(MYSQL* conn)
		{
			MYSQL_RES* res;
			cout<<"\t\t\tEnter your college id: ";
			getline(cin>>ws,collegeid);
			cout<<"\n\t\t\tEnter your password: ";
			getline(cin>>ws,password);
			ss<<"select* from login_data where StudentID='"+collegeid+"' and Password='"+password+"'";
			string query=ss.str();
			const char* q= query.c_str();
			mysql_query(conn,q);
			res=mysql_store_result(conn);
			my_ulonglong count=mysql_num_rows(res);
			if(count==1)
			{
				studentlibrary(collegeid);
			}
			else
			{
				cout<<"\n\t\t\tCollegeID or Password is incorrect\n";
			}
		}
		void studentlibrary(string id)
		{
			MYSQL* conn;
			conn= mysql_init(0);
			conn= mysql_real_connect(conn,"localhost","root","","student_information",3306,NULL,0);
			if(conn)
			{
				MYSQL_ROW row;
				MYSQL_RES* res;
				stringstream s;
				s<<"select * from student_details where Id='"+id+"'";
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
				bookrecord(id);
			}
		}
		void bookrecord(string id)
		{
			MYSQL* conn;
			conn= mysql_init(0);
			conn= mysql_real_connect(conn,"localhost","root","","book",3306,NULL,0);
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
};

int main() {
	
	MYSQL* conn;
	conn= mysql_init(0);
	conn= mysql_real_connect(conn,"localhost","root","","student_login",3306,NULL,0);
	library lib;
	lib.getandcheck(conn);
	return 0;
}

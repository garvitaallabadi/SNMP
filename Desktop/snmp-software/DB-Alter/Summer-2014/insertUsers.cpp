#include <iostream>
#include <pqxx/pqxx>
#include<sstream>
#include "sha256.h"

using namespace std;
using namespace pqxx;

std::string generatehash(std::string pass){
	std::string output1,salt="digivjay";
	for(int i=0; i< 1000; i++){
		output1 = sha256(output1 + pass + salt);
	}
	return output1;
}

int main(int argc, char* argv[])
{
   char * sql;
   
   try{
      connection C("dbname=snmpdb user=postgres password=harkirat \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      string user,pass;
	cout<<"Enter username"<<endl;
	cin>>user;
	cout<<"Enter password"<<endl;
	cin>>pass;
	string hashedpass = generatehash(pass);
	work w(C);

	stringstream ss;
	ss << "INSERT INTO users VALUES ('" << user << "','" << hashedpass <<"');";
	w.exec(ss.str());
	w.commit();

      cout << "Records created successfully" << endl;
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}



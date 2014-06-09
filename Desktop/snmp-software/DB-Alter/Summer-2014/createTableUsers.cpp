#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   char *sql;
   
   try{
      connection C("dbname=snmpdb user=postgres password=harkirat \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      /* Create SQL statement */
      sql = (char*)"CREATE TABLE users("  \
      "username       TEXT        PRIMARY KEY," \
      "password       TEXT        NOT NULL);";

      /* Create a transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Table created successfully" << endl;
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}

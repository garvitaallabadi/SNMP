#include <iostream>
#include <pqxx/pqxx>

using namespace std;

int main2()
{
    pqxx::connection conn("dbname=mydb user=postgres password=admin hostaddr=127.0.0.1 port=5432");
    if (conn.is_open()) {
	cout << "We are connected to" << conn.dbname() << endl;
    } 
    else {
	cout << "We are not connected!" << endl;
    return 0;
    }
    pqxx::work w(conn);
    pqxx::result res = w.exec("SELECT 1");
    w.commit();

    cout << res[0][0].as<int>() << endl;
}

#include <pqxx/pqxx>
#include <string>

class Database{
	private:
		void setSize(int);
		pqxx::connection *conn;
	public:
		Database();
		int Connect();
		int size():
		std::string getRow(int);
		~Database();
}

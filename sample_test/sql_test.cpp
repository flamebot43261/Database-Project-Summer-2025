#include <iostream>
#include <stdlib.h>
#include <string>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

int main(){
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    try {
        const char* db_pass_cstr = getenv("DB_PASSWORD");
        if (db_pass_cstr == nullptr) {
            std::cerr << "Error: DB_PASSWORD environment variable not set." << std::endl;
            return 1;
        }
        std::string pass = db_pass_cstr;
        
        driver = get_driver_instance();

        // --- Use your Google Cloud SQL details here ---
        std::string host = "tcp://127.0.0.1:3306"; // e.g., "tcp://34.123.45.67:3306"
        std::string user = "root";
        std::string db = "vinyl_db";

        con = driver->connect(host, user, pass);
        con->setSchema(db);
        // ---------------------------------------------

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT 'Successfully connected to Google Cloud SQL!' AS _message");

        while (res->next()) {
            std::cout << res->getString("_message") << std::endl;
        }

        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return 1;
    }
    return 0;
}
#include "ECommerceFunctions.cpp"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

int main()
{
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;


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
    
    // Initialize Customer, Staff, and cart objects
    Customer customer;
    Staff staff;
    std::vector<vinyl_record> cart;

    /* LOGIN PAGE ======================================================*/
    /* LOGIN PAGE ======================================================*/
    int boolean = true;
    while (boolean)
    {
        int choice;
        std::cout << "\nVinyl Store Sign In" << std::endl;
        std::cout << "====================" << std::endl;
        std::cout << "Please select a sign in option: " << std::endl;
        std::cout << "1. Customer" << std::endl;
        std::cout << "2. Staff" << std::endl;
        std::cout << "3. Register as a  new customer" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice)
        {
        case 1:
            // Handle customer sign in
            {
                customer_sign_in(con,customer);
                boolean = false; // Exit loop after successful sign in
            }
            break;
        case 2:
            // Handle staff sign in
            {
                staff_sign_in(con, staff);
                boolean = false; // Exit loop after successful sign in
            }
            break;
        case 3:
            // Handle new customer registration
            {
                register_customer(con, customer);
                boolean = false;
            }
            break;
        case 4:
            std::cout << "Exiting the application. Thank you!\n" << std::endl;
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again.\n" << std::endl;
        }
    }
    /* LOGIN PAGE ====================================================== */
    /* LOGIN PAGE ====================================================== */

    boolean = true; // Reset boolean for home page loop

    /* HOME PAGE ======================================================= */
    /* HOME PAGE ======================================================= */
    while (boolean)
    {
        std::cout << "\nWelcome to the Vinyl Record Store!" << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << "Menu Options:" << std::endl;
        std::cout << "1. Search Vinyls by Title" << std::endl;
        std::cout << "2. Search Vinyls by Artist" << std::endl;
        std::cout << "3. View All Vinyls" << std::endl;
        std::cout << "4. View Cart" << std::endl;
        std::cout << "5. Checkout" << std::endl;
        std::cout << "6. Account Settings" << std::endl;
        std::cout << "7. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        // Handle the choice
        switch (choice)
        {
        case 1:
            // Handle search by title
            search_vinyl_by_title(con, cart);
            break;
        case 2:
            // Handle search by artist
            search_vinyl_by_artist(con);
            break;
        case 3:
            // Handle view all vinyls
            view_all_vinyls(con);
            break;
        case 4:
            // Handle view cart
            view_cart(cart, con, customer);
            break;
        case 5:
            // Handle checkout
            checkout(con, customer, cart);
            break;
        case 6:
            // Handle account settings
            // account_settings(customer, staff);
            break;
        case 7:
            std::cout << "\nExiting the applciation. Thank you!" << std::endl;
            exit(0);
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }

    delete res;
    delete stmt;
    delete con;

    return 0;
}
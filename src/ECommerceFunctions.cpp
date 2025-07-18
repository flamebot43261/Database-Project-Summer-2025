#include "DBAttributes.h"
#include "ECommerceFunctions.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

/*
void start_menu(Customer customer, Staff staff)
{
    int choice;
    std::cout << "Vinyl Store Sign In" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "Please select a sign in option: " << std::endl;
    std::cout << "1. Customer" << std::endl;
    std::cout << "2. Staff" << std::endl;
    std::cout << "3. Register as a  new customer" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        // Handle customer sign in
        {
            customer_sign_in(customer);
        }
        break;
    case 2:
        // Handle staff sign in
        staff_sign_in(staff);
        break;
    case 3:
        // Handle new customer registration
        register_customer(customer, staff);
        break;
    case 4:
        std::cout << "Exiting the application. Thank you!" << std::endl;
        exit(0);
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        start_menu(customer, staff);
    }
}
*/

// Pass the database connection and a reference to the customer object
void customer_sign_in(sql::Connection *con, Customer &customer)
{
    std::string email, password;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    std::cout << "Enter your email: ";
    std::cin >> email;

    try
    {
        // 1. Prepare the SQL query
        pstmt = con->prepareStatement("SELECT * FROM customer WHERE email = ?");
        pstmt->setString(1, email);

        // 2. Execute the query and get the ResultSet
        res = pstmt->executeQuery();

        // 3. Use res->next() to check if a row was returned
        if (res->next())
        {
            // A customer was found, now get their stored password
            int customer_ID = res->getInt("customerID");
            std::string last_name = res->getString("lastName");
            std::string cust_email = res->getString("email");
            std::string address = res->getString("address");
            std::string city = res->getString("city");
            std::string state = res->getString("state");
            std::string zip_code = res->getString("zip_code");
            std::string phone_number = res->getString("phone_number");
            std::string db_password = res->getString("userPassword");
            std::string first_name = res->getString("firstName");

            customer.customer_id = customer_ID;
            customer.last_name = last_name;
            customer.email = cust_email;
            customer.set_address(address);
            customer.set_city(city);
            customer.set_state(state);
            customer.set_zip_code(zip_code);
            customer.phone_number = phone_number;

            std::cout << "Customer found. Please enter your password: ";
            std::cin >> password;

            // 4. Validate the entered password against the one from the database
            if (db_password == password)
            {
                std::cout << "Sign in successful! Welcome, " << first_name << "!" << std::endl;
                // You can populate your customer object here if needed
                // customer.first_name = first_name;
                customer.customer_id = 
            }
            else
            {
                std::cout << "Invalid password. Please try again." << std::endl;
            }
        }
        else
        {
            std::cout << "No customer found with that email address." << std::endl;
        }

        // 5. Clean up the resources
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Error during sign-in: " << e.what() << std::endl;
    }
}

void staff_sign_in(sql::Connection *con, Staff &staff)
{
    std::string email, password;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    std::string email, password;
    std::cout << "Enter your email: ";
    std::cin >> email;
    // Search for staff in the database
    // Database Logic
    // If staff exists, create user instance and prompt for password
    try
    {
        // 1. Prepare the SQL query
        pstmt = con->prepareStatement("SELECT * FROM staff WHERE email = ?");
        pstmt->setString(1, email);

        // 2. Execute the query and get the ResultSet
        res = pstmt->executeQuery();

        // 3. Use res->next() to check if a row was returned
        if (res->next())
        {
            // A customer was found, now get their stored password
            std::string db_password = res->getString("password_hash");
            std::string first_name = res->getString("firstName");

            std::cout << "Customer found. Please enter your password: ";
            std::cin >> password;

            // 4. Validate the entered password against the one from the database
            if (db_password == password)
            {
                std::cout << "Sign in successful! Welcome, " << first_name << "!" << std::endl;
                // You can populate your customer object here if needed
                // customer.first_name = first_name;
                
            }
            else
            {
                std::cout << "Invalid password. Please try again." << std::endl;
            }
        }
        else
        {
            std::cout << "No customer found with that email address." << std::endl;
        }

        // 5. Clean up the resources
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Error during sign-in: " << e.what() << std::endl;
    }
}

void register_customer(Customer &customer)
{
    std::string first_name, last_name, email, phone_number, password, address, state, zip_code;
    std::cout << "Enter your first name: ";
    std::cin >> first_name;
    std::cout << "Enter your last name: ";
    std::cin >> last_name;
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter your phone number: ";
    std::cin >> phone_number;
    std::cout << "Create a password: ";
    std::cin >> password;
    std::cout << "Enter your address: ";
    std::cin >> address;
    std::cout << "Enter your state: ";
    std::cin >> state;
    std::cout << "Enter your zip code: ";
    std::cin >> zip_code;

    // If user already exists, prompt to try again
    // Database Logic to check if customer already exists
    if (false) // Example condition
    {
        std::cout << "Customer with this email already exists. Please try again.\n"
                  << std::endl;
        register_customer(customer); // Retry registration
        return;
    }

    // Create new customer instance
    // Database logic that will
    Customer new_customer(0, first_name, last_name, email, phone_number); // exmaple
    new_customer.set_password(password);
    new_customer.set_address(address);
    new_customer.set_state(state);
    new_customer.set_zip_code(zip_code);

    // Save new customer to the database
    // Database Logic

    std::cout << "Registration successful! You can now sign in.\n\n"
              << std::endl;
}

/*
void home_page(Customer customer, Staff staff)
{
    std::cout << "Welcome to the Vinyl Record Store!" << std::endl;
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
        search_vinyl_by_title();
        break;
    case 2:
        // Handle search by artist
        search_vinyl_by_artist();
        break;
    case 3:
        // Handle view all vinyls
        view_all_vinyls();
        break;
    case 4:
        // Handle view cart
        view_cart();
        break;
    case 5:
        // Handle checkout
        checkout();
        break;
    case 6:
        // Handle account settings
        account_settings(customer, staff);
        break;
    case 7:
        std::cout << "Logging out..." << std::endl;
        //start_menu(customer, staff); // Return to start menu
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        home_page(customer, staff); // Retry home page
    }
}
*/

void search_vinyl_by_title()
{
    std::string title;
    std::cout << "Enter the title of the vinyl: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, title);
    // Search logic here
    /* Database Logic */
    std::cout << "Searching for vinyls with title: " << title << std::endl;
    // Display results
}

void search_vinyl_by_artist()
{
    std::string artist;
    std::cout << "Enter the artist name: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, artist);
    // Search logic here
    /* Database Logic */
    std::cout << "Searching for vinyls by artist: " << artist << std::endl;
    // Display results
}

void view_all_vinyls()
{
    std::cout << "Displaying all vinyl records..." << std::endl;
    // Fetch and display all vinyl records from the database
    /* Database Logic */
}

void view_cart()
{
    std::cout << "Viewing your cart..." << std::endl;
    // Fetch and display items in the cart
    /* Database Logic */
}

void checkout()
{
    std::cout << "Proceeding to checkout..." << std::endl;
    // Checkout logic here
    /* Database Logic */
    std::cout << "Checkout successful! Thank you for your purchase." << std::endl;
    // home_page(Customer(0, "", "", "", ""), Staff(0, "", "", "", "", "", "")); // Return to home page
}

/*
void account_settings(Customer &customer, Staff &staff)
{
    std::cout << "Account Settings" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "1. Update Password" << std::endl;
    std::cout << "2. Update Address" << std::endl;
    std::cout << "3. Update State" << std::endl;
    std::cout << "4. Update Zip Code" << std::endl;
    std::cout << "5. Update Payment Method" << std::endl;
    std::cout << "6. Back to Home Page" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        // Update password
        {
            std::string new_password;
            // Prompt for old password
            std::string old_password;
            std::cout << "Enter your old password: ";
            std::cin >> old_password;
            // Validate old password
            if (customer.get_password() != old_password)
            {
                std::cout << "Old password is incorrect. Please try again." << std::endl;
                account_settings(customer, staff); // Retry account settings
                return;
            }
            std::cout << "Enter new password: ";
            std::cin >> new_password;
            customer.set_password(new_password);
            std::cout << "Password updated successfully!" << std::endl;
        }
        break;
    case 2:
        // Update address
        {
            std::string new_address;
            std::cout << "Enter new address: ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, new_address);
            customer.set_address(new_address);
            std::cout << "Address updated successfully!" << std::endl;
        }
        break;
    case 3:
        // Update state
        {
            std::string new_state;
            std::cout << "Enter new state: ";
            std::cin >> new_state;
            customer.set_state(new_state);
            std::cout << "State updated successfully!" << std::endl;
        }
        break;
    case 4:
        // Update zip code
        {
            std::string new_zip_code;
            std::cout << "Enter new zip code: ";
            std::cin >> new_zip_code;
            customer.set_zip_code(new_zip_code);
            std::cout << "Zip code updated successfully!" << std::endl;
        }
        break;
    case 5:
        // Update payment method
        {
            std::string card_type, card_number, cardholder_name, expiration_date, billing_address;
            std::cout << "Enter card type: ";
            std::cin >> card_type;
            std::cout << "Enter card number: ";
            std::cin >> card_number;
            std::cout << "Enter cardholder name: ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, cardholder_name);
            std::cout << "Enter expiration year (YYYY): ";
            std::cin >> expiration_date;
            std::cout << "Enter billing address: ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, billing_address);

            PaymentMethod payment_method(0, customer.customer_id, card_type, card_number, cardholder_name, expiration_date, billing_address);
            // Save payment method to the database
            // Database Logic

            std::cout << "Payment method updated successfully!" << std::endl;
        }
        break;
    case 6:
        std::cout << "Returning to home page..." << std::endl;
        // home_page(customer, staff); // Return to home page
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        account_settings(customer, staff); // Retry account settings
    }
    // home_page(customer, staff); // Return to home page after settings

}
*/
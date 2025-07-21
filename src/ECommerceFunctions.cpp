#include "DBAttributes.h"
#include "ECommerceFunctions.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <vector>
#include <limits>

std::string hash_password(const std::string&password) {
    unsigned long hash = 5381;
    for (char c: password){
        hash=((hash << 5)+hash)+c;
    }
    return std::to_string(hash);
}

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
            std::string db_password_hash = res->getString("userPassword");
            std::string first_name = res->getString("firstName");

            std::cout << "Customer found. Please enter your password: ";
            std::cin >> password;

            // 4. Validate the entered password against the one from the database
            if (db_password_hash == hash_password(password))
            {
                std::cout << "Sign in successful! Welcome, " << first_name << "!" << std::endl;
                // You can populate your customer object here if needed
                // customer.first_name = first_name;
                int customer_ID = res->getInt("customerID");
                std::string last_name = res->getString("lastName");
                std::string cust_email = res->getString("email");
                std::string address = res->getString("address");
                std::string city = res->getString("city");
                std::string state = res->getString("state");
                std::string zip_code = res->getString("zip_code");
                std::string phone_number = res->getString("phone_number");

                customer.customer_id = customer_ID;
                customer.last_name = last_name;
                customer.email = cust_email;
                customer.set_address(address);
                customer.set_city(city);
                customer.set_state(state);
                customer.set_zip_code(zip_code);
                customer.phone_number = phone_number;
            }
            else
            {
                std::cout << "Invalid password. Please try again." << std::endl;
                customer_sign_in(con, customer);
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

void register_parameters(std::string &first_name, std::string &last_name, std::string &email, std::string &phone_number, std::string &password,
    std::string &address, std::string &state, std::string &city, std::string &zip_code)
{
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
    // std::cin >> address;
    std::cin.ignore();
    std::getline(std::cin, address);
    // std::cin.clear();

    std::cout << "Enter your city: ";
    // std::cin.ignore();
    std::getline(std::cin, city);
    // std::cin.clear();
    
    
    std::cout << "Enter your state: ";
    // std::cin.ignore();
    std::getline(std::cin, state);
    // std::cin.clear();
    
    std::cout << "Enter your zip code: ";
    std::cin >> zip_code;
}

void register_customer(sql::Connection *con, Customer &customer)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    std::string first_name, last_name, email, phone_number, password, address, state, city, zip_code;
    register_parameters(first_name, last_name, email, phone_number, password, address, state, city, zip_code);

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
            // A customer was found, make user try again
            std::cout << "\nAn account already exists with this email. Please register with a different email.\n";
            register_customer(con, customer);
        }
        else 
        {
            // Prepare the INSERT statement
            pstmt = con->prepareStatement("INSERT INTO customer(firstName, lastName, email, userPassword, address, city, state, zip_code, phone_number) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
            pstmt->setString(1, first_name);
            pstmt->setString(2, last_name);
            pstmt->setString(3, email);
            pstmt->setString(4, hash_password(password));
            pstmt->setString(5, address);
            pstmt->setString(6, city);
            pstmt->setString(7, state);
            pstmt->setString(8, zip_code);
            pstmt->setString(9, phone_number);

            // Execute the INSERT statement
            pstmt->executeUpdate();
            delete pstmt;
            //to fix the issue of state mismatch when attempting to get acocunt details in the same instance as registering an acocunt.
            pstmt = con->prepareStatement("SELECT LAST_INSERT_ID()");
            res = pstmt->executeQuery();
            if(res->next()) {
                customer.customer_id = res->getInt(1);
                customer.first_name = first_name;
                customer.last_name = last_name;
                customer.email = email;
                customer.set_address(address);
                customer.set_city(city);
                customer.set_state(state);
                customer.set_zip_code(zip_code);
                customer.phone_number = phone_number;
            }

            std::cout << "\nRegistration successful! You can now sign in.\n" << std::endl;
        }
        if (res) delete res;
        if (pstmt) delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        // Clean up in case of an exception
        if (res) delete res;
        if (pstmt) delete pstmt;
        std::cerr << "SQL Error during registration: " << e.what() << std::endl;
    }
}

void search_vinyl_by_title(sql::Connection* con, std::vector<vinyl_record> &cart)
{
    std::string title;
    std::cout << "Enter the title of the vinyl: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, title);
    // Search logic here
    /* Database Logic */
    std::cout << "Searching for vinyls with title: " << title << std::endl;
    // Display results
    std::cout << "==================================";
    
    sql::PreparedStatement *pstmt = nullptr;
    sql::ResultSet *res = nullptr;

    try
    {
        // This query joins vinyl_record with artists to get the artist's name.
        // It uses "LIKE" to allow for partial matches on the title.
        std::string query = "SELECT v.vinylID, v.title, v.artistID, v.genre, v.releaseYear, v.price, v.stockQuantity, v.description, a.artistName "
                            "FROM vinyl_record v "
                            "JOIN artists a ON v.artistID = a.artistID "
                            "WHERE v.title LIKE ?";
        
        pstmt = con->prepareStatement(query);
        
        // Add '%' wildcards to the search term for partial matching
        std::string search_term = "%" + title + "%";
        pstmt->setString(1, search_term);

        res = pstmt->executeQuery();

        std::cout << "\n--- Search Results ---\n" << std::endl;
        bool found = false;
        // Loop through all the matching records
        while (res->next())
        {
            found = true;
            // Retrieve and display data for each record
            std::cout << "Title: " << res->getString("title") << std::endl;
            std::cout << "Artist: " << res->getString("artistName") << std::endl;
            std::cout << "Price: $" << res->getDouble("price") << std::endl;
            std::cout << "Stock: " << res->getInt("stockQuantity") << std::endl;
            std::cout << "----------------------------------" << std::endl;
            // Create temp variable and add to cart
            vinyl_record temp(res->getInt("vinylID"), res->getString("title"), res->getInt("artistID"), res->getString("genre"), res->getInt("releaseYear"), res->getDouble("price"), res->getInt("stockQuantity"), res->getString("description"));
            add_to_cart(cart, temp);
            return;
        }

        
        // Prompt user to add vinyl to cart if search is successful
        if (!found)
        {
            std::cout << "No vinyl records found matching that title." << std::endl;
        }

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Error during search: " << e.what() << std::endl;
        // Clean up in case of an exception
        if (res) delete res;
        if (pstmt) delete pstmt;
    }
}

void search_vinyl_by_artist(sql::Connection* con)
{
    std::string artist;
    std::cout << "Enter the artist name: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, artist);
    // Search logic here
    sql::PreparedStatement *pstmt = nullptr;
    sql::ResultSet *res = nullptr;
    /* Database Logic */
    std::cout << "Searching for vinyls by artist: " << artist << std::endl;
    // Display results
    try
    {
        // This query joins vinyl_record with artists to get the artist's name.
        // It uses "LIKE" to allow for partial matches on the artist's name.
        std::string query = "SELECT v.title, a.artistName, v.price, v.stockQuantity "
                            "FROM vinyl_record v "
                            "JOIN artists a ON v.artistID = a.artistID "
                            "WHERE a.artistName LIKE ?";
        
        pstmt = con->prepareStatement(query);
        
        // Add '%' wildcards to the search term for partial matching
        std::string search_term = "%" + artist + "%";
        pstmt->setString(1, search_term);

        res = pstmt->executeQuery();

        std::cout << "\n--- Search Results ---\n" << std::endl;
        bool found = false;
        // Loop through all the matching records
        while (res->next())
        {
            found = true;
            // Retrieve and display data for each record
            std::cout << "Title: " << res->getString("title") << std::endl;
            std::cout << "Artist: " << res->getString("artistName") << std::endl;
            std::cout << "Price: $" << res->getDouble("price") << std::endl;
            std::cout << "Stock: " << res->getInt("stockQuantity") << std::endl;
            std::cout << "----------------------------------" << std::endl;
        }

        if (!found)
        {
            std::cout << "No vinyl records found for that artist." << std::endl;
        }
        
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Error during search: " << e.what() << std::endl;
        // Clean up in case of an exception
        if (res) delete res;
        if (pstmt) delete pstmt;
    }
}

void view_all_vinyls(sql::Connection* con)
{
    std::cout << "\n--- All Vinyl Titles ---\n";
    std::cout << "==========================\n";
    
    sql::PreparedStatement *pstmt = nullptr;
    sql::ResultSet *res = nullptr;

    try
    {
        // Query to select just the titles from the vinyl_record table, ordered alphabetically.
        pstmt = con->prepareStatement("SELECT title FROM vinyl_record ORDER BY title");
        res = pstmt->executeQuery();

        bool found = false;
        // Loop through all records and print the title
        while (res->next())
        {
            found = true;
            std::cout << "- " << res->getString("title") << std::endl;
        }

        if (!found)
        {
            std::cout << "There are no vinyl records currently in the store." << std::endl;
        }
        
        std::cout << "\n------------------------\n" << std::endl;

        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Error while fetching all vinyls: " << e.what() << std::endl;
        if (res) delete res;
        if (pstmt) delete pstmt;
    }

}

void add_to_cart(std::vector<vinyl_record> &cart, const vinyl_record &record)
{
    std::cout << "\nWould you like to add this vinyl to your cart?: ";
    if (std::getchar() == 'y' || std::getchar() == 'Y')
    {
        cart.push_back(record);
        std::cout << "\n'" << record.title << "' has been added to your cart.\n\n";
    }
    std::cin.clear();
    std::cout << "Returning to homepage...\n\n";
}

void view_cart( std::vector<vinyl_record> &cart, sql::Connection* con, Customer customer)
{
    std::cout << "\nYour cart\n";
    std::cout << "===========\n";
    // Fetch and display items in the cart
    for (auto record : cart)
    {
        std::cout << record.title << std::endl;
    }
    std::cin.ignore();
    std::cout << "\nWould you like to checkout? (y/n): ";
    if (std::getchar() == 'y' || std::getchar() == 'Y')
    {
        checkout(con, customer, cart);
    }
    else
    {
        std::cout << "\nReturning to menu...\n";
    }
}

void checkout(sql::Connection* con, const Customer customer, std::vector<vinyl_record> &cart)
{
    std::cout << "\nProceeding to checkout..." << std::endl;
    if (cart.empty()) {
        std::cout << "Your cart is empty. Nothing to check out." << std::endl;
        return;
    }

    int customer_id, card_id;
    
    sql::PreparedStatement *pstmt = nullptr;
    sql::PreparedStatement *pstmt2 = nullptr;
    sql::ResultSet *res = nullptr;
    
    customer_id = customer.customer_id;

    try
    {
        // 1. Find the customer's credit card
        pstmt = con->prepareStatement("SELECT cardID FROM creditcards WHERE customerID = ?");
        pstmt->setInt(1, customer_id); // FIX: Parameter index is 1
        
        res = pstmt->executeQuery();

        if (res->next())
        {
            card_id = res->getInt("cardID");
            delete res; // Clean up immediately
            res = nullptr;
            delete pstmt; // Clean up immediately
            pstmt = nullptr;

            // 2. Prepare the transaction insert statement ONCE
            // FIX: Removed transactionID (AUTO_INCREMENT) and corrected card_id to cardID
            pstmt = con->prepareStatement("INSERT INTO transactions(customerID, vinylID, cardID, quantity, price_at_purchase, transactionStatus) VALUES (?, ?, ?, ?, ?, ?)");
            pstmt2 = con->prepareStatement("UPDATE vinyl_record SET stockQuantity = stockQuantity - 1 WHERE vinylID = ?");

            // 3. Loop through the cart and execute the insert for each item
            for (const auto& record : cart)
            {
                int quantity = 1; // Assuming quantity is always 1 per cart item
                
                pstmt->setInt(1, customer_id);
                pstmt->setInt(2, record.vinyl_id);
                pstmt->setInt(3, card_id);
                pstmt->setInt(4, quantity);
                pstmt->setDouble(5, record.price); // FIX: Use price from the record
                pstmt->setString(6, "Completed"); // FIX: Set a default status

                pstmt->executeUpdate();

                // Execute stock decrementation on vinyl
                pstmt2->setInt(1, record.vinyl_id);
                pstmt2->executeUpdate();
            }
            
            std::cout << "Checkout successful! Thank you for your purchase." << std::endl;
            cart.clear(); // Empty cart after successful checkout
        }
        else
        {
            std::cout << "It seems that you have not saved a payment method to your profile." << std::endl;
            std::cout << "Would you like to add a payment card? (Not implemented)\n";
        }

        // Final cleanup
        if (res) delete res;
        if (pstmt) delete pstmt;
    }
    catch(sql::SQLException &e)
    {
        std::cerr << "SQL Error during checkout: " << e.what() << std::endl;
        // Ensure cleanup on error
        if (res) delete res;
        if (pstmt) delete pstmt;
    }
}


void account_settings(sql::Connection *con, Customer &customer)
{
    std::cout << "\nAccount Settings" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "1. Update Password" << std::endl;
    std::cout << "2. Update Address" << std::endl;
    std::cout << "3. Update Payment Method" << std::endl;
    std::cout << "4. View Transaction History" << std::endl;
    std::cout << "5. Back to Home Page" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    // Prompt for choice
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        // Update password
        {
            // DB pointers
            sql::PreparedStatement *pstmt = nullptr;
            sql::ResultSet *res = nullptr;
            std::string password_entry,db_password_hash, new_password;
            try
            {
                pstmt=con->prepareStatement("SELECT userPassword FROM customer WHERE customerID = ? ");
                pstmt->setInt(1,customer.customer_id);
                res=pstmt->executeQuery();
                
                if (res->next()){
                    db_password_hash=res->getString("userPassword");
                } else {
                    std::cout<< "\nCould not find your account.\n";
                    break;
                }
                delete res;res=nullptr;
                delete pstmt;pstmt=nullptr;

                std::cout<<"Enter your old password: ";
                std::cin>> password_entry;

                if (hash_password(password_entry)==db_password_hash) {
                    std::cout<<"\nAuthentication successful. Enter new password: ";
                    std::cin>>new_password;


                    pstmt=con->prepareStatement("UPDATE customer SET userPassword = ? where customerID = ? ");
                    pstmt->setString(1,hash_password(new_password));
                    pstmt->setInt(2,customer.customer_id);

                    if(pstmt->executeUpdate() > 0){
                        std::cout<<"\nPassword updated successfully!\n"<<std::endl;

                    } else {
                        std::cout<<"\nPassword update failed.\n"<<std::endl;
                    }

                } else {
                    std::cout<<"\nIncorrect password. Please try again.\n"<<std::endl;
                }

                if (res) delete res;  
                if (pstmt) delete pstmt;
            }
            catch(sql::SQLException& e)
            {
                if (res) delete res;  
                if (pstmt) delete pstmt;
                std::cerr << e.what() << '\n';
            }
            if (res) delete res;
            if (pstmt) delete res;
            account_settings(con, customer);
        }
        break;
            
    case 2:
        // Update address
        {
            // DB pointers
            sql::PreparedStatement *pstmt = nullptr;
            sql::ResultSet *res = nullptr;
            std::string new_street, new_city, new_state, new_zip;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            // Prompt new street address
            std::cout << "\nEnter new street address: ";
            std::getline(std::cin, new_street);
            // Prompt new city
            std::cout << "Enter City: ";
            std::getline(std::cin, new_city);
            // Prompt new state
            std::cout << "Enter State: ";
            std::getline(std::cin, new_state);
            // Prompt new zip
            std::cout << "Enter Zip/Postal Code: ";
            std::getline(std::cin, new_zip);
            
            // Set new information
            customer.set_address(new_street);
            customer.set_city(new_city);
            customer.set_state(new_state);
            customer.set_zip_code(new_zip);

            // Update in DB
            try
            {
            // 1. Prepare the SQL query
            pstmt = con->prepareStatement("SELECT * FROM customer WHERE email = ?");
            pstmt->setString(1, customer.email);

            // 2. Execute the query and get the ResultSet
            res = pstmt->executeQuery();

            // 3. Use res->next() to check if a row was returned
            if (res->next())
            {
                // Update statements
                pstmt = con->prepareStatement("UPDATE customer SET address = ?, city = ?, state = ?, zip_code = ? WHERE email = ?");
                pstmt->setString(1, customer.get_address());
                pstmt->setString(2, customer.get_city());
                pstmt->setString(3, customer.get_state());
                pstmt->setString(4, customer.get_zip_code());
                pstmt->setString(5, customer.email);

                // Execute the update statement
                pstmt->executeUpdate();
                std::cout << "\nAddress updated successfully!\n" << std::endl;
            }
            else 
            {
                std::cout << "\nThere was an error processing your request\n\n";
                if (res) delete res;
                if (pstmt) delete pstmt;
                account_settings(con, customer);
            }
            if (res) delete res;
            if (pstmt) delete pstmt;
            }
            catch (sql::SQLException &e)
            {
                // Clean up in case of an exception
                if (res) delete res;
                if (pstmt) delete pstmt;
                std::cerr << "SQL Error during address change: " << e.what() << std::endl;
            }
        }
        break;
    case 3:
        // Update payment method
        {
            // DB pointers
            sql::PreparedStatement *pstmt = nullptr;
            sql::ResultSet *res = nullptr;
            // Info variables
            std::string card_type, card_number, cardholder_name, expiration_date, billing_address;
            // Get card type
            std::cout << "\nEnter card type: ";
            std::cin >> card_type;
            // Get card number
            std::cout << "Enter card number: ";
            std::cin >> card_number;
            // Get exp year
            std::cout << "Enter expiration date (MM/YYYY): ";
            std::cin >> expiration_date;
            // Get billing address
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter full billing address: ";
            std::getline(std::cin, billing_address);
            // Save payment method to the database
            // Database Logic
            try
            {
                // 1. Prepare the SQL query
                pstmt = con->prepareStatement("SELECT * FROM creditcards WHERE customerID = ?");
                pstmt->setInt(1, customer.customer_id);

                // 2. Execute the query and get the ResultSet
                res = pstmt->executeQuery();

                // 3. Use res->next() to check if a row was returned
                if (res->next())
                {
                    // Update statements
                    pstmt = con->prepareStatement("UPDATE creditcards SET cardNumber = ?, cardType = ?, expirationDate = ?, billingAddress = ? WHERE customerID = ?");
                    pstmt->setString(1, card_number);
                    pstmt->setString(2, card_type);
                    pstmt->setString(3, expiration_date);
                    pstmt->setString(4, billing_address);
                    pstmt->setInt(5, customer.customer_id);

    
                    // Execute the update statement
                    pstmt->executeUpdate();
                    std::cout << "\nPayment has been updated successfully!\n\n";
                }
                else 
                {
                    pstmt = con->prepareStatement("INSERT INTO creditcards(cardNumber, cardType, expirationDate, billingAddress, customerID) VALUES (?, ?, ?, ?, ?)");
                    pstmt->setString(1, card_number);
                    pstmt->setString(2, card_type);
                    pstmt->setString(3, expiration_date);
                    pstmt->setString(4, billing_address);
                    pstmt->setInt(5, customer.customer_id);

                    // Process request
                    pstmt->executeUpdate();
                    
                    std::cout << "\nPayment has been added successfully!\n\n";
                }
                if (res) delete res;
                if (pstmt) delete pstmt;
            }
            catch (sql::SQLException &e)
            {
                // Clean up in case of an exception
                if (res) delete res;
                if (pstmt) delete pstmt;
                std::cerr << "SQL Error during payment info change: " << e.what() << std::endl;
            }
        }
        break;
    case 4:
        {
           sql::PreparedStatement *pstmt = nullptr;
           sql::ResultSet *res = nullptr; 

           
            std::cout << "\n--- Your Transaction History ---\n";
            std::cout << "================================\n";
            try
            {
                pstmt = con->prepareStatement(
                    "SELECT t.transactionDate, v.title, t.quantity, t.price_at_purchase "
                    "FROM transactions t "
                    "JOIN vinyl_record AS v ON t.vinylID=v.vinylID "
                    "WHERE t.customerID = ? "
                    "ORDER BY t.transactionDate DESC"
                );
                pstmt->setInt(1,customer.customer_id);
                res=pstmt->executeQuery();
                bool found_transactions=false;
                while(res->next()) {
                    found_transactions = true;
                    std::cout<<"Date: "<< res->getString("transactionDate")<<std::endl;
                    std::cout<<"  Item: "<< res->getString("title")<<std::endl;
                    std::cout<<"  Quantity: "<< res->getInt("quantity")<<std::endl;
                    std::cout<<"  Price: $"<< res->getDouble("price_at_purchase")<<std::endl;
                }
                if (!found_transactions) {
                    std::cout<<"You have no past transactions."<<std::endl;
                }
            }
            catch (sql::SQLException &e)
            {
                std::cerr << "SQL Error fetching transaction history: " << e.what() << std::endl;
                if (res) delete res;
                if (pstmt) delete pstmt;
            }
                
            std::cout << "\nPress Enter to return to the account settings...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin.get();
            account_settings(con,customer);
        }
        break;
    case 5:
        std::cout << "\nReturning to home page...\n"<<std::endl;
        break;
    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        account_settings(con, customer); // Retry account settings
    }
}

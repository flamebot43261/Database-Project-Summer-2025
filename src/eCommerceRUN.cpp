#include "ECommerceFunctions.cpp"

int main()
{
    // Initialize Customer and Staff objects
    Customer customer;
    Staff staff;

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
                customer_sign_in(customer);
                boolean = false; // Exit loop after successful sign in
            }
            break;
        case 2:
            // Handle staff sign in
            {
                staff_sign_in(staff);
                boolean = false; // Exit loop after successful sign in
            }
            break;
        case 3:
            // Handle new customer registration
            register_customer(customer);
            break;
        case 4:
            std::cout << "Exiting the application. Thank you!" << std::endl;
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    /* LOGIN PAGE ====================================================== */
    /* LOGIN PAGE ====================================================== */

    boolean = true; // Reset boolean for home page loop

    /* HOME PAGE ======================================================= */
    /* HOME PAGE ======================================================= */
    while (boolean)
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
            // account_settings(customer, staff);
            break;
        case 7:
            std::cout << "Logging out..." << std::endl;
            // start_menu(customer, staff); // Return to start menu
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
    return 0;
}
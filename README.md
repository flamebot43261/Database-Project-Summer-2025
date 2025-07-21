# Vinyl Record E-Commerce CLI

This project is a C++ command-line interface (CLI) application that simulates a simple e-commerce platform for a vinyl record store. It uses a MySQL database to manage users, products, and transactions, providing a complete backend and user interaction experience through the terminal.

## Features

*   **User Authentication:** Secure customer registration and sign-in.
*   **Password Hashing:** Passwords are hashed before being stored in the database for enhanced security.
*   **Product Catalog:**
    *   Search for vinyl records by title or artist.
    *   View a list of all available vinyl records.
*   **Shopping Cart:**
    *   Add items to a personal shopping cart.
    *   View the contents of the cart before checkout.
*   **Checkout Process:**
    *   Simulates a complete transaction using saved payment methods.
    *   Records each purchase in a transaction history.
*   **Account Management:**
    *   Update user password.
    *   Update shipping address.
    *   Add or update payment methods (credit cards).
    *   View personal transaction history.
*   **Database Integration:** All data is persisted in a MySQL database.

## Technologies Used

*   **C++:** Core application logic.
*   **MySQL:** Relational database for data storage.
*   **MySQL Connector/C++:** Library for connecting the C++ application to the MySQL database.
*   **Make/g++:** For compiling and building the project.

## Database Schema

The application relies on a relational database schema to organize its data. The primary tables include:

*   `customer`: Stores user account information, including credentials and personal details.
*   `creditcards`: Manages customer payment information, linked to the `customer` table.
*   `artists`: Stores information about the music artists.
*   `vinyl_record`: Contains the product catalog, including details like title, artist, price, and stock.
*   `transactions`: Logs all purchase history, linking customers to the vinyls they bought.

## Setup and Installation

### Prerequisites

*   A C++ compiler (like g++)
*   `make` build automation tool
*   MySQL Server
*   MySQL Connector/C++ library installed and linked

### 1. Database Setup

1.  **Start your MySQL server.**
2.  Connect to your MySQL instance and create the database:
    ```sql
    CREATE DATABASE vinyl_db;
    ```
3.  Use the provided SQL scripts in the `/sql/` directory to create the necessary tables and (optionally) populate them with initial data.
4.  Set the `DB_PASSWORD` environment variable to your MySQL root user password. This is required for the application to connect to the database.
    ```bash
    export DB_PASSWORD="your_mysql_password"
    ```

### 2. Build the Application

Navigate to the project's root directory and use the provided `Makefile` to compile the source code.

```bash
make
```

This will generate an executable file (e.g., `vinyl_store`) in the `bin/` directory.

### 3. Run the Application

Execute the compiled binary from the root directory:

```bash
./bin/vinyl_store
```

## Usage

Once the application is running, you will be presented with a main menu. Follow the on-screen prompts to:

1.  Sign in as a customer or register for a new account.
2.  Navigate the menus by entering the corresponding number for your choice.
3.  Browse vinyls, add them to your cart, and proceed to checkout.
4.  Manage your account details through the "Account Settings" menu.

## Future Improvements

*   **Secure Hashing:** Replace the current simple hashing function with a robust, salted cryptographic library like **Argon2** or **bcrypt**.
*   **Staff/Admin Panel:** Fully implement the staff sign-in and create an admin panel for managing inventory, users, and viewing all transactions.
*   **GUI:** Develop a graphical user interface using a library like Qt or wxWidgets for a more user-friendly experience.
*   **Unit Testing:** Add a testing suite to ensure the reliability and correctness of database interactions and business logic.
```# Vinyl Record E-Commerce CLI

This project is a C++ command-line interface (CLI) application that simulates a simple e-commerce platform for a vinyl record store. It uses a MySQL database to manage users, products, and transactions, providing a complete backend and user interaction experience through the terminal.

## Features

*   **User Authentication:** Secure customer registration and sign-in.
*   **Password Hashing:** Passwords are hashed before being stored in the database for enhanced security.
*   **Product Catalog:**
    *   Search for vinyl records by title or artist.
    *   View a list of all available vinyl records.
*   **Shopping Cart:**
    *   Add items to a personal shopping cart.
    *   View the contents of the cart before checkout.
*   **Checkout Process:**
    *   Simulates a complete transaction using saved payment methods.
    *   Records each purchase in a transaction history.
*   **Account Management:**
    *   Update user password.
    *   Update shipping address.
    *   Add or update payment methods (credit cards).
    *   View personal transaction history.
*   **Database Integration:** All data is persisted in a MySQL database.

## Technologies Used

*   **C++:** Core application logic.
*   **MySQL:** Relational database for data storage.
*   **MySQL Connector/C++:** Library for connecting the C++ application to the MySQL database.
*   **Make/g++:** For compiling and building the project.

## Database Schema

The application relies on a relational database schema to organize its data. The primary tables include:

*   `customer`: Stores user account information, including credentials and personal details.
*   `creditcards`: Manages customer payment information, linked to the `customer` table.
*   `artists`: Stores information about the music artists.
*   `vinyl_record`: Contains the product catalog, including details like title, artist, price, and stock.
*   `transactions`: Logs all purchase history, linking customers to the vinyls they bought.

## Setup and Installation

### Prerequisites

*   A C++ compiler (like g++)
*   `make` build automation tool
*   MySQL Server
*   MySQL Connector/C++ library installed and linked

### 1. Database Setup

1.  **Start your MySQL server.**
2.  Connect to your MySQL instance and create the database:
    ```sql
    CREATE DATABASE vinyl_db;
    ```
3.  Use the provided SQL scripts in the `/sql/` directory to create the necessary tables and (optionally) populate them with initial data.
4.  Set the `DB_PASSWORD` environment variable to your MySQL root user password. This is required for the application to connect to the database.
    ```bash
    export DB_PASSWORD="your_mysql_password"
    ```

### 2. Build the Application

Navigate to the project's root directory and use the provided `Makefile` to compile the source code.

```bash
make
```

This will generate an executable file (e.g., `vinyl_store`) in the `bin/` directory.

### 3. Run the Application

Execute the compiled binary from the root directory:

```bash
./bin/vinyl_store
```

## Usage

Once the application is running, you will be presented with a main menu. Follow the on-screen prompts to:

1.  Sign in as a customer or register for a new account.
2.  Navigate the menus by entering the corresponding number for your choice.
3.  Browse vinyls, add them to your cart, and proceed to checkout.
4.  Manage your account details through the "Account Settings" menu.

## Future Improvements

*   **Secure Hashing:** Replace the current simple hashing function with a robust, salted cryptographic library like **Argon2** or **bcrypt**.
*   **Staff/Admin Panel:** Fully implement the staff sign-in and create an admin panel for managing inventory, users, and viewing all transactions.
*   **GUI:** Develop a graphical user interface using a library like Qt or wxWidgets for a more user-friendly experience.
*   **Unit Testing:** Add a testing suite to ensure the reliability and correctness of database interactions and business logic.
#ifndef ECOMMERCEFUNCTIONS_H
#define ECOMMERCEFUNCTIONS_H

#include "DBAttributes.h"
#include <cppconn/connection.h> // Include for sql::Connection

// Function Declarations
// Note: We pass the database connection and user objects to the functions that need them.

// Login/Registration
void customer_sign_in(sql::Connection* con, Customer customer);
void staff_sign_in(sql::Connection* con, Staff staff);
void register_customer(sql::Connection* con, Customer &customer);

// Vinyl Searching
void search_vinyl_by_title(sql::Connection* con);
void search_vinyl_by_artist(sql::Connection* con);
void view_all_vinyls(sql::Connection* con);

// Cart & Checkout
void view_cart(sql::Connection* con, const Customer customer);
void checkout(sql::Connection* con, const Customer customer);

// Account Management
void account_settings(sql::Connection* con, Customer customer);

#endif // ECOMMERCEFUNCTIONS_H
#ifndef DBATTRIBUTES_H
#define DBATTRIBUTES_H
#include <iostream>
#include <iomanip>
#include <string>

// Artist class definition
class artist
{
public:
    int artist_id;
    std::string name;
    std::string country;
    // Constructor
    artist(int id, const std::string &n, const std::string &c)
        : artist_id(id), name(n), country(c) {}
};

// Vinyl Record class definition
class vinyl_record
{
public:
    int vinyl_id;
    std::string title;
    int artist_id;
    std::string genre;
    int release_year;
    double price;
    int stock_quantity;
    std::string description;
    // Constructor
    vinyl_record(int id, const std::string &t, int a_id, const std::string &g, int year, double p, int stock, const std::string &desc)
        : vinyl_id(id), title(t), artist_id(a_id), genre(g), release_year(year), price(p), stock_quantity(stock), description(desc) {}
};

class Customer
{
public:
    int customer_id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string phone_number;
    // Constructor
    Customer(int id, const std::string &f_name, const std::string &l_name, const std::string &e, const std::string &phone)
        : customer_id(id), first_name(f_name), last_name(l_name), email(e), phone_number(phone) {}
    // Getters
    std::string get_password() const { return password; }
    std::string get_address() const { return address; }
    std::string get_state() const { return state; }
    std::string get_zip_code() const { return zip_code; }
    // Setters
    void set_password(const std::string &pass) { password = pass; }
    void set_address(const std::string &addr) { address = addr; }
    void set_state(const std::string &st) { state = st; }
    void set_zip_code(const std::string &zip) { zip_code = zip; }

private:
    std::string password;
    std::string address;
    std::string state;
    std::string zip_code;
};

class PaymentMethod
{
public:
    int card_id;
    int customer_id;
    std::string card_type;
    // constructor
    PaymentMethod(int id, int c_id, const std::string &type, const std::string &number, const std::string &holder_name, const std::string &exp_date, const std::string &billing_addr)
        : card_id(id), customer_id(c_id), card_type(type), card_number(number), cardholder_name(holder_name), expiration_date(exp_date), billing_address(billing_addr) {}
    // Getters
    std::string get_card_number() const { return card_number; }
    std::string get_cardholder_name() const { return cardholder_name; }
    std::string get_expiration_date() const { return expiration_date; }
    std::string get_billing_address() const { return billing_address; }

private:
    std::string card_number;
    std::string cardholder_name;
    std::string expiration_date;
    std::string billing_address;
};

class Transaction
{
public:
    int transaction_id;
    int customer_id;
    int vinyl_id;
    int quantity;
    double total_amount;
    std::string transaction_date;
    std::string transaction_status;
    int card_id;
    // Constructor
    Transaction(int id, int c_id, int v_id, int qty, double amount, const std::string &date, const std::string &status, int card)
        : transaction_id(id), customer_id(c_id), vinyl_id(v_id), quantity(qty), total_amount(amount), transaction_date(date), transaction_status(status), card_id(card) {}
};

class Staff
{
public:
    int staff_id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string phone_number;
    std::string role;
    std::string hire_date;
    // Constructor
    Staff(int id, const std::string &f_name, const std::string &l_name, const std::string &e, const std::string &phone, const std::string &r, const std::string &date)
        : staff_id(id), first_name(f_name), last_name(l_name), email(e), phone_number(phone), role(r), hire_date(date) {}
    // Getters
    std::string get_password() const { return password; }
    double get_salary() const { return salary; }
    // Setters
    void set_password(const std::string &pass) { password = pass; }
    void set_salary(double sal) { salary = sal; }

private:
    std::string password;
    double salary;
};

#endif
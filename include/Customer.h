#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
public:
    int customer_id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string phone_number;
    // Constructor
    Customer() : customer_id(0), first_name(""), last_name(""), email(""), phone_number("") {};
    Customer(int id, const std::string &f_name, const std::string &l_name, const std::string &e, const std::string &phone)
        : customer_id(id), first_name(f_name), last_name(l_name), email(e), phone_number(phone) {}
    // Getters
    std::string get_password() const { return password; }
    std::string get_address() const { return address; }
    std::string get_city() const { return city; }
    std::string get_state() const { return state; }
    std::string get_zip_code() const { return zip_code; }
    // Setters
    void set_password(const std::string &pass) { password = pass; }
    void set_address(const std::string &addr) { address = addr; }
    void set_city(const std::string &cty) { city = cty; }
    void set_state(const std::string &st) { state = st; }
    void set_zip_code(const std::string &zip) { zip_code = zip; }

private:
    std::string password;
    std::string address;
    std::string city;
    std::string state;
    std::string zip_code;
};

#endif // CUSTOMER_H

#ifndef STAFF_H
#define STAFF_H

#include <string>

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
    Staff() : staff_id(0), first_name(""), last_name(""), email(""), phone_number(""), role(""), hire_date("") {};
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

#endif // STAFF_H

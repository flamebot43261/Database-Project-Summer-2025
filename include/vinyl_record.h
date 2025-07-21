#ifndef VINYL_RECORD_H
#define VINYL_RECORD_H

#include <string>

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
    vinyl_record() : vinyl_id(0), title(""), artist_id(0), genre(""), release_year(0), price(0.0), stock_quantity(0), description("") {}
    vinyl_record(int id, const std::string &t, int a_id, const std::string &g, int year, double p, int stock, const std::string &desc)
        : vinyl_id(id), title(t), artist_id(a_id), genre(g), release_year(year), price(p), stock_quantity(stock), description(desc) {}
};

#endif // VINYL_RECORD_H

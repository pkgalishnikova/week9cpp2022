#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

//     Main task - to implement the function fillCountries to put countries into a container]
// (vector<Country> or map<std::string, Country>).

//     Intermediate steps:
//     1. Define operator< for both Cities and Countries based on their names.
//     2. Read cities as pairs <City, name of the country>.
//     3. Use the name of the country to find if there is such country in the container.
//     4. Add a country to the container or a city to an existing country.

struct Coordinate {
    double longitude;
    double latitude;
};

struct City {
    std::string name;
    int population;
    Coordinate coordinate;
};

struct Country {
    std::string name;
    std::set<City> cities;
};


bool operator<(const City& lhs, const City& rhs)
{
    return lhs.population > rhs.population;
}

std::istream& extractDataFromLine(std::istream& in, City& city, std::string& countryName)
{
    std::string buffer;
    std::getline(in, buffer);
    if (!in)
    {
        return in;
    }
    std::stringstream sstr(buffer);
    // Manila,14.5958,120.9772,Philippines,23088000

    std::getline(sstr, buffer, ',');
    city.name = buffer;

    std::getline(sstr, buffer, ',');
    city.coordinate.latitude = std::stod(buffer);
    // double latitude = std::stod(buffer);

    std::getline(sstr, buffer, ',');
    city.coordinate.longitude = std::stod(buffer);
    // double longitude = std::stod(buffer);

    std::getline(sstr, buffer, ',');
    countryName = buffer;

    std::getline(sstr, buffer, ',');
    city.population = std::stoi(buffer);

    return in;
}

bool countryNameExists(const std::vector<Country>& countries, const std::string& name, size_t& index)
{
    for (size_t i = 0; i < countries.size(); ++i)
    {
        if (countries[i].name == name)
        {
            index = i;
            return true;
        }
    }
    return false;
}

void fillCountries(std::istream& inFile, std::vector<Country>& countries)
{
    std::string lineBuffer;
    std::string countryName;
    City city;
    std::getline(inFile, lineBuffer);
    while (extractDataFromLine(inFile, city, countryName))
    {
        size_t index;
        if (countryNameExists(countries, countryName, index))
        {
            countries[index].cities.insert(city);
        }
        else
        {
            Country newCountry;
            newCountry.name = countryName;
            newCountry.cities.insert(city);
            countries.push_back(newCountry);
        }
    }
}

std::ostream& operator<< (std::ostream& out, const Coordinate& coord)
{
    out << "( lat = " << coord.latitude << ", lon = ";
    out << coord.longitude << " )";
    return out;
}

std::ostream& operator<< (std::ostream& out, const City& outCity)
{
    out << "( city = " << outCity.name << ", population = ";
    out << outCity.population << " , coordinates = ( ";
    out << outCity.coordinate << " )\n";
    return out;
}


std::ostream& operator<< (std::ostream& out, const std::set<City>& outCities)
{
    for (const City& city: outCities)
    {
        out << city;
    }
    return out;
}


std::ostream& operator<< (std::ostream& out, const Country& country)
{
    out << "Country: " << country.name << std::endl;
    out << "Cities:\n" << country.cities << std::endl;
    return out;
}


int main()
{
    const std::string FILENAME = "../data/problem1_cities/cities.csv";
    std::ifstream inputFile;
    inputFile.open(FILENAME);
    if (inputFile)
    {
        std::cout << "OK\n";
    }
    std::vector<Country> countries;
    fillCountries(inputFile, countries);

    // City& city;

    std::cout << countries[0];


    std::cout << countries.size() << std::endl;
    return 0;
}

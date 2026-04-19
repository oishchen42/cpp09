#include <iostream>
#include <vector>

#include <map>
#include <unordered_map>

struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;
};

namespace std{
    template<>
    struct hash<CityRecord>
    {
        size_t operator()(const CityRecord& key)
        {
            return hash<std::string>()(key.Name);
        }
    };
};

int main()
{
    std::unordered_map<CityRecord, uint32_t> foundedMap;

    foundedMap[CityRecord]

    std::map<std::string, CityRecord> cityMap;
    cityMap["Mlebourne"] = CityRecord{"Mlebourne", 5000000, 2.4, 9.4};
    cityMap["Lol-town"] = CityRecord{"Lol-town", 5000000, 2.4, 9.4};
    cityMap["Berlin"] = CityRecord{"Berlin", 5000000, 2.4, 9.4};
    cityMap["Paris"] = CityRecord{"Paris", 5000000, 2.4, 9.4};
    cityMap["London"] = CityRecord{"Mlebourne", 5000000, 2.4, 9.4};

    CityRecord& berilnData = cityMap["Berlin"];
    std::cout << "bData: " << berilnData.Latitude << std::endl;
}
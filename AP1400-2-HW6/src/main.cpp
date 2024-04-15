#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        // auto flights = q3::gather_flights("resources\flights.txt");
        // int size = flights.size();
        // std::vector<std::string> flight_numbers;
        // std::vector<size_t> durations;
        // std::vector<size_t> connections;
        // std::vector<size_t> connection_times;
        // std::vector<size_t> prices;
        // while (!flights.empty()) 
        // {
        //     flight_numbers.push_back(flights.top().flight_number);
        //     durations.push_back(flights.top().duration);
        //     connections.push_back(flights.top().connections);
        //     connection_times.push_back(flights.top().connection_times);
        //     prices.push_back(flights.top().price);
        //     flights.pop();
        // }
        // for (int i = 1; i <= size; ++i){
        //     std::cout << i << "- flight_number:" << flight_numbers[i] << " - duration:" << durations[i] << " - connections:" << connections[i] << " - connection_times:" << connection_times[i] << " - price:" << prices[i] << std::endl;
        // }
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}
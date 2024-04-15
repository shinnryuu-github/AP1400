#ifndef Q3_H
#define Q3_H

#include <queue>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

namespace q3 {

struct Flight{
	std::string flight_number;
	size_t duration;
	size_t connections;
	size_t connection_times;
	size_t price;
};

size_t exchange_time(std::string s) {
    size_t time = 0;
    auto start = 0;
    auto end = s.find('h');
    std::string temp = s.substr(start, end);
    time = stoi(temp) * 60;

    if (s.find('m') == std::string::npos) {
        return time;
    }

    start = end + 1;
    end = s.find('m');
    temp = s.substr(start, end);
    time += stoi(temp);

    return time;
}

std::vector<std::string> split(const std::string &line){
    std::vector<std::string> res;
    std::string tmp;
    std::stringstream ss(line);
    while (std::getline(ss, tmp, '-')){
        tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
        res.push_back(tmp);
    }
    return res;
}

std::string get_flight_number(const std::string &flight_number){
    std::string tmp;
    std::stringstream ss(flight_number);
    std::getline(ss, tmp, ':');
    std::string res;
    ss >> res;
    return res;
}

size_t get_duration(const std::string &duration){
    std::string tmp;
    std::stringstream ss(duration);
    std::getline(ss, tmp, ':');
    std::string res;
    ss >> res;
    return exchange_time(res);
}

size_t get_connections(const std::string &connections){
    std::string tmp;
    std::stringstream ss(connections);
    std::getline(ss, tmp, ':');
    size_t res;
    ss >> res;
    return res;
}

size_t get_connection_times(const std::string &connection_times, size_t connection){
    size_t res{0};
    std::string tmp;
    std::stringstream ss(connection_times);
    std::getline(ss, tmp, ':');
    for (int i = 0; i < connection; i++){
        std::getline(ss, tmp, ',');
        res += exchange_time(tmp);
    }
    return res;
}

size_t get_price(const std::string &price){
    std::string tmp;
    std::stringstream ss(price);
    std::getline(ss, tmp, ':');
    size_t res;
    ss >> res;
    return res;
}

auto comp = [](const Flight& a, const Flight& b) {
    return a.duration + a.connection_times + 3 * a.price > b.duration + b.connection_times + 3 * b.price;
};

//duration + connection_times + 3*price
std::priority_queue<Flight, std::vector<Flight>, decltype(comp)> gather_flights(std::string filename){
    std::priority_queue<Flight, std::vector<Flight>, decltype(comp)> res;
    std::fstream f(filename);
    if (!f){
        std::cout << "File not found" << std::endl;
        exit(1);
    }
    else{
        std::string line;
        while (std::getline(f, line)){
            auto sp = split(line);
            auto flight_num = get_flight_number(sp[1]);
            auto duration = get_duration(sp[2]);
            auto connections = get_connections(sp[3]);
            auto connection_times = get_connection_times(sp[4], connections);
            auto price = get_price(sp[5]);
            res.push({flight_num, duration, connections, connection_times, price});
        }
    }
    f.close();
    return res;
}
}

#endif //Q3_H
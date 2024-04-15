#ifndef Q2_H
#define Q2_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace q2{
struct Patient{
    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
};

std::vector<Patient> read_file(std::string filename){
    std::vector<Patient> res;
    std::fstream f(filename);
    if (!f){
        std::cout << "File not found" << std::endl;
        exit(1);
    }
    else{
        std::string line;
        std::getline(f, line);
        std::getline(f, line);
        while (std::getline(f, line)){
            std::stringstream ss(line);
            std::string field;
            std::string name = "";
            int mark = 0;
            std::vector<std::string> row;
            line = " " + line;
            while (getline(ss, field, ',')) {
                if (mark == 0) {
                    field.erase(std::remove(field.begin(), field.end(), ' '), field.end());
                    name += field;
                    mark++;
                } else if (mark == 1) {
                    field.erase(std::remove(field.begin(), field.end(), ' '), field.end());
                    name += " ";
                    name += field;
                    mark++;
                } else {
                    row.push_back(field);
                }
            }
            Patient p{name, stoul(row[0]), stoul(row[1]), stoul(row[2]), stoul(row[3])};
            res.push_back(p);
        }

    }
    f.close();
    return res;
}

void sort(std::vector<Patient>& p){
    std::sort(p.begin(), p.end(), [](const Patient &a, const Patient &b)
              { return (3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol) > (3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol); }
    );
}

}

#endif //Q2_H
#ifndef Q4_H
#define Q4_H

#include <vector>

namespace q4{

struct Vector2D{
    double x;
    double y; 
};

struct Sensor{
	Vector2D pos;
	double accuracy;    
};

Vector2D kalman_filter(std::vector<Sensor> sensors){
    Vector2D tmp{0, 0};
    double weights{0.0};
    for (auto sensor : sensors){
        weights += sensor.accuracy;
        tmp.x += sensor.pos.x * sensor.accuracy;
        tmp.y += sensor.pos.y * sensor.accuracy;
    }
    tmp.x /= weights;
    tmp.y /= weights;
    return tmp;
}
}

#endif //Q4_H
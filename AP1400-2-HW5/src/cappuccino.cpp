#include "cappuccino.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino(){
    this->ingredients = std::vector<Ingredient*>{};
    (this->ingredients).push_back(new Espresso{2});
    (this->ingredients).push_back(new Milk{2});
    (this->ingredients).push_back(new MilkFoam{1});
    this->side_items = std::vector<Ingredient*>{};
    this->name = "Cappuccino";
}

Cappuccino::Cappuccino(const Cappuccino& cap){
    this->ingredients = std::vector<Ingredient*>{};
    (this->ingredients).push_back(new Espresso{2});
    (this->ingredients).push_back(new Milk{2});
    (this->ingredients).push_back(new MilkFoam{1});
    this->side_items = std::vector<Ingredient*>{};
    this->name = "Cappuccino";
    for (const auto i : cap.side_items){
        this->side_items.push_back(i->clone());
    }
}

Cappuccino::~Cappuccino(){
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

std::string Cappuccino::get_name(){
    return this->name;
}

void Cappuccino::operator=(const Cappuccino& cap){
    if (this != &cap){
        this->ingredients = std::vector<Ingredient*>{};
        (this->ingredients).push_back(new Espresso{2});
        (this->ingredients).push_back(new Milk{2});
        (this->ingredients).push_back(new MilkFoam{1});
        this->side_items = std::vector<Ingredient*>{};
        this->name = "Cappuccino";
        for (const auto i : cap.side_items){
            this->side_items.push_back(i->clone());
        }
    }
}

double Cappuccino::price(){
    double res{0};
    for (auto i : ingredients){
        res += i->price();
    }
    for (auto i : side_items){
        res += i->price();
    }
    return res;
}

void Cappuccino::add_side_item(Ingredient* side){
    this->side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return this->side_items;
}


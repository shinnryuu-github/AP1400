#include "espresso_based.h"
#include <ncurses.h>

EspressoBased::EspressoBased()
: name("nothing"), ingredients({}) {}

EspressoBased::EspressoBased(const EspressoBased& esp)
: name(esp.name), ingredients(esp.ingredients){}

EspressoBased::~EspressoBased(){
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

void EspressoBased::operator=(const EspressoBased& esp){
    name = esp.name;
    ingredients = esp.ingredients;
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}

void EspressoBased::brew(){
    // initscr();
    // curs_set(0);
    // int ingredient{1};
    // for (int i = 0; i <= 100; ++i) {
    //     mvprintw(0, 0, "brewing:");
    //     mvprintw(0, 8, "[");
    //     mvprintw(0, 110, "]");
    //     mvprintw(0, i + 9, "#");
    //     mvprintw(0, 111, "%d/100", i);
    //     refresh();
    //     napms(100);
    // }
    // getch();
    // endwin(); 
}
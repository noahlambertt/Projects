#include "Song.h"
#include <iostream>
#include <string>

void Song::setname(std::string n){
    name = n;
}

void Song::setartist(std::string n){
    artist = n;
}

void Song::setrating(int i){
    rating = i;
}

void Song::setcompare(int i){
    compare = i;
}

void Song::settotal(int i){
    total = i;
}

void Song::display(){
    std::cout << name << " - " << artist << std::endl;
    std::cout << rating << " / 10" << std::endl;
    std::cout << compare << " / " << total << std::endl;
}

void Song::choice(Song song){
    compare++;
    total++;
    song.total++;
}

std::string Song::getname(){
    return name;
}

std::string Song::getartist(){
    return artist;
}

int Song::getcompare(){
    return compare;
}

int Song::gettotal(){
    return total;
}

int Song::getrating(){
    return rating;
}

Song::Song(){
}

Song::~Song(){
}
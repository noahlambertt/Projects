#include "Playlist.h"
#include "Song.h"
#include <string>
#include <vector>
#include <iostream>
#include <cctype>

Playlist::Playlist(){
}

Playlist::~Playlist(){
}

void Playlist::addsong(std::string song_name, std::string song_artist, int song_rating, int song_compare, int song_total){
    Song temp;
    temp.setname(song_name);
    temp.setartist(song_artist);
    temp.setrating(song_rating);
    temp.setcompare(song_compare);
    temp.settotal(song_total);
    playlist.push_back(temp);
}

void Playlist::comparison(){
    std::cout << "Please select which song you think fits better in the backpacking playlist" << std::endl;
    std::cout << "If you prefer the first song, press 1. If you prefer the second song, press 2" << std::endl;
    std::cout << "If you're unsure, press 3. If you want to quit, press 4" << std::endl;
    std::cout << "Please do not close this program before pressing 4. No data is stored until you quit" << std::endl;
    std::cout << "==================================================================================" << std::endl;
    srand((unsigned) time(NULL));
    int input;
    do{
        int index1 = rand() % playlist.size();
        int index2 = rand() % playlist.size();
        while(index1 == index2)
            index2 = rand() % playlist.size();
        Song one = playlist.at(index1);
        Song two = playlist.at(index2);
        std::cout << one.getname() << " - " << one.getartist() << " or " << two.getname() << " - " << two.getartist() << std::endl;
        std::cin >> input;
        if(input == 1){
            one.choice(two);
            playlist.at(index1) = one;
            playlist.at(index2) = two;
        }
        if(input ==2){
            two.choice(one);
            playlist.at(index1) = one;
            playlist.at(index2) = two;
        }
    }while(input != 4);
}

void Playlist::rate(){
    int songsleft = 0;
    int input, index;
    srand((unsigned) time(NULL));
    std::cout << "Rate the songs provided from 1 - 10. Answers outside of the range will not be accepted" << std::endl;
    std::cout << "If you are unsure, enter 11. Enter 0 to quit" << std::endl;
    std::cout << "Please do not close this program before pressing 0. No data is stored until you quit" << std::endl;
        
    for(size_t i = 0; i < playlist.size(); i++)
        if((playlist.at(i)).getrating() == 0)
            songsleft++;
    std::cout << "You have " << songsleft << " songs left to rate" << std::endl;
    std::cout << "==================================================================================" << std::endl;
                
    while(songsleft > 0 && input != 0){
        index = rand() % playlist.size();
        while((playlist.at(index)).getrating() != 0)
            index = rand() % playlist.size();
        std::cout << (playlist.at(index)).getname() << " - " << (playlist.at(index)).getartist() << std::endl;
        std::cin >> input;
        if(input > 0 && input < 10){
            (playlist.at(index)).setrating(input);
            songsleft--;
        }
    }
    if(songsleft == 0)
        std::cout << "You have rated every song on the playlist" << std::endl;
}

void Playlist::change(){
    std::string songname;
    std::vector<std::string> songsfound;
    int numfound = 0;
    std::cout << "Which song would you like to change the rating for? (You do not have to type out the whole song) ";
    std::cin.ignore();
    std::getline(std::cin, songname);
    for(size_t i = 0; i < playlist.size(); i++)
        if(((playlist.at(i)).getname()).find(songname) == 0){
            numfound++;
            songsfound.push_back((playlist.at(i)).getname());
            songsfound.push_back((playlist.at(i)).getartist());
        }
        
    if(numfound == 0)
        std::cout << "No songs found called " << songname << std::endl;
    else{
        int temp, input = 0;
        if(numfound > 1){
            std::cout << "Which song would you like to change the rating?" << std::endl;
            for(int i = 0; i < 2*numfound; i+=2)
                std::cout << i/2 + 1 << ". " << songsfound.at(i) << " - " << songsfound.at(i+1) << std::endl;
            do{
                std::cin >> input;
                if(input > numfound || input < 0)
                    std::cout << "Please enter e number between 1 and " << numfound << std::endl;
            }while(input > numfound || input < 0);
            input--;//Subtracting to adjust for counting starting at 0
        }
        songname = songsfound.at(2*input);
        for(size_t i = 0; i < playlist.size(); i++)
            if(((playlist.at(i)).getname()).find(songname) == 0)
                temp = i;
        std::cout << "What would you like to change the rating to? Current rating is " << (playlist.at(temp)).getrating() << " / 10" << std::endl;
        std::cin >> input;
        while(input > 10 || input < 1){
            std::cout << "Please enter a number from 1 to 10" << std::endl;
            std::cin >> input;
        }
        (playlist.at(temp)).setrating(input);
        std::cout << (playlist.at(temp)).getname() << " - " << (playlist.at(temp)).getartist() << " changed to " << input << " / 10" << std::endl;
    }
}

void Playlist::showstats(){
    std::cout << "===============" << std::endl;
    for(auto song : playlist)
        song.display();
    std::cout << "The first row is number of times picked in option 1 out of the number of times it appeared" << std::endl;
    std::cout << "The second row is your rating out of 10" << std::endl;
    std::cout << "If the second row is a 0 / 10, you have not rated it yet" << std::endl;
}

void Playlist::order(){
    std::cout << "===============" << std::endl;
    std::string arr[playlist.size()];
    for(size_t i = 0; i < playlist.size(); i++)
        arr[i] = (playlist.at(i)).getname();
        
    bool swapped;
    for (size_t i = 0; i < playlist.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < playlist.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    std::vector<Song> alpha;
    for(size_t i = 0; i < playlist.size(); i++){
        for(size_t j = 0; j < playlist.size(); j++)
            if(((playlist.at(j)).getname()).find(arr[i]) == 0)
                alpha.push_back(playlist.at(j));
    }
    for(auto song : alpha)
        song.display();
}

void Playlist::numorder(){
    std::cout << "===============" << std::endl;
    std::vector<Song> numalpha;
    for(size_t i = 0; i < playlist.size(); i++)
        if((playlist.at(i)).getrating() != 0)
            numalpha.push_back(playlist.at(i));
    
    bool swapped;
    for (size_t k = 0; k < numalpha.size() - 1; k++) {
        swapped = false;
        for (size_t j = 0; j < numalpha.size() - k - 1; j++) {
            if ((numalpha.at(j)).getrating() < (numalpha.at(j+1)).getrating()) {
                std::swap(numalpha.at(j), numalpha.at(j+1));
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    
    for(int i = 10; i > 0; i--){
        std::cout << i << " / 10" << std::endl;
        for(size_t j = 0; j < numalpha.size(); j++)
            if((numalpha.at(j)).getrating() == i)
                std::cout << (numalpha.at(j)).getname() << " - " << (numalpha.at(j)).getartist() << std::endl;
        std::cout << "===============" << std::endl;
    }
}

void Playlist::ratingorder(){
    std::cout << "===============" << std::endl;
    std::vector<Song> compare;
    for(size_t i = 0; i < playlist.size(); i++)
        if((playlist.at(i)).gettotal() != 0)
            compare.push_back(playlist.at(i));
    
    double arr[compare.size()];
    for(size_t i = 0; i < compare.size(); i++)
        arr[i] = static_cast<double>((compare.at(i)).getcompare()) / (compare.at(i)).gettotal();
    
    bool swapped;
    for (size_t k = 0; k < compare.size() - 1; k++) {
        swapped = false;
        for (size_t j = 0; j < compare.size() - k - 1; j++) {
            if(arr[j] < arr[j+1]){
                std::swap(compare.at(j), compare.at(j+1));
                std::swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(swapped == false)
            break;
    }
        
    for(size_t i = 0; i < compare.size(); i++){
        std::cout << (compare.at(i)).getname() << " - " << (compare.at(i)).getartist() << std::endl;
        std::cout << 10*arr[i] << " / 10 (picked " << (compare.at(i)).getcompare() << " out of " << (compare.at(i)).gettotal() << " times)" << std::endl;
        std::cout << "===============" << std::endl;
    }
}

int Playlist::getsize(){
    return playlist.size();
}

int Playlist::getcompare(int i){
    return (playlist.at(i)).getcompare();
}

int Playlist::gettotal(int i){
    return (playlist.at(i)).gettotal();
}

int Playlist::getrating(int i){
    return (playlist.at(i)).getrating();
}
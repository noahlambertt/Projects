#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Playlist.h"
using namespace std;

void menu();

int main(){
    
	Playlist list;
    string song_name, song_artist;
    int song_rating, song_compare, song_total;
    ifstream playlist("Songs.txt");
    ifstream artists("Artists.txt");
    ifstream compare("Backpacking_data.txt");
    ifstream ratings("Backpacking_rate.txt");

    while(getline(playlist, song_name)){
        getline(artists, song_artist);
        ratings >> song_rating;
        compare >> song_compare;
        compare >> song_total;
        list.addsong(song_name, song_artist, song_rating, song_compare, song_total);
    }
    
    menu();
    int choice;
    cin >> choice;
    
    if(choice == 1)
        list.comparison();
    if(choice == 2)
        list.rate();
    if(choice == 3)
        list.change();
    if(choice == 4)
        list.showstats();
    if(choice == 5)
        list.order();
    if(choice == 6)
        list.numorder();
    if(choice == 7)
        list.ratingorder();
        
    playlist.close();
    artists.close();
    compare.close();
    ratings.close();
    
    if(choice == 1 || choice == 2 || choice == 3){
    
        filesystem::remove("Backpacking_data.txt");
        filesystem::remove("Backpacking_rate.txt");
        fstream new_file1;
        new_file1.open("Backpacking_data.txt", ios::out);
        if(new_file1.is_open())
            for(int i = 0; i < list.getsize(); i++){
                new_file1 << list.getcompare(i) << " ";
                new_file1 << list.gettotal(i) << endl;
            }
    
        fstream new_file2;
        new_file2.open("Backpacking_rate.txt", ios::out);
        if(new_file2.is_open())
            for(int i = 0; i < list.getsize(); i++)
                new_file2 << list.getrating(i) << endl;
            
        new_file1.close();
        new_file2.close();
        
    }
    return 0;
}

void menu(){
    cout << "What would you like to do?" << endl;
    cout << "1. Preference between two songs" << endl;
    cout << "2. Rate individual songs" << endl;
    cout << "3. Change a rating" << endl;
    cout << "4. Show your stats" << endl;
    cout << "5. Show your stats in alphabetical order" << endl;
    cout << "6. Show your stats by rating" << endl;
    cout << "7. Show your stats by comparison rating" << endl;
}
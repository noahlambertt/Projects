#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_
#include <string>
#include <vector>
#include "Song.h"

class Playlist{
private:
    std::vector<Song> playlist;
public:
    Playlist();
    ~Playlist();
    void addsong(std::string song_name, std::string song_artist, int song_rating, int song_compare, int song_total);
    void comparison();
    void rate();
    void change();
    void showstats();
    void order();
    void numorder();
    void ratingorder();
    int getsize();
    int getcompare(int i);
    int gettotal(int i);
    int getrating(int i);
};

#endif // _PLAYLIST_H_
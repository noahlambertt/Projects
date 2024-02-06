#ifndef _SONG_H_
#define _SONG_H_
#include <string>

class Song{
private:
    std::string name;
    std::string artist;
    int rating;
    int compare;
    int total;
public:
    void setname(std::string n);
    void setartist(std::string n);
    void setrating(int i);
    void setcompare(int i);
    void settotal(int i);
    void display();
    void choice(Song song);
    std::string getname();
    std::string getartist();
    int getcompare();
    int gettotal();
    int getrating();
    bool search(std::string choice);
    Song();
    ~Song();
};

#endif // _SONG_H_
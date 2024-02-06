#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
using namespace std;

void menu(){
    cout << "1. Solve" << endl;
    cout << "2. View times by scrambles" << endl;
    cout << "3. View times by time" << endl;
    cout << "4. View best averages" << endl;
}

void practice(vector<string> &scrambleslist, vector<int> &timeslist);
void viewscrambles(vector<string> scrambleslist, vector<int> timeslist);
void viewtimes(vector<string> scrambleslist, vector<int> timeslist);
void viewaverages(vector<int> timeslist);
bool parity(int r, int r1, int r2);
int findsmallest(vector<int> temp);
int findlargest(vector<int> temp);

int main(){
    
    srand((unsigned) time(NULL));
    string moves;
    int seconds;
    vector<string> scrambleslist;
    vector<int> timeslist;
    ifstream scrambles("Scrambles.txt");
    ifstream times("Times.txt");
    
    while(getline(scrambles, moves)){
        times >> seconds;
        scrambleslist.push_back(moves);
        timeslist.push_back(seconds);
    }
    
    menu();
    int input;
    cin >> input;
    
    if(input == 1){
        practice(scrambleslist, timeslist);
        
        scrambles.close();
        times.close();
    
        filesystem::remove("Scrambles.txt");
        filesystem::remove("Times.txt");
        fstream new_file1;
        new_file1.open("Scrambles.txt", ios::out);
        if(new_file1.is_open())
            for(size_t i = 0; i < scrambleslist.size(); i++)
                new_file1 << scrambleslist.at(i) << endl;
                
        fstream new_file2;
        new_file2.open("Times.txt", ios::out);
        if(new_file2.is_open())
            for(size_t i = 0; i < timeslist.size(); i++)
                new_file2 << timeslist.at(i) << endl;
            
        new_file1.close();
        new_file2.close();
        }
        
    if(input == 2)
        viewscrambles(scrambleslist, timeslist);
    if(input == 3)
        viewtimes(scrambleslist, timeslist);
    if(input == 4)
        viewaverages(timeslist);
        
    
    return 0;
}

void practice(vector<string> &scrambleslist, vector<int> &timeslist){
    int r, r1, r2;
    string scramble[25];
    string temp;
    string notation = {"RLUDFB"};
    int solve;
    do{
        for(int i = 0; i < 25; i++){
            r = rand() % 6;
            if(i != 0)
                while(parity(r, r1, r2))
                    r = rand() % 6;
            
            scramble[i] = notation[r];
            
            if(i != 0)
                r2 = r1;
            r1 = r;
        }
        int s;
        for(int i = 0; i < 25; i++){
            s = rand() % 3;
            cout << scramble[i];
            if(s == 0){
                cout << "' ";
                temp.append(scramble[i] + "' ");
            }
            if(s == 1){
                cout << "2 ";
                temp.append(scramble[i] + "2 ");
            }
            if(s == 2){
                cout << " ";
                temp.append(scramble[i] + " ");
            }
        }
        cin >> solve;
        if(solve > 2){
            scrambleslist.push_back(temp);
            timeslist.push_back(solve);
            temp.erase(0, temp.length() - 1);
            }
        if(solve == 1){
            scrambleslist.pop_back();
            timeslist.pop_back();
            temp.erase(0, temp.length() - 1);
        }
        if(solve == 2)
            temp.erase(0, temp.length() - 1);
    }while(solve > 0);
}

void viewscrambles(vector<string> scrambleslist, vector<int> timeslist){
    for(size_t i = 0; i < scrambleslist.size(); i++){
        cout << i + 1 << ".";
        if((scrambleslist.at(i)).front() != ' ')
            cout << " ";
        cout << scrambleslist.at(i) << " " << timeslist.at(i) / 100 << ".";
        if(timeslist.at(i) % 100 < 10)
            cout << "0";
        cout << timeslist.at(i) % 100 << endl;
    }
}

void viewtimes(vector<string> scrambleslist, vector<int> timeslist){
    string tempsolve;
    int temptime;
    
    bool swapped;
    for(size_t i = 0; i < timeslist.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < timeslist.size() - i - 1; j++) {
            if (timeslist.at(j) > timeslist.at(j + 1)){
                tempsolve = scrambleslist.at(j);
                scrambleslist.at(j) = scrambleslist.at(j + 1);
                scrambleslist.at(j + 1) = tempsolve;
                
                temptime = timeslist.at(j);
                timeslist.at(j) = timeslist.at(j + 1);
                timeslist.at(j + 1) = temptime;
                
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    
    viewscrambles(scrambleslist, timeslist);
    
    int mean = 0;
    cout << "Average solve time is ";
    for(size_t i = 0; i < timeslist.size(); i++)
        mean += timeslist.at(i);
    cout << (mean / timeslist.size()) / 100 << ".";
    if((mean / timeslist.size()) % 100 < 10)
        cout << "0";
    cout << (mean / timeslist.size()) % 100 << " seconds" << endl;
}

void viewaverages(vector<int> timeslist){
    vector<int> temp;
    vector<int> averages;
    vector<int> solves;
    for(int i = 0; i < 5; i++)
        temp.push_back(timeslist.at(i));
    int small, large, mean = 0;
    
    for(size_t i = 0; i < timeslist.size() - 4; i++){
        small = findsmallest(temp);
        large = findlargest(temp);
        for(int j = 0; j < 5; j++)
            if(temp.at(j) != small && temp.at(j) != large)
                mean += timeslist.at(i + j);
        averages.push_back(static_cast<double>(mean) / 3);
        mean = 0;
        if(i != timeslist.size() - 5)
            temp.at(i % 5) = timeslist.at(i + 5);
        for(int j = 0; j < 5; j++)
            solves.push_back(temp.at(j));
    }
    
    bool swapped;
    int tempnum;
    int tempnum1, tempnum2, tempnum3, tempnum4, tempnum5;
    for(size_t i = 0; i < averages.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < averages.size() - i - 1; j++) {
            if (averages.at(j) > averages.at(j + 1)){
                tempnum = averages.at(j);
                averages.at(j) = averages.at(j + 1);
                averages.at(j + 1) = tempnum;
                
                tempnum1 = solves.at(5*j);
                tempnum2 = solves.at(5*j + 1);
                tempnum3 = solves.at(5*j + 2);
                tempnum4 = solves.at(5*j + 3);
                tempnum5 = solves.at(5*j + 4);
                
                solves.at(5*j) = solves.at(5*j + 5);
                solves.at(5*j + 1) = solves.at(5*j + 6);
                solves.at(5*j + 2) = solves.at(5*j + 7);
                solves.at(5*j + 3) = solves.at(5*j + 8);
                solves.at(5*j + 4) = solves.at(5*j + 9);
                
                solves.at(5*j + 5) = tempnum1;
                solves.at(5*j + 6) = tempnum2;
                solves.at(5*j + 7) = tempnum3;
                solves.at(5*j + 8) = tempnum4;
                solves.at(5*j + 9) = tempnum5;
                
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    
    bool smallfound = false;
    bool largefound = false;
    
    for(size_t i = 0; i < averages.size(); i++){
        for(int j = 0; j < 5; j++)
            temp.at(j) = solves.at(5*i + j);
        cout << i + 1 << ". " << averages.at(i) / 100 << ".";
        if(averages.at(i) % 100 < 10)
            cout << "0";
        cout << averages.at(i) % 100 << "  ";
        for(int j = 0; j < 5; j++){
            if(temp.at(j) == findsmallest(temp) && !(smallfound)){
                cout << "(";
                smallfound = true;
            }
            if(temp.at(j) == findlargest(temp) && !(largefound)){
                cout << "(";
                largefound = true;
            }
            cout << temp.at(j) / 100 << ".";
            if(temp.at(j) % 100 < 10)
                cout << "0";
            cout << temp.at(j) % 100;
            if(temp.at(j) == findsmallest(temp))
                cout << ")";
            if(temp.at(j) == findlargest(temp))
                cout << ")";
            cout << " ";
        }
        cout << endl;
        smallfound = largefound = false;
    }
    
    cout << "Average solve time is ";
    for(size_t i = 0; i < timeslist.size(); i++)
        mean += timeslist.at(i);
    cout << (mean / timeslist.size()) / 100 << ".";
    if((mean / timeslist.size()) % 100 < 10)
        cout << "0";
    cout << (mean / timeslist.size()) % 100 << " seconds" << endl;
}

bool parity(int r, int r1, int r2){
    if(r == r1)
        return true;
    if(r1 % 2 == 0){
        if(r == r2)
            return true;
        return false;
    }
    if(r1 % 2 == 1){
        if(r == r2)
            return true;
        return false;
    }
}

int findsmallest(vector<int> temp){
    int small = temp.at(0);
    for(int i = 1; i < 5; i++)
        if(small > temp.at(i))
            small = temp.at(i);
    return small;
}

int findlargest(vector<int> temp){
    int large = temp.at(0);
    for(int i = 1; i < 5; i++)
        if(large < temp.at(i))
            large = temp.at(i);
    return large;
}
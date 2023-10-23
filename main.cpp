#include <iostream>
#include <vector>
using namespace std;

//This program asks the user to input any number of integers and then performs various tests on the list provided

void menu();
void printnum(vector<int> list);
void addnum(vector<int> &list);
void mean(vector<int> list);
void smallest(vector<int> list);
void largest(vector<int> list);
void order(vector<int> &list);

int main(){
    
    vector<int> list{};
    char input;
    
    cout << "Hello! Please select a choice." << endl;
    menu();

    do{
        cin >> input;
        input = toupper(input);
        
        if (input == 'P')
            printnum(list);
        if (input == 'A')
            addnum(list);
        if (input == 'M')
            mean(list);
        if (input == 'S')
            smallest(list);
        if (input == 'L')
            largest(list);
        if (input == 'O')
            order(list);
        if (input == 'D')
            menu();
        
            
        }while (input != 'Q');
}

void menu(){
    cout << "P - Print numbers" << endl;
    cout << "A - Add a number" << endl;
    cout << "M - Display mean of numbers" << endl;
    cout << "S - Display the smallest number" << endl;
    cout << "L - Display the largest number" << endl;
    cout << "O - Switch the order of two numbers" << endl;
    cout << "D - Display the menu" << endl;
    cout << "Q - quit" << endl;
}

void printnum(vector<int> list){
    if (list.size() == 0)
            cout << "[] - The list is empty" << endl;
        else{
            cout << "[ ";
            for(size_t i{0}; i < list.size(); i++)
                cout << list.at(i) << " ";
            cout << "]" << endl;
        }
}

void addnum(vector<int> &list){
    cout << "Please enter an integer to add to the list -->";
    int num;
    cin >> num;
    list.push_back(num);
    cout << num << " added" << endl;
}

void mean(vector<int> list){
    if(list.size() == 0)
        cout << "Unable to calculate the mean. The list is empty" << endl;
    else{
        int total = 0;
        for(size_t i{0}; i < list.size(); i++)
            total += list.at(i);
        double mean = static_cast<double>(total) / list.size();
        cout << "The mean is " << mean << endl;
    }
}


void smallest(vector<int> list){
    if (list.size() == 0)
        cout << "Unable to determine the smallest number - list is empty" << endl;
    else{
        int small = list.at(0);
        for(size_t i{0}; i < list.size(); i++)
            if(list.at(i) < small)
                small = list.at(i);
        cout << "The smallest number is " << small << endl;   
    }
}

void largest(vector<int> list){
    if (list.size() == 0)
        cout << "Unable to determine the largest number - list is empty" << endl;
    else{
        int large = list.at(0);
        for(size_t i{0}; i < list.size(); i++)
            if(list.at(i) > large)
                large = list.at(i);
        cout << "The largest number is " << large << endl;
    }
}

void order(vector<int> &list){
    if (list.size() <= 1)
        cout << "Unable to switch the order of two elements - list has too few elements" << endl;
    else{
        cout << "Which two numbers would you like to switch? -->";
        int num1, num2, index1 {0}, index2 {0}, pos1 {0}, pos2 {0};
        cin >> num1 >> num2;
        
        for(size_t i{0}; i < list.size(); i++)
            if(num1 == list.at(i))
                index1++;
        for(size_t i{0}; i < list.size(); i++)
            if(num2 == list.at(i))
                index2++;
        
        if(index1 == 0 || index2 == 0)
            cout << "At least one element is not in the list" << endl;
        else{
            if(index1 > 1){
                cout << "Which " << num1 << " would you like to switch? ";
                int choice;
                cin >> choice;
                do{
                    if(choice > index1){
                        cout << "There are only " << index1 << " " << num1 << "s in the list" << endl;
                        cin >> choice;
                    }
                    if(choice <= 0){
                        cout << "You must select a number greater than 0" << endl;
                        cin >> choice;
                    }
                }while(choice > index1 || choice <= 0);
                index1 = choice;
            }
            if(index2 > 1){
                cout << "Which " << num2 << " would you like to switch? ";
                int choice;
                cin >> choice;
                do{
                    if(choice > index2){
                        cout << "There are only " << index2 << " " << num2 << "s in the list" << endl;
                        cin >> choice;
                    }
                    if(choice <= 0){
                        cout << "You must select a number greater than 0" << endl;
                        cin >> choice;
                    }
                }while(choice > index2 || choice <= 0);
                index2 = choice;
            }
                
                for(size_t i{0}; index1 != 0; i++)
                    if(list.at(i) == num1)
                        pos1 = i, index1--;
                    
                for(size_t i{0}; index2 != 0; i++)
                    if(list.at(i) == num2)
                        pos2 = i, index2--;
                
            
            int temp = list.at(pos1);
            list.at(pos1) = list.at(pos2);
            list.at(pos2) = temp; //Finally switching the two elements
            
            cout << "The new list is [ ";
            for(size_t i{0}; i < list.size(); i++)
                cout << list.at(i) << " ";
            cout << "]" << endl;
        }
    }
}

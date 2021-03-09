/* Andy Ha
 * March 8th, 2021
 * Version 1.0
 * 
 * Assumptions:
 * Input and Output files are written to txt files
 * 
 * 
 */

#include <iostream>
#include <vector>
#include <string>
#include "theater.h"
#include <fstream>

using namespace std;

// struct for input reservations
struct reservation
{
    int partySize;
    string resNum;
    string oriLine;

    reservation() {} ;

    reservation(string str, int num, string line) {
        partySize = num;
        resNum = str;
        oriLine = line;
    }
};

// pre: vector of reservatins
// post: opens file, populates vector with reservations, 
// sorts reservations by party size
void openFilePopulateList(vector<reservation> & res, string fileUN);

// pre: vector of reservatins
// post: uses insertion sort to sort reservations by party size
void insertionSort(vector<reservation> & res);

// pre: Theater object and vector of reservations
// post: iterates through vector of reservations
// places parties in theater room
void placeParties(Theater &theater, vector<reservation> res);

// pre: dictionary returned from theater object
// post: creates and writes to file
// output from result of theater object
void createAndWriteToOutputFile(map<string, vector<string>> result);


int main() {
    Theater theater1 = Theater();
    vector<reservation> reservationInput;
    
    openFilePopulateList(reservationInput, "");

    // place parties in theater
    placeParties(theater1, reservationInput);

    // get list of taken seats
    map<string, vector<string>> result = theater1.getResult();

    // write to output file
    createAndWriteToOutputFile(result);

    // testing three default input files
    for(int i = 0; i < 3; i++) {
        Theater tests;
        vector<reservation> tempRes;
        openFilePopulateList(tempRes, "input\\input" + to_string(i) + ".txt");
        placeParties(tests, tempRes);
        map<string, vector<string>> tempResult = tests.getResult();
        createAndWriteToOutputFile(tempResult);
    }
    return 0;
}


void openFilePopulateList(vector<reservation> & res, string fileUN) {
    string filename = fileUN;
    string line;
    ifstream file;

    cout << "Enter file name: ";
    cin >> filename;
    if(filename == "") {
        filename = fileUN;
    }
    
    file.open(filename);
    if(file) {
        while (getline(file, line))
        {
            size_t index = line.find(" ");
            int numResSeats = stoi(line.substr(index));
            reservation temp(line.substr(0, index), numResSeats, line);
            res.push_back(temp);
        }
        insertionSort(res);
    } else {
        cout << "File cannot be opened" << endl;
    }
}

void insertionSort(vector<reservation> & res) {
    int i, key, j; 
    reservation keyObj;
    for (i = 1; i < res.size(); i++)
    { 
        key = res[i].partySize; 
        keyObj = res[i];
        j = i - 1; 
 
        while (j >= 0 && res[j].partySize < key)
        { 
            res[j + 1] = res[j]; 
            j = j - 1; 
        } 
        res[j + 1] = keyObj;
    } 
}

void placeParties(Theater& theater, vector<reservation> res) {
    bool call;
    for(int i = 0; i < res.size(); i++) {
        call = theater.bookSeats(res[i].oriLine);
        if(call) {
            cout << "successfully added reservation " << res[i].resNum << " to theater." << endl;
        } else {
            cout << "UNsuccessfully added reservation " << res[i].resNum << " to theater." << endl;
        }
    }
}


void createAndWriteToOutputFile(map<string, vector<string>> result) {
    string line;
    ofstream output("output\\output.txt");
    for (auto itr = result.begin(); itr != result.end(); ++itr) {
        line = itr->first + ": ";
        for(int i = 0; i < itr->second.size(); i++) {
            line += itr->second[i] + " ";
        }
        line += '\n';
        output << line;
    }
    output.close();
}
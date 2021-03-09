#include "theater.h"
#include <iostream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>
#include <vector>
using namespace std;

Theater::Theater() {
    for(int i = 0; i < MAX_ROWS_IN_ROOM; i++) {
        fill_n(theaterRoom[i], MAX_SEATS_IN_ROW, Seat());
    }   
}

bool Theater::bookSeats(string reservation) {
    // gets the size of the party
    size_t index = reservation.find(" ");
    int numResSeats = stoi(reservation.substr(index));
    int row;
    string prefix;
    string resID = reservation.substr(0, index);
    if(numResSeats > MAX_SEATS_IN_ROW) {
        return false;
    }

    if(rowCounter < 9) {
        if (firstSeatAvail[rowPlacements[rowCounter]] + numResSeats > MAX_SEATS_IN_ROW) {
            return false;
        }
        takeSeats(rowPlacements[rowCounter], numResSeats, resID);
        row = rowPlacements[rowCounter];
        rowCounter++;
    } else {
        // for loop through rows, find where a party can fit in
        int ind = 0;
        while(numSeatsAvail[ind] > numResSeats || ind < MAX_ROWS_IN_ROOM || rowFull[ind]) {
            ind++;
        }
        if(ind == MAX_ROWS_IN_ROOM || firstSeatAvail[ind] + numResSeats > MAX_SEATS_IN_ROW || numSeatsAvail[ind] < numResSeats) {
            return false;
        }
        
        takeSeats(ind, numResSeats, resID);
        row = ind;
    }
    
    return true;
}




map<string, vector<string>> Theater::getResult() {
    return result;
}

void Theater::takeSeats(int row, int partySize, string resID) {
    string temp;
    vector<string> resSeats;
    for(int i = firstSeatAvail[row]; i < firstSeatAvail[row] + partySize && firstSeatAvail[row] + partySize <= MAX_SEATS_IN_ROW; i++) {
        // take seats
        theaterRoom[row][i].takeSeat();

        // adding values to result map
        temp = rowLetter[row] + to_string(i);
        resSeats.push_back(temp);
    }
    result.insert({resID, resSeats});


    // updating rows and seats
    updateRow(row);
}

void Theater::updateRow(int row){
    for (int i = row - 1; i <= row + 1; i++) {
        if(i > -1 && i < MAX_ROWS_IN_ROOM) {
            for (int j = 0; j < MAX_SEATS_IN_ROW; j++) {
                // checks the four corners
                if((i == 0 && j == 0) && (theaterRoom[i][j+1].taken || theaterRoom[i+1][j].taken)) {
                    theaterRoom[i][j].availableSpace = false;
                } else if ((i == 0 && j == MAX_SEATS_IN_ROW - 1) && (theaterRoom[i][j-1].taken || theaterRoom[i+1][j].taken)) {
                    theaterRoom[i][j].availableSpace = false;
                } else if ((i == MAX_ROWS_IN_ROOM - 1  && j == 0) && (theaterRoom[i-1][j].taken || theaterRoom[i][j+1].taken)) {
                    theaterRoom[i][j].availableSpace = false;
                } else if ((i == MAX_ROWS_IN_ROOM - 1  && j == MAX_SEATS_IN_ROW - 1) && (theaterRoom[i-1][j].taken || theaterRoom[i][j-1].taken)) {
                    theaterRoom[i][j].availableSpace = false;
                }
                
                // checks all 4 edges
                if ((j == 0) && (theaterRoom[i-1][j].taken || theaterRoom[i+1][j].taken || theaterRoom[i][j+1].taken))  {
                    theaterRoom[i][j].availableSpace = false;
                } else if ((i == 0) && (theaterRoom[i][j-1].taken || theaterRoom[i+1][j].taken || theaterRoom[i][j+1].taken)) {
                    theaterRoom[i][j].availableSpace = false;
                }else if ((j == MAX_SEATS_IN_ROW - 1) && (theaterRoom[i-1][j].taken || theaterRoom[i+1][j].taken || theaterRoom[i][j-1].taken)) {
                    theaterRoom[i][j].availableSpace = false;
                } else if ((i == MAX_ROWS_IN_ROOM - 1) && (theaterRoom[i-1][j].taken || theaterRoom[i][j-1].taken || theaterRoom[i][j+1].taken)) {
                    theaterRoom[i][j].availableSpace = false;
                }

                // checks for seats anywhere in between
                if (theaterRoom[i][j-1].taken || theaterRoom[i][j+1].taken || theaterRoom[i-1][j].taken || theaterRoom[i+1][j].taken ||
                    theaterRoom[i-1][j-1].taken || theaterRoom[i+1][j-1].taken || theaterRoom[i+1][j+1].taken || theaterRoom[i-1][j+1].taken) {
                    theaterRoom[i][j].availableSpace = false;
                }
                
            }
        } 
        
    }

    // find first occ for numseats avail & firstseat avail func
    for(int i = 0; i < MAX_ROWS_IN_ROOM; i++) {
        findFirstAvailSeat(i);
    }
}

void Theater::findFirstAvailSeat(int row){

    int low = 0, high = MAX_SEATS_IN_ROW - 1;
    int index = firstSeatAvail[row];
    while (low <= high) {
        int mid = (high + low) / 2;
        
        if(theaterRoom[row][mid].availableSpace) {
            index = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    firstSeatAvail[row] = index;
    numSeatsAvail[row] = MAX_SEATS_IN_ROW - firstSeatAvail[row];
    
    if (numSeatsAvail[row] == 0) {
        rowFull[row] = true;
        numSeatsAvail[row] = -1;
    }
}
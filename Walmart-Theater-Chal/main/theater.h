/* Andy Ha
 * March 8th, 2021
 * Version 1.0
 * 
 * Assumptions:
 * No two parties can be sitting right next to each other
 * Parties must have a row and/or column between them
 * Parties can not be larger than 20 
 * 
 * Class Invarients:
 * - all seats are initialized to available and untaken using bools
 * - maps are initialized accordingly as well
 * 
 * Interface Invariants:
 * - Theater will encapsulate a 2D array of a struct Seat
 * - bookSeats will return true/false depending on if the party was able to be seated. 
 * - If a party is larger than the size of the row, the party will not be seated. 
 * - Each party will have a row and/or column between them
 * - 
 */

#ifndef THEATER_H
#define THEATER_H
#include <string>
#include <map>
#include <vector>
using namespace std;




class Theater {
    public:
    // ctor
    // post: creates and init Theater object
    // all Seats in 2d Seat array is init to Seat()
    Theater();

    // pre: reservation string
    // post: returns true if party reservation was 
    // successfully booked and places
    // false if not
    bool bookSeats(string reservation);

    // post: returns resulting map containing
    // reserved and placed parties
    map<string, vector<string>> getResult();

    private:

    // struct for each seat in Theater
    struct Seat
    {
        // true if seat is taken
        bool taken;
        // true if seat is available
        // false if there exists another seat 1 row or col away from it
        bool availableSpace;

        // init bools
        Seat() {
            taken = false;
            availableSpace = true;
        }

        // seat has been taken
        void takeSeat() {
            taken = true;
            availableSpace = false;
        }
    };

    // pre: row being seated in, size of reservation, reservation ID
    // post: iterates through seats the party will take
    // change the bools in Seat Struct for each seat
    // update maps
    void takeSeats(int row, int partySize, string resID);

    // pre: row being checked
    // update seats that are taken/avail for this row, behind row, infront row
    // update first avail seat for this row, behind row, infront row
    void updateRow(int row);

    // pre: row being checked
    // post: Binary Search Variant to determine first available seat in row
    // update maps
    void findFirstAvailSeat(int row);
    
    // const for size of theater
    const unsigned static int MAX_ROWS_IN_ROOM = 10;
    const unsigned static int MAX_SEATS_IN_ROW = 20;

    // Theater 2D array
    Seat theaterRoom[MAX_ROWS_IN_ROOM][MAX_SEATS_IN_ROW];

    // result map containing parties and seats and reservationIDs
    map<string, vector<string>> result;

    // map for each row a letter corresponds with the row
    map<int, string> rowLetter = {
        {0, "A"},
        {1, "B"}, 
        {2, "C"}, 
        {3, "D"},
        {4, "E"},
        {5, "F"},
        {6, "G"},
        {7, "H"},
        {8, "I"},
        {9, "J"},
    };

    // map for number of seats available in each row
    map<int, int> numSeatsAvail = {
        {0, 20},
        {1, 20}, 
        {2, 20}, 
        {3, 20},
        {4, 20},
        {5, 20},
        {6, 20},
        {7, 20},
        {8, 20},
        {9, 20},
    };

    // map for the first available seat in each row
    map<int, int> firstSeatAvail = {
        {0, 0},
        {1, 0}, 
        {2, 0}, 
        {3, 0},
        {4, 0},
        {5, 0},
        {6, 0},
        {7, 0},
        {8, 0},
        {9, 0},
    };

    // map to determine if the row is full or can hold more people
    map<int, bool> rowFull = {
        {0, false},
        {1, false}, 
        {2, false}, 
        {3, false},
        {4, false},
        {5, false},
        {6, false},
        {7, false},
        {8, false},
        {9, false},
    };

    // self chosen row by row. Add party to row
    int rowPlacements[10] = {9, 0, 7, 2, 5, 4, 1, 3, 6, 8};
    int rowCounter = 0; 

};

#endif
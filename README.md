**Movie Theater Seating Challenge**

**Language used:**  C++

**Program Description:**

This solution takes an input file from the user, reads file and executes user request for seating partues in a movie theater. 

**Goal:**
Design and write a seat assignment program to maximize both customer satisfaction and customer
safety

**Assumptions:**
1. Input and Output files are written to txt files
2. No two parties can be sitting right next to each other
3. Parties must have a row and/or column between them
4. Parties can not be larger than 20 
5. Each line in the file will be comprised of a reservation identifier, followed by a space, and then the number of seats requested. 
6. The reservation identifier will have the format: R####.
7. The program should output a file containing the seating assignments for each request.


**Goal Achieved**
1. To make sure we are able to seat everyone, we have the largest parties either at the very front or the very back. This way the seats that become unavailable around them are minimized. 
2. We place parties starting from the front and the back and make our way towards to center, placng smaller parties where they fit. 
3. This was achieved using a class with an internal struct.

**Steps for running**
1. Download and save the src folder in a directory.
2. Compile files MovieTheaterSeatingChallenge.cpp and theater.cpp
3. Compile using g++ MovieTheaterSeatingChallenge.cpp theater.cpp -o out
4. run using command line ./out

**Default Tests**
The program has 3 default input files that can be used to test the program. To add more, add input file into input folder and when asked by program the file name, enter input file path.

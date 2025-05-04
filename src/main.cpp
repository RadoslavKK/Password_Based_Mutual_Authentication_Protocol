/*

__________________________________________ How to Run: ___________________________________________

 1. Open a Terminal window.

 2. Navigate to the project directory:
    cd Password_Based_Mutual_Authentication_Protocol 
    // Change to the project directory.

 3. Build the program:
    make 
    // Compile the project and generate the executable.

 4. Run the program:
    make run 
    // Execute the program.

    SHA-256 - Hash → Enter a string (TEXT) and press Enter/Return
    Base64 Encoder operational. 100% integration coming soon.

 5. Clean the build files:
    make clean // Remove compiled files and clean up the project.

__________________________________________________________________________________________________

*/

#include <iostream>

// Include Simulator
#include "simulator.h"

int main(void)
{
    Simulator sim;
    sim.run();

    return 0;
}
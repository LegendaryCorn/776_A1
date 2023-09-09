#include <cmath>

// The hill climber should be able to solve this.
// This function divides the 100 length string into 10 bit numbers, which are then converted into binary.
// Even numbered 10 bit numbers are added (numbers 0, 2, 4, 6, and 8)
// Odd numbered 10 bit numbers are subtracted (numbers 1, 3, 5, 7, 9)
// The optimal string is 1111111111 0000000000 1111111111 0000000000 1111111111 0000000000 1111111111 0000000000 1111111111 0000000000
// This adds up to 1023 * 5 = 5115.
// Every correct bit will add to the total, and every incorrect bit will remove from the total.
double eval_easy(int* c){

    double total = 0;

    for(int i = 0; i < 100; i+= 10){

        double dec = 0;
        for(int j = i; j < 10 + i; j++){
            // Check if all values are 0/1
            if(c[j] != 0 && c[j] != 1)
                return 0;

            double e = j - i;
            if(c[j] == 1) // Don't need to do this if c[j] == 0
                dec += std::pow(2, e);
            
        }

        double mult = (i / 10) % 2 == 0 ? 1 : -1;
        total += mult * dec;
        
    }

    return total;
}

// Difficult for the hill climber to solve in most cases as it has local maxima.
// This adds up the total number of 1's and puts it under the function:
// sqrt(count) + cos(0.25 * pi * count)
// This function has many local maxima and the only way a hill climber will solve
// this is if it gets lucky with its starting position.
// The optimal value is at 96 1's with a value of 10.8.
double eval_hard(int* c){
    double total = 0;

    for(int i = 0; i < 100; i+= 1){

        // Check if all values are 0/1
        if(c[i] != 0 && c[i] != 1)
            return 0;

        total += c[i];
    }

    return std::sqrt(total) + std::cos(0.25 * M_PI * total);
}



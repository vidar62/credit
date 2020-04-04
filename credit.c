//
//  CS50 Week 1 
//  Problem Set 1.3b credit.c
//  03/04/2020
//  By: Colin Lee
//

#include <cs50.h>
#include <stdio.h>
#include <math.h>   // needed for power operator

int card_type(long card_num, int digit_total); // card check adds the left 1 or 2 number checks

int main(void)
{
    long x = 0; // var for user entered cc number
    long sum = 0; // adds up all the numbers
    long multiplier = 10; // 10 starts at very right, 100 will skip to 2nd digit from very right
    int z = 0; // flag to switch b/t multiplying digits by 2 or not (just add up only)
    int digits = 0; // card length - number of digits
    long cardcheck = 0; // which type of card - checks beginning numbers
    long temp = 0; // temp stores card number for card check

    do
    {
        x = get_long("Number: ");
    }
    while (x < 0);

    temp = x;  // store card num in temp for cardcheck since x var will be modified

    while (x > 0) 
    {
        if (z == 1) // z=1 means the 2nd digit from very right (or 10's position and every other one). Do the multiply by                  2 and additions per the prescribed formulas
        {
            if ((2 * ((x % multiplier) / (multiplier / 10))) > 9)
            {
                //split up 2 digit product and add together instead
                sum = sum + ((2 * (x % multiplier) / (multiplier / 10)) % 10) + ((2 * (x % multiplier) / (multiplier / 10)) % 100 / 10); 
                z = 0; // change back to other digit which isn't multiplied
            }
            else
            {
                sum = sum + 2 * (x % multiplier) / (multiplier / 10); // no need to split up if one digit product (i.e., 0-9)
                z = 0;
            }
        }
        else
        {  
            // this is z=0 or the very right digit and every other one. Just add up, no need to multiply by 2, etc.
            sum = sum + (x % multiplier) / (multiplier / 10); 
            z = 1; // flip flag around to run formulation as the "multiply by 2" variation
        }
        x = x / 10;
        digits++;
//        printf("sum: %li\n", sum); // used for debugging:  show sum as it iterates in this loop
    }

    cardcheck = card_type(temp, digits);

    if ((sum % 10) == 0)
    {

        if ((digits == 15) && (cardcheck == 3))
        {
            printf("AMEX\n");    
        }
        else if ((digits == 16) && (cardcheck == 2))
        {
            printf("MASTERCARD\n");    
        }
        else if (((digits == 13) || (digits == 16)) && (cardcheck == 1))
        {
            printf("VISA\n");    
        }
        else
        {
            printf("INVALID\n"); 
        }
    }
    else
    {
        printf("INVALID\n");
    }
//    printf("digits = %i\n", digits); // used for debugging
}


int card_type(long card_num, int digit_total)
{
    long first, second = 0;  // first number and second number from the left
    
    if (digit_total > 0)  //added to prevent divide by zero error
    {
        first = card_num / (pow(10, digit_total - 1));  // extract first 1st from very left
        second = card_num % ((long)(pow(10, digit_total - 1))) / (pow(10, digit_total - 2)); // extract 2nd number from very left

        if (first == 4)
        {
            return 1; //1 = VISA
        }
        else if ((first == 5) && ((second > 0) && (second < 6)))
        {
            return 2; //2 = MASTERCARD
        }
        else if (((first == 3) && (second == 4)) || ((first == 3) && (second = 7)))
        {
            return 3; // 3 = AMEX
        }
        else
        {
            return 0; // INVALID
        }
    }
    else
    {
        return 0;
    }
}

#include <iostream>
#include <string>
#include <random>
#include <algorithm>

/* These are the character sets. 
These sets will never change so may aswell make them a 'const'. */
const std::string LOWER = "abcdefghijklmnopqrstuvwxyz";
const std::string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string DIGITS = "0123456789";
const std::string SPECIAL = "!@#$%^&*()-_=+[]{}|;:,.<>?";

/* This function does the password generation calculation. */
std::string generatePassword(int length)
{
    /* Add all the charsets into the variable 'allChars'. */
    std::string allChars = SPECIAL + DIGITS + UPPER + LOWER;

    /* This line is a special random number generator designed 
    to provide non-deterministic random number. (i.e., truly random values, 
    or as close as the hardware and OS can provide). */

    /* So all in all this line basically generates non-deterministic a random 'seed'. */
    std::random_device rd;

    /* Now I will add (seed) this Mersenne Twister with it.

    What is a 'mt19937'? well it short for 'Mersenne Twister' which is a popular random 
    number generator algorithm. */
    std::mt19937 gen(rd());

    /* This line below looks mad confusing. It makes me a 'tool' that gives me
    random whole numbers starting from 0 up to one less than the number of characters I have. */

    /* If you're still confused let me try and explain in simpler terms. 
    It makes sure every character in 'allChars' has an equal chance of being picked. */
    std::uniform_int_distribution<> distribution(0, allChars.size() - 1);

    /* Here I define the outputted sum of this function which is the generated password. */
    std::string password;

    /* Start counting at 0. */
    for (int i = 0; i < length; ++i)  /* Keep going while i is less than the password length, 
    then increase i by 1 each time. */ 
    {
        /* Pick a random position from (allChars) and adds that character to the password. */
        password += allChars[distribution(gen)];
    }
    return password;  /* When done, give back the full password. */
}

int main()
{
    /* Now we declare the length as an integer below. */
    int length;

    /* Program asks for desired password length. */
    std::cout << "Enter your desired password length : ";
    /* The length the user picks is stored in the 'length' variable. */
    std::cin >> length;

    /* If-statement which doesn't allow the user to input a 
    desired password length of 0 or below becuase that wouldn't make sense. */
    if (length <= 0)
    {
        /* Outputted error message. Why 'cerr' instead of 'cout'?
        well 'cerr' is used to indicate an error/warning message. */
        std::cerr << "Invalid length!" << std::endl;

        /* Why do I use return 1 instead of 0? 
        Well, by convention in programming, returning 0 means success,  
        while returning 1 (or any non-zero value) indicates failure or an error. */
        return 1;
    }

    /* The line below uses the generatePassword function I made earlier and 
    passes 'length' in it and stores the sum in 'password'. */
    std::string password = generatePassword(length);

    /* This line outputs the generated password. */
    std::cout << "Generated password : " << password << std::endl;

    /* Pause before exiting so user can see output. */
    std::cout << "Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    
    /* If the program reaches the last line 'Return 0', well then that means the program 
    has been successful. '0' = success. */
    return 0;
}
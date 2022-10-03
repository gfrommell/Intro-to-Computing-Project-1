// CSCI 1300 Fall 2022
// Author: George Frommell
// Recitation: B with Jot Kaur
// Project 1: Problem 7

#include <iostream>             // *****SORRY FOR ALL THE FUNCTIONS AT THE BEGINNING*****
#include <iomanip>
#include <string>

using namespace std;

bool isValidNote(string note)
{
    bool note_validity = false;                 // initialize variable

    if (note.length() != 2)                     // input validation
    {
        note_validity = false;
    }
    else if (note[0] >= 65 && note[0] <= 71)    // ASCII validation for alphabet
    {
        if (note[1] >= 48 && note[1] <= 57)     // ASCII validation for numbers
            {
                note_validity = true;
            }
    }
    else
    {
        note_validity = false;
    }

    return note_validity;                       // return boolean value true = 1, false = 0
}

bool isValidTune(string tune)
{
    bool tune_validity;                             // initialize variables

    if (tune.length() % 2 != 0)                     // checking if tunr string has even # of chars
    {
        tune_validity = false;
        return false;
    }

    for (int i = 0; i < tune.length(); i+=2)        // i += 2 operates over every two characters, therefore only operating on full notes
    {
        if (isValidNote(tune.substr(i,2)))          // substring function makes sure the loop is looking at the current i character and the one following
        {
            tune_validity = true;
        }
        else if (!isValidNote(tune.substr(i,2)))    // same substring function
        {
            tune_validity = false;
            return tune_validity;
        }
    }
    
    return tune_validity;                           // return boolean value
}

int numValidNotes(string tune)
{
    int note_count = 0;                         // initialize variables
    for (int i = 0; i < tune.length(); i++)     
    {
        if (isValidNote(tune.substr(i,2)))      // checks the note validity for each substring(i,2)
        {
            note_count++;                       // ncreases valid note count if the note is valid
        }
    }
    return note_count;                          // output note count
}

double tuneSimilarity(string tune1, string tune2)
{
    if (tune1.length() != tune2.length())       // input validation because tunes have to be same length
    {
        return 0;
    }  

    double tune_notes = tune1.length() / 2;     // initialize all variables
    int same_pitches = 0;
    int identical_notes = 0;
    int diff_notes = 0;
    
    for (int i = 0; i < tune1.length(); i+=2)   // checks if the pitches are the same
    {
        if (tune1[i] == tune2[i])
        {
            same_pitches++;                     // similar pitches increment

            if (tune1[i+1] == tune2[i+1])       // if pitches are the same, also checks if octave os the same
            {
                identical_notes++;              // identical notes increment
            }
        }
        
        else if (tune1[i+1] != tune2[i+1])      // checks if pitch and octave are different and then increments diff notes
        {
            diff_notes++;
        }

    }
    double similarity = (same_pitches / tune_notes) + identical_notes - diff_notes;     // similarity calculation
    return similarity;
}

double bestSimilarity(string input_tune, string target_tune)
{
    double max_sim = -89342598746;                      // initialize starting similarity variable to a very low number so that the new sim scores can't be below it
    if (input_tune.length() < target_tune.length())
    {
        return 0;
    }



    for (int i = 0; i <= input_tune.length() - target_tune.length() + 1; i+=2)          // i increments by 2 so we don't run arbitrary processes on the integer parts
    {                                                                                   // bounds are the difference between string lengths plus 1 so we operate over all possible string positions
        double similarity = tuneSimilarity(input_tune.substr(i, target_tune.length()),  // declare similarity variable for each loop
                                            target_tune);
        
        if (similarity > max_sim)       // checks if current sim is greater than max sim
        {
            max_sim = similarity;       // replaces max sim with current sim
        }
    }
    
    return max_sim;                     // return max sim value
}

void printTuneRankings(string tune1, string tune2, string tune3, string target_tune)        // void function because we don't want any return values, only outputs
{
    double tune1_sim = bestSimilarity(tune1, target_tune);          // declares the best similarities for tunes 1-3
    double tune2_sim = bestSimilarity(tune2, target_tune);
    double tune3_sim = bestSimilarity(tune3, target_tune);

    if (tune1_sim >= tune2_sim && tune1_sim >= tune3_sim)           // checks if tune1 is biggest
    {
        if (tune2_sim >= tune3_sim)                                 // checks if tune2 is second
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
        else if (tune3_sim >= tune2_sim)                            // checks if tune3 is second
        {
            cout << "1) Tune 1, 2) Tune 3, 3) Tune 2" << endl;

        }
    }

    else if (tune2_sim >= tune1_sim && tune2_sim >= tune3_sim)      // checks if tune2 is biggest
    {
        if (tune1_sim >= tune3_sim)                                 // checks if tune1 is second
        {
            cout << "1) Tune 2, 2) Tune 1, 3) Tune 3" << endl;
        }
        else if (tune3_sim >= tune1_sim)                            // checks if tune3 is second
        {
            cout << "1) Tune 2, 2) Tune 3, 3) Tune 1" << endl;

        }
    }

    else if (tune3_sim >= tune1_sim && tune3_sim >= tune2_sim)      // checks if tune3 is biggest
    {
        if (tune1_sim >= tune2_sim)                                 // checks if tune1 is second
        {
            cout << "1) Tune 3, 2) Tune 1, 3) Tune 2" << endl;
        }
        else if (tune2_sim >= tune1_sim)                            // checks if tune2 is second
        {
            cout << "1) Tune 3, 2) Tune 2, 3) Tune 1" << endl;

        }
    }

    return;     // no return because void function
}

int main()
{ 
    string user_choice;     // declare all string variables
    string tune1;
    string tune2;
    string tune3;
    string target_tune;
    
    cout << fixed << setprecision(2);       // set precision for all decimal outputs

    cout << "--- Menu --- \n1. Calculate similarity between two tunes.\n2. "<<          // first menu output
        "Calculate best similarity between two tunes of potentially different "<<
        "lengths.\n3. Print three input tunes in order from most to least similar"<<
        " to the target tune.\n4. Exit.\nPlease enter your choice (1 - 4): "
    << endl;
    cin >> user_choice;
    
    if (user_choice[0] == 52)           // termination clause
    {
        cout << "Goodbye!" << endl;
        return 0;
    }
    
    while (user_choice[0] < 49 || user_choice[0] > 52 || user_choice.length() != 1)     // input validation after first menu
    {
        cout << "Invalid Input.\n";
        cout << "--- Menu --- \n1. Calculate similarity between two tunes."<<
        "\n2. Calculate best similarity between two tunes of potentially "<<
        "different lengths.\n3. Print three input tunes in order from most "<<
        "to least similar to the target tune.\n4. Exit.\nPlease enter your "<<
        "choice (1 - 4): " << endl;
        cin >> user_choice;
    }
    
    if (user_choice[0] == 52)           // termination clause
    {
        cout << "Goodbye!" << endl;
        return 0;  
    }

    while (user_choice[0] >= 49 && user_choice[0] <= 52 && user_choice.length() == 1)   // checks valid input
    {
        switch (user_choice[0])         // uses index because user_choice is a string
        {
            case 49:                    // ASCII values because char                    // tuneSimilarity()
                cout << "Please enter the first tune: " << endl;
                cin >> tune1;

                while (!isValidTune(tune1))     // checks if tunes are valid
                {
                    cout << "Invalid Input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune1;
                }

                cout << "Please enter the second tune:" << endl;
                cin >> tune2;

                while (!isValidTune(tune2))
                {
                    cout << "Invalid Input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune2;
                }

                cout << "The similarity score is " << tuneSimilarity(tune1, tune2) << endl;     // performs the function
                
            break;
        
            case 50:                                                                    // bestSimilarity()
                cout << "Please enter the input tune: " << endl;
                cin >> tune1;

                while (!isValidTune(tune1))     // same validation as last case
                {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune1;
                    break;
                }

                cout << "Please enter the target tune:" << endl;
                cin >> tune2;

                while (!isValidTune(tune2))
                {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune2;
                    break;
                }

                cout << "The best similarity score is: " << setprecision(2) <<          // output best similarity
                        bestSimilarity(tune1, tune2) << endl;
                
            break;
            
            case 51:                                                                    // printTuneRankings()
                cout << "Please enter the first tune: " << endl;
                cin >> tune1;

                while (!isValidTune(tune1))         // validation
                {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune1;
                }

                cout << "Please enter the second tune:" << endl;
                cin >> tune2;

                while (!isValidTune(tune2))
                {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune2;
                }
                
                cout << "Please enter the third tune:" << endl;
                cin >> tune3;

                while (!isValidTune(tune3))
                {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune3;
                }
                
                cout << "Please enter the target tune:" << endl;
                cin >> target_tune;
                
                while (!isValidTune(target_tune))
                {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> target_tune;
                }
                
                printTuneRankings(tune1, tune2, tune3, target_tune);        // no need to cout because the printTuneRankings() function couts it for us
                
            break;
        }
        
        cout << "--- Menu --- \n1. Calculate similarity between two tunes.\n2. "        // loop back to menu
            <<"Calculate best similarity between two tunes of potentially different"
            <<" lengths.\n3. Print three input tunes in order from most to least"
            << " similar to the target tune.\n4. Exit.\nPlease enter your choice"
            << " (1 - 4): "
            << endl;
        cin >> user_choice;
        
        while (user_choice[0] < 49 || user_choice[0] > 52 || user_choice.length() != 1) // input validation
        {
            cout << "Invalid Input.\n";
            cout << "--- Menu --- \n1. Calculate similarity between two tunes."<<
            "\n2. Calculate best similarity between two tunes of potentially "<<
            "different lengths.\n3. Print three input tunes in order from most "<<
            "to least similar to the target tune.\n4. Exit.\nPlease enter your "<<
            "choice (1 - 4): " << endl;
            cin >> user_choice;
        }
        
        if (user_choice[0] == 52)       // termination clause
        {
            cout << "Goodbye!" << endl;
            break;
        }
    }

    return 0;           // DONE!! YAY!!!!  :)
}


/* **********************************************
 Magic Mansion Wordle
 Description:
Fetches a random word from the Dictionary file, getting a new word each round
 Each round the word is one letter longer, starting at 4 letters
 User inputs guesses and when they get each word correct, program goes to next round.

Note: this version is built to be used in an online C compiler. 
	Upload this c file and the dictionary text file into the compiler and the code should function.
************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<string.h>

 FILE * fptr; //file pointer

void markerSet(ushort, char *, char *);
    //Function converts the dictionary sections to usable character markers

int main()
{
    // ******************* Random seed *************************
    time_t t;
    srand(time(&t));
    // *********************************************************
    
    
    // ******************** variable declaration ***************
    ushort i = 0,j = 0, k = 0, S=0, match = 0, d=0;
    char s_word[20] = {"0"};
    char guess[20];
    char rightLetters[20] = {};
    char current[20] = {"0"};
    char check,marker=0, marker2=0;
    ushort start_count = 0;
    int num_bytes = 1; //starting at one to skip past numbers to next line containing the word
    int ran_bytes;
    int round_bytes[20];
    round_bytes[0]=0; //initialize the first element to 0.
    // *********************************************************
    
    
    
    // ******************** Start of main loop *********************
    for(j = 0; j<11;j++) //max of 8 until fix integer conversion
    {
        S = 4 + j; //stores size of word for the round, starting at 4.
        markerSet(j, &marker, &marker2); //sets markers to characters
        
        // ********* fetching a word from file in current directory********
        fptr = fopen("./Dictionary_WMM.txt", "r+");
        
        fseek(fptr, 0, SEEK_SET); //sets pointer to start of file
        start_count = 0; //reset to 0 at start of each round
        
        
            // ************* scan file byte-wise, count # of words *******
        do
        {
            check = fgetc(fptr);
            if(check == marker) //takes '0' and turns to character '1'
            {
                    start_count = 1;
            }
            if(start_count == 1) //begins counting at start of each round of #'s
            {
                ++num_bytes;
            }
            fseek(fptr,0,SEEK_CUR); //increments file pointer to next byte location
            
        } while(check != marker2); //end if hit next set of #'s
        
        round_bytes[j+1] = num_bytes; //stores each total bytes in element of an array
                    //arrays holds the total bytes from each round
            // ***************** end of scan ******************************
        
        
        
        // ******* Choosing random word ****************
        ran_bytes = rand()%((num_bytes - round_bytes[j])/(S+1));
            //number between (# bytes in current chunk) / length of strings in chunk
                //Result: number of bytes from start of chunk to start of random word
        ran_bytes = round_bytes[j] + (ran_bytes*(S+1));
            //Converts to location of random string from beginning of the file
            //stores result in same variable
       // *************************************************
        
        
        
        // *************fetch random word from file *****************
        switch (S) //this is to correct the fptr position to print from the beginning of the word
        {
            case (4) :
                fseek(fptr, ran_bytes+2, SEEK_SET);
                break;
            case (5) :
                fseek(fptr, ran_bytes, SEEK_SET);
                break;
            case (6) :
                fseek(fptr, ran_bytes-1, SEEK_SET);
                break;
            case (7) :
                fseek(fptr, ran_bytes-2, SEEK_SET);
                break;
            case (8) :
                fseek(fptr, ran_bytes-3, SEEK_SET);
                break;
            case (9) :
                fseek(fptr, ran_bytes-4, SEEK_SET);
                break;
            case (10) :
                fseek(fptr, ran_bytes-5, SEEK_SET);
                break;
            case (11) :
                fseek(fptr, ran_bytes-6, SEEK_SET);
                break;
            case (12) :
                fseek(fptr, ran_bytes-7, SEEK_SET);
                break;
            case (13) :
                fseek(fptr, ran_bytes-8, SEEK_SET);
                break;
            default :
                printf("Either something went wrong or the game is over.");
                break;
        }
        
        fgets(s_word, 20, fptr); //gets max of 20 characters. Stores in array.
                                    //Stops at '\n' character
        // **************** end fetch random word*******************
        
        
        
        fclose(fptr);
        // *********************file closed **********************
        
        
        
        
        // *************** Wordle Guessing Loop begin **************
        
        //
        //
        //printf("%s", s_word); //FOR TESTING ***********
        //
        //
        
        
        do
        {
            printf("\n\t\tEnter a guess (%d letters)\n\n", S);
            for(k=0; (k<25); ++k)
            {
                guess[k] = getchar(); //might be hitting buffer limit
                guess[k] = toupper(guess[k]);
                if(guess[k] == '\n') break;
            }
            
            match = 0;
            for(i=0; i<S; ++i)
            {
                if(guess[i] == s_word[i])
                {
                    current[i] = s_word[i];
                    ++match;
                }else
                {
                    current[i] = '_';
                }
            }
            
            //checking for right letter, wrong place
            d=0;
            for(i=0; i<S;++i)
            {
                for(k=0;k<S;++k)
                {
                    if(guess[i] == s_word[k])
                    {
                        rightLetters[d] = guess[i];
                        d++;//variable to track the number of matched letter. Used for printing
                    }
                    
                }
            }
            
            //remove duplicates from rightLetters (maybe)
            
            
            for(i=0;i<50;++i)
                printf("\n"); //clears the console
            
            printf("\t\tCurrent guess:\n\t\t%s\n\n", current);
            
            printf("\t\tCorrect Letters: ");
            for(i=0;i<d;++i)
            {
                printf("%c, ", rightLetters[i]);
            }
            printf("\n\n");
            
        }while(match != S);
        printf("\nYou got it!\n\n");
        // *************** end guessing loop *********************
        
    }
    // ****************** end of main loop ***********************
    return 0;
}







void markerSet(ushort i, char * marker, char * marker2)
{
      switch (i)
    {
        case (0) :
            *marker = '0';
            *marker2 = '1';
            break;
        case (1) :
            *marker = '1';
            *marker2 = '2';
            break;
        case (2) :
            *marker = '2';
            *marker2 = '3';
            break;
        case (3) :
            *marker = '3';
            *marker2 = '4';
            break;
        case (4) :
            *marker = '4';
            *marker2 = '5';
            break;
        case (5) :
            *marker = '5';
            *marker2 = '6';
            break;
        case (6) :
            *marker = '6';
            *marker2 = '7';
            break;
        case (7) :
            *marker = '7';
            *marker2 = '8';
            break;
        case (8) :
            *marker = '8';
            *marker2 = '9';
            break;
        case (9) :
            *marker = '9';
            *marker2 = '!';
            break;
        case (10) :
            *marker = '!';
            *marker2 = '@';
            break;
        case (11) :
            *marker = '@';
            *marker2 = '#';
            break;
    }
    return;
}

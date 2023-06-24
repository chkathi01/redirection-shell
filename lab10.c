/* Author(s): Ruthann Biel & Chandu Kathi                   	 
 * This is csc60mshell.c
 * This is lab9.c the csc60mshell
 * This program serves as the base for doing labs 9 and 10.
 * Student is required to use this program to build a mini shell
 * using the specification as documented in the directions.
 * Date: Spring 2023
 */

#include "lab9_10.h"


/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
int main(void)
{
    char CmdLine[MAXLINE];

    // Stores arguments
    char *argv[MAXARGS];
    
    // Stores the number of arguments
    int argc;

    /* Used with char *getcwd(char[size], int size) 
       to get the current working directory */
    char path[MAX_PATH_LENGTH];

    /* Used with int chdir(char* dir)
       to change the directory to char *dir  */
    char *dir;  
         
    // Used to keep track of the success or failure of int chdir(char *dir)     
    int callReturn = 0; 

    // Loop forever to wait and process commands 
    // Ends when user enters "exit" as argv[0]
    while (TRUE) 
    {
        //Fill in the prompt name here
        printf("\ncsc60msh> ");

        /* read the command the user types into the terminal */
        fgets(CmdLine, MAXLINE, stdin);

        /* Call ParseCmd to build argc/argv; their limits declared in lab9_10.h */
        /* ParseCmd gets # of arguments typed in terminal */
        argc = ParseCmd(CmdLine, argv);

        // REQUIRED: Just-to-make-sure printfs 
        printf("Argc = %i \n",  argc);

        int i;
        for(i = 0; i < argc; i++)
            printf ("Argv %i = %s \n", i, argv[i]);

        // If argc is zero, no command declared */
        if (argc == 0)
            /* cmd not entered, just Enter or Space&Enter */
            continue;
 
        if (strcmp(argv[0], "exit") == 0) {
            /* Issue an exit call */
            return(EXIT_SUCCESS);
        } 
        else if (strcmp(argv[0], "pwd") == 0) {
            /* gets and prints working directory */

            /* Error checking if no working directory is returned */
            if ( getcwd(path, MAX_PATH_LENGTH) == NULL) 
                perror("Error finding current working directory");
            else 
                printf("%s\n", path);
            
            continue;            
        }
        else if (strcmp(argv[0], "cd") == 0) {
            // if just cd go set dir to home directory
            if (argc == 1) 
                dir = getenv("HOME"); 
            else
                dir = argv[1]; 
         
            // Change directory and get return value
            callReturn = chdir(dir);
            
            // Use return value to error check
            if (callReturn != 0)
                perror("Error changing directory");   
            
            continue;       
        }
        /* Else, fork off a process */
        else
        {
            ProcessExtCmd(argc, argv);

        }  /* end of the if-else-if (exit) */

    }	   /* end of the while loop */
}   	   /* end of main */


/* Author(s): Chandu Kathi */

/* ----------------------------------------------------------------- */
/*                  Redirect, part of a child process                */
/* ----------------------------------------------------------------- */

#include "lab9_10.h"

void Redirect(int argc, char *argv[])
{
    int i;	     // loop counter
    int out = 0;  // track position of location Out redirection, >
    int in = 0;   // track position of location In redirection, <
    int fd;
    
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], ">") == 0) {
            if (out != 0) {
                // User entered "ls > lsout > file1" 
                printf("Error: Cannot output to more than one file.\n");
                _exit(EXIT_FAILURE);  
            } else if (i == 0) {
                // User entered "> lsout"
                printf("Error: No command was entered.\n");
                _exit(EXIT_FAILURE);
            }
            
            // set out to the current loop_counter
            out = i;     
        } else if (strcmp(argv[i], "<") == 0) {
            if (in != 0) {
                // User entered "wc < lsout < file1"
                printf("Error: Cannot input from more than one file.\n");
                _exit(EXIT_FAILURE);
            } else if (i == 0) {
                // User entered "< lsout"
                printf("Error: No command was entered.\n");
                _exit(EXIT_FAILURE);    
            }

            // set in to the current loop_counter
            in = i;
        }   
    }

    if (out != 0) {
        if (argv[out + 1] == NULL){
            // User entered "ls > NULL"
            printf("Error: No file was entered.\n");
            _exit(EXIT_FAILURE);
        }
        
        // Open the file using name from argv (create file if needed)
        fd = open(argv[out + 1], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
        
        // Error check the open
        if (fd == -1) {
            perror("Error: Failed to open file.");
            _exit(EXIT_FAILURE);   
        }    

        // Switch standard-out to the value of file descriptor 
        dup2(fd, STDOUT_FILENO);
        close(fd);
        
        argv[out] = NULL;
    }    

    if (in != 0) {
        if (argv[in + 1] == NULL) {
            printf("Error: There no file.\n");
            _exit(EXIT_FAILURE);        
        } 
        
        // Open the file using the name from argv
        fd = open(argv[in + 1], O_RDONLY);

        // Error check 
        if (fd == -1) {
            perror("Error Failed to open file.");
            _exit(EXIT_FAILURE);
        }

        // Switch standard-in to the value of the file descriptor
        dup2(fd, STDIN_FILENO);
        close(fd);

        argv[in] = NULL;
    }
}  /*end of function*/


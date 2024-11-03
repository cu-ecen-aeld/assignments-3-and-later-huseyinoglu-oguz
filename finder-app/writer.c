#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        fprintf(stderr,"Not eneugh argument passed!\n");
    }

    //open connection to the syslog
    openlog("WRITER",LOG_PID | LOG_CONS, LOG_USER);

    FILE* fptr;

    fptr = fopen(argv[1],"w");

    if(fptr == NULL) {

        syslog(LOG_ERR,"Error opening file: %s", argv[1]);
        perror("The file could not be opned\n");
        closelog();
        return 1;

    };

   
    fprintf(fptr,"%s",argv[2]);
    fclose(fptr);

    syslog(LOG_INFO,"Successfully wrote to file: %s",argv[1]);
    closelog();

    return 0;
}



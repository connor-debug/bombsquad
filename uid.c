#include <dirent.h>
#include <stdio.h>
#include "get_uid.h"
void get_uid(long tgid) {
  extern int verbose;
  extern char * ulimit_arg;
    char path[40], line[100], *p;
    FILE* statusf;
    extern int connor, test1, statusl; // count the # of processes a user has

    //generalize this by adding configure file later

    snprintf(path, 40, "/proc/%ld/status", tgid);

    statusf = fopen(path, "r");
    
    if(!statusf)
        return;

    while(fgets(line, 100, statusf)) {
      if(strncmp(line, "Uid:", 4) != 0)
            continue;
        //ignore whitespace
        p = line + 5;
        while(isspace(*p)) ++p;

	if(verbose){

        printf("%ld %s", tgid, p);

	}

	if(strncmp(p, "1001", 4) == 0){ // check the uid
	  test1++;
	}
	
        break;
    }

    fclose(statusf);
}

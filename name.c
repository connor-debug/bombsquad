#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "get_name.h"
void get_name(long tgid) { // pass in the pid
	extern int verbose;
    char path[40], line[100], *p;
    FILE* statusf;
    int statusl;

    snprintf(path, 40, "/proc/%ld/status", tgid);

    statusf = fopen(path, "r");
    
    if(!statusf)
		return;

	while(fgets(line, 100, statusf)) {
		if(strncmp(line, "Name:", 5) != 0)
			continue;
		p = line + 6;
        while(isspace(*p)) ++p;

	if(verbose)
		printf("%ld %s", tgid, p);


	//Name of suspect process names,this is configured preemptivley, adding config file later to make this easier-----------------------------------------------------------------------------------------------------------------
	
	if(strncmp(p, "forkbombing", 10) == 0){
		statusl = system("exec killall -9 forkbombing");
	}

	if(strncmp(p, "vfork", 4) == 0){
		statusl = system("exec killall -9 vfork");
	}

	if(strncmp(p, "fork_test", 9) == 0){
		statusl = system("exec killall -9 fork_test");
	}

	//------------------------------------------
	  
        break;
    }

	fclose(statusf);
}

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "proc.h"
  
int stdo = 0;
int n = 0;

int proc (){
DIR* proc = opendir("/proc");
struct dirent* ent;
extern int fast, verbose, linear, test1;
extern char * linear_arg, * cycle_arg, * sleep_arg, * ulimit_arg, * exp_proc ;
char command [60];
long tgid;
int status, linear_a, ulimit_a, exp_proc_a, c, freq = 0;
int curr_count_proc = 0, prev_count_proc, defuse = 0, cycles = 0;
 
if(proc == NULL) {
    perror("opendir(/proc)");
    return 1;
}

exp_proc_a = strtol(exp_proc, NULL, 10); // general default procs expected
linear_a = strtol(linear_arg, NULL, 10); // expected linear rate
ulimit_a = strtol(ulimit_arg, NULL, 10); // highest user limit

while(1){
	while(ent = readdir(proc)) {
		if(!isdigit(*ent->d_name))
			continue;

    tgid = strtol(ent->d_name, NULL, 10);

    curr_count_proc++;
    get_name(tgid);
    get_uid(tgid);
}

	printf("\r                                                                        ");
	printf("\rScanning processes(%d)...", curr_count_proc);
    fflush(stdout);

  //configure users here -----------------------

  if(test1 > ulimit_a){ // user limit exceeded
	  status = system("skill -u test1");
   }

  test1 = 0; //did not exceed limit this cycle

  //--------------------------------------------

	if(linear = 0 && cycles > 0 && curr_count_proc - exp_proc_a  >= 2 * (prev_count_proc - exp_proc_a)){
		printf("exponential growth rate detected, terminating processess...\n");
		status = system("skill -u test1");
		defuse = 1;
		break;
	}

	if(linear = 1 && cycles > 0 && curr_count_proc - exp_proc_a  >=( prev_count_proc - exp_proc_a)+linear_a){
		printf("found it, terminating processess... \n");
		status = system("skill -u test1");
		defuse = 1;
	}
   
	prev_count_proc = curr_count_proc;
	curr_count_proc = 0;
	cycles++;
	closedir(proc);
	proc = opendir("/proc");
    
	if (strtol(cycle_arg, NULL, 10) == cycles){
		printf("Finished.\n");
		break;
	}
	
	if(fast != 1){
		sleep(strtol(sleep_arg, NULL, 10)); //dont sleep if there is speed flag
		}
	}

	closedir(proc);
}

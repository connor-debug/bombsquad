
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parseinput.h"

int fast  = 0, linear = 0, verbose = 0;
int connor, test1 = 0, statusl;
char *exp_proc = "170"; // average processes count for ubuntu
char *linear_arg = "10";
char *cycle_arg = "INFINITE";
char *sleep_arg = "1";
char *ulimit_arg = "500";


int main (int argc, char **argv)
{
	int index;
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "fvl:c:s:u:")) != -1){
		switch (c)
      {
      case 'f':
        fast = 1;
        break;
      case 'v':
        verbose = 1;
        break;
      case 'l':
	linear = 1;
        linear_arg = optarg;
        break;
      case 'c':
	cycle_arg = optarg;
	break;
      case 's':
	sleep_arg = optarg;
	break;
      case 'u':
	ulimit_arg = optarg;
	break;
      case '?':
        if (optopt == 'l')
          fprintf (stderr, "Option requires an argument.\n");
	if (optopt == 'c')
	  fprintf (stderr, "Option requires an argument.\n");
	 if (optopt == 's')
          fprintf (stderr, "Option requires an argument.\n");
	if (optopt == 'u')
	  fprintf (stderr, "Option requires an argument.\n");
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  }


  printf ("fast = %d | verbose = %d | linear argument = %s | number of cycles: %s | sleep per cycle: %s | limiting user processes: %s\n",fast, verbose, linear_arg, cycle_arg,sleep_arg, ulimit_arg);

  proc();

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);
	return 0;
}

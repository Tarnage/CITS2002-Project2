#include "duplicates.h"
#include <getopt.h>

//  duplicates-soln, written by Chris.McDonald@uwa.edu.au, October 2021
//  under licence - creativecommons.org/licenses/by-nc-sa/4.0/

#if	defined(ADVANCED)
#define	OPTLIST		"aAf:h:lmq"
#else
#define	OPTLIST		"aAf:h:lq"
#endif

//  REPORT ERRORS WITH COMMAND-LINE OPTIONS TO stderr
static void usage(char *progname)
{
#if	defined(ADVANCED)
    fprintf(stderr, "Usage: %s [options] dirname1 [dirname2 ...]\n", progname);
#else
    fprintf(stderr, "Usage: %s [options] dirname\n", progname);
#endif
    fprintf(stderr, "where options are:\n");

    fprintf(stderr,
    "  -a\t\tcheck all files, including those beginning with '.'\n");
    fprintf(stderr,
    "  -A\t\treport if this program attempts advanced features\n");
    fprintf(stderr,
    "  -l\t\tlist all duplicates found\n");
#if	defined(ADVANCED)
    fprintf(stderr,
    "  -m\t\tminimize duplicates by creating hard-links\n");
#endif
    fprintf(stderr,
    "  -q\t\tquietly test if any duplicates exist\n");

    fprintf(stderr, "\nPlease report any bugs to %s\n", AUTHOR_EMAIL);
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
    char *progname      = (progname = strrchr(argv[0],'/')) ? progname+1 : argv[0];
    int  nduplicates    = 0;

    bool	aflag	= false;    // include 'hidden' files and directories
    char        *fflag  = NULL;     // files matching this file's SHA2
    char        *hflag  = NULL;     // files with this SHA2
    bool	lflag	= false;    // list duplicates
    bool	qflag	= false;    // silently test for duplicates

#if	defined(ADVANCED)
    bool	mflag	= false;    // minimize duplicates
#endif

    int		opt;

    opterr	= 0;
    while((opt = getopt(argc, argv, OPTLIST)) != -1) {
	switch (opt) {

//  CHECK ALL FILES  (INCLUDING 'hidden' FILES)
	case 'a' :  aflag	= !aflag;
		    break;

//  REPORT ADVANCED ATTEMPT
	case 'A' :
#if	defined(ADVANCED)
                    exit(EXIT_SUCCESS);
#else
                    exit(EXIT_FAILURE);
#endif
		    break;

//  FILES MATCHING THIS FILE'S SHA2
        case 'f' :  fflag       = strdup(optarg);
                    CHECK_ALLOC(fflag);
                    break;

//  FILES WITH THIS SHA2
        case 'h' :  hflag       = strdup(optarg);
                    CHECK_ALLOC(hflag);
                    break;

//  LIST DUPLICATES
	case 'l' :  lflag	= !lflag;
		    break;

#if	defined(ADVANCED)
//  MINIMIZE DUPLICATES
	case 'm' :  mflag	= !mflag;
		    break;
#endif

//  QUIETLY TEST FOR DUPLICATES
	case 'q' :  qflag	= !qflag;
		    break;

//  IF NONE OF THE ABOVE, VALID OPTIONS
	default :   fprintf(stderr,"%s : illegal option -%c\n",
                            progname, optopt);
		    argc = -1;
		    break;
	}
    }
    argv	+= optind;
    argc	-= optind;

//  ENSURE THAT WE HAVE THE REQUIRED NUMBER OF DIRECTORIES
#if	defined(ADVANCED)
    if(argc < 1) {
#else
    if(argc != 1) {
#endif
	usage(progname);
    }

//  FIND FILES WITH SAME HASH AS GIVEN FILENAME
    if(fflag) {

//  THE NEXT BLOCK IS A SIMPLY A TEST TO DETERMINE IF THIS PROGRAM HAS BEEN
//  INVOKED VIA THE WEB-INTERFACE  (WHICH DOES NOT ACCEPT/SUPPORT  -f )
        if(getenv("HTTP_HOST") != NULL) {
            fprintf(stderr,
  "%s: -f option unsupported in sample solution as it cannot be given file '%s'\n",
                    progname, fflag);
        }

//  ENSURE THAT WE CAN READ ANY FILE FOLLOWING THE -f OPTION
        else if(access(fflag, R_OK) != 0) {
            perror(fflag);
            exit(EXIT_FAILURE);
        }

        else {
//  IF GIVEN THE -f OPTION, PRETEND THAT WE WERE, INSTEAD, GIVEN THE -h OPTION
            hflag  = strSHA2(fflag);
            if(hflag == NULL) {
                fprintf(stderr, "%s: cannot calculate SHA2 of '%s'\n", progname, fflag);
                exit(EXIT_FAILURE);
            }
        }
    }

//  CONSIDER EACH REQUESTED DIRECTORY (WILL BE JUST 1 FOR BASIC VERSION)
    nduplicates    = 0;
    for(int a=0 ; a<argc ; ++a) {
        struct stat     statinfo;

//  ENSURE THAT WE CAN ACCESS EACH REQUESTED DIRECTORY
        if(stat(argv[a], &statinfo) != 0 || !S_ISDIR(statinfo.st_mode)) {
            perror(argv[a]);
	    exit(EXIT_FAILURE);
	}
	nduplicates += process_directory(argv[a], aflag, fflag, hflag, qflag);
    }

#if	defined(ADVANCED)
//  MINIMIZE DUPLICATES BY HARD-LINKING DUPLICATE FILES
    if(mflag) {
	nduplicates = minimize_duplicates();
    }
#endif

//  EXIT QUIETLY WITHOUT PRINTING ANYTHING, JUST PROVIDE AN EXIT STATUS
    if(qflag) {
	exit(nduplicates == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    }

//  LIST DUPLICATES?
    else if(lflag) {
	list_duplicates();
    }

//  NO OPTIONS SELECTED, JUST PERFORM DEFAULT ACTION
    else if(hflag == NULL) {
	list_statistics();
    }

    exit(EXIT_SUCCESS);
    return 0;
}

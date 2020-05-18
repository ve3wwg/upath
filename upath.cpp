//////////////////////////////////////////////////////////////////////
// upath.cpp -- Reduce $PATH to unique paths
// Date: Mon May 18 10:49:36 2020   (C) ve3wwg@gmail.com
///////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>

#include <set>
#include <vector>
#include <string>
#include <sstream>

extern int optind;

static unsigned version = 1;
static unsigned point_version = 0;

static int opt_help = 0;
static int opt_version = 0;

static void
usage(char const *cmd) {
	char const *bptr = strrchr(cmd,'/');

	if ( bptr )
		cmd = bptr;
	printf("Usage: %s [-options] [envname..]\n"
		" --help | -h\t\tHelp info.\n"
		" --version | -V\t\tVersion info.\n",
		cmd);
	exit(0);
}

int
main(int argc,char **argv) {
	static option long_opts[] = {
		{ "help", 	no_argument,	nullptr, 0 },
		{ "version",	no_argument,	nullptr, 1 },
	};
	static char const * def[] = { "PATH" };
	char **av = argv;
	unsigned ax = 1;
	int opt_index = 0, opt;
	
	if ( argc <= 1 ) {
		av = (char **)&def;
		argc = 1;
		ax = 0u;
	} else	{
		while ( (opt = getopt_long(argc,argv,"hV",long_opts,&opt_index)) != -1 ) {
			switch ( opt ) {
			case 0:
			case 'h':
				opt_help = 1;
				break;
			case 1:
			case 'V':
				opt_version = 1;
				break;
			case '?':
				// getopt_long() already reported error
				break;
			default:
				abort();
			}
		}
		ax = unsigned(optind);
	}

	if ( opt_version )
		printf("Version %u.%u\n",version,point_version);
	if ( opt_help )
		usage(argv[0]);
	if ( (opt_version | opt_help) && int(ax) >= argc )
		exit(0);

	std::set<std::string> cset;
	std::vector<std::string> vcomp;

	vcomp.reserve(64);

	for ( ; int(ax) < argc && av[ax]; ++ax ) {
		char const *envname = av[ax];
		char const *envp = getenv(envname);

		if ( envp ) {
			if ( !strchr(envp,':') ) {
				printf("%s\n",envp);	// As is
				continue;
			} 

			size_t slen = strlen(envp);
			char buf[slen+1];
			char *ep, *cp;

			strncpy(buf,envp,slen+1);
			for ( cp = strtok_r(buf,":",&ep); cp; cp = strtok_r(nullptr,":",&ep) ) {
				auto it = cset.find(cp);
				if ( it == cset.end() ) {
					cset.insert(cp);
					vcomp.push_back(cp);
				}
			}

			std::stringstream ss;

			for ( auto& component : vcomp ) {
				if ( ss.tellp() > 0 )
					ss << ':';
				ss << component;
			}
			printf("%s\n",ss.str().c_str());
		} else	{
			fprintf(stderr,"Error: Environment variable '%s' is not defined/exported.\n",envname);
			exit(1);		
		}
	}
	return 0;
}

// End upath.cpp

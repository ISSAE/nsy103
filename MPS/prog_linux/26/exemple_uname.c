	#define _GNU_SOURCE
	#include <stdio.h>
	#include <sys/utsname.h>

	int
main (void)
{
	struct utsname	utsname;
	uname (& utsname);
	fprintf (stdout, " sysname  = %s \n nodename = %s \n"
			 " release  = %s \n version  = %s \n"
			 " machine  = %s  \n domain   = %s \n",
		utsname . sysname,
		utsname . nodename,
		utsname . release,
		utsname . version,
		utsname . machine,
		utsname . domainname);
	return (0);
}

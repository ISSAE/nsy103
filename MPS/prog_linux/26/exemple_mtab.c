	#include <stdio.h>
	#include <mntent.h>

	int
main (int argc, char * argv[])
{
	struct mntent mtab;
	char buffer [256];
	FILE * file;

	if (argc != 2) {
		fprintf (stderr, "%s <fichier mtab>\n", argv [0]);
		exit (1);
	}
	if ((file = setmntent (argv [1], "r")) == NULL) {
		perror ("setmntent");
		exit (1);
	}	
	while (1) {
		if (getmntent_r (file, & mtab, buffer, 256) == NULL)
			break;
		fprintf (stdout, "fsname = %s \n dir = %s\n type = %s \n"
				 " opts = %s \n freq = %d \n passno = %d \n",
				 mtab . mnt_fsname, mtab . mnt_dir,
				 mtab . mnt_type,   mtab . mnt_opts,
				 mtab . mnt_freq,   mtab . mnt_passno);
	}
	endmntent (file);
	return (0);
}	
		

	#include <stdio.h>
	#include <mntent.h>

	int
main (void)
{
	FILE * fichier;
	struct mntent * mntent;

	fichier = setmntent ("/etc/fstab", "r");
	if (fichier == NULL)
		exit (1);
	while (1) {
		mntent = getmntent (fichier);
		if (mntent == NULL)
			break;
		if (hasmntopt (mntent, "mand") != NULL)
			fprintf (stdout, "%s (%s)\n",
				mntent -> mnt_fsname,
				mntent -> mnt_dir);
	}
	endmntent (fichier);
	return (0);
}

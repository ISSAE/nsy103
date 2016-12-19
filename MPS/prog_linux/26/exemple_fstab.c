	#include <stdio.h>
	#include <fstab.h>

	int
main (void)
{
	struct fstab * fstab;

	while (1) {
		if ((fstab = getfsent ()) == NULL)
			break;
		fprintf (stdout, "spec = %s \n file = %s\n vfstype = %s \n"
				 " mntops = %s \n type = %s \n freq = %d \n"
				 " passno = %d \n",
				 fstab -> fs_spec, fstab -> fs_file,
				 fstab -> fs_vfstype, fstab -> fs_mntops,
				 fstab -> fs_type, fstab -> fs_freq,
				 fstab -> fs_passno);
	}
	return (0);
}	
		


        #include <stdio.h>
	#include <unistd.h>
	#include <sys/types.h>

	int
main (void)
{
    gid_t	gid_reel;
    gid_t	gid_eff;
    gid_t	gid_sauve;    

    getresgid (& gid_reel, & gid_eff, & gid_sauve);
    fprintf (stdout, "  GID-R = %u,  GID-E = %u, GID-S = %u\n", 
			gid_reel, gid_eff, gid_sauve);

    fprintf (stdout, " setresgid (-1, %u, %u) = %d\n", 
			gid_reel, gid_eff,
	             setresgid (-1, gid_reel, gid_eff));

    getresgid (& gid_reel, & gid_eff, & gid_sauve);
    fprintf (stdout, "  GID-R = %u,  GID-E = %u, GID-S = %u\n", 
			gid_reel, gid_eff, gid_sauve);

    fprintf (stdout, " setresgid (-1, %u, -1) = %d\n", gid_sauve,
	             setresgid (-1, gid_sauve, -1));

    getresgid (& gid_reel, & gid_eff, & gid_sauve);
    fprintf (stdout, "  GID-R = %u,  GID-E = %u, GID-S = %u\n", 
			gid_reel, gid_eff, gid_sauve);

    return (0);
}

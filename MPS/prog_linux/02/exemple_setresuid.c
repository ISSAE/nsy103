
        #include <stdio.h>
	#include <unistd.h>
	#include <sys/types.h>

	int
main (void)
{
    uid_t	uid_reel;
    uid_t	uid_eff;
    uid_t	uid_sauve;    

    getresuid (& uid_reel, & uid_eff, & uid_sauve);
    fprintf (stdout, "  UID-R = %u,  UID-E = %u, UID-S = %u\n", 
			uid_reel, uid_eff, uid_sauve);

    fprintf (stdout, " setresuid (-1, %u, %u) = %d\n", 
			uid_reel, uid_eff,
	             setresuid (-1, uid_reel, uid_eff));

    getresuid (& uid_reel, & uid_eff, & uid_sauve);
    fprintf (stdout, "  UID-R = %u,  UID-E = %u, UID-S = %u\n", 
			uid_reel, uid_eff, uid_sauve);

    fprintf (stdout, " setresuid (-1, %u, -1) = %d\n", uid_sauve,
	             setresuid (-1, uid_sauve, -1));

    getresuid (& uid_reel, & uid_eff, & uid_sauve);
    fprintf (stdout, "  UID-R = %u,  UID-E = %u, UID-S = %u\n", 
			uid_reel, uid_eff, uid_sauve);

    return (0);
}

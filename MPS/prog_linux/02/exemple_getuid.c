        #include <stdio.h>
        #include <unistd.h>

        int
main (void)
{
        fprintf (stdout, "UID r�el = %u, UID effectif = %u\n",
                 getuid (), geteuid ());
        return (0);
}

/* config.h.  Generated automatically by configure.  */
/* Define the following if you have the corresponding header */
#define	CPU_VENDOR_OS ""
/* #undef	HAVE_NETCONFIG_H */	/* <netconfig.h> */
/* #undef	HAVE_NETDIR_H */		/* <netdir.h> */
#define	HAVE_POLL_H 1		/* <poll.h> */
#define	HAVE_PTHREAD_H 1		/* <pthread.h> */
#define	HAVE_STRINGS_H 1		/* <strings.h> */
/* #undef	HAVE_XTI_INET_H */		/* <xti_inet.h> */
/* #undef	HAVE_SYS_FILIO_H */	/* <sys/filio.h> */
#define	HAVE_SYS_IOCTL_H 1	/* <sys/ioctl.h> */
#define	HAVE_SYS_SELECT_H 1	/* <sys/select.h> */
/* #undef	HAVE_SYS_SOCKIO_H */	/* <sys/sockio.h> */
#define	HAVE_SYS_SYSCTL_H 1	/* <sys/sysctl.h> */
#define	HAVE_SYS_TIME_H 1		/* <sys/time.h> */

/* Define if we can include <time.h> with <sys/time.h> */
#define	TIME_WITH_SYS_TIME 1

/* Define the following if the function is provided */
#define	HAVE_BZERO 1
#define	HAVE_GETHOSTBYNAME2 1
#define	HAVE_POLL 1
#define	HAVE_PSELECT 1
#define	HAVE_VSNPRINTF 1

/* Define the following if the function prototype is in a header */
#define	HAVE_GETADDRINFO_PROTO 1	/* <netdb.h> */
#define	HAVE_GETNAMEINFO_PROTO 1	/* <netdb.h> */
#define	HAVE_GETHOSTNAME_PROTO 1	/* <unistd.h> */
#define	HAVE_GETRUSAGE_PROTO 1	/* <sys/resource.h> */
#define	HAVE_HSTRERROR_PROTO 1	/* <netdb.h> */
#define	HAVE_IF_NAMETOINDEX_PROTO 1	/* <net/if.h> */
#define	HAVE_INET_ATON_PROTO 1	/* <arpa/inet.h> */
#define	HAVE_INET_PTON_PROTO 1	/* <arpa/inet.h> */
/* #undef	HAVE_ISFDTYPE_PROTO */		/* <sys/stat.h> */
#define	HAVE_PSELECT_PROTO 1		/* <sys/select.h> */
#define	HAVE_SNPRINTF_PROTO 1		/* <stdio.h> */
#define	HAVE_SOCKATMARK_PROTO 1	/* <sys/socket.h> */

/* Define the following if the structure is defined. */
#define	HAVE_ADDRINFO_STRUCT 1	/* <netdb.h> */
#define	HAVE_IF_NAMEINDEX_STRUCT 1	/* <net/if.h> */
/* #undef	HAVE_SOCKADDR_DL_STRUCT */	/* <net/if_dl.h> */
#define	HAVE_TIMESPEC_STRUCT 1	/* <time.h> */

/* Define the following if feature is provided. */
/* #undef	HAVE_SOCKADDR_SA_LEN */	/* sockaddr{} has sa_len member */
#define	HAVE_MSGHDR_MSG_CONTROL 1	/* msghdr{} has msg_control member */

/* Names of XTI devices for TCP and UDP */
/* #undef	HAVE_DEV_TCP */		/* most XTI have devices here */
/* #undef	HAVE_DEV_XTI_TCP */	/* AIX has them here */
/* #undef	HAVE_DEV_STREAMS_XTISO_TCP */	/* OSF 3.2 has them here */

/* Define the following to the appropriate datatype, if necessary */
/* #undef	int8_t */			/* <sys/types.h> */
/* #undef	int16_t */			/* <sys/types.h> */
/* #undef	int32_t */			/* <sys/types.h> */
/* #undef	uint8_t */			/* <sys/types.h> */
/* #undef	uint16_t */		/* <sys/types.h> */
/* #undef	uint32_t */		/* <sys/types.h> */
/* #undef	size_t */			/* <sys/types.h> */
/* #undef	ssize_t */			/* <sys/types.h> */
/* socklen_t should be typedef'd as uint32_t, but configure defines it
   to be an unsigned int, as it is needed early in the compile process,
   sometimes before some implementations define uint32_t. */
/* #undef	socklen_t */		/* <sys/socket.h> */
/* #undef	sa_family_t */		/* <sys/socket.h> */
/* #undef	SA_FAMILY_T */

/* #undef	t_scalar_t */		/* <xti.h> */
/* #undef	t_uscalar_t */		/* <xti.h> */

/* Define the following, if system suports the feature */
#define	IPV4 1			/* IPv4, uppercase V name */
#define	IPv4 1			/* IPv4, lowercase v name, just in case */
#define	IPV6 1			/* IPv6, uppercase V name */
#define	IPv6 1			/* IPv6, lowercase v name, just in case */
#define	UNIXDOMAIN 1		/* Unix domain sockets */
#define	UNIXdomain 1		/* Unix domain sockets */
#define	MCAST 1			/* multicasting support */

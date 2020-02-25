#include "fct.h"

int aff_type(const char *path)
{
	struct stat sb;
	
	if (stat(path, &sb) == -1)
	{
        fprintf(stderr, "aff_type erreur stat : %s\n", strerror(errno));
        return -1;
    }
    
    printf("Type de fichier : ");

    switch (sb.st_mode & S_IFMT) {
    case S_IFSOCK:  printf("socket\n");				break;
    case S_IFLNK:  printf("lien symbolique\n");		break;
    case S_IFREG:  printf("fichier ordinaire\n");	break;
    case S_IFBLK:  printf("périphérique blocs\n");	break;
    case S_IFCHR:  printf("périphérique blocs\n");	break;
    case S_IFDIR:  printf("répertoire\n"); 			break;
    case S_IFIFO:  printf("fifo\n"); 				break;
    default:       printf("inconnu ?\n");           break;
    }
    
    return 0;
}

int aff_permission(const char *path)
{
	struct stat sb;
	
    if(stat(path,&sb) < 0) 
    {
		fprintf(stderr, "aff_permission erreur stat : %s\n", strerror(errno));
		return -1;
	}   
        
	printf("File Permissions: \t");
    printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");
	
	return 0;
}

int aff_proprietaire(const char *path)
{
	struct stat sb;
	
    if(stat(path,&sb) < 0) 
    {
		fprintf(stderr, "aff_permission erreur stat : %s\n", strerror(errno));
		return -1;
	}   
	
	printf("Propriétaires : UID=%ld GID=%ld\n", (char) sb.st_uid, (char) sb.st_gid);
	return 0;	
}

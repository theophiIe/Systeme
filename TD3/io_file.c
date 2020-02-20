#include "io_file.h"

IO_FILE IO_open(const char *path, int access)
{
	IO_FILE file;
	
	//Initialisation de file
	file.desc = -1;
	file.path = NULL;
	file.access = -1;
	
	//Allocation de la mémoire pour le chemin
	file.path = malloc(strlen(path)*sizeof(char));
	
	if(!file.path)
	{
		fprintf(stderr, "IO_open erreur allocation de mémoir : %s\n", strerror(errno));
		return file;
	}
	
	//Etat d'un fichiher
	struct stat sb;
	int fd1, fd2;
	
	//Test de l'existence du fichier
	if(stat(path, &sb) == -1)
	{
			fd1 = creat(path, 0644);
			
			if(fd1 == -1)
			{
				fprintf(stderr, "IO_open erreur lors de la création du fichier : %s\n", strerror(errno));
				return file;
			}
			
			fd2 = open(path, access);
	}
	
	else
		fd2 = open(path, access);
		
	if(fd2 == -1)
	{
		fprintf(stderr, "IO_open erreur lors de l'ouverture du fichier : %s\n", strerror(errno));
		return file;	
	}
	
	file.desc = fd2;
	strcpy(file.path, path);
	file.access = access;
	
	return file;
}

int IO_close(IO_FILE file)
{
	int valClose = close(file.desc);
	
	if(valClose == -1)
	{
		fprintf(stderr,"IO_close errreur lors de la fermeture du fichier : %s\n", strerror(errno));
        return -1;
	}
	
	free(file.path);
	return 0;
}

int IO_remove(const char *path)
{
	int valUnlink = unlink(path);
	
	if(valUnlink != 0)
	{
		fprintf(stderr,"IO_remove errreur suppresion du fichier : %s\n", strerror(errno));
        return -1;
	}
	
	else 
		return 0;
}

int IO_char_read(IO_FILE file, char *c)
{
	if(file.access == (O_CREAT | O_WRONLY) || file.access == (O_CREAT | O_RDWR) || file.access == O_RDONLY || file.access == O_RDWR)
	{
		int valRead = read(file.desc, c, 1);
		
		if(valRead == -1)
		{
			fprintf(stderr,"IO_char_read errreur de lecture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valRead;
	}
	
	return -1;
}

int IO_char_write(IO_FILE file, const char c)
{
	if(file.access == (O_CREAT | O_WRONLY) || file.access == (O_CREAT | O_RDWR) || file.access == O_RDONLY || file.access == O_RDWR)
	{
		int valWrite = write(file.desc, &c, 1);
		
		if(valWrite == -1)
		{
			fprintf(stderr,"IO_char_write errreur d'ecriture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valWrite;
	}

	return -1;
}

int IO_string_read(IO_FILE file, char *string, int maxSize)
{
	if(file.access == (O_CREAT | O_WRONLY) || file.access == (O_CREAT | O_RDWR) || file.access == O_RDONLY || file.access == O_RDWR)
	{
		int valRead = read(file.desc, string, maxSize);
		
		if(valRead == -1)
		{
			fprintf(stderr,"IO_string_read errreur de lecture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valRead;
	}
	
	return -1;
}

int IO_string_write(IO_FILE file, const char *string, int size)
{
	if(file.access == (O_CREAT | O_WRONLY) || file.access == (O_CREAT | O_RDWR) || file.access == O_RDONLY || file.access == O_RDWR)
	{
		int valWrite = write(file.desc, string, size);
		
		if(valWrite == -1)
		{
			fprintf(stderr,"IO_string_write errreur d'ecriture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valWrite;
	}

	return -1;
}

int IO_int_read(IO_FILE file, int *n)
{
	if(file.access == (O_CREAT | O_WRONLY) || file.access == (O_CREAT | O_RDWR) || file.access == O_RDONLY || file.access == O_RDWR)
	{
		int valRead = read(file.desc, n, 1);
		
		if(valRead == -1)
		{
			fprintf(stderr,"IO_int_read errreur de lecture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valRead;
	}
	
	return -1;
}

int nbre_cara_int(float nbr)
{
	int nbrCara = 0;
	
	while(nbr < 1 && nbr > 0)
	{
		nbr = nbr/10;
		nbrCara++;
	}
	
	return nbrCara;
}

int IO_int_write(IO_FILE file, const int n)
{
	if(file.access == (O_CREAT | O_WRONLY) || file.access == (O_CREAT | O_RDWR) || file.access == O_RDONLY || file.access == O_RDWR)
	{
		
		float nb = n;
		int valWrite = write(file.desc, &n, nbre_cara_int(nb));
		
		if(valWrite == -1)
		{
			fprintf(stderr,"IO_int_write errreur d'ecriture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valWrite;
	}

	return -1;
}


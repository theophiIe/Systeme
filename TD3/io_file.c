#include "io_file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

IO_FILE IO_open(const char *path,int access)
{
	IO_FILE file;
	file.path = malloc(256*sizeof(char));
	int fd = open(path, access | O_CREAT, 0644);
	file.desc = fd;
	
	if(fd == -1)         
        fprintf(stderr,"impossible d'ouvrir le fichier erreur : %s\n", strerror(errno));
	
	else
	{
		strcpy(file.path, path);
		file.access = access;
	}
	
	return file;
}

int IO_close(IO_FILE file)
{
	int val = close(file.desc);
	
	if(val == -1)
	{
		fprintf(stderr,"Errreur fermeture du fichier : %s\n", strerror(errno));
        return -1;
	}
	
	free(file.path);
	return 0;
}

int IO_remove(const char *path)
{
	int valRemove = unlink(path);
	
	if(valRemove != 0)
	{
		fprintf(stderr,"Errreur suppresion du fichier : %s\n", strerror(errno));
        return -1;
	}
	else 
		return 0;
}

int IO_char_read(IO_FILE file, char *c)
{
	if(file.access == O_RDONLY)
	{
		int valRead = read(file.desc ,c ,1);
		
		if(valRead == -1)
		{
			fprintf(stderr,"Errreur de lecture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valRead;
	}
	
	else if(file.access == O_RDWR)
	{
		int valRead = read(file.desc ,c ,1);
		
		if(valRead == -1)
		{
			fprintf(stderr,"Errreur de lecture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valRead;
	}
	
	else 
	{
		return -1;
	}
}
	
int IO_char_write(IO_FILE file, const char c)
{
	if(file.access == O_WRONLY)
	{
		int valWrite = write(file.desc , &c, 1);
		
		if(valWrite == -1)
		{
			fprintf(stderr,"Errreur d'ecriture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valWrite;
	}
	
	else if(file.access == O_RDWR)
	{
		int valWrite = write(file.desc , &c, 1);
		
		if(valWrite == -1)
		{
			fprintf(stderr,"Errreur d'ecriture : %s\n", strerror(errno));
			return -1;
		}
		
		else 
			return valWrite;
	}
	
	else 
	{
		return -1;
	}
}

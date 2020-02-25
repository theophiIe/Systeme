#ifndef H_FCT
#define H_FCT

#include "stdlib.h"		//Fonctions C standard antérieures à POSIX
#include <stdio.h>		//Bibliothèque d’E/S standard
#include <sys/types.h>	//Définition de types standard
#include <sys/stat.h>	//Accès aux caractèristiques d’un fichier
#include <errno.h>		//Gestion des erreurs
#include <unistd.h>		//Appels système antérieurs à POSIX 
#include <fcntl.h>		//Manipuler un descripteur de fichier  
#include <string.h>		//Manipulation de chaînes de caractères

int aff_type(const char *path);
int aff_permission(const char *path);
int aff_proprietaire(const char *path);

#endif


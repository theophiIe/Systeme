#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "io_file.h"

// Affichage du contenu d'un fichier
// \param	path			Nom/chemin du fichier à afficher
// \return					-1 si échec à l'ouverture, 0 sinon
int print(const char *path) 
{
	IO_FILE file = IO_open(path, O_RDONLY);
	
	//Test de l'ouverture du fichier
	if(path == NULL)
	{
		fprintf(stderr, "print erreur ouverture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	char caractere;
	int valRead, valClose;
	
	do
	{
		valRead = IO_char_read(file, &caractere);
		
		if(valRead)
			printf("%c", caractere);
	}
	while(valRead > 0);
	
	valClose = IO_close(file);
	
	//Test de la fermeture du fichier
	if(valClose == -1)
	{
		fprintf(stderr, "print erreur fermeture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	return 0;
}

// Copie de fichier
// \param	path1			Nom/chemin du fichier source
// \param	path2			Nom/chemin du fichier destination
// \return					-1 si échec à l'ouverture, 0 sinon
int copy(const char *path1, const char *path2)
{
	IO_FILE file = IO_open(path1, O_RDONLY);
	
	//Test de l'ouverture du fichier
	if(path1 == NULL)
	{
		fprintf(stderr, "copy erreur ouverture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	char caractere;
	int valRead, valClose;
	
	char *stockCara = malloc(256*sizeof(char));
	int cmptStockRead = 0;
	
	//Test de l'allocation de mémoire 
	if (stockCara == NULL)
	{
		free(stockCara);
		
		fprintf(stderr, "copy erreur probleme memoire : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	//Lecture de file
	do
	{
		valRead = IO_char_read(file, &caractere);
		
		if(valRead)
		{
			stockCara[cmptStockRead] = caractere;
			cmptStockRead++;
		}
	}
	while(valRead > 0);
	
	valClose = IO_close(file);
	
	//Test de la fermeture du fichier
	if(valClose == -1)
	{
		free(stockCara);
		
		fprintf(stderr, "copy erreur fermeture du fichier : %s\n", strerror(errno));
		return -1;
	}
		
	//Ouverture du second fichier
	file = IO_open(path2, O_WRONLY);
	
	//Test de l'ouverture du fichier
	if(path2 == NULL)
	{
		free(stockCara);
		
		fprintf(stderr, "copy erreur ouverture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	int valWrite;
	int cmptStockWrite = 0;
	
	//Ecriture dans le second fichier des caracters du premier ficher
	do
	{
		valWrite = IO_char_write(file, stockCara[cmptStockWrite]);
		
		if(valWrite == -1)
		{
			free(stockCara);
			
			fprintf(stderr, "copy erreur lors de l'ecriture du fichier : %s\n", strerror(errno));
			return -1;
		}
		
		cmptStockWrite++;
		
	}
	while(cmptStockWrite < cmptStockRead && valWrite > 0);
	
	valClose = IO_close(file);
	
	//Test de la fermeture du fichier
	if(valClose == -1)
	{
		free(stockCara);
		
		fprintf(stderr, "copy erreur fermeture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	free(stockCara);
	
	return 0;
}

// Déplacement de fichier
// \param	path1			Nom/chemin du fichier source
// \param	path2			Nom/chemin du fichier destination
// \return					-1 si échec à l'ouverture, 0 sinon
int move(const char *path1, const char *path2)
{
	int valCopy = copy(path1, path2);
	
	if(valCopy == -1)
	{
		fprintf(stderr, "move erreur lors de la copie du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	int valRemove = IO_remove(path1);
	
	if(valRemove == -1)
	{
		fprintf(stderr, "move erreur lors de la suppression du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	return 0;
}

// Comparaison entre deux fichiers
// \param	path1			Nom/chemin du premier fichier
// \param	path2			Nom/chemin du second fichier
// \return					-1 si échec à l'ouverture,
//							1 si fichiers identiques, 0 sinon
int are_the_same(const char *path1, const char *path2)
{
	//Test d'ouverture
	if(path1 == NULL || path2 == NULL)
	{
		fprintf(stderr, "are_the_same erreur ouverture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	char *stockCaraFile1 = malloc(256*sizeof(char));
	char *stockCaraFile2 = malloc(256*sizeof(char));
	
	if (stockCaraFile1 == NULL || stockCaraFile2 == NULL)
	{
		free(stockCaraFile1);
		free(stockCaraFile2);
		
		fprintf(stderr, "are_the_same erreur probleme memoire : %s\n", strerror(errno));
		return -1;
	}
	
	int cmptStockReadFile1 = 0;
	int cmptStockReadFile2 = 0;
	
	int valReadFile1, valReadFile2;
	char caractereFile1, caractereFile2;
	
	//Ouverture du premier fichier
	IO_FILE file1 = IO_open(path1, O_RDONLY);
	
	//Lecture des caracteres du fichier 1
	do
	{
		valReadFile1 = IO_char_read(file1, &caractereFile1);
		
		if(valReadFile1)
		{
			stockCaraFile1[cmptStockReadFile1] = caractereFile1;
			cmptStockReadFile1++;
		}
	}while(valReadFile1 > 0);
	
	int valClose = IO_close(file1);
	
	//Test de fermeture de file1
	if(valClose == -1)
	{
		free(stockCaraFile1);
		free(stockCaraFile2);
		
		fprintf(stderr, "are_the_same erreur fermeture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	//Ouverture du second fichier
	IO_FILE file2 = IO_open(path2, O_RDONLY);
	
	//Lecture des caracteres du second fichier
	do{
		
		valReadFile2 = IO_char_read(file2, &caractereFile2);
		
		if(valReadFile2)
		{
			stockCaraFile2[cmptStockReadFile2] = caractereFile2;
			cmptStockReadFile2++;
		}
	}while(valReadFile2 > 0);
	
	valClose = IO_close(file2);
	
	//Test de fermeture de file2
	if(valClose == -1)
	{
		free(stockCaraFile1);
		free(stockCaraFile2);
		
		fprintf(stderr, "are_the_same erreur fermeture du fichier : %s\n", strerror(errno));
		return -1;
	}
	
	//Comparatif des deux fichiers
	if(!strcmp(stockCaraFile1,stockCaraFile2))
	{
		free(stockCaraFile1);
		free(stockCaraFile2);
		return 1;
	}
	
	free(stockCaraFile1);
	free(stockCaraFile2);
	
	return 0;
}

void check_print() {
	int nstdout = creat("test2.txt", 0644);
	int tmp;

	system("echo 'This file\nis\n\nGREAT!\n' >test1.txt");

	tmp = dup(fileno(stdout));

	// Vider (entre autre) le buffer de stdout
	fflush(NULL);
	dup2(nstdout, fileno(stdout));

	print("test1.txt");

	// Vider (entre autre) le buffer de stdout
	fflush(NULL);
	dup2(tmp, fileno(stdout));

	close(nstdout); close(tmp);
	
	if (!system("diff test1.txt test2.txt >diff.log"))
		printf("'print()' test has succeeded.\n");
	else
		printf("'print()' test has failed.\n");

	system("rm -f diff.log test1.txt test2.txt");
}

void check_copy() {
	system("echo 'This file\nis\n\nGREAT!\n' >test1.txt");

	copy("test1.txt", "test2.txt");

	if (!system("diff test1.txt test2.txt >diff.log"))
		printf("'copy()' test has succeeded.\n");
	else
		printf("'copy()' test has failed.\n");

	system("rm -f diff.log test1.txt test2.txt");
}

void check_move() {
	system("echo 'This file\nis\n\nGREAT!\n' >test1.txt");
	system("cat test1.txt >test2.txt");

	move("test2.txt", "test3.txt");

	if (!system("test -e test2.txt") )
		printf("'move() test has failed.\n");
	else if (!system("diff test1.txt test3.txt >diff.log"))
		printf("'move()' test has succeeded.\n");
	else
		printf("'move()' test has failed.\n");

	system("rm -f diff.log test1.txt test3.txt");
}

void check_are_the_same () {
	system("echo 'This file\nis\n\nGREAT!\n' >test1.txt");
	system("echo 'This file\nis\n\nGREAT!\n' >test2.txt");
	system("echo 'This file\nis\n\nGREAT!\n\n' >test3.txt");
	system("echo 'This fil\nis\n\nGREAT!\n' >test4.txt");
	system("echo 'This file\nis\nGREAT!\n' >test5.txt");

	if (!are_the_same("test1.txt", "test2.txt"))
		printf("'are_the_same()' test#1 has failed.\n");
	else if (are_the_same("test1.txt", "test3.txt"))
		printf("'are_the_same()' test#2 has failed.\n");
	else if (are_the_same("test2.txt", "test4.txt"))
		printf("'are_the_same()' test#3 has failed.\n");
	else if (are_the_same("test3.txt", "test5.txt"))
		printf("'are_the_same()' test#4 has failed.\n");
	else
		printf("'are_the_same()' test has succeeded.\n");

	system("rm -f test1.txt test2.txt test3.txt test4.txt test5.txt");
}

int main(int argc, char **argv) {
	check_print();
	check_copy();
	check_move();
	check_are_the_same();

	return 0;
}

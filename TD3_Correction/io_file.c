#include "io_file.h"

IO_FILE IO_open(const char *path, int access)
{
  IO_FILE file;

  // Init file
  file.path=NULL;
  file.access=-1;
  file.desc=-1;

  // Init the path
  file.path=malloc(strlen(path)*sizeof(char));
  if(!file.path) 
  {
    puts("Error: malloc failed");
    return file;
  }

  // Open the file
  // Test if file exist, creat if doesn't existe
  int fd, fd2;

  struct stat *buffer=malloc(sizeof(struct stat));
  if(stat(path, buffer) == -1) 
  {
    fd2=creat(path, 0644);
    fd=open(path, access);
  }
  // Else open
  else
    fd=open(path, access);

  if((fd == -1) || (fd2 == -1)) 
  {
    printf("Error: file creation failed\nfd = %d, fd2 = %d\n", fd, fd2);
    return file;
  }
  // puts("File '%s' successfully open");

  // It's all is ok
  strcpy(file.path, path);
  file.access=access;
  file.desc=fd;

  return file;
}

int IO_close(IO_FILE file) 
{
  free(file.path);
  // puts("File successfully close");
  return close(file.desc);
}

int IO_remove(const char *path) 
{
  // puts("File successfully dell");
  return unlink(path);
}

int IO_char_read(IO_FILE file, char *c) 
{
  // Test if we have the right to read
  if(file.access == O_RDONLY)
    return read(file.desc, c, 1);
    
  return -1;
}

int IO_char_write(IO_FILE file, const char c) 
{
  // test if we have the right to write
  if(file.access == O_WRONLY)
    return write(file.desc, &c, 1);
    
  return -1;
}

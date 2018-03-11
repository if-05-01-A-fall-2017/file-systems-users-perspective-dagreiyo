#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char* argv[])
{
	printf("Copying from %s to %s\n", argv[1], argv[2]);
	int firstFile = open(argv[1], O_RDONLY);
	int secondFile = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 
							S_IRUSR | S_IROTH | S_IRGRP | S_IXUSR | S_IWUSR);
	char buffer[255];
	int length = read(firstFile, buffer, 255);
	write(secondFile, buffer, length);
	return 0;
}

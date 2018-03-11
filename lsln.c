#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

struct stat at;

void printAcP() {
	printf((S_ISDIR(at.st_mode)) ? "d" : "-");
	printf((at.st_mode & S_IRUSR) ? "r" : "-");
	printf((at.st_mode & S_IWUSR) ? "w" : "-");
	printf((at.st_mode & S_IXUSR) ? "x" : "-");
	printf((at.st_mode & S_IRGRP) ? "r" : "-");
	printf((at.st_mode & S_IWGRP) ? "w" : "-");
	printf((at.st_mode & S_IXGRP) ? "x" : "-");
	printf((at.st_mode & S_IROTH) ? "r" : "-");
	printf((at.st_mode & S_IWOTH) ? "w" : "-");
	printf((at.st_mode & S_IXOTH) ? "x" : "-");
}

int main(int argc, char *argv[]) {
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
        if (dir->d_name[0] != '.') {
          lstat(dir->d_name, &at);
        if (S_ISBLK(at.st_mode) != 0)
          printf("b");
        if (S_ISCHR(at.st_mode) != 0)
          printf("c");
        if (S_ISDIR(at.st_mode) != 0)
          printf("d");
        if (S_ISFIFO(at.st_mode) != 0)
          printf("f");
        if (S_ISLNK(at.st_mode) != 0)
          printf("Symbolic link\n");
        if (S_ISREG(at.st_mode) != 0)
          printf("-");
        if (S_ISSOCK(at.st_mode) != 0)
        printf("s");
				printf(" ");
				printAcP();
				printf("%5d%5d %9d", at.st_uid, at.st_gid, at.st_size);
				struct tm *i;
				i = gmtime(&at.st_mtimespec);
				printf("%6d-%2d-%2d-%2d-%2d ", (1990 + i->tm_year), i->tm_mon + 1, i->tm_mday, i->tm_hour + 1, i->tm_min + 1);
				printf("%s\n", dir->d_name);
			}
		}
		closedir(d);
	}
	return 0;
}

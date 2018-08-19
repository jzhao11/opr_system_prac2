#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//You may also add more include directives as well.
#define NAME "Jianfei"

//THIS VALUE CANNOT BE CHANGED.
//You should use this value when creating your buffer.
// And also to limit the amount each read CAN do.
#define BUFF_MAX 13

int
main(int argc, char const *argv[])
{
	char fromFile[128];
	char toFile[128];
	int in = 0;
	int out = 0;
	int bytes_read = 0;
	int bytes_copied = 0;
	char buffer[BUFF_MAX];

	// user interface
	// ask the user to enter the file name
	printf("Welcome to the File Copy Program by %s!\n", NAME);
	printf("%s\n", "Enter the name of the file to copy from:");
	scanf("%s", fromFile);
	printf("%s\n", "Enter the name of the file to copy to:");
	scanf("%s", toFile);

	// if input (source) file does not exist, then abort
	// if output (destination) file does not exist, then create
	// if output file already exists, then abort
	in = open(fromFile, O_RDONLY, S_IRUSR);
	if (in < 0) {
		perror("error! the input file does not exist");
		return -1;
	}
	out = open(toFile, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (out < 0) {
		perror("error! the output file already exists");
		return -1;
	}

	// copying by repeatedly read and write
	// read from the input file into the buffer
	// write from the buffer to the output file
	while ((bytes_read = read(in, buffer, BUFF_MAX)) > 0) {
		bytes_copied += write(out, buffer, bytes_read);
	}
	close(in);
	close(out);

	// user interface
	// print out message after successfully copying the file
	printf("%s%d%s\n", "File Copy Successful, ", bytes_copied, " bytes copied");
	return 0;
}

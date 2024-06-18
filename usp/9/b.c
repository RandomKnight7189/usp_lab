#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void read_and_display(int fd, int num_chars)
{
    char buffer[21]; // One extra for null terminator
    ssize_t bytes_read = read(fd, buffer, num_chars);
    if (bytes_read < 0)
    {
        perror("Failed to read from file");
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0'; // Null terminate the string
    printf("%s\n", buffer);
}

int main()
{
    const char *filename = "example.txt";

    // Open the file for reading
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Read and display the first 20 characters
    printf("First 20 characters:\n");
    read_and_display(fd, 20);

    // Seek to the 10th byte from the beginning and display 20 characters
    if (lseek(fd, 10, SEEK_SET) < 0)
    {
        perror("Failed to seek to 10th byte");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("20 characters from 10th byte:\n");
    read_and_display(fd, 20);

    // Seek 10 bytes ahead from the current offset and display 20 characters
    if (lseek(fd, 10, SEEK_CUR) < 0)
    {
        perror("Failed to seek 10 bytes ahead from current offset");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("20 characters from current offset + 10 bytes:\n");
    read_and_display(fd, 20);

    // Display the file size
    struct stat file_stat;
    if (fstat(fd, &file_stat) < 0)
    {
        perror("Failed to get file status");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File size: %ld bytes\n", file_stat.st_size);

    // Close the file
    close(fd);

    return 0;
}

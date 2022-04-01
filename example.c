#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int fuzzme(char *buf)
{
  if (strlen(buf) >= 3)
    if (buf[0] == 'b')
      if (buf[1] == 'u')
        if (buf[2] == 'g')
        {
          printf("You've got it!");
          return 1 / 0; // Defect: divide-by-zero.
        }
  return 0;
}

int main(int argc, char *argv[])
{
  FILE *f;
  char buf[12];

  if (argc != 2)
  {
    fprintf(stderr, "Must supply a text file\n");
    return -1;
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    fprintf(stderr, "Could not open %s\n", argv[1]);
    return -1;
  }
  if (read(fd, buf, sizeof(buf)) == -1)
  {
    fprintf(stderr, "Could not read from %s\n", argv[1]);
    return -1;
  }
  fuzzme(buf);
  close(fd);
  return 0;
}

#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shell(char *str, size_t size, const char *script)
{
  FILE *fp;
  char buf[256];  // buffer to hold the output of the script

  // Construct the command string, redirecting stderr to /dev/null to suppress errors
  snprintf(buf, sizeof(buf), "/bin/sh -c \"%s 2>/dev/null\"", script);

  // Execute the command and open a pipe to it
  fp = popen(buf, "r");
  if (!fp) {
    // If the command fails to execute, return an empty string
    str[0] = '\0';
    return 0;  // return 0 to indicate no output
  }

  // Read the output of the command into the buffer
  if (fgets(str, size, fp) == NULL) {
    // If no output, return an empty string
    pclose(fp);
    str[0] = '\0';
    return 0;  // return 0 to indicate no output
  }

  // Clean up and close the pipe
  pclose(fp);

  // Ensure there's no newline in the output
  str[strcspn(str, "\n")] = 0;

  return strlen(str);  // return the length of the output string
}

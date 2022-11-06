#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t session_id = setsid();

  return 0;
}
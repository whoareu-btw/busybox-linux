#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

void print_os() {
   FILE *fp = fopen("/etc/os-release", "r");
   char line[256];

   while (fp && fgets(line, sizeof(line), fp)) {
      if (strncmp(line, "PRETTY_NAME", 12) == 0) {
         char *name = strchr(line, '=');
         if (name) {
            name++;
            if (*name == '"') name++;
            char *end = strrchr(name, '"');
            if (end) *end = '\0';
            printf("OS        : %s\n", name);
         }
      }
   }
   if (fp) fclose(fp);
}

void print_kernel() {
   struct utsname uts;
   uname(&uts);
   printf("Kernel       : %s\n", uts.release);
}

void print_cpu() {
   FILE *fp = fopen("/proc/cpuinfo", "r");
   char line[256];

   while (fp && fgets(line, sizeof(line), fp)) {
      if (strncmp(line, "model name", 10) == 0) {
         char *cpu = strchr(line, ':');
         if (cpu) {
            cpu +=2;
            cpu[strcspn(cpu, "\n")] = '\0';
            printf("CPU          : %s\n", cpu);
            break;
         }
      }
   }
   if (fp) fclose(fp);
}

void print_ram() {
   FILE *fp = fopen("/proc/meminfo", "r");
   char line[256];
   
   long memTotal = 0;
   long memAvail = 0;
   long swapTotal = 0;
   long swapFree = 0;

   while (fp && fgets(line, sizeof(line), fp)) {
      sscanf(line, "MemTotal: %ld kB", &memTotal);
      sscanf(line, "MemAvailable: %ld kB", &memAvail);
      sscanf(line, "SwapTotal: %ld kB", &swapTotal);
      sscanf(line, "SwapFree: %ld kB", &swapFree);
   }

   if (fp) fclose(fp);
   printf("Memory       : %.1f / %.1f GB\n",
         (memTotal - memAvail) / 1024.0 / 1024.0,
        memTotal / 1024.0 / 1024.0);

   printf("Swap         : %.1f / %.1f GB\n",
         (swapTotal - swapFree) / 1024.0 / 1024.0,
         swapTotal / 1024.0 / 1024.0);
}

void print_uptime() {
   FILE *fp = fopen("/proc/uptime", "r");
   double up;

   if (fp && fscanf(fp, "%lf", &up) == 1) {
      int h =up / 3600;
      int m = ((int)up % 3600) / 60;

      printf("Uptime       : %dh %dm\n\n", h, m);
   }
   if (fp) fclose(fp);
}

int main() {
   printf(">>> Fetch <<<\n\n");
   print_os();
   print_kernel();
   print_cpu();
   print_ram();
   print_uptime();
   printf("echo 'end of line'\n");

   return 0;
}

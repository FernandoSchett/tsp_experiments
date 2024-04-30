#ifndef sys_time_functions
#define sys_time_functions

#include <sys/resource.h>

struct CPUTime {
    double s_CPU_inicial, s_CPU_during, s_CPU_final;
    double s_total_inicial, s_total_during, s_total_final;
    double total_s_CPU;
};

void get_cpu_time(double* seg_CPU_total, double* seg_sistema_total);

#endif
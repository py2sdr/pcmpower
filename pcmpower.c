/*
 * PCM Audio Power Meter
 * -------------------------------------------------------------------------
 * Author: Edson Pereira, PY2SDR
 * Code Assistant: Claude AI
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define BLOCK_SIZE 8192

int main()
{
    int16_t buffer[BLOCK_SIZE];
    struct timeval tv;
    struct tm *tm;
    char timestamp[64];
    size_t n;

    while ((n = fread(buffer, sizeof(int16_t), BLOCK_SIZE, stdin)) > 0)
    {
        double sum = 0.0;
        for (size_t i = 0; i < n; i++)
        {
            double s = buffer[i];
            sum += s * s;
        }
        double mean_sq = sum / n;
        double pwr_db = (mean_sq >= 1.0) ? 10.0 * log10(mean_sq) : -INFINITY;  // or 0.0 if you prefer
        gettimeofday(&tv, NULL);
        tm = localtime(&tv.tv_sec);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm);
        printf("%s.%03ld -- %.1f dBFS\n", timestamp, tv.tv_usec / 1000, pwr_db);
        fflush(stdout);
    }

    if (ferror(stdin))
    {
        perror("fread");
        return 1;
    }
    return 0;
}

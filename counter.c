#include <stdio.h>
#include <string.h>
#include <time.h>

int is_numeric(const char* str);
int atoi(const char* str);
void print_time(const char* str, int time);

int main(int argc, char* argv[]){
    printf("\n");
    if (argc == 1){
        time_t t2;
        int t1 = 0;
        while (1){
            print_time("\033[F\rtime: ", t1++);
            t2 = time(NULL);
            while (t2 == time(NULL));
        }
    }else if (argc == 2){
        if (!strcmp("h", argv[1])) {
            printf("usage: counter [h] <time>\n");
            printf("example:\n");
            printf("  counter               to incremently count\n");
            printf("  counter h             show this log\n");
            printf("  counter 120           count 120 seconds decremently\n");
        }else if (is_numeric(argv[1])) {
            time_t t;
            print_time("\033[F\rtime: ", atoi(argv[1]));
            for (int i = atoi(argv[1]); --i >= 0;) {
                t = time(NULL);
                while (t == time(NULL));
                print_time("\033[F\rtime: ", i);
            }
        }else{
            printf("unrecognized command\n");
        }
    }else{
        printf("unrecognized command\n");
    }
    return 0;
}

int is_numeric(const char* str){
    for (int i = 0; i < strlen(str); ++i)
        if (str[i] < 48 || str[i] > 57)
            return 0;
    return 1;
}

int atoi(const char* str){
    int res = 0;
    for (int i = 0; i < strlen(str); ++i) res = res * 10 + str[i] - '0';
    return res;
}

void print_time(const char* str, int time){
    int b = printf(str);
    int s = time, m, h, d;
    if (s >= 60){
        m = s / 60;
        s %= 60;
        if (m >= 60){
            h = m / 60;
            m %= 60;
            b += printf("%d hours ", h);
        }
        b += printf("%d minutes ", m);
    }
    char space[b];
    for (int t=0; t < b; ++t) space[t] = 32;
    space[b-1] = '\0';
    printf("%d seconds%s\n", s, space);
    fflush(stdout);
}

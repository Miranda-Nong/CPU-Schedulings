#include <stdio.h>

int main() {
    int n, m,total[5];
    printf("Enter no. of Process:");
    scanf("%d", &n);
    printf("Enter no. of Resources:");
    scanf("%d", &m);

    int alloc[n][m];
    int max[n][m];
    int avail[m];

    // Input allocation matrix
    for (int i = 0; i < n; ++i) {
        printf("Enter allocation for resource %d\n", i + 1);
        for (int j = 0; j < m; ++j) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum matrix
    for (int i = 0; i < n; ++i) {
        printf("Enter maximum for resource %d\n", i + 1);
        for (int j = 0; j < m; ++j) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter available resources\n");
    for (int i = 0; i < m; ++i) {
        scanf("%d", &avail[i]);
    }

    int need[n][m];

    // Calculate the need matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    printf("Need Matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // calculate total
    int total_need[m];
    for (int i = 0; i < m; ++i) {
         total_need[i] = 0;
        for (int j = 0; j < n; ++j) {
            total_need[i] += need[j][i];
        }
        printf("Total need for resource %d is %d\n", i + 1, total_need[i]);
    }
    int fp[n];
    int p[n];
    int pc = 0;
    int flag = 1;

    for (int i = 0; i < n; ++i) {
        fp[i] = 0;
    }

    while (pc < n) {
        int c = 0;

        for (int j = 0; j < n; ++j) {
            int co = 0;

            if (fp[j] != 1) {
                for (int i = 0; i < m; ++i) {
                    if (need[j][i] <= avail[i]) {
                        co++;
                    }
                }
            }

            if (co == m) {
                c = 1;
                p[pc] = j;
                for (int i = 0; i < m; ++i) {
                    avail[i] += alloc[j][i];
                }
                fp[j] = 1;
                pc++;
            }
        }

        if (c == 0) {
            printf("There will be no safe sequence\n");
            flag = 0;
            break;
        }
    }

    if (flag) {
        printf("The safe sequence will be:\t");
        for (int i = 0; i < n - 1; ++i) {
            printf("P%d -> ", p[i]);
        }
        printf("P%d\n", p[n - 1]);
    }

    return 0;
}
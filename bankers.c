#include <stdio.h>

int main() {
    int n, m;
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
    
    // Print the need matrix
    printf("Need Matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

   // Calculate total allocation and available resources
   int total_alloc[m], total_avail[m];
   for(int i=0;i<m;++i){
       total_alloc[i] = 0;
       total_avail[i] = avail[i];
       for(int j=0;j<n;++j){
           total_alloc[i] += alloc[j][i];
           total_avail[i] += alloc[j][i];
       }
   }

   // Print total allocation and available resources
   printf("Total Allocation and Available Resources:\n");
   for(int i=0;i<m;++i){
       printf("Resource %d: Total Allocation = %d, Total Available = %d\n", i+1, total_alloc[i], total_avail[i]);
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

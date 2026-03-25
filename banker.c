#include <stdio.h>

#define N 5
#define M 3

int main() {
    int alloc[N][M] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[N][M]   = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int avail[M] = {3,3,2}, need[N][M];

    // Need = Max - Allocation
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Display matrices
    printf("\nAlloc\tMax\tNeed\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++) printf("%d ",alloc[i][j]);
        printf("\t");
        for(int j=0;j<M;j++) printf("%d ",max[i][j]);
        printf("\t");
        for(int j=0;j<M;j++) printf("%d ",need[i][j]);
        printf("\n");
    }
    printf("Available: ");
    for(int i=0;i<M;i++) printf("%d ",avail[i]);

    int p, req[M];
    printf("\n\nEnter process (0-4): ");
    scanf("%d",&p);
    printf("Enter request: ");
    for(int i=0;i<M;i++) scanf("%d",&req[i]);

    // Check request
    for(int j=0;j<M;j++){
        if(req[j] > need[p][j]) return printf("Error\n"),0;
        if(req[j] > avail[j]) return printf("Wait\n"),0;
    }

    // Pretend allocation
    for(int j=0;j<M;j++){
        avail[j]-=req[j];
        alloc[p][j]+=req[j];
        need[p][j]-=req[j];
    }

    // Safety Algorithm
    int work[M], finish[N]={0}, safe[N], count=0;
    for(int i=0;i<M;i++) work[i]=avail[i];

    while(count<N){
        int found=0;
        for(int i=0;i<N;i++){
            if(!finish[i]){
                int j;
                for(j=0;j<M;j++)
                    if(need[i][j]>work[j]) break;

                if(j==M){
                    for(int k=0;k<M;k++)
                        work[k]+=alloc[i][k];
                    safe[count++]=i;
                    finish[i]=1;
                    found=1;
                }
            }
        }
        if(!found) return printf("UNSAFE\n"),0;
    }

    printf("\nSAFE sequence: ");
    for(int i=0;i<N;i++) printf("P%d ",safe[i]);

    printf("\nRequest Granted\n");
    return 0;
}

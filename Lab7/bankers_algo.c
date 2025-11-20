// Bankers_Algo
#include <stdio.h>
#include<stdlib.h>

int main()
{

	int n, m, i, j, k;
	printf("Enter no. of processes:\n");
	scanf("%d", &n); // No. of processes
	printf("Enter no. of resources:\n");
	scanf("%d", &m); // No. of resources
	printf("Input Allocation Matrix:\n");
	int alloc[n][m]; // Allocation Mat

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &alloc[i][j]);
		}
	}
	printf("Input MAX Matrix:\n");
	int max[n][m]; // MAX Mat

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &max[i][j]);
		}
	}
	printf("Input Availabe Resources:\n");
	int avail[m]; // Available Resources
	int avail2[m];
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &avail[i]);
		avail2[i]=avail[i];
	}
	label:
	int f[n], ans[n], ind = 0;
	for (k = 0; k < n; k++)
	{
		f[k] = 0;
	}
	int need[n][m];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	}
	int y = 0;
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			if (f[i] == 0)
			{

				int flag = 0;
				for (j = 0; j < m; j++)
				{
					if (need[i][j] > avail[j])
					{
						flag = 1;
						break;
					}
				}

				if (flag == 0)
				{
					ans[ind++] = i;
					for (y = 0; y < m; y++)
						avail[y] += alloc[i][y];
					f[i] = 1;
				}
			}
		}
	}

	int flag = 1;

	for (int i = 0; i < n; i++)
	{
		if (f[i] == 0)
		{
			flag = 0;
			printf("Unsafe.\n P%d must wait. The old resource-allocation state will restore.\n", f[i]);
			break;
		}
	}

	if (flag == 1)
	{
		printf("The system is in a safe state since the sequence < ");
		for (i = 0; i < n - 1; i++)
			printf(" P%d, ", ans[i]);
		printf(" P%d", ans[n - 1]);
		printf("> satisfies safety criteria\n");
	}
	printf("Enter Request process ID:");
	int req;
	scanf("%d",&req);
	printf("Enter Requested resources:");
	int req2[m];
	for(int i=0;i<m;i++){
		scanf("%d",&req2[i]);
	}
	int flag2=0;
	for(int i=0;i<m;i++){
		if(need[req][i]<req2[i]){
			flag2=1;
		}
	}
	if(flag2==0){
		for(int i=0;i<m;i++){
			alloc[req][i]+=req2[i];
			need[req][i]-=req2[i];
			avail2[i]-=req2[i];
		}
		
		printf("yes\nupdated alloc mat:\n");
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				printf("%d ",alloc[i][j]);
			}
			printf("\n");
		}
		printf("\nupdated need mat:\n");
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				printf("%d ",need[i][j]);
			}
			printf("\n");
		}
		printf("\nupdated available resources:\n");
		for(int i=0;i<m;i++){
				printf("%d ",avail2[i]);
			printf("\n");
		}
	}else{
		printf("Request can not immediately be granted. P%d has to wait since resources are not available.",req);
	}

	return (0);
}

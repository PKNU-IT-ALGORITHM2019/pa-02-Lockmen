
#include<stdio.h> 
#include<math.h>
#define MAX 100

typedef struct coordinate {
	int x;
	int y;
	int index;
}coordinate;

int N;
int visit[MAX];
double tsp(coordinate spot[], int k, double min);
double total(int N, coordinate a[]);
double distance(coordinate a, coordinate b);
void swap(coordinate spot[], int a, int b);



double tsp(coordinate spot[], int k, double min) { //prefix 0~k-1  set k~N-1
	if (k == N) { //  모든 배열이 prefix                       

		return total(N, spot);
	}

	for (int i = k; i < N; i++) {
		swap(spot, k, i); // 한 좌표씩 대장을 시켜준다
		double tmp = tsp(spot, k + 1, min);
		if (min> tmp) {
			min = tmp;
			if (k == N - 1)
				for (int i = 0; i < N; i++)
					visit[i] = spot[i].index;
		}
		swap(spot, k, i); //전과 후 동일성 유지
	}
	return min;
}

double total(int N, coordinate a[]) //총 이동 거리
{
	double sum = 0;
	for (int i = 0; i < N; i++) {
		if (i == N - 1) sum += distance(a[i], a[0]);
		else sum += distance(a[i], a[i + 1]);
	}
	return sum;
}

double distance(coordinate a, coordinate  b)  //좌표 공식
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void swap(coordinate spot[], int a, int b)
{
	coordinate temp = spot[a];
	spot[a] = spot[b];
	spot[b] = temp;
}



int main() {
	FILE *fp;
	fopen("input0.txt", "r");
	fscanf(fp, "%d", &N);
	coordinate spot[MAX];
	for (int i = 0; i < N; i++) {
		spot[i].index = i;
		fscanf(fp, "%d %d", &spot[i].x, &spot[i].y);
	}
	double min1 = total(N, spot);

	printf("%lf\n", tsp(spot, 0, min1));
	printf("경로: [ ");
	for (int i = 0; i <= N - 1; i++) printf("%d ", visit[i]);
	printf("]");


	fclose(fp);

	return 0;

}



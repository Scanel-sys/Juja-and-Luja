#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <stdint.h>

struct elem
{
    int x;
    int y;
    int size;
    int if_used;
    int out;
    struct elem *prev;
    struct elem *next;
};

void make_clean(struct elem ** plat, int n);
void print_plat(struct elem ** plat, int n);
void print_if_used(struct elem ** plat, int n);

int main()
{
	uint64_t start_tick, stop_tick;
	int n;
    int level;
    int i, j;
	printf("n = ");
	scanf("%d", &n);
	struct elem** plat = (struct elem **)malloc(sizeof(struct elem *) * n);

	for (i = 0; i < n; i++)
	{
		plat[i] = (struct elem *)malloc(sizeof(struct elem) * n);
	}
	printf("Input map :\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
        {
			scanf("%d", &plat[i][j].size);
            plat[i][j].if_used = 0;
            plat[i][j].prev = NULL;
            plat[i][j].next = NULL;
            plat[i][j].out = 2;
            plat[i][j].x = j;
            plat[i][j].y = i;
        }
	}
	printf("\n");

    struct elem *t_elem;
    struct elem *last_elem = NULL;

    //обработка утечек по борту
	start_tick = __rdtsc();    
    for(i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if((i % (n - 1)) * (j % (n - 1)) == 0)
            {
                t_elem = &plat[i][j];
                last_elem = t_elem;
                t_elem->if_used = 1;

                level = t_elem->size;
                while(plat[i][j].out == 2)
                {
                    if (t_elem->y > 0 && t_elem->y - 1 != 0
                        && !plat[t_elem->y - 1][t_elem->x].if_used)
                    {
                        if (plat[t_elem->y - 1][t_elem->x].size >= t_elem->size &&
                            plat[t_elem->y - 1][t_elem->x].size >= level &&
                            plat[t_elem->y - 1][t_elem->x].out != 1)
                        {
                            last_elem->next = &plat[t_elem->y - 1][t_elem->x];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }

                    if (t_elem->y < n - 1 && t_elem->y + 1 != n
                        && !plat[t_elem->y + 1][t_elem->x].if_used)
                    {
                        if (plat[t_elem->y + 1][t_elem->x].size >= t_elem->size && 
                            plat[t_elem->y + 1][t_elem->x].size >= level &&
                            plat[t_elem->y + 1][t_elem->x].out != 1)
                        {
                            last_elem->next = &plat[t_elem->y + 1][t_elem->x];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }

                    if (t_elem->x > 0 && t_elem->x - 1 != 0
                        && !plat[t_elem->y][t_elem->x - 1].if_used)
                    {
                        if (plat[t_elem->y][t_elem->x - 1].size >= t_elem->size && 
                            plat[t_elem->y][t_elem->x - 1].size >= level &&
                            plat[t_elem->y][t_elem->x - 1].out != 1)
                        {
                            last_elem->next = &plat[t_elem->y][t_elem->x - 1];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }

                    if (t_elem->x < n - 1 && t_elem->x + 1 != n
                        && !plat[t_elem->y][t_elem->x + 1].if_used)
                    {
                        if (plat[t_elem->y][t_elem->x + 1].size >= t_elem->size && 
                            plat[t_elem->y][t_elem->x + 1].size >= level && 
                            plat[t_elem->y][t_elem->x + 1].out != 1)
                        {
                            last_elem->next = &plat[t_elem->y][t_elem->x + 1];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }
                    if(t_elem != last_elem)
                        t_elem = t_elem->next;
                    else
                    {
                        t_elem->if_used = 0;
                        t_elem->out = 1;
                        while(t_elem->prev != NULL)
                        {
                            t_elem = t_elem->prev;
                            t_elem->next->prev = NULL;
                            t_elem->next = NULL;
                            t_elem->if_used = 0;
                            t_elem->out = 1;
                        }
                    }
                }
            }
        }
    }
    //cleanin ised cells
    for(i = 0; i < n; i++)
    {
        plat[i][0].if_used = 0;
        plat[0][i].if_used = 0;
        plat[n-1][i].if_used = 0;
        plat[i][n-1].if_used = 0;
    }

    //поиск внутренних столбов
    for(i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            t_elem = &plat[i][j];
            last_elem = t_elem;
            t_elem->if_used = 1;

            level = t_elem->size;
            while(plat[i][j].out == 2)
            {
                if ((t_elem->y % (n - 1)) == 0 
                     || (t_elem->x % (n - 1)) == 0)
                {
                    t_elem = last_elem;
                    plat[i][j].out = 1;
                    t_elem->if_used = 0;
                    while(t_elem->prev != NULL)
                    {
                        t_elem = t_elem->prev;
                        t_elem->next->prev = NULL;
                        t_elem->next = NULL;
                        t_elem->if_used = 0;
                        if(t_elem->size == level)
                            t_elem->out = 1;
                    }
                }
                else
                {
                    if (!plat[t_elem->y - 1][t_elem->x].if_used)
                    {
                        if (plat[t_elem->y - 1][t_elem->x].size <= level)
                        {
                            last_elem->next = &plat[t_elem->y - 1][t_elem->x];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }
                    if (!plat[t_elem->y + 1][t_elem->x].if_used)
                    {
                        if (plat[t_elem->y + 1][t_elem->x].size <= level)
                        {
                            last_elem->next = &plat[t_elem->y + 1][t_elem->x];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }
                    if (!plat[t_elem->y][t_elem->x - 1].if_used)
                    {
                        if (plat[t_elem->y][t_elem->x - 1].size <= level)
                        {
                            last_elem->next = &plat[t_elem->y][t_elem->x - 1];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }
                    if (!plat[t_elem->y][t_elem->x + 1].if_used)
                    {
                        if (plat[t_elem->y][t_elem->x + 1].size <= level)
                        {
                            last_elem->next = &plat[t_elem->y][t_elem->x + 1];
                            last_elem->next->prev = last_elem;
                            last_elem = last_elem->next;
                            last_elem->if_used = 1;
                        }
                    }
                }
                if(t_elem != last_elem)
                    t_elem = t_elem->next;
                else
                {
                    if (!((t_elem->y % (n - 1)) == 0 || 
                          (t_elem->x % (n - 1)) == 0))
                    {
                        t_elem->out = 0;
                        t_elem->if_used = 0;
                        while(t_elem->prev != NULL)
                        {
                            t_elem = t_elem->prev;
                            t_elem->next->prev = NULL;
                            t_elem->next = NULL;
                            t_elem->if_used = 0;
                            t_elem->out = 0;
                        }
                    }
                }
            }
        }
    }
    
	stop_tick = __rdtsc();
	printf("\n%llu\n", stop_tick - start_tick);

    print_plat(plat, n);

	return 0;
}

void make_clean(struct elem ** plat, int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            plat[i][j].if_used = 0;
}

void print_plat(struct elem ** plat, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            if(plat[i][j].out != 0)
                printf("%d ", plat[i][j].out);
            else
                printf("  ");
        printf("\n");
    }   
}

void print_if_used(struct elem ** plat, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            if(plat[i][j].if_used != 0)
                printf("%d ", plat[i][j].if_used);
            else
                printf("  ");
        printf("\n");
    }   
}

/*
 * * Breno Helfstein Moura       NUSP: 9790972
 * * Lucas Daher                 NUSP: 8991769
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <assert.h>
#include "event.h"
#include "track.h"
#include "cyclist.h"

int min (int a, int b) {
    return (a < b) ? a : b;
}

int max (int a, int b) {
    return (a > b) ? a : b;
}

void merge(int dist[], int id[], int beg, int mid, int end) {
    int size = 1 + end - beg;
    int tempDist[size], tempID[size];
    int x = beg, y = mid + 1;
    for (int i = 0; i < size; i++) {
        if (x > mid) {
            tempDist[i] = dist[y];
            tempID[i] = id[y];
            y++;
        }
        else if (y > end) {
            tempDist[i] = dist[x];
            tempID[i] = id[x];
            x++;
        }
        else {
            if (dist[x] > dist[y]) {
                tempDist[i] = dist[x];
                tempID[i] = id[x];
                x++;
            }
            else {
                tempDist[i] = dist[y];
                tempID[i] = id[y];
                y++;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        dist[beg + i] = tempDist[i];
        id[beg + i] = tempID[i];
    }
}

void sort(int dist[], int id[], int beg, int end) {
    if (beg == end) return;
    int mid = (beg+end)/2;
    sort(dist, id, beg, mid);
    sort(dist, id, mid+1, end);
    merge(dist, id, beg, mid, end);
}

Cyclist ** Cyclists;
Cyclist * report;
Track ** Pista;
int track_size;
int cyclists_num;
int laps_num;
int running;
int checkpoint;
int lucky = -1;
double sim_time;
pthread_mutex_t * run_mutex;
pthread_mutex_t * checkpoint_mutex;
int PlacingDist[13];
int PlacingID[13];
pthread_mutex_t * Placing_mutex;
int broken;
int ** LapPlacing;
pthread_mutex_t * LapPlacing_mutex;

void try_break(Cyclist * C) {
    int rnd = rand() % 100;
    if (rnd == 0) {
	pthread_mutex_lock(run_mutex);
	if (running > 5) {
	    running--;
	    pthread_cancel(*(C->thread));
	    C->broken = 1;
	    broken++;
	    printf("The cyclist %d has just broken at %lf\n", C->id, C->cur_time); 
	}
	pthread_mutex_unlock(run_mutex);
    }
}

void * ciclista(void * ptr) {
    Cyclist * C = (Cyclist *) ptr;
    C->dist = 0;
    C->cur_speed = 30;

    fprintf(stderr, "Ciclista %d pos (%d, %d)\n", C->id, C->i, C->j);    
    while (C->cur_lap < laps_num) {	
	C->cur_time += sim_time;

	if (C->id == lucky) C->cur_speed = 90;

	/* Verify cyclists right in front and try to surpass */
	int ok = 0;
	int my_speed = C->cur_speed;
	while (!ok) {
	    my_speed = 500;
	    int i, qtd = 0;
	    Cyclist * nxt = NULL;
	    for (i = C->i; (nxt = reading_position(Pista, i, C->j)) != NULL && qtd < track_size;
	    	 i = (i + 1) % track_size, qtd++) {
		assert(nxt != NULL);
		my_speed = min(my_speed, max(nxt->cur_speed, 30));
		stop_reading_position(Pista, i, C->j);
	    }
	    stop_reading_position(Pista, i, C->j);
	    if (my_speed == C->cur_speed) ok = 1;
	    else {
		assert(qtd > 1);
		Cyclist * side = NULL;
		Cyclist * behind = NULL;

		if (C->j > 0) {
		    side = reading_position(Pista, i, C->j - 1);
		    behind = reading_position(Pista, (i - 1 + track_size) % track_size, C->j - 1); 
		}
		
		if (C->j > 0 && side == NULL
		    && behind == NULL) {
		    fprintf(stderr, "Ultrapassando coeh %d %d %d\n", C->id, C->i, C->j);
		    stop_reading_position(Pista, i, C->j - 1);
		    fprintf(stderr, "1\n");
		    stop_reading_position(Pista, (i - 1 + track_size) % track_size, C->j - 1); 
		    fprintf(stderr, "2\n");
		    track_leaving_cyclist(Pista, C->i, C->j);
		    fprintf(stderr, "3\n");
		    C->j--;
		    track_arriving_cyclist(Pista, C->i, C->j, C);
		    fprintf(stderr, "Ultrapassei coeh %d %d %d\n", C->id, C->i, C->j);
		}
		else {
		    ok = 1;
		    if (C->j > 0) {
			stop_reading_position(Pista, i, C->j - 1);
			stop_reading_position(Pista, (i - 1 + track_size) % track_size, C->j - 1); 
		    }
		}
	    }
	}

	fprintf(stderr, "Decided speed %d\n", C->id);
	
	if (sim_time == 0.06) {
	    C->dist += (my_speed == 30) ? .5 : 1;
	} else if (sim_time == 0.02) {
	    if (my_speed == 90)
		C->dist += .5;
	    else if (my_speed == 60)
		C->dist += 1.0/3.0;
	    else if (my_speed == 30)
		C->dist += 1.0/6.0;
	}

	if (C->dist >= 1.0) {
	    /* Anda pra frente */
	    fprintf(stderr, "--> %d andando\n", C->id);
	    track_leaving_cyclist(Pista, C->i, C->j);
	    C->i++;
	    C->i %= track_size;
	    track_arriving_cyclist(Pista, C->i, C->j, C);
	    C->blocks++;
	    C->dist = 0;
	    fprintf(stderr, "--> %d andou\n", C->id);
	}
	
	if (C->dist == 0 && C->i == 0) {
	    int rnd = rand() % 10 + 1;
	        
	    C->cur_lap++;
	        
	    pthread_mutex_lock(LapPlacing_mutex);
	    LapPlacing[C->cur_lap][C->id + 2] = LapPlacing[C->cur_lap][1];
	    LapPlacing[C->cur_lap][0]++;
	    pthread_mutex_unlock(LapPlacing_mutex);
	    
	    if (C->cur_speed == 30) {
		if (rnd <= 7) C->cur_speed = 60;
		else C->cur_speed = 30;
	    } else if (C->cur_speed == 60) {
		if (rnd <= 5) C->cur_speed = 60;
		else C->cur_speed = 30;
	    }

	    if (C->cur_lap % 15 == 0) try_break(C);

	    pthread_mutex_lock(checkpoint_mutex);
	    if (C->cur_lap % 10 == 0 &&
		C->cur_lap / 10 > checkpoint) {
		checkpoint++;
	    }
	    if (laps_num - C->cur_lap == 2
		&& lucky == -1) {
		rnd = rand() % 10;
		/* Sortear o cara cm 90 */
		if (rnd == 0) {
		    lucky = rand() % cyclists_num;
		    while (Cyclists[lucky]->broken) {
			lucky = rand() % cyclists_num;
		    }		    
		} else lucky = -2;		
	    }
	    
	    pthread_mutex_unlock(checkpoint_mutex);
	    
	}
        
        int found = 0;
        if (C->blocks > PlacingDist[12]) {
            pthread_mutex_lock(Placing_mutex);
            if (C->blocks >= PlacingDist[12]) {
                for (int cont = 0; cont < 13 && found == 0; cont++) {
                    if (C->id == PlacingID[cont]) {
                        PlacingDist[cont] = C->blocks;
                        sort(PlacingDist, PlacingID, 0, 12);
                        found = 1;
                    }
                }
                if (found == 0) {
                    PlacingDist[12] = C->blocks;
                    PlacingID[12] = C->id;
                    sort(PlacingDist, PlacingID, 0, 12);
                }
            }
            pthread_mutex_unlock(Placing_mutex);
        }

	
	//fprintf(stderr, "Thread %d arrived\n", C->id);
	C->arrive = 1;
	while (C->cont == 0);
	C->cont = 0;
    }
    pthread_mutex_lock(run_mutex);
    running--;
    C->finished = 1;
    pthread_mutex_unlock(run_mutex);
    
}

void print_final_log() {
    int i, q = 1;
    for (i = 0; i < cyclists_num; i++) report[i] = *Cyclists[i];
    qsort(report, cyclists_num, sizeof(Cyclist), cmp_points);
    printf("Final log:\n\n");
    for (i = 0; i < cyclists_num; i++) {
	if (!report[i].broken)
	    printf("[%.3lf] Cyclist %d with %d points\n", report[i].cur_time, report[i].id, report[i].points);
    }
    printf("\nBroken Cyclists:\n\n");
    for (i = 0; i < cyclists_num; i++) {
	if (report[i].broken)
	    printf("Cyclist %d broken in lap %d\n", report[i].id, report[i].cur_lap);
    }
}

void print_report() {
    int i, q = 1;
    for (i = 0; i < cyclists_num; i++) report[i] = *Cyclists[i];
    qsort(report, cyclists_num, sizeof(Cyclist), cmp_blocks);
    for (i = 0; i < cyclists_num; i++) {
	if (!report[i].broken) {
	    if (q == 1) report[i].points += 5;
	    else if (q == 2) report[i].points += 3;
	    else if (q == 3) report[i].points += 2;
	    else if (q == 4) report[i].points += 1;
	    
	    printf("%d. Cyclist %d with %d points [%d]\n", q++, report[i].id, report[i].points, report[i].blocks);
	        
	}
    }
    printf("\n\n");
}

void print_10_log() {
    int i, q = 1;
    for (i = 0; i < cyclists_num; i++) report[i] = *Cyclists[i];
    qsort(report, cyclists_num, sizeof(Cyclist), cmp_points);
    printf("Current score:\n");
    for (i = 0; i < cyclists_num; i++) {
	if (!report[i].broken)
	    printf("Cyclist %d with %d points\n", report[i].id, report[i].points);
    }
    printf("\n");
}

void print_lap_log(int n) {
    
    //printf("LapPlacing[%d][0] = %d\n", n, LapPlacing[n][0]);
    //printf("LapPlacing[%d][1] = %d\n", n, LapPlacing[n][1]);
    
    for (int i = 0; i < cyclists_num; i++) {
        if (LapPlacing[n][i + 2] != -1) {
            printf("Cyclist %d completed lap %d in place #%d\n", i, n, LapPlacing[n][i + 2]);
        }
    }
    printf("\n");
}

int main(int argc, char * argv[]) {
    /*
      d = Track size (in meters)
      v = Number of Circuits
      n = Number of Ciclists
    */
    int d, v, n;
    int i, j, q;
    int next_to_print = 1;
    
    srand(time(NULL));
    
    if (argc < 4) {
	fprintf(stderr, "Fatal error: Not enough arguments\n");
	return -1;
    }
    
    d = atoi(argv[1]);
    n = atoi(argv[2]);
    v = atoi(argv[3]);

    /*
      if (d < 250) {
      fprintf(stderr, "Track Size must be greater or equal than 250\n");
      return -1;
      }

      if (n <= 5 || n > 5 * d) {
      fprintf(stderr, "Number of Ciclists must be between 6 and 5 * Track_Size, inclusive\n");
      return -1;
      }

      if (v % 20 != 0) {
      fprintf(stderr, "Number of circuits must be divisible by 20\n");
      return -1;
      }
    */

    /*
      Turn on the debug (event) log
    */
    if (argc > 4 && strcmp(argv[4], "d") == 0) {
	event(NULL);
    }    

    
    /*
      Initializing Variables
    */
    track_size = d;
    cyclists_num = n;
    laps_num = v;
    run_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    checkpoint_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    Placing_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    LapPlacing_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(run_mutex, NULL);
    pthread_mutex_init(Placing_mutex, NULL);
    pthread_mutex_init(LapPlacing_mutex, NULL);
    sim_time = 0.06;
    running = cyclists_num;
    report = (Cyclist *) malloc(sizeof(Cyclist) * cyclists_num);
    LapPlacing = (int **) malloc(sizeof(int *) * (laps_num + 1));
    for (int i = 0; i <= laps_num; i++) {
        LapPlacing[i] = (int *) malloc(sizeof(int) * (cyclists_num + 2));
        LapPlacing[i][0] = 0;
        LapPlacing[i][1] = 1;
        for (int j = 2; j < cyclists_num + 2; j++) LapPlacing[i][j] = -1;
    }
    
    
    /*
      Creating Track
    */    
    Pista = track_create(track_size);
    Cyclists = (Cyclist **) malloc (sizeof(Cyclist *) * cyclists_num);
    q = 0;
    for (i = 0; i < track_size && q < cyclists_num; i++) {
	for (j = 0; j < 10 && q < cyclists_num; j++) {
	    Cyclists[q] = cyclist_create(q, i, j);
	    track_arriving_cyclist(Pista, i, j, Cyclists[q]);
	    report[q] = *Cyclists[q];
	    q++;
	}
    }

    int local_checkpoint = checkpoint;
    
    /* Creating Threads */    
    for (i = 0; i < cyclists_num; i++) {
	pthread_create(Cyclists[i]->thread, NULL, ciclista, (void *) Cyclists[i]);    
    }
    
    /* Coordinator */
    double cord_time = 0;
    while (running > 0) {
	cord_time += sim_time;
	for (i = 0; i < cyclists_num; i++) {
	    if (Cyclists[i]->finished || Cyclists[i]->broken)
		continue;
	    else {
		while (Cyclists[i]->arrive == 0 && Cyclists[i]->finished == 0 && Cyclists[i]->broken == 0);
		Cyclists[i]->arrive = 0;	
	    }
	}

        if (PlacingDist[0] - PlacingDist[1] >= track_size * (1 + Cyclists[PlacingID[0]]->voltas_vantagem)) {
            Cyclists[PlacingID[0]]->voltas_vantagem++;
            Cyclists[PlacingID[0]]->points += 10;
            
            /*debug
	      printf("Volta de vantagem do %d\nPlacingDist[0] = %d, %d\n", PlacingID[0], PlacingDist[0], Cyclists[PlacingID[0]]->blocks);
	      printf("PlacingDist[1] = %d, %d\n", PlacingDist[1], Cyclists[PlacingID[1]]->blocks);
            */
        }
        
        
        int numC = min(12, cyclists_num - broken);
        for (int i = numC; i >= 0; i--) {
            if (PlacingDist[i] != 0 &&
                Cyclists[PlacingID[i]]->dist == 0 &&
                PlacingDist[i] % (track_size * 10) == 0) {
                if (PlacingDist[i] == PlacingDist[0]) {
                    Cyclists[PlacingID[i]]->points += 5;
                    //printf("%d marcou 5 pontos em %lf\n", PlacingID[i], Cyclists[PlacingID[i]]->cur_time);
                }
                else if (PlacingDist[i] == PlacingDist[1]) {
                    Cyclists[PlacingID[i]]->points += 3;
                    //printf("%d marcou 3 pontos em %lf\n", PlacingID[i], Cyclists[PlacingID[i]]->cur_time);
                }
                else if (PlacingDist[i] == PlacingDist[2]) {
                    Cyclists[PlacingID[i]]->points += 2;
                    //printf("%d marcou 2 pontos em %lf\n", PlacingID[i], Cyclists[PlacingID[i]]->cur_time);
                }
                else if (PlacingDist[i] == PlacingDist[3]) {
                    Cyclists[PlacingID[i]]->points += 1;
                    //printf("%d marcou 1 pontos em %lf\n", PlacingID[i], Cyclists[PlacingID[i]]->cur_time);
                }
                if (PlacingDist[i] == track_size * laps_num) PlacingDist[i]++;
            }
        }
        
        for (int i = next_to_print; i <= laps_num; i++) {
            LapPlacing[i][1] += LapPlacing[i][0];
            LapPlacing[i][0] = 0;
            if (LapPlacing[i][1] > cyclists_num - broken) {
                print_lap_log(next_to_print);
                if ((next_to_print %10) == 0) print_10_log();
                next_to_print++;
            }
        }
        
	if (lucky != -1) sim_time = 0.02;
	track_print(Pista, track_size, cord_time);
	if (local_checkpoint < checkpoint) {
	    //print_report();
	    local_checkpoint = checkpoint;
	}	

	for (i = 0; i < cyclists_num; i++) {
	    if (Cyclists[i]->finished || Cyclists[i]->broken)
		continue;
	    else {
		Cyclists[i]->cont = 1;
	    }
	}
		
    }
    
    for (i = 0; i < cyclists_num; i++) {
	if (Cyclists[i]->broken == 0) {
	    if (pthread_join(* (Cyclists[i]->thread), NULL)) {
		fprintf(stderr, "Fatal error: failed to join thread %d\n", Cyclists[i]->id);
		return -1;
	    }
	}
    }

    print_final_log();
    
    track_destroy(Pista, track_size);
    for (i = 0; i < cyclists_num; i++) {
	free(Cyclists[i]);	
    }
    free(Cyclists);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char * string;

typedef enum facing_ { RIGHT, LEFT } facing;

typedef struct domino_ {
    int alive;
    facing face;
    int id;
} domino;

domino init_domino(int id, char c) {
    domino d;
    d.id = id;
    switch (c) {
        case '\\':
            d.face = 0;
            break;
        case '/':
            d.face = 1;
            break;
    }
    d.alive = 1;
    return d;
}

typedef struct grid_ {
    int size;
    domino * tab;
} grid;

grid init_grid(string filename) {
    FILE * fp = fopen(filename, "r");
    
    grid nGrid;

    int n;
    fscanf(fp, "%d\n", &n);
    nGrid.size = n;

    nGrid.tab = (domino *)malloc(n * sizeof(domino));

    char c;
    for(int d_i = 0; d_i < n; d_i++) {
        fscanf(fp, "%c", &c);
        domino d = init_domino(d_i, c);
        nGrid.tab[d_i] = d;
    }

    return nGrid;
}

void print_grid(grid g) {
    char c;
    for(int d_i = 0; d_i < g.size; d_i++) {
        if (!g.tab[d_i].alive) {
            printf("_  ");
            continue;
        }
        switch (g.tab[d_i].face) {
            case 0:
                c = '\\';
                break;
            case 1:
                c = '/';
                break;
        }
        printf("%c  ", c);
    }
    printf("\n");
    for(int d_i = 0; d_i < g.size; d_i++) {
        if (d_i < 10) printf("%d  ", g.tab[d_i].id);
        else printf("%d ", g.tab[d_i].id);
    }
    printf("\n");
}

void trigger(grid * g, int n) {
    int starting, ending;
    switch (g->tab[n].face) {
        case 0:
            starting = 0;
            ending = n + 1;
            break;
        case 1:
            starting = n;
            ending = g->size;
            break;
    }
    for(int d_i = starting; d_i < ending; d_i++) {
        g->tab[d_i].alive = 0;
    }
}

int main(int argc, string argv[]) {
    grid game = init_grid(argv[1]);
    
    int in;
    while (1) {
        print_grid(game);
        printf("Piece to trigger : ");
        scanf("%d%*c", &in);
        trigger(&game, in);
    }
}
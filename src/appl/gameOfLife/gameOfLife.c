/*
 *
 *  GameOfLife ((c) 2026 Antirez)  
 *
 *  Adeguato per farlo girare con la libc e driver VGA interno a null0s - (c) jack0e|ee
 *
 *  Le modifiche son queste poche :
 *
 *  a) ho tradotto i commenti in italiano, durante la lettura del codice
 *  b) rinominato i nomi delle funzioni (mi piaceva avercele con altro nome, secondo le
 *     naming convention.
 *  c) modificata essenzialmente la funzione che visualizza l'array a video (printGrid), 
 *     che utilizzava la printf ed una sequenza di escape VT100 per pulire lo schermo.           
 *     Per la printf, non avendoci ancora tale funzione l'ho sostituita con una putchar  
 *     che va bene uguale visto che stampava un carattere dell'array per volta. 
 *     Invece per la pulizia dello schermo, non avendo implementato ancora, ne la 
 *     printf ne tantomeno un parse per interpretare gli escape VT100, l'ho sostituita 
 *     con la chiamata di una funzione del driver vga, quindi tramite funzione non
 *     standard C (c98/x99). In futuro cerchero' di implementare le funzionalita' mancanti
 *     elencate, per far girare il codice antirez originale, e cos apiu' importante
 *     ANSI.
 *  d) Inoltre ho aggiunto la chiamata ad un altra funzione non standard (sempre del 
 *     driver_vga per colorare foreground ed underground, sostituendo nella fase di 
 *     visualizzazione dei semplici spazi ai caratteri '*' (stato ELIVE) e '.' 
 *     (stato DEAD).
 *
 *  Un ringraziamento ad Antirez per il corso di C, che mi ha rivegliato il piacere 
 *  immenso nel programmare in linguaggio C.
 *
 */

#include <stdio.h>  

/*
.---------------------------------------------.
| Define che dimensionano la griglia di gioco |
| e gli stati possibili stati delle celle.    |
'---------------------------------------------' */
#define GRID_COLS 79 
#define GRID_ROWS 20 
#define GRID_CELLS (GRID_COLS*GRID_ROWS)
#define ALIVE '*'
#define DEAD  '.'

/*
.--------------------------------------------------------------------------------------.
| Cell2Offset : Traduce le coordinate in offset, gestendo punti al di fuori della      |
| griglia (sia positivi che negativi.                                                  |
+--------------------------------------------------------------------------------------+
|                                                                                      |
| Casistiche per la griglia :                                                          |
|                                                                                      |
| GRID_COLS  : 60                                                                      |
| GRID_ROWS  : 20                                                                      |
| Dimensioni : GRID_COLS * GRID_ROWS = 1200 (offset 0-1199)                            | 
|                                                                                      |
| STEP01 - Eventuale Correzione     : x,y -> x1,y1                                     |
| STEP02 - Calcola e Rirorna Offset : y1 * GRID_COLS + x1                              |
|                                                                                      |
|     +-------+-------+--------+--------+---------------------+-----------------+      |
|     |   x   |   y   |   x1   |   y1   |       Offset        |      Nota       |      |
|     +-------+-------+--------+--------+---------------------+-----------------+      |
|     |  10   |  10   |   10   |   10   |  (10*60)+10 =  610  |                 |      |
|     |  60   |  10   |    0   |   10   |  (10*60)+ 0 =  600  | return SX       |      |
|     |  10   |  20   |   10   |    0   |  ( 0*60)+10 =   10  | return UP       |      |
|     |  60   |  20   |    0   |    0   |  ( 0*60)+ 0 =    0  | return SX/UP    |      |
|     |  -1   |  10   |   59   |   10   |  (10*60)+59 =  659  | return DX       |      |
|     |  10   |  -1   |   10   |   19   |  (19*60)+10 = 1150  | return DOWN     |      |
|     |  -1   |  -1   |   59   |   19   |  (19*60)+59 = 1199  | return DX/DOWN  |      |
|     |  59   |  19   |   59   |   19   |  (19*60)+59 = 1199  |                 |      |
|     +-------+-------+--------+--------+---------------------+-----------------+      | 
|                                                                                      |
|                                                                                      |
'--------------------------------------------------------------------------------------' */  
int cell2Offset(int x, int y) {
    if (x < 0) {
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x;
    }
    if (y < 0) {
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y;
    }

    if (x >= GRID_COLS) x = x % GRID_COLS;
    if (y >= GRID_ROWS) y = y % GRID_ROWS;

    return y*GRID_COLS+x;
}

/*
.--------------------------------------------------------------------------.
| setCell | Imposta lo STATO (viva|morta) di una cella di posizione (x,y)  | 
|           all'interno di una griglia.                                    |
'--------------------------------------------------------------------------' */
void setCell(char *grid, int x, int y, char state) {
    grid[cell2Offset(x,y)] = state;
}

/*
.--------------------------------------------------------------------------.
| getCell | Ritorna lo STATO (viva|morta) di una cella di posizione (x,y)  |
|           all'interno di una griglia.                                    |
'--------------------------------------------------------------------------' */
char getCell(char *grid, int x, int y) {
    return grid[cell2Offset(x,y)];
}

/*
.-------------------------------------------------------------------------.
| setGrid | inizializza l'intera Griglia con lo STATO ricevuto           |
'-------------------------------------------------------------------------' */
void setGrid(char *grid, char state) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            setCell(grid,x,y,state);
        }
    }
}

/*
.--------------------------------------------------------------.
| printGrid | Mostra a video la Griglia ricevuta               |
'--------------------------------------------------------------' */
void printGrid(char *grid) {

    /* Si riposiziona all'origine (0,0) */ 
    vga_console_setposition (0,3);

    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {

             /*
              * Per ALIVE e DEAD cambia esclusivamente lo sfondo
              * a distinguerli, rendendo invisibile il contenuto della cella
              * impostando con lo stesso colore background e foreground */
             if ( getCell(grid,x,y) == ALIVE ) { 
                    vga_console_setcolor ( VGA_COLOR_BLUE, VGA_COLOR_BLUE );
             }

             if ( getCell(grid,x,y) == DEAD  ) {
                    vga_console_setcolor ( VGA_COLOR_CYAN, VGA_COLOR_CYAN );
             }

             putchar(getCell(grid,x,y));
        }
        putchar('\n');
    }
}

/*
.-----------------------------------------------------------.
| countLivingNeighbors | Ritorna il numero di celle vice    |
| attorno ad una cella di coordinate (x,y) all'interno      |
| della griglia.                                            |
'-----------------------------------------------------------' */
int countLivingNeighbors(char *grid, int x, int y) {
    int alive = 0;
    for (int yo = -1; yo <= 1; yo++) {
        for (int xo = -1; xo <= 1; xo++) {
            if (xo == 0 && yo == 0) continue;
            if (getCell(grid,x+xo,y+yo) == ALIVE) alive++;
        }
    }
    return alive;
} 

/*
.---------------------------------------------------------.
| computeNewState | crea l'immagine nuova delle Griglia   |
| in base alla regola che ogni cella vive se ha almeno    |
| 2|3 celle vive attorno, altrimenti e' morta.            |
| old e' la griglia attuale che riceve e *new* e' la      |
| griglia nuova che imposta.                              |
'---------------------------------------------------------' */
void compute_new_state(char *old, char *new) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
//-------
            int n_alive = countLivingNeighbors(old,x,y);
//-------
            int new_state = DEAD;
//-------
            if (getCell(old,x,y) == ALIVE) {
                if (n_alive == 2 || n_alive == 3)
                   new_state = ALIVE;
            } else {
                if (n_alive == 3)
                    new_state = ALIVE;
            }
//-------
            setCell(new,x,y,new_state);
//-------
        }
    }
}

void usleep_fake(long time) {  
   for (long count=0; count<=time; count++) {};
}

void gameOfLife(void) {
//-----
    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];

    /* Pulisce la griglia di memoria - tutti DEAD :P */
    setGrid(old_grid,DEAD);

    /* Imposta gli schemo magici. Questi son parametri importanti
     * andrebbero portati fuori e passati alla funzione principale...
     * sarebbe meglio */ 

    /* 
     * forma-1 :
     *
     *                  X
     *                X X
     *                 XX
     *
     */
    setCell(old_grid, 9,10,ALIVE);
    setCell(old_grid,10,10,ALIVE);
    setCell(old_grid,11,10,ALIVE);
    setCell(old_grid,11, 9,ALIVE);
    setCell(old_grid,10, 8,ALIVE);

    /* 
     * forma-2 :
     *
     *                  XX
     *                  X X
     *                  X
     *
     */
    setCell(old_grid,49,15,ALIVE);   
    setCell(old_grid,49,16,ALIVE);
    setCell(old_grid,50,15,ALIVE);
    setCell(old_grid,50,17,ALIVE);
    setCell(old_grid,51,15,ALIVE);


    /*
     * forma-3 :
     *
     *                  X
     *                  X X
     *                  XX
     *
     */
    setCell(old_grid,29,5,ALIVE);
    setCell(old_grid,30,5,ALIVE);
    setCell(old_grid,30,7,ALIVE);
    setCell(old_grid,31,5,ALIVE);
    setCell(old_grid,31,6,ALIVE);

    /* 
     * forma CUBO 2x2 -- statica
     */
    setCell(old_grid,25,15,ALIVE);
    setCell(old_grid,26,15,ALIVE);
    setCell(old_grid,25,16,ALIVE);
    setCell(old_grid,26,16,ALIVE);


    /* Ciclo di infinito, in cui viene sempre creata una nuova immagine       
     * della giglia applicando la regola del gioco. Ho inserito una usleep_fake
     * a volo per far girare il codice mantenendo la pausa. In quetso caso pero'
     * la fake genera dei NOP verso la CPU, cioe' la tiene comunque occupata
     * mentre la vera usleep dice alla CPU di non occuparsi del processo 
     * per il tempo di milli o microsecondi specificati --PUNTO DA RIVEDERE-- */ 
    while (1) {
//--------
        compute_new_state(old_grid, new_grid);
        printGrid(new_grid);
        usleep_fake(10000000);
//--------
        compute_new_state(new_grid, old_grid);
        printGrid(old_grid);
        usleep_fake(10000000);
    }
}

/* EOF */


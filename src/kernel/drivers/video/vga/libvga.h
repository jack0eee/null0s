
/* libvga.h | driver vga */ 

#ifndef LIBVGA_H
#define LIBVGA_H

#define VGA_DIM_X   80
#define VGA_DIM_Y   25

/*

Buffer VGA 

Il Buffer VGA corrisponde ad un area di memoria che inizia  
all'indirizzo "0xB8000" e con dimensione di quasi 4k (4000 byte)
Corrisponde ad un'area video di 80x25 caratteri (2000), e  
se si considera che, ogni carattere dovra' essere seguito dal 
suo attributo, i calcoli quadrano. (80*25*2=4000)

0xB8000
+-------+-------+-------+-------+ - - - - +-----------+-----------+
|       | attr  |       | attr  |         |           | attr      |
| char1 | char1 | char2 | char2 |         | char-2000 | char-2000 |
+-------+-------+-------+-------+ - - - - +-----------+-----------+

Del byte attributo del carattere i primi 4bit son per il 
Foreground [FG] ed i successivo 4bit per il backgound [BG] 
Per ognuno dei 2 blocchi, i primi 3 bit sono per il colore ed 
il bit 4 per l'intensita', ottenendo di fatto 16 colori totali.
Su alcuni device VGA il bit 4 del BG viene implementato con il
blinking. 

      BG             FG
  ==========     ==========
  7  6  5  4     3  2  1  0 
  |  -------     |  ------- foreground
  |     |        '--------- foreground intensity (bright foreground)
  |     |
  |     '------------------ backbround color
  '------------------------ background intensity o blinking


Di seguito la lista di colori risultante, valida per BG e FG : 

  -------+--------+---------------------------------
  Codice | Codice | Alias           | Descrizione
  -------+--------+---------------------------------
       0 |      0 | BLACK           | nero
       1 |      1 | BLUE            | blu
       2 |      2 | GREEN           | verde
       3 |      3 | CYAN            | celeste [?] 
       4 |      4 | RED             | rosso
       5 |      5 | MAGENDA         | magenda [?]
       6 |      6 | BROWN           | marrone / giallo scuro
       7 |      7 | GREY_LIGHT      | grigio chiaro 
         |        |
       8 |      8 | GREY_DARK       | grigio scuro
       9 |      9 | BLUE_LIGHT      | blu chiaro
      10 |      A | GREEN_LIGHT     | verde chiaro
      11 |      B | CYAN_LIGHT      | ciano chiaro
      12 |      C | RED_LIGHT       | rosso chiaro
      13 |      D | MAGENDA_LIGHT   | magenda
      14 |      E | YELLOW          | giallo
      15 |      F | WHITE           | bianco brillante (o blinking BG)         
  -------+--------+-----------------+---------------

Ad esempio :

  CARATTERE           = 'A'
  ATTRIBUTO_CARATTERE = 0 | 5

corrispondera' ad un carattere A rosso su sfondo nero.
  
*/ 

#define VGA_COLOR_BLACK           0   
#define VGA_COLOR_BLUE            1
#define VGA_COLOR_GREEN           2
#define VGA_COLOR_CYAN            3
#define VGA_COLOR_RED             4
#define VGA_COLOR_MAGENDA         5  
#define VGA_COLOR_BROWN           6   
#define VGA_COLOR_GREY_LIGHT      7   
#define VGA_COLOR_GREY_DARK       8   
#define VGA_COLOR_BLUE_LIGHT      9   
#define VGA_COLOR_GREEN_LIGHT     10  
#define VGA_COLOR_CYAN_LIGHT      11   
#define VGA_COLOR_RED_LIGHT       12   
#define VGA_COLOR_MAGENDA_LIGHT   13   
#define VGA_COLOR_YELLOW          14   
#define VGA_COLOR_WHITE           15   


/* ------------------------ utility di conversione  -----------------------
Rientrano in questa classe di funzione tutte quelle di conversione 
di qualche dimensione dal formato VGA a quello applicativo o viceversa.
Ad esempio : "coordinata cella video"<->offset o dei colori di FG/BG 
nel formato attributo VGA in cui entrambi sono vanno scritti in un unico 
byte, in cui la ognuno dei 2 colori occupa 4bit. */ 

/*
Funzione che trasforma una coordinata video in offset 
nel buffer VGA */
int vga_coordinate2offset ( int x, int y );

/* 
Struttura di ritorno della funzione vga_offset2coordinate */ 
typedef struct {
   int x ;
   int y ;
} tcoordinate; 

/* 
Funzione che trasforma un Offset VGA nelle corrispondenti
coordinate video (80x25). Ritorna la struttura tcoordinate */
tcoordinate vga_offset2coordinate ( int coordinate ) ;

/*
Struttura di ritorno della funzione vga_attribute2color */
typedef struct {
   unsigned char font_color_background ;
   unsigned char font_color_foreground ;
} tcolor ; 

/*
Converte l'attributo del carattere nel buffer
vga nei due campi colore: background e foreground */
tcolor vga_attribute2color(unsigned char attribute);

/*
Converte i colori: background e foreground in
un unico byte: background color nel semibyte 
alto e foreground color nel byte basso. */ 
unsigned char vga_color2attribute(unsigned char font_color_background, unsigned char font_color_foreground);


/* 
Funzione che stampa un carattere nel buffer VGA. Ha il 
medesimo prototipo della putchar ANSI di libc, al momento
cioe' non permette il passaggio ne dell'attributo,
ne tatomeno dell'Offset  */
int vga_putchar ( int c );

/*
Libera l'ultima riga del buffer VGA posizionandosi con
l'offset al primo byte della seconda riga, e poi copiando
carattere per carattere da quella posizione all'ultima,
alla riga precedente e nella medesima posizione. */
void vga_video_scroll();


/* ---------------------------- console ---------------------------
La console virtuale e' una struttura applicativa che mantiene 
alcune impostazioni aggiornate, che altre API VGA utilizzeranno.
Le informazioni trattate sono : la "posizione attuale" del cursore 
applicativo che ad esempio utilizzera la vga_putchar(), che per 
aderenza ad altre API di libc, accodano il carattere da stampare, 
e a cui non viene passata la posizione. Altra informazione che 
mantiene e' ad esempio il colore (di background e foreground) 
da impostare di default, sempre per il medesimo motivo 
dichiarato precedentemente. In futuro potrebbe contenere altre
informazione. Il campo *buffer al momento non e' utilizzato, e 
forse verra' eliminato, se risultera' utile conterra' una copia 
del buffer vga, e potrebbe essere utilizzato come area di appoggio
per manipolazioni complesse a piu' passaggi prima di essere
copiato nel buffer reale vga. I metodi previsti in questa 
classe servono per inizializzare la struttura console,
o aggiornare/leggere singoli attributi  */ 

/*
Struttura Console (80x25), per la posizione del cursore
(x e y), ed il contenuto del buffer (4k) */
typedef struct {
      int x ;
      int y ;
      char *buffer ;
      unsigned char font_color_background ;
      unsigned char font_color_foreground ;
} tConsole;

/*
Funzione che inizializza la struttura console, perche'
l'inizializzazione di x ed y a zero, non e' garantita,
ne dal kernel e ne dal boot loader */
void vga_console_init();

/*
Valorizza il colore di default di foreground e background del carattere.
I prossimi caratteri stampati utilizzerano questi valori */ 
void vga_console_setcolor (unsigned char font_color_background, unsigned char font_color_foreground);

/* 
Posizione il cursore della console a specifiche coordinate passate.
Va quindi a settare console.x e console.y */
void vga_console_setposition (int x, int y);


/* --------------------------- cell/font --------------------------
La classe cell/font (consideriamoli sinonimi per il momento) sono
quella serie di metodi utili per cambiare --ma direttamente 
nel buffer VGA-- gli attributi o il valore della singola cella
video, quindi la stampa di un carattere o il setteggio del colore
(background/foreground). Anche la funzionalita' di scrolling 
al momento rientra in questa categoria anche se non e' 
collegata alla singola cella. */   

/*
Legge per una cella video i colori di background e foreground
di una cella specificata dalla sue coordinate video. */
tcolor vga_font_getcolor (int x, int y);  

/*
Valorizza il colore di foreground e background del carattere, direttamente nel buffer VGA. */
void vga_font_setcolor ( unsigned char font_color_background, unsigned char font_color_foreground, int x, int y ); 

/*
Funzione che stampa un carattere nel buffer VGA. Ha il
medesimo prototipo della putchar ANSI di libc, al momento
cioe' non permette il passaggio ne dell'attributo,
ne tatomeno dell'Offset  */
int vga_putchar ( int c );

/*
Libera l'ultima riga del buffer VGA posizionandosi con
l'offset al primo byte della seconda riga, e poi copiando
carattere per carattere da quella posizione all'ultima,
alla riga precedente e nella medesima posizione. */
void vga_video_scroll();


/* ----------------------------- cursor ---------------------------
Rientrano in questa classe, quei metodi legati al cursore hardware
di VGA. Questo ha senso esclusivamente per la modalita' testuale
80x25. Un cursore hardware acquisisce il colore di foreground         
dell'attributo carattere, e deve essere presente un carattere
in quella cella realmente, anche il blank va bene, ma non caratteri
non editabili molto probabilmente, perche' in tal caso il cursore 
non e' apparso.  */
 
/*
abilita il cursore hardware, definendo la sua forma */
void vga_cursor_enable (unsigned char start, unsigned char end);

/*
definisce la posizione del cursore hardware */
void vga_cursor_setposition (int x, int y); 


#endif

/* EOF */

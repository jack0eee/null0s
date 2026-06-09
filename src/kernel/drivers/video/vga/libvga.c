#include "libvga.h"

#include "device_io.h"

/*
.---------------------------------------------------------------------.
|                                                                     |
|                                                                     |
|                              driver VGA                             |
|                                                                     |
|  API :                                                              |
|                                                                     |
|  CONSOLE                                                            |
|  vga_console_init()                                console          |
|  vga_console_setcolor (background, foreground)     console          |
| *vga_console_getcolor()                            console          |
|  vga_console_setposition (x, y)                    console          |
| *vga_console_getposition()                         console          |
|                                                                     |
|  UTILITY CONVERSIONE                                                |
|  vga_coordinate2offset (x, y)                                       |
|  vga_offset2coordinate (offset)                                     |
|  vga_attribute2color (attribute)                                    |
|  vga_color2attribute(background,foreground)                         |
|                                                                     |
|  BUFFER HARDWARE/VIRTALIZZATO (offset e attributi)                  |
|  vga_putchar(c)                                    vga | console    |
| *vga_getchar()                                     vga | console    |
|  vga_video_scroll()                                vga              |
|  vga_font_getcolor (x, y)                          vga              |
|  vga_font_setcolor (background, foreground, x, y)  vga              |
|                                                                     |
|  CURSORE HARDWARE                                                   |
|  vga_cursor_setposition (x, y)                     vga              |
|  vga_cursor_enable (start, end)                    vga              |
|  vga_cursor_disable ()                             vga              |
|                                                                     |
'---------------------------------------------------------------------' */

static tConsole console ;

/*
.----------------------------------------------------.
| Inizializzazione della struttura console, perche'  |
| questa non viene garantita ne dal kernel e ne      |
| tantomeno dal bootloader.                          |
'----------------------------------------------------' */
void vga_console_init() {
     console.x = 0 ;
     console.y = 0 ;
     console.buffer = 0 ;
     console.font_color_background =  0 ; 
     console.font_color_foreground = 15 ; 
}

/*
.----------------------------------------------------.
| Converte una coppia di coordinate in               |
| offset considerando come numero di colonna 80      |
| e senza numero massimo di righe.                   | 
'----------------------------------------------------' */
int vga_coordinate2offset ( int x, int y )
{
     return (y * VGA_DIM_X + x) * 2 ;
}

/*
.-----------------------------------------------.
| Converte l'offset nelle cordinate             |
| considerando come numero di colonne 80        |
| e senza numero massimo di righe               |
'-----------------------------------------------'*/ 
tcoordinate vga_offset2coordinate ( int offset )
{
     tcoordinate coordinate ;

     coordinate.x = offset / VGA_DIM_X ;
     coordinate.y = offset % VGA_DIM_X ;  

     return coordinate ;
}

/*
.-----------------------------------------------.
| Converte l'attributo del carattere nel buffer |
| vga nei due campi colore: background e        |
| foreground.                                   |
'-----------------------------------------------'*/
tcolor vga_attribute2color(unsigned char attribute)
{
      /* L'attributo contiene sia il valore del background e
        sia il valore del foreground, in un unico byte.
        [BBBBFFFF]
        Ogni colore occupa 4 bit e puoi contenere
        un valore da 0 ad F (15)

        Esempio
        01011111 (0F: Background = 5 [MAGENTA] e Foreground = 15 [WHITE])

        Per dividerli in campi separati e' necessario effettuare :

        a) Per il background : il mascheramento con f0 e lo shift di 4 bit
           (sia a destra che sinistra, e' uguale), che avra' come effetto
           l'inversione di BG con FG

           0101|1111 background + foreground
           1111|0000 (maschera f0)
           --------
           0101|0000 (azzera il valore del foreground)
            BG   FG

           Il mascheramento azzera la parte da escudere, in questo caso il foreground

           0000|0101 (shift di 4 bit | << 4
            FG   BG

           Risultato finale : Background = 00000101 [5] 

        b) Per il foreground, sara' necessario il solo mascheramento
           questa volta per 0f, per annullare il background
           Il foreground e' gia' nel semi-byte basso, quindi non e'
           necessario l'inversione con lo shift di 4 bite.

           0101|1111 background + foreground
           0000|1111 (maschera 0f)
           ---------
           0000|1111 (azzera il valore del background)
            BG   FG

           Risultato finale : Foreground ? 00001111 [15]
     */

     tcolor color ;

     color.font_color_background = attribute ; 
     color.font_color_background = (color.font_color_background & 0xF0) << 4 ;

     color.font_color_foreground = attribute ;
     color.font_color_foreground = (color.font_color_foreground & 0x0F) ;

     return color ;
}

/*
.-----------------------------------------------.
| Converte i colori: background e foreground in |
| un unico byte: background color nel semibyte  |
| alto e foreground color nel byte basso.       |
'-----------------------------------------------' */
unsigned char vga_color2attribute(unsigned char font_color_background, unsigned char font_color_foreground)
{
     /* Scrive l'attributo colore del carattere alla posizione
        successiva, leggendo i colori da due attributi della console:
        font_color_background e font_color_foreground,
        e li concatena in un unico byte :

        1) Muove i primi 4 byte (1-4) di console.font_color_background,
           nella parte alta del byte attributi (5-8).

           Esempio :

           00001110 (bg)
           11100000 (bg << 4)

        2) Per font_color_foreground il valore (4bit=0-15) e',
           e' gia' posizionato nella parte bassa del byte attributi (1-4)
           quindi non bisogna far nulla.

        3) La concatenazione, tra BG e FG (BG|FG) fornisce un valore di 1 byte
           dalla concatenazione di BG (semi-byte-alto) e di FG (semi-byte-basso)

              font_color_background        font_color_foreground
                     [BBBB0000]                   [0000FFFF]
                           |                            |
                           |                            |
                           '-------> [BBBBFFFF] <-------'
                                      87654321
     */

     return font_color_background << 4 | font_color_foreground ;
}

/*
.-----------------------------------------------.
| vga_putchar | scrive un carattere nell'area   |
| di memoria vga, che parte all'indirizzo       |
| 0xB8000.                                      |
'-----------------------------------------------'*/
int vga_putchar(int c)
{
     volatile char *video = (volatile char*) 0xB8000;

     int offset ;

     /* Va a capo per Carriage Return */
     if (c == '\n') {
        console.x=0;
        console.y++;
     }
     else 
     {
        /* Calcola l'Offset nell'area VGA */
        offset = vga_coordinate2offset (console.x, console.y);

        /* Scrive il carattere in memoria VGA alla posizione offset */
        video[offset]     = c    ;
        video[offset + 1] = vga_color2attribute(console.font_color_background, console.font_color_foreground) ;

        /* Se il cursore non e' ancora a fine riga,
           allora sposta il curso avanti di una posizione
           per il prossimo carattere. In caso contrario
           sposta il cursore alla riga successiva, in prima
           posizione */ 
        if ( console.x < VGA_DIM_X - 1 ) { 
             console.x++;
        }
        else
        {
             console.x = 0;
             console.y++;
        }
     }

     /* effettua lo scroll quando il cursore raggiunge
        la riga VGA_DIM_Y + 1. */
     if ( console.y >= VGA_DIM_Y )
          vga_video_scroll();

     return 0 ;
}

/*
.-----------------------------------------------------------------.
| Libera l'ultima riga del buffer VGA posizionandosi con          |
| l'offset al primo byte della seconda riga, e poi copiando       |
| carattere per carattere da quella posizione all'ultima,         |
| alla riga precedente e nella medesima posizione.                |
'-----------------------------------------------------------------' */ 
void vga_video_scroll()
{
     volatile char *video = (volatile char *)0xB8000;

     /* Determina il primo byte della seconda riga (lunghezza riga) */
     unsigned int offset = VGA_DIM_X * 2 ;

     /* Determina l'ultimo byte del buffer */
     unsigned int offset_fin = VGA_DIM_X*2 * VGA_DIM_Y ;     

     /* dalla seconda riga - sposta ogni byte nella medesima 
        posizione, ma alla riga precedente */ 
     while (offset < offset_fin ) 
     {
            video[offset - VGA_DIM_X*2] = video[offset] ;
            offset++;
     }

     /* sposta l'offset da fine buffer VGA (offset_fin) 
        ad inizio ultima riga (offset_fin - VGA_DIM_X*2)
        impostando lungo la strada nei NULL. Quindi 
        pulisce l'ultima riga, che intanto con lo scroll
        all'insu' si e' liberata. */ 
     while (offset > (offset_fin - VGA_DIM_X*2)) {
       offset-- ;
       video[offset] = '\0' ;
     };
         
     /* Posizione il cursore all'inizio della riga precedente,
        appena liberata dallo scrolling all'insu'. */             
     if ( console.y > 0 ) {
          console.x = 0 ;
          console.y = VGA_DIM_Y - 1; 
     }
}

/*
.---------------------------------------------------------------.
| Imposta i colori di default.                                  |
'---------------------------------------------------------------' */
void vga_console_setcolor (unsigned char font_color_background, unsigned char font_color_foreground)
{
     console.font_color_background = font_color_background ;
     console.font_color_foreground = font_color_foreground ; 
}

/*
.-------------------------------------------------------.
| Imposta la posizione del cursore software             |
'-------------------------------------------------------' */ 
void vga_console_setposition (int x, int y)
{
     console.x = x ;
     console.y = y ;
}

/* 
.----------------------------------------------------.
| Legge gli attributo di una cella                   |
'----------------------------------------------------' */ 
tcolor vga_font_getcolor (int x, int y) 
{
     volatile char *video = (volatile char *)0xB8000;

     tcolor color ;

     int offset = vga_coordinate2offset ( x, y ) ; 

     /*
     spacchetta l'attributo nei due colori, per 
     background e foreground */ 
     return vga_attribute2color( video[offset+1] ) ; 
}

/*
.---------------------------------------------------.
| Setta l'attributo della cella                     |
'---------------------------------------------------' */
void vga_font_setcolor ( unsigned char font_color_background, unsigned char font_color_foreground, int x, int y )
{
     volatile char *video = (volatile char *)0xB8000;

     int offset = vga_coordinate2offset ( x, y ) ;

     video[offset+1] = font_color_background << 4 | font_color_foreground ;
}

/*
.--------------------------------------------.
| Abilita il cursore hardware, impostando    |
| la sua dimensione, pul coprire 16 righe e  |
| gli si puo' indicare riga iniziale finale. |
| Le righe vanno da 0 a 15. Alcuni esempi :  |
| 1) Cursore Pieno : 0-15                    |
| 2) Mezzo cursore alto : 0-7                |
| 3) Mezzo cursore basso : 8-15              |
| 4) Minimo (tipo sottolineatura) : 15-15    |
| ---                                        |
| Si puo' anche nasconderlo con A-20         |
|                                            |
| Piu' in generale :                         |
|                                            |
| Registro 0x0A                              |
| 76543210                                   |
| ||||'--- 0-16 scanline iniziale            |
| |||'---- 0-1  abilita/disabilita cursore   |                                            
| ||'----- ???? riservato                    |
| |'------ ???? riservato                    |
| '------- ???? riservato                    |
|                                            | 
'--------------------------------------------' */
void vga_cursor_enable (unsigned char start, unsigned char end)
{
    device_t *vga_dev ;

    vga_dev->type = DEV_PMIO ;
    vga_dev->port_base = 0;

//  registro 0x0A - descrizione : 
//  scanline iniziale 0-3 
//  scanline disabilitata
//  riservati

//
//  BLOCCHI PRINCIPALI :
//
//    BLOCCO : CRTC (Cathode Ray Tube Controller) : Timing e Cursore
//
//       Timing ???
//
//       Cursore (80x25 Colore)
//
//  Le Porte sono :
//  - 0x3D4 | CRTC Index Register   (Porta Selezione Registro)
//  - 0x3D5 | CRTC Data Register    (Porta Valorizzazione Registro Selezionato)
//
//  I Registri sono :
//  - 0x0A  | Cursor Location HIGH  (Registro del Valore Alto  dell'Offset in cui posizionare il Cursore)
//  - 0x0B  | Cursor Location LOW   (Registro per Valore Basso dell'Offset in cui posizionare il Cursore)
//
//       Cursore (80x25 Monocromatico)
//
//  Le porte sono : 0x3B4/0x3B5 
//
//  BLOCCO Sequencer : Clock e gestione della memoria video [0x3C4, 0x3C5]
//  BLOCCO Graphics Controller : Modalita' grafiche, bit planei [0x3CE, 0x3CF]
//  BLOCCO Attribute Controller : Colori, Palette e Modalita' testo [0x3C0, 0x3C1]
//  BLOCCO DAC (Palette 256 colori) [0x3C6, 0x3C7, 0x3C8, 0x3C9]
//  BLOCCO Misc / STatus [0x3C2, 0x3CC, 0x3CA, 0x3DA]
//
//  CPU invia messaggio diretto ad una porta ed VGA capisce che \xc3\xa8 suo e selo prende
//  Le porte di VGA sono da 0x3B0 a 0x3DF

    device_write ( vga_dev, 0x3D4, 0x0A  ) ;
    device_write ( vga_dev, 0x3D5, (unsigned char)start ) ;

    device_write ( vga_dev, 0x3D4, 0x0B ) ;
    device_write ( vga_dev, 0x3D5, (unsigned char)end ) ;
}

/*
.--------------------------------------------.
| Disabilita il cursore hardware             |
'--------------------------------------------' */
void vga_cursor_disable ()
{
    device_t *vga_dev ;

    vga_dev->type = DEV_PMIO ;
    vga_dev->port_base = 0;

    device_write ( vga_dev, 0x3D4, 0x0A ) ;
    device_write ( vga_dev, 0x3D5, 0x20 ) ;
}

/*
.--------------------------------------------.
| Setta la posizione del cursore hardware    |
'--------------------------------------------' */
void vga_cursor_setposition (int x, int y)
{
    unsigned short int offset = vga_coordinate2offset ( x, y ) ;

    ///////Registri :
    #define VGA_INDEX 0x3D4
    #define VGA_DATA  0x3D5

    device_t *vga_dev ;

    vga_dev->type = DEV_PMIO ;
    vga_dev->port_base = 0;

    device_write ( vga_dev, 0x3D4, 0x0E ) ;
    device_write ( vga_dev, 0x3D5, (unsigned char)offset >> 8 ) ;

    device_write ( vga_dev, 0x3D4, 0x0F ) ;
    device_write ( vga_dev, 0x3D5, (unsigned char)offset & 0xFF ) ;
}


/* :::... EOF */ 



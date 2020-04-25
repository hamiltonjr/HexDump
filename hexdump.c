#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define BUFFSIZE 17
#define LINEWIDTH 16
#define SCREENWIDTH 80

/*********************************************************
 *                      HEXDUMP                          *
 *  This program reads a file and shows each character   *
 *  representation in hexa in an organized format.       *
 *********************************************************/

// prototypes
long size( char* );
void stradj( char* );
void spaces( int );
void print_line( char ch, int sz );
void presentation();

int main( int argc, char** argv ) {

    char *buffer = ( char* )malloc( BUFFSIZE );
    int line, column, little;
    long bytes, lines;
    FILE *fpin;
    char c = 0;

    // check argument (file name)
    if ( 2 != argc ) {
        printf( "Error!\n" );
        exit( EXIT_FAILURE );
    }

    // formatting a line
    bytes = size( argv[1] );
    lines = (long)bytes / LINEWIDTH + 1;
    little = bytes % LINEWIDTH;

    if ( (fpin = fopen(argv[1], "r")) == NULL ) {
        printf( "Error\n" );
        exit( EXIT_FAILURE );
    }

    // printing...
    presentation();

    // show formatted lines
    line = 0;
    column = 0;
    while ( (c = getc(fpin)) != EOF ) {
        if ( 0 == column )
            printf( "%08X  ", 16*line );

        printf( "%02X ", c );
        buffer[ column ] = c;

        if ( LINEWIDTH-1 == column ) {
            column = 0;
            ++line;
            stradj( buffer );
            printf( "|%s|\n", buffer );
        } else
            ++column;
    }

    // at the last line
    buffer[ column ] = '\0';
    spaces( 3*(LINEWIDTH - little) );
    stradj( buffer );
    printf( "|%s|\n", buffer );

    print_line( '-', SCREENWIDTH );
    printf("Space(s)....: %d\n", 50-3*little);
    printf("Byte(s).....: %ld\n", bytes);
    printf("Line(s).....: %ld\n", lines);
    printf("Little(s)...: %d\n", little);
    print_line( '-', SCREENWIDTH );
    printf( "\n" );

    fclose( fpin );
    return EXIT_SUCCESS;
}

/*********************************************************
 *  Calculates file size.                                *
 *********************************************************/
long size( char *file ) {
    FILE *fp;
    long bytes;

    if ( (fp = fopen(file, "r")) == NULL ) {
        printf( "Error\n" );
        exit( EXIT_FAILURE );
    }

    fseek( fp, 0, SEEK_END );
    bytes = ftell( fp );
    fclose( fp );
    return bytes;
}

/*********************************************************
 * Adjusts string content. If contenxt is non-peintable, *
 * it is changed by a period.                            *
 *********************************************************/
void stradj( char* s ) {
    for ( unsigned int i=0; s[i]!='\0'; ++i )
        if ( s[ i ]<32 )
            s[ i ] = '.';
}

/*********************************************************
 *  Prints a number of spaces for formatting.            *
 *********************************************************/
void spaces( int x ) {
    for ( unsigned int i=0; i<x; ++i )
        printf( " " );
}

/*********************************************************
 *  Prints a line for formatting (decoration)            *
 *********************************************************/
void print_line( char ch, int sz ) {
    for ( unsigned int i=0; i<sz; ++i )
        printf( "%c", ch );
    printf( "\n" );
}

/*********************************************************
 *  Prints a presentation                                *
 *********************************************************/
void presentation() {
    printf( "\n" );
    print_line( '-', SCREENWIDTH );
    printf( "   HEXDUMP cross-platform - version 1.0.1 release 25/04/2020. Have fun!\n" );
    printf( "   Powered by RobotoLab. This is free software; see the source for copying \n" );
    printf( "   conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS\n" );
    printf( "   FOR A PARTICULAR PURPOSE.\n" );
    print_line( '-', SCREENWIDTH );
}

// 開發平台     : Windows XP
// 使用開發環境 : Dev-C++ 4.9.9.2

// 說明你的程式設計(功能，流程，使用的data structure)：
// ====================Funtion==================== 
// 


#include <cstdlib>
#include <iostream.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

typedef char Name[20] ;

int tnum ;
int ttnum ;

struct God {
       string name ;
       string code ;
       int f ; // frequen
} ;

struct Total {
       string name ;
       int belong[200]  ;
       int nbelong ;
       int f ; // frequen
} ;

typedef God Kami[200] ;
typedef Total total[200] ;

Kami huff = {} ;
total thuff = {} ;

bool check ( int a, int b ) {
     if ( thuff[a].f > thuff[b].f ) return true ;
     else if ( thuff[a].f == thuff[b].f && thuff[a].name > thuff[b].name ) return true ;
     else if ( thuff[a].f == thuff[b].f && thuff[a].name < thuff[b].name ) return false ;
     else return false ;
} //

void Find( int &a, int &b )
{
     a = 0 ;
     b = 1 ;
     for ( int i = 2 ; i < ttnum ; i++ )
     {
         if ( check ( a, i ) || ( check ( b, i ) ) ) {
              if ( ( check ( a, b ) ) ) a = i ;
              else b = i ;
         }
         
     }
}

int search ( int a ) {
    for ( int i = 0 ; i != tnum ; i++ )
    {
        if ( ( thuff[a].name == huff[i].name ) ) return i ;
    }
}

void reset ( int a, int b, int c )
{
     thuff[b].f = c ;

     if ( thuff[a].nbelong == 0 && thuff[b].nbelong == 0 ) {
        thuff[b].belong[thuff[b].nbelong] = search ( a ) ;
        thuff[b].nbelong++ ;
        thuff[b].belong[thuff[b].nbelong] = search ( b ) ;
        thuff[b].nbelong++ ;
     }
     else if ( thuff[a].nbelong == 0 && thuff[b].nbelong != 0 ) {
        thuff[b].belong[thuff[b].nbelong] = search ( a ) ;
        thuff[b].nbelong++ ;
     }
     else if ( thuff[a].nbelong > 0 && thuff[b].nbelong == 0 ) {
        for ( int i = 0 ; i < thuff[a].nbelong ; i++ ) {
            thuff[b].belong[thuff[b].nbelong] = thuff[a].belong[i] ;
            thuff[b].nbelong++ ;
        } 
        thuff[b].belong[thuff[b].nbelong] = search ( b ) ;
        thuff[b].nbelong++ ;
     }
     else if ( thuff[a].nbelong > 0 && thuff[b].nbelong != 0 ) {
        for ( int i = 0 ; i < thuff[a].nbelong ; i++ ) {
            thuff[b].belong[thuff[b].nbelong] = thuff[a].belong[i] ;
            thuff[b].nbelong++ ;
        }
        
     }
     
     for ( int i = a ; i != ttnum-1 ; i++ ) {         
         thuff[i].name = thuff[i+1].name ;
         thuff[i].nbelong = thuff[i+1].nbelong ;
         thuff[i].f = thuff[i+1].f ;
         for ( int j = 0 ; j != thuff[i+1].nbelong ; j++ ) thuff[i].belong[j] = thuff[i+1].belong[j] ;      
     }
     
     ttnum-- ;
     
} //

void add ( int w, int x )
{
     if ( thuff[w].nbelong > 0 ) {
     for ( int i = 0 ; i < thuff[w].nbelong ; i++ )
     {
         if ( x == 1 ) huff[thuff[w].belong[i]].code = "1" + huff[thuff[w].belong[i]].code ;
         else if ( x == 0 ) huff[thuff[w].belong[i]].code = "0" + huff[thuff[w].belong[i]].code ;
     }
     }
     else {
         if ( x == 1 ) huff[search(w)].code = "1" + huff[search(w)].code ;
         else if ( x == 0 ) huff[search(w)].code = "0" + huff[search(w)].code ;   
     }
}

void Godway()
{
     int a, b ;
     int c ;
     while ( ttnum > 1 ) {
           Find ( a, b ) ;
           
           if ( check ( a, b ) ) {
              add ( a , 1 ) ;
              add ( b , 0 ) ;
           }
           else {
                add ( b , 1 ) ;
                add ( a , 0 ) ;
           }
           
           
           c = thuff[a].f + thuff[b].f ;
           
           reset ( a, b, c ) ;

     } //
     
} //

//=============================== Main ===================================

int main(int argc, char *argv[])

{
    // ===============[read&write]================
    /*
    Name InNameOfFile ;
    Name OutNameOfFile ;
    cout << "Pleade enter the filename\n" ;
    cin >> InNameOfFile ;
    strcpy ( OutNameOfFile, InNameOfFile ) ;
    strcat ( OutNameOfFile, ".out" ) ;
    ofstream fout( OutNameOfFile );
    ifstream fin( InNameOfFile );
    */
    // =======================================
    
    cin >> tnum ;
    ttnum = tnum ;
    string temps ;
    int tempi ;
    
    for ( int i = 0 ; i != tnum ; i++ )
    {
        cin >> huff[i].name >> huff[i].f ;
    }


    for ( int i = 0 ; i != tnum ; i++ )
    {
        thuff[i].name = huff[i].name ;
        thuff[i].f = huff[i].f ;
    }
    
    
    Godway() ;
    
    
    
    for ( int i = 0 ; i != tnum-1 ; i++ )
    {
         for ( int j = 0 ; j != tnum-1-i ; j++ )
         {
             if ( huff[j].name > huff[j+1].name )
             {   
                 
                  tempi = huff[j].f ;
                  huff[j].f = huff[j+1].f ;
                  huff[j+1].f = tempi ;
                  
                  temps = huff[j].name ;
                  huff[j].name = huff[j+1].name ;
                  huff[j+1].name = temps ;
                  
                  temps = huff[j].code ;
                  huff[j].code = huff[j+1].code ;
                  huff[j+1].code = temps ;
             }
         }
    }
    
    cout <<   " ┌──────┬──────┐\n │" ;
    cout.width(12);
    cout.setf(std::ios::left, std::ios::adjustfield);
    cout << " Char" ;
    cout << "│" ;
    cout.width(12);
    cout.setf(std::ios::left, std::ios::adjustfield);
    cout << "Code" ;
    cout << "│\n ├──────┼──────┤\n" ;
    
    for ( int i = 0 ; i != tnum ; i++ )
    {

        cout << " │" ;
        cout.width(12);
        cout.setf(std::ios::left, std::ios::adjustfield);
        cout << huff[i].name ;
        cout << "│" ;
        cout.width(12);
        cout.setf(std::ios::left, std::ios::adjustfield);
        cout << huff[i].code ;
        cout << "│\n" ;
        if ( i != tnum-1 ) cout << " ├──────┼──────┤\n" ;
    }
    cout <<   " └──────┬──────┘\n │" ;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}


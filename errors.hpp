#ifndef ERRORS_H
#define ERRORS_H
#include<iostream>
//all functions in error class are inline any memmber function in a class is inline implicetly 
// inline functions are not under odr 
    class Errors {
        public :
        static void fatal (std :: string message ){
            std :: cerr <<"ERROR : "<<message <<"\n";
            std ::exit (EXIT_FAILURE);
        }
        static void dBug(std :: string message){
            std :: cout <<"Dbugging Message : "<<message<<"\n";
        }
        static void warning (std :: string msg ){
            std :: cout <<"Warning message : "<<msg<<"\n";
        }   
    };
#endif
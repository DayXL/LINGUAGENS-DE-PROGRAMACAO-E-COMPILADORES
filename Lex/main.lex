%{ 
    #include <stdio.h> 
    #include <string.h> 
    #include "calc.tab.h"
    void yyerror(char *);
%} 
  
%% 
\+ {return add;}

- {return sub;}

\* {return mul;}

\/ {return divi;}

([0-9])+ {yylval = atoi(yytext); return num;}

[\n] ;
[\tab] ;
= {return igual;}

. yyerror("Caractere inválido");
%% 
  
int yywrap(void){
    return 1;
} 
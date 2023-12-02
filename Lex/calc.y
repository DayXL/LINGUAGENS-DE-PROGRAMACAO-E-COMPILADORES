%{
 #include <stdio.h>
 #include <stdlib.h>
 void yyerror(char *);
 int yylex(void);
 int vet[20];
%}

%token num add sub igual
%left add sub

%%

inicio: exp igual
    { printf("%d\n", $1); exit(1);}
    ;

exp: 
    exp add exp { $$ = $1 + $3; }
    | exp sub exp { $$ = $1 - $3; }
    | sub exp { $$ = -$2; }
    | num
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}

int main(void) {
    yyparse();
}
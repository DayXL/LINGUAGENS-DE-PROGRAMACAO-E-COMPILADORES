%{
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(char *);
    int yylex(void);
%}

%token num add sub mul divi igual
%left add sub 
%left divi mul

%%

inicio: exp igual
    { printf("%d\n", $1); exit(1);}
    ;

exp: 
    exp add exp { $$ = $1 + $3; }
    | exp sub exp { $$ = $1 - $3; }
    | exp mul exp { $$ = $1 * $3; }
    | exp divi exp { $$ = $1 / $3; }
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
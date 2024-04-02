%option noyywrap
%option nodefault

%{
    FILE *outfile;
    int chars = 0;
    int words = 0;
    int lines = 0;
    int singleComments = 0;
    int multiComments = 0;
    int fors = 0;
    int dos = 0;
    int whiles = 0;
%}

%x COMMENT

%%

\/\/.*                          { singleComments++; fprintf(outfile, "%s", yytext); }
"/*"                            { BEGIN(COMMENT); fprintf(outfile, "/*"); /* multiline comment approach taken from flex & bison book */}
<COMMENT>"*/"                   { BEGIN(INITIAL); multiComments++; fprintf(outfile, "*/"); }
<COMMENT>.                      { fprintf(outfile, "%s", yytext); }
<COMMENT>\n                     { fprintf(outfile, "%s", yytext); }
"for"[ \n\t\r\f\v]*"("          { words++; chars += strlen(yylex); fors++; fprintf(outfile, "for ("); /* do increase word count for keywords */ }
"do"[ \n\t\r\f\v]*"{"           { words++; chars += strlen(yylex); dos++; fprintf(outfile, "do {"); /* extra spaces are manually replaced here */ }
"while"[ \n\t\r\f\v]*"("        { words++; chars += strlen(yylex); whiles++; fprintf(outfile, "while ("); }
[a-zA-Z0-9]+                    { words++; chars += strlen(yylex); fprintf(outfile, "%s", yytext); }
[\t\r\f\v]+                     { chars += strlen(yylex); fprintf(outfile, "%s", yytext); }
[ ]+                            { chars += strlen(yylex) /* char count is of unmodified input */; fprintf(outfile, " "); } 
\n                              { chars++; lines++; fprintf(outfile, "%s", yytext); }
.                               { chars++; fprintf(outfile, "%s", yytext); }

%%

/* main function taken from flex & bison book */
main(int argc, char **argv)
{
    outfile = fopen("problem4output.txt", "w");
    int i;
    int totlines = 0;
    int totwords = 0;
    int totchars = 0;
    int totsingleComments = 0;
    int totmultiComments = 0;
    int totfors = 0;
    int totdos = 0;
    int totwhiles = 0;
    printf("     Lines    Words  Chars Single Comments    Multi Comments    Fors    Whiles    Dos\n");
    
    if(argc < 2) { /* just read stdin */
        yylex();
        printf("%8d%8d%8d%12d%17d%13d%8d%10d\n", lines, words, chars, singleComments, multiComments, fors, whiles, dos);
        return 0;
    }
    for(i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if(!f) {
            perror(argv[i]);
            return (1);
        }
        yyrestart(f);
        yylex();
        fclose(f);
        printf("%8d%8d%8d%12d%17d%13d%8d%10d %s\n", lines, words, chars, singleComments, multiComments, fors, whiles, dos, argv[i]);
        totchars += chars; chars = 0;
        totwords += words; words = 0;
        totlines += lines; lines = 0;
        totsingleComments += singleComments; singleComments = 0;
        totmultiComments += multiComments; multiComments = 0;
        totfors += fors; fors = 0;
        totdos += dos; dos = 0;
        totwhiles += whiles; whiles = 0;

    }
    if(argc > 1) /* print total if more than one file */
    printf("%8d%8d%8d%12d%17d%13d%8d%10d total\n", totlines, totwords, totchars, totsingleComments, totmultiComments, totfors, totwhiles, totdos);
    return 0;
}

#include <stdio.h>
#define and &&
#define or ||

int main(){
    FILE *input, *output;
    char sym, tmp_sym;
    int counter = 0;
    input = fopen("../laba7tests/test (7).c", "rt");
    output = fopen("../laba7tests/test (7).wc", "wt");
    while (!feof(input)){
        sym = fgetc(input);
        counter = 0;
        if (sym == '"'){
            fputc('o', output);
            do{
                fputc(sym, output);
                tmp_sym = sym;
                if (sym == '\\') counter++;
                else { counter = 0; }
                sym = fgetc(input);
            } while(!feof(input) and (sym != '\n' or counter % 2 or tmp_sym == 13) and (sym != '"' or counter % 2));
            fputc('c', output);
            printf("---%c %c----\n", tmp_sym, sym);
        }
        else if (sym == '\''){
            do{
                fputc(sym, output);
                if (sym == 92) counter++;
                else { counter = 0; }
                sym = fgetc(input);
            } while(!feof(input) and (sym != '\n' or counter % 2 or tmp_sym == 13) and (sym != '\'' or counter % 2));
        }
        else{
            if (sym == '/'){
                sym = fgetc(input);
                if (sym == '/'){
                    do{
                        if (sym == '\\') counter++;
                        else{ counter = 0; }
                        sym = fgetc(input);
                    }while(!(sym == '\n' and !counter) and !feof(input));
                    fputc('\n', output);
                    continue;
                }
                else if(sym == '*'){
                    tmp_sym = fgetc(input);
                    do{
                        sym = tmp_sym;
                        tmp_sym = fgetc(input);
                    }while((tmp_sym != '/' or sym != '*') and !feof(input));
                    continue;
                }
                else if(sym == '"'){
                    fputc('/', output);
                    do{
                        fputc(sym, output);
                        tmp_sym = sym;
                        if (sym == '\\') counter++;
                        else{ counter = 0; }
                        sym = fgetc(input);
                    } while(!feof(input) and (sym != '\n' or counter % 2 or tmp_sym == 13) and (sym != '"' or counter % 2));
                }
                else if(sym == '\''){
                    fputc('/', output);
                    do{
                        fputc(sym, output);
                        tmp_sym = sym;
                        if (sym == '\\') counter++;
                        else { counter = 0; }
                        sym = fgetc(input);
                    } while(!feof(input) and (sym != '\n' or counter % 2 or tmp_sym == 13) and (sym != '\'' or counter % 2));
                }
                else {
                    fputc('/', output);
                }
            }
        }
        if(!feof(input)) fputc(sym, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}
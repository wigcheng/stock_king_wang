#include <stdio.h>
#include <stdlib.h>
#include "minicsv.h"


static char code[32]={0};

static void
display_cols(char * const * const cols, const size_t cols_count)
{

    size_t i = (size_t) 0U;
	char code_str[8]={0};
	sprintf(code_str,"%s",code);

    while (i < cols_count) {
        if (i != (size_t) 0U) {
            putchar('\t');
        }
		if(i==0){
			if(strcmp(code_str,cols[i])!=0){
				break;
			}
		}
		printf("%s", cols[i]);
		i++;
    }
    //putchar('\n');
}

int
main(int argc, char *argv[])
{
	
    char  *cols[10];
    char  *r;
    size_t cols_count;
	int recordcnt=0;
	char tmp[512]={0x0};
	FILE *in=fopen(argv[1],"r");
	
	if(in==NULL)
	{
		perror("File open error");
		return 1;
	}

	sprintf(code,"%s",argv[2]);
	
	while(fgets(tmp,sizeof(tmp),in)!=0) /* read a record */
	{
		int i=0;
		recordcnt++;
		//printf("Record number: %d\n",recordcnt);

		r = minicsv_parse_line(tmp, cols, &cols_count, sizeof cols / sizeof cols[0]);
		display_cols(cols, cols_count);

		//r = minicsv_parse_line(tmp, cols, &cols_count, sizeof cols / sizeof cols[0]);
		//display_cols(cols, cols_count);

		//printf("Remainder: [%s]\n", tmp);
	}

	fclose(in);

    return 0;
}

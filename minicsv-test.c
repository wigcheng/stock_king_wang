
#include <stdio.h>

#include "minicsv.h"

static void
display_cols(char * const * const cols, const size_t cols_count)
{
    size_t i = (size_t) 0U;

    while (i < cols_count) {
        if (i != (size_t) 0U) {
            putchar('\t');
        }
        printf("[%s]", cols[i]);
        i++;
    }
    putchar('\n');
}

int
main(int argc, char *argv[])
{
    char  *cols[10];
    char   buf[] = "first,line,has,\"comas,\"\"escaped\"\" characters\",and,\"multiples\r\nlines\"\r\n"
        "second,line,\"has\",,empty,,,,columns\r\nremainder";
    char  *r = buf;
    size_t cols_count;
	int recordcnt=0;
	char tmp[1024]={0x0};
	FILE *in=fopen(argv[1],"r");
	
	printf("test chinese =%s\n","測");

	if(in==NULL)
	{
		perror("File open error");
		return 1;
	}
	while(fgets(tmp,sizeof(tmp),in)!=0) /* read a record */
	{
		int i=0;
		recordcnt++;
		printf("Record number: %d\n",recordcnt);

		r = minicsv_parse_line(tmp, cols, &cols_count, sizeof cols / sizeof cols[0]);
		display_cols(cols, cols_count);

		r = minicsv_parse_line(tmp, cols, &cols_count, sizeof cols / sizeof cols[0]);
		display_cols(cols, cols_count);

		printf("Remainder: [%s]\n", tmp);
	}

	fclose(in);

    return 0;
}

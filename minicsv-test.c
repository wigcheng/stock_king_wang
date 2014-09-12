#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minicsv.h"


static char code[32]={0};
static unsigned char price_cnt=0;

static void display_cols(char * const * const cols, const size_t cols_count,char* type);
static void help_func(void);



static void
display_cols(char * const * const cols, const size_t cols_count, char* type)
{
	size_t i = (size_t) 0U;
	char code_str[8]={0};
	sprintf(code_str,"%s",code);


	while (i < cols_count) {
		if (i != (size_t) 0U) {
			putchar('\t');
		}
	
		if(strcmp(type,"-s")==0)
		{
			if(i==0)
			{
				if(strcmp(code_str,cols[i])!=0)
				{
					break;
				}
			}
		}
		else if(strcmp(type,"-p")==0)
		{
			if(price_cnt<2)
			{
				price_cnt+=1;
				break;
			}
		}
		printf("%s", cols[i]);
		i++;
	}

	if(strcmp(type,"-p")==0)
	{
		if(price_cnt>=2)
		{
			putchar('\n');
		}
	}
}

static void
help_func(void)
{
	printf("-h: help list. ex: ./mini -h\n");
	printf("-p: code price research. ex: ./mini -p 20140901 20140911 2349\n");
	printf("-s: 3 people sold research. ex: ./mini -s 20140911.csv 2349\n");
}

int
main(int argc, char *argv[])
{
	
    char  *cols[10];
    char  *r;
    size_t cols_count;
	int recordcnt=0;
	char tmp[1024]={0x0},type[4]={0x0};
	FILE *in=(FILE*)NULL;
	
	sprintf(type,"%s",argv[1]);
	if(strcmp(type,"-h")==0)
	{
		help_func();
		return 0;
	}
	else if(strcmp(type,"-p")==0 || strcmp(type,"-s")==0)
	{
		in=fopen(argv[2],"r");
	
		if(in==NULL)
		{
			perror("File open error");
			return 1;
		}

		if(strcmp(type,"-s")==0)
		{
			sprintf(code,"%s",argv[3]);
		}

		while(fgets(tmp,sizeof(tmp),in)!=0) /* read a record */
		{
			int i=0;
			recordcnt++;
			//printf("Record number: %d\n",recordcnt);

			r = minicsv_parse_line(tmp, cols, &cols_count, sizeof cols / sizeof cols[0]);
			display_cols(cols, cols_count,type);

			//r = minicsv_parse_line(tmp, cols, &cols_count, sizeof cols / sizeof cols[0]);
			//display_cols(cols, cols_count);

			//printf("Remainder: [%s]\n", tmp);
		}

		fclose(in);
	}
	else
	{
		printf("error input\n");
		return 1;
	}

    return 0;
}

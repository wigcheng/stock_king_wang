#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minicsv.h"


typedef enum{
	waitsu=0,
	toshin,
    tsuyinshan,
}SOLD_MODE;

static char code[16]={0};
static unsigned char price_cnt=0;
static SOLD_MODE stock_mode;

static int display_cols(char * const * const cols, const size_t cols_count);
static void help_func(void);



static int
display_cols(char * const * const cols, const size_t cols_count)
{
	size_t i = (size_t) 0U;
	char code_str[16]={0};
	int ret=0,check_val;

	check_val=(stock_mode==tsuyinshan)? 0:1;

	sprintf(code_str,"%s",code);

	while (i < cols_count)
	{
		if(i==check_val)
		{
			if(strcmp(code_str,cols[i])!=0)
				return 0;
			else
				ret=1;
		}
		
		if(ret==1)
		{
			if(stock_mode==tsuyinshan)
			{
				if(i<2 || i>7)
					printf("%s\t", cols[i]);
			}
			else
			{
				printf("%s\t", cols[i]);
			}
		}

		i++;
	}

	//putchar('\n');
	return ret;
}

static void
help_func(void)
{
	printf("-h: help list. ex: ./mini -h\n");
	printf("-p: code price research. ex: ./mini -p 201409_2349.csv 2014/09/11\n");
	printf("-toshin: 3 people sold search. ex: ./mini -toshin 20140911.csv 2349\n");
	printf("-waitsu: 3 people sold search. ex: ./mini -waitsu  20140911.csv 2349\n");
	printf("-tsuyinshan: 3 people sold search. ex: ./mini -tsuyinshan 20140911.csv 2349\n");


}

int
main(int argc, char *argv[])
{
	
    char  *cols[20];
    char  *r;
    size_t cols_count;
	int recordcnt=0;
	int scan_tmp1,scan_tmp2,scan_tmp3;
	char tmp[1024]={0x0},type[16]={0x0};
	FILE *in=(FILE*)NULL;

	sprintf(type,"%s",argv[1]);

	if(strcmp(type,"-h")==0)
	{
		help_func();
		goto exit;
	}

	in=fopen(argv[2],"r");
	if(in==NULL)
		perror("File open error\n");

	if(strcmp(type,"-toshin")==0 || strcmp(type,"-waitsu")==0   || strcmp(type,"-tsuyinshan")==0 )
	{
		if(strlen(argv[3])==4)
			sprintf(code,"%s  ",argv[3]);
		else
			sprintf(code,"%s",argv[3]);

		if(strcmp(type,"-toshin")==0)
			stock_mode=toshin;
		else if(strcmp(type,"-waitsu")==0)
			stock_mode=waitsu;
		else if(strcmp(type,"-tsuyinshan")==0)
			stock_mode=tsuyinshan;
	}
	else if(strcmp(type,"-p")==0)
	{
		sscanf(argv[3],"%04d/%02d/%02d",&scan_tmp1,&scan_tmp2,&scan_tmp3);
		scan_tmp1-=1911;
		sprintf(code," %d/%02d/%02d",scan_tmp1,scan_tmp2,scan_tmp3);
	}
	else
	{
		printf("error input\n");
		goto exit;
	}

	while(fgets(tmp,sizeof(tmp),in)!=0) /* read a record */
	{
		int i=0;
		recordcnt++;

		r = minicsv_parse_line(tmp, cols, &cols_count, sizeof cols / sizeof cols[0]);
		if(display_cols(cols, cols_count)==1)
			break;
	}



exit:
	if(in)	
		fclose(in);

    return 0;
}

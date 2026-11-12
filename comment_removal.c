#include"preprocessor.h"

void remove_comments(FILE *src,FILE *dest){
	int ch,next;
	int in_string=0;
	int in_char=0;

	while((ch=fgetc(src)) != EOF){
		if(ch=='"' && !in_char) {
			in_string=!in_string;
			fputc(ch,dest);
		}
		else if(ch=='\'' && !in_string)
		{
			in_char=!in_char;
			fputc(ch,dest);
		}
		else if(!in_string && !in_char && ch=='/'){
			next=fgetc(src);
			if(next == '/')
            		{
                		while((ch = fgetc(src)) != EOF && ch != '\n');

                			if(ch == '\n')
                    				fputc('\n', dest);
            		}
            		else if(next == '*')
            		{
                		while((ch = fgetc(src)) != EOF)
                		{
                    			if(ch == '\n')
                        			fputc('\n', dest);

                    			if(ch == '*')
                    			{
                        			next = fgetc(src);

                        			if(next == '/')
                            				break;

                        			if(next != EOF)
                            				ungetc(next, src);
                    			}
                		}
            		}
            		else
            		{
                		fputc(ch, dest);

                		if(next != EOF)
                    			ungetc(next, src);
            		}
        }
        else
        {
            fputc(ch, dest);
        }
    }
}

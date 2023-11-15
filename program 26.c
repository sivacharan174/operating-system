#include <stdio.h>
#include <stdlib.h>
main()
{
	FILE *fp;
	char filename[40], mode[4];

	while (1)
	{
		* Input filename and mode. */
		printf("\nEnter a filename: ");
		gets(filename);
		printf("\nEnter a mode (max 3 characters): ");
		ets(mode);
		/* Try to open the file. */
		if ( (fp = fopen( filename, mode )) != NULL )
		{
			printf("\nSuccessful opening %s in mode %s.\n",
      filename, mode);
			fclose(fp);
			puts("Enter x to exit, any other to continue.");
			if ( (getc(stdin)) == `x')
				break;
			else
				continue;
		}
		else
			fprintf(stderr, "\nError opening file %s in mode %s.\n",filename, mode);
		puts("Enter x to exit, any other to try again.");
		if ( (getc(stdin)) == `x')
			break;
		else
			continue;
	}
	}


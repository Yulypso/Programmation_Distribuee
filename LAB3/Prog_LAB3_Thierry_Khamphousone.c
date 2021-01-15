#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //for open function
#include <unistd.h> //for close function
#include <time.h>
#include <string.h>
#include <pwd.h>

/*Thierry Khamphousone - TC-44*/

int main(int argc, const char* argv[])
{
	struct stat buffer;

	int desc;
	if((desc=open(argv[1], O_RDWR|O_CREAT|O_EXCL, 0400)) < 0)
		perror("open error");
	else
	{
/*****GET Current time*****/
		time_t current_time = time(NULL); 
		struct tm *time_info;

		time(&current_time);
		time_info = localtime(&current_time);
		char* time_xml = asctime(time_info); 
		
		size_t time_xml_len = strlen(time_xml);
		time_xml[strlen(time_xml) - 1] = 0; //on retire le '\n'  

/*****GET uid*****/

		stat(argv[1], &buffer);
		int uid = buffer.st_uid;
		char uid_xml[10]="";
		sprintf(uid_xml, "%d", uid);
		size_t uid_xml_len = strlen(uid_xml);

/*****GET Owner Name*****/
		struct passwd *p = getpwuid(buffer.st_uid);
		char* username_xml = p->pw_name;
		size_t username_xml_len = strlen(username_xml);

/*****GENERATE Password*****/
		srand(time (NULL));
		int ap; char a; char password_xml[10];

		for(int i=0; i<10; i++)
		{
			ap=rand()%10;
			a=ap+'0';
			password_xml[i]=a;
		}

		size_t password_xml_len = strlen(password_xml)-4;

/*****Display XML*****/
		write(desc, "<TK_new_user>\n", 15);

		write(desc, "\t<TK_date>", 10);
		write(desc, time_xml, time_xml_len);
		write(desc, "</TK_date>\n", 11);

		write(desc, "\t<TK_username>", 14);
		write(desc, username_xml, username_xml_len);
		write(desc, "</TK_username>\n", 15);

		write(desc, "\t<TK_uid>", 9);
		write(desc, uid_xml, uid_xml_len);
		write(desc, "</TK_uid>\n", 10);

		write(desc, "\t<TK_password>", 14);
		write(desc, password_xml, password_xml_len);
		write(desc, "</TK_password>\n", 15);

		write(desc, "</TK_new_user>", 14);

		close(desc);
	}
	return 0;
}
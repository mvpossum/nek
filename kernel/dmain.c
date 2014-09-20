#include <sys/logging.h>
#include <stdio.h>
#include <sys/vfs.h>
#include <errno.h>
#include <graphics/video.h>
#include <sys/timer.h>
#include <sys/syscall.h>
#include <sys/task.h>


int start_service(char *daemon,int essential,int (*func)())
{
	if(func()){
		printk("daemon","Starting kernel daemon %s... failed\n",daemon);
		if(essential) panic("Couldn't start required daemon!");
		return 1;
	}
	else printk("daemon","Starting kernel daemon %s... done\n",daemon);
	return 0;
}

void kmain();
void dmain()
{
	printk("ok","Entering Kernel Environment...\n");
	//Start services
	start_service("syscalld",1,init_syscalls);
	//~ start_service("taskd",1,task_init);
	//~ start_service("kvfsd",0,init_vfs);
	start_service("timerd",1,init_timer);
}
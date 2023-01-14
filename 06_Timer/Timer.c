#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>

static struct timer_list mytimer;

static void my_callback(struct timer_list* timmi)
{
	mytimer.expires=timmi->expires+2*HZ;	
	printk("Callback wurde aufgerufen, expires ist %lu\n",timmi->expires);	
	add_timer(&mytimer);
}

static int mod_init(void)
{
	timer_setup(&mytimer,my_callback,0);
	mytimer.expires=jiffies+2*HZ;
	add_timer(&mytimer);
	printk("Timer wurde gestartet, der Wert für HZ ist %d\n",HZ);
	return 0;
}

static void mod_exit(void)
{
	if(timer_pending(&mytimer))
	printk("Timer noch aktiv\n");
	if(del_timer_sync(&mytimer))
		printk("Timer war aktiv, habe beendet!\n");
	else
		printk("War alles ok, reg dich nicht auf!\n");
}


module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");

#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>
#include <linux/delay.h>

static struct task_struct *thread_id;
static wait_queue_head_t  wq;
static DECLARE_COMPLETION(on_exit);

static int thread_code(void *data)
{
	unsigned long timeout;
	int i;
	allow_signal(SIGTERM);
	for (i=0; i<10 && (kthread_should_stop()==0);i++)
	{
		timeout=HZ;
		timeout=wait_event_interruptible_timeout(wq,(false),timeout);
		printk("threat_function: Bin aufgewacht mit Rückgabewert %ld\n",timeout);
		
		if(timeout==-ERESTARTSYS)
		{
			printk("bin unerwartet geweckt worden, ich soll mich wohl beenden\n");
			break;
		}
		
	}
	if(kthread_should_stop()!=0) printk("Soll mich wegen kthread_should_stop beenden\n");
	printk("Bin fertig und beende mich\n");
	complete_and_exit(&on_exit,0);
}

static int __init kthread_init(void)
{
	init_waitqueue_head(&wq);
	thread_id=kthread_create(thread_code,NULL,"mykthread");
	if(thread_id==0)
		return -EIO;
	wake_up_process(thread_id);
	msleep(3000);
	kthread_stop(thread_id);
		return 0;
}
static void __exit kthread_exit(void)
{
	kill_pid(task_pid(thread_id),SIGTERM,1);
	printk("sende SIGTERM %d\n\n",SIGTERM);
	printk("Warte auf Beendigung des Threats\n");
	wait_for_completion(&on_exit);
	printk("Threat beendet\n");
	
}





module_init (kthread_init);
module_exit (kthread_exit);

MODULE_LICENSE("GPL");

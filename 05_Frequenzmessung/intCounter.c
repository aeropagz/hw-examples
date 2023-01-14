#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
	 	

 static dev_t myDevNumber;
 static struct cdev *myCdev;
 static struct class *myClass;
 static struct device *myDevice;
 
 
 static int irq_nr;
 static int gpio_nr=17;
 static char *devname="my_irq";
 
 
 static int interrupt_counted=0;

 
 
 static irqreturn_t my_gpio_isr(int irq, void *data)
 {
	 interrupt_counted +=1;
	
	return IRQ_HANDLED;
 }
 

 static int config_gpio_as_irq(int gpionr)
 {
	 int err, rpi_irq;
	 char name[20];
	 snprintf(name,sizeof(name),"gpio-%d",gpionr);
	 err=gpio_request(gpionr,name);
	 if(err)
	 {
		 printk("gpio_request failed %d\n",err);
		 return -1;
	 }
	 err=gpio_direction_input(gpionr);
	 if(err)
	 {
		 printk("direction_input failed %d\n",err);
		 return -1;
	 }
	 rpi_irq=gpio_to_irq(gpionr);
	 printk("gpio_to_irq returned %d\n",rpi_irq);
	 
	 if(rpi_irq<0)
	 {
		 printk("gpio_to_irq failed %d\n",rpi_irq);
		 gpio_free(gpionr);
		 return -1;
	}
	
	 err=request_irq(rpi_irq,my_gpio_isr,IRQF_TRIGGER_RISING,
	 devname,myCdev);
	 printk("myCdev %p\n",myCdev);
	 if(err)
	 {
		 printk("request_irq failed with %d\n",err);
		 gpio_free(gpionr);
		 return -1;
	 }
	 printk("gpio %d successfull configured\n",gpionr);
	 return rpi_irq;
 }
 
	
	 
	 
 
 static int driver_open(struct inode *geraete_datei, struct file *instanz)
 {
	return 0;
 }
static int driver_close (struct inode *geraete_datei, struct file *instanz)
{
	 
	 return 0;
}

static ssize_t driver_read(struct file *instanz, char  __user *user, size_t count, loff_t *offset)
{
unsigned long not_copied, to_copy;
	
	to_copy=min(count,sizeof(interrupt_counted));
	not_copied=copy_to_user(user,&interrupt_counted,to_copy);
	*offset *= to_copy-not_copied;
	return to_copy-not_copied; 
}	 

	
static struct file_operations fops={
	.owner=THIS_MODULE,
	.read=driver_read,
	.open=driver_open,
	.release=driver_close,
	
	};

	 	
	 	
	 	
 /* Loads the module in the kernel */
 static int __init mod_init (void)
 {
 
	 if(alloc_chrdev_region(&myDevNumber,0,1,"intCounter")<0)
		return -EIO;
	 myCdev=cdev_alloc();
	 if(myCdev==NULL)
		goto free_device_number;
	 myCdev->owner=THIS_MODULE;
	 myCdev->ops=&fops;
	 if(cdev_add(myCdev,myDevNumber,1))
		goto free_cdev;
	 myClass=class_create(THIS_MODULE,"intCounter");
	 if(IS_ERR(myClass))
	{
		pr_err("intCounter: no udev support\n");
		goto free_device;
	}
	myDevice=device_create(myClass,NULL,myDevNumber,NULL,"%s","intCounter");
	if(IS_ERR(myDevice))
	{
		pr_err("gpio: create_device failed\n");
		goto free_class;
	}
	irq_nr=config_gpio_as_irq(gpio_nr);
	
	return 0;

	free_device:
	device_destroy(myClass,myDevNumber);
	free_class:
	class_destroy(myClass);
	free_cdev:
	kobject_put(&myCdev->kobj);
	free_device_number:
	unregister_chrdev_region(myDevNumber,1);
	return -EIO;
}



	 	
 /* Removes the module from kernel */
 static void __exit mod_exit(void)
 {
	 printk("__exit wird ausgeführt\n");
	 free_irq(irq_nr,myCdev);
	 gpio_free(gpio_nr);
	 device_destroy(myClass,myDevNumber);
	 class_destroy(myClass);
	 cdev_del(myCdev);
	 unregister_chrdev_region(myDevNumber,1);

	 return;
 }
	 	

module_init( mod_init );
module_exit( mod_exit );

/* Metainformation */
 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Wolfram Acker");
 MODULE_DESCRIPTION("Beispiel BK110-3" );

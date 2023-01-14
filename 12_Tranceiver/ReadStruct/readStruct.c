#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#include "MyStruct.h"


	 	
 static struct myStruct strus[]={{"Sinus",50,23,{1,2,3,4}},{"Rechteck",15,33,{5,6,7,8,9}},{"Saegezahn",18,12,{10,11,12,13,14,15}}};
 static int index=0;
 
 static dev_t myDevNumber;
 static struct cdev *myCdev;
 static struct class *myClass;
 static struct device *myDevice;
 
 static int my_drv_open(struct inode *geraete_datei, struct file *instanz)
 {
	 dev_info(myDevice,"my_drv_open called\n");
	 return 0;
 }

static int my_drv_close (struct inode *geraete_datei, struct file *instanz)
{
	 dev_info(myDevice,"my_drv_close called\n");
	 return 0;
}

static ssize_t my_drv_read(struct file *instanz, char  __user *user, size_t count, loff_t *offset)
{	int j;
	unsigned long not_copied, to_copy;
	size_t size=sizeof(strus[index]);
	printk("Bytes angefordert %d, moechte senden %d\n",count,size);
	to_copy=min(count,size);
	not_copied=copy_to_user(user,&strus[index],to_copy);
	printk("Nachricht gesendet:%s i:%d  j:%d values:",strus[index].nachricht,strus[index].i,strus[index].j);
	for(j=0;j<20;j++)
		{
			printk(" %d ",strus[index].values[j]);	
		}
	 
	printk(" \n ");
	index=(index+1)%3;
	*offset += to_copy-not_copied;
	return to_copy-not_copied; 
}	
	
static struct file_operations fops={
	.owner=THIS_MODULE,
	.read=my_drv_read,
	.open=my_drv_open,
	.release=my_drv_close,
	};

	 	
 /* Loads the module in the kernel */
 static int __init mod_init (void)
 {
	 printk("init wird ausgeführt\n");
	 if(alloc_chrdev_region(&myDevNumber,0,1,"MessageKiel")<0)
	 return EIO;
	 
	 myCdev=cdev_alloc();
	 if(myCdev==NULL)
	 	 
	 goto free_device_number;
	 
	 myCdev->owner=THIS_MODULE;
	 myCdev->ops=&fops;
	 
	 if(cdev_add(myCdev,myDevNumber,1))
	 goto free_cdev;
	 
	 myClass=class_create(THIS_MODULE,"MessageKiel");
	 if(IS_ERR(myClass))
	 {
		 pr_err("Keine Anmeldung beim Udev\n");
		 goto free_cdev;
	 }
	
	myDevice=device_create(myClass,NULL,myDevNumber,NULL,"%s","MessageKiel");
	
	if(IS_ERR(myDevice))
	{
		pr_err("create_device failed\n");
		goto free_class;
	}
	return 0;

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
 MODULE_AUTHOR("Wolfram Acker>");
 MODULE_DESCRIPTION("Beispiel BK110-2" );

cmd_/home/piuser/Desktop/Examples/09_Kernel_Threads/modules.order := {   echo /home/piuser/Desktop/Examples/09_Kernel_Threads/kthread.ko; :; } | awk '!x[$$0]++' - > /home/piuser/Desktop/Examples/09_Kernel_Threads/modules.order

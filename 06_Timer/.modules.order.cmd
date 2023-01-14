cmd_/home/piuser/Desktop/Examples/06_Timer/modules.order := {   echo /home/piuser/Desktop/Examples/06_Timer/Timer.ko; :; } | awk '!x[$$0]++' - > /home/piuser/Desktop/Examples/06_Timer/modules.order

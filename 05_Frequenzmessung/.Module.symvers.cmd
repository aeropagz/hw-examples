cmd_/home/piuser/Desktop/Examples/05_Frequenzmessung/Module.symvers := sed 's/\.ko$$/\.o/' /home/piuser/Desktop/Examples/05_Frequenzmessung/modules.order | scripts/mod/modpost -m -a  -o /home/piuser/Desktop/Examples/05_Frequenzmessung/Module.symvers -e -i Module.symvers   -T -
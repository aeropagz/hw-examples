cmd_/home/piuser/Desktop/Examples/03_First_Module/Module.symvers := sed 's/\.ko$$/\.o/' /home/piuser/Desktop/Examples/03_First_Module/modules.order | scripts/mod/modpost -m -a  -o /home/piuser/Desktop/Examples/03_First_Module/Module.symvers -e -i Module.symvers   -T -
import xml.etree.ElementTree as ET
import os
import sys
try:
    if len(sys.argv) > 2:
        filename=sys.argv[1]
        filenamePath=sys.argv[2]
        header = """
    <control>
    //default_path=  relative path of your samples
    <global>
    // parameters that affect the whole instrument go here.
    // *****************************************************************************
    // Your mapping starts here
    // *****************************************************************************
    <group>
        """
        tree = ET.parse(filename)
        num = 1
        for gro in tree.iter('group'):
            name = gro.get('name')
            num = num + 1
            f = open(filenamePath + '/' + str(num) + str(name) +'.sfz','wb')
            f.write(header+'\n')
            if gro.get('name') == name:
                for neighbor in gro.iter('sample'):
                    getchi = neighbor.get('path')
                    root = neighbor.get('rootNote')
                    lokey = neighbor.get('loNote')
                    hikey = neighbor.get('hiNote')
                    hivel = neighbor.get('hiVel')
                    lovel = neighbor.get('loVel')

                    if(hivel == None and lovel == None):
                        hivel = 127
                        lovel = 0
                        f.write('<region>' + 'sample='+str(getchi)+' key= '+str(root)+' lokey= '+str(lokey)+' hikey= '+str(hikey)+' pitch_keycenter= '+str(root)+' hivel= '+str(hivel)+' lovel= '+str(lovel) +'\n')
                    else:
                        f.write('<region>' + 'sample=' + str(getchi) + ' key= ' + str(root) + ' lokey= ' + str(lokey) + ' hikey= ' + str(hikey) + ' pitch_keycenter= ' + str(root) + ' hivel= ' + str(hivel) + ' lovel= ' + str(lovel) + '\n')
            
            f.close()
        print('All Done')
        

        
    else:
        print('No file selected..')

except Exception as error:
   error_string = str(error)
   print(error_string)

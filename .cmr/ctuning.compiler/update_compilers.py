# Collective Mind
#
# See cM LICENSE.txt for licensing details.
# See cM Copyright.txt for copyright details.
#
# Developer(s): Grigori Fursin, started on 2011.09

# Misc scripts

import json
import os

px1='.cm'
px2='data.json'
px3=''

# Load array update
try:
   f=file('update_compilers.json')
   au=json.loads(f.read())
   f.close()
except Exception as e:
   print 'Can\'t load json for update'
   exit(1)


dirList=os.listdir('.')
for fn in dirList:
    # Check if startswith
    if fn.startswith(px3):

       # Load config
       p1=os.path.join(fn,px1,px2)

       success=True

       try:
          f=file(p1)
       except Exception as e:
          success=False

       if success:
          try:
             array=json.loads(f.read())
          except Exception as e:
             success=False

          if success:
             f.close()

             print 'Processing '+fn+' ...'

             b=array['all_compiler_flags_desc']
             for x in b:
                 y=b[x]
                 if y.get('desc_text','')!='':
                    z=y.get('default_value','')
                    z1=y.get('explore_prefix','')
                    if z1!='': z=z1

                    b[x]['desc_text']='compiler flag: '+str(z)

             # Writing updated array
             success=True
             try:
                f=file(p1,'w')
                f.write(json.dumps(array, indent=2, sort_keys=True)+'\n')
                f.close()
             except Exception as e:
                success=False

             if not success:
                print 'Failed!'

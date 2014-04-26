# Collective Mind
#
# See cM LICENSE.txt for licensing details.
# See cM Copyright.txt for copyright details.
#
# Developer(s): Grigori Fursin, started on 2011.09

# Misc scripts

import json
import os

# Load array update
try:
   f=file('data.json')
   a=json.loads(f.read())
   f.close()
except Exception as e:
   print 'Can\'t load json for update'
   exit(1)

for x in a['all_compiler_flags_desc']:
    if x!='##base_flag':
#       if 'explore_prefix' in a['all_compiler_flags_desc'][x]:
       a['all_compiler_flags_desc'][x]['forbid_disable_at_random']='no'

try:
   f=file('data1.json','w')
   f.write(json.dumps(a, indent=2, sort_keys=True)+'\n')
   f.close()
except Exception as e:
   print 'Failed!'

#!/usr/bin/env python

# Read the xml interface files and generate some code
#
# Usage: gencreate *.xml > sample.c

import sys
import re
from string import Template

ifaces = []

for file in sys.argv:
    if file.endswith(".xml"):
        f = open(file)
        lines = f.readlines()
        f.close()
        for line in lines:
            m = re.match("\s*<interface\s+name=\"([^\"]+)\"", line)
            if m != None:
                iface = m.group(1)
                m = re.match(".*\.(Operation|Environment|UserInterfaceSettings|Input)\.(\w+)", iface)
                if m != None:
                    cat = m.group(1).lower()
                    short = m.group(2)
                    ifaces.append((cat, short, iface))



for (cat, short, full) in ifaces:
    code = Template('#include "Models/$cat/${short}ModelImpl.h"')
    print code.substitute(cat = cat, short = short)

print
print

for (cat, short, full) in ifaces:
    code = Template("""if (strcmp(cmd->interface, "$full") == 0)
{
    status = Handle${short}Command(cmd, context);
}
else
""")
    print code.substitute(short = short, full = full),
import os
import sys
def Run(Path, oldtype, newtype):
    allFile = os.listdir(Path)
    for file_name in allFile:
        currentdir = os.path.join(Path, file_name)
	if os.path.isdir(currentdir):
	    Run(currentdir, oldtype, newtype)
	fname = os.path.splitext(file_name)[0]
	ftype = os.path.splitext(file_name)[1]
	if oldtype in ftype[1:]:
	    #typecount[0] += 1
	    ftype = ftype.replace(oldtype, newtype)
	    newname = os.path.join(Path, fname + ftype)
	    os.rename(currentdir, newname)
	    #print newname
Run(".","txt", "cpp")

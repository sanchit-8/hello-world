#reseting the seats
from file_manipulation import*
import os
def reset():
    l=['m_v1.txt','m_v2.txt','m_v3.txt','m_v4.txt','m_v5.txt']
    for i in l:
        k=[[]for j in range(9)]
        ref=1
        for lst in k:
            strt=65
            for m in range(1,21):
                lst.append(chr(strt)+str(ref))
                strt+=1
            ref+=1
        writing_file(k,i)
    print "Reset Successfully"

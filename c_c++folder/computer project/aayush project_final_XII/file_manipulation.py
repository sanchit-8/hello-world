import os
def check(q):
    l=[]
    for i in q:
        if i==chr(215):
            m=' '+chr(215)
            l.append(m)
        else:
            l.append(i)
    return l
def writing_file(a,name):
    k=open(name,'r+')
    k.truncate()
    k.close()
    k=open(name,'a')
    for i in a:
        p=''
        for m in i:
            p+=m+' '
        k.write(p+'\n')
    k.close()
    k=open(name,'r')
def reading_file(name):
    name=str(name)
    k=open(name,'r+')
    j=k.readlines()
    k.close()
    k=open(name,'r+')
    l=[]
    for s in j:
        q=s.split()
        q=check(q)
        l.append(q)
    return l


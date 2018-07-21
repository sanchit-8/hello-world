from file_manipulation import*
def updating(a,l,name):           #UPDATING THE GRID
    for check in a:
        for i in l:
            for j in range(len(i)):
                if check==i[j]:
                    i[j]=' '+chr(215)
    writing_file(l,name)
    return l
def star(name,num):                 #PRINTIN STARS
    k=l=0
    for i in range(1):
        for j in range(74):
            if k==0:
                print"         "+'*',
                k+=1
            else:
                print '*',
        print
        k=0
        for i in range(33):
            if k==0:
                print"         "+'*',
                k+=1
            else:
                l+=1
                print '*',
                if l==29:
                    print "<<---"+name+"-->>" ,
                    for k in range(num):
                        print '*',
        print
        k=0
        for i in range(1):
            for j in range(74):
                if k==0:
                    print"         "+'*',
                    k+=1
                else:
                    print '*',
        print
        k=0
            
def line2(m):               #PRINTING LINES
    for i in range(m):
        print '_______________________________________________________________________________________________________________________________________________________________________'
def printing_grid(l,name,num):  #printing the updated seats
    k=1
    n=0
    s=0
    ext=nb=0
    st='*'
    print '                                    !!!..............THE AVAILABLE SEATS FOR',name,'ARE................!!!'
    line2(1)
    print '         __________________________________________________________________________________________________________________________________________________'
    print
    star(name,num)
    for i in l:
        ext+=1
        for j in i:
            n+=1
            s+=1
            if ext==9 or ext==2:
                if nb==0:
                    print "         "+st+"|EXIT|"+"                          "*5+'   '+"|EXIT|"+st
                    nb+=1
            if k==1:
                print '         '+st*6+'  '+'|'+j+'|',
                k=0
           
            elif s==3 or s==4 or s==9 or s==5 or s==10 or s==11 or s==12 or s==13 or s==17 or s==18 or s==19:
                print '|'+j+'|',
            elif n==len(i):
                 print '___',
                 print '|'+j+'|'+'  '+st*6,
            else:
                print '___',
                print '|'+j+'|',
        print
        k+=1
        n=0
        s=0
        nb=0
    star(name,num)
    print '         __________________________________________________________________________________________________________________________________________________'
def grid(m,k,l):            #CINEMA HALL GRID
    for n in range(65,85):
        l[m].append(chr(n)+str(k))
    return l

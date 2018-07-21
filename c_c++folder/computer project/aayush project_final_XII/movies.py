import module                                              #USER_DEFINED MODULE
def listnw(m):
    l=[]
    for i in m:
        for j in i:
           l.append(j)
    return l
def thanks():                                               #GREETING THANKS
    print "                                       !!<<--YOUR SEATS/TICKETS ARE BOOKED-->>!!"
    print "                                                THANK YOU FOR BOOKING"
def welcome():
    print "                                                              SELECT THE SEAT YOU DESIRE"
def mov_1(movie1,seats_unavailable1):           #MOVIE-1
    emp_lst=[]
    flname='m_v1.txt'
    name='STARWARS'
    var=0
    seats_res=[]
    module.line2(1)                                        #using function of module
    print
    NUM=input("ENTER THE NUMBER OF SEATS YOU WANT TO BOOK: ")
    welcome()
    print
    module.printing_grid(movie1,name,32)                   #using function of module
    while var<NUM:
        print
        seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ").upper()
        #paste here
        nwlst=listnw(movie1)
        chk=seat.capitalize() in nwlst
        if chk==True:
                emp_lst.append(seat)
        while chk==False:
            print "INVALID SEAT,PLEASE ENTER AGAIN"
            seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
            #paste here
            chk=seat.capitalize() in nwlst
            if chk==True:
                emp_lst.append(seat)
        if seat not in(seats_unavailable1):
            seats_res.append(seat.capitalize())
            var+=1
        else:
            print "SORRY THIS SEAT IS ALREDY BOOKED"
        seats_unavailable1.append(seat)
    thanks()
    module.line2(1)                                         #using function of module
    movie1=module.updating(seats_res,movie1,flname)         #using function of module
    return movie1,seats_unavailable1,emp_lst
def mov_2(movie2,seats_unavailable2):                       #MOVIE-2
    var=0
    emp_lst=[]
    name='WAZIR'
    flname='m_v2.txt'
    seats_res=[]
    module.line2(1)
    print
    NUM=input("ENTER THE NUMBER OF SEATS YOU WANT TO BOOK: ")
    welcome()
    print
    module.printing_grid(movie2,name,33)
    while var<NUM:
        print
        seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
        nwlst=listnw(movie2)
        chk=seat.capitalize() in nwlst
        if chk==True:
                emp_lst.append(seat)
        while chk==False:
            print "INVALID SEAT,PLEASE ENTER AGAIN"
            seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
            chk=seat.capitalize() in nwlst
            if chk==True:
                emp_lst.append(seat)
        if seat not in(seats_unavailable2):
            seats_res.append(seat.capitalize())
            var+=1
        else:
            print "SORRY THIS SEAT IS ALREDY BOOKED"
        seats_unavailable2.append(seat)
    thanks()
    module.line2(1)
    movie2=module.updating(seats_res,movie2,flname)
    return movie2,seats_unavailable2,emp_lst
def mov_3(movie3,seats_unavailable3):                       #MOVIE-3
    var=0
    emp_lst=[]
    flname='m_v3.txt'
    name='TRANSFORMERS'
    seats_res=[]
    module.line2(1)
    print
    NUM=input("ENTER THE NUMBER OF SEATS YOU WANT TO BOOK: ")
    welcome()
    print
    module.printing_grid(movie3,name,30)
    while var<NUM:
        print
        seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
        nwlst=listnw(movie3)
        chk=seat.capitalize() in nwlst
        if chk==True:
                emp_lst.append(seat)
        while chk==False:
            print "INVALID SEAT,PLEASE ENTER AGAIN"
            seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
            chk=seat.capitalize() in nwlst
            if chk==True:
                emp_lst.append(seat)
        if seat not in(seats_unavailable3):
            seats_res.append(seat.capitalize())
            var+=1
        else:
            print "SORRY THIS SEAT IS ALREDY BOOKED"
        seats_unavailable3.append(seat)
    thanks()
    module.line2(1)
    movie1=module.updating(seats_res,movie3,flname)
    return movie3,seats_unavailable3,emp_lst
def mov_4(movie4,seats_unavailable4):                     #MOVIE-4
    var=0
    emp_lst=[]
    name='TERMINATOR'
    flname='m_v4.txt'
    seats_res=[]
    module.line2(1)
    print
    NUM=input("ENTER THE NUMBER OF SEATS YOU WANT TO BOOK: ")
    welcome()
    print
    module.printing_grid(movie4,name,31)
    while var<NUM:
        print
        seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
        nwlst=listnw(movie4)
        chk=seat.capitalize() in nwlst
        if chk==True:
                emp_lst.append(seat)
        while chk==False:
            print "INVALID SEAT,PLEASE ENTER AGAIN"
            seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
            chk=seat.capitalize() in nwlst
            if chk==True:
                emp_lst.append(seat)
        if seat not in(seats_unavailable4):
            seats_res.append(seat.capitalize())
            var+=1
        else:
            print "SORRY THIS SEAT IS ALREDY BOOKED"
        seats_unavailable4.append(seat)
    thanks()
    module.line2(1)
    movie4=module.updating(seats_res,movie4,flname)
    return movie4,seats_unavailable4,emp_lst
def mov_5(movie5,seats_unavailable5):                   #MOVIE-5
    var=0
    emp_lst=[]
    flname='m_v5.txt'
    name='SPIDERMAN-2'
    seats_res=[]
    module.line2(1)
    print
    NUM=input("ENTER THE NUMBER OF SEATS YOU WANT TO BOOK: ")
    welcome()
    print
    module.printing_grid(movie5,name,30)
    while var<NUM:
        print
        seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
        nwlst=listnw(movie5)
        chk=seat.capitalize() in nwlst
        if chk==True:
                emp_lst.append(seat)
        while chk==False:
            print "INVALID SEAT,PLEASE ENTER AGAIN"
            seat=raw_input("ENTER THE SEAT YOU WANT TO BOOK: ")
            chk=seat.capitalize() in nwlst
            if chk==True:
                emp_lst.append(seat)
        if seat not in(seats_unavailable5):
            seats_res.append(seat.capitalize())
            var+=1
        else:
            print "SORRY THIS SEAT IS ALREDY BOOKED"
        seats_unavailable5.append(seat)
    thanks()
    module.line2(1)
    movie5=module.updating(seats_res,movie5,flname)
    return movie5,seats_unavailable5,emp_lst

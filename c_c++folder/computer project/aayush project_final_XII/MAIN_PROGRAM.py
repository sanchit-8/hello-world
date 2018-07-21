import module,movies,file_manipulation,os,re_setting,pickle,time,random
#<<--------MAIN PROGRAM---------->>
class details:
    def __init__(self):
        self.name=''
        self.phnum=0
        self.add=''
        self.tickets=[]
        self.b_code=''

    def code_gen(self):
        code=''
        for i in range(3):
            code=code+str(random.randint(0,9))
            code=code+chr(random.randint(65,90))
        f=open('codes.txt','r+')
        code_list=f.readlines()
        if code in code_list:
            code_gen()
        f.write(code+'\n')
        return code

    def input_data(self):
        self.name=raw_input("Enter name of the person on whose name tickets are to be booked: ").upper()
        self.phnum=raw_input("Enter your phone number: ")
        self.add=raw_input("Enter your address: ").upper()
        self.b_code=self.code_gen()

    def display(self):
        print
        print 'YOUR DETAILS ARE'
        print 'NAME: ',self.name
        print 'PHONE NUMBER: ',self.phnum
        print 'SEATS YOU BOOKED: ',self.tickets
        print 'ADDRESS: ',self.add
        print

def movie(obj):
    def line(m,n):                              #PRINTING THE LINES AND MENU
        k=''
        for j in range(n):
            k+=m
        print k
    def start():                                #PRINTING THE MENU
        line('.',167)
        line('_',167)
        print
        print "                                                        !!......WELCOME TO BOOK-YOUR SHOW.....!!"
        line('_',167)
        line('.',167)
    start()
    print "                                                 <<<--------THE MOVIES ON THE SHOW------->>>"
    print '''                                            ____________________________________________________________
                                            |         MOVIE-NAME                             CODES     |
                                            |                                                          |
                                            |          STARWARS                                 0      |
                                            |          WAZIR                                    1      |
                                            |       TRANSFORMER                                 2      |
                                            |        TERMINATOR                                 3      |
                                            |         SPIDERMAN-2                               4      |
                                            |__________________________________________________________|'''
    movie1=file_manipulation.reading_file('m_v1.txt')
    movie2=file_manipulation.reading_file('m_v2.txt')
    movie3=file_manipulation.reading_file('m_v3.txt')
    movie4=file_manipulation.reading_file('m_v4.txt')
    movie5=file_manipulation.reading_file('m_v5.txt')
    seats_unavailable1=[]
    seats_unavailable2=[]
    seats_unavailable3=[]
    seats_unavailable4=[]
    seats_unavailable5=[]
    n=input("ENTER THE CODE: ")
    if n==0:
        M1,seats_unavailable1,obj.tickets=movies.mov_1(movie1,seats_unavailable1)
    elif n==1:
        M2,seats_unavailable2,obj.tickets=movies.mov_2(movie2,seats_unavailable2)
    elif n==2:
        M3,seats_unavailable3,obj.tickets=movies.mov_3(movie3,seats_unavailable3)
    elif n==3:
        M4,seats_unavailable4,obj.tickets=movies.mov_4(movie4,seats_unavailable4)
    elif n==4:
        M5,seats_unavailable5,obj.tickets=movies.mov_5(movie5,seats_unavailable5)


def begins():
    global object_list
    while True:
        print '''        Enter 'B',to book seats
        Enter 'C' to check details
        Enter 'E' to exit
        Enter 'R' to reset everything'''
        print
        n=raw_input("Enter your choice: ").upper()
        if n=='B':                                           #booking tickets
            f=open('person_details.dat','ab')                 #file_object
            a=details()
            a.input_data()
            movie(a)                                          #sending the object
            pickle.dump(a,f)
            f.close()
            print
            print 'Your Booking Code Is ',a.b_code
            print 'TOTAL COST OF TICKETS: Rs',len(a.tickets)*250,'/-'
            print '____________________________________________________________________________________________________________________________________________________________________'

        elif n=='E':                                         #exit the program
            print 'Saving data.....exiting.....'
            time.sleep(3)
            break


        elif n=='R':
            re_setting.reset()


        elif n=='C':
            code=raw_input('Enter your booking code: ').upper()
            f=open('person_details.dat','rb')
            try:
                while True:
                    obj=pickle.load(f)
                    if obj.b_code==code:
                        obj.display()
            except:
                f.close()
object_list=[]
begins()


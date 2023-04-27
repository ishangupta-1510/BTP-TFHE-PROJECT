from ast import Num
from datetime import time
from re import S
import subprocess 
from subprocess import Popen, PIPE
from tokenize import Number 
from threading import Timer
import time
import struct
# def runMKTFHE():
#     print('function running')
#     subprocess.call("./MK-TFHE","/build","/test","/testMKbootNAND_FFT_v2-spqlios-fma")
def mk_selectFunc(mk_txt):
    # print(mk_txt)
    t1 = int(mk_txt)
    subprocess.call(["make"])
    # subprocess.call(["./alice.o"])
    p = subprocess.Popen(["./build/test/select-spqlios-fma"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    p.stdin.write(t3)
    p.stdin.flush()
    verify = p.stdout.readline()
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(veri)
    i = -1
    j = 0
    global mk_ar
    mk_ar = [[0]*9 for _ in range(10)]
    s = ""
    #print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
           # print(s)
            j+=1
            s = ""
        elif(element == " "):
            #print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            mk_ar[i][j] = int(s)
def mk_veri():
    return mk_ar

def order_by(val):
    t1=int(val)
    # print(t1)
    subprocess.call(["gcc","order_Employee.c", "-o", "order_employee.o", "-ltfhe-spqlios-fma"])
    p1 = subprocess.Popen(["./order_Employee.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t2 = b"%d\n" % t1
    p1.stdin.write(t2)
    p1.stdin.flush()
    print("hello")
    #p1.stdout.flush()
    result = p1.stdout.read()
    print("value of result")
    print(result)
    doNextne_orderby()
# def multi_key():
#     subprocess.call(["gcc", "order_server.c", "-o", "order_server.o", "-ltfhe-spqlios-fma"])
def doNextne_orderby():
    subprocess.call(["gcc", "order_server.c", "-o", "order_server.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./order_server.o")
    print("order_run")
    subprocess.call(["gcc", "order_verify.c", "-o", "order_verify.o", "-ltfhe-spqlios-fma"])
    program_path = "./order_verify.o"
    p = subprocess.Popen(["./order_verify.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    # print(p)
    # print("valur")
    verify = p.stdout.readline()
    # print("verifu=")
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(ver)
    i = 0
    j = 0
    global ar_orderby
    ar_orderby = [[0]*9 for _ in range(10)]
    s = ""
   # print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            ar_orderby[i][j] = int(s)
            s=""
            j+=1
        elif(element == " "):
            i+=1
            s=""
            j=0
        else:
            s+=element
    # for element in ver:
    #     if(element == ","):
    #         #ar[i][j] = int(s)
    #         # print(i,j)
    #         # print(ar[0][0])
    #         # print("s=")
    #         # print(i)
    #         # print(j)
    #         #print(s)
    #         j+=1
    #         s = ""
    #     elif(element == " "):
    #        # print(i,j)
    #         #print(ar[0][0])
    #         #print("run")
    #         i+=1
    #         s=""
    #         j=0
    #         # print(i,j)
    #     else:
    #         s+=element
    #         ar_orderby[i][j] = int(s)
    #result = p.stdout.readline().strip()
    # print("this is result")
    #print(result)
    # print("check")
    # print("Task is done.")
    print(ar_orderby)
def order_by_val():
    return ar_orderby
def runFunc1(txt1, txt2):
    t1=bytes(txt1+'\n', encoding='utf8')
    t2=bytes(txt2+'\n', encoding='utf8')
    print(t1)
    print(t2)
    global result
    print("Inside Python file.....")
    subprocess.call(["gcc","account.c", "-o", "account.o"])
    program_path = "./account.o"
    p1 = subprocess.Popen(["./account.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    p1.stdin.write(t1)
    p1.stdin.write(t2)
    p1.stdin.flush()
    print("hello")
    #p1.stdout.flush()
    result = p1.stdout.read()
    result = int(result)
    print(result)
 
    # print("this is result")
#     result1 = int.from_bytes(result, "big")
#    # result1=int(result)
#     print(result1)
   
  #  print(result1)
    # p.stdin.flush()
def result():
    return result
def subFunc(txt1,txt2):    
    t11 = int(txt1)
    t22 = int(txt2)
    print("Inside Python file.....")
    # print(txt1)
    # print(txt2)
    subprocess.call(["gcc","sub.c", "-o", "sub.o"])
    program_path = "./sub.o"
    sub = subprocess.Popen(["./sub.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    # ret = sub.stdout.readline()
    # print(ret)
    t33 = b'%d\n' %t11
    t44 = b'%d\n' %t22
    # print(t3)
    sub.stdin.write(t33)
    sub.stdin.write(t44)
    sub.stdin.flush()
    sub.stdin.close()
    sub1 = sub.stdout.readline()
    print(sub1)
    global subtract
    subtract = int(sub1)
    print("ans ")
    print(subtract)
    print("Task is done.")

def subtract():
    return subtract
def runFunc(txt1,txt2):
    t1 = int(txt1)
    t2 = int(txt2)
    print("Inside Python file.....")
    # print(txt1)
    # print(txt2)
    subprocess.call(["gcc","alice.c", "-o", "alice.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./alice.o"
    p = subprocess.Popen(["./alice.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    t4 = b"%d\n" % t2
    # print(t3)
    p.stdin.write(t3)
    p.stdin.write(t4)
    p.stdin.flush()
    doNext()
# def like(id1,name1,age1,balance1,id2,name2,age2,balance2,id3,name3,age3,balance3,id4,name4,age4,balance4,id5,name5,age5,balance5,id6,name6,age6,balance6,id7,name7,age7,balance7,id8,name8,age8,balance8):
#     iid1 = id1
#     iage1 = age1
#     ibalance1 = balance1
#     iid2 = id2
#     iage2 = age2
#     ibalance2 = balance2
#     iid3 = id3
#     iage3 = age3
#     ibalance3 = balance3
#     iid4 = id4
#     iage4 = age4
#     ibalance4 = balance4
#     iid5 = id5
#     iage5 = age5
#     ibalance5 = balance5
#     iid6 = id6
#     iage6 = age6
#     ibalance6 = balance6
#     iid7 = id7
#     iage7 = age7
#     ibalance7 = balance7
#     iid8 = id8
#     iage8 = age8
#     ibalance8 = balance8
#     subprocess.call(["gcc","Ownerl.c", "-o", "ownerl.o", "-ltfhe-spqlios-fma"])
#     # subprocess.call(["./alice.o"])
#     program_path = "./ownerl.o"
#     p = subprocess.Popen(["./ownerl.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
#     t11 = b"%d\n" % iid1
#     p.stdin.write(t11)
#     t12 = name1
#     p.stdin.write(t12)
#     t13 = b"%d\n" % iage1
#     p.stdin.write(t13)
#     t14 = b"%d\n" % ibalance1
#     p.stdin.write(t14)
#     t21 = b"%d\n" % iid2
#     p.stdin.write(t21)
#     t22 = name2
#     p.stdin.write(t22)
#     t23 = b"%d\n" % iage2
#     p.stdin.write(t23)
#     t24 = b"%d\n" % ibalance2
#     p.stdin.write(t24)
#     t31 = b"%d\n" % iid3
#     p.stdin.write(t31)
#     t32 = name3
#     p.stdin.write(t32)
#     t33 = b"%d\n" % iage3
#     p.stdin.write(t33)
#     t34 = b"%d\n" % ibalance3
#     p.stdin.write(t34)
#     t41 = b"%d\n" % iid4
#     p.stdin.write(t41)
#     t42 = name4
#     p.stdin.write(t42)
#     t43 = b"%d\n" % iage4
#     p.stdin.write(t43)
#     t44 = b"%d\n" % ibalance4
#     p.stdin.write(t44)
#     t51 = b"%d\n" % iid5
#     p.stdin.write(t51)
#     t52 = name5
#     p.stdin.write(t52)
#     t53 = b"%d\n" % iage5
#     p.stdin.write(t53)
#     t54 = b"%d\n" % ibalance5
#     p.stdin.write(t54)
#     t61 = b"%d\n" % iid6
#     p.stdin.write(t61)
#     t62 = name6
#     p.stdin.write(t62)
#     t63 = b"%d\n" % iage6
#     p.stdin.write(t63)
#     t64 = b"%d\n" % ibalance6
#     p.stdin.write(t64)
#     t71 = b"%d\n" % iid7
#     p.stdin.write(t71)
#     t72 = name7
#     p.stdin.write(t72)
#     t73 = b"%d\n" % iage7
#     p.stdin.write(t73)
#     t74 = b"%d\n" % ibalance7
#     p.stdin.write(t74)
#     t81 = b"%d\n" % iid8
#     p.stdin.write(t81)
#     t82 = name8
#     p.stdin.write(t82)
#     t83 = b"%d\n" % iage8
#     p.stdin.write(t83)
#     t84 = b"%d\n" % ibalance8
#     p.stdin.write(t84)
#     p.stdin.flush()
#     doNextlike()
# def doNextlike():
#     subprocess.call(["gcc", "serverl.c", "-o", "serverl.o", "-ltfhe-spqlios-fma"])
#     subprocess.call("./serverl.o")
#     # subprocess.call(["gcc", "verifyl.c", "-o", "verifyl.o", "-ltfhe-spqlios-fma"])
#     # p = Popen("./verifyl.o", stdout=PIPE, stdin=PIPE)
#     # result = p.stdout.readline().strip()
#     # # print("this is result")
#     # print(result)
#     # global ans
#     # ans = int(result)
#     print("ans ")
#     # print(ans)
#     print("Task is done.")
def emp(txt1):
    t1 = int(txt1)
    print("Inside Python file.....")
    # print(txt1)
    # print(txt2)
    subprocess.call(["gcc","emplyee.c", "-o", "employee.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./employee.o"
    p = subprocess.Popen(["./employee.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    # print(t3)
    p.stdin.write(t3)
    p.stdin.flush()
    doNextne()

def doNextne():
    time.sleep(6)
    subprocess.call(["gcc", "join_server.c", "-o", "join_server.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./join_server.o")
    subprocess.call(["gcc", "join_verifyn.c", "-o", "join_verifyn.o", "-ltfhe-spqlios-fma"])
    p = Popen("./join_verifyn.o", stdout=PIPE, stdin=PIPE)
    result = p.stdout.readline().strip()
    # print("this is result")
    print(result)
    global ans_cust
    ans_cust = int(result)
    print("ans ")
    print(ans_cust)
    print("Task is done.")
def answer_cust():
    return ans_cust

def doNext():
    time.sleep(6)
    subprocess.call(["gcc", "cloud.c", "-o", "cloud.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./cloud.o")
    subprocess.call(["gcc", "verify.c", "-o", "verify.o", "-ltfhe-spqlios-fma"])
    p = Popen("./verify.o", stdout=PIPE, stdin=PIPE)
    result = p.stdout.readline().strip()
    # print("this is result")
    print(result)
    global ans
    ans = int(result)
    print("ans ")
    print(ans)
    print("Task is done.")

def answer():
    return ans
def uploadFunc():
    subprocess.call(["gcc","Owner.c", "-o", "owner.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./owner.o"
    p = subprocess.Popen(["./owner.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    global up
    up='File upload successfully'
    print(up)
def up(request):
    return up

def verifynFunc():
    subprocess.call(["gcc","verifyn.c", "-o", "verifyn.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./verifyn.o"
    p = subprocess.Popen(["./verifyn.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
   # print(p)
    verify = p.stdout.readline()
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(veri)
    i = -1
    j = 0
    global arra
    arra = [[0]*9 for _ in range(10)]
    s = ""
   # print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
            #print(s)
            j+=1
            s = ""
        elif(element == " "):
           # print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            arra[i][j] = int(s)
def veri():
    return arra

def verifyFunc():
    subprocess.call(["gcc","verify1.c", "-o", "verify1.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./verify1.o"
    p = subprocess.Popen(["./verify1.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
   # print(p)
    verify = p.stdout.readline()
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(veri)
    i = -1
    j = 0
    global ar
    ar = [[0]*9 for _ in range(10)]
    s = ""
   # print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
            #print(s)
            j+=1
            s = ""
        elif(element == " "):
           # print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            ar[i][j] = int(s)
def veri():
    return ar

def equal_test(txt1):
    t1 = int(txt1)
    subprocess.call(["gcc","select.c", "-o", "select.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./select.o"
    p = subprocess.Popen(["./select.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    p.stdin.write(t3)
    p.stdin.flush()
    doNext1()
def doNext1():
    time.sleep(6)
    subprocess.call(["gcc", "equal_cloud.c", "-o", "equal_cloud.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./equal_cloud.o")
    subprocess.call(["gcc","verify.c", "-o", "verify.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./verify.o"
    p = subprocess.Popen(["./verify.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
   # print(p)
    verify = p.stdout.readline()
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(veri)
    i = -1
    j = 0
    global ar
    ar = [[0]*9 for _ in range(10)]
    s = ""
    #print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
           # print(s)
            j+=1
            s = ""
        elif(element == " "):
            #print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            ar[i][j] = int(s)
def s_veri():
    return ar
def likem(txt7,txt8,txt9):
    t1 = txt7
    t2 = txt8
    t3 = txt9
    subprocess.call(["gcc","Employee_like.c", "-o", "Employee_like.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./Employee_like.o"
    p = subprocess.Popen(["./Employee_like.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t4 = str.encode(t1)
    t5 = str.encode(t2)
    t6 = str.encode(t3)
    p.stdin.write(t4)
    p.stdin.write(t5)
    p.stdin.write(t6)
    p.stdin.flush()
    subprocess.call(["gcc","server_like.c", "-o", "server_like.o", "-ltfhe-spqlios-fma"])
    subprocess.call(["./server_like.o"])
    subprocess.call(["gcc","like_verify.c", "-o", "like_verify.o", "-ltfhe-spqlios-fma"])
    # p = subprocess.call(["./like_verify.o"])
    program_path = "./like_verify.o"
    p = subprocess.Popen(["./like_verify.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
   # print(p)
    verify = p.stdout.readline()
    global verif
    verif = verify.decode()
    print(verif)
    global ark
    ark = [[0]*3 for _ in range(3)]
    s = ""
    i = -1
    j = 0
    #print("vart=")
    #print(ver)
    for element in verif:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
            # print(s)
            j+=1
            s = ""
        elif(element == " "):
            #print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            ark[i][j] = s
    # doNext1()
def s5_veri():
    return ark


def greater_test(txt4):
    t1 = int(txt4)
    subprocess.call(["gcc","select.c", "-o", "select.o", "-ltfhe-spqlios-fma"])
    program_path = "./select.o"
    p = subprocess.Popen(["./select.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    p.stdin.write(t3)
    p.stdin.flush()
    doNext3()

def doNext3():
    time.sleep(6)
    subprocess.call(["gcc", "greater_cloud.c", "-o", "greater_cloud.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./greater_cloud.o")
    subprocess.call(["gcc","verify.c", "-o", "verify.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./verify.o"
    p = subprocess.Popen(["./verify.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
   # print(p)
    verify = p.stdout.readline()
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(veri)
    i = -1
    j = 0
    global ar
    ar = [[0]*9 for _ in range(10)]
    s = ""
    #print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
            # print(s)
            j+=1
            s = ""
        elif(element == " "):
            #print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            ar[i][j] = int(s)
def s1_veri():
    return ar
def s2_veri():
    return ar
def lesser_then(txt4):
    t1 = int(txt4)
    subprocess.call(["gcc","select.c", "-o", "select.o", "-ltfhe-spqlios-fma"])
    program_path = "./select.o"
    p = subprocess.Popen(["./select.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    p.stdin.write(t3)
    p.stdin.flush()
    doNext_lesser()

def doNext_lesser():
    time.sleep(6)
    subprocess.call(["gcc", "lesser_cloud.c", "-o", "lesser_cloud.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./lesser_cloud.o")
    subprocess.call(["gcc","verify.c", "-o", "verify.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./verify.o"
    p = subprocess.Popen(["./verify.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
   # print(p)
    verify = p.stdout.readline()
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(veri)
    i = -1
    j = 0
    global ar
    ar = [[0]*9 for _ in range(10)]
    s = ""
    #print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
            # print(s)
            j+=1
            s = ""
        elif(element == " "):
            #print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            ar[i][j] = int(s)
def s2_veri():
    return ar
def multi_equal_test(txt4,txt5):
    t1 = int(txt4)
    t2 = int(txt5)
    subprocess.call(["gcc","s1_select.c", "-o", "s1_select.o", "-ltfhe-spqlios-fma"])
    program_path = "./s1_select.o"
    p = subprocess.Popen(["./s1_select.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    t4 = b"%d\n" % t2
    p.stdin.write(t3)
    p.stdin.write(t4)
    p.stdin.flush()
    doNext4()
def doNext4():
    time.sleep(6)
    subprocess.call(["gcc", "multi_equal_cloud.c", "-o", "multi_equal_cloud.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./multi_equal_cloud.o")
    subprocess.call(["gcc","verify.c", "-o", "verify.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./verify.o"
    p = subprocess.Popen(["./verify.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
   # print(p)
    verify = p.stdout.readline()
    # print(verify)
    global ver
    ver = verify.decode()
    # print("vari=")
    # print(veri)
    i = -1
    j = 0
    global ar
    ar = [[0]*9 for _ in range(10)]
    s = ""
    #print("vart=")
    #print(ver)
    for element in ver:
        if(element == ","):
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
            # print(s)
            j+=1
            s = ""
        elif(element == " "):
            #print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            j=0
            # print(i,j)
        else:
            s+=element
            ar[i][j] = int(s)
def s3_veri():
    return ar
def join(txt6):
    
    t1 = int(txt6)
    subprocess.call(["gcc","Employee_join.c", "-o", "Employee_join.o", "-ltfhe-spqlios-fma"])
    program_path = "./Employee_join.o"
    p = subprocess.Popen(["./Employee_join.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    
    t3 = b"%d\n" % t1
    print("t1=")
    print(t1)
    # verify = p.stdout.readline()
    # print("verify=")
    # print(verify)
    p.stdin.write(t3)
    p.stdin.flush()
    # print("run")
    doNext6()

def doNext6():
    print("run")
    subprocess.call(["gcc", "join_server.c", "-o", "join_server.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./join_server.o")
    print("absi")
    subprocess.call(["gcc","join_verifyn.c", "-o", "join_verifyn.o", "-ltfhe-spqlios-fma"])
    # subprocess.call(["./alice.o"])
    program_path = "./join_verifyn.o"
    p = subprocess.Popen(["./join_verifyn.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    verify = p.stdout.readline()
    global verim
    verim = verify.decode()
    # print("vari=")
    # print(verim)
    i = 0
    j = 0
    global arpk
    arpk = [[0]*20 for _ in range(20)]
    s = ""

    for element in verim:
        # print(element)
        if(element == ","):
            print("came")
            #ar[i][j] = int(s)
            # print(i,j)
            # print(ar[0][0])
            # print("s=")
            # print(i)
            # print(j)
            # print(s)
            j+=1
            s = ""
            i=0
        elif(element == " "):
            #print(i,j)
            #print(ar[0][0])
            #print("run")
            i+=1
            s=""
            # print(i,j)
        else:
            s+=element
            # print("k")
            # print(s)
            # print("i=")
            # print(i)
            # print("j=")
            # print(j)
            arpk[j][i] = int(s)

def s4_veri():
    # print(arp)
    return arpk


def updateFunc(txt1, txt2):
    t1 = int(txt1)
    t2 = int(txt2)
    subprocess.call(["gcc","update.c", "-o", "update.o", "-ltfhe-spqlios-fma"])
    program_path = "./update.o"
    p = subprocess.Popen(["./update.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    t3 = b"%d\n" % t1
    t4 = b"%d\n" % t2
    p.stdin.write(t3)
    p.stdin.write(t4)
    p.stdin.flush()
    doNext5()

def doNext5():
    time.sleep(6)
    subprocess.call(["gcc", "up_cloud.c", "-o", "up_cloud.o", "-ltfhe-spqlios-fma"])
    subprocess.call("./up_cloud.o")
    p = subprocess.Popen(["./up_cloud.o"], stdout=subprocess.PIPE, stdin=PIPE, stderr = subprocess.PIPE)
    global up
    up='File update successfully'
    print(up)
def upexe():
    return up
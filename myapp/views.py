# Made by me - Manan Patel
import django.shortcuts
from django.http import HttpResponse
from django.shortcuts import render
import subprocess
from .tfhe.testa import likem,lesser_then,greater_test,equal_test,order_by_val,order_by,emp,runFunc,runFunc1, subFunc, uploadFunc,verifyFunc,multi_equal_test, join, updateFunc, mk_selectFunc
from subprocess import Popen, PIPE
from myapp.tfhe import testa
from threading import Timer
def mk_query(request):
    return render(request, 'mk_query.html')
def mk_result(request):
    textx = request.POST.get('mk_text', 'default')
    # print("mk_text" + textx)
    txt1 = textx
    global numchar
    mk_selectFunc(txt1)
    numchar = testa.mk_veri()
    print("numchar")
    print(type(numchar))
    params = {'numchar':numchar}
    print(params)
    return render(request, 'mk_result.html', params)
def mk_select(request):
  return render(request, 'mk_select.html')
def selection(request):
  return render(request, 'selection.html')
#def multi_key(request):
#   return render(request, 'multikey.html')
def like(request):
    t7 = request.POST.get('text7', 'default')
    t8 = request.POST.get('text8', 'default')
    t9 = request.POST.get('text9', 'default')
    global numchar
    if 's6exe' in request.POST:
      select5Func(t7,t8,t9)
      numchar = testa.s_veri()
      print("numchar")
      print(type(numchar))
    return render(request, 'like.html')
def emp(request):
    return render(request, 'employee.html')
def index(request):
    return render(request, 'index.html')
def adminP(request):
    a = request.POST.get('abc', 'default')
    tuid = request.POST.get('tuid', 'default')
    tpassword = request.POST.get('tpassword', 'default')
    runFunc1(tuid, tpassword)
    numchar1 = 0
    num= testa.result
    print(num)
    if 'abc' in request.POST:
        return render(request, 'adminP.html')
    if (num==1):
        return render(request, 'adminP.html')
    else: 
        return render(request, 'index.html')
    analyzed=''
def upload(request):
    uploadFunc()
    return render(request, 'upload.html')
def output(request):
    if 'abc' in request.POST:
        return render(request, 'adminP.html')
    if 'upload' in request.POST:
        return render(request, 'uploadSuccess.html')
    elif 'verify' in request.POST:
        verifyFunc()
        numchar = testa.veri()
        i=0
        arr = [[0]*11] * 11
        print("numchar")
    params = {'numchar':numchar}
    return render(request, 'output.html', params)
def query(request):
    return render(request, 'query.html')     

def select(request):
    return render(request, 'select.html') 

def update(request):
    return render(request, 'update.html') 

def result_cust(request):
    textx = request.POST.get('text1', 'default')
    txt1 = textx
    global numch
    if '6exe' in request.POST:
        print(txt1)
        select4Func(txt1) 
        print("thirdstatement")
        numch = testa.s4_veri()  
        print(type(numch))
        return reder(request, 'result_cust.html')
    params = {'numch':numch}
    print(params)
    print("abcdefg")
    return render(request, 'result_cust.html', params) 

def result(request):
    textx = request.POST.get('text1', 'default')
    texty = request.POST.get('text2', 'default')
    textz = request.POST.get('text3', 'default')
    textu = request.POST.get('text4', 'default')
    textv = request.POST.get('text5', 'default')
    textw = request.POST.get('text6', 'default')
    texta = request.POST.get('text7', 'default')
    textb = request.POST.get('text8', 'default')
    textc = request.POST.get('text9', 'default')
    txt1 = textx
    txt2 = texty
    txt3 = textz
    txt4 = textu
    txt5 = textv
    txt6 = textw
    txt7 = texta
    txt8 = textb
    txt9 = textc
    global numchar
    if 'sexe' in request.POST:
      equal_test(txt1)
      numchar = testa.s_veri()
      print("numchar")
      print(type(numchar))
      params = {'numchar':numchar}
      return render(request, 'result.html', params)
    
    elif 's1exe' in request.POST:
       greater_test(txt2) 
       numchar = testa.s1_veri() 
       print("numchar")
       print(type(numchar))
       params = {'numchar':numchar}
       return render(request, 'result.html', params)
       
    elif 's2exe' in request.POST:
       print("fihsuhwew the text is")
       print(txt3)
       lesser_then(txt3) 
       numchar = testa.s2_veri()
       params = {'numchar':numchar}
       return render(request, 'result.html', params) 
       print("numchar")
       print(type(numchar)) 
    elif 's3exe' in request.POST:
       multi_equal_test(txt4,txt5) 
       numchar = testa.s3_veri()  
    #    pass two input
       print("numchar")
       print(type(numchar))
    elif 's4exe' in request.POST:
        print(txt6)
        join(txt6) 
        print("thirdstatement")
        numchar = testa.s4_veri()  
        print(type(numchar))
        params = {'numchar':numchar}
        return render(request, 'result_cust.html', params)
    elif 's5exe' in request.POST:
        likem(txt7, txt8, txt9)
        numchar = testa.s5_veri()
        print(numchar)
        params = {'numchar':numchar}
        return render(request,'result_like.html',params)
    elif 'my-dropdown' in request.POST:
        if request.method == 'POST':
            selected_option = request.POST.get('my-dropdown')
            print("this is the selected option")
            order_by(selected_option)
            numchar = order_by_val()
            params = {'numchar':numchar}
            print(params)
            # print("selected_option")
            # print(selected_option)
            return render(request, 'result.html', params)
        else:
            return render(request, 'result.html', params)
    params = {'numchar':numchar}
    return render(request, 'result.html', params)
    
# def result_cust(request):
#     textx = request.POST.get('text1', 'default')
#     texty = request.POST.get('text2', 'default')
#     textz = request.POST.get('text3', 'default')
#     textu = request.POST.get('text4', 'default')
#     textv = request.POST.get('text5', 'default')
#     textw = request.POST.get('text6', 'default')
#     txt1 = textx
#     txt2 = texty
#     txt3 = textz
#     txt4 = textu
#     txt5 = textv
#     txt6 = textw
#     global numchar
#     if 'sexe' in request.POST:
#       selectFunc(txt1)
#       numchar = testa.s_veri()
#       print("numchar")
#       print(type(numchar))
#     elif 's1exe' in request.POST:
#        select1Func(txt2) 
#        numchar = testa.s1_veri() 
#        print("numchar")
#        print(type(numchar))
       
#     elif 's2exe' in request.POST:
#        select2Func(txt4) 
#        numchar = testa.s2_veri() 
#        print("numchar")
#        print(type(numchar)) 
#     elif 's3exe' in request.POST:
#        select3Func(txt5) 
#        numchar = testa.s3_veri()  
#        print("numchar")
#        print(type(numchar))
#     elif 's5exe' in request.POST:
#         print(txt6)
#         select4Func(txt6) 
#         print("thirdstatement")
#         numchar = testa.s4_veri()  
#         print(type(numchar))
#     params = {'numchar':numchar}
#     return render(request, 'result_cust.html', params) 
def my_view(request):
  if request.method == 'POST':
    selected_option = request.POST.get('my-dropdown')
    # Do something with the selected option
    return render(request, 'result.html', {'selected_option': selected_option})
  else:
    return render(request, 'result.html')
def analyze1(request):
    textx = request.POST.get('text1', 'default')
    texty = request.POST.get('text2', 'default')
    txt1 = textx
    txt2 = texty
    updateFunc(txt1,txt2)
    numchar = testa.upexe()
    params = {'numchar':numchar}
    return render(request, 'analyze1.html', params)
def result1(request):
      verifyFunc()
      numchar = testa.veri()
      print("numchar")
      print(type(numchar))
      params = {'numchar':numchar}
      return render(request, 'result1.html', params)


def welcome(request):
    return render(request, 'welcome.html')

def analyze(request):
    textx = request.POST.get('text1', 'default')
    texty = request.POST.get('text2', 'default')
    job = ""
    analyzed = ""
    numchar = 0
    punctuations = '''!()-[]{};:'"\/,<>.?@#$%^&*~`'''
    analyzed = ""
    for char in textx:
        if char not in punctuations:
            analyzed += char
    job += '| Removed Puntuations '
    textx = analyzed

    count = 0
    for char in textx:
        if not (char == " " and char == '\n'):
            count += 1
    txt1 = textx
    txt2 = texty
    if 'add' in request.POST:
        runFunc(txt1, txt2)
        numchar = testa.answer
    elif 'sub' in request.POST:
        subFunc(txt1,txt2)
        numchar = testa.subtract
    params = {'job':job , 'analyzed_text':analyzed, 'numchar':numchar}
    return render(request, 'analyze.html', params)

def analyzesub(request):
    textx = request.POST.get('text1', 'default')
    texty = request.POST.get('text2', 'default')
    job = ""
    analyzed = ""
    numchar = 0
    punctuations = '''!()-[]{};:'"\/,<>.?@#$%^&*~`'''
    analyzed = ""
    for char in textx:
        if char not in punctuations:
            analyzed += char
    job += '| Removed Puntuations '
    textx = analyzed

    count = 0
    for char in textx:
        if not (char == " " and char == '\n'):
            count += 1
    txt1 = textx
    txt2 = texty
    subFunc(txt1, txt2)
    numchar = testa.subtract
    params = {'job':job , 'analyzed_text':analyzed, 'numchar':numchar}
    return render(request, 'analyze.html', params)
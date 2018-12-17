# AdvancedScript

It's just Functions which will help Plugin Coder , maybe in the future It will be as name it have :)

////////////////////////////////////////////////////////////////////////////
## History Section:
```
- version 1.6:
      1- add Parser system to recognize arguments.
      2- begin build Script system.
      3- add more Helper Functions.
- version 1.4:
      1- make StrCompx in separate Thread and add Sleep time to wait x64dbg to finish process.
      2- Fix Hex2duint function add length check in case it less than 2 . 
- version 1.3:
      1- Add another argument to cbLogxJustAtBP for printing on LogxWindow.
      2- now it accept bool argument like this (true/false-on/off-1/0).
      3- add StrComp_BP function for compare string in memory at BP.
      4- compiled x32.
 ```

////////////////////////////////////////////////////////////////////////////
## Script Section:
-arguments value system (AVS): all argument pass through Parser system recognizer,how it work:
      1- search for all {} which is releated x64dbg system and try to resolve it.
      2- search for all $ which it's related to defined variables of AdvancedScript and resolve it. 
      3- search for all tokens by order ( * / + -) and resolve it. 
 sample :
      - $x +4/2 -1
      - {x} + $y +2
      - {rax} + 5       // all numbera are decimal , hexadecimal not support yet .
      - {rax +2*rcx} + $x

### 1- Varx: 
it's Like Var in x64dbg system, for defining variable's which can used in Script commands.
```
Parameter:
Varx P1, P2 , P3(optional) 
      P1: variable type it holde ( str , int , array )  /// array is defined with 500 elements.
      P2: variable name it should not have spaces or begin with $ , 
        >>>>>>but when resolve it's value it should add $ before it.<<<< like this $x  >> value of x 
      P3: the value of the variable it's optional for str and array only and the value will be null
            for int type it should be have a value and must be int 
            note : you can use variable for this arguments like $x or {rax}.
            no need to use ""
  sample :
         - varx int, x, 90
         - varx array, y, 1
         - varx str, x, {rax}
         - varx array, y
         - varx str, x
```
### 2- SetVarx / MovVarx : 
set value to the virables in AdvancedScript vriable system.
```
Parameter:
SetVarx P1, P2 , P3
      P1: variable name, it must (not) begin with $, because we need to assigned new value .
      P2: element index of the array , no need for int and str or value=0
      P3: the value of the variable can used AVS, no need to use "".
      
   sample :
         - varx int, x, 90   >>>> x=90
           SetVarx x,10    >>>> x=10
         
         - varx str, x, {rax}     >>> x=rax value
           SetVarx x,test    >>> x=test
         
         - varx array, y
           SetVarx y,0,test1   >>>  y[0]=test1 
           SetVarx y,100,testx >>>  y[100]=testx
           SetVarx y,100,testx >>>  y[100]=testx
           SetVarx y,200,10 >>>  y[200]=10
```
### 3- SetVarx / MovVarx : 
set value to the virables in AdvancedScript vriable system.
```
Parameter:
SetVarx P1, P2 , P3
      P1: variable name, it must (not) begin with $, because we need to assigned new value .
      P2: element index of the array , no need for int and str or value=0
      P3: the value of the variable can used AVS, no need to use "".
      
   sample :
         - varx int, x, 90   >>>> x=90
           SetVarx x,10    >>>> x=10
         
         - varx str, x, {rax}     >>> x=rax value
           SetVarx x,test    >>> x=test
         
         - varx array, y
           SetVarx y,0,test1   >>>  y[0]=test1 
           SetVarx y,100,testx >>>  y[100]=testx
           SetVarx y,100,testx >>>  y[100]=testx
           SetVarx y,200,10 >>>  y[200]=10
```
### 3- GetVarx / PrintVarx : 
set value to the virables in AdvancedScript vriables system.
```
Parameter:
SetVarx P1, P2 
      P1: variable name, it must begin with $, because we need to get the value .
      P2: element index of the array , no need for int and str or value=0
          the value of the variable can used AVS, no need to use "".
      
   sample :
         - varx int, x, 90   >>>> x=90
           SetVarx x,10    >>>> x=10
         
         - varx str, x, {rax}     >>> x=rax value
           SetVarx x,test    >>> x=test
         
         - varx array, y
           SetVarx y,0,test1   >>>  y[0]=test1 
           SetVarx y,100,testx >>>  y[100]=testx
           SetVarx y,100,testx >>>  y[100]=testx
           SetVarx y,200,10 >>>  y[200]=10
```
### 3- findallmemx : 
it's same findallmem in x64dbg system, but it accept variables in the parameter.
```
Parameter:
SetVarx P1, P2, P3 
      P1: The address to start searching from.
      P2: The byte pattern to search for. This byte pattern can contain wildcards (?)
            for example: EB0?90??8D
      P3: The size of the data to search in. Default is the entire memory map..
                  >>all variable can used AVS<<
   sample :
         - varx str, search, "4533C94533C033"
           varx str, base, { rdx }
           findallmemx $base, $search
           mov rdi, ref.addr(0)

         - findallmem 0x10000, "4533C94533C033"
           mov rdi, ref.addr(0)
```
////////////////////////////////////////////////////////////////////////////
## Log Section:

### 1- LogxJustAtBP: 
```
Enable user to Log Just At BP or HW-BP so the Log window will contain the Value's you log, nothing else.
ofc you have to set the Log at Edit BreakPoint Dialog,Like this:
```
![bp_box](https://user-images.githubusercontent.com/7176580/49206425-787a6d00-f3cb-11e8-91fb-7b961eef9853.png)
```
using:
      LogxJustAtBP true,true  /// Log at BreakPoints on both Log window ( x64dbg and LogxWindow)
      LogxJustAtBP false,false /// Log as defaults 
      you can use another way to set the arguments Like :
      LogxJustAtBP on,on     or    LogxJustAtBP 1,1
      LogxJustAtBP off,off     or    LogxJustAtBP 0,0
```
**note: use the last version of x64dbg.**

//////////////////////////////////

### 2- LogxTemplateManager: 
```
Show Template window which enable u to define many template you want to used it later at BP or At tracer.
it anable you to save and rename and delete template edit Template.
note : Template Folder will be in the x64dbg folder root as LogTemplate.
No parameters needed.
```
![logxtemplatemanager](https://user-images.githubusercontent.com/7176580/49510131-c6e2ac80-f8a0-11e8-8594-421f880e829b.png)

//////////////////////////////////

### 3- logxwindow: 
```
Show Additional log window which log data from Logx Function it just for help to see log
when u want without extra info .
No parameters needed
```
![logxwindow](https://user-images.githubusercontent.com/7176580/49495151-7f95f500-f87b-11e8-867d-33458678005f.png)

//////////////////////////////////

### 4- logx: 
```
useding to log by defined Template so you can used at command line direct, or you can put it at BP dialog to 
log as defined Template .
usage:
      logx TemplateName     /// Template name should define in LogxTemplateManager      
```
![logx](https://user-images.githubusercontent.com/7176580/49495460-78231b80-f87c-11e8-9cef-6c66e118f0df.png)

//////////////////////////////////

### 5- logxTrace: 
```
this used as a Tracer to log as defined template using step triger ( F7 , F8 )
it will log direct to a file at LogTrace Folder as the name it define.
note : Trace Folder will be in the x64dbg folder root as LogTrace.
usege :
logxTrace P1,P2,P3
      P1 : on or off // (on:Enable tracer, need to enter (P2 & P3) , (off:disable Tracer , no need P2,P3).
      P2: Template Name should be define in LogxTemplateManager.
      P3: Trace file name ( it will created in LogTrace folder and it will be as Text file).
sample:
logxTrace off
logxTrace on,Template0,test
```
////////////////////////////////////////////////////////////////////////////
## Functions Section:

### 1- strcompx : 
```
used at the command of BP dialog to get the string at the address of memory , this Function use 
Contains compare so no need to write all string it's enough to write part of it and function will
find it.
```
![strcompx](https://user-images.githubusercontent.com/7176580/49727096-e73bae00-fc88-11e8-9548-d97e1057d692.png)
```
Parameter:
StrCompx P1, P2 , P3 , P4
      P1: resume after hit the BP (true/false - on/off - 1/0). 1: contiue , 0: stop
      P2: log Template name ,it should defined in the LogxTemplateManager.
      P3: memory Address which hold the string if it's number then no problem, if it's string 
            (like [rsp+4]) it should follow x64dbg string format 
 ```
![string Formatting](https://x64dbg.readthedocs.io/en/latest/introduction/Formatting.html?highlight=string)          
```
      P4: UserString2Compare u can put any string you want but it should not contain ,
sample:  
 StrCompx 0,t1,{[esp+4]},x32dbg   // t1 name of the template
 StrCompx 1,Template0,{rdx},MSCTFIME UI
```
//////////////////////////////////

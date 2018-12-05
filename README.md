# AdvancedScript

It's just Functions which will help Plugin Coder , maybe in the future It will be as name it have :)

### 1- LogxJustAtBP: 
```
Enable user to Log Just At BP or HW-BP so the Log window will contain the Value's you log, nothing else.
ofc you have to set the Log at Edit BreakPoint Dialog,Like this:
```
![bp_box](https://user-images.githubusercontent.com/7176580/49206425-787a6d00-f3cb-11e8-91fb-7b961eef9853.png)
```
using:
      LogxJustAtBP true  /// Log at BreakPoints
      LogxJustAtBP false /// Log as defaults 
```
**note: use the last version of x64dbg.**

////////////////////////////////////////////////////////////////////////////

### 2- LogxTemplateManager: 
```
Show Template window which enable u to define many template you want to used it later at BP or At tracer.
it anable you to save and rename and delete template edit Template.
note : Template Folder will be in the x64dbg folder root as LogTemplate.
No parameters needed.
```
![logxtemplatemanager](https://user-images.githubusercontent.com/7176580/49494711-021db500-f87a-11e8-995a-8ba256d8098f.png)

////////////////////////////////////////////////////////////////////////////

### 3- logxwindow: 
```
Show Additional log window which log data from Logx Function it just for help to see log
when u want without extra info .
No parameters needed
```
![logxwindow](https://user-images.githubusercontent.com/7176580/49495151-7f95f500-f87b-11e8-867d-33458678005f.png)

////////////////////////////////////////////////////////////////////////////

### 4- logx: 
```
useding to log by defined Template so you can used at command line direct, or you can put it at BP dialog to 
log as defined Template .
usage:
      logx TemplateName     /// Template name should define in LogxTemplateManager      
```
![logx](https://user-images.githubusercontent.com/7176580/49495460-78231b80-f87c-11e8-9cef-6c66e118f0df.png)

////////////////////////////////////////////////////////////////////////////

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

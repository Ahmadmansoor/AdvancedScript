# AdvancedScript

just a try to add more feature's to x64dbg script system

![ScriptWindow 3 0](https://user-images.githubusercontent.com/7176580/54919824-30073200-4f1b-11e9-9221-7e94496583d7.png)

[![AdvancedScript How to](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://youtu.be/hku8Is8-Z34)

[![Script How to fix IAT](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://youtu.be/37gTCNIAIAM)

[![Themida API Comment Script Good for Static Analyzing](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://youtu.be/SKustnN7qEY)


## use Scriptw command for showing the Script window and F12 for steping and F11 for Auto run.
////////////////////////////////////////////////////////////////////////////
## History Section:
```
- version 3.0 :
	1- add help file and command help on the form.
	2- add ads lib like ("GetAPIName","GetArraySize","ReadStr","GetdesCallJmp","isInArray","isAddrBelongSection").
	3- Write2File_ can write array directly.
	4- add commentset  command.
	5- replace Script::Debug::Wait();  with waitPauseProcess();
	6- at ret command .
	7- AutoComplete for Functions and variables and ads lib.
	8- add log box for future work.
	9- add AutoUpdate checkbox for enable disable update of variables list.
	10- fix some bug and improve some others like (findallmemx  .
	

- version 2.8 :
	1- fix a lot of bugs in calculations and get values.
	2- F11 run/stop script now Enabled, F12 step script.
	3- get values for nasted variables like $x[$z+1]
	4- add new commands (ret ,GetAPIName ,ResizeArray ,GetArraySize ,Write2File ,inputbox).
	5- add Dependency and samples Script as separate package.
	
- version 2.5 beta :
	1- Script window is sperate.
	2- Create Folder for script,form Load script with category.
	3- add more mirror Functions (xorx - pushx ...), and Functions like 
	       ( if , goto,writestr ) to shortcut the work.
	4- show all variables in a list with it's values.
	5- edit script onfly.
	6- enable to define array with range like z[n].
	7- writestr Function.
	8- run from anyware in the script.
	9- rest variables list in case maintenance. 
	10- insert rows as much as you need.
	11- insert from clipboard replace all script.
	12- insert from clipboard inside the script.
	13- copy separated lines to used in other script.
	14- insert description without confusing ;).
	15- add the dll file of c++ runtime for each package.
	16- as it is beta version so it support one step not auto step , use F12 for step, sorry for that 
		I need to check if it work then I will add auto step :}
	
- version 2.0:
      1-all numbers are hex numbers.
      2-more nested in arguments.
      3-Build bridge to make plugin system Compatible with x64dbg script system.
      4-create parallel Functions to x64dbg Functions, like ( cmp >> cmpx ).
      5-rename new name (Varx Getx Setx) and fix array index entry.
      6-add VarxClear ( clear all variable to help user in test's ) , memdump with print style.
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
```
- notes:
	1-to call the window of plugin type: Scriptw
	2-use F11 to run or stop Auto step
	3-use F12 to step on.
	4-sometime you think it's hange,but check if the Plugin send error messageBox for some lines.
	5-when you use F11 if the software in run mode ( not suspended) ,you have to pause it to work with Script window,
	  as it use wait Function form x64dbg which will not respond till the process is suspended.
	6-AutoComplete will show the Function name when typing and help box will show info, just press right arrow to finish
		but for get Variable name of call ads library press Ctrl + j and you will get textbox just type $ for variables
		name or type ads to get ads lib then press Enter and the command will set to end of line ( i didn't find a way 
		to insert text inside command :( ).
	7-when u use F11 try to not check AutoUpdate checkBox because the process will be heavy ( when fill array ).
	8-when u use BP at array list maybe x64dbg will take time to respond i DON'T Know why !!.
	
-arguments value system (AVS): all argument pass through Parser system recognizer,how it work:
      1- all numbers are in hex shape ( setx $x,50  == setx $x,0x50). 
      2- search for all {} which is releated x64dbg system and try to resolve it.
      3- search for all $ which it's related to defined variables of AdvancedScript and resolve it. 
      4- search for all tokens by order ( * / + -) and resolve it.
      5- all numbers in int variables are saved as decimal, put when it printed it print with 
            two way hex and decimal.
      6- all numbers which stored in str or array var are heximal.
      7- when define variables no need to use $, but wher ever you use this var you should add $ first.
      8- when calulate int value all arguments will converted to int and make the formula exist.
      9- when calulate str or array all arguments are set to gather after it calculate it's value's.
      10- we can define array of string with n elements.
      11- in parameter if string begin with " and end with " it will take it as it without analyzed.
      	  so if u want to write a command for some functions like asm command u can define the asm command 
	  with coma like "mov rax,1".
```
### 1- Varx:
Varx      variable type ,  variable name, value
it's Like Var in x64dbg system, for defining variable's which can used in Script commands.
```
Parameter:
Varx P1, P2 , P3(optional just for array and str) 
      P1: variable type it holde ( str , int , array )  /// array is just string elements.
      P2: variable name it should not have spaces or begin with $ , 
        >>>>>>but when resolve it's value, we should add $ before it.<<<< like this $x  >> value of x 
	For array variable we add [size] after the varible like this :
	 - varx array,x[10]		Create array with 16 elements
	 - varx array,x[10],test	Create array with 16 elements and set the first element value to (test)
      P3: the value of the variable it's optional for str and array only and the value will be null
            for int type it should be have a value and must be int 
            note : you can use variables as a value of the variable like this  $x or {rax}.
            no need to use "" in general, but if it had comma (,) we should but "" to define it as one string
	    like :
	    - varx str,x,this is test comma,done     >>this is wrong because it contain comma ",", so it should be 
	    - varx str,x,"this is test comma,done"
	    in some cases for some commands like findallmemx command we should use ""
	    like :
	    - varx str, search, "4533C94533C033"	here we should use comma
	    - varx str, base, { rdx }
	    - findallmemx $base, $search    
	    - mov rdi, ref.addr(0)
 Variable type is :
 - int: all value will saved as int value but it will show as hex or printed with two value hex/decimal.
 - str.
 - array with n string elements ( it's just string).
  sample :
         - varx int, x, 90
           varx array, y[1],10	       array with 1 elemnt with value =10 we get it by getx y[0]
	   getx y[0]			as array index is begin from 0
           varx str, x, {rax}
           varx array, y[10]	array with 16 elemnts 
           varx str, x
         //////////
         - varx int, x, 0x45fa
           varx int,x1,25+30    	 /// 0x55 /85
           varx array, z[$x],10		<<<you can use variable or equation in the index of the array>>>
	   varx array,cx[z[0]+$x+6]
           setx $z[10],test
           varx int,x2,$x +$x1+$z[0]
	   
	- varx array,x[1]
	  setx $x[0],10
	  getx $x[0]
	  varx array,z[$x[0]+1],t3
	  getx $z[0]
```
### 2- Setx : 
Setx  varname, value
set value to the virables in AdvancedScript vriable system or x64dbg system.
you can make add sub or multi or divide and you can nested arguments as you like.

```
Parameter:
Setx P1, P2 
      P1: variable name, it must (not) begin with $, because we need to assigned new value .
      for the array variable we use [Array_index] , no need this for int and str or Array_index=0
       array_index can accept variable's value
      P2: the value of the variable can used AVS, no need to use "".
      
   sample :
         - varx int, x, 90                x=0x90
           Setx x,10                      x=0x10
           
         - varx str, x, {rax}             x=rax value
           Setx $x,test                   x=test
           varx array,z[23],10            z[0]=10     because all elements are string       
           setx $z[5],$x$z[0]             z[5]=test10
           setx $z[5],$x $z[0]            z[5]=test 10
           setx $z[5],$x+$z[0]            z[5]=test+10
           setx $x,$z[0]                  x=0x10
           setx $x,$z[5]                  wrong value can't converted to int
           
         - varx int, x, 0x45fa            int x= 0x45FA\17914 :has been added
           varx str, z, 0xaa              str z= 0xaa :has been added
           setx $x, $z + 0x33 - 25        x= 0xB8\184
           varx array, y[6], 0x10         array y[0]= 0x10 :has been added
           setx $x, $x + $y[0]            x= 0xC8\200
	 
```
### 3- Getx / Printx : 
Getx   variable name
print the value of the virables .
```
Parameter:
Getx P1 
      P1: variable name, it must begin with $, because we need to get the value .
            for the array we put [array_index] if not used then it will print first 
            element in the array.
            array_index can accept variable's value
          the value of the variable can used AVS, no need to use comma "".
      
   sample :
         - varx int, x, 90          x=0x90
           SetVarx $x,10            x=0x10
           getx $x                  x=0x10
         - varx str, x, {rax}       x=rax value
           getx $x                  x=rax value
         
         -varx int, x, 10           int x= 0x10\16 :has been added
          varx array, y[$x], 1          array y[0]= 1 :has been added
          setx $y[$x], 110          y[10]= 110
          getx $y                   y[0]= 1
          getx $y[$x]               y[10]= 110
```
### 4- commands parallel of x64dbg  : 
it's collection of edit functions from x64dbg system, but it accept variables in the parameter.
- (Movx , addx , subx , mulx , divx , andx , orx , xorx , shlx ) : first parameter will not analyzed, just the second one.
- (pushx , popx):parameter will analyzed
- (BPxx , bpcx ,bpex ,bpdx ,bphx ,bphcx ,bphex ,bphdx ,bpmx) 	parallel commands for break point commands, 
								   parameters will analyzed.
- cmpx : both parameter will analyzed  /// replaced with (if) commands on the new Script window,
						but can be used at x64dbg Script Screen.
 ```
 -note :
	in new Update BPxx for one parameter can set on array of address directly , but for some resone x64dbg will take 
	time to respond ( I don't know why ) so u can go to refrence and set BP on all finded items.
	sample :
	- varx str,IATCall,"E8????????90"			//define the search pattern
	- varx int,TxSecBegin,{rip}				//define begin of section and set rip address
	- setx $TxSecBegin,ads.SectionBegin($TxSecBegin)	//Get section begin address by ads libary 
	- varx array,IatCallList[1]				//define array of call xxx
	- findallmemx $TxSecBegin,$IATCall,$IatCallList		//search for the pattern and fill IatCallList list
	- bpxx $MagicLineList		  			///set BP at IatCallList list fo the address 
```
```
sample :
     - again:
       varx str,base,{rax}
       cmpx {rax},$base   	>>> cmpx analyzed both parameters so we can write like this
       jne done
       jmp again 
       done:
     - varx int,x,20
       varx int,y,0xFF
       var z     		>>> this var from x64dbg system
       addx rax,$x+$y               rax =rax + 0x32+ 0x255 = rax + 0x287 
       addx z,$x+$y                 z=z+0x287
	
     -	varx str,addr,{rip+4}
	varx str,BPname,test
	bpxx $addr,$BPname
	bpcx $addr
	bphx $addr,r

    -	varx int,x,50
	setx $x ,0x30
	varx str,y,20
	movx rax,$x

         
```
### 5- findallmemx : 
findallmemx address, byte pattern to search, array variable to handle result ,  size of the data to search in

it's same findallmem in x64dbg system, but it accept variables in the parameter.
Find all occurrences of a pattern in the entire memory map.
note : in the new update now we can assign the result directly to ArrayList

```
Parameter:
findallmemx P1, P2, P3 ,P4
      P1: The address to start searching from.
      P2: The byte pattern to search for. This byte pattern can contain wildcards (?)
            for example: EB0?90??8D   or  "EB0?90??8D"
      P3: array variable it recommended to define array with 1 elements because this function will fill the array    
      P4: The size of the data to search in. Default is the entire memory map.. (optional)
                  >>all variable can used AVS<<
<<<<<<note: you can find the count of result by get {$result}>>>>>>>>
    sample :
         - varx str, search, "4533C94533C033"  << or >> varx str, search, 4533C94533C033
           varx str, base, { rdx }
	   varx array,y[1]
           findallmemx $base, $search ,$y
	or:   findallmemx $base,4533C94533C033 ,$y
	or:   findallmemx $base,"4533C94533C033" ,$y   // recomanded 
           //mov rdi, ref.addr(0)		       // old way  u can still used it 
	   
   
	- varx str, search, "4533C94533C033"
	  varx str, base, { rdx }
	  varx array,z[1]
	  findallmemx $base, $search,$z
	  	log {ref.addr(500)}
	  or 	getx $z[500]
	  varx int,k,0
	  	setx $k,{ref.addr(500)}
	  or	
	  setx $k,{$result} //result hold the array length    old way
	  or  GetArraySize $z,$k   // return the length of arry	  
	  mov rdi, ref.addr(0)
	  varx int, x0, 90
	  varx int, x1, 5
	  getx $x0
	  getx $x1
	  varx array, y, 1
	  setx $y, 110, 100
	  getx $y, 10 + $x + $x1 + 5
 
```
### 6- memdump : 
memdump  address , size of data

dump memory to log window like windbg style
```
	//00007ff8`02f42280  cc c3 cc cc cc cc cc cc - 0f 1f 84 00 00 00 00 00  ................
	//00007ff8`02f42290  cc c3 cc cc cc cc cc cc - 0f 1f 84 00 00 00 00 00  ................

Parameter:
memdump P1, P2 
      P1: The address to start dump.
      P2: size of data   
   sample :
         - memdump 00000000FF613570,50
                        
                  00000000FF613570         4883EC28E807FEFFFF4883C428EB1190        H?�(����H?�(�.
                  00000000FF613580         90909090909090909090909090909090        ................ 
                  00000000FF613590         488974240848897C241041544881ECB0        H?t$H?|$ATH��� 
                  00000000FF6135A0         0000008364242000488D4C2440FF157D        ...?d$ .H�L$@�} 
                  00000000FF6135B0         8C00009065488B042530000000488B78        ?...eH?%0...H?x
        
        - memdump {cip},50         {cip}= rip address
         
        -varx str,address,{cip}
         varx str,size,20
         memdump $address,$size
         
```
### 7- VarxClear : 
clear all variable's rest variables list , so we can add again same var 
Good for maintenance.
``` 
   sample :
         - VarxClear           
```
### 8- asmx : 
asmx 	Address ,Instruction text, filled with NOPs

it's mirror of asm command in x64dbg, it accept variables.
Parameter  asmx  addr , Instruction , fill with nops
	For Instruction: if you define it as var no problem if u but "" or not 
			but if you define it direct it good to surrounded it by ""
	fill with nops : just put 1 that enough and it will fill the rest with nops.
``` 
   sample :
         - varx str,addr,{rip}
	   varx str,command,"add rax,10"
	   asmx $addr,$command
      or   asmx $addr,"add rax,10"     
      
     How to asmeble command ( call qword ptr ds:[0x000000014004C408] ) at address, way to fix IAT
     -  varx str,addr,{rip}
	varx str,IAT,0x000000014004C408  or varx str,IAT,{rax}
 	varx str,call,"call qword ptr ds:["
 	setx $call,$call 0x$IAT ]		Don't forget 0x before $IAT ,and Don't forget the spaces before ] :), 
						so the it mix with var IAT name
	asmx $addr,$call   << this asm without fill with nops
	asmx $addr,$call,"1" << this asm with fill with nops	
	
	asmx 0x0000000140EA0010,"call qword ptr ds:[0x777259C0]",1
     - 

```
### 9- writeStr : 
writeStr  address , text to write , replace old string

this Function write any string to address of memory, in case replace is true, it read the string ( Asci or unicode )
then it zero the string memory and replace it with new string according the string type ( Asci or unicode ).
```
WriteStr  duint address, String^ text, bool replace

	- writeStr {rdx},"This is test" ,0
	- writeStr {rdx},"This is test" ,1
```
### 10- if / goto: 
(if) this Function as any if, its good for short the work of cmp jne .
(goto) it is as any goto it will jmp to line, it use the same Line number formulas of (if) command

 if condtion ( > < = != ?) , type (int, str/strb,stre,strc ) , line number if true , line number if false
 
 - note : if you set line number to 0 that mean step to next line.
 - note : in new version we can use ads lib like some commands which return true or false 
 	  like ( ads.isInArray  , ads.isAddrBelongSection  ) WILL explain later
 - note : when use ads lib parameter type will be ignored so u set it as str.
 - in parameter 1 :we can make any compare with variables ( >  <  =  != )  (?) just for string compare and should use 
 	one of the comapre string which is :
	strb : if string begin with 
	stre : if string end with 
	strc : if string contain
	
	sample :
		if mainStr?"string_",strb,5d,7d /// check if mainStr begin with (string_)
		
 - in parameter 2 :we define the type of variable we need to compare. we can compare int with int or string to string
 		int	
		str
		strb	string begin with
		stre	string end with
		strc	string contain with
		
 - Line number : there are 3 way to set it 
 
 		1- number + d : it mean the number is int not hex value Like 10d = line number 10
		2- number : it mean the number hex value Like 10 = line number 16
		3- string lable : it mean there are lable in the script it will jmp to 
		4- set one of them to 0 mean jmp to next line
		sample :
		1	varx int,x,0
		2	varx int,y,10
		3	if $x>$y,int,0,5d     /// if x>y then it will go to line 4 otherwise go to line 5
		4	........
		5	........
		
note : we can mix this tow commands and we get a loop good for IAT read write fix Loop
	or for search 
 
```
	-0	varx int,x,10
	 1	varx int,y,5
	 2	if $x=$y,int,GotHere,4d   compare between 2 int if they equal it will jmp to 
	 					lable (GotHere) else jmp to line number 4
 	 3	getx $x
 	 4	goto GotHere		go to line 8 ( lable GotHere)
 	 5	getx $y
 	 6	varx array,z[5],test
  	 7	setx $x,20
  	 8	GotHere:
  	 9	movx rax,{rsp}
	 .
	 .
	 .
	 20	goto 10			go to line 16
	 21 	goto 10d		go to line 10
	 
	 -Loop:
	 	varx int,x,0
		if $x<10,int,2d,Finish
		setx $x,$x+1
		getx $x
		goto 1d
		Finish:

	-varx str,Rstr
	 again:
	 run
 	 ReadStr $Rstr,{rdx}
	 if $Rstr?"ImmIMPGetIMEA",strc,5d,2d
	 ret

```
### 11- GetAPIName: 
this Function get API name of the address and set it to variable .
GetAPIName  varname ,  addrress
 - in parameter 1 :the variable which will handle the name it should be str or array
 - in parameter 2 :valid address of the API.
 
```
	-varx array,x[30],{rax}
	 GetApiName $x[2],$x[0]
 	 setx $x[4],APIAddr : $x[0] / $x[2]
 	 getx $x[4]
```
### 12- ResizeArray: 
this Function used to Resize Array variable it's good if we don't know how much we want to reverse.
so we can add more elements or sub some elements . 
resizeArr array,added amount
 - in parameter 1 :the array name .
 - in parameter 2 :the amount need to sub (-n) or add (+n) . 
```
	-varx array,x[1],1r
	 resizearray $x,10    add elements 
	 resizearray $x,-7    sub elements

```
### 13- GetArraySize: 
this Function used to get the size of Array variable.
GetArraySize  varArrName, varname
 - in parameter 1 :the array name .
 - in parameter 2 :the amount need to sub (-n) or add (+n) . 
```
	-GetArraySize $temp,$sizeArray	
```
### 14- Write2File:
write2File path,over_append(false/true),data (Can be array )
note: you can write array directly to file by write the array name see sample

this Function used to write data to file and can write array to file too .
write2File path,over_append(false/true),data
 - in parameter 1 :set the path of the file it can be done by variable other wise use "" surrounded path.
 - in parameter 2 :
 		- false: to over write file . ( u can use false or 0 or off )
		- true: to append to file . ( u can use true or 1 or on )
 - in parameter 3 : the data you want to write to the file it will analyzed if it have variables can be array .
```
	-varx str,path,"E:\temp1\log.txt"
	 varx array,x[2]
	 GetAPIName $x[0],{rax}
	 write2file $path,1,$x[0]	here it will append data to the log file
	 write2file $path,0,"API Name:" $x[0]     this will write the value of x[0]
	 
	 -varx array,x[2]
	  setx $x[0],test
	  setx $x[1],again
  	  Write2File "D:\t.txt",0,$x   	this will write all x array to t.txt file

```
### 15- InputBox: 
inputBox  variable, message, title

this Function used to get data from the user like address , it could be used as dialog to see if user say
yes or no or (y/n).
inputBox  variable, message, title
 - in parameter 1 :the variable which will hold the return message.
 - in parameter 2 :
 		- false: to over write file . ( u can use false or 0 or off )
		- true: to append to file . ( u can use true or 1 or on )
```
	-varx array,x[2],10
	 InputBox $x[1],this is $x[0],"info"
	 varx int,z,0
 	 InputBox $z,int test,test

```
### 16- ReadStr: 
ReadStr  variable , duint address

this Function used to read string at address.
ReadStr  variable , duint address
 - in parameter 1 :the variable which will hold string.
 - in parameter 2 :the address which have the string
```
	-varx str,Rstr
	 again:
	 run
 	 ReadStr $Rstr,{rdx}
	 if $Rstr?"ImmIMPGetIMEA",strc,5d,2d
	 ret

```
### 17- commentset: 
commentset  address,String comment

this Function set comment at address.
commentset  address,String comment

- P1 parameter 1 :address where we will set the comment at .
- P2 parameter 2 :comment string
```
	-varx int,x,{rip+4}	
	 varx str,z	
	 GetApiName $z,{rax}	
	 commentset $x,$z	

```
### 18- GetdesCallJmp: 
GetdesCallJmp   variable, address of call

this Function get the address of (Call xxxxx  or Jmp xxxx )and store it in a variable.
GetdesCallJmp   variable, address of call

- P1 parameter 1 :variable which gold the value .
- P2 parameter 2 :address of Call or jmp 
```
	-varx int,x,0	
	 GetdesCallJmp $x,{rip}		

```
////////////////////////////////////////////////////////////////////////////
## ads library: 
ads.____		/// ____ mean command
this library is used for fast get info like exebase or Sctionbase .....
ads.Command
commands Like :exebase,	modulebase,SectionSize,	exefolderpath,exename,SectionBegin,SectionEnd,
note : don't use nested command with ads lib which have brackets  ( it is not support yet )  .
like : ads.____ (ads.____(),____)    this not allow
but  : ads.____(ads.exebase,____)   this no problem      
form :
```
ads.exebase				get exe base
ads.modulebase(Modulename or address) 	get the base of module by name or address ( any address from the section)
ads.SectionSize(address) 		get Section base by address ( any address from the section)
ads.exefolderpath			get exe folder path
ads.exename				get exe name
ads.SectionBegin(address)		get begin of the section by address ( any address from the section)
ads.SectionEnd(address)			get End of the section by address ( any address from the section)
ads.GetAPIName(address)			get API name from address
ads.GetArraySize($arrayName)		get the array size
ads.ReadStr(address)			get string at address
ads.GetdesCallJmp(address of Call)	get the destination of call or Jmp :Like 
					0000000140EA4000 call 0x01F50304 
					ads.GetdesCallJmp(0000000140EA4000) >> return 0x01F50304 
ads.isInArray(text , arrayName)		used with if command it return true or false if the text exist in the array.
					ads.isInArray(GetProcAddress,$x)  or  ads.isInArray($z,$x)
					
ads.isAddrBelongSection((addr,any addr of the section)  used with if command it return true or false if this command belong to this
							section, 

```
	-varx str,IATCall,"E8????????90" //search for all call xxxx  nop in text section
	 varx str,MagicLine,"xxxxxx" //search for all magic line in Themida section
	 varx int,TxSecBegin,0 //text sction begin address
	 varx int,ThemidaSecBegin,0 //Themida sction begin address
	 varx int,TxSecEnd,0 //text sction End address
	 varx int,ThemidaSecEnd,0 //Themida sction End address
	 varx array,IatCallList[1] //list of Call emulated IAT, it's 1 because it will Auto refill later
	 varx array,MagicLineList[1] //list of magic line
	 varx int,i,0 //counter
	 inputbox $TxSecBegin,Please paste any address from text Section,Text Section //get address form text section to use it later to get Begin and End Section
	 inputbox $ThemidaSecBegin,Please paste any address from Themida Section,Themida Section //get address form Themida section to use it later to get Begin and End Section
	 setx $TxSecBegin,ads.SectionBegin($TxSecBegin) //Get address of text Section begin
	 setx $TxSecEnd,ads.SectionEnd($TxSecBegin) //Get address of text Section end
	 setx $ThemidaSecBegin,ads.SectionBegin($ThemidaSecBegin) //Get address of Themida Section begin
	 setx $ThemidaSecEnd,ads.SectionEnd($ThemidaSecBegin) //Get address of Themida Section End
	 findallmemx $TxSecBegin,$IATCall,$IatCallList //Find all Call xxxx nop and fill the list with result
	 findallmemx $ThemidaSecBegin,$MagicLine,$MagicLineList //Find all magic line and fill the list with result
	 bpxx $MagicLineList //set breack point on all items in the list
	 varx int,tempAddr,0
	 if $ThemidaSecBegin=$ThemidaSecEnd,int,17d,13d //begin check
	
```
	- varx str,x,ads.GetAPIName({rax})   // u can get the API name directly
```
```
	- varx array,x[20],30
	  varx int,y,ads.GetArraySize( $x)   // get array size direct
	  varx str,z,ads.ReadStr({rax})      // read string at address
```
Sample Scripts :

	-tracer :
		varx str,path,"E:\temp1\log.txt"
		varx str,addr
		varx str,APIname
		varx int,OEP,0000000140226B80
		varx array,temp[1]
		varx int,i,0
		if {rip}=$OEP,int,14d,7d
		resizearray $temp,1
		setx $addr,{rax}
		GETAPIName $APIname,$addr
		setx $temp[$i],$addr    $APIname
		setx $i,$i + 1
		go
		goto 6d
		varx int,sizeArray,0
		GetArraySize $temp,$sizeArray
		if $sizeArray=0,int,19d,17d
		write2file $path,1,$temp[$sizeArray]
		setx $sizeArray,$sizeArray -1
		goto 16d

```
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

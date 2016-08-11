Here is files for Windows build of QInterpreter with MSVC2010

note: 
x86 configured
x64 not configured, but differs from x86 only with libcurl.dll

Few steps to configure IDE for working with Flex and Bison:
1. 	Open solution
2. 	-> right click on project QInterpreter 
	-> Build Customizations...
	-> Find Existing
	-> choose file:
		 ../QInterpreter/3rdparty/win_flex_bison-latest/custom_build_rules/win_flex_bison_custom_build.targets
	-> click Yes
	-> choose win_flex_bison_build(.targets, .props)
	-> click OK
3. build
(hope it will work..)

If failed:
1. remove cpp, h, Lexer.l and Parser.y files from project
2. make sure build customization is enabled
3. add Lexer.l and Parse.y
4. add headers and cource files
5. build

If api-ms-win-crt-runtime-l1-1-0.dll is missing
	install windows updates IN NEXT ORDER(ORDER IS CRITICAL):
	1. 2919442 https://support.microsoft.com/en-us/kb/2919442
	(may fail to install - whatever go to the next step)	

	2919355 https://support.microsoft.com/en-us/kb/2919355 
	WAIT! KEEP THE ORDER!
	2. clearcompressionflag.exe
	3. KB2919355
	4. KB2932046
	5. KB2959977
	6. KB2937592
	7. KB2938439
	8. KB2934018
	9. 2999226 https://support.microsoft.com/en-us/kb/2999226
	10. Download and install the Visual C++ Redistributable 2015
	11. Do not forget praying to Bill Gates for Great OS ^_^

If VCRUNTIME140.dll is missing
	install x86 Visual C++ Redistributable for Visual Studio 2015 
	https://www.microsoft.com/en-us/download/details.aspx?id=48145
	
Flex options for Windows:
win_flex.exe --outfile="src/Lexer.cpp" --header-file="include/Lexer.h" --wincompat --bison-bridge --reentrant "Lexer.l" --warn --nodefault --noyywrap --never-interactive --nounistd 

______________________________
Anyway, be free to contact me:
mail: 4215050@gmail.com
skype: FrayaMiner

Have a good |x>,
Alex
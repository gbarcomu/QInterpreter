cd ../../../
mkdir build
cd build
mkdir win
cd win
mkdir x86
cd x86
mkdir Debug
mkdir Release
cd ../
mkdir x64
cd x64
mkdir Debug
mkdir Release
cd ../../../
copy 3rdparty\curl\curl-7.46.0-win32\dlls\libcurl.dll build\win\x86\Debug
copy 3rdparty\curl\curl-7.46.0-win32\dlls\libcurl.dll build\win\x86\Release
copy 3rdparty\curl\curl-7.46.0-win64\dlls\libcurl.dll build\win\x64\Debug
copy 3rdparty\curl\curl-7.46.0-win64\dlls\libcurl.dll build\win\x64\Release
copy vc\QInterpreter\test_me.bat build\win\x86\Debug
copy vc\QInterpreter\test_me.bat build\win\x86\Release
copy vc\QInterpreter\test_me.bat build\win\x64\Debug
copy vc\QInterpreter\test_me.bat build\win\x64\Release
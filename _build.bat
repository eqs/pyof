call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"

rem msbuild pyoflib\pyoflib.sln /t:clean;rebuild /p:Configuration=Release;Platform="x64"
msbuild pyoflib\pyoflib.sln /t:build /p:Configuration=Release;Platform="x64"
if %ERRORLEVEL% neq 0 (
    echo ErrorLevel:%ERRORLEVEL%
    echo ビルド失敗
    exit /b 1
)

exit /b 0

@echo off
call "%~dp0phase4\analyzer\Analyze.cmd" %*
exit /b %errorlevel%

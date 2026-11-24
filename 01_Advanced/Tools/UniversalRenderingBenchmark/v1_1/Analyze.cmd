@echo off
call "%~dp0analyzer\Analyze.cmd" %*
exit /b %errorlevel%

texcount -inc Report.tex
echo off
texcount -v -html -inc Report.tex > count.html
echo on
pause
pdflatex -synctex=1 report.tex
makeindex report.nlo -s nomencl.ist -o report.nls
bibtex report
pdflatex -synctex=1 report.tex
pdflatex -synctex=1 report.tex
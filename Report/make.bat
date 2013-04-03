pdflatex -synctex=1 report.tex
bibtex report
pdflatex -synctex=1 report.tex
pdflatex -synctex=1 report.tex
copy Report.pdf /Y C:\Users\hslovett\Dropbox\Report.pdf
texcount -brief Report.tex Research.tex InvestigationVision.tex Introduction.tex HardwareDevelopment.tex Conclusions.tex
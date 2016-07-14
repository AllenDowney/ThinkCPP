LATEX = latex

DVIPS = dvips

PDFFLAGS = -dCompatibilityLevel=1.4 -dPDFSETTINGS=/prepress  \
           -dCompressPages=true -dUseFlateCompression=true  \
           -dEmbedAllFonts=true -dSubsetFonts=true -dMaxSubsetPct=100


%.dvi: %.tex
	$(LATEX) $<

%.ps: %.dvi
	$(DVIPS) -o $@ $<

%.pdf: %.ps
	ps2pdf $@

all:	top.tex
	latex top
	makeindex top
	latex top
	dvips -Ppdf -o thinkCScpp.ps top
	ps2pdf $(PDFFLAGS) thinkCScpp.ps

distrib:
	rm -rf dist
	mkdir dist dist/tex dist/html
	cp thinkCScpp.pdf thinkCScpp.ps dist
	cp Makefile *.tex *.eps dist/tex
	cd dist/tex; make clean
	cd dist; tar -czf thinkCScpp.tex.tar.gz tex
	cd dist; cp thinkCScpp.tex.tar.gz thinkCScpp.tex.tgz
	cp -r dist/* /home/downey/public_html/greent/thinkcpp
	chmod -R o+r /home/downey/public_html/greent/thinkcpp/*

clean:
	rm -f *~ *.aux *.log *.dvi *.idx *.ilg *.ind *.toc


cha1.ps: cha1.tex
	latex cha1
	dvips -o cha1.ps cha1

cha2.ps: cha2.tex
	latex cha2
	dvips -o cha2.ps cha2

cha3.ps: cha3.tex
	latex cha3
	dvips -o cha3.ps cha3

cha4.ps: cha4.tex
	latex cha4
	dvips -o cha4.ps cha4

cha5.ps: cha5.tex
	latex cha5
	dvips -o cha5.ps cha5

cha6.ps: cha6.tex
	latex cha6
	dvips -o cha6.ps cha6

cha7.ps: cha7.tex
	latex cha7
	dvips -o cha7.ps cha7

cha8.ps: cha8.tex
	latex cha8
	dvips -o cha8.ps cha8

cha9.ps: cha9.tex
	latex cha9
	dvips -o cha9.ps cha9

cha10.ps: cha10.tex
	latex cha10
	dvips -o cha10.ps cha10

cha11.ps: cha11.tex
	latex cha11
	dvips -o cha11.ps cha11

cha12.ps: cha12.tex
	latex cha12
	dvips -o cha12.ps cha12

cha12_alt.ps: cha12_alt.tex
	latex cha12_alt
	dvips -o cha12_alt.ps cha12_alt

cha13.ps: cha13.tex
	latex cha13
	dvips -o cha13.ps cha13



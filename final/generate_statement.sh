#!/bin/bash

cd a-sort-pair
pdflatex statement.tex

cd ../b-snake-cube
pdflatex statement.tex

cd ../c-query-convex-hull
pdflatex statement.tex

cd ../d-tree-point
pdflatex statement.tex

cd ../e-range-time-query
pdflatex statement.tex

cd ../f-point-separation
pdflatex statement.tex

cd ../g-recursive-modular
pdflatex statement.tex

cd ../h-kotak-coklat
pdflatex statement.tex

cd ..

pdftk a-sort-pair/statement.pdf \
	b-snake-cube/statement.pdf \
	c-query-convex-hull/statement.pdf \
	d-tree-point/statement.pdf \
	e-range-time-query/statement.pdf \
	f-point-separation/statement.pdf \
	g-recursive-modular/statement.pdf \
	h-kotak-coklat/statement.pdf cat output problems.pdf
#!/bin/bash

cd Analysis
rm */*.eps

cd 24
gnuplot ../../CreateSeparateDiagrams.gnuplot
cd ../10
gnuplot ../../CreateSeparateDiagrams.gnuplot

#!/bin/bash

cd Analysis
rm */*.eps

cd 10
gnuplot ../../CreateSeparateDiagrams.gnuplot
cd ../16
gnuplot ../../CreateSeparateDiagrams.gnuplot
cd ../24
gnuplot ../../CreateSeparateDiagrams.gnuplot
cd ../36
gnuplot ../../CreateSeparateDiagrams.gnuplot

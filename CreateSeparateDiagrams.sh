#!/bin/bash

cd Analysis
rm */*.eps

cd 10
gnuplot ../../CreateSeparateDiagrams.gnuplot

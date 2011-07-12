SCRIPT=$(readlink -f $0)
SCRIPTPATH=`dirname $SCRIPT`
sed -e "s/DATAFILE/${1}/" $SCRIPTPATH/CreateDiagrams.gnuplot | gnuplot

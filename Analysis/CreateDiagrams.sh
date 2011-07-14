SCRIPT=$(readlink -f $0)
SCRIPTPATH=`dirname $SCRIPT`
cat $SCRIPTPATH/CreateDiagrams.gnuplot | gnuplot

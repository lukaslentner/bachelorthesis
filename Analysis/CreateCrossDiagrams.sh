SCRIPT=$(readlink -f $0)
SCRIPTPATH=`dirname $SCRIPT`
sed -e "s/DATAFOLDER/${1}/" $SCRIPTPATH/CreateCrossDiagrams.gnuplot | gnuplot

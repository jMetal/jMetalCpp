# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal svg size 400,300 enhanced fname 'arial'  fsize 10 butt solid
set output 'out.svg'

# Key means label...
set xlabel 'Function 1'
set ylabel 'Function 3'
set xrange[0:1]
set yrange[0:15]
set grid
set title 'OMOPSO - It=100 PI=0.5 SIZE=100 ASIZE=50'
plot  "data.txt" notitle
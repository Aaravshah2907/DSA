# plot.gp
set terminal pngcairo size 1200,700
set output "sorting_times_vs_size.png"

set logscale x 10
set style data linespoints
set title "Sorting Algorithm Time vs File Size"
set xlabel "File Size (Number of elements)"
set ylabel "Time (seconds)"
set key left top

# Plot using every 4th row starting from offset (skip header line at 0)
plot "sorting_times.dat" using 2:3 every ::1::999::4 with linespoints title "CountingSort", \
     "" using 2:3 every ::2::999::4 with linespoints title "RadixSort", \
     "" using 2:3 every ::3::999::4 with linespoints title "RadixExchangeSort", \
     "" using 2:3 every ::4::999::4 with linespoints title "BucketSort"
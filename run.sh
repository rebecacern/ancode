echo "Remove previous file"
rm results/histos.root
echo "Run now"
for i in {1..4}; do 
    root.exe -b -l -q histos.C+\($i\)
done 
root.exe -b -l -q plot.C\

echo "finished"

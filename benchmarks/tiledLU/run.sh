ITERATIONS=9
NPROCS=12

echo 'Making Directory stats'
mkdir -p stats

for n in 1 `seq 2 1 $NPROCS`;
do
    for it in `seq 1 $ITERATIONS`; 
    do
        echo Running mpirun -np ${n} fibonacci -a45 -w30 \> stats/fib_p${n}_${it}.txt;
        mpirun -np ${n} lu -n2000 -b200 > stats/lu_p${n}_${it}.txt;
    done
done

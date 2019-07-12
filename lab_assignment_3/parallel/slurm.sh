BATCH --partition=nuc     ### Partition
#SBATCH --job-name=sort     ### Job Name
#SBATCH --time=1:00:00      ### WallTime
#SBATCH --nodes=1            ### Number of Nodes
#SBATCH --ntasks-per-node=4 ### Number of tasks (MPI processes)
##SBATCH --cpus-per-task=1

echo Running on `hostname`
module load mpi/openmpi-2.1_pgi-18
which mpirun

mpirun -np 16 ./mpi_heat.o

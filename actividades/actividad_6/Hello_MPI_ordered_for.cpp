#include <iostream>
#include <mpi.h>

int main(int argc, char * argv[]) {
	int vec[1];
	MPI_Status status;
	if(MPI_Init(&argc, &argv) == MPI_SUCCESS) {
		int rank =-1;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		
		int process_count = -1;
		MPI_Comm_size(MPI_COMM_WORLD,&process_count);
		
		char hostname[MPI_MAX_PROCESSOR_NAME]:
		int hostname_lenght = -1;
		MPI_Get_processor_name(hostname, &hostname_lenght);
		
		if(rank == 0){
			cout << "Hello from process " << rank << "/" << process_count << " on " << hostname << endl;
			for(int i=1; i < process_count;i++){
				MPI_Send(&vec,1,MPI_INT,i,2020,MPI_COMM_WORLD);
				MPI_Recv(&vec,1,MPI_INT,i,2020,MPI_COMM_WORLD,&status);
				cout<<"Rank:"<<rank<<"received hello from"<<i<<endl;
			}
		}

		if(rank > 0){
			MPI_Recv(&vec,1,MPI_INT,0,2020,MPI_COMM_WORLD,&status);
			cout << "Hello from process " << rank << "/" << process_count << " on " << hostname << endl;
			MPI_Send(&%vec,1,MPI_INT,0,2020,MPI_COMM_WORLD);
		}
		MPI_Finalize();
	}
				
}

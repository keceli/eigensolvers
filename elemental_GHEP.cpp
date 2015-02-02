#include "El.hpp"

using namespace El;

typedef double Real;

int main( int argc, char* argv[] )
{
	Initialize( argc, argv );

	try
	{
	    std::string filename="";
	      std::string filenameA = Input("-A","file name ",std::string(""));
	      std::string filenameB = Input("-B","file name ",std::string(""));
	      const double vl       = Input("-l","local limit ",-0.8);
	      const double vu       = Input("-u","upper limit ",0.2);
		if(filenameA == "" or filenameB == "")
		{
			filename= Input("--filename","file name ",std::string(""));
			filenameA = filename + "A.bin";
			filenameB = filename + "B.bin";
		}
		const Int n = Input("-n","size of matrix",1);
		ProcessInput();

		Grid g( mpi::COMM_WORLD );
		DistMatrix<double> A( g );
		DistMatrix<double> B( g );
		std::string eigenfile = "eig_" + filename + std::to_string(g.Size());

		if( g.Rank() == 0 )
		{
			std::cout << " Grid info: "<< g.Height() << "x" << g.Width() << std::endl;
			std::cout << "  Reading matrices..." << std::endl;
			std::cout.flush();
		}
		double t0=mpi::Time();
		if(n==1)
		{
			Read(A,filenameA, AUTO, false);
			Read(B,filenameB, AUTO, false);
		}
		else
		{
		//	OneTwoOne( A, n );
			HermitianUniformSpectrum( A, n );
			Identity( B, n, n );
		}
		mpi::Barrier( g.Comm() );
		double t1=mpi::Time();

		if( g.Rank() == 0 )
		{
			if (n==1) std::cout << filenameA << " , "<< filenameB << " was read in (s): " << t1-t0 << std::endl;
			std::cout << "  Matrix heights: " << A.Height()<< " , "<< B.Height() << std::endl;
			std::cout << "  Memory size: " << A.AllocatedMemory()<< std::endl;
			std::cout << "  Redundant size: " << A.RedundantSize()<< std::endl;
			std::cout.flush();
		}

		Pencil pencil;
		pencil = AXBX;
		DistMatrix<Real,VR,STAR> w( g );
		DistMatrix<double> X(g);
		HermitianEigSubset<double> subset;
                const UpperOrLower uplo=CharToUpperOrLower('U');
		const Int sortInt = 2;
		const SortType sort = static_cast<SortType>(sortInt);
		HermitianEigCtrl<double> ctrl;
		ctrl.timeStages=true;
		if( g.Rank() == 0 )
		{
			std::cout << "  Solving matrix pencil..." << std::endl;
			std::cout.flush();
		}
		t0=mpi::Time();
                subset.rangeSubset = true;
		subset.lowerBound = vl;
		subset.upperBound = vu;
		
		//HermitianGenDefEig( eigType, uplo, A, B, w,vl,vu, sort );
		HermitianGenDefEig( pencil, uplo, A, B, w,X, sort,subset,ctrl );
		mpi::Barrier(g.Comm() );
		t1=mpi::Time();
		if( g.Rank() == 0 )
		{
			std::cout << "  Solved in (s): "<< t1-t0 << std::endl;
  			std::cout << "  Found "<< w.Height() << " eigenpairs in interval "<< vl <<"," << vu<< std::endl;
			std::cout.flush();
		}
		    std::string eigfilename = "myeigs." + FileExtension(ASCII);
		    std::ofstream file( eigfilename.c_str() );
		    if( !file.is_open() )
		        RuntimeError("Could not open ",eigfilename);

		    file.setf( std::ios::scientific );
		    file.precision(20);
		    Print( w, "", file );
		    //Write( w, eigenfile, ASCII );
		//Print(w,"Eigenvalues")
	}
	catch( std::exception& e ) { ReportException(e); }

	Finalize();
	return 0;
}

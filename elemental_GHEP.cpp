#include "El.hpp"

using namespace El;

typedef double Real;

int main( int argc, char* argv[] )
{
	Initialize( argc, argv );

	try
	{
    std::string filenameA = Input("-A","file name ",std::string(""));
    std::string filenameB = Input("-B","file name ",std::string(""));
    const double vl       = Input("-l","local limit ",-0.8);
    const double vu       = Input("-u","upper limit ",0.2);
		const Int n           = Input("-n","size of matrix",1);
		ProcessInput();
    const UpperOrLower uplo=CharToUpperOrLower('U');

		Grid g( mpi::COMM_WORLD );
		DistMatrix<double> A( g );
		DistMatrix<double> B( g );

		double t0=mpi::Time();
		if(n==1)
		{
			Read(A,filenameA, AUTO, false);
			Read(B,filenameB, AUTO, false);
		}
		else
		{

		//	OneTwoOne( A, n );
		  HermitianUniformSpectrum( A, n, 1, 100 );
		  HermitianUniformSpectrum( B, n, 1, 100 );
		//	Identity( B, n, n );
      // Because we will multiply by L three times, generate HPD B more 
      // carefully than just adding m to its diagonal entries.
    //  Zeros( B, n, n );
    //  DistMatrix<double> C(g);
    //  Uniform( C, n, n );
    //  Herk( uplo, ADJOINT, Real(100), C, Real(0), B );
		}
		mpi::Barrier( g.Comm() );
		double t1=mpi::Time();

		if( g.Rank() == 0 )
		{
			if (n==1) std::cout << filenameA << " , "<< filenameB << " was read in (s): " << t1-t0 << std::endl;
			if (n!=1) std::cout << "  Matrices generated in (s): " << t1-t0 << std::endl;
			std::cout << "  Grid info: "<< g.Height() << "x" << g.Width() << std::endl;
			std::cout << "  Matrix heights: " << A.Height()<< " , "<< B.Height() << std::endl;
			std::cout << "  Memory size: " << A.AllocatedMemory()<< std::endl;
			std::cout << "  Redundant size: " << A.RedundantSize()<< std::endl;
			std::cout << "  Solving matrix pencil..." << std::endl;
			std::cout.flush();
		}

		Pencil pencil;
		pencil = AXBX;
		DistMatrix<Real,VR,STAR> w( g );
		DistMatrix<double> X(g);
		HermitianEigSubset<double> subset;
		const Int sortInt = 2;
		const SortType sort = static_cast<SortType>(sortInt);
		HermitianEigCtrl<double> ctrl;
		ctrl.timeStages=true;
		t0=mpi::Time();
		if( n == 1 )
		{
      subset.rangeSubset = true;
		  subset.lowerBound = vl;
		  subset.upperBound = vu;
		}
    else
    {
      subset.indexSubset = true;
      subset.lowerIndex = 0;
      subset.upperIndex = int(n*0.6);
    }
		//HermitianGenDefEig( eigType, uplo, A, B, w,vl,vu, sort );
		HermitianGenDefEig( pencil, uplo, A, B, w,X, sort,subset,ctrl );
		mpi::Barrier(g.Comm() );
		t1=mpi::Time();
		if( g.Rank() == 0 )
		{
			std::cout << "  Solved in (s): "<< t1-t0 << std::endl;
  		if (n==1) std::cout << "  Found "<< w.Height() << " eigenpairs in interval "<< vl <<"," << vu<< std::endl;
  		if (n!=1) std::cout << "  Found "<< w.Height() << " eigenpairs "<< std::endl;
			std::cout.flush();
		}
		  //  std::string eigfilename = "myeigs." + FileExtension(ASCII);
		  //  std::ofstream file( eigfilename.c_str() );
		  std::string eigenfile = "eig." + std::to_string(A.Height())+"." + std::to_string(g.Size())+ "." +FileExtension(ASCII);
      if (n==1) std::string eigenfile = "eig." + filenameA +"." + std::to_string(g.Size())+ "." +FileExtension(ASCII);

		  std::ofstream file( eigenfile );
		  if( !file.is_open() ) RuntimeError("Could not open ",eigenfile);

		  file.setf( std::ios::scientific );
		  file.precision(20);
		  Print( w, "", file );
	}
	catch( std::exception& e ) { ReportException(e); }

	Finalize();
	return 0;
}

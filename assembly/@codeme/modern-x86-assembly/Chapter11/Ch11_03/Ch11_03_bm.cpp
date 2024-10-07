//-----------------------------------------------------------------------------
// Ch11_03_bm.cpp
//-----------------------------------------------------------------------------

#include "Ch11_03.h"
#include "BmThreadTimer.h"

void MatrixMulF64_bm(void)
{
    std::cout << "\nRunning benchmark function MatrixMulF64_bm() - please wait\n";

    constexpr size_t n = 100;
    constexpr size_t a_nrows = n;
    constexpr size_t a_ncols = n;
    constexpr size_t b_nrows = a_ncols;
    constexpr size_t b_ncols = n;
    constexpr size_t c_nrows = a_nrows;
    constexpr size_t c_ncols = b_ncols;

    MatrixF64 a(a_nrows, a_ncols);
    MatrixF64 b(b_nrows, b_ncols);
    MatrixF64 c1(c_nrows, c_ncols);
    MatrixF64 c2(c_nrows, c_ncols);

    InitMat(c1, c2, a, b);

    size_t sizes[3];
    sizes[0] = c2.GetNumRows();
    sizes[1] = c2.GetNumCols();
    sizes[2] = a.GetNumCols();

    double* a_p = a.Data();
    double* b_p = b.Data();
    double* c2_p = c2.Data();

    constexpr size_t num_alg = 2;
    constexpr size_t num_iter = BmThreadTimer::NumIterDef;
    constexpr size_t num_ops = 100;
    BmThreadTimer bmtt(num_iter, num_alg);

    for (size_t i = 0; i < num_iter; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            MatrixMulF64_cpp(c1, a, b);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            MatrixMulF64_avx2(c2_p, a_p, b_p, sizes);
        bmtt.Stop(i, 1);

        if (i % 25 == 0)
            std::cout << '.' << std::flush;
    }

    std::cout << std::endl;

    bool is_equal = MatrixF64::IsEqual(c1, c2, c_Epsilon);

    if (is_equal)
        std::cout << "Matrix compare passed\n";
    else
        std::cout << "Matrix compare failed!\n";

#if 0
    // Test code
    SaveResults(c1, c2, a, b, "bm_");
#endif

    std::string fn = bmtt.BuildCsvFilenameString("@Ch11_03_MatrixMulF64_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}

#include <mkl.h>
#include <hbwmalloc.h>


//implement scratch buffer on HBM and compute FFTs, refer instructions on Lab page
void runFFTs( const size_t fft_size, const size_t num_fft, MKL_Complex8 *data, DFTI_DESCRIPTOR_HANDLE *fftHandle) {

  MKL_Complex8* buff;
  hbw_posix_memalign((void**) &buff, 4096, sizeof(MKL_Complex8)*fft_size);

  for(size_t j = 0; j < num_fft; j++) {

#pragma omp parallel for
    for(size_t i = 0; i < fft_size; i++) {
      buff[i].real = data[(j * fft_size) + i].real;
      buff[i].imag = data[(j * fft_size) + i].imag;
    }
   
    DftiComputeForward (*fftHandle, &buff[0]);

#pragma omp parallel for
    for(size_t i = 0; i < fft_size; i++) {
      data[(j * fft_size) + i].real = buff[i].real;
      data[(j * fft_size) + i].imag = buff[i].imag;
    }
  }
  hbw_free(buff);
}

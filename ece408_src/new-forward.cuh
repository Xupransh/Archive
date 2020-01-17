
#ifndef MXNET_OPERATOR_NEW_FORWARD_CUH_
#define MXNET_OPERATOR_NEW_FORWARD_CUH_

#include <mxnet/base.h>

namespace mxnet
{
namespace op
{

# define TILE_WIDTH 16
# define CUDA_MAX_NUM_THREADS 1024


__global__ void kernel_fusion(const float * __restrict__ x, float*  y, const float * __restrict__  k,
            const int B, const int M, const int C, const int H, const int W, const int K, int W_grid)
{


    #define x4d(i3, i2, i1, i0) x[(i3) * (C * H * W) + (i2) * (H * W) + (i1) * (W) + i0]
    #define y4d(i3, i2, i1, i0) y[(i3) * (M * H_out * W_out) + (i2) * (H_out * W_out) + (i1) * (W_out) + i0]

    __shared__ float mask[TILE_WIDTH][TILE_WIDTH];
    __shared__ float unrolled[TILE_WIDTH][TILE_WIDTH];

    const int H_out = H - K + 1;
    const int W_out = W - K + 1;

    int bz = blockIdx.z;

    const int rowC = M;
    const int colC = H_out * W_out;
    const int width = C*K*K;


    int row = blockIdx.y * TILE_WIDTH + threadIdx.y;
    int col = blockIdx.x * TILE_WIDTH + threadIdx.x;

    float result = 0;
    int x_c, x_h, x_w, x_p, x_q, x_pq;

    #pragma unroll
    for(int tile = 0; tile < (width + TILE_WIDTH-1)/TILE_WIDTH; tile++) {
        if(tile*TILE_WIDTH + threadIdx.x < width && row < rowC) {
            mask[threadIdx.y][threadIdx.x] = k[row*width + tile*TILE_WIDTH+threadIdx.x];
        } else {
            mask[threadIdx.y][threadIdx.x] = 0;
        } if(tile*TILE_WIDTH + threadIdx.y < width && col < colC) {
            x_c = (tile*TILE_WIDTH+threadIdx.y)/(K*K);
            x_h = col/W_out;
            x_w = col%W_out;
            x_pq = (tile*TILE_WIDTH+threadIdx.y)%(K*K);
            x_p = x_pq/K;
            x_q = x_pq%K;
            unrolled[threadIdx.y][threadIdx.x] = x4d(bz, x_c, x_h + x_p, x_w + x_q);
        } else {
            unrolled[threadIdx.y][threadIdx.x] = 0.0;
        }

    __syncthreads();

    #pragma unroll
    for(int i = 0; i < TILE_WIDTH; i++) {
        result += (mask[threadIdx.y][i] * unrolled[i][threadIdx.x]);
    }
    __syncthreads();

    } if(row < rowC && col < colC) {
        y4d(bz, row, 0, col) = result;
    }

#undef x4d
#undef y4d

}

/*
   This function is called by new-inl.h
   Any code you write should be executed by this function.
   For ECE408, we only expect the float version of the operator to be called, so here we specialize with only floats.
*/
template <>
void forward<gpu, float>(mshadow::Tensor<gpu, 4, float> &y, const mshadow::Tensor<gpu, 4, float> &x, const mshadow::Tensor<gpu, 4, float> &w)
{


    // Extract the tensor dimensions into B,M,C,H,W,K
    // ...

    const int B = x.shape_[0];
    const int M = y.shape_[1];
    const int C = x.shape_[1];
    const int H = x.shape_[2];
    const int W = x.shape_[3];
    const int K = w.shape_[3];

    const int H_out = H - K + 1;
    const int W_out = W - K + 1;

    int W_grid = ceil(1.0*W_out/TILE_WIDTH);
    int H_grid = ceil(1.0*H_out/TILE_WIDTH);

    int H_unroll = H_out * W_out;

    dim3 dimBlock(TILE_WIDTH, TILE_WIDTH, 1.0);
    dim3 dimGrid(B, M, W_grid*H_grid);

    const float* kernel = w.dptr_;
    float hostKernel[M*C*K*K];
    size_t shmem = sizeof(float) *  (TILE_WIDTH + K-1)*(TILE_WIDTH + K-1);

    cudaMemcpy(hostKernel, kernel, M*C*K*K*sizeof(float), cudaMemcpyDeviceToHost );
    cudaMemcpyToSymbol(mask, hostKernel, M*C*K*K*sizeof(float));
    forward_kernel_shared<<<dimGrid, dimBlock, shmem>>>(y.dptr_,x.dptr_, B,M,C,H,W,K);


    // Use MSHADOW_CUDA_CALL to check for CUDA runtime errors.
    MSHADOW_CUDA_CALL(cudaDeviceSynchronize());

}



/*
   This tells mxnet how to do an op when it's not a float.
   This is not used in the ECE408 project
*/
template <typename gpu, typename DType>
void forward(mshadow::Tensor<gpu, 4, DType> &y, const mshadow::Tensor<gpu, 4, DType> &x, const mshadow::Tensor<gpu, 4, DType> &w)
{
   CHECK_EQ(0,1) << "Remove this line and replace it with your implementation.";
}
}
}

#endif

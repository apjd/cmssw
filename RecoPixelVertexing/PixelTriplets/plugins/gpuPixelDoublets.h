#ifndef RecoLocalTracker_SiPixelRecHits_plugins_gpuPixelDoublets_h
#define RecoLocalTracker_SiPixelRecHits_plugins_gpuPixelDoublets_h

#include "RecoPixelVertexing/PixelTriplets/plugins/gpuPixelDoubletsAlgos.h"

#define CONSTANT_VAR __constant__

namespace gpuPixelDoublets {

  using namespace gpuPixelDoubletsAlgos;

  constexpr int nPairs = 59;//13 + 2 + 4;
  static_assert(nPairs <= CAConstants::maxNumberOfLayerPairs());

  // start constants
  // clang-format off

/*
  CONSTANT_VAR const uint8_t layerPairs[2 * nPairs] = {

      0, 1, 0, 4, 0, 7,              // BPIX1 (3)
      1, 2, 1, 4, 1, 7,              // BPIX2 (5)
      4, 5, 7, 8,                    // FPIX1 (8)
      2, 3, 2, 4, 2, 7, 5, 6, 8, 9,  // BPIX3 & FPIX2 (13)
      0, 2, 1, 3,                    // Jumping Barrel (15)
      0, 5, 0, 8,                    // Jumping Forward (BPIX1,FPIX2)
      4, 6, 7, 9                     // Jumping Forward (19)
  };
*/

  
CONSTANT_VAR const uint8_t layerPairs[2 * nPairs] = {

    0, 1, 0, 4, 0, 16,             // BPIX1 (3)
    1, 2, 1, 4, 1, 16,             // BPIX2 (6)

    4, 5, 16, 17,                  // FPIXi (4*12+6) i = 1 - 12
    5, 6, 17, 18,
    6, 7, 18, 19,
    7, 8, 19, 20,
    8, 9, 20, 21,
    9, 10, 21, 22,
    10, 11, 22, 23,
    11, 12, 23, 24,
    12, 13, 24, 25,
    13, 14, 25, 26,
    14, 15, 26, 27,
    15, 16, 27, 28,

    2, 3, 2, 4, 2, 16,             // BPIX3 & FPIX2 (13)

    0, 2, 1, 3,                    // Jumping Barrel (15)
    0, 5, 0, 17,                   // Jumping Forward (BPIX1,FPIX2)

    4, 6, 16, 18,                  // Jumping Forward (19)
    5, 7, 17, 19,
    6, 8, 18, 20,
    7, 9, 19, 21,
    8, 10, 20, 22,
    9, 11, 21, 23,
    10, 12, 22, 24,
    11, 13, 23, 25,
    12, 14, 24, 26,
    13, 15, 25, 27,
    14, 16, 26, 28
};

  constexpr int16_t phi0p05 = 522;  // round(521.52189...) = phi2short(0.05);
  constexpr int16_t phi0p06 = 626;  // round(625.82270...) = phi2short(0.06);
  constexpr int16_t phi0p07 = 730;  // round(730.12648...) = phi2short(0.07);
/*
  CONSTANT_VAR const int16_t phicuts[nPairs]{phi0p05,
                                             phi0p07,
                                             phi0p07,
                                             phi0p05,
                                             phi0p06,
                                             phi0p06,
                                             phi0p05,
                                             phi0p05,
                                             phi0p06,
                                             phi0p06,
                                             phi0p06,
                                             phi0p05,
                                             phi0p05,
                                             phi0p05,
                                             phi0p05,
                                             phi0p05,
                                             phi0p05,
                                             phi0p05,
                                             phi0p05};
 */
 CONSTANT_VAR const int16_t phicuts[nPairs]{phi0p05, phi0p07, phi0p07,
                                           phi0p05, phi0p06, phi0p06,

                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,

                                           phi0p06, phi0p06, phi0p06,

                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05,
                                           phi0p05, phi0p05

                                         }; 
 //   phi0p07, phi0p07, phi0p06,phi0p06, phi0p06,phi0p06};  // relaxed cuts

  CONSTANT_VAR float const minz[nPairs] = {
      -20., 0., -30., -22., 10., -30., -70., -70., -22., 15., -30, -70., -70., -20., -22., 0, -30., -70., -70.};
  CONSTANT_VAR float const maxz[nPairs] = {
      20., 30., 0., 22., 30., -10., 70., 70., 22., 30., -15., 70., 70., 20., 22., 30., 0., 70., 70.};
  CONSTANT_VAR float const maxr[nPairs] = {
      20., 9., 9., 20., 7., 7., 5., 5., 20., 6., 6., 5., 5., 20., 20., 9., 9., 9., 9.};

  // end constants
  // clang-format on

  using CellNeighbors = CAConstants::CellNeighbors;
  using CellTracks = CAConstants::CellTracks;
  using CellNeighborsVector = CAConstants::CellNeighborsVector;
  using CellTracksVector = CAConstants::CellTracksVector;

  __global__ void initDoublets(GPUCACell::OuterHitOfCell* isOuterHitOfCell,
                               int nHits,
                               CellNeighborsVector* cellNeighbors,
                               CellNeighbors* cellNeighborsContainer,
                               CellTracksVector* cellTracks,
                               CellTracks* cellTracksContainer) {
    assert(isOuterHitOfCell);
    int first = blockIdx.x * blockDim.x + threadIdx.x;
    for (int i = first; i < nHits; i += gridDim.x * blockDim.x)
      isOuterHitOfCell[i].reset();
  }

  constexpr auto getDoubletsFromHistoMaxBlockSize = 64;  // for both x and y
  constexpr auto getDoubletsFromHistoMinBlocksPerMP = 16;

  __global__
#ifdef __CUDACC__
  __launch_bounds__(getDoubletsFromHistoMaxBlockSize, getDoubletsFromHistoMinBlocksPerMP)
#endif
      void getDoubletsFromHisto(GPUCACell* cells,
                                uint32_t* nCells,
                                CellNeighborsVector* cellNeighbors,
                                CellTracksVector* cellTracks,
                                TrackingRecHit2DSOAView const* __restrict__ hhp,
                                GPUCACell::OuterHitOfCell* isOuterHitOfCell,
                                int nActualPairs,
                                bool ideal_cond,
                                bool doClusterCut,
                                bool doZ0Cut,
                                bool doPtCut,
                                uint32_t maxNumOfDoublets) {
    auto const& __restrict__ hh = *hhp;
    doubletsFromHisto(layerPairs,
                      nActualPairs,
                      cells,
                      nCells,
                      cellNeighbors,
                      cellTracks,
                      hh,
                      isOuterHitOfCell,
                      phicuts,
                      minz,
                      maxz,
                      maxr,
                      ideal_cond,
                      doClusterCut,
                      doZ0Cut,
                      doPtCut,
                      maxNumOfDoublets);
  }

}  // namespace gpuPixelDoublets

#endif  // RecoLocalTracker_SiPixelRecHits_plugins_gpuPixelDouplets_h

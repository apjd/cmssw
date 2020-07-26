#ifndef RecoLocalTracker_SiPixelRecHits_plugins_gpuPixelDoublets_h
#define RecoLocalTracker_SiPixelRecHits_plugins_gpuPixelDoublets_h

#include "RecoPixelVertexing/PixelTriplets/plugins/gpuPixelDoubletsAlgos.h"

#define CONSTANT_VAR __constant__

namespace gpuPixelDoublets {

  constexpr int nPairs = 13 + 2 + 4;
  constexpr int nPairsPhase2 = 69;
  static_assert(nPairs <= CAConstants::maxNumberOfLayerPairs());

  // start constants
  // clang-format off

  CONSTANT_VAR const uint8_t layerPairs[2 * nPairs] = {
      0, 1, 0, 4, 0, 7,              // BPIX1 (3)
      1, 2, 1, 4, 1, 7,              // BPIX2 (5)
      4, 5, 7, 8,                    // FPIX1 (8)
      2, 3, 2, 4, 2, 7, 5, 6, 8, 9,  // BPIX3 & FPIX2 (13)
      0, 2, 1, 3,                    // Jumping Barrel (15)
      0, 5,
      0, 8,                    // Jumping Forward (BPIX1,FPIX2)
      4, 6, 7, 9                     // Jumping Forward (19)
  };

/*
  CONSTANT_VAR const uint8_t layerPairsPhase2[2 * nPairsPhase2] = {

      0, 1, 0, 4, 0, 16,             // BPIX1 (3)

      4, 5, 16, 17,                  // 5
      5, 6, 17, 18,                  // 7
      6, 7, 18, 19,                  // 9
      7, 8, 19, 20,                  // 11
      8, 9, 20, 21,                  // 13
      9, 10, 21, 22,                 // 15
      10, 11, 22, 23,                // 17

      1, 2, 1, 4, 1, 16,             // 20
      2, 3, 2, 4, 2, 16,             // 23

      11, 12, 23, 24,                // 25
      12, 13, 24, 25,                // 27
      13, 14, 25, 26,                // 29
      14, 15, 26, 27,                // 31

      0, 5, 0, 17,                   // 31
      1, 5, 1, 17,
      0, 6, 0, 18,                   // 35
      1, 6, 1, 18,
      0, 7, 0, 19,                   // 39
      1, 7, 1, 19,



      0, 2, 1, 3                     // 45
};
*/

CONSTANT_VAR const uint8_t layerPairsPhase2[2 * nPairsPhase2] = {

    0, 1, 0, 4, 0, 16,
    1, 2, 1, 4, 1, 16,
    4, 5, 16, 17,
    2, 3, 2, 4, 2, 16, 5, 6, 17, 18,
    0, 2, 1, 3,
    0, 5, 0, 17,
    4, 6, 17, 18,

    3, 4, 3, 16,

    //  Jumping Barrel to Forwad
    1, 5, 1, 17,
    2, 5, 2, 17,
    3, 5, 3, 17,


    4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, // right side
    16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, // left side


    5, 7, 7, 9, 9, 11, 11, 13, 13, 15,
    17, 19, 19, 21, 21, 23, 23, 25, 25, 27,

    4, 6, 6, 8, 8, 10, 10, 12, 12, 14, // jump right side
    16, 18, 18, 20, 20, 22, 22, 24, 24, 26 // jump left side

};


  constexpr int16_t phi0p05 = 522;  // round(521.52189...) = phi2short(0.05);
  constexpr int16_t phi0p06 = 626;  // round(625.82270...) = phi2short(0.06);
  constexpr int16_t phi0p07 = 730;  // round(730.12648...) = phi2short(0.07);
  constexpr int16_t phi0p09 = 960;  // round(730.12648...) = phi2short(0.07);

    CONSTANT_VAR const int16_t phicutsPhase2[nPairsPhase2]{
                                             phi0p06, phi0p06, phi0p06,

                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,

                                             phi0p06, phi0p06, phi0p06,
                                             phi0p06, phi0p06, phi0p06,

                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,

                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06,

                                             phi0p06, phi0p06,
                                             phi0p06, phi0p06

                                           };

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
  //   phi0p07, phi0p07, phi0p06,phi0p06, phi0p06,phi0p06};  // relaxed cuts

  CONSTANT_VAR float const minz[nPairs] = {
      -20.,  // _-_-_- 0 1
      0.,  // ____ | 0 4
      -30., // | ____ 0 7

      -22., // _-_-_- 1 2
      10., // _-_-_- | 1 4
      -30., // | _-_-_- 1 7


      -70., -70., // || 4 5 & 7 8 minz below min z for pixel tracker

      -22., 15.,  -30,

      -70., -70., -20., -22., 0, -30., -70., -70.};
  CONSTANT_VAR float const maxz[nPairs] = {
      20., 30., 0., 22., 30., -10., 70., 70., 22., 30., -15., 70., 70., 20., 22., 30., 0., 70., 70.};
  CONSTANT_VAR float const maxr[nPairs] = {
      20., 9., 9., 20., 7., 7., 5., 5., 20., 6., 6., 5., 5., 20., 20., 9., 9., 9., 9.};

    // CONSTANT_VAR float const maxzPhase2[nPairsPhase2] = {
    //   10, 20, -6, 25, 2, 32, 2, 41, 2, 53, 2, 67, 2, 86,
    //   2, 110, 2, 12, 20, -8, 15, 20, -11, 140, 2, 175,
    //   2, 201, 2, 2, 20, 2, 20, 2, 20, 2, 20, 2, 20, 2,
    //     20, 231, 2, 7, 9};
    //   //, 5, 71, 5, 90, 5, 114, 5, 144, 5, 179, 5, 205};
    //
    // CONSTANT_VAR float const minzPhase2[nPairsPhase2] = {
    //   -10, 6, -20, -2, -29, -2, -36, -2, -44, -2, -56,
    //   -2, -71, -2, -89, -2, -113, -12, 8, -20, -15, 11,
    //   -20, -2, -144, -2, -179, -2, -205, -20, -2, -20,
    //   -2, -20, -2, -20, -2, -20, -2, -20, -2, -2, -234,
    //   -7, -9};

      // -71, -5, -90, -5, -114, -5, -144,
      // -5, -179, -5, -205, -5};

    // CONSTANT_VAR float const maxrPhase2[nPairsPhase2] = {
    //   4.5, 6.5, 7.5, 14.5, 14.5, 14.5, 14.5, 14.5, 14.5,
    //   14.5, 14.5, 14.5, 14.5, 14.5, 14.5, 14.5, 14.5, 5.5,
    //   8.5, 10.5, 5.5, 10.5, 12.5, 23.5, 23.5, 20.5, 20.5,
    //   20.5, 20.5, 2.5, 2.5, 11.5, 11.5, 2.5, 2.5, 11.5,
    //   11.5, 2.5, 2.5, 11.5, 11.5, 20.5, 20.5, 8.5, 9.5};

    CONSTANT_VAR float const maxzPhase2[nPairsPhase2] = {
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.};
      //, 5, 71, 5, 90, 5, 114, 5, 144, 5, 179, 5, 205};

    CONSTANT_VAR float const minzPhase2[nPairsPhase2] = {
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.,
      -100000.,-100000.,-100000.,-100000.,-100000.};
    //
    //   // -71, -5, -90, -5, -114, -5, -144,
    //   // -5, -179, -5, -205, -5};
    //
    CONSTANT_VAR float const maxrPhase2[nPairsPhase2] = {
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.,
      100000., 100000., 100000., 100000., 100000.};

    // , 28.5, 28.5, 28.5,
    // 28.5, 42.0, 42.0, 42.0, 42.0, 37.5, 37.5, 37.5,
    // 37.5};
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
                                uint32_t maxNumOfDoublets, bool upgrade) {
    auto const& __restrict__ hh = *hhp;
    upgrade = true;
    if(!upgrade)
    {
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
                        maxNumOfDoublets,false);
     }else
     {
       doubletsFromHisto(layerPairsPhase2,
                         nActualPairs,
                         cells,
                         nCells,
                         cellNeighbors,
                         cellTracks,
                         hh,
                         isOuterHitOfCell,
                         phicutsPhase2,
                         minzPhase2,
                         maxzPhase2,
                         maxrPhase2,
                         ideal_cond,
                         false,
                         doZ0Cut,
                         doPtCut,
                         maxNumOfDoublets,true);
     }
  }

}  // namespace gpuPixelDoublets

#endif  // RecoLocalTracker_SiPixelRecHits_plugins_gpuPixelDouplets_h

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Modifier_tracker_apv_vfp30_2016_cff import tracker_apv_vfp30_2016 as _tracker_apv_vfp30_2016
from Configuration.Eras.Modifier_fastSim_cff import fastSim


hltPhase2L1TrackStepChi2Est = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltPhase2L1TrackStepChi2Est'),
    MaxChi2 = cms.double(30.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000000000),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('SiStripClusterChargeCutNone')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(15.0)
)

hltPhase2L1TrackStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CompositeTrajectoryFilter'),
    filters = cms.VPSet(
        cms.PSet(
            refToPSet_ = cms.string('hltPhase2L1TrackStepTrajectoryFilterBase')
        ),
        cms.PSet(
            refToPSet_ = cms.string('ClusterShapeTrajectoryFilter')
        )
    )
)

hltPhase2L1TrackStepTrajectoryFilterBase = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('SiStripClusterChargeCutNone')
    ),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.2),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

hltPhase2L1TrackStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    MeasurementTrackerName = cms.string(''),
    TTRHBuilder = cms.string('WithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltPhase2L1TrackStepChi2Est'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('CkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterial'),
    propagatorOpposite = cms.string('PropagatorWithMaterialOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(True), #try this?
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('hltPhase2L1TrackStepTrajectoryFilter')
    ),
    updator = cms.string('KFUpdator'),
    useSameTrajFilter = cms.bool(False)
)

hltPhase2L1TrackRegionalStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    minimumNumberOfHits = cms.int32(2),
    seedPairPenalty = cms.int32(0),
    chargeSignificance = cms.double(-1.0),
    minPt = cms.double(1.8),
    nSigmaMinPt = cms.double(5.0),
    minHitsMinPt = cms.int32(2),
    maxLostHits = cms.int32(999),
    maxConsecLostHits = cms.int32(2),
    maxNumberOfHits = cms.int32(100),

    maxLostHitsFraction = cms.double(1.1),
    constantValueForLostHitsFractionFilter = cms.double(2.),

    seedExtension = cms.int32(0),
    strictSeedExtension = cms.bool(False),
    pixelSeedExtension = cms.bool(False),

    minNumberOfHitsForLoopers           = cms.int32(13),
    minNumberOfHitsPerLoop              = cms.int32(4),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),

    maxCCCLostHits = cms.int32(9999),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('SiStripClusterChargeCutNone')
    ),
)

hltPhase2L1TrackRegionalStepTrajectoryBuilder =  cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    bestHitOnly = cms.bool(True),
    propagatorAlong = cms.string('PropagatorWithMaterial'),
    propagatorOpposite = cms.string('PropagatorWithMaterialOpposite'),
    trajectoryFilter = cms.PSet(refToPSet_ = cms.string('hltPhase2L1TrackRegionalStepTrajectoryFilter')),
    inOutTrajectoryFilter = cms.PSet(refToPSet_ = cms.string('CkfBaseTrajectoryFilter_block')),
    # If true, then the inOutTrajectoryFilter will be ignored
    # and the trajectoryFilter will be used for in-out tracking too.
    useSameTrajFilter = cms.bool(True),
    # Maximum number of track candidates followed at each step of
    # track building
    maxCand = cms.int32(50),
    intermediateCleaning = cms.bool(True),
    # Chi2 added to track candidate if no hit found in layer
    lostHitPenalty = cms.double(30.0),
    foundHitBonus = cms.double(10.0),
    MeasurementTrackerName = cms.string(''),
    lockHits = cms.bool(False), #What does this do?
    TTRHBuilder = cms.string('WithTrackAngle'),
    updator = cms.string('KFUpdator'),
    # If true, track building will allow for possibility of no hit
    # in a given layer, even if it finds compatible hits there.
    alwaysUseInvalidHits = cms.bool(True),
    requireSeedHitsInRebuild = cms.bool(False), #(?)
    keepOriginalIfRebuildFails = cms.bool(True), #(?)
    estimator = cms.string('hltPhase2L1TrackStepChi2Est'),
    # Out-in tracking will not be attempted unless this many hits
    # are on track after in-out tracking phase.
    minNrOfHitsForRebuild = cms.int32(5),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0),
    seedAs5DHit = cms.bool(False) #?
)

hltPhase2L1TrackSeedsFromL1Tracks = cms.EDProducer("SeedGeneratorFromTTracksEDProducer",
    InputCollection = cms.InputTag("TTTracksFromTracklet", "Level1TTTracks"),
    estimator = cms.string('hltPhase2L1TrackStepChi2Est'),
    propagator = cms.string('PropagatorWithMaterial'),
    MeasurementTrackerEvent = cms.InputTag("MeasurementTrackerEvent"),
    maxEtaForTOB = cms.double(1.2),
    minEtaForTEC = cms.double(0.8),
    # for testing
    TrajectoryBuilder = cms.string('GroupedCkfTrajectoryBuilder'),
    TrajectoryBuilderPSet = cms.PSet( refToPSet_ = cms.string('hltPhase2L1TrackRegionalStepTrajectoryBuilder'))
)

hltPhase2L1TrackCandidatesCustom= cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("MeasurementTrackerEvent"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    # During tracking, eliminate seeds used by an already found track
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    # Decide how to eliminate tracks sharing hits at end of tracking phase
    TrajectoryCleaner = cms.string('TrajectoryCleanerBySharedHits'),
    # Run cleaning after in-out tracking in addition to at end of tracking ?
    cleanTrajectoryAfterInOut = cms.bool(True),
    reverseTrajectories  =cms.bool(False),
    # Split matched strip tracker hits into mono/stereo components.
    useHitsSplitting = cms.bool(True),
    # After in-out tracking, do out-in tracking through the seeding
    # region and then further in.
    doSeedingRegionRebuilding = cms.bool(True),
    # Seed Producer
    maxNSeeds = cms.uint32(500000),
    maxSeedsBeforeCleaning = cms.uint32(10000),
    SimpleMagneticField = cms.string(''),
    src = cms.InputTag('hltPhase2L1TrackSeedsFromL1Tracks'),
    alias = cms.string('hltPhase2L1CtfTrackCandidatesCustom'),
    TrajectoryBuilder = cms.string('GroupedCkfTrajectoryBuilder'),
    TrajectoryBuilderPSet = cms.PSet( refToPSet_ = cms.string('hltPhase2L1TrackRegionalStepTrajectoryBuilder')),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterial'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialOpposite')
    ),
)

hltPhase2L1CtfTracks = cms.EDProducer( "TrackProducer",
    AlgorithmName = cms.string('hltPhase2L1CtfTracks'),
    Fitter = cms.string('FlexibleKFFittingSmoother'),
    GeometricInnerState = cms.bool(False),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag( "MeasurementTrackerEvent"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    Propagator = cms.string('RungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string(''),
    TTRHBuilder = cms.string('WithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('hltPhase2L1CtfTracks'),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltPhase2L1TrackCandidatesCustom"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(False)
)


#hltPhase2L1TracksSequence = cms.Sequence(
#
#)

#vertices
from RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi import offlinePrimaryVertices as _offlinePrimaryVertices
l1TrackStepsPrimaryVerticesUnsorted = _offlinePrimaryVertices.clone()
l1TrackStepsPrimaryVerticesUnsorted.TrackLabel = cms.InputTag("hltPhase2L1CtfTracks")
l1TrackStepsPrimaryVerticesUnsorted.vertexCollections = [_offlinePrimaryVertices.vertexCollections[0].clone()]


# we need a replacment for the l1TrackStepsPrimaryVerticesUnsorted
# that includes tracker information of signal and pile up
# after mixing there is no such thing as initialStepTracks,
# so we replace the input collection for l1TrackStepsPrimaryVerticesUnsorted with generalTracks
l1TrackStepsPrimaryVerticesBeforeMixing =  l1TrackStepsPrimaryVerticesUnsorted.clone()


from RecoJets.JetProducers.TracksForJets_cff import trackRefsForJets
l1TrackRefsForJets = trackRefsForJets.clone(src = cms.InputTag('hltPhase2L1CtfTracks'))

from RecoJets.JetProducers.caloJetsForTrk_cff import *
from CommonTools.RecoAlgos.sortedPrimaryVertices_cfi import sortedPrimaryVertices as _sortedPrimaryVertices
l1TrackStepsPrimaryVertices = _sortedPrimaryVertices.clone(
    vertices = "l1TrackStepsPrimaryVerticesUnsorted",
    particles = "l1TrackRefsForJets",
)


# Final selection
from RecoTracker.FinalTrackSelectors.TrackMVAClassifierPrompt_cfi import *
from RecoTracker.FinalTrackSelectors.TrackMVAClassifierDetached_cfi import *

l1TracksClassifier = TrackMVAClassifierPrompt.clone()
l1TracksClassifier.src = 'hltPhase2L1CtfTracks'
l1TracksClassifier.mva.GBRForestLabel = 'MVASelectorIter0_13TeV'
l1TracksClassifier.qualityCuts = [-0.9,-0.8,-0.7]

from RecoTracker.IterativeTracking.DetachedTripletStep_cff import detachedTripletStepClassifier1
from RecoTracker.IterativeTracking.LowPtTripletStep_cff import lowPtTripletStep



from RecoTracker.FinalTrackSelectors.ClassifierMerger_cfi import *
l1Step = ClassifierMerger.clone()
l1Step.inputClassifiers=['l1TracksClassifier']

# For LowPU and Phase2PU140
import RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi
l1TracksSelector = RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.multiTrackSelector.clone(
    src = 'hltPhase2L1CtfTracks',
    useAnyMVA = cms.bool(False),
    GBRForestLabel = cms.string('MVASelectorIter0'),
    trackSelectors = [
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.looseMTS.clone(
            name = 'l1StepLoose',
        ), #end of pset
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.tightMTS.clone(
            name = 'l1StepTight',
            preFilterName = 'l1StepLoose',
        ),
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.highpurityMTS.clone(
            name = 'QualityMasks',
            preFilterName = 'l1StepTight',
        ),
    ] #end of vpset
) #end of clone
trackingPhase2PU140.toModify(l1TracksSelector,
    useAnyMVA = None,
    GBRForestLabel = None,
    trackSelectors= cms.VPSet(
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.looseMTS.clone(
            name = 'l1StepLoose',
            chi2n_par = 2.0,
            res_par = ( 0.003, 0.002 ),
            minNumberLayers = 3,
            maxNumberLostLayers = 3,
            minNumber3DLayers = 3,
            d0_par1 = ( 0.8, 4.0 ),
            dz_par1 = ( 0.9, 4.0 ),
            d0_par2 = ( 0.6, 4.0 ),
            dz_par2 = ( 0.8, 4.0 )
            ), #end of pset
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.tightMTS.clone(
            name = 'l1StepTight',
            preFilterName = 'l1StepLoose',
            chi2n_par = 1.4,
            res_par = ( 0.003, 0.002 ),
            minNumberLayers = 3,
            maxNumberLostLayers = 2,
            minNumber3DLayers = 3,
            d0_par1 = ( 0.7, 4.0 ),
            dz_par1 = ( 0.8, 4.0 ),
            d0_par2 = ( 0.5, 4.0 ),
            dz_par2 = ( 0.7, 4.0 )
            ),
        RecoTracker.FinalTrackSelectors.multiTrackSelector_cfi.highpurityMTS.clone(
            name = 'l1Step',
            preFilterName = 'l1StepTight',
            min_eta = -4.1,
            max_eta = 4.1,
            chi2n_par = 1.2,
            res_par = ( 0.003, 0.001 ),
            minNumberLayers = 3,
            maxNumberLostLayers = 2,
            minNumber3DLayers = 3,
            d0_par1 = ( 0.6, 4.0 ),
            dz_par1 = ( 0.7, 4.0 ),
            d0_par2 = ( 0.45, 4.0 ),
            dz_par2 = ( 0.55, 4.0 )
            ),
        ), #end of vpset
) #end of clone



# Final sequence
L1StepTask = cms.Task(
                           hltPhase2L1TrackSeedsFromL1Tracks,
                           hltPhase2L1TrackCandidatesCustom,
                           hltPhase2L1CtfTracks,
                           l1TrackStepsPrimaryVerticesUnsorted,
                           l1TrackRefsForJets,
                           l1TrackStepsPrimaryVertices,
                           l1TracksClassifier1,
                           l1Step,caloJetsForTrkTask)

L1Step = cms.Sequence(l1TracksStepTask)

_L1StepTask_trackingPhase2 = L1StepTask.copyAndExclude([l1TracksClassifier])
_L1StepTask_trackingPhase2.replace(l1Step, l1TracksSelector)
trackingPhase2PU140.toReplaceWith(L1StepTask, _L1StepTask_trackingPhase2)

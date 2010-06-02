/* $Header: /home/cvs/bp/oofem/oofemlib/src/inputrecord.h,v 1.4 2003/05/19 13:03:57 bp Exp $ */
/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2008   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


//
// Class stringReader
//

#ifndef inputrecord_h
#define inputrecord_h


#include "intarray.h"
#include "flotarry.h"
#include "dictionr.h"
#include "dynalist.h"
#include "range.h"

#ifndef __MAKEDEPEND
 #include <stdio.h>
 #include <string.h>
#endif

namespace oofem {

/**
 * Type defining the return values of InputRecord reading operations.
 * IRRT_OK the corresponding value to given keyword was successfully read.
 *       the answer parameter contains the value.
 * IRRT_NOTFOUND the keyword is not found; the answer is not modified
 * IRRT_BAD_FORMAT the keyword was found but the record is not correctly formated.
 */
enum IRResultType { IRRT_OK = 0, IRRT_NOTFOUND, IRRT_BAD_FORMAT };

/**
 * Enumeration type used to determine particular field in record
 */
enum InputFieldType {
    IFT_RecordIDField,
    IFT_EngngModel_nsteps,
    IFT_EngngModel_contextoutputstep,
    IFT_EngngModel_renumberflag,
    IFT_EngngModel_nmsteps,
    IFT_EngngModel_parallelflag,
    IFT_EngngModel_outfile,
    IFT_EngngModel_probname,
    IFT_EngngModel_probdescription,
    IFT_EngngModel_nxfemman,
    IFT_EngngModel_nonLinFormulation,

    IFT_MetaStep_nsteps,

    IFT_ExportModuleManager_nmodules,
    IFT_InitModuleManager_nmodules,

    IFT_ExportModule_tstepall,
    IFT_ExportModule_tstepstep,
    IFT_ExportModule_tstepsout,
    IFT_ExportModule_domainall,
    IFT_ExportModule_domainmask,

    IFT_VTKExportModule_cellvars,
    IFT_VTKExportModule_vars,
    IFT_VTKExportModule_primvars,
    IFT_VTKExportModule_stype,
    IFT_VTKExportModule_regionstoskip,

    IFT_VTKXMLExportModule_vars,
    IFT_VTKXMLExportModule_primvars,
    IFT_VTKXMLExportModule_stype,
    IFT_VTKXMLExportModule_regionstoskip,

    IFT_POIExportModule_vars,
    IFT_POIExportModule_primvars,
    IFT_POIExportModule_mtype,
    IFT_POIExportModule_poifilename,

    IFT_HOMExportModule_scale,
    IFT_HOMExportModule_matnum,

    IFT_IncrementalLinearStatic_endoftimeofinterest,
    IFT_IncrementalLinearStatic_prescribedtimes,
    IFT_IncrementalLinearStatic_lstype,
    IFT_IncrementalLinearStatic_smtype,

    IFT_DEIDynamic_dumpcoef,
    IFT_DEIDynamic_deltat,

    IFT_DIIDynamic_deltat,
    IFT_DIIDynamic_alpha,
    IFT_DIIDynamic_beta,
    IFT_DIIDynamic_psi,

    IFT_NlDEIDynamic_dumpcoef,
    IFT_NlDEIDynamic_deltat,
    IFT_NlDEIDynamic_drflag,
    IFT_NlDEIDynamic_tau,
    IFT_NlDEIDynamic_py,

    IFT_NonLinearStatic_controllmode,
    IFT_NonLinearStatic_deltat,
    IFT_NonLinearStatic_rtolv,
    IFT_NonLinearStatic_stiffmode,
    IFT_NonLinearStatic_refloadmode,
    IFT_NonLinearStatic_keepll,
    IFT_NonLinearStatic_donotfixload,
    IFT_NonLinearStatic_nonlocstiff,
    IFT_NonLinearStatic_nonlocalext,
    IFT_NonLinearStatic_loadBalancingFlag,
    IFT_NonLinearStatic_forceloadBalancingFlag,

    IFT_EigenValueDynamic_nroot,
    IFT_EigenValueDynamic_rtolv,
    IFT_EigenValueDynamic_stype,
    IFT_EigenValueDynamic_smtype,

    IFT_LinearStability_nroot,
    IFT_LinearStability_rtolv,
    IFT_LinearStability_stype,

    IFT_PNlDEIDynamic_dumpcoef,
    IFT_PNlDEIDynamic_deltat,
    IFT_PNlDEIDynamic_drflag,
    IFT_PNlDEIDynamic_tau,
    IFT_PNlDEIDynamic_py,
    IFT_PNlDEIDynamic_nodecutmode,
    IFT_PNlDEIDynamic_elementcutmode,
    IFT_PNlDEIDynamic_nonlocalext,

    IFT_LinearStatic_lstype,
    IFT_LinearStatic_smtype,

    IFT_AdaptiveLinearStatic_eetype,
    IFT_AdaptiveLinearStatic_meshpackage,

    IFT_AdaptiveNonLinearStatic_eetype,
    IFT_AdaptiveNonLinearStatic_meshpackage,
    IFT_AdaptiveNonLinearStatic_equilmc,
    IFT_AdaptiveNonLinearStatic_controllmode,
    IFT_AdaptiveNonLinearStatic_ddm,
    IFT_AdaptiveNonLinearStatic_refloadmode,
    IFT_AdaptiveNonLinearStatic_preMappingLoadBalancingFlag,

    IFT_StationaryTransportProblem_lstype,
    IFT_StationaryTransportProblem_smtype,
    IFT_StationaryTransportProblem_exportfields,
    IFT_StationaryTransportProblem_atomicfields,

    IFT_NonStationaryTransportProblem_lstype,
    IFT_NonStationaryTransportProblem_smtype,
    IFT_NonStationaryTransportProblem_deltat,
    IFT_NonStationaryTransportProblem_dtf,
    IFT_NonStationaryTransportProblem_alpha,
    IFT_NonStationaryTransportProblem_lumpedcapa,
    IFT_NonStationaryTransportProblem_exportfields,
    IFT_NonStationaryTransportProblem_atomicfields,

    IFT_NLTransientTransportProblem_nsmax,
    IFT_NLTransientTransportProblem_rtol,
    IFT_NLTransientTransportProblem_manrmsteps,

    IFT_StaggeredProblem_deltat,
    IFT_StaggeredProblem_dtf,
    IFT_StaggeredProblem_stepmultiplier,
    IFT_StaggeredProblem_prob1,
    IFT_StaggeredProblem_prob2,

    IFT_CBS_lstype,
    IFT_CBS_smtype,
    IFT_CBS_deltat,
    IFT_CBS_mindeltat,
    IFT_CBS_cmflag,
    IFT_CBS_theta1,
    IFT_CBS_theta2,
    IFT_CBS_scaleflag,
    IFT_CBS_lscale,
    IFT_CBS_uscale,
    IFT_CBS_dscale,
    IFT_CBS_miflag,

    IFT_SUPG_lstype,
    IFT_SUPG_smtype,
    IFT_SUPG_deltat,
    IFT_SUPG_deltatltf,
    IFT_SUPG_cmflag,
    IFT_SUPG_alpha,
    IFT_SUPG_scaleflag,
    IFT_SUPG_lscale,
    IFT_SUPG_uscale,
    IFT_SUPG_dscale,
    IFT_SUPG_miflag,
    IFT_SUPG_rtolv,
    IFT_SUPG_atolv,
    IFT_SUPG_maxiter,
    IFT_SUPG_stopmaxiter,
    IFT_SUPG_fsflag,
    IFT_SUPG_renumberflag,

    IFT_CylindricalALM_psi,
    IFT_CylindricalALM_maxiter,
    IFT_CylindricalALM_minsteplength,
    IFT_CylindricalALM_steplength,
    IFT_CylindricalALM_initialsteplength,
    IFT_CylindricalALM_reqiterations,
    IFT_CylindricalALM_miniterations,
    IFT_CylindricalALM_manrmsteps,
    IFT_CylindricalALM_hpcmode,
    IFT_CylindricalALM_hpc,
    IFT_CylindricalALM_hpcw,
    IFT_CylindricalALM_lstype,
    IFT_CylindricalALM_linesearch,
    IFT_CylindricalALM_lsearchtol,
    IFT_CylindricalALM_lsearchamp,
    IFT_CylindricalALM_lsearchmaxeta,
    IFT_CylindricalALM_nccdg,
    IFT_CylindricalALM_ccdg,
    IFT_CylindricalALM_rtolv,
    IFT_CylindricalALM_rtolf,
    IFT_CylindricalALM_rtold,


    IFT_NRSolver_maxiter,
    IFT_NRSolver_miniterations,
    IFT_NRSolver_minsteplength,
    IFT_NRSolver_manrmsteps,
    IFT_NRSolver_lstype,
    IFT_NRSolver_ddm,
    IFT_NRSolver_ddv,
    IFT_NRSolver_ddltf,
    IFT_NRSolver_linesearch,
    IFT_NRSolver_nccdg,
    IFT_NRSolver_ccdg,
    IFT_NRSolver_rtolv,
    IFT_NRSolver_rtolf,
    IFT_NRSolver_rtold,

    IFT_LineSearchNM_lsearchtol,
    IFT_LineSearchNM_lsearchamp,
    IFT_LineSearchNM_lsearchmaxeta,

    IFT_SpoolesSolver_msglvl,
    IFT_SpoolesSolver_msgfile,

    IFT_IMLSolver_lstype,
    IFT_IMLSolver_lstol,
    IFT_IMLSolver_lsiter,
    IFT_IMLSolver_lsprecond,

    IFT_FETISolver_maxiter,
    IFT_FETISolver_maxerr,
    IFT_FETISolver_limit,
    IFT_FETISolver_energynormflag,

    IFT_GeneralBoundaryCondition_LoadTimeFunct,
    IFT_BoundaryCondition_IsImposedTimeFunct,
    IFT_BoundaryCondition_PrescribedValue,
    IFT_GeneralBoundaryCondition_valType,

    IFT_Load_components,
    IFT_Load_dofexcludemask,
    IFT_BoundaryLoad_ndofs,
    IFT_BoundaryLoad_loadtype,
    IFT_BoundaryLoad_cstype,
    IFT_BoundaryLoad_properties,
    IFT_LinearEdgeLoad_formulation,
    IFT_LinearEdgeLoad_startcoord,
    IFT_LinearEdgeLoad_endcoord,
    IFT_PointLoad_ndofs,
    IFT_PointLoad_coords,
    IFT_PointLoad_loadtype,
    IFT_PointLoad_cstype,

    IFT_InitialCondition_conditions,

    IFT_LoadTimeFunction_initialvalue,
    IFT_LoadTimeFunction_ft,
    IFT_Domain_type,
    IFT_Domain_ndofman,
    IFT_Domain_nelem,
    IFT_Domain_nmat,
    IFT_Domain_ncrosssect,
    IFT_Domain_nbc,
    IFT_Domain_nic,
    IFT_Domain_nloadtimefunct,
    IFT_Domain_nbarrier,
    IFT_Domain_nrfg,

    IFT_DofManager_ndofs,
    IFT_DofManager_dofidmask,
    IFT_DofManager_load,
    IFT_DofManager_bc,
    IFT_DofManager_ic,
    IFT_DofManager_mastermask,
    IFT_DofManager_doftypemask,
    IFT_DofManager_boundaryflag,
    IFT_DofManager_globnum,
    IFT_DofManager_partitions,
    IFT_DofManager_sharedflag,
    IFT_DofManager_remoteflag,
    IFT_DofManager_nullflag,

    IFT_Node_coords,
    IFT_Node_lcs,
    IFT_Particle_rad,
    IFT_RigidArmNode_coords,
    IFT_RigidArmNode_master,
    IFT_RigidArmNode_load,
    IFT_RigidArmNode_bc,
    IFT_RigidArmNode_ic,
    IFT_RigidArmNode_mastermask,
    IFT_RigidArmNode_lcs,
    IFT_RigidArmNode_globnum,
    IFT_RigidArmNode_partitions,
    IFT_RigidArmNode_shared,
    IFT_RigidArmNode_remote,
    IFT_RigidArmNode_null,

    IFT_HangingNode_type,
    IFT_HangingNode_masters,
    IFT_HangingNode_weigths,
    IFT_HangingNode_ksi,
    IFT_HangingNode_eta,
    IFT_HangingNode_dzeta,

    IFT_Element_mat,
    IFT_Element_crosssect,
    IFT_Element_nodes,
    IFT_Element_sides,
    IFT_Element_bodyload,
    IFT_Element_boundaryload,
    IFT_Element_lcs,
    IFT_Element_globnum,
    IFT_Element_partitions,
    IFT_Element_remote,

    IFT_StructuralElement_activityltf,

    IFT_CBSElement_bsides,
    IFT_CBSElement_bcodes,

    IFT_SUPGElement_bsides,
    IFT_SUPGElement_bcodes,


    IFT_NLStructuralElement_nlgeoflag,

    IFT_Axisymm3d_nip,
    IFT_Axisymm3d_nipfish,
    IFT_CCTPlate_nip,
    IFT_LSpace_nip,
    IFT_LTrElementPPDE_nip,
    IFT_L4Axisymm_nip,
    IFT_PlaneStress2d_nip,
    IFT_Quad1PlaneStrain_nip,
    IFT_RerShell_nip,
    IFT_QPlaneStress2d_nip,
    IFT_QSpace_nip,
    IFT_QTrPlaneStress2d_nip,
    IFT_Q4Axisymm_nip,
    IFT_Q4Axisymm_nipfish,
    IFT_TrPlaneStress2d_nip,
    IFT_TrPlaneStrRot_nip,
    IFT_TrPlaneStrRot_niprot,
    IFT_LTRSpace_nip,
    IFT_Beam2d_dofstocondense,
    IFT_Beam3d_refnode,
    IFT_Beam3d_dofstocondense,
    IFT_LIBeam3dNL_refnode,
    IFT_TrPlaneStrain_nip,
    IFT_LIBeam3dNL2_refnode,
    IFT_LIBeam3d_refnode,
    IFT_LIBeam3d2_refnode,
    IFT_Truss2d_cs,

    IFT_Quad1_ht_nip,
    IFT_Brick1_ht_nip,
    IFT_Tetrah1_ht_nip,

    IFT_TR12DCBS_vof,
    IFT_TR12DCBS_pvof,

    IFT_TR12DSUPG_pvof,
    IFT_TR12DSUPG_vof,
    IFT_TR12DSUPG2_mat0,
    IFT_TR12DSUPG2_mat1,

    IFT_SimpleCrossSection_thick,
    IFT_SimpleCrossSection_width,
    IFT_SimpleCrossSection_area,
    IFT_SimpleCrossSection_iy, // Inertia moment y
    IFT_SimpleCrossSection_iz, // Inertia moment z
    IFT_SimpleCrossSection_ik, // Torsion moment x
    IFT_SimpleCrossSection_shearcoeff,

    IFT_HeatCrossSection_thick,
    IFT_HeatCrossSection_width,

    IFT_LayeredCrossSection_nlayers,
    IFT_LayeredCrossSection_layermaterials,
    IFT_LayeredCrossSection_thicks,
    IFT_LayeredCrossSection_widths,
    IFT_LayeredCrossSection_midsurf,

    IFT_FiberedCrossSection_nfibers,
    IFT_FiberedCrossSection_fibermaterials,
    IFT_FiberedCrossSection_thicks,
    IFT_FiberedCrossSection_widths,
    IFT_FiberedCrossSection_fiberycentrecoords,
    IFT_FiberedCrossSection_fiberzcentrecoords,
    IFT_FiberedCrossSection_thick,
    IFT_FiberedCrossSection_width,

    IFT_Material_density,
    IFT_Material_castingtime,
    IFT_StructuralMaterial_referencetemperature,
    IFT_IsotropicLinearElasticMaterial_e,
    IFT_IsotropicLinearElasticMaterial_n,
    IFT_IsotropicLinearElasticMaterial_talpha,

    IFT_IsotropicLinearHeatMaterial_k, // conductivity
    IFT_IsotropicLinearHeatMaterial_c, // specific heat

    IFT_IsotropicHeatTransferMaterial_k,
    IFT_IsotropicHeatTransferMaterial_c,

    IFT_HeMoTKMaterial_a_0,
    IFT_HeMoTKMaterial_nn,
    IFT_HeMoTKMaterial_phi_c,
    IFT_HeMoTKMaterial_delta_wet,
    IFT_HeMoTKMaterial_w_h,
    IFT_HeMoTKMaterial_n,
    IFT_HeMoTKMaterial_a,
    IFT_HeMoTKMaterial_latent,
    IFT_HeMoTKMaterial_c,
    IFT_HeMoTKMaterial_rho,
    IFT_HeMoTKMaterial_chi_eff,
    IFT_HeMoTKMaterial_por,
    IFT_HeMoTKMaterial_rho_gws,


    IFT_B3Material_mode,
    IFT_B3Material_emodulimode,
    IFT_B3Material_fc,
    IFT_B3Material_cc,
    IFT_B3Material_wc,
    IFT_B3Material_ac,
    IFT_B3Material_t0,
    IFT_B3Material_shmode,
    IFT_B3Material_es0,
    IFT_B3Material_r,
    IFT_B3Material_rprime,
    IFT_B3Material_at,
    IFT_B3Material_wh,
    IFT_B3Material_ncoeff,
    IFT_B3Material_a,
    IFT_B3Material_alpha1,
    IFT_B3Material_alpha2,
    IFT_B3Material_ks,
    IFT_B3Material_hum,
    IFT_B3Material_vs,
    IFT_B3Material_talpha,
    IFT_B3Material_q1,
    IFT_B3Material_q2,
    IFT_B3Material_q3,
    IFT_B3Material_q4,
    IFT_B3Material_q5,
    IFT_B3Material_kt,
    IFT_B3Material_EpsSinf,
    IFT_B3Material_microprestress,
    IFT_B3Material_c0,
    IFT_B3Material_c1,
    IFT_B3Material_ksh,
    IFT_B3Material_ts0,
    IFT_B3Material_finalhumidity,
    IFT_B3Material_initialhumidity,

    IFT_CebFip78Material_e28,
    IFT_CebFip78Material_fibf,
    IFT_CebFip78Material_kap_a,
    IFT_CebFip78Material_kap_c,
    IFT_CebFip78Material_kap_tt,
    IFT_CebFip78Material_u,

    IFT_Concrete2_e,
    IFT_Concrete2_n,
    IFT_Concrete2_sccc,
    IFT_Concrete2_scct,
    IFT_Concrete2_epp,
    IFT_Concrete2_epu,
    IFT_Concrete2_eopp,
    IFT_Concrete2_eopu,
    IFT_Concrete2_sheartol,
    IFT_Concrete2_is_plastic_flow,
    IFT_Concrete2_ifad,
    IFT_Concrete2_stirr_e,
    IFT_Concrete2_stirr_ft,
    IFT_Concrete2_stirr_a,
    IFT_Concrete2_stirr_tol,
    IFT_Concrete2_stirr_eref,
    IFT_Concrete2_stirr_lambda,

    IFT_Concrete3_exp_soft,

    IFT_DoublePowerLawMaterial_e28,
    IFT_DoublePowerLawMaterial_fi1,
    IFT_DoublePowerLawMaterial_m,
    IFT_DoublePowerLawMaterial_n,
    IFT_DoublePowerLawMaterial_alpha,

    IFT_RheoChainMaterial_n,
    IFT_RheoChainMaterial_relmatage,
    IFT_RheoChainMaterial_begoftimeofinterest,
    IFT_RheoChainMaterial_endoftimeofinterest,
    IFT_RheoChainMaterial_timefactor,

    IFT_OrthotropicLinearElasticMaterial_ex,
    IFT_OrthotropicLinearElasticMaterial_ey,
    IFT_OrthotropicLinearElasticMaterial_ez,
    IFT_OrthotropicLinearElasticMaterial_nyyz,
    IFT_OrthotropicLinearElasticMaterial_nyxz,
    IFT_OrthotropicLinearElasticMaterial_nyxy,
    IFT_OrthotropicLinearElasticMaterial_gyz,
    IFT_OrthotropicLinearElasticMaterial_gxz,
    IFT_OrthotropicLinearElasticMaterial_gxy,
    IFT_OrthotropicLinearElasticMaterial_talphax,
    IFT_OrthotropicLinearElasticMaterial_talphay,
    IFT_OrthotropicLinearElasticMaterial_talphaz,
    IFT_OrthotropicLinearElasticMaterial_lcs,
    IFT_OrthotropicLinearElasticMaterial_scs,

    IFT_RCM2Material_gf,
    IFT_RCM2Material_ft,

    IFT_RCSDMaterial_sdtransitioncoeff,
    IFT_RCSDEMaterial_sdtransitioncoeff,
    IFT_RCSDNLMaterial_ft,
    IFT_RCSDNLMaterial_sdtransitioncoeff,
    IFT_RCSDNLMaterial_sdtransitioncoeff2,
    IFT_RCSDNLMaterial_r,
    IFT_RCSDNLMaterial_ef,
    IFT_RCSDNLMaterial_gf,

    IFT_MicroplaneMaterial_nmp,

    IFT_M4Material_c3,
    IFT_M4Material_c4,
    IFT_M4Material_c20,
    IFT_M4Material_k1,
    IFT_M4Material_k2,
    IFT_M4Material_k3,
    IFT_M4Material_k4,
    IFT_M4Material_e,
    IFT_M4Material_n,
    IFT_M4Material_talpha,

    IFT_IsotropicDamageMaterial_talpha,
    IFT_IsotropicDamageMaterial_maxOmega,

    IFT_IsotropicDamageMaterial1_e0,
    IFT_IsotropicDamageMaterial1_ef,
    IFT_IsotropicDamageMaterial1_equivstraintype,

    IFT_IsotropicDamageMaterial2_eps0,
    IFT_IsotropicDamageMaterial2_epsk,
    IFT_IsotropicDamageMaterial2_gf,
    IFT_IsotropicDamageMaterial2_gft,
    IFT_IsotropicDamageMaterial2_softeningtype,

    IFT_CompoDamageMat_ex,
    IFT_CompoDamageMat_ez,
    IFT_CompoDamageMat_nyxy,
    IFT_CompoDamageMat_nyyz,
    IFT_CompoDamageMat_Gxy,
    IFT_CompoDamageMat_components,
    IFT_CompoDamageMat_afteriter,
    IFT_CompoDamageMat_allowSnapBack,

    IFT_MicroMaterialFileName,
    IFT_MacroLspace_microMasterNodes,
    IFT_MacroLspace_microBoundaryNodes,
    IFT_MacroLspace_stiffMatrxFileName,

    IFT_IDNLMaterial_r,
    IFT_IDNLMaterial_averagingtype,

    IFT_MazarsMaterial_version,
    IFT_MazarsMaterial_e0,
    IFT_MazarsMaterial_ac,
    IFT_MazarsMaterial_bc,
    IFT_MazarsMaterial_beta,
    IFT_MazarsMaterial_at,
    IFT_MazarsMaterial_bt,
    IFT_MazarsMaterial_ef,
    IFT_MazarsMaterial_r,
    IFT_MazarsMaterial_hreft,
    IFT_MazarsMaterial_hrefc,

    IFT_MazarsNLMaterial_r,

    IFT_DruckerPragerPlasticitySM_iys,
    IFT_DruckerPragerPlasticitySM_alpha,
    IFT_DruckerPragerPlasticitySM_alphapsi,
    IFT_DruckerPragerPlasticitySM_ht,
    IFT_DruckerPragerPlasticitySM_hm,
    IFT_DruckerPragerPlasticitySM_kc,
    IFT_DruckerPragerPlasticitySM_lys,
    IFT_DruckerPragerPlasticitySM_yieldtol,
    IFT_DruckerPragerPlasticitySM_newtoniter,

    IFT_Masonry02_ft0,
    IFT_Masonry02_gfi,
    IFT_Masonry02_gfii,
    IFT_Masonry02_kn,
    IFT_Masonry02_ks,
    IFT_Masonry02_c0,
    IFT_Masonry02_tanfi0,
    IFT_Masonry02_tanfir,
    IFT_Masonry02_tanpsi,
    IFT_Masonry02_cnn,
    IFT_Masonry02_css,
    IFT_Masonry02_cn,
    IFT_Masonry02_si,
    IFT_Masonry02_sp,
    IFT_Masonry02_sm,
    IFT_Masonry02_sr,
    IFT_Masonry02_kp,
    IFT_Masonry02_km,
    IFT_Masonry02_kr,
    IFT_Masonry02_cplane,

    IFT_IsoInterfaceDamageMaterial_kn,
    IFT_IsoInterfaceDamageMaterial_ks,
    IFT_IsoInterfaceDamageMaterial_ft,
    IFT_IsoInterfaceDamageMaterial_gf,
    IFT_IsoInterfaceDamageMaterial_maxOmega,
    IFT_IsoInterfaceDamageMaterial_talpha,

    IFT_CebFipSlip90Material_tmax,
    IFT_CebFipSlip90Material_tres,
    IFT_CebFipSlip90Material_s1,
    IFT_CebFipSlip90Material_s2,
    IFT_CebFipSlip90Material_s3,


    IFT_J2Mat_ry,
    IFT_J2Mat_khm,
    IFT_J2Mat_ihm,
    IFT_J2Mat_rma,

    IFT_MDM_talpha,
    IFT_MDM_parmd,
    IFT_MDM_nonloc,
    IFT_MDM_r,
    IFT_MDM_efp,
    IFT_MDM_ep,
    IFT_MDM_gf,
    IFT_MDM_ft,
    IFT_MDM_formulation,
    IFT_MDM_mode,
    IFT_MDM_mapper,

    IFT_Steel1_ry,

    IFT_J2plasticMaterial_ry,
    IFT_J2plasticMaterial_khm,
    IFT_J2plasticMaterial_ihm,

    IFT_J2MPlasticMaterial_ry,
    IFT_J2MPlasticMaterial_khm,
    IFT_J2MPlasticMaterial_ihm,
    IFT_J2MPlasticMaterial_rma,

    IFT_RankinePlasticMaterial_ry,

    IFT_HellmichMaterial_E,
    IFT_HellmichMaterial_nu,
    IFT_HellmichMaterial_linearE,
    IFT_HellmichMaterial_epscu,
    IFT_HellmichMaterial_fc,
    IFT_HellmichMaterial_tAlpha,
    IFT_HellmichMaterial_isoT,
    IFT_HellmichMaterial_Tltf,
    IFT_HellmichMaterial_hltf,
    IFT_HellmichMaterial_iniT,
    IFT_HellmichMaterial_baseT,
    IFT_HellmichMaterial_flatT,
    IFT_HellmichMaterial_hemomat,
    IFT_HellmichMaterial_hydration,
    IFT_HellmichMaterial_timeScale,
    IFT_HellmichMaterial_shr,
    IFT_HellmichMaterial_noshr,
    IFT_HellmichMaterial_ashr,
    IFT_HellmichMaterial_bshr,
    IFT_HellmichMaterial_kshr,
    IFT_HellmichMaterial_dryingc,
    IFT_HellmichMaterial_nocreep,
    IFT_HellmichMaterial_modulusH,
    IFT_HellmichMaterial_ur,
    IFT_HellmichMaterial_jv,
    IFT_HellmichMaterial_tw,
    IFT_HellmichMaterial_devc,
    IFT_HellmichMaterial_noplast,
    IFT_HellmichMaterial_zeroalpha,
    IFT_HellmichMaterial_nohardening,
    IFT_HellmichMaterial_approxnewton,
    IFT_HellmichMaterial_computedl,
    IFT_HellmichMaterial_plotss,
    IFT_HellmichMaterial_pssiter,
    IFT_HellmichMaterial_psselem,
    IFT_HellmichMaterial_pssgp,
    IFT_HellmichMaterial_prestress,
    IFT_HellmichMaterial_prestressFrom,
    IFT_HellmichMaterial_prestressTo,
    IFT_HellmichMaterial_c60mix,

    IFT_HyperElasticMaterial_k,
    IFT_HyperElasticMaterial_g,

    IFT_MisesMat_sig0,
    IFT_MisesMat_h,
    IFT_MisesMat_omega_crit,
    IFT_MisesMat_a,

    IFT_CohSur3d_kx,
    IFT_CohSur3d_ky,
    IFT_CohSur3d_kz,

    IFT_HydrationModel_hydration,
    IFT_HydrationModel_c60mix,
    IFT_HydrationModel_timeScale,
    IFT_HydrationModel_hheat,
    IFT_HydrationModel_cv,
    IFT_HydrationModel_water,

    IFT_HydratingIsoHeatMaterial_hydration,
    IFT_HydratingIsoHeatMaterial_mix,
    IFT_HydratingIsoHeatMaterial_noHeat,
    IFT_HydratingIsoHeatMaterial_noLHS,

    IFT_HydratingHeMoMaterial_hydration,
    IFT_HydratingHeMoMaterial_mix,
    IFT_HydratingHeMoMaterial_noHeat,
    IFT_HydratingHeMoMaterial_noLHS,

    IFT_HydrationModelInterface_hydration,
    IFT_HydrationModelInterface_castAt,

    IFT_TrabBoneMaterial_E0,
    IFT_TrabBoneMaterial_Eil,
    IFT_TrabBoneMaterial_Eie,
    IFT_TrabBoneMaterial_kie,
    IFT_TrabBoneMaterial_Ek,
    IFT_TrabBoneMaterial_Cc,
    IFT_TrabBoneMaterial_Cc2,
    IFT_TrabBoneMaterial_EpsC,
    IFT_TrabBoneMaterial_SigYp,
    IFT_TrabBoneMaterial_SigYn,
    IFT_TrabBoneMaterial_adam,

    IFT_TrabBoneNL_r,
    IFT_TrabBoneNL_m,

    IFT_TrabBone3D_eps0,
    IFT_TrabBone3D_nu0,
    IFT_TrabBone3D_mu0,
    IFT_TrabBone3D_expk,
    IFT_TrabBone3D_expl,

    IFT_TrabBone3D_m1,
    IFT_TrabBone3D_m2,
    IFT_TrabBone3D_rho,

    IFT_TrabBone3D_sig0Pos,
    IFT_TrabBone3D_sig0Neg,
    IFT_TrabBone3D_chi0Pos,
    IFT_TrabBone3D_chi0Neg,
    IFT_TrabBone3D_tau0,
    IFT_TrabBone3D_expq,
    IFT_TrabBone3D_plasHardFactor,
    IFT_TrabBone3D_expPlasHard,

    IFT_TrabBone3D_expDam,
    IFT_TrabBone3D_critDam,

    IFT_TrabBone3D_gamDens,
    IFT_TrabBone3D_tDens,
    IFT_TrabBone3D_JCrit,

    IFT_TrabBoneNL3D_r,
    IFT_TrabBoneNL3D_m,

    IFT_TrabBoneEmbed_eps0,
    IFT_TrabBoneEmbed_nu0,
    IFT_TrabBoneEmbed_mu0,
    IFT_TrabBoneEmbed_rho,

    IFT_TrabBoneNLEmbed_r,
    IFT_TrabBoneNLEmbed_m,

    IFT_ConcreteDPM_fc,
    IFT_ConcreteDPM_ft,
    IFT_ConcreteDPM_ecc,
    IFT_ConcreteDPM_kinit,
    IFT_ConcreteDPM_ahard,
    IFT_ConcreteDPM_bhard,
    IFT_ConcreteDPM_chard,
    IFT_ConcreteDPM_dhard,
    IFT_ConcreteDPM_asoft,
    IFT_ConcreteDPM_bsoft,
    IFT_ConcreteDPM_dilation,
    IFT_ConcreteDPM_yieldtol,
    IFT_ConcreteDPM_newtoniter,
    IFT_ConcreteDPM_ef,
    IFT_ConcreteDPM_cycmode,
    IFT_ConcreteDPM_cycpar,
    IFT_ConcreteDPM_reltime,
    IFT_ConcreteDPM_rateexp,
    IFT_ConcreteDPM_href,

    IFT_ConcreteDPMnlMaterial_r,
    IFT_ConcreteDPMnlMaterial_m,

    IFT_NewtonianFluidMaterial_mu,

    IFT_BinghamFluidMaterial_mu0,
    IFT_BinghamFluidMaterial_tau0,
    IFT_BinghamFluidMaterial_muinf,

    IFT_TwoFluidMaterial_mat,

    IFT_CompRowPrecond_droptol,
    IFT_CompRowPrecond_partfill,

    IFT_NonlocalMaterialExtensionInterface_regionmap,
    IFT_NonlocalMaterialExtensionInterface_permanentNonlocTableFlag,

    IFT_OutputManager_name,
    IFT_OutputManager_tstepall,
    IFT_OutputManager_tstepstep,
    IFT_OutputManager_dofmanall,
    IFT_OutputManager_elementall,
    IFT_OutputManager_tstepsout,
    IFT_OutputManager_dofmanoutput,
    IFT_OutputManager_dofmanexcept,
    IFT_OutputManager_elementoutput,
    IFT_OutputManager_elementexcept,


    IFT_HeavisideLTF_origin,
    IFT_HeavisideLTF_value,

    IFT_PeakFunction_t,
    IFT_PeakFunction_ft,

    IFT_PiecewiseLinFunction_npoints,
    IFT_PiecewiseLinFunction_t,
    IFT_PiecewiseLinFunction_ft,

    IFT_PeriodicPiecewiseLinFunction_period,
    IFT_PeriodicPiecewiseLinFunction_addtf,

    IFT_UserDefinedLoadTimeFunction_ft,

    IFT_UserDefinedTemperatureField_size,
    IFT_UserDefinedTemperatureField_t1,
    IFT_UserDefinedTemperatureField_t2,
    IFT_UserDefinedTemperatureField_t3,

    IFT_PolylineNonlocalBarrier_vertexnodes,
    IFT_PolylineNonlocalBarrier_xcoordindx,
    IFT_PolylineNonlocalBarrier_ycoordindx,

    IFT_SymmetryBarrier_origin,
    IFT_SymmetryBarrier_normals,
    IFT_SymmetryBarrier_activemask,



    IFT_ErrorEstimator_regionskipmap,

    IFT_ScalarErrorIndicator_vartype,

    IFT_DirectErrorIndicatorRC_minlim,
    IFT_DirectErrorIndicatorRC_maxlim,
    IFT_DirectErrorIndicatorRC_mindens,
    IFT_DirectErrorIndicatorRC_maxdens,
    IFT_DirectErrorIndicatorRC_defdens,
    IFT_DirectErrorIndicatorRC_remeshingdensityratio,

    IFT_ZZErrorEstimator_normtype,
    IFT_ZZErrorEstimator_recoverytype,
    IFT_ZZRemeshingCriteria_requirederror,
    IFT_ZZRemeshingCriteria_minelemsize,


    IFT_HuertaErrorEstimator_normtype,
    IFT_HuertaErrorEstimator_refinelevel,
    IFT_HuertaErrorEstimator_requirederror,
    IFT_HuertaErrorEstimator_skipsteps,
    IFT_HuertaErrorEstimator_initialskipsteps,
    IFT_HuertaErrorEstimator_werror,
    IFT_HuertaErrorEstimator_permat,
    IFT_HuertaErrorEstimator_impmat,
    IFT_HuertaErrorEstimator_imppos,
    IFT_HuertaErrorEstimator_exact,

    IFT_HuertaRemeshingCriteria_requirederror,
    IFT_HuertaRemeshingCriteria_minelemsize,
    IFT_HuertaRemeshingCriteria_noremesh,
    IFT_HuertaRemeshingCriteria_werror,
    IFT_HuertaRemeshingCriteria_refinecoeff,

    IFT_HuertaErrorEstimatorInterface_coords,

    IFT_MMALeastSquareProjection_statefilter,
    IFT_MMALeastSquareProjection_regionfilter,

    IFT_LEPLIC_refVol,

    IFT_LSPCS_levelSetValues,
    IFT_LSPCS_refmatpoly_x,
    IFT_LSPCS_refmatpoly_y,
    IFT_LSPCS_reinit_dt,
    IFT_LSPCS_reinit_err,
    IFT_LSPCS_reinit_alg,
    IFT_LSPCS_nsd,
    IFT_LSPCS_ci1,
    IFT_LSPCS_ci2,

    IFT_LoadBalancer_wtp,
    IFT_LoadBalancerMonitor_nodeWeightMode,
    IFT_LoadBalancerMonitor_initialnodeweights,
    IFT_WallClockLoadBalancerMonitor_relwct,
    IFT_WallClockLoadBalancerMonitor_abswct,
    IFT_WallClockLoadBalancerMonitor_minwct,
    IFT_WallClockLoadBalancerMonitor_lbstep,
    IFT_WallClockLoadBalancerMonitor_perturbedsteps,
    IFT_WallClockLoadBalancerMonitor_perturbfactor,
    IFT_WallClockLoadBalancerMonitor_recoveredsteps,
    IFT_WallClockLoadBalancerMonitor_processingweights,

    IFT_LocalGaussianRandomGenerator_mean,
    IFT_LocalGaussianRandomGenerator_variance,
    IFT_LocalGaussianRandomGenerator_seed,

    IFT_RandomMaterialExt_randVariables,
    IFT_RandomMaterialExt_randGen,

    IFT_XfemManager_numberOfGeometryItems,
    IFT_XfemManager_numberOfEnrichmentItems,
    IFT_XfemManager_numberOfEnrichmentFunctions,
    IFT_XfemManager_name,

    IFT_Circle_center,
    IFT_Circle_radius,

    IFT_Line_start,
    IFT_Line_end,

    IFT_EnrichmentItem_geometryItemNr,
    IFT_EnrichmentItem_enrichmentFunctionNr,
    IFT_EnrichmentItem_materialNr,

    IFT_Unknown
};


/**
 * Macro simplifying the erorr reporting.
 */
#define IR_IOERR(__class, __proc, __id, __keyword, __ir, __result) \
    __ir->report_error(__class, __proc, __id, __keyword, __result, __FILE__, __LINE__);

/**
 * Macro facilitating the use of input record reading methods.
 * uses the given input record (__ir parameter) and reads the compulsory
 * field identified by __kwd and stores the  result into __value parameter.
 * Includes also the erorr reporting.
 */
#define IR_GIVE_FIELD(__ir, __value, __id, __kwd) result = __ir->giveField(__value, __id, __kwd); \
    if ( result != IRRT_OK ) { IR_IOERR(giveClassName(), __proc, __id, __kwd, __ir, result); }

/**
 * Macro facilitating the use of input record reading methods.
 * uses the given input record (__ir parameter) and reads the optional
 * field identified by __kwd and stores the  result into __value parameter.
 * Includes also the erorr reporting.
 */
#define IR_GIVE_OPTIONAL_FIELD(__ir, __value, __id, __kwd) result = __ir->giveOptionalField(__value, __id, __kwd); \
    if ( result != IRRT_OK ) { IR_IOERR(giveClassName(), __proc, __id, __kwd, __ir, result); }

/**
 * Macro facilitating the use of input record reading methods.
 * uses the given input record (__ir parameter) and reads the compulsory
 * field identified by __kwd and stores the  result into __value parameter.
 * Includes also the erorr reporting.
 */
#define IR_GIVE_FIELD2(__ir, __value, __id, __kwd, __opt) result = __ir->giveField(__value, __opt, __id, __kwd); \
    if ( result != IRRT_OK ) { IR_IOERR(giveClassName(), __proc, __id, __kwd, __ir, result); }

/**
 * Macro facilitating the use of input record reading methods.
 * uses the given input record (__ir parameter) and reads the optional
 * field identified by __kwd and stores the  result into __value parameter.
 * Includes also the erorr reporting.
 */
#define IR_GIVE_OPTIONAL_FIELD2(__ir, __value, __id, __kwd, __opt) \
    result = __ir->giveOptionalField(__value, __opt, __id, __kwd); \
    if ( result != IRRT_OK ) { IR_IOERR(giveClassName(), __proc, __id, __kwd, __ir, result); }
/**
 * Macro facilitating the use of input record reading methods.
 * uses the given input record (__ir parameter) and reads the compulsory record keyword (__kwd)
 * and its number (__value param). Includes also the erorr reporting.
 */
#define IR_GIVE_RECORD_KEYWORD_FIELD(__ir, __name, __value, __opt) \
    result = __ir->giveRecordKeywordField(__name, __value, __opt); \
    if ( result != IRRT_OK ) { IR_IOERR(giveClassName(), __proc, IFT_RecordIDField, "RecordIDField", __ir, result); }



/**
 * Class representing the general Input Record. The input record consists of several fields.
 * Provides several requesting functions for reading field values. The derived classes of
 * Input record can represent database records or text file records, allowing the transparent
 * input operations.
 * The input record after init phase should "contain" all relevant data, so the input record should
 * resolve all dependencies. THis allows to create a copy of input record instance for later use
 * without the need to re-open input files (used for metasteps).
 */
class InputRecord
{
protected:
public:
    /// Constructor. Creates an empty input record.
    InputRecord();
    /// Copy constructor
    InputRecord(const InputRecord &);
    /// Destructor
    virtual ~InputRecord() { }
    // Assingnment operator
    InputRecord &operator=(const InputRecord &);

    /** Creates a newly allocated copy of the receiver */
    virtual InputRecord *GiveCopy() = 0;

    /**@name Compulsory field extraction methods
     * Reads the field value identified by keyword
     * @param answer contains result
     * @param idString field keyword
     * @return IRResultType
     */
    //@{
    /// Reads the record id field  (type of record) and its corresponding number
    virtual IRResultType giveRecordKeywordField(char *answer, int &value, int maxchar) = 0;
    /// Reads the record id field  (type of record)
    virtual IRResultType giveRecordKeywordField(char *answer, int maxchar) = 0;
    /// Reads the integer field value
    virtual IRResultType giveField(int &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the double field value
    virtual IRResultType giveField(double &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the char* field value
    virtual IRResultType giveField(char *answer, int maxchar, const InputFieldType fieldI, const char *idString) = 0;
    /// Reads the FloatArray field value
    virtual IRResultType giveField(FloatArray &answer, const InputFieldType fieldI, const char *idString) = 0;
    /// Reads the IntArray field value
    virtual IRResultType giveField(IntArray &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the FloatMatrix field value
    virtual IRResultType giveField(FloatMatrix &answer, const InputFieldType fieldI, const char *idString) = 0;
    /// Reads the Dictionary field value
    virtual IRResultType giveField(Dictionary &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the dynaList<Range> field value
    virtual IRResultType giveField(dynaList< Range > &answer, const InputFieldType fieldID, const char *idString) = 0;
    //@}

    /**@name Optional field extraction methods
     * Reads the field value identified by keyword
     * @param answer contains result
     * @param idString field keyword
     * @return IRResultType
     */
    //@{
    /// Reads the integer field value
    virtual IRResultType giveOptionalField(int &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the double field value
    virtual IRResultType giveOptionalField(double &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the char* field value
    virtual IRResultType giveOptionalField(char *answer, int maxchar, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the FloatArray field value
    virtual IRResultType giveOptionalField(FloatArray &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the IntArray field value
    virtual IRResultType giveOptionalField(IntArray &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the FloatMatrix field value
    virtual IRResultType giveOptionalField(FloatMatrix &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the Dictionary field value
    virtual IRResultType giveOptionalField(Dictionary &answer, const InputFieldType fieldID, const char *idString) = 0;
    /// Reads the dynaList<Range> field value
    virtual IRResultType giveOptionalField(dynaList< Range > &answer, const InputFieldType fieldID, const char *idString) = 0;
    //@}

    /// Returns true if record contains field identified by idString keyword
    virtual bool         hasField(const InputFieldType fieldID, const char *idString) = 0;

    /// Returns error string corresponding to given value of IRResultType type
    const char *strerror(IRResultType);

    /// Prints the error message
    void report_error(const char *_class, const char *proc, const InputFieldType fieldID, const char *kwd,
                      IRResultType result, const char *file, int line);

    /** terminates the current record session and if the flag is true, warning is printed for unscanned tokens */
    virtual void finish(bool wrn = true) = 0;
};

} // end namespace oofem
#endif // inputrecord_h
